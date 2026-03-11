#pragma once

inline bool ReadRegistry_StrValue(LPCSTR rKeyName, char* value) {stub_unix();}
inline void WriteRegistry_StrValue(LPCSTR rKeyName, const char* value) {stub_unix();}

inline u32 const ReadRegistry_BinaryValue(LPCSTR rKeyName, u8* buffer_dest, u32 const buffer_size) {stub_unix();}
inline void WriteRegistry_BinaryValue(LPCSTR rKeyName, u8 const* buffer_src, u32 const buffer_size) {stub_unix();}

inline void ReadRegistry_DWValue(LPCSTR rKeyName, DWORD& value) {stub_unix();}
inline void WriteRegistry_DWValue(LPCSTR rKeyName, const DWORD& value) {stub_unix();}
