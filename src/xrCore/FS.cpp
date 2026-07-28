#include <cstdio>
#include <filesystem>
#include <sys/stat.h>
#include "FS_internal.h"
#include "LocatorAPI.h"

//////////////////////////////////////////////////////////////////////
// Tools
//////////////////////////////////////////////////////////////////////
//---------------------------------------------------

void* FileDownload(std::fs::path file_path, int& file_size)
{
	auto [size, time] = GetFileStat(file_path);
	file_size = size;
	void* buffer = Memory.mem_alloc(file_size);
	FILE* file = fopen(file_path.c_str(), "rb");

	auto r_bytes = fread(buffer, 1, file_size, file);
	R_ASSERT3(
		file_size == (u32)r_bytes,
		"can't read from file : ",
		file_path.c_str()
	);

	fclose(file);
	return (buffer);
}

typedef char MARK[9];
IC void mk_mark(MARK& M, const char* S)
{
	strncpy_s(M, sizeof(M), S, 8);
}

void FileCompress(const char* fn, const char* sign, void* data, u32 size)
{
	MARK M;
	mk_mark(M, sign);
	//FIXME:
	{ stub_unix(__func__); }
	int H =  0;//open(fn, O_BINARY | O_CREAT | O_WRONLY | O_TRUNC, S_IREAD | S_IWRITE);
	R_ASSERT2(H > 0, fn);
	_write(H, &M, 8);
	_writeLZ(H, data, size);
	_close(H);
}

