#pragma once


#include <sys/_types.h>
#include <machine/_types.h> 
#include <sys/syslimits.h>

// Must be defined before ANY includes — SDK headers pull in _types.h
// which uses PATH_MAX before we get a chance to define it otherwise
#ifndef PATH_MAX
#  define PATH_MAX 260
#endif
#ifndef _MAX_PATH
#  define _MAX_PATH PATH_MAX
#endif


#include <ctype.h>
#include <limits.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <unistd.h>
#define IC inline
#define ICF inline

#if defined(__clang__)
#define __assume(expr) __builtin_assume(expr)
#elif defined(_MSC_VER)
#else
#define __assume
#endif

#define ENGINE_API
typedef void *HANDLE;
typedef const char *LPCSTR;
typedef char *PSTR, *LPSTR;
typedef const void *LPCVOID;
typedef uint32_t COLORREF;
typedef unsigned char BYTE;
typedef int __int32;
typedef struct {
  long left, top, right, bottom;
} RECT;
typedef struct {
  long x, y;
} POINT;
typedef POINT *LPPOINT;
typedef RECT *LPRECT;
typedef void *LPVOID;
typedef size_t ULONG_PTR;
typedef void *PVOID;
typedef uintptr_t DWORD_PTR;
typedef DWORD_PTR *PDWORD_PTR;
typedef uint32_t DWORD;
typedef DWORD D3DCOLOR;
typedef DWORD *LPDWORD;
typedef unsigned short WORD;
typedef void *HWND;
typedef void *HINSTANCE;
typedef void *HMODULE;
#define interface struct
#define _stricmp strcasecmp
#define RGB(r, g, b)                                                           \
  ((COLORREF)(((uint8_t)(r) | ((uint16_t)((uint8_t)(g)) << 8)) |               \
              (((uint32_t)(uint8_t)(b)) << 16)))

typedef void *HANDLE;
typedef void *HDC;
typedef void *HINSTANCE;
typedef void *HMONITOR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned int UINT;
typedef long LONG;
typedef unsigned long ULONG;
typedef long long LONGLONG;
typedef unsigned long long ULONGLONG;
typedef float FLOAT;
typedef size_t SIZE_T;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef signed char INT8;
typedef short INT16;
typedef int INT32;
typedef long long INT64;
typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;
typedef char CHAR;
typedef wchar_t WCHAR;
typedef const char *LPCSTR;
typedef const wchar_t *LPCWSTR;
typedef char *LPSTR;
typedef wchar_t *LPWSTR;
typedef void *LPVOID;
typedef const void *LPCVOID;
typedef unsigned int UINT_PTR;
typedef uint64_t LUID_TYPE;
typedef int64_t __int64;
typedef int BOOL;
typedef BYTE *LPBYTE;
typedef char *LPTSTR;
typedef uint8_t *LPBYTE;
typedef const char *LPCTSTR;
typedef void *MINIDUMPWRITEDUMP;
typedef intptr_t LPARAM;
typedef int INT_PTR;
typedef unsigned int UINT_PTR;
typedef uintptr_t ULONG_PTR;
typedef uintptr_t *PLARGE_INTEGER;
typedef void *HGLOBAL;
typedef void VOID;
typedef HANDLE LPHANDLE;
typedef void *HKL;
typedef unsigned long LCID;

typedef uintptr_t WPARAM;
typedef intptr_t LRESULT;

#define _A_SUBDIR 0x10
#define BFFM_INITIALIZED 1
#define TRUE true
#define FALSE false
#define _STL_UNREACHABLE 0
#define MCW_EM 0
#define INVALID_SET_FILE_POINTER 0
#define _A_HIDDEN 0
#define FILE_ATTRIBUTE_READONLY 0
#define FILE_FLAG_NO_BUFFERING 0
#define PAGE_READWRITE 0
#define FILE_MAP_ALL_ACCESS 0
#define FILE_MAP_READ 0
#define FORMAT_MESSAGE_ALLOCATE_BUFFER 0
#define LANG_NEUTRAL 0
#define SUBLANG_DEFAULT 0
#define EXCEPTION_CONTINUE_SEARCH 0
#define EXCEPTION_CONTINUE_EXECUTION 0
#define EXCEPTION_STACK_OVERFLOW 0
#define REALTIME_PRIORITY_CLASS 0
#define HIGH_PRIORITY_CLASS 0
#define _PC_24 0
#define _PC_64 0
#define BFFM_SETSELECTION 0
#define MAX_PATH 256
#define CALLBACK
#define O_CREAT 0
#define O_WRONLY 0
#define O_TRUNC 0
#define O_RDONLY 0
#define S_IREAD 0
#define S_IWRITE 0
#define MEM_FREE 0
#define MEM_RESERVE 0
#define MEM_COMMIT 0
#define _HEAPOK 0
#define _HEAPEMPTY 0
#define _HEAPEND 0
#define _HEAPBADPTR 0
#define _HEAPBADBEGIN 0
#define _HEAPBADNODE 0
#define _USEDENTRY 0
#define GHND 0
#define CF_TEXT 0
#define __forceinline

#define GWL_STYLE 0
#define WS_VISIBLE 0
#define WS_POPUP 0

#define HWND_TOP 0
#define SWP_FRAMECHANGED 0

#define WM_SYSKEYDOWN 0
#define WM_ACTIVATE 0
#define WM_SETCURSOR 0
#define WM_SYSCOMMAND 0
#define WM_CLOSE 0
#define WM_HOTKEY 0
#define WM_SYSCHAR 0
#define WM_CHAR 0
#define WM_INPUTLANGCHANGE 0

