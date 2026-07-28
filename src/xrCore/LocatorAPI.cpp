// LocatorAPI.cpp: implementation of the CLocatorAPI class.
//
//////////////////////////////////////////////////////////////////////

// #include <direct.h>
#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <optional>
#include <regex>
#include <fstream>
#include <chrono>
#include <string>
#include <string_view>
#include <sys/stat.h>
#include <stdlib.h>
#include <rt_compressor.h>
#include <string_concatenations.h>
#include <system_error>
#include <xr_ini.h>
#include <xr_trims.h>

#include "FS.h"
#include "_std_extensions.h"
#include "xrCore.h"
#include "FTimer.h"
#include "FileSystem.h"
#include "FS_internal.h"
#include "LocatorAPI.h"
#include "stream_reader.h"
#include "file_stream_reader.h"
#include "xrDebug_macros.h"

const u32 BIG_FILE_READER_WINDOW_SIZE = 1024 * 1024;

//typedef void DUMMY_STUFF (const void*,const u32&,void*);
//XRCORE_API DUMMY_STUFF *g_temporary_stuff = 0;

CLocatorAPI* xr_FS = NULL;

#ifdef _EDITOR
# define FSLTX "fs.ltx"
#else
# define FSLTX "fsgame.ltx"
#endif

std::filesystem::path fsRoot;

struct _open_file
{
	union
	{
		IReader* _reader;
		CStreamReader* _stream_reader;
	};

	shared_str _fn;
	u32 _used;
};

template <typename T>
struct eq_pointer;

template <>
struct eq_pointer<IReader>
{
	IReader* _val;

	eq_pointer(IReader* p) : _val(p)
	{
	}

	bool operator ()(_open_file& itm)
	{
		return (_val == itm._reader);
	}
};

template <>
struct eq_pointer<CStreamReader>
{
	CStreamReader* _val;

	eq_pointer(CStreamReader* p) : _val(p)
	{
	}

	bool operator ()(_open_file& itm)
	{
		return (_val == itm._stream_reader);
	}
};

struct eq_fname_free
{
	shared_str _val;
	eq_fname_free(shared_str s) { _val = s; }

	bool operator ()(_open_file& itm)
	{
		return (_val == itm._fn && itm._reader == NULL);
	}
};

struct eq_fname_check
{
	shared_str _val;
	eq_fname_check(shared_str s) { _val = s; }

	bool operator ()(_open_file& itm)
	{
		return (_val == itm._fn && itm._reader != NULL);
	}
};

XRCORE_API xr_vector<_open_file> g_open_files;

void _check_open_file(const shared_str& _fname)
{
	xr_vector<_open_file>::iterator it = std::find_if(g_open_files.begin(), g_open_files.end(), eq_fname_check(_fname));
	if (it != g_open_files.end())
		Log("file opened at least twice", _fname.c_str());
}

_open_file& find_free_item(const shared_str& _fname)
{
	xr_vector<_open_file>::iterator it = std::find_if(g_open_files.begin(), g_open_files.end(), eq_fname_free(_fname));
	if (it == g_open_files.end())
	{
		g_open_files.resize(g_open_files.size() + 1);
		_open_file& _of = g_open_files.back();
		_of._fn = _fname;
		_of._used = 0;
		return _of;
	}
	return *it;
}

void setup_reader(CStreamReader* _r, _open_file& _of)
{
	_of._stream_reader = _r;
}

void setup_reader(IReader* _r, _open_file& _of)
{
	_of._reader = _r;
}

template <typename T>
void _register_open_file(T* _r, LPCSTR _fname)
{
	xrCriticalSection _lock;
	_lock.Enter();

	shared_str f = _fname;
	_check_open_file(f);

	_open_file& _of = find_free_item(_fname);
	setup_reader(_r, _of);
	_of._used += 1;

	_lock.Leave();
}

template <typename T>
void _unregister_open_file(T* _r)
{
	xrCriticalSection _lock;
	_lock.Enter();

	xr_vector<_open_file>::iterator it = std::find_if(g_open_files.begin(), g_open_files.end(), eq_pointer<T>(_r));
	VERIFY(it != g_open_files.end());
	_open_file& _of = *it;
	_of._reader = NULL;
	_lock.Leave();
}

XRCORE_API void _dump_open_files(int mode)
{
	xr_vector<_open_file>::iterator it = g_open_files.begin();
	xr_vector<_open_file>::iterator it_e = g_open_files.end();

	bool bShow = false;
	if (mode == 1)
	{
		for (; it != it_e; ++it)
		{
			_open_file& _of = *it;
			if (_of._reader != NULL)
			{
				if (!bShow)
					Log("----opened files");

				bShow = true;
				Msg("[%d] fname:%s", _of._used, _of._fn.c_str());
			}
		}
	}
	else
	{
		Log("----un-used");
		for (it = g_open_files.begin(); it != it_e; ++it)
		{
			_open_file& _of = *it;
			if (_of._reader == NULL)
				Msg("[%d] fname:%s", _of._used, _of._fn.c_str());
		}
	}
	if (bShow)
		Log("----total count=", g_open_files.size());
}

CLocatorAPI::CLocatorAPI()
{
	m_Flags.zero();
	m_iLockRescan = 0;
	dwOpenCounter = 0;
}

CLocatorAPI::~CLocatorAPI()
{
	VERIFY(0 == m_iLockRescan);
	_dump_open_files(1);
}

