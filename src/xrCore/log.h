#ifndef logH
#define logH

#include "xrstring.h"
#include "_vector3d.h"
#include <cstdio>

#define VPUSH(a) ((a).x), ((a).y), ((a).z)

void Msg(LPCSTR format, ...);
void Log(LPCSTR msg);
void Log(LPCSTR msg);
void Log(LPCSTR msg, LPCSTR dop);
void Log(LPCSTR msg, u32 dop);
void Log(LPCSTR msg, int dop);
void Log(LPCSTR msg, float dop);
void Log(LPCSTR msg, const Fvector& dop);
void Log(LPCSTR msg, const Fmatrix& dop);
void LogWinErr(LPCSTR msg, long err_code);
inline auto NeedAttention(const char* hint = nullptr, const char* filename = __FILE__, const char* func = __func__) -> void {
    Msg("Attention required here. Debug it! [%s:%s]. Hint: %s\n", filename, func, hint ? hint : "None");
    fprintf(stderr, "Attention required here. Debug it! [%s:%s]. Hint: %s\n", filename, func, hint ? hint : "None");
}

typedef void (*LogCallback)(LPCSTR string);
LogCallback SetLogCB(LogCallback cb);
void CreateLog(BOOL no_log = FALSE);
void InitLog();
void CloseLog();
void FlushLog();

extern xr_vector<shared_str>* LogFile;
extern BOOL LogExecCB;

shared_str FormatString(LPCSTR fmt, ...);

#endif