#define SC_MOVE 0
#define SC_SIZE 0
#define SC_MAXIMIZE 0
#define SC_MONITORPOWER 0
#define _MAX_PATH 250
#define PATH_MAX 250
#define HFONT void *
#define HBRUSH void *
#define HBITMAP void *
#define ICN 

#define WM_PAINT 0
#define WM_ERASEBKGND 0
#define WM_NCPAINT 0

#define HIWORD(x) (((unsigned int)(x) >> 16) & 0xFFFF)

typedef union _LARGE_INTEGER {
  struct {
    unsigned int LowPart;
    int HighPart;
  };
  long long QuadPart;
} LARGE_INTEGER;
// fucking stub section. Don't use it. Only for
// compiling//////////////////////////////////////////////// FUCKINGHELL:
// FIXME:

struct _finddata_t {
  unsigned attrib;
  long time_create;
  long time_access;
  long time_write;
  long size;
  char name[260];
};

typedef struct _CRITICAL_SECTION {
  void *reserved;
} CRITICAL_SECTION;

typedef struct _MEMORY_BASIC_INFORMATION {
  void *BaseAddress;
  void *AllocationBase;
  uint32_t AllocationProtect;
  size_t RegionSize;
  uint32_t State;
  uint32_t Protect;
  uint32_t Type;
} MEMORY_BASIC_INFORMATION;

typedef MEMORY_BASIC_INFORMATION *PMEMORY_BASIC_INFORMATION;

typedef struct _HEAPINFO {
  int *_pentry;
  size_t _size;
  int _useflag;
} _HEAPINFO;

#define MAXD3DDECLLENGTH 64

#define D3DCOLOR_ARGB(a, r, g, b)                                              \
  ((D3DCOLOR)((((a) & 0xff) << 24) | (((r) & 0xff) << 16) |                    \
              (((g) & 0xff) << 8) | ((b) & 0xff)))
#define D3DCOLOR_RGBA(r, g, b, a) D3DCOLOR_ARGB(a, r, g, b)
#define D3DCOLOR_XRGB(r, g, b) D3DCOLOR_ARGB(0xff, r, g, b)
#define D3DCOLOR_XYUV(y, u, v) D3DCOLOR_ARGB(0xff, y, u, v)
#define D3DCOLOR_AYUV(a, y, u, v) D3DCOLOR_ARGB(a, y, u, v)

#define MAILSLOT_WAIT_FOREVER 0xFFFFFFFF
#define GENERIC_WRITE 0x40000000
#define FILE_SHARE_READ 0x00000001
#define INVALID_HANDLE_VALUE ((HANDLE)(LPVOID) - 1)
#define STATUS_STACK_OVERFLOW 0xC00000FD

typedef struct _SECURITY_ATTRIBUTES {
  DWORD nLength;
  LPVOID lpSecurityDescriptor;
  bool bInheritHandle;
} SECURITY_ATTRIBUTES;

typedef struct _OVERLAPPED {
  ULONG_PTR Internal;
  ULONG_PTR InternalHigh;
  union {
    struct {
      DWORD Offset;
      DWORD OffsetHigh;
    };
    PVOID Pointer;
  };
  HANDLE hEvent;
} OVERLAPPED;

typedef SECURITY_ATTRIBUTES *LPSECURITY_ATTRIBUTES;
typedef OVERLAPPED *LPOVERLAPPED;

inline HANDLE CreateMailslot(LPCSTR lpName, DWORD nMaxMessageSize,
                             DWORD lReadTimeout,
                             LPSECURITY_ATTRIBUTES lpSecurityAttributes) {}

typedef struct _finddata64i32_t {
  unsigned attrib;
  int64_t time_create;
  int64_t time_access;
  int64_t time_write;
  uint32_t size;
  char name[260];
} _finddata64i32_t;

#define OPEN_EXISTING 3
#define FILE_ATTRIBUTE_NORMAL 0x00000080
#define MAILSLOT_NO_MESSAGE 0xFFFFFFFF
#define _MAX_DRIVE 3
#define _MAX_DIR 256
#define _MAX_EXT 256
#define _MAX_FNAME 256

typedef enum _MINIDUMP_TYPE {
  MiniDumpNormal = 0x00000000,
  MiniDumpWithDataSegs = 0x00000001,
  MiniDumpWithFullMemory = 0x00000002,
  MiniDumpWithHandleData = 0x00000004,
  MiniDumpFilterMemory = 0x00000008,
  MiniDumpScanMemory = 0x00000010,
  MiniDumpWithUnloadedModules = 0x00000020,
  MiniDumpWithIndirectlyReferencedMemory = 0x00000040,
  MiniDumpFilterModulePaths = 0x00000080,
  MiniDumpWithProcessThreadData = 0x00000100,
  MiniDumpWithPrivateReadWriteMemory = 0x00000200,
  MiniDumpWithoutOptionalData = 0x00000400,
  MiniDumpWithFullMemoryInfo = 0x00000800,
  MiniDumpWithThreadInfo = 0x00001000,
  MiniDumpWithCodeSegs = 0x00002000,
  MiniDumpWithoutAuxiliaryState = 0x00004000,
  MiniDumpWithFullAuxiliaryState = 0x00008000,
  MiniDumpWithPrivateWriteCopyMemory = 0x00010000,
  MiniDumpIgnoreInaccessibleMemory = 0x00020000,
  MiniDumpWithTokenInformation = 0x00040000,
  MiniDumpWithModuleHeaders = 0x00080000,
  MiniDumpFilterTriage = 0x00100000,
  MiniDumpWithAvxXStateContext = 0x00200000,
  MiniDumpWithIptTrace = 0x00400000,
  MiniDumpScanInaccessiblePartialPages = 0x00800000,
  MiniDumpFilterWriteCombinedMemory,
  MiniDumpValidTypeFlags = 0x01ffffff
} MINIDUMP_TYPE;