void CLocatorAPI::Register(std::fs::path path, u32 vfs, u32 crc, u32 ptr, u32 size_real, u32 size_compressed, time_t modif)
{
	// try to add a folder before
	auto parent_path = vfs::parent_path(path);
	if (m_files.find({.name = parent_path}) == m_files.end()) {
		m_files.insert(file {
			.name = xr_pathlwr(parent_path),
			.vfs = vfs,
			.crc = 0,
			.ptr = 0,
			.size_real = 0,
			.size_compressed = 0,
			.modif = u32(-1),
		});
	}
	
	m_files.insert(file {
		.name = xr_pathlwr(path),
		.vfs = vfs,
		.crc = crc,
		.ptr = ptr,
		.size_real = size_real,
		.size_compressed = size_compressed,
		.modif = modif,
	});
}

IReader* open_chunk(std::fs::path path, u32 ID)
{
	std::ifstream file(path, std::ios::binary);
	VERIFY(file.is_open());
	file.seekg(0);

	uint32_t type{}, size{};
	while (true) {
		file.read(reinterpret_cast<char*>(&type), 4);
		file.read(reinterpret_cast<char*>(&size), 4);

		if ((type & (~CFS_CompressMark)) == ID) {
			u8* data = xr_alloc<u8>(size);
			file.read(reinterpret_cast<char*>(data), size);

			if (type & CFS_CompressMark) {
				BYTE* dest;
				unsigned dest_sz;
				_decompressLZ(&dest, &dest_sz, data, size);
				xr_free(data);
				return xr_new<IReader>(dest, dest_sz, 0);
			} else {
				return xr_new<IReader>(data, size, 0);
			}
		}
		else {
			file.seekg(size, std::ios::cur);
			if (!file)
				return nullptr;
		}
	}

	return nullptr;
};

void CLocatorAPI::LoadArchive(archive& A, LPCSTR entrypoint)
{
	// Create base path
	std::fs::path fs_entry_point;
	if (A.header)
	{
		shared_str read_path = A.header->r_string("header", "entry_point");
		if (0 == _stricmp(read_path.c_str(), "gamedata"))
		{
			PathPairIt P = pathes.find("$fs_root$");
			if (P != pathes.end())
			{
				FS_Path* root = P->second;
				// R_ASSERT3 (root, "path not found ", read_path.c_str());
				fs_entry_point = root->m_Path;
			}
			fs_entry_point = fs_entry_point / "gamedata";
		}
		else
		{
			string256 alias_name;
			alias_name[0] = 0;
			R_ASSERT2(*read_path.c_str() == '$', read_path.c_str());

			int count = sscanf(read_path.c_str(), "%[^\\]s", alias_name);
			R_ASSERT2(count == 1, read_path.c_str());

			PathPairIt P = pathes.find(alias_name);

			if (P != pathes.end())
			{
				FS_Path* root = P->second;
				// R_ASSERT3 (root, "path not found ", alias_name);
				fs_entry_point =  root->m_Path;
			}
			// TODO: make it better
			std::string a = read_path.c_str() + xr_strlen(alias_name) + 1;
			normalize_path(a);
			fs_entry_point = fs_entry_point / a;
		}
	}
	else
	{
		R_ASSERT2(0, "unsupported");
		fs_entry_point = A.path.c_str();
	}
	
	if (entrypoint)
		fs_entry_point = entrypoint;

	// Read FileSystem
	A.open();
	auto hdr = open_chunk(A.path, 1);
	R_ASSERT(hdr);
	RStringVec fv;
	while (!hdr->eof())
	{
		string_path name;
		string1024 buffer_start;
		u16 buffer_size = hdr->r_u16();
		VERIFY(buffer_size < sizeof(name) + 4 * sizeof(u32));
		VERIFY(buffer_size < sizeof(buffer_start));
		u8* buffer = (u8*)&*buffer_start;
		hdr->r(buffer, buffer_size);

		u32 size_real = *(u32*)buffer;
		buffer += sizeof(size_real);

		u32 size_compr = *(u32*)buffer;
		buffer += sizeof(size_compr);

		u32 crc = *(u32*)buffer;
		buffer += sizeof(crc);

		u32 name_length = buffer_size - 4 * sizeof(u32);
		Memory.mem_copy(name, buffer, name_length);
		name[name_length] = 0;
		buffer += buffer_size - 4 * sizeof(u32);

		u32 ptr = *(u32*)buffer;
		buffer += sizeof(ptr);

		normalize_path(name);

		Register(fs_entry_point / name, A.vfs_idx, crc, ptr, size_real, size_compr, 0);
	}
	hdr->close();
}

void CLocatorAPI::archive::open()
{
	if (fileMapping)
		return;

	try {
		fileMapping = std::make_shared<boost::interprocess::file_mapping>(path.c_str(), boost::interprocess::read_only);
		size = std::fs::file_size(path);
	} catch (...) {
		Msg("Failed to load archive: %s", path.c_str());
	}
}

void CLocatorAPI::archive::close()
{
	fileMapping.reset();
}

void CLocatorAPI::ProcessArchive(std::fs::path path)
{
	// find existing archive
	for (archives_it it = m_archives.begin(); it != m_archives.end(); ++it)
		if (it->path == path)
			return;

	m_archives.push_back(archive());
	archive& A = m_archives.back();
	A.vfs_idx = m_archives.size() - 1;
	A.path = path;

	A.open();

	// Read header
	BOOL bProcessArchiveLoading = TRUE;

	// DUMMY_STUFF *g_temporary_stuff_subst = NULL;
	// g_temporary_stuff_subst = g_temporary_stuff;
	// g_temporary_stuff = NULL;

	auto hdr = open_chunk(A.path, CFS_HeaderChunkID);
	if (hdr)
	{
		A.header = xr_new<CInifile>(hdr, "archive_header");
		hdr->close();
		bProcessArchiveLoading = A.header->r_bool("header", "auto_load");
	}
	// g_temporary_stuff = g_temporary_stuff_subst;

	if (bProcessArchiveLoading || Core.Params.auto_load_arch)
		LoadArchive(A);
	else
		A.close();
}