void* FileDecompress(const char* fn, const char* sign, u32* size)
{
	MARK M, F;
	mk_mark(M, sign);
	//FIXME:
	{ stub_unix(__func__); }
	int H = 0;// open(fn, O_BINARY | O_RDONLY);
	R_ASSERT2(H > 0, fn);
	_read(H, &F, 8);
	if (strncmp(M, F, 8) != 0)
	{
		F[8] = 0;
		Msg("FATAL: signatures doesn't match, file(%s) / requested(%s)", F, sign);
	}
	R_ASSERT(strncmp(M, F, 8) == 0);

	void* ptr = 0;
	u32 SZ;
	SZ = _readLZ(H, ptr, filelength(H) - 8);
	_close(H);
	if (size) *size = SZ;
	return ptr;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//---------------------------------------------------
// memory
CMemoryWriter::~CMemoryWriter()
{
	xr_free(data);
}

void CMemoryWriter::w(const void* ptr, u32 count)
{
	if (position + count > mem_size)
	{
		// reallocate
		if (mem_size == 0) mem_size = 128;
		while (mem_size <= (position + count)) mem_size *= 2;
		if (0 == data)
			data = (BYTE*)Memory.mem_alloc(mem_size);
		else
			data = (BYTE*)Memory.mem_realloc(data, mem_size);
	}
	CopyMemory(data + position, ptr, count);
	position += count;
	if (position > file_size) file_size = position;
}

//static const u32 mb_sz = 0x1000000;
bool CMemoryWriter::save_to(LPCSTR fn)
{
	IWriter* F = FS.w_open(fn);
	if (F)
	{
		F->w(pointer(), size());
		FS.w_close(F);
		return true;
	}
	return false;
}


void IWriter::open_chunk(u32 type)
{
	w_u32(type);
	chunk_pos.push(tell());
	w_u32(0); // the place for 'size'
}

void IWriter::close_chunk()
{
	VERIFY(!chunk_pos.empty());

	int pos = tell();
	seek(chunk_pos.top());
	w_u32(pos - chunk_pos.top() - 4);
	seek(pos);
	chunk_pos.pop();
}

u32 IWriter::chunk_size() // returns size of currently opened chunk, 0 otherwise
{
	if (chunk_pos.empty()) return 0;
	return tell() - chunk_pos.top() - 4;
}

void IWriter::w_compressed(void* ptr, u32 count)
{
	BYTE* dest = 0;
	unsigned dest_sz = 0;
	_compressLZ(&dest, &dest_sz, ptr, count);

	if (dest && dest_sz)
		w(dest, dest_sz);
	xr_free(dest);
}

void IWriter::w_chunk(u32 type, void* data, u32 size)
{
	open_chunk(type);
	if (type & CFS_CompressMark) w_compressed(data, size);
	else w(data, size);
	close_chunk();
}

void IWriter::w_sdir(const Fvector& D)
{
	Fvector C;
	float mag = D.magnitude();
	if (mag > EPS_S)
	{
		C.div(D, mag);
	}
	else
	{
		C.set(0, 0, 1);
		mag = 0;
	}
	w_dir(C);
	w_float(mag);
}

void IWriter::w_printf(const char* format, ...)
{
	va_list mark;
	char buf[1024];

	va_start(mark, format);
#ifndef _EDITOR
	vsprintf_s(buf, format, mark);
#else
    vsprintf(buf, format, mark);
#endif
	va_end(mark);

	w(buf, xr_strlen(buf));
}

//---------------------------------------------------
// base stream
IReader* IReader::open_chunk(u32 ID)
{
	BOOL bCompressed;

	u32 dwSize = find_chunk(ID, &bCompressed);
	if (dwSize != 0)
	{
		if (bCompressed)
		{
			BYTE* dest;
			unsigned dest_sz;
			_decompressLZ(&dest, &dest_sz, pointer(), dwSize);
			return xr_new<CTempReader>(dest, dest_sz, tell() + dwSize);
		}
		else
		{
			return xr_new<IReader>(pointer(), dwSize, tell() + dwSize);
		}
	}
	else return 0;
};

void IReader::close()
{
	//xr_delete((IReader*)this);
	IReader* self = this;
	xr_delete(self);
}

#include "FS_impl.h"


#ifdef FIND_CHUNK_BENCHMARK_ENABLE
find_chunk_counter g_find_chunk_counter;
#endif // FIND_CHUNK_BENCHMARK_ENABLE

u32 IReader::find_chunk(u32 ID, BOOL* bCompressed)
{
	return inherited::find_chunk(ID, bCompressed);
}

IReader* IReader::open_chunk_iterator(u32& ID, IReader* _prev)
{
	if (0 == _prev)
	{
		// first
		rewind();
	}
	else
	{
		// next
		seek(_prev->iterpos);
		_prev->close();
	}

	// open
	if (elapsed() < 8) return NULL;
	ID = r_u32();
	u32 _size = r_u32();
	if (ID & CFS_CompressMark)
	{
		// compressed
		u8* dest;
		unsigned dest_sz;
		_decompressLZ(&dest, &dest_sz, pointer(), _size);
		return xr_new<CTempReader>(dest, dest_sz, tell() + _size);
	}
	else
	{
		// normal
		return xr_new<IReader>(pointer(), _size, tell() + _size);
	}
}

void IReader::r(void* p, int cnt)
{
	VERIFY(Pos + cnt <= Size);
	CopyMemory(p, pointer(), cnt);
	advance(cnt);
#ifdef DEBUG
    BOOL bShow = FALSE;
    if (fast_dynamic_cast<CFileReader*>(this)) bShow = TRUE;
    if (fast_dynamic_cast<CVirtualFileReader*>(this)) bShow = TRUE;
    if (bShow)
    {
        FS.dwOpenCounter++;
    }
#endif
};

IC BOOL is_term(char a) { return (a == 13) || (a == 10); };
IC u32 IReader::advance_term_string()
{
	u32 sz = 0;
	char* src = (char*)data;
	while (!eof())
	{
		Pos++;
		sz++;
		if (!eof() && is_term(src[Pos]))
		{
			while (!eof() && is_term(src[Pos]))
				Pos++;
			break;
		}
	}
	return sz;
}

void IReader::r_string(char* dest, u32 tgt_sz)
{
	char* src = (char*)data + Pos;
	u32 sz = advance_term_string();
	R_ASSERT2(sz < (tgt_sz - 1), "Dest string less than needed.");

#ifdef _EDITOR
    CopyMemory(dest, src, sz);
#else
	strncpy_s(dest, tgt_sz, src, sz);
#endif
	dest[sz] = 0;
}

void IReader::r_string(xr_string& dest)
{
	char* src = (char*)data + Pos;
	u32 sz = advance_term_string();
	dest.assign(src, sz);
}

void IReader::r_stringZ(char* dest, u32 tgt_sz)
{
	char* src = (char*)data;
	u32 sz = xr_strlen(src);
	R_ASSERT2(sz < tgt_sz, "Dest string less than needed.");
	while ((src[Pos] != 0) && (!eof())) *dest++ = src[Pos++];
	*dest = 0;
	Pos++;
}

void IReader::r_stringZ(shared_str& dest)
{
	dest = (char*)(data + Pos);
	Pos += (dest.size() + 1);
}

void IReader::r_stringZ(xr_string& dest)
{
	dest = (char*)(data + Pos);
	Pos += int(dest.size() + 1);
};

void IReader::skip_stringZ()
{
	char* src = (char*)data;
	while ((src[Pos] != 0) && (!eof())) Pos++;
	Pos++;
};

//---------------------------------------------------
// temp stream
CTempReader::~CTempReader()
{
	xr_free(data);
};
//---------------------------------------------------

//---------------------------------------------------
// file stream
CFileReader::CFileReader(const char* name) 
{
	data = (char*)FileDownload(name, Size);
	Pos = 0;
};

CFileReader::~CFileReader()
{
	xr_free(data);
};
//---------------------------------------------------
// compressed stream
CCompressedReader::CCompressedReader(const char* name, const char* sign)
{
	data = (char*)FileDecompress(name, sign, (u32*)&Size);
	Pos = 0;
}

CCompressedReader::~CCompressedReader()
{
	xr_free(data);
};


CVirtualFileReader::CVirtualFileReader(const char* cFileName)
{
	// Open the file
	hSrcFile = CreateFile(cFileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	R_ASSERT3(hSrcFile != INVALID_HANDLE_VALUE, cFileName, Debug.error2string(GetLastError()));
	Size = (int)GetFileSize(hSrcFile, NULL);
	R_ASSERT3(Size, cFileName, Debug.error2string(GetLastError()));

	hSrcMap = CreateFileMapping(hSrcFile, 0, PAGE_READONLY, 0, 0, 0);
	R_ASSERT3(hSrcMap != INVALID_HANDLE_VALUE, cFileName, Debug.error2string(GetLastError()));

	data = (char*)MapViewOfFile(hSrcMap, FILE_MAP_READ, 0, 0, 0);
	R_ASSERT3(data, cFileName, Debug.error2string(GetLastError()));
}

CVirtualFileReader::~CVirtualFileReader()
{
	UnmapViewOfFile((void*)data);
	CloseHandle(hSrcMap);
	CloseHandle(hSrcFile);
}