#define GENERIC_READ 0x80000000
#define FILE_SHARE_WRITE 0x00000002
#define CREATE_ALWAYS 2
#define PAGE_READONLY 0x02
#define _PC_53 0x00010000
#define MCW_PC 0x00030000
#define _RC_CHOP 0x00000C00
#define _RC_NEAR 0x00000000
#define MCW_RC 0x00000C00
#define _MCW_EM 0x0008001F
#define COINIT_MULTITHREADED 0x0
#define DLL_PROCESS_ATTACH 1
#define DLL_THREAD_ATTACH 2
#define DLL_THREAD_DETACH 3
#define DLL_PROCESS_DETACH 0
#define MB_OK 0x00000000
#define MB_ICONERROR 0x00000010
#define MB_SYSTEMMODAL 0x00001000
#define SW_FORCEMINIMIZE 11
#define FORMAT_MESSAGE_FROM_SYSTEM 0x00001000
#define EXCEPTION_EXECUTE_HANDLER 1
#define OFN_HIDEREADONLY 0x00000004
#define OFN_NOCHANGEDIR 0x00000008
#define OFN_ALLOWMULTISELECT 0x00000200
#define OFN_PATHMUSTEXIST 0x00000800
#define OFN_FILEMUSTEXIST 0x00001000
#define OFN_OVERWRITEPROMPT 0x00000002
#define OFN_EXPLORER 0x00080000
#define OFN_EX_NOPLACESBAR 0x00000001
#define FNERR_BUFFERTOOSMALL 0x3003
#define _WRITE_ABORT_MSG 0x1
#define _CALL_REPORTFAULT 0x2
#define SIGABRT_COMPAT 6
#define WINAPI

typedef struct _SYSTEM_INFO {
  uint32_t dwOemId;
  uint32_t dwPageSize;
  void *lpMinimumApplicationAddress;
  void *lpMaximumApplicationAddress;
  uint32_t *dwActiveProcessorMask;
  uint32_t dwNumberOfProcessors;
  uint32_t dwProcessorType;
  uint32_t dwAllocationGranularity;
  uint16_t wProcessorLevel;
  uint16_t wProcessorRevision;
} SYSTEM_INFO;

typedef void *hPSGP;

typedef struct _EXCEPTION_POINTERS {
  void *ExceptionRecord;
  void *ContextRecord;
} EXCEPTION_POINTERS, *LPEXCEPTION_POINTERS;

typedef struct tagOFN {
  uint32_t lStructSize;
  void *hwndOwner;
  HINSTANCE hInstance;
  const char *lpstrFilter;
  char *lpstrCustomFilter;
  uint32_t nMaxCustFilter;
  uint32_t nFilterIndex;
  char *lpstrFile;
  uint32_t nMaxFile;
  char *lpstrFileTitle;
  uint32_t nMaxFileTitle;
  const char *lpstrInitialDir;
  const char *lpstrTitle;
  uint32_t Flags;
  uint16_t nFileOffset;
  uint16_t nFileExtension;
  const char *lpstrDefExt;
  void *lCustData;
  void *lpfnHook;
  const char *lpTemplateName;
  void *pvReserved;
  uint32_t dwReserved;
  uint32_t FlagsEx;
} OPENFILENAME;

typedef struct _EXCEPTION_RECORD {
  uint32_t ExceptionCode;
  uint32_t ExceptionFlags;
  void *ExceptionRecord;
  void *ExceptionAddress;
  uint32_t NumberParameters;
  uintptr_t ExceptionInformation[15];
} EXCEPTION_RECORD;

typedef struct tagWNDCLASS {
  unsigned int style;
  void *lpfnWndProc;
  int cbClsExtra;
  int cbWndExtra;
  void *hInstance;
  void *hIcon;
  void *hCursor;
  void *hbrBackground;
  const char *lpszMenuName;
  const char *lpszClassName;
} WNDCLASS;

typedef struct tagPAINTSTRUCT {
  void *hdc;
  int fErase;
  struct {
    long left, top, right, bottom;
  } rcPaint;
  int fRestore;
  int fIncUpdate;
  unsigned char rgbReserved[32];
} PAINTSTRUCT;

typedef struct tagTEXTMETRIC {
  long tmHeight;
  long tmAscent;
  long tmDescent;
  long tmInternalLeading;
  long tmExternalLeading;
  long tmAveCharWidth;
  long tmMaxCharWidth;
  long tmWeight;
  long tmOverhang;
  long tmDigitizedAspectX;
  long tmDigitizedAspectY;
  unsigned char tmFirstChar;
  unsigned char tmLastChar;
  unsigned char tmDefaultChar;
  unsigned char tmBreakChar;
  unsigned char tmItalic;
  unsigned char tmUnderlined;
  unsigned char tmStruckOut;
  unsigned char tmPitchAndFamily;
  unsigned char tmCharSet;
} TEXTMETRIC;

typedef struct tagWINDOWINFO {
  unsigned int cbSize;
  struct {
    long left, top, right, bottom;
  } rcWindow;
  struct {
    long left, top, right, bottom;
  } rcClient;
  unsigned int dwStyle;
  unsigned int dwExStyle;
  unsigned int dwWindowStatus;
  unsigned int cxWindowBorders;
  unsigned int cyWindowBorders;
  unsigned short atomWindowType;
  unsigned short wCreatorVersion;
} WINDOWINFO;