void CLocatorAPI::unload_archive(CLocatorAPI::archive& A)
{
	for(const auto& entry : m_files) {
		if (entry.vfs == A.vfs_idx) {
#ifndef MASTER_GOLD
            Msg("unregistering file [%s]", entry.name.c_str());
#endif // #ifndef MASTER_GOLD
			m_files.erase(entry);
			break;
		}
	}
	A.close();
}

bool CLocatorAPI::load_all_unloaded_archives()
{
	bool res = false;
	for (auto& A : m_archives) {
		if (!A.fileMapping) {
			LoadArchive(A);
			res = true;
		}
	}
	return res;
}

IC bool pred_str_ff(const _finddata_t& x, const _finddata_t& y)
{
	return xr_strcmp(x.name, y.name) < 0;
}

bool CLocatorAPI::Recurse(std::fs::path path)
{
	if (!std::fs::exists(path))
		return false;

	for(auto i = std::fs::recursive_directory_iterator(path); i != std::fs::recursive_directory_iterator(); i++) {
		if (std::fs::is_regular_file(i->path())) {
			auto ext = i->path().extension().string();

			if (ext == ".xrignore") {
				i.disable_recursion_pending();
				continue;
			}

			bool is_db = (ext.find(".db") != std::string::npos) || (ext.find(".xdb") != std::string::npos);
			if (is_db && i->path().filename().string() != "Thumbs.db") {
				ProcessArchive(i->path());
				continue;
			}

			auto [fsize, last_modif] = GetFileStat(i->path());

			Register(i->path(), 0xffffffff, 0, 0, fsize, fsize, last_modif);	
		}
		else {
			Register(i->path(), 0xffffffff, 0, 0, 0, 0, 0);
		}
	}
	Register(path, 0xffffffff, 0, 0, 0, 0, 0);
	return true;
}

bool file_handle_internal(std::fs::path file_name, size_t& size, FILE* file_handle);
// void* FileDownload(LPCSTR file_name, const int& file_handle, u32& file_size);

static void searchForFsltx(const char* fs_name, std::fs::path& fsltxPath)
{
	//#TODO: Update code, when std::filesystem is out (not much work, standards don't change dramatically)
	const char* realFsltxName = nullptr;
	if (fs_name)
	{
		realFsltxName = fs_name;
	}
	else
	{
		realFsltxName = FSLTX;
	}

	//try in working dir
	if (std::filesystem::exists(realFsltxName))
	{
		fsltxPath = realFsltxName;
		return;
	}

	auto tryPathFunc = [realFsltxName](std::filesystem::path possibleLocationFsltx,
	                                   std::fs::path& fsltxPath) -> bool
	{
		possibleLocationFsltx.append(realFsltxName);

		if (std::filesystem::exists(possibleLocationFsltx))
		{
			fsltxPath = possibleLocationFsltx;
			return true;
		}
		return false;
	};

	//try parent directory
	if (tryPathFunc("../", fsltxPath)) return;

	//same for application path (fix for launching the game from discord)
	if (tryPathFunc(Core.ApplicationPath, fsltxPath)) return;

	//parent directory again
	if (tryPathFunc(Core.ApplicationPath.parent_path(), fsltxPath)) return;
}

IReader* CLocatorAPI::setup_fs_ltx(LPCSTR fs_name)
{
	std::fs::path fs_path;	
	searchForFsltx(fs_name, fs_path);

	CHECK_OR_EXIT(std::fs::exists(fs_path),
	              make_string("Cannot find fsltx file: \"%s\"\nCheck your working directory", fs_name));
	xr_pathlwr(fs_path);
	fsRoot = fs_path;
	fsRoot = std::filesystem::absolute(fsRoot);
	fsRoot = fsRoot.parent_path();

	Msg("using fs-ltx %s", fs_path.c_str());

	int file_size;
	void* buffer = FileDownload(fs_path, file_size);

	IReader* result = new CTempReader(buffer, (int)file_size, 0);

#ifdef DEBUG
	if (result && m_Flags.is(flBuildCopy | flReady))
		copy_file_to_build(result, fs_path);
#endif // DEBUG

	if (m_Flags.test(flDumpFileActivity))
		_register_open_file(result, fs_path.c_str());

	return (result);
}


