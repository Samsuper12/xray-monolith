#ifndef xr_trimsH
#define xr_trimsH

#include "_types_own.h"
#include "xrstring.h"

// refs
struct xr_token;

XRCORE_API int _GetItemCount(LPCSTR, char separator = ',');
XRCORE_API char * _GetItem(LPCSTR, int, char *, u32 const dst_size, char separator = ',', LPCSTR = "", bool trim = true);

template <int count>
inline char * _GetItem(LPCSTR src, int index, char (&dst)[count], char separator = ',', LPCSTR def = "",
                      bool trim = true)
{
	return _GetItem(src, index, dst, count, separator, def, trim);
}

XRCORE_API char * _GetItems(LPCSTR, int, int, char *, char separator = ',');
XRCORE_API LPCSTR _SetPos(LPCSTR src, u32 pos, char separator = ',');
XRCORE_API LPCSTR _CopyVal(LPCSTR src, char * dst, u32 const dst_size, char separator = ',');
XRCORE_API char * _Trim(char * str);
XRCORE_API char * _TrimLeft(char * str);
XRCORE_API char * _TrimRight(char * str);
XRCORE_API char * _ChangeSymbol(char * name, char src, char dest);
XRCORE_API u32 _ParseItem(LPCSTR src, xr_token* token_list);
XRCORE_API u32 _ParseItem(char * src, int ind, xr_token* token_list);
XRCORE_API char * _ReplaceItem(LPCSTR src, int index, LPCSTR new_item, char * dst, char separator);
XRCORE_API char * _ReplaceItems(LPCSTR src, int idx_start, int idx_end, LPCSTR new_items, char * dst, char separator);
XRCORE_API void _SequenceToList(LPSTRVec& lst, LPCSTR in, char separator = ',');
XRCORE_API void _SequenceToList(RStringVec& lst, LPCSTR in, char separator = ',');
XRCORE_API void _SequenceToList(SStringVec& lst, LPCSTR in, char separator = ',');

XRCORE_API xr_string& _Trim(xr_string& src);
XRCORE_API xr_string& _TrimLeft(xr_string& src);
XRCORE_API xr_string& _TrimRight(xr_string& src);
XRCORE_API xr_string& _ChangeSymbol(xr_string& name, char src, char dest);
XRCORE_API LPCSTR _CopyVal(LPCSTR src, xr_string& dst, char separator = ',');
XRCORE_API LPCSTR _GetItem(LPCSTR src, int, xr_string& p, char separator = ',', LPCSTR = "", bool trim = true);
XRCORE_API xr_string _ListToSequence(const SStringVec& lst);
XRCORE_API shared_str _ListToSequence(const RStringVec& lst);

#endif