typedef struct tagMONITORINFO {
  unsigned int cbSize;
  struct {
    long left, top, right, bottom;
  } rcMonitor;
  struct {
    long left, top, right, bottom;
  } rcWork;
  unsigned int dwFlags;
} MONITORINFO;

typedef struct _devicemodeA {
  char dmDeviceName[32];
  unsigned short dmSpecVersion;
  unsigned short dmDriverVersion;
  unsigned short dmSize;
  unsigned short dmDriverExtra;
  unsigned int dmFields;
  int dmPositionX;
  int dmPositionY;
  unsigned int dmDisplayOrientation;
  unsigned int dmDisplayFixedOutput;
  short dmColor;
  short dmDuplex;
  short dmYResolution;
  short dmTTOption;
  short dmCollate;
  char dmFormName[32];
  unsigned short dmLogPixels;
  unsigned int dmBitsPerPel;
  unsigned int dmPelsWidth;
  unsigned int dmPelsHeight;
  unsigned int dmDisplayFlags;
  unsigned int dmDisplayFrequency;
  unsigned int dmICMMethod;
  unsigned int dmICMIntent;
  unsigned int dmMediaType;
  unsigned int dmDitherType;
  unsigned int dmReserved1;
  unsigned int dmReserved2;
  unsigned int dmPanningWidth;
  unsigned int dmPanningHeight;
} DEVMODE;

typedef struct _stat {
  uint32_t st_dev;
  uint16_t st_ino;
  uint16_t st_mode;
  int16_t st_nlink;
  int16_t st_uid;
  int16_t st_gid;
  uint32_t st_rdev;
  int32_t st_size;
  time_t st_atime;
  time_t st_mtime;
  time_t st_ctime;
} _stat;

typedef struct _utimbuf {
  time_t actime;
  time_t modtime;
} _utimbuf;

typedef long (*LPTOP_LEVEL_EXCEPTION_FILTER)(EXCEPTION_POINTERS *);

typedef struct _MINIDUMP_EXCEPTION_INFORMATION *PMINIDUMP_EXCEPTION_INFORMATION;

typedef void *CONST;

typedef struct _SYSTEMTIME {
  WORD wYear;
  WORD wMonth;
  WORD wDayOfWeek;
  WORD wDay;
  WORD wHour;
  WORD wMinute;
  WORD wSecond;
  WORD wMilliseconds;
} SYSTEMTIME;

#define _declspec
#define INFINITE 0
#define WAIT_ABANDONED 0
#define WAIT_OBJECT_0 0
#define WAIT_FAILED 0
#define SW_SHOW 0
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define O_BINARY 0
#define _O_BINARY 0
#define _O_RDONLY 0
#define _O_WRONLY 0
#define _O_TRUNC 0
#define _O_CREAT 0
#define _S_IREAD 0
#define _S_IWRITE 0
#define SH_DENYWR 0
#define _SH_DENYNO 0
#define FILE_BEGIN 0
#define FILE_CURRENT 0
#define FILE_END 0
#define WS_OVERLAPPEDWINDOW 0
#define IDC_ARROW 0
#define GRAY_BRUSH 0
#define WS_CHILD 0
#define FW_NORMAL 0
#define DEFAULT_CHARSET 0
#define OUT_STRING_PRECIS 0
#define CLIP_STROKE_PRECIS 0
#define DRAFT_QUALITY 0
#define VARIABLE_PITCH 0
#define FF_SWISS 0
#define BLACK_BRUSH 0
#define SRCCOPY 0
#define SORT_DEFAULT 0
#define LOCALE_RETURN_NUMBER 0
#define LOCALE_IDEFAULTANSICODEPAGE 0
#define CP_ACP 0
#define MB_PRECOMPOSED 0
#define WS_ACTIVECAPTION 0
#define MONITOR_DEFAULTTOPRIMARY 0
#define ENUM_CURRENT_SETTINGS 0
#define CLSCTX_INPROC_SERVER 0x1
#define S_OK 0
#define S_FALSE 1
struct IUnknown {};

typedef struct _GUID {
  unsigned long Data1;
  unsigned short Data2;
  unsigned short Data3;
  unsigned char Data4[8];
} GUID;
#define GUID_DEFINED


struct WAVEFORMATEX {
  WORD wFormatTag;
  WORD nChannels;
  DWORD nSamplesPerSec;
  DWORD nAvgBytesPerSec;
  WORD nBlockAlign;
  WORD wBitsPerSample;
  WORD cbSize;
};
enum ERole { eConsole, eSommunications, eMultimedia, ERole_enum_count };
enum EDataFlow { eRender, eCapture, eAll, EDataFlow_enum_count };

struct PROPERTYKEY {
  GUID fmtid;
  DWORD pid;
};

typedef GUID IID;
typedef GUID CLSID;
typedef const IID *REFIID;

typedef long HRESULT;

#define STDMETHOD(method) HRESULT method
#define STDMETHODIMP_(type) type

#define WAVE_FORMAT_PCM (0x0001)

typedef int WINBOOL;

typedef struct _LUID {
  unsigned long LowPart;
  long HighPart;
} LUID;

typedef const GUID *REFGUID;

#include <ctype.h>
#include <string.h>
#define _sys_errlist sys_errlist

#ifdef __cplusplus

static inline void stub_unix(const char* f) {

  fprintf(stderr, "function: %s\n", f);
  fprintf(stderr, "stub");
}

typedef LONG SCODE;
typedef unsigned long long ULONGLONG;
typedef short VARIANT_BOOL;
typedef unsigned short VARTYPE;
struct STICKYKEYS {
  DWORD cbSize;
  DWORD dwFlags;
};

struct TOGGLEKEYS {
  DWORD cbSize;
  DWORD dwFlags;
};