void CLocatorAPI::_initialize(u32 flags, LPCSTR target_folder, LPCSTR fs_name)
{
	char _delimiter = '|'; //','
	if (m_Flags.is(flReady))return;
	CTimer t;
	t.Start();
	Log("Initializing File System...");
	size_t M1 = Memory.mem_usage();

	m_Flags.set(flags, TRUE);

	// scan root directory
	bNoRecurse = TRUE;
	string4096 buf;

	// append application path
	if (m_Flags.is(flScanAppRoot))
		append_path("$app_root$", Core.WorkingPath.c_str(), nullptr, FALSE);


	//-----------------------------------------------------------
	// append application data path
	// target folder
	if (m_Flags.is(flTargetFolderOnly))
	{
		append_path("$target_folder$", target_folder, nullptr, TRUE);
	}
	else
	{
		IReader* pFSltx = setup_fs_ltx(fs_name);
		// append all pathes    
		string_path id, root, add, def, capt;
		const char *lp_add, *lp_def, *lp_capt;
		string16 b_v;
		string4096 temp;

		while (!pFSltx->eof())
		{
			pFSltx->r_string(buf, sizeof(buf));
			if (buf[0] == ';') continue;

			_GetItem(buf, 0, id, '=');

			if (!m_Flags.is(flBuildCopy) && (0 == xr_strcmp(id, "$build_copy$")))
				continue;

			_GetItem(buf, 1, temp, '=');
			int cnt = _GetItemCount(temp, _delimiter);
			R_ASSERT2(cnt >= 3, temp);
			u32 fl = 0;
			_GetItem(temp, 0, b_v, _delimiter);

			if (CInifile::IsBOOL(b_v))
				fl |= FS_Path::flRecurse;

			_GetItem(temp, 1, b_v, _delimiter);
			if (CInifile::IsBOOL(b_v))
				fl |= FS_Path::flNotif;

			_GetItem(temp, 2, root, _delimiter);
			_GetItem(temp, 3, add, _delimiter);
			_GetItem(temp, 4, def, _delimiter);
			_GetItem(temp, 5, capt, _delimiter);

			normalize_path(root);
			normalize_path(add);
			xr_strlwr(id);

			xr_strlwr(root);
			lp_add = (cnt >= 4) ? xr_strlwr(add) : nullptr;
			lp_def = (cnt >= 5) ? def : nullptr;
			lp_capt = (cnt >= 6) ? capt : nullptr;

			auto p_it = pathes.find(root);

			if (p_it == pathes.end() && xr_strcmp(root, "$fs_root$") == 0)
			{
				//Old good fsltx
				//replace root with predefined path
				//xr_strcpy(root, fsRoot.generic_string().c_str());
				FS_Path* P = new FS_Path(fsRoot.generic_string().c_str(), "");
				pathes.insert(std::make_pair(xr_strdup("$fs_root$"), P));
				p_it = pathes.find(root);
			}

			FS_Path* P = new FS_Path((p_it != pathes.end()) ? p_it->second->m_Path.c_str() : root, lp_add, lp_def, lp_capt, fl);
			bNoRecurse = !(fl & FS_Path::flRecurse);
			Recurse(P->m_Path);
			auto I = pathes.insert(std::make_pair(xr_strdup(id), P));
#ifndef DEBUG
			m_Flags.set(flCacheFiles, FALSE);
#endif // DEBUG

			//CHECK_OR_EXIT		(I.second,"The file 'fsgame.ltx' is corrupted (it contains duplicated lines).\nPlease reinstall the game or fix the problem manually.");
		}
		r_close(pFSltx);
		R_ASSERT(path_exist("$app_data_root$"));
	};


	Msg("File System Ready...");
	size_t M2 = Memory.mem_usage();
	Msg("FS: %d files cached %d archives, %lldKb memory used.", m_files.size(), m_archives.size(), (M2 - M1) / 1024);

	m_Flags.set(flReady, TRUE);

	Msg("Init FileSystem %f sec", t.GetElapsed_sec());
	//-----------------------------------------------------------
	if (Core.Params.overlaypath)
	{
		auto c_newAppPathRoot = args::get(Core.Params.overlaypath);
		FS_Path* pLogsPath = FS.get_path("$logs$");
		FS_Path* pAppdataPath = FS.get_path("$app_data_root$");


		if (pLogsPath) pLogsPath->_set_root(c_newAppPathRoot.c_str());
		if (pAppdataPath)
		{
			pAppdataPath->_set_root(c_newAppPathRoot.c_str());
			rescan_path(pAppdataPath->m_Path, pAppdataPath->m_Flags.is(FS_Path::flRecurse));
		}
	}
	//-----------------------------------------------------------

	CreateLog(Core.Params.nolog);
}

void CLocatorAPI::_destroy()
{
	CloseLog();
	m_files.clear();
	for (PathPairIt p_it = pathes.begin(); p_it != pathes.end(); p_it++)
	{
		char* str = LPSTR(p_it->first);
		xr_free(str);
		xr_delete(p_it->second);
	}
	pathes.clear();
	for (archives_it a_it = m_archives.begin(); a_it != m_archives.end(); a_it++)
	{
		xr_delete(a_it->header);
		a_it->close();
	}
	m_archives.clear();
}

const CLocatorAPI::file* CLocatorAPI::exist(std::filesystem::path N) {
	return this->exist(N.c_str());
}


const CLocatorAPI::file* CLocatorAPI::exist(const char* fn)
{
	auto str = normalize_path(fn);
	auto it = file_find_it(str.c_str());
	return (it != m_files.end()) ? &(*it) : nullptr;
}

const CLocatorAPI::file* CLocatorAPI::exist(const char* path, const char* name)
{
	string_path temp;
	update_path(temp, path, name);
	return exist(temp);
}

const CLocatorAPI::file* CLocatorAPI::exist(string_path& fn, LPCSTR path, LPCSTR name)
{
	update_path(fn, path, name);
	return exist(fn);
}

const CLocatorAPI::file* CLocatorAPI::exist(std::fs::path& fn, LPCSTR path, LPCSTR name) {
	update_path(fn, path, name);
	return exist(fn);
}


const CLocatorAPI::file* CLocatorAPI::exist(string_path& fn, LPCSTR path, LPCSTR name, LPCSTR ext)
{
	string_path nm;
	strconcat(sizeof(nm), nm, name, ext);
	update_path(fn, path, nm);
	return exist(fn);
}


