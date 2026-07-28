// #include <io.h>
// #include <direct.h>
// #include <fcntl.h>
#include <sys/stat.h>

#include <string_concatenations.h>

#include "LocatorAPI.h"
#include "LocatorAPI_defs.h"

//////////////////////////////////////////////////////////////////////
// FS_File
//////////////////////////////////////////////////////////////////////
FS_File::FS_File(const xr_string& nm, long sz, time_t modif, unsigned attr) { set(nm, sz, modif, attr); }
FS_File::FS_File(const xr_string& nm) { set(nm, 0, 0, 0); }
FS_File::FS_File(const _FINDDATA_T& f) { set(f.name, f.size, f.time_write, (f.attrib & _A_SUBDIR) ? flSubDir : 0); }

FS_File::FS_File(const xr_string& nm, const _FINDDATA_T& f)
{
	set(nm, f.size, f.time_write, (f.attrib & _A_SUBDIR) ? flSubDir : 0);
}

void FS_File::set(const xr_string& nm, long sz, time_t modif, unsigned attr)
{
	name = nm;
	xr_strlwr(name);
	size = sz;
	time_write = modif;
	attrib = attr;
}

//////////////////////////////////////////////////////////////////////
// FS_Path
//////////////////////////////////////////////////////////////////////
FS_Path::FS_Path(LPCSTR _Root, LPCSTR _Add, LPCSTR _DefExt, LPCSTR _FilterCaption, u32 flags)
{
	m_Path = _Add ? std::fs::path(_Root) / std::fs::path(_Add) : std::fs::path(_Root);
	m_DefExt = _DefExt ? _DefExt : "";
	m_FilterCaption = _FilterCaption ? _FilterCaption : "";
	m_Add = _Add ? _Add : "";
	m_Root = _Root;
	m_Flags.assign(flags);
}

FS_Path::~FS_Path()
{
}

void FS_Path::_set(std::string_view add)
{
	m_Add = add;
	m_Path = m_Add.empty() ? m_Root : m_Root / std::fs::path(m_Add);
}

void FS_Path::_set_root(std::fs::path root)
{
	m_Root = root;
	m_Path = m_Add.empty() ? m_Root : m_Root / std::fs::path(m_Add);
}

std::fs::path FS_Path::_update(std::fs::path& dest, std::fs::path src) const
{
	dest = m_Path / src;
	return dest;
}

/*
void FS_Path::_update(xr_string& dest, LPCSTR src)const
{
R_ASSERT(src);
dest = xr_string(m_Path)+src;
xr_strlwr (dest);
}*/
void FS_Path::rescan_path_cb()
{
	m_Flags.set(flNeedRescan, TRUE);
	FS.m_Flags.set(CLocatorAPI::flNeedRescan, TRUE);
}

bool XRCORE_API PatternMatch(LPCSTR s, LPCSTR mask)
{
	LPCSTR cp = 0;
	LPCSTR mp = 0;
	for (; *s && *mask != '*'; mask++, s++) if (*mask != *s && *mask != '?') return false;
	for (;;)
	{
		if (!*s)
		{
			while (*mask == '*') mask++;
			return !*mask;
		}
		if (*mask == '*')
		{
			if (!*++mask) return true;
			mp = mask;
			cp = s + 1;
			continue;
		}
		if (*mask == *s || *mask == '?')
		{
			mask++, s++;
			continue;
		}
		mask = mp;
		s = cp++;
	}
}