#define SW_SHOWNORMAL 1

#define WM_DESTROY 0x0002
#define WM_COMMAND 0x0111

#define LOWORD(l) ((WORD)(((DWORD_PTR)(l)) & 0xffff))

#define IDCANCEL 2

#define TKF_AVAILABLE 0x00000002

#define SPI_GETSCREENSAVEACTIVE 0x0010
#define SPI_SETSCREENSAVEACTIVE 0x0011
#define SPI_SETFILTERKEYS 0x0033

struct FILTERKEYS {
  DWORD cbSize;
  DWORD dwFlags;
  DWORD iWaitMSec;
  DWORD iDelayMSec;
  DWORD iRepeatMSec;
  DWORD iBounceMSec;
};

struct BLOB {
  ULONG cbSize;
  BYTE *pBlobData;
};

union ULARGE_INTEGER {
  struct {
    DWORD LowPart;
    DWORD HighPart;
  };
  ULONGLONG QuadPart;
};

struct PROPVARIANT {
  VARTYPE vt;
  WORD wReserved1;
  WORD wReserved2;
  WORD wReserved3;
  union {
    LONG lVal;
    ULONG ulVal;
    FLOAT fltVal;
    double dblVal;
    VARIANT_BOOL boolVal;
    SCODE scode;
    LARGE_INTEGER hVal;
    ULARGE_INTEGER uhVal;
    LPSTR pszVal;
    LPWSTR pwszVal;
    BLOB blob;
  };
};

#define SPI_GETSTICKYKEYS 0x003A
#define SPI_SETSTICKYKEYS 0x003B
#define SPI_GETFILTERKEYS 0x0032
#define SPI_SETFILTERKEYS 0x0033
#define SPI_GETTOGGLEKEYS 0x0034
#define SPI_SETTOGGLEKEYS 0x0035

#define SKF_AVAILABLE 0x00000002
#define FKF_AVAILABLE 0x00000002

#define READ_CONTROL 0x00020000L

#define MAKEINTRESOURCE(i) ((LPSTR)((ULONG_PTR)((WORD)(i))))

#define HWND_TOPMOST ((HWND) - 1)
#define SWP_NOMOVE 0x0002
#define SWP_SHOWWINDOW 0x0040

enum HEAP_INFORMATION_CLASS {
  HeapCompatibilityInformation,
  HeapEnableTerminationOnCorruption
};

struct STARTUPINFO {
  DWORD cb;
  LPSTR lpReserved;
  LPSTR lpDesktop;
  LPSTR lpTitle;
  DWORD dwX;
  DWORD dwY;
  DWORD dwXSize;
  DWORD dwYSize;
  DWORD dwXCountChars;
  DWORD dwYCountChars;
  DWORD dwFillAttribute;
  DWORD dwFlags;
  WORD wShowWindow;
  WORD cbReserved2;
  LPBYTE lpReserved2;
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
};

struct PROCESS_INFORMATION {
  HANDLE hProcess;
  HANDLE hThread;
  DWORD dwProcessId;
  DWORD dwThreadId;
};

typedef const PROPERTYKEY &REFPROPERTYKEY;
typedef const PROPVARIANT &REFPROPVARIANT;

struct IPropertyStore {
  STDMETHOD(GetCount)(DWORD *cProps) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(GetAt)(DWORD iProp, PROPERTYKEY *pkey) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(GetValue)(REFPROPERTYKEY key, PROPVARIANT *pv) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(SetValue)(REFPROPERTYKEY key, REFPROPVARIANT propvar) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(Commit)() {
    stub_unix(__func__);
    return S_OK;
  }
};

struct IMMDevice {
  STDMETHOD(Activate)(REFIID iid, DWORD dwClsCtx,
                      PROPVARIANT *pActivationParams, void **ppInterface) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(OpenPropertyStore)(DWORD stgmAccess,
                               IPropertyStore **ppProperties) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(GetId)(LPWSTR *ppstrId) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(GetState)(DWORD *pdwState) {
    stub_unix(__func__);
    return S_OK;
  }
};

struct IMMNotificationClient {
  STDMETHOD(OnDeviceStateChanged)(LPCWSTR pwstrDeviceId, DWORD dwNewState) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(OnDeviceAdded)(LPCWSTR pwstrDeviceId) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(OnDeviceRemoved)(LPCWSTR pwstrDeviceId) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(OnDefaultDeviceChanged)(EDataFlow flow, ERole role,
                                    LPCWSTR pwstrDefaultDeviceId) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(OnPropertyValueChanged)(LPCWSTR pwstrDeviceId,
                                    const PROPERTYKEY key) {
    stub_unix(__func__);
    return S_OK;
  }
};

struct IMMDeviceCollection {
  STDMETHOD(GetCount)(UINT *pcDevices) {
    stub_unix(__func__);
    return S_OK;
  }
  STDMETHOD(Item)(UINT nDevice, IMMDevice **ppDevice) {
    stub_unix(__func__);
    return S_OK;
  }
};

struct IMMDeviceEnumerator {
  STDMETHOD(EnumAudioEndpoints)(EDataFlow dataFlow, DWORD dwStateMask,
                                IMMDeviceCollection **ppDevices) {
    stub_unix(__func__);
  }
  STDMETHOD(GetDefaultAudioEndpoint)(EDataFlow dataFlow, ERole role,
                                     IMMDevice **ppEndpoint) {
    stub_unix(__func__);
  }
  STDMETHOD(GetDevice)(LPCWSTR pwstrId, IMMDevice **ppEndpoint) { stub_unix(__func__); }
  STDMETHOD(RegisterEndpointNotificationCallback)(
      IMMNotificationClient *pClient) {
    stub_unix(__func__);
  }
  STDMETHOD(UnregisterEndpointNotificationCallback)(
      IMMNotificationClient *pClient) {
    stub_unix(__func__);
  }
};