std::vector<CLocatorAPI::file> CLocatorAPI::file_list_open_impl(const std::string& path, uint32_t flags, std::initializer_list<std::regex> patterns) {
	R_ASSERT(!path.empty());
	VERIFY(flags);
	check_pathes();

	std::fs::path N;

	if (path_exist(path.c_str()))
		update_path(N, path.c_str(), "");
	else
		N = std::fs::path(path);

	std::vector<file> dest {};
	auto begin = m_files.lower_bound({.name = N});

	auto patternMatch = [patterns] (const std::fs::path& p) -> bool {
		auto s = p.string();
		for (const auto& pattern : patterns) {
			if (std::regex_match(s, pattern))
				return true;
		}
		return false;
	};
	auto useRegex = patterns.size() > 0;

	for (auto itt = begin; itt != m_files.end(); itt++) {
		const auto& entry = *itt;
		// FIXME: C++23 std::string::contains.
		if (strncmp(entry.name.c_str(), N.c_str(), N.string().size()) != 0) break;
		if ((flags & FS_RootOnly) != 0 && vfs::parent_path(entry.name) != begin->name) continue;
		if (useRegex && !patternMatch(entry.name)) continue;

		if (vfs::is_regular_file(entry.name)) {
			if ((flags & FS_ListFiles) == 0) continue;

			if (flags & FS_ClampExt) {
				file tmp = entry;
				tmp.name = entry.name.parent_path() / entry.name.stem();
				dest.push_back(tmp);
			}
			else
				dest.push_back(entry);
		}
		else if (vfs::is_directory(entry.name)) {
			if ((flags & FS_ListFolders) == 0) continue;

			dest.push_back(entry);
		}
	}

	return dest;
}

void CLocatorAPI::check_cached_files(LPSTR fname, const u32& fname_size, const file& desc, LPCSTR& source_name)
{
	string_path fname_copy;
	if (pathes.size() <= 1)
		return;

	if (!path_exist("$server_root$"))
		return;

	LPCSTR path_base = get_path("$server_root$")->m_Path.c_str();
	u32 len_base = xr_strlen(path_base);
	LPCSTR path_file = fname;
	u32 len_file = xr_strlen(path_file);
	if (len_file <= len_base)
		return;

	if ((len_base == 1) && (*path_base == '\\'))
		len_base = 0;

	if (0 != memcmp(path_base, fname, len_base))
		return;

	BOOL bCopy = FALSE;

	string_path fname_in_cache;
	update_path(fname_in_cache, "$cache$", path_file + len_base);
	files_it fit = file_find_it(fname_in_cache);
	if (fit != m_files.end())
	{
		// use
		const file& fc = *fit;
		if ((fc.size_real == desc.size_real) && (fc.modif == desc.modif))
		{
			// use
		}
		else
		{
			// copy & use
			Msg("copy: db[%X],cache[%X] - '%s', ", desc.modif, fc.modif, fname);
			bCopy = TRUE;
		}
	}
	else
	{
		// copy & use
		bCopy = TRUE;
	}

	// copy if need
	if (bCopy)
	{
		IReader* _src;
		if (desc.size_real < 256 * 1024) _src = xr_new<CFileReader>(fname);
		else _src = xr_new<CVirtualFileReader>(fname);
		IWriter* _dst = xr_new<CFileWriter>(fname_in_cache, false);
		_dst->w(_src->pointer(), _src->length());
		xr_delete(_dst);
		xr_delete(_src);
		set_file_age(fname_in_cache, desc.modif);
		Register(fname_in_cache, 0xffffffff, 0, 0, desc.size_real, desc.size_real, desc.modif);
	}

	// Use
	source_name = &fname_copy[0];
	xr_strcpy(fname_copy, sizeof(fname_copy), fname);
	xr_strcpy(fname, fname_size, fname_in_cache);
}

void CLocatorAPI::file_from_cache_impl(IReader*& R, LPSTR fname, const file& desc)
{
	if (desc.size_real < 16 * 1024)
	{
		R = xr_new<CFileReader>(fname);
		return;
	}

	R = xr_new<CVirtualFileReader>(fname);
}

void CLocatorAPI::file_from_cache_impl(CStreamReader*& R, LPSTR fname, const file& desc)
{
	CFileStreamReader* r = xr_new<CFileStreamReader>();
	r->construct(fname, BIG_FILE_READER_WINDOW_SIZE);
	R = r;
}

template <typename T>
void CLocatorAPI::file_from_cache(T*& R, LPSTR fname, const u32& fname_size, const file& desc, LPCSTR& source_name)
{
#ifdef DEBUG
    if (m_Flags.is(flCacheFiles))
        check_cached_files(fname, fname_size, desc, source_name);
#endif // DEBUG

	file_from_cache_impl(R, fname, desc);
}

void CLocatorAPI::file_from_archive(IReader*& R, LPCSTR fname, const file& desc)
{
	//TODO: dwAllocGranularity
	// Archived one
	archive& A = m_archives[desc.vfs];
	u32 start = desc.ptr;
	u32 end = desc.ptr + desc.size_compressed;

	if (end > A.size) end = A.size;
	u32 sz = (end - start);
	auto region = boost::interprocess::mapped_region(*A.fileMapping, boost::interprocess::read_only, start, sz);
	u8* ptr = static_cast<u8*>(region.get_address());
	VERIFY3(ptr, "cannot create file mapping on file", fname);

#ifdef FS_DEBUG
	string512 temp;
	xr_sprintf(temp, sizeof(temp), "%s:%s", *A.path.c_str(), fname);
    register_file_mapping(ptr, sz, temp);
#endif // DEBUG

	u8* dest = xr_alloc<u8>(desc.size_real);
	
	if (desc.size_real == desc.size_compressed)
		memcpy(dest, ptr, desc.size_real);
	else
		rtc_decompress(dest, desc.size_real, ptr, desc.size_compressed);
	// Compressed
	
	R = xr_new<CTempReader>(dest, desc.size_real, 0);

#ifdef FS_DEBUG
    unregister_file_mapping(ptr, sz);
#endif // DEBUG
}

void CLocatorAPI::file_from_archive(CStreamReader*& R, LPCSTR fname, const file& desc)
{
	archive& A = m_archives[desc.vfs];
	R_ASSERT2(
		desc.size_compressed == desc.size_real,
		make_string(
			"cannot use stream reading for compressed data %s, do not compress data to be streamed",
			fname
		)
	);

	R = xr_new<CStreamReader>();
	R->construct(
		A.hSrcMap,
		desc.ptr,
		desc.size_compressed,
		A.size,
		BIG_FILE_READER_WINDOW_SIZE
	);
}

void CLocatorAPI::copy_file_to_build(IWriter* W, IReader* r)
{
	W->w(r->pointer(), r->length());
}

void CLocatorAPI::copy_file_to_build(IWriter* W, CStreamReader* r)
{
	u32 buffer_size = r->length();
	u8* buffer = xr_alloc<u8>(buffer_size);
	r->r(buffer, buffer_size);
	W->w(buffer, buffer_size);
	xr_free(buffer);
	r->seek(0);
}

template <typename T>
void CLocatorAPI::copy_file_to_build(T*& r, LPCSTR source_name)
{
	string_path cpy_name;
	string_path e_cpy_name;
	FS_Path* P;
	//if (!(source_name==strstr(source_name,(P=get_path("$server_root$"))->m_Path)||
	// source_name==strstr(source_name,(P=get_path("$server_data_root$"))->m_Path)))
	// return;

	string_path fs_root;
	update_path(fs_root, "$fs_root$", "");
	LPCSTR const position = strstr(source_name, fs_root);
	if (position == source_name)
		update_path(cpy_name, "$build_copy$", source_name + xr_strlen(fs_root));
	else
		update_path(cpy_name, "$build_copy$", source_name);

	IWriter* W = w_open(cpy_name);
	if (!W)
	{
		Log("!Can't build:", source_name);
		return;
	}

	copy_file_to_build(W, r);
	w_close(W);
	set_file_age(cpy_name, get_file_age(source_name));
	if (!m_Flags.is(flEBuildCopy))
		return;

	LPCSTR ext = strext(cpy_name);
	if (!ext)
		return;

	IReader* R = 0;
	if (0 == xr_strcmp(ext, ".dds"))
	{
		P = get_path("$game_textures$");
		update_path(e_cpy_name, "$textures$", source_name + xr_strlen(P->m_Path.c_str()));
		// tga
		*strext(e_cpy_name) = 0;
		xr_strcat(e_cpy_name, ".tga");
		r_close(R = r_open(e_cpy_name));
		// thm
		*strext(e_cpy_name) = 0;
		xr_strcat(e_cpy_name, ".thm");
		r_close(R = r_open(e_cpy_name));
		return;
	}

	if (0 == xr_strcmp(ext, ".ogg"))
	{
		P = get_path("$game_sounds$");
		update_path(e_cpy_name, "$sounds$", source_name + xr_strlen(P->m_Path.c_str()));
		// wav
		*strext(e_cpy_name) = 0;
		xr_strcat(e_cpy_name, ".wav");
		r_close(R = r_open(e_cpy_name));
		// thm
		*strext(e_cpy_name) = 0;
		xr_strcat(e_cpy_name, ".thm");
		r_close(R = r_open(e_cpy_name));
		return;
	}

	if (0 == xr_strcmp(ext, ".object"))
	{
		xr_strcpy(e_cpy_name, sizeof(e_cpy_name), source_name);
		// object thm
		*strext(e_cpy_name) = 0;
		xr_strcat(e_cpy_name, ".thm");
		R = r_open(e_cpy_name);
		if (R) r_close(R);
	}
}

bool CLocatorAPI::check_for_file(LPCSTR path, LPCSTR _fname, string_path& fname, const file*& desc)
{
	// проверить нужно ли пересканировать пути
	check_pathes();

	// correct path
	xr_strcpy(fname, _fname);
	xr_strlwr(fname);
	if (path && path[0])
		update_path(fname, path, fname);

	// Search entry
	file desc_f;
	desc_f.name = fname;

	files_it I = m_files.find(desc_f);
	if (I == m_files.end())
		return (false);

	++dwOpenCounter;
	desc = &*I;
	return (true);
}

#include "../xrGame/Actor_Flags.h"

template <typename T>
T* CLocatorAPI::r_open_impl(LPCSTR path, LPCSTR _fname)
{
	T* R = 0;
	string_path fname;
	const file* desc = 0;
	LPCSTR source_name = &fname[0];

	if (!check_for_file(path, _fname, fname, desc))
	{
		if (m_Flags.test(flPrintLTX))
			Log("Warning : Unable to find", _fname);
		return (0);
	}

	// OK, analyse
	if (0xffffffff == desc->vfs)
		file_from_cache(R, fname, sizeof(fname), *desc, source_name);
	else
		file_from_archive(R, fname, *desc);

#ifdef DEBUG
    if (R && m_Flags.is(flBuildCopy | flReady))
        copy_file_to_build(R, source_name);
#endif // DEBUG

	if (m_Flags.test(flDumpFileActivity))
		_register_open_file(R, fname);

	return (R);
}