inline bool ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead,
                     LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) {
  stub_unix(__func__);
}

inline HANDLE CreateMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner,
                    LPCSTR lpName) {
  stub_unix(__func__);
}
inline HWND GetDlgItem(HWND hDlg, int nIDDlgItem) { stub_unix(__func__); }

inline VOID PostQuitMessage(int nExitCode) { stub_unix(__func__); }
inline BOOL FreeLibrary(HMODULE hLibModule) { stub_unix(__func__); }


inline bool CloseHandle(HANDLE hObject) { stub_unix(__func__); }
inline HANDLE CreateEvent(LPSECURITY_ATTRIBUTES lpEventAttributes,
                          bool bManualReset, bool bInitialState,
                          LPCSTR lpName) {
  stub_unix(__func__);
}

inline uint64_t __rdtsc() {
  stub_unix(__func__);
}


inline HANDLE CreateFile(LPCSTR lpFileName, DWORD dwDesiredAccess,
                         DWORD dwShareMode,
                         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                         DWORD dwCreationDisposition,
                         DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
  stub_unix(__func__);
}
inline bool GetProcessAffinityMask(HANDLE hProcess, PDWORD_PTR lpProcessAffinityMask,
                            PDWORD_PTR lpSystemAffinityMask) {
  stub_unix(__func__);
}
inline void GetSystemTime(SYSTEMTIME *st) { stub_unix(__func__); }
inline void GetLocalTime(SYSTEMTIME *st) { stub_unix(__func__); }
inline bool SetEvent(HANDLE hEvent) { stub_unix(__func__); }
inline DWORD WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds) {
  stub_unix(__func__);
}
inline bool SwitchToThread() { stub_unix(__func__); }
inline bool ClipCursor(const RECT *lpRect = nullptr) { stub_unix(__func__); }
inline bool UpdateWindow(HWND hWnd) { stub_unix(__func__); }
inline bool ShowWindow(HWND hWnd, int nCmdShow) { stub_unix(__func__); }
inline bool DestroyWindow(HWND hWnd) { stub_unix(__func__); }
inline int MapWindowPoints(HWND hWndFrom, HWND hWndTo, LPPOINT lpPoints,
                    unsigned int cPoints) {
  stub_unix(__func__);
}
inline HINSTANCE ShellExecute(HWND hwnd, LPCSTR lpOperation, LPCSTR lpFile,
                       LPCSTR lpParameters, LPCSTR lpDirectory, int nShowCmd) {
  stub_unix(__func__);
}
inline DWORD GetModuleFileName(HMODULE hModule, LPSTR lpFilename, DWORD nSize) {
  stub_unix(__func__);
}
inline DWORD GetFullPathName(LPCSTR lpFileName, DWORD nBufferLength, LPSTR lpBuffer,
                      LPSTR *lpFilePart) {
  stub_unix(__func__);
}
inline HWND GetForegroundWindow() { stub_unix(__func__); }
inline DWORD CommDlgExtendedError() { stub_unix(__func__); }
inline BOOL IsDebuggerPresent() { stub_unix(__func__); }
inline LPSTR GetCommandLine() { stub_unix(__func__); }
inline unsigned int _clear87(void) { stub_unix(__func__); }
inline HWND GetActiveWindow() { stub_unix(__func__); }
inline HMODULE LoadLibrary(LPCSTR lpLibFileName) { stub_unix(__func__); }
inline LONG InterlockedExchange(LONG volatile *Target, LONG Value) { stub_unix(__func__); }
inline DWORD GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh) { stub_unix(__func__); }
inline void MoveMemory(PVOID Destination, const void *Source, SIZE_T Length) {
  stub_unix(__func__);
}
inline HMODULE GetModuleHandle(LPCSTR lpModuleName) { stub_unix(__func__); }
inline DWORD GetCurrentDirectory(DWORD nBufferLength, LPTSTR lpBuffer) { stub_unix(__func__); }
inline BOOL GetUserName(LPSTR lpBuffer, LPDWORD pcbBuffer) { stub_unix(__func__); }
inline BOOL TerminateProcess(HANDLE hProcess, UINT uExitCode) { stub_unix(__func__); }
inline unsigned int _control87(unsigned int n, unsigned int mask) { stub_unix(__func__); }
inline unsigned int _controlfp(unsigned int n, unsigned int mask) { stub_unix(__func__); }
inline int __control87_2(unsigned int n, unsigned int mask, unsigned int *x86_cw,
                  unsigned int *sse2_cw) {
  stub_unix(__func__);
}
inline int _read(int const fd, void *const buffer, unsigned const buffer_size) {
  stub_unix(__func__);
}
inline int _write(int fd, const void *buffer, unsigned int count) { stub_unix(__func__); }
inline BOOL GetOpenFileName(OPENFILENAME *ofn) { stub_unix(__func__); }
inline BOOL GetSaveFileName(OPENFILENAME *ofn) { stub_unix(__func__); }
inline void MessageBox(HWND hWnd, const char *text, const char *caption,
                       uint32_t type) {
  stub_unix(__func__);
}
inline DWORD GetLastError() { stub_unix(__func__); }
inline void LocalFree(void *mem) { stub_unix(__func__); }
inline void CoInitializeEx(void *, uint32_t) { stub_unix(__func__); }
inline void DXGetErrorDescription(uint32_t code, char *buf, size_t size) {
  stub_unix(__func__);
}
inline void FormatMessage(uint32_t flags, void *, uint32_t, uint32_t, char *buf,
                          size_t size, void *) {
  stub_unix(__func__);
}
inline HWND GetTopWindow(HWND hWnd) { stub_unix(__func__); }
inline void *MapViewOfFile(HANDLE hMap, uint32_t access, uint32_t offHigh,
                           uint32_t offLow, size_t sz) {
  stub_unix(__func__);
}
inline BOOL UnmapViewOfFile(void *addr) { stub_unix(__func__); }
inline HANDLE CreateFileMapping(HANDLE h, void *, uint32_t protect,
                                uint32_t sizeHigh, uint32_t sizeLow,
                                const char *name) {
  stub_unix(__func__);
}
inline DWORD GetProcAddress(HANDLE hModule, const char *name) { stub_unix(__func__); }
inline const char *_sys_errlist_get(int idx) { stub_unix(__func__); }
inline intptr_t _findfirst64i32(const char *filespec,
                                _finddata64i32_t *fileinfo) {
  stub_unix(__func__);
}
inline int _findnext64i32(intptr_t handle, _finddata64i32_t *fileinfo) {
  stub_unix(__func__);
}
inline int _findclose(intptr_t handle) { stub_unix(__func__); }
inline int _sopen(const char *path, int oflag, int shflag, ...) {
  stub_unix(__func__);
  return -1;
}
inline int _sopen_s(...) {
  stub_unix(__func__);
  return -1;
}
inline long filelength(int fd) {
  stub_unix(__func__);
  return 0;
}
inline uint32_t SetFilePointer(HANDLE h, int32_t dist, void *,
                               uint32_t method) {
  stub_unix(__func__);
  return 0;
}
inline void RaiseException(uint32_t, uint32_t, uint32_t, uintptr_t *) {
  stub_unix(__func__);
}
inline BOOL SetPriorityClass(HANDLE, uint32_t) {
  stub_unix(__func__);
  return 0;
}
inline uint32_t timeGetTime() {
  stub_unix(__func__);
  return 0;
}
inline BOOL QueryPerformanceCounter(PLARGE_INTEGER *) {
  stub_unix(__func__);
  return 0;
}
inline BOOL QueryPerformanceFrequency(PLARGE_INTEGER *) {
  stub_unix(__func__);
  return 0;
}
inline uintptr_t _beginthread(void (*)(void *), uint32_t, void *) {
  stub_unix(__func__);
  return 0;
}
inline int vsprintf_s(char *, const char *, va_list) {
  stub_unix(__func__);
  return 0;
}
inline int _utime(const char *, struct _utimbuf *) {
  stub_unix(__func__);
  return 0;
}
inline void SendMessage(HWND, uint32_t, BOOL, LPARAM) { stub_unix(__func__); }
inline intptr_t _findfirst(const char *, void *) {
  stub_unix(__func__);
  return -1;
}
inline int _findnext(intptr_t, void *) {
  stub_unix(__func__);
  return -1;
}
inline int _set_new_mode(int) {
  stub_unix(__func__);
  return 0;
}