CStreamReader* CLocatorAPI::rs_open(LPCSTR path, LPCSTR _fname)
{
	return (r_open_impl<CStreamReader>(path, _fname));
}

IReader* CLocatorAPI::r_open(LPCSTR path, LPCSTR _fname)
{
	static bool p = false;
	if (p) {
		FILE* fw = fopen("/Users/eva00/all_files.txt", "w+");
		for(auto&& f : m_files) {
			fprintf(fw, "%s\n", f.name.c_str());
		}
	}
	return (r_open_impl<IReader>(path, _fname));
}

void CLocatorAPI::r_close(IReader*& fs)
{
	if (m_Flags.test(flDumpFileActivity))
		_unregister_open_file(fs);

	xr_delete(fs);
}

void CLocatorAPI::r_close(CStreamReader*& fs)
{
	if (m_Flags.test(flDumpFileActivity))
		_unregister_open_file(fs);

	fs->close();
}

IWriter* CLocatorAPI::w_open(LPCSTR path, LPCSTR _fname)
{
	string_path fname;
	xr_strcpy(fname, _fname);
	//xr_strlwr(fname); //,".$");
	if (path && path[0]) update_path(fname, path, fname);
	CFileWriter* W = xr_new<CFileWriter>(fname, false);
#ifdef _EDITOR
    if (!W->valid()) xr_delete(W);
#endif
	return W;
}

IWriter* CLocatorAPI::w_open_ex(LPCSTR path, LPCSTR _fname)
{
	string_path fname;
	xr_strcpy(fname, _fname);
	xr_strlwr(fname); //,".$");
	if (path && path[0]) update_path(fname, path, fname);
	CFileWriter* W = xr_new<CFileWriter>(fname, true);
#ifdef _EDITOR
    if (!W->valid()) xr_delete(W);
#endif
	return W;
}

void CLocatorAPI::w_close(IWriter*& S)
{
	if (S)
	{
		R_ASSERT(S->fName.size());
		string_path fname;
		xr_strcpy(fname, sizeof(fname), *S->fName);
		bool bReg = S->valid();
		xr_delete(S);

		if (bReg)
		{
			auto [fsize, last_modif] = GetFileStat(fname);
			Register(fname, 0xffffffff, 0, 0, fsize, fsize, last_modif);
		}
	}
}

CLocatorAPI::files_it CLocatorAPI::file_find_it(LPCSTR fname)
{
	check_pathes();
	return m_files.find({.name = std::fs::path(fname)});
}

BOOL CLocatorAPI::dir_delete(LPCSTR path, LPCSTR nm, BOOL remove_files)
{
	std::fs::path fpath;
	std::error_code e;

	if (path && path[0])
		update_path(fpath, path, nm);
	else 
		fpath = std::fs::path(path);


	auto outOfScope = [fpath] (const std::fs::path& p) {
		return p.string().find(fpath.string()) == std::string::npos ? true : false;
	};

	if (remove_files) {
		std::fs::remove_all(fpath, e);
	} else {
		if (!std::fs::is_directory(fpath)) {
			Msg("Failed to remove dir: %s, %s. it's a file!", path, nm);
			return false;
		}
		std::fs::remove(fpath, e);
	}

	if (e) {
		Msg("Failed to remove dir: %s, %s. Message: %s", path, nm, e.message().c_str());
		return false;
	}

	// cleanup
	for(auto itt = file_find_it(fpath.c_str()); itt != m_files.end(); itt++) {
		const auto& entry = *itt;

		if (outOfScope(entry.name))
			break;

		m_files.erase(itt);
	}

	return true;
}

void CLocatorAPI::file_delete(LPCSTR path, LPCSTR nm)
{
	std::fs::path fpath;

	if (path && path[0])
		update_path(fpath, path, nm);
	else 
		fpath = std::fs::path(path);

	if (auto itt = file_find_it(fpath.c_str()); itt != m_files.end()) {
		const auto& entry = *itt;
		std::error_code e;

		std::fs::remove(entry.name, e);

		if (e) {
			Msg("Failed to remove file: %s, %s. Message: %s", path, nm, e.message().c_str());
			return;
		}

		m_files.erase(itt);
	}
}

void CLocatorAPI::file_copy(LPCSTR src, LPCSTR dest)
{
	if (exist(src))
	{
		IReader* S = r_open(src);
		if (S)
		{
			IWriter* D = w_open(dest);
			if (D)
			{
				D->w(S->pointer(), S->length());
				w_close(D);
			}
			r_close(S);
		}
	}
}

void CLocatorAPI::file_rename(LPCSTR src, LPCSTR dest, bool bOwerwrite)
{
	if (!bOwerwrite && file_find_it(dest) != m_files.end()) {
		m_files.erase(file_find_it(dest));
		return;
	}

	
	if (auto S = file_find_it(src); S != m_files.end()) {
		file newFile = *S;
		std::error_code e;
		std::fs::rename(S->name, std::fs::path(dest), e);

		if (e) {
			Msg("Cant rename file %s to %s. Code: %s", src, dest, e.message().c_str());
			return;
		}
		newFile.name = std::fs::path(dest);
		m_files.erase(S);
		m_files.insert(newFile);

		VerifyPath(dest);
	}
}