inline FILE *_fdopen(int fd, const char *mode) {
  stub_unix(__func__);
  return nullptr;
}
inline int _vsnprintf(char *, size_t, const char *, ...) {
  stub_unix(__func__);
  return 0;
}
inline int _mkdir(const char *path) {
  stub_unix(__func__);
  return 0;
}
inline int _rmdir(const char *path) {
  stub_unix(__func__);
  return 0;
}
inline void _tzset() { stub_unix(__func__); }
inline int _close(int fd) {
  stub_unix(__func__);
  return 0;
}
inline uint64_t _strtoui64(const char *, char **, int) {
  stub_unix(__func__);
  return 0;
}
inline int64_t _atoi64(const char *) {
  stub_unix(__func__);
  return 0;
}

inline BOOL GetCursorPos(LPPOINT lpPoint) { stub_unix(__func__); }

inline BOOL TryEnterCriticalSection(CRITICAL_SECTION *) {
  stub_unix(__func__);
  return 0;
}
inline HGLOBAL GlobalAlloc(uint32_t, size_t) { stub_unix(__func__); }
inline void *GlobalLock(HGLOBAL) { stub_unix(__func__); }
inline BOOL GlobalUnlock(HGLOBAL) {
  stub_unix(__func__);
  return 0;
}
inline HGLOBAL GetClipboardData(uint32_t) { stub_unix(__func__); }
inline BOOL SetClipboardData(uint32_t, HGLOBAL) {
  stub_unix(__func__);
  return 0;
}
inline BOOL OpenClipboard(HWND) {
  stub_unix(__func__);
  return 0;
}
inline BOOL CloseClipboard() {
  stub_unix(__func__);
  return 0;
}
inline BOOL EmptyClipboard() {
  stub_unix(__func__);
  return 0;
}
inline int _heapwalk(_HEAPINFO *) {
  stub_unix(__func__);
  return 0;
}
inline void InitializeCriticalSection(CRITICAL_SECTION *) { stub_unix(__func__); }
inline void DeleteCriticalSection(CRITICAL_SECTION *) { stub_unix(__func__); }
inline void EnterCriticalSection(CRITICAL_SECTION *) { stub_unix(__func__); }
inline void LeaveCriticalSection(CRITICAL_SECTION *) { stub_unix(__func__); }

inline LRESULT SetWindowLongPtr(void *hWnd, int nIndex, LRESULT dwNewLong) {
  stub_unix(__func__);
}

inline bool SetWindowPos(void *hWnd, void *hWndInsertAfter, int X, int Y, int cx,
                  int cy, unsigned int uFlags) {
  stub_unix(__func__);
}