int CLocatorAPI::file_length(LPCSTR src)
{
	files_it I = file_find_it(src);
	return (I != m_files.end()) ? I->size_real : -1;
}

bool CLocatorAPI::path_exist(LPCSTR path)
{
	PathPairIt P = pathes.find(path);
	return (P != pathes.end());
}

FS_Path* CLocatorAPI::append_path(LPCSTR path_alias, LPCSTR root, LPCSTR add, BOOL recursive)
{
	VERIFY(root/*&&root[0]*/);
	VERIFY(false == path_exist(path_alias));
	FS_Path* P = xr_new<FS_Path>(root, add, LPCSTR(0), LPCSTR(0), 0);
	bNoRecurse = !recursive;
	Recurse(P->m_Path);
	pathes.insert(mk_pair(xr_strdup(path_alias), P));
	return P;
}

FS_Path* CLocatorAPI::get_path(LPCSTR path)
{
	PathPairIt P = pathes.find(path);
	R_ASSERT2(P != pathes.end(), path);
	return P->second;
}

LPCSTR CLocatorAPI::update_path(string_path& dest, LPCSTR initial, LPCSTR src)
{
	std::fs::path p;
	auto str = std::fs::path(normalize_path(src));
	xr_pathlwr(str);
	get_path(initial)->_update(p, str.c_str());
	std::strncpy(dest, p.c_str(), sizeof(dest));
	return dest;
}

std::fs::path CLocatorAPI::update_path(std::fs::path& dest, LPCSTR initial, std::fs::path src)
{
	normalize_path(src);
	xr_pathlwr(src);
	return get_path(initial)->_update(dest, src);
}

u32 CLocatorAPI::get_file_age(LPCSTR nm)
{
	// проверить нужно ли пересканировать пути
	check_pathes();

	files_it I = file_find_it(nm);
	return (I != m_files.end()) ? I->modif : u32(-1);
}

void CLocatorAPI::set_file_age(LPCSTR nm, u32 age)
{
	// проверить нужно ли пересканировать пути
	check_pathes();

	// set file
	_utimbuf tm;
	tm.actime = age;
	tm.modtime = age;
	int res = _utime(nm, &tm);
	if (0 != res)
	{
		//FIXME:
	{ stub_unix(__func__); }
		//Msg("!Can't set file age: '%s'. Error: '%s'", nm, _sys_errlist[errno]);
	}
	else
	{
		// update record
		files_it I = file_find_it(nm);
		if (I != m_files.end())
		{
			file& F = (file&)*I;
			F.modif = age;
		}
	}
}

//TODO: don't forget to call each time the std::fs::exists()
void CLocatorAPI::rescan_path(std::fs::path full_path, BOOL bRecurse)
{
	file desc;
	desc.name = full_path;
	files_it I = m_files.lower_bound(desc);
	if (I == m_files.end()) return;

	auto outOfScope = [full_path] (const std::fs::path& p) {
		return p.string().find(full_path.string()) == std::string::npos ? true : false;
	};

	auto parentDir = std::fs::is_directory(full_path) ? full_path : full_path.parent_path();

	for(; I != m_files.end(); I++) {
		const auto& entry = *I;
		
		if (outOfScope(entry.name)) break;
		if (entry.vfs != 0xFFFFFFFF) continue;
		if(!bRecurse && entry.name.parent_path() != parentDir) continue;

		m_files.erase(I);
	}
	

	bNoRecurse = !bRecurse;
	Recurse(full_path);
}

void CLocatorAPI::rescan_pathes()
{
	m_Flags.set(flNeedRescan, FALSE);
	for (PathPairIt p_it = pathes.begin(); p_it != pathes.end(); p_it++)
	{
		FS_Path* P = p_it->second;
		if (P->m_Flags.is(FS_Path::flNeedRescan))
		{
			rescan_path(P->m_Path, P->m_Flags.is(FS_Path::flRecurse));
			P->m_Flags.set(FS_Path::flNeedRescan, FALSE);
		}
	}
}

void CLocatorAPI::lock_rescan()
{
	m_iLockRescan++;
}

void CLocatorAPI::unlock_rescan()
{
	m_iLockRescan--;
	VERIFY(m_iLockRescan >= 0);
	if ((0 == m_iLockRescan) && m_Flags.is(flNeedRescan))
		rescan_pathes();
}

void CLocatorAPI::check_pathes()
{
	if (m_Flags.is(flNeedRescan) && (0 == m_iLockRescan))
	{
		lock_rescan();
		rescan_pathes();
		unlock_rescan();
	}
}

BOOL CLocatorAPI::can_write_to_folder(LPCSTR path)
{
	if (path && path[0])
	{
		string_path temp;
		LPCSTR fn = "$!#%TEMP%#!$.$$$";
		strconcat(sizeof(temp), temp, path, path[xr_strlen(path) - 1] != '\\' ? "\\" : "", fn);
		FILE* hf = fopen(temp, "wb");
		if (hf == 0) return FALSE;
		else
		{
			fclose(hf);
			unlink(temp);
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

BOOL CLocatorAPI::can_write_to_alias(LPCSTR path)
{
	string_path temp;
	update_path(temp, path, "");
	return can_write_to_folder(temp);
}

BOOL CLocatorAPI::can_modify_file(LPCSTR fname)
{
	FILE* hf = fopen(fname, "r+b");
	if (hf)
	{
		fclose(hf);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CLocatorAPI::can_modify_file(LPCSTR path, LPCSTR name)
{
	string_path temp;
	update_path(temp, path, name);
	return can_modify_file(temp);
}