inline void *SetActiveWindow(void *hWnd) { stub_unix(__func__); }

inline void *SelectObject(void *hdc, void *h) { stub_unix(__func__); }

inline unsigned int SetTextColor(void *hdc, unsigned int color) { stub_unix(__func__); }

inline unsigned int SetBkColor(void *hdc, unsigned int color) { stub_unix(__func__); }

inline void *MonitorFromWindow(void *hwnd, unsigned int dwFlags) { stub_unix(__func__); }

inline bool GetMonitorInfoA(void *hMonitor, MONITORINFO *lpmi) { stub_unix(__func__); }

inline void *GetDesktopWindow(void) { stub_unix(__func__); }

inline bool EnumDisplaySettings(const char *lpszDeviceName, unsigned int iModeNum,
                         DEVMODE *lpDevMode) {
  stub_unix(__func__);
}

inline long _InterlockedCompareExchange(long *Destination, long Exchange,
                                 long Comperand) {
  stub_unix(__func__);
}

inline int ReleaseDC(void *hWnd, void *hDC) { stub_unix(__func__); }

inline int FillRect(void *hDC, const void *lprc, void *hbr) { stub_unix(__func__); }

inline bool InvalidateRect(void *hWnd, const void *lpRect, bool bErase) {
  stub_unix(__func__);
}


inline bool GetWindowInfo(void *hwnd, WINDOWINFO *pwi) { stub_unix(__func__); }

inline int MultiByteToWideChar(unsigned int CodePage, unsigned long dwFlags,
                        const char *lpMultiByteStr, int cbMultiByte,
                        wchar_t *lpWideCharStr, int cchWideChar) {
  stub_unix(__func__);
}

inline bool ClientToScreen(void *hWnd, void *lpPoint) { stub_unix(__func__); }

inline bool SetCursorPos(int X, int Y) { stub_unix(__func__); }

inline SIZE_T VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer,
                    SIZE_T dwLength) {
  stub_unix(__func__);
}

inline int _ui64toa_s(uint64_t val, char *buf, size_t size, int radix) {
  stub_unix(__func__);
}

inline int _i64toa_s(int64_t val, char *buf, size_t size, int radix) {
  stub_unix(__func__);
}

inline int wcstombs_s(size_t *ret, char *dst, size_t size, const wchar_t *src,
                      size_t count) {
  stub_unix(__func__);
}

inline BOOL SetRect(LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom) {
  stub_unix(__func__);
}
inline BOOL GetWindowRect(HWND hWnd, LPRECT lpRect) { stub_unix(__func__); }

inline LRESULT DefWindowProcW(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
  stub_unix(__func__);
}



// not stubs////////////////////////////////////////////////////////////////////

inline void CopyMemory(PVOID Destination, const VOID *Source, SIZE_T Length) {
  memcpy(Destination, Source, Length);
}

inline void _strdate(char *buf) {
  time_t t = time(nullptr);
  struct tm *tm = localtime(&t);
  strftime(buf, 9, "%m/%d/%y", tm);
}

inline void _strtime(char *buf) {
  time_t t = time(nullptr);
  struct tm *tm = localtime(&t);
  strftime(buf, 9, "%H:%M:%S", tm);
}

inline uint64_t GetTickCount() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

inline char *_strupr(char *str) {
  if (!str)
    return NULL;
  for (char *p = str; *p; p++)
    *p = toupper((unsigned char)*p);
  return str;
}

inline unsigned long GetCurrentThreadId() {
  return (unsigned long)pthread_self();
}

inline char *_strlwr(char *s) {
  for (size_t i = 0; s[i]; ++i)
    s[i] = tolower((unsigned char)s[i]);
  return s;
}

inline int _strupr_s(char *str, size_t size) {
  if (!str || size == 0)
    return -1;
  for (char *p = str; *p; p++)
    *p = toupper((unsigned char)*p);
  return 0;
}

template <typename... Args>
inline int sprintf_s(char *buffer, size_t sizeOfBuffer, const char *format,
                     Args... args) {
  return snprintf(buffer, sizeOfBuffer, format, args...);
}

template <size_t size, typename... Args>
inline int sprintf_s(char (&buffer)[size], const char *format, Args... args) {
  return snprintf(buffer, size, format, args...);
}

template <size_t size> inline int _strupr_s(char (&str)[size]) {
  return _strupr_s(str, size);
}


template <typename... Args>
inline int sscanf_s(const char *buffer, const char *format, Args... args) {
  return sscanf(buffer, format, args...);
}

inline void strncat_s(char* dest, size_t destSize, const char* src, size_t count)
{
  stub_unix(__func__);
}

inline char *_itoa(int i, char *s, int dummy_radix) {
  sprintf(s, "%ld", i);
  return s;
}



inline DWORD GetCurrentProcessId() { return (DWORD)getpid(); }

inline HANDLE GetCurrentProcess() { return (HANDLE)(uintptr_t)getpid(); }



//// not stubs
#include <filesystem>
inline size_t FileSize(std::filesystem::path file)
{
	auto* handle = fopen(file.c_str(), "rb");

	if (handle == nullptr)
		return 0;

	auto pos = ftell(handle);
	fseek(handle, 0, SEEK_END);
	size_t size = ftell(handle);
	fseek(handle, pos, SEEK_SET);
	fclose(handle);
	
	return size;
}

// use default version later
inline char* strncpy_s(char *strDest, size_t numberOfElements,
                     const char *strSource, size_t count) {
  return strncpy(strDest, strSource, count);
}

template <size_t size>
inline char* strncpy_s(char (&strDest)[size], const char *strSource,
                     size_t count) {
  return strncpy_s(strDest, size, strSource, count);
}

#endif
