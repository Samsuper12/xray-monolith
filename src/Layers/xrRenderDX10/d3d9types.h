#pragma once
#ifndef __D3D9TYPES_H__
#define __D3D9TYPES_H__

/*
 * d3d9types.h - Linux stub header for compilation purposes only.
 * All functions are empty stubs and do not provide actual DirectX functionality.
 */

#include <stdint.h>
#include <stddef.h>

/* =========================================================================
 * GUID
 * ========================================================================= */
#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} GUID;
#endif



#ifndef DEFINE_GUID
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern const GUID name
#endif

/* =========================================================================
 * HRESULT helpers
 * ========================================================================= */
#ifndef SUCCEEDED
#define SUCCEEDED(hr)   (((HRESULT)(hr)) >= 0)
#endif
#ifndef FAILED
#define FAILED(hr)      (((HRESULT)(hr)) < 0)
#endif

#ifndef S_OK
#define S_OK            ((HRESULT)0x00000000L)
#endif
#ifndef S_FALSE
#define S_FALSE         ((HRESULT)0x00000001L)
#endif
#ifndef E_NOTIMPL
#define E_NOTIMPL       ((HRESULT)0x80004001L)
#endif
#ifndef E_NOINTERFACE
#define E_NOINTERFACE   ((HRESULT)0x80004002L)
#endif
#ifndef E_FAIL
#define E_FAIL          ((HRESULT)0x80004005L)
#endif
#ifndef E_INVALIDARG
#define E_INVALIDARG    ((HRESULT)0x80070057L)
#endif
#ifndef E_OUTOFMEMORY
#define E_OUTOFMEMORY   ((HRESULT)0x8007000EL)
#endif

/* D3D9 specific HRESULT codes */
#define D3D_OK                              S_OK
#define D3DERR_WRONGTEXTUREFORMAT           ((HRESULT)0x88760818L)
#define D3DERR_UNSUPPORTEDCOLOROPERATION    ((HRESULT)0x88760819L)
#define D3DERR_UNSUPPORTEDCOLORARG         ((HRESULT)0x8876081AL)
#define D3DERR_UNSUPPORTEDALPHAOPERATION   ((HRESULT)0x8876081BL)
#define D3DERR_UNSUPPORTEDALPHAARG         ((HRESULT)0x8876081CL)
#define D3DERR_TOOMANYOPERATIONS           ((HRESULT)0x8876081DL)
#define D3DERR_CONFLICTINGTEXTUREFILTER    ((HRESULT)0x8876081EL)
#define D3DERR_UNSUPPORTEDFACTORVALUE      ((HRESULT)0x8876081FL)
#define D3DERR_CONFLICTINGRENDERSTATE      ((HRESULT)0x88760821L)
#define D3DERR_UNSUPPORTEDTEXTUREFILTER    ((HRESULT)0x88760822L)
#define D3DERR_CONFLICTINGTEXTUREPALETTE   ((HRESULT)0x88760826L)
#define D3DERR_DRIVERINTERNALERROR         ((HRESULT)0x88760827L)
#define D3DERR_NOTFOUND                    ((HRESULT)0x88760866L)
#define D3DERR_MOREDATA                    ((HRESULT)0x88760867L)
#define D3DERR_DEVICELOST                  ((HRESULT)0x88760868L)
#define D3DERR_DEVICENOTRESET              ((HRESULT)0x88760869L)
#define D3DERR_NOTAVAILABLE                ((HRESULT)0x8876086AL)
#define D3DERR_OUTOFVIDEOMEMORY            ((HRESULT)0x8876017CL)
#define D3DERR_INVALIDDEVICE               ((HRESULT)0x8876086BL)
#define D3DERR_INVALIDCALL                 ((HRESULT)0x8876086CL)
#define D3DERR_DRIVERINVALIDCALL           ((HRESULT)0x8876086DL)
#define D3DERR_WASSTILLDRAWING             ((HRESULT)0x8876021CL)
#define D3DOK_NOAUTOGEN                    ((HRESULT)0x0876086FL)
#define D3DERR_DEVICEREMOVED               ((HRESULT)0x88760870L)
#define D3DERR_DEVICEHUNG                  ((HRESULT)0x88760874L)
#define D3DERR_UNSUPPORTEDOVERLAY          ((HRESULT)0x88760875L)
#define D3DERR_UNSUPPORTEDOVERLAYFORMAT    ((HRESULT)0x88760876L)
#define D3DERR_CANNOTPROTECTCONTENT        ((HRESULT)0x88760877L)
#define D3DERR_UNSUPPORTEDCRYPTO           ((HRESULT)0x88760878L)
#define D3DERR_PRESENT_STATISTICS_DISJOINT ((HRESULT)0x88760902L)

/* =========================================================================
 * Calling conventions
 * ========================================================================= */
#ifndef STDMETHODCALLTYPE
#define STDMETHODCALLTYPE
#endif
#ifndef WINAPI
#define WINAPI
#endif
#ifndef CALLBACK
#define CALLBACK
#endif

/* =========================================================================
 * D3D9 primitive types / handles
 * ========================================================================= */


/* =========================================================================
 * Structures
 * ========================================================================= */
typedef struct _D3DVECTOR {
    float x, y, z;
} D3DVECTOR;

typedef struct _D3DCOLORVALUE {
    float r, g, b, a;
} D3DCOLORVALUE;

typedef struct _D3DRECT {
    LONG x1, y1, x2, y2;
} D3DRECT;

typedef struct _D3DMATRIX {
    union {
        struct { float _11,_12,_13,_14, _21,_22,_23,_24, _31,_32,_33,_34, _41,_42,_43,_44; };
        float m[4][4];
    };
} D3DMATRIX;

typedef struct _D3DVIEWPORT9 {
    DWORD X, Y, Width, Height;
    float MinZ, MaxZ;
} D3DVIEWPORT9;

typedef struct _D3DCLIPSTATUS9 {
    DWORD ClipUnion;
    DWORD ClipIntersection;
} D3DCLIPSTATUS9;

typedef struct _D3DMATERIAL9 {
    D3DCOLORVALUE Diffuse;
    D3DCOLORVALUE Ambient;
    D3DCOLORVALUE Specular;
    D3DCOLORVALUE Emissive;
    float         Power;
} D3DMATERIAL9;

typedef struct _D3DLIGHT9 {
    DWORD         Type;           /* D3DLIGHTTYPE */
    D3DCOLORVALUE Diffuse;
    D3DCOLORVALUE Specular;
    D3DCOLORVALUE Ambient;
    D3DVECTOR     Position;
    D3DVECTOR     Direction;
    float         Range;
    float         Falloff;
    float         Attenuation0;
    float         Attenuation1;
    float         Attenuation2;
    float         Theta;
    float         Phi;
} D3DLIGHT9;

typedef struct _D3DVERTEXELEMENT9 {
    WORD  Stream;
    WORD  Offset;
    BYTE  Type;     /* D3DDECLTYPE */
    BYTE  Method;   /* D3DDECLMETHOD */
    BYTE  Usage;    /* D3DDECLUSAGE */
    BYTE  UsageIndex;
} D3DVERTEXELEMENT9;

#define D3DDECL_END() {0xFF, 0, D3DDECLTYPE_UNUSED, 0, 0, 0}

typedef struct _D3DDISPLAYMODE {
    UINT        Width, Height, RefreshRate;
    DWORD       Format;         /* D3DFORMAT */
} D3DDISPLAYMODE;

typedef struct _D3DDEVICE_CREATION_PARAMETERS {
    UINT    AdapterOrdinal;
    DWORD   DeviceType;         /* D3DDEVTYPE */
    HWND    hFocusWindow;
    DWORD   BehaviorFlags;
} D3DDEVICE_CREATION_PARAMETERS;

typedef struct _D3DPRESENT_PARAMETERS {
    UINT                BackBufferWidth;
    UINT                BackBufferHeight;
    DWORD               BackBufferFormat;   /* D3DFORMAT */
    UINT                BackBufferCount;
    DWORD               MultiSampleType;    /* D3DMULTISAMPLE_TYPE */
    DWORD               MultiSampleQuality;
    DWORD               SwapEffect;         /* D3DSWAPEFFECT */
    HWND                hDeviceWindow;
    BOOL                Windowed;
    BOOL                EnableAutoDepthStencil;
    DWORD               AutoDepthStencilFormat; /* D3DFORMAT */
    DWORD               Flags;
    UINT                FullScreen_RefreshRateInHz;
    UINT                PresentationInterval;
} D3DPRESENT_PARAMETERS;

typedef struct _D3DGAMMARAMP {
    WORD red[256];
    WORD green[256];
    WORD blue[256];
} D3DGAMMARAMP;

typedef struct _D3DVERTEXBUFFER_DESC {
    DWORD   Format;     /* D3DFORMAT */
    DWORD   Type;       /* D3DRESOURCETYPE */
    DWORD   Usage;
    DWORD   Pool;       /* D3DPOOL */
    UINT    Size;
    DWORD   FVF;
} D3DVERTEXBUFFER_DESC;

typedef struct _D3DINDEXBUFFER_DESC {
    DWORD   Format;     /* D3DFORMAT */
    DWORD   Type;       /* D3DRESOURCETYPE */
    DWORD   Usage;
    DWORD   Pool;       /* D3DPOOL */
    UINT    Size;
} D3DINDEXBUFFER_DESC;

typedef struct _D3DSURFACE_DESC {
    DWORD   Format;     /* D3DFORMAT */
    DWORD   Type;       /* D3DRESOURCETYPE */
    DWORD   Usage;
    DWORD   Pool;       /* D3DPOOL */
    DWORD   MultiSampleType;    /* D3DMULTISAMPLE_TYPE */
    DWORD   MultiSampleQuality;
    UINT    Width, Height;
} D3DSURFACE_DESC;

typedef struct _D3DVOLUME_DESC {
    DWORD   Format;     /* D3DFORMAT */
    DWORD   Type;       /* D3DRESOURCETYPE */
    DWORD   Usage;
    DWORD   Pool;       /* D3DPOOL */
    UINT    Width, Height, Depth;
} D3DVOLUME_DESC;

typedef struct _D3DLOCKED_RECT {
    INT     Pitch;
    void*   pBits;
} D3DLOCKED_RECT;

typedef struct _D3DLOCKED_BOX {
    INT     RowPitch;
    INT     SlicePitch;
    void*   pBits;
} D3DLOCKED_BOX;

typedef struct _D3DBOX {
    UINT Left, Top, Right, Bottom, Front, Back;
} D3DBOX;

typedef struct _D3DRANGE {
    UINT Offset, Size;
} D3DRANGE;

typedef struct _D3DRASTER_STATUS {
    BOOL InVBlank;
    UINT ScanLine;
} D3DRASTER_STATUS;

typedef struct _D3DCAPS9 {
    DWORD   DeviceType;
    UINT    AdapterOrdinal;
    DWORD   Caps, Caps2, Caps3;
    DWORD   PresentationIntervals;
    DWORD   CursorCaps;
    DWORD   DevCaps;
    DWORD   PrimitiveMiscCaps;
    DWORD   RasterCaps;
    DWORD   ZCmpCaps;
    DWORD   SrcBlendCaps;
    DWORD   DestBlendCaps;
    DWORD   AlphaCmpCaps;
    DWORD   ShadeCaps;
    DWORD   TextureCaps;
    DWORD   TextureFilterCaps;
    DWORD   CubeTextureFilterCaps;
    DWORD   VolumeTextureFilterCaps;
    DWORD   TextureAddressCaps;
    DWORD   VolumeTextureAddressCaps;
    DWORD   LineCaps;
    DWORD   MaxTextureWidth, MaxTextureHeight;
    DWORD   MaxVolumeExtent;
    DWORD   MaxTextureRepeat;
    DWORD   MaxTextureAspectRatio;
    DWORD   MaxAnisotropy;
    float   MaxVertexW;
    float   GuardBandLeft, GuardBandTop, GuardBandRight, GuardBandBottom;
    float   ExtentsAdjust;
    DWORD   StencilCaps;
    DWORD   FVFCaps;
    DWORD   TextureOpCaps;
    DWORD   MaxTextureBlendStages;
    DWORD   MaxSimultaneousTextures;
    DWORD   VertexProcessingCaps;
    DWORD   MaxActiveLights;
    DWORD   MaxUserClipPlanes;
    DWORD   MaxVertexBlendMatrices;
    DWORD   MaxVertexBlendMatrixIndex;
    float   MaxPointSize;
    DWORD   MaxPrimitiveCount;
    DWORD   MaxVertexIndex;
    DWORD   MaxStreams;
    DWORD   MaxStreamStride;
    DWORD   VertexShaderVersion;
    DWORD   MaxVertexShaderConst;
    DWORD   PixelShaderVersion;
    float   PixelShader1xMaxValue;
    DWORD   DevCaps2;
    float   MaxNpatchTessellationLevel;
    DWORD   Reserved5;
    UINT    MasterAdapterOrdinal;
    UINT    AdapterOrdinalInGroup;
    UINT    NumberOfAdaptersInGroup;
    DWORD   DeclTypes;
    DWORD   NumSimultaneousRTs;
    DWORD   StretchRectFilterCaps;
    /* VS20 / PS20 caps omitted for brevity - add structs if needed */
    DWORD   VS20Caps[4];
    DWORD   PS20Caps[4];
    DWORD   VertexTextureFilterCaps;
    DWORD   MaxVShaderInstructionsExecuted;
    DWORD   MaxPShaderInstructionsExecuted;
    DWORD   MaxVertexShader30InstructionSlots;
    DWORD   MaxPixelShader30InstructionSlots;
} D3DCAPS9;

typedef struct _D3DADAPTER_IDENTIFIER9 {
    char    Driver[512];
    char    Description[512];
    char    DeviceName[32];
    LONGLONG DriverVersion;
    DWORD   VendorId;
    DWORD   DeviceId;
    DWORD   SubSysId;
    DWORD   Revision;
    GUID    DeviceIdentifier;
    DWORD   WHQLLevel;
} D3DADAPTER_IDENTIFIER9;

typedef struct _D3DDEVINFO_D3DVERTEXSTATS {
    DWORD NumRenderedTriangles;
    DWORD NumExtraClippingTriangles;
} D3DDEVINFO_D3DVERTEXSTATS;

typedef struct _D3DRESOURCESTATS {
    BOOL    bThrashing;
    DWORD   ApproxBytesDownloaded;
    DWORD   NumEvicts;
    DWORD   NumVidCreates;
    DWORD   LastPri;
    DWORD   NumUsed;
    DWORD   NumUsedInVidMem;
    DWORD   WorkingSet;
    DWORD   WorkingSetBytes;
    DWORD   TotalManaged;
    DWORD   TotalBytes;
} D3DRESOURCESTATS;

typedef struct _D3DDEVINFO_D3DRESOURCEMANAGER {
    D3DRESOURCESTATS stats[8];
} D3DDEVINFO_D3DRESOURCEMANAGER;

typedef struct _D3DDEVINFO_VCACHE {
    DWORD   Pattern;
    DWORD   OptMethod;
    DWORD   CacheSize;
    DWORD   MagicNumber;
} D3DDEVINFO_VCACHE;

typedef struct _D3DOVERLAYCAPS {
    UINT Caps;
    UINT MaxOverlayDisplayWidth;
    UINT MaxOverlayDisplayHeight;
} D3DOVERLAYCAPS;

typedef struct _D3DAUTHENTICATEDCHANNELDESC {
    GUID ChannelGUID;
    HANDLE DeviceHandle;
} D3DAUTHENTICATEDCHANNELDESC;

typedef struct _D3DCONTENTPROTECTIONCAPS {
    DWORD Caps;
    GUID  KeyExchangeType;
    UINT  BufferAlignmentStart;
    UINT  BlockAlignmentSize;
    ULONGLONG ProtectedMemorySize;
} D3DCONTENTPROTECTIONCAPS;

typedef struct _D3DCOMPOSITIONSCANBEHAVIOR {
    DWORD CompositionEnabled;
    DWORD ScanlineOrdering;
} D3DCOMPOSITIONSCANBEHAVIOR;

/* =========================================================================
 * Enumerations
 * ========================================================================= */

/* D3DFORMAT */
typedef enum _D3DFORMAT {
    D3DFMT_UNKNOWN              = 0,
    D3DFMT_R8G8B8               = 20,
    D3DFMT_A8R8G8B8             = 21,
    D3DFMT_X8R8G8B8             = 22,
    D3DFMT_R5G6B5               = 23,
    D3DFMT_X1R5G5B5             = 24,
    D3DFMT_A1R5G5B5             = 25,
    D3DFMT_A4R4G4B4             = 26,
    D3DFMT_R3G3B2               = 27,
    D3DFMT_A8                   = 28,
    D3DFMT_A8R3G3B2             = 29,
    D3DFMT_X4R4G4B4             = 30,
    D3DFMT_A2B10G10R10          = 31,
    D3DFMT_A8B8G8R8             = 32,
    D3DFMT_X8B8G8R8             = 33,
    D3DFMT_G16R16               = 34,
    D3DFMT_A2R10G10B10          = 35,
    D3DFMT_A16B16G16R16         = 36,
    D3DFMT_A8P8                 = 40,
    D3DFMT_P8                   = 41,
    D3DFMT_L8                   = 50,
    D3DFMT_A8L8                 = 51,
    D3DFMT_A4L4                 = 52,
    D3DFMT_V8U8                 = 60,
    D3DFMT_L6V5U5               = 61,
    D3DFMT_X8L8V8U8             = 62,
    D3DFMT_Q8W8V8U8             = 63,
    D3DFMT_V16U16               = 64,
    D3DFMT_A2W10V10U10          = 67,
    D3DFMT_UYVY                 = 0x59565955, /* MAKEFOURCC('U','Y','V','Y') */
    D3DFMT_R8G8_B8G8            = 0x47424752, /* MAKEFOURCC('R','G','B','G') */
    D3DFMT_YUY2                 = 0x32595559, /* MAKEFOURCC('Y','U','Y','2') */
    D3DFMT_G8R8_G8B8            = 0x42475247, /* MAKEFOURCC('G','R','G','B') */
    D3DFMT_DXT1                 = 0x31545844, /* MAKEFOURCC('D','X','T','1') */
    D3DFMT_DXT2                 = 0x32545844,
    D3DFMT_DXT3                 = 0x33545844,
    D3DFMT_DXT4                 = 0x34545844,
    D3DFMT_DXT5                 = 0x35545844,
    D3DFMT_D16_LOCKABLE         = 70,
    D3DFMT_D32                  = 71,
    D3DFMT_D15S1                = 73,
    D3DFMT_D24S8                = 75,
    D3DFMT_D24X8                = 77,
    D3DFMT_D24X4S4              = 79,
    D3DFMT_D16                  = 80,
    D3DFMT_D32F_LOCKABLE        = 82,
    D3DFMT_D24FS8               = 83,
    D3DFMT_D32_LOCKABLE         = 84,
    D3DFMT_S8_LOCKABLE          = 85,
    D3DFMT_L16                  = 81,
    D3DFMT_VERTEXDATA           = 100,
    D3DFMT_INDEX16              = 101,
    D3DFMT_INDEX32              = 102,
    D3DFMT_Q16W16V16U16         = 110,
    D3DFMT_MULTI2_ARGB8         = 0x3154454D, /* MAKEFOURCC('M','E','T','1') */
    D3DFMT_R16F                 = 111,
    D3DFMT_G16R16F              = 112,
    D3DFMT_A16B16G16R16F        = 113,
    D3DFMT_R32F                 = 114,
    D3DFMT_G32R32F              = 115,
    D3DFMT_A32B32G32R32F        = 116,
    D3DFMT_CxV8U8               = 117,
    D3DFMT_A1                   = 118,
    D3DFMT_A2B10G10R10_XR_BIAS  = 119,
    D3DFMT_BINARYBUFFER         = 199,
    D3DFMT_FORCE_DWORD          = 0x7fffffff,
} D3DFORMAT;

/* D3DRESOURCETYPE */
typedef enum _D3DRESOURCETYPE {
    D3DRTYPE_SURFACE        = 1,
    D3DRTYPE_VOLUME         = 2,
    D3DRTYPE_TEXTURE        = 3,
    D3DRTYPE_VOLUMETEXTURE  = 4,
    D3DRTYPE_CUBETEXTURE    = 5,
    D3DRTYPE_VERTEXBUFFER   = 6,
    D3DRTYPE_INDEXBUFFER    = 7,
    D3DRTYPE_FORCE_DWORD    = 0x7fffffff,
} D3DRESOURCETYPE;

/* D3DPOOL */
typedef enum _D3DPOOL {
    D3DPOOL_DEFAULT     = 0,
    D3DPOOL_MANAGED     = 1,
    D3DPOOL_SYSTEMMEM   = 2,
    D3DPOOL_SCRATCH     = 3,
    D3DPOOL_FORCE_DWORD = 0x7fffffff,
} D3DPOOL;

/* D3DDEVTYPE */
typedef enum _D3DDEVTYPE {
    D3DDEVTYPE_HAL         = 1,
    D3DDEVTYPE_REF         = 2,
    D3DDEVTYPE_SW          = 3,
    D3DDEVTYPE_NULLREF     = 4,
    D3DDEVTYPE_FORCE_DWORD = 0xffffffff,
} D3DDEVTYPE;

/* D3DMULTISAMPLE_TYPE */
typedef enum _D3DMULTISAMPLE_TYPE {
    D3DMULTISAMPLE_NONE         = 0,
    D3DMULTISAMPLE_NONMASKABLE  = 1,
    D3DMULTISAMPLE_2_SAMPLES    = 2,
    D3DMULTISAMPLE_3_SAMPLES    = 3,
    D3DMULTISAMPLE_4_SAMPLES    = 4,
    D3DMULTISAMPLE_5_SAMPLES    = 5,
    D3DMULTISAMPLE_6_SAMPLES    = 6,
    D3DMULTISAMPLE_7_SAMPLES    = 7,
    D3DMULTISAMPLE_8_SAMPLES    = 8,
    D3DMULTISAMPLE_9_SAMPLES    = 9,
    D3DMULTISAMPLE_10_SAMPLES   = 10,
    D3DMULTISAMPLE_11_SAMPLES   = 11,
    D3DMULTISAMPLE_12_SAMPLES   = 12,
    D3DMULTISAMPLE_13_SAMPLES   = 13,
    D3DMULTISAMPLE_14_SAMPLES   = 14,
    D3DMULTISAMPLE_15_SAMPLES   = 15,
    D3DMULTISAMPLE_16_SAMPLES   = 16,
    D3DMULTISAMPLE_FORCE_DWORD  = 0xffffffff,
} D3DMULTISAMPLE_TYPE;

/* D3DSWAPEFFECT */
typedef enum _D3DSWAPEFFECT {
    D3DSWAPEFFECT_DISCARD       = 1,
    D3DSWAPEFFECT_FLIP          = 2,
    D3DSWAPEFFECT_COPY          = 3,
    D3DSWAPEFFECT_OVERLAY       = 4,
    D3DSWAPEFFECT_FLIPEX        = 5,
    D3DSWAPEFFECT_FORCE_DWORD   = 0xffffffff,
} D3DSWAPEFFECT;

/* D3DPRIMITIVETYPE */
typedef enum _D3DPRIMITIVETYPE {
    D3DPT_POINTLIST     = 1,
    D3DPT_LINELIST      = 2,
    D3DPT_LINESTRIP     = 3,
    D3DPT_TRIANGLELIST  = 4,
    D3DPT_TRIANGLESTRIP = 5,
    D3DPT_TRIANGLEFAN   = 6,
    D3DPT_FORCE_DWORD   = 0x7fffffff,
} D3DPRIMITIVETYPE;

/* D3DTRANSFORMSTATETYPE */
typedef enum _D3DTRANSFORMSTATETYPE {
    D3DTS_VIEW          = 2,
    D3DTS_PROJECTION    = 3,
    D3DTS_TEXTURE0      = 16,
    D3DTS_TEXTURE1      = 17,
    D3DTS_TEXTURE2      = 18,
    D3DTS_TEXTURE3      = 19,
    D3DTS_TEXTURE4      = 20,
    D3DTS_TEXTURE5      = 21,
    D3DTS_TEXTURE6      = 22,
    D3DTS_TEXTURE7      = 23,
    D3DTS_FORCE_DWORD   = 0x7fffffff,
} D3DTRANSFORMSTATETYPE;

#define D3DTS_WORLDMATRIX(index)    (D3DTRANSFORMSTATETYPE)(index + 256)
#define D3DTS_WORLD                 D3DTS_WORLDMATRIX(0)
#define D3DTS_WORLD1                D3DTS_WORLDMATRIX(1)
#define D3DTS_WORLD2                D3DTS_WORLDMATRIX(2)
#define D3DTS_WORLD3                D3DTS_WORLDMATRIX(3)

/* D3DLIGHTTYPE */
typedef enum _D3DLIGHTTYPE {
    D3DLIGHT_POINT          = 1,
    D3DLIGHT_SPOT           = 2,
    D3DLIGHT_DIRECTIONAL    = 3,
    D3DLIGHT_FORCE_DWORD    = 0x7fffffff,
} D3DLIGHTTYPE;

/* D3DRENDERSTATETYPE */
typedef enum _D3DRENDERSTATETYPE {
    D3DRS_ZENABLE                   = 7,
    D3DRS_FILLMODE                  = 8,
    D3DRS_SHADEMODE                 = 9,
    D3DRS_ZWRITEENABLE              = 14,
    D3DRS_ALPHATESTENABLE           = 15,
    D3DRS_LASTPIXEL                 = 16,
    D3DRS_SRCBLEND                  = 19,
    D3DRS_DESTBLEND                 = 20,
    D3DRS_CULLMODE                  = 22,
    D3DRS_ZFUNC                     = 23,
    D3DRS_ALPHAREF                  = 24,
    D3DRS_ALPHAFUNC                 = 25,
    D3DRS_DITHERENABLE              = 26,
    D3DRS_ALPHABLENDENABLE          = 27,
    D3DRS_FOGENABLE                 = 28,
    D3DRS_SPECULARENABLE            = 29,
    D3DRS_FOGCOLOR                  = 34,
    D3DRS_FOGTABLEMODE              = 35,
    D3DRS_FOGSTART                  = 36,
    D3DRS_FOGEND                    = 37,
    D3DRS_FOGDENSITY                = 38,
    D3DRS_RANGEFOGENABLE            = 48,
    D3DRS_STENCILENABLE             = 52,
    D3DRS_STENCILFAIL               = 53,
    D3DRS_STENCILZFAIL              = 54,
    D3DRS_STENCILPASS               = 55,
    D3DRS_STENCILFUNC               = 56,
    D3DRS_STENCILREF                = 57,
    D3DRS_STENCILMASK               = 58,
    D3DRS_STENCILWRITEMASK          = 59,
    D3DRS_TEXTUREFACTOR             = 60,
    D3DRS_WRAP0                     = 128,
    D3DRS_WRAP1                     = 129,
    D3DRS_WRAP2                     = 130,
    D3DRS_WRAP3                     = 131,
    D3DRS_WRAP4                     = 132,
    D3DRS_WRAP5                     = 133,
    D3DRS_WRAP6                     = 134,
    D3DRS_WRAP7                     = 135,
    D3DRS_CLIPPING                  = 136,
    D3DRS_LIGHTING                  = 137,
    D3DRS_AMBIENT                   = 139,
    D3DRS_FOGVERTEXMODE             = 140,
    D3DRS_COLORVERTEX               = 141,
    D3DRS_LOCALVIEWER               = 142,
    D3DRS_NORMALIZENORMALS          = 143,
    D3DRS_DIFFUSEMATERIALSOURCE     = 145,
    D3DRS_SPECULARMATERIALSOURCE    = 146,
    D3DRS_AMBIENTMATERIALSOURCE     = 147,
    D3DRS_EMISSIVEMATERIALSOURCE    = 148,
    D3DRS_VERTEXBLEND               = 151,
    D3DRS_CLIPPLANEENABLE           = 152,
    D3DRS_POINTSIZE                 = 154,
    D3DRS_POINTSIZE_MIN             = 155,
    D3DRS_POINTSPRITEENABLE         = 156,
    D3DRS_POINTSCALEENABLE          = 157,
    D3DRS_POINTSCALE_A              = 158,
    D3DRS_POINTSCALE_B              = 159,
    D3DRS_POINTSCALE_C              = 160,
    D3DRS_MULTISAMPLEANTIALIAS      = 161,
    D3DRS_MULTISAMPLEMASK           = 162,
    D3DRS_PATCHEDGESTYLE            = 163,
    D3DRS_DEBUGMONITORTOKEN         = 165,
    D3DRS_POINTSIZE_MAX             = 166,
    D3DRS_INDEXEDVERTEXBLENDENABLE  = 167,
    D3DRS_COLORWRITEENABLE          = 168,
    D3DRS_TWEENFACTOR               = 170,
    D3DRS_BLENDOP                   = 171,
    D3DRS_POSITIONDEGREE            = 172,
    D3DRS_NORMALDEGREE              = 173,
    D3DRS_SCISSORTESTENABLE         = 174,
    D3DRS_SLOPESCALEDEPTHBIAS       = 175,
    D3DRS_ANTIALIASEDLINEENABLE     = 176,
    D3DRS_MINTESSELLATIONLEVEL      = 178,
    D3DRS_MAXTESSELLATIONLEVEL      = 179,
    D3DRS_ADAPTIVETESS_X            = 180,
    D3DRS_ADAPTIVETESS_Y            = 181,
    D3DRS_ADAPTIVETESS_Z            = 182,
    D3DRS_ADAPTIVETESS_W            = 183,
    D3DRS_ENABLEADAPTIVETESSELLATION = 184,
    D3DRS_TWOSIDEDSTENCILMODE       = 185,
    D3DRS_CCW_STENCILFAIL           = 186,
    D3DRS_CCW_STENCILZFAIL          = 187,
    D3DRS_CCW_STENCILPASS           = 188,
    D3DRS_CCW_STENCILFUNC           = 189,
    D3DRS_COLORWRITEENABLE1         = 190,
    D3DRS_COLORWRITEENABLE2         = 191,
    D3DRS_COLORWRITEENABLE3         = 192,
    D3DRS_BLENDFACTOR               = 193,
    D3DRS_SRGBWRITEENABLE           = 194,
    D3DRS_DEPTHBIAS                 = 195,
    D3DRS_WRAP8                     = 198,
    D3DRS_WRAP9                     = 199,
    D3DRS_WRAP10                    = 200,
    D3DRS_WRAP11                    = 201,
    D3DRS_WRAP12                    = 202,
    D3DRS_WRAP13                    = 203,
    D3DRS_WRAP14                    = 204,
    D3DRS_WRAP15                    = 205,
    D3DRS_SEPARATEALPHABLENDENABLE  = 206,
    D3DRS_SRCBLENDALPHA             = 207,
    D3DRS_DESTBLENDALPHA            = 208,
    D3DRS_BLENDOPALPHA              = 209,
    D3DRS_FORCE_DWORD               = 0x7fffffff,
} D3DRENDERSTATETYPE;

/* D3DBLEND */
typedef enum _D3DBLEND {
    D3DBLEND_ZERO               = 1,
    D3DBLEND_ONE                = 2,
    D3DBLEND_SRCCOLOR           = 3,
    D3DBLEND_INVSRCCOLOR        = 4,
    D3DBLEND_SRCALPHA           = 5,
    D3DBLEND_INVSRCALPHA        = 6,
    D3DBLEND_DESTALPHA          = 7,
    D3DBLEND_INVDESTALPHA       = 8,
    D3DBLEND_DESTCOLOR          = 9,
    D3DBLEND_INVDESTCOLOR       = 10,
    D3DBLEND_SRCALPHASAT        = 11,
    D3DBLEND_BOTHSRCALPHA       = 12,
    D3DBLEND_BOTHINVSRCALPHA    = 13,
    D3DBLEND_BLENDFACTOR        = 14,
    D3DBLEND_INVBLENDFACTOR     = 15,
    D3DBLEND_SRCCOLOR2          = 16,
    D3DBLEND_INVSRCCOLOR2       = 17,
    D3DBLEND_FORCE_DWORD        = 0x7fffffff,
} D3DBLEND;

/* D3DBLENDOP */
typedef enum _D3DBLENDOP {
    D3DBLENDOP_ADD          = 1,
    D3DBLENDOP_SUBTRACT     = 2,
    D3DBLENDOP_REVSUBTRACT  = 3,
    D3DBLENDOP_MIN          = 4,
    D3DBLENDOP_MAX          = 5,
    D3DBLENDOP_FORCE_DWORD  = 0x7fffffff,
} D3DBLENDOP;

/* D3DCMPFUNC */
typedef enum _D3DCMPFUNC {
    D3DCMP_NEVER        = 1,
    D3DCMP_LESS         = 2,
    D3DCMP_EQUAL        = 3,
    D3DCMP_LESSEQUAL    = 4,
    D3DCMP_GREATER      = 5,
    D3DCMP_NOTEQUAL     = 6,
    D3DCMP_GREATEREQUAL = 7,
    D3DCMP_ALWAYS       = 8,
    D3DCMP_FORCE_DWORD  = 0x7fffffff,
} D3DCMPFUNC;

/* D3DSTENCILOP */
typedef enum _D3DSTENCILOP {
    D3DSTENCILOP_KEEP       = 1,
    D3DSTENCILOP_ZERO       = 2,
    D3DSTENCILOP_REPLACE    = 3,
    D3DSTENCILOP_INCRSAT    = 4,
    D3DSTENCILOP_DECRSAT    = 5,
    D3DSTENCILOP_INVERT     = 6,
    D3DSTENCILOP_INCR       = 7,
    D3DSTENCILOP_DECR       = 8,
    D3DSTENCILOP_FORCE_DWORD = 0x7fffffff,
} D3DSTENCILOP;

/* D3DFILLMODE */
typedef enum _D3DFILLMODE {
    D3DFILL_POINT       = 1,
    D3DFILL_WIREFRAME   = 2,
    D3DFILL_SOLID       = 3,
    D3DFILL_FORCE_DWORD = 0x7fffffff,
} D3DFILLMODE;

/* D3DSHADEMODE */
typedef enum _D3DSHADEMODE {
    D3DSHADE_FLAT       = 1,
    D3DSHADE_GOURAUD    = 2,
    D3DSHADE_PHONG      = 3,
    D3DSHADE_FORCE_DWORD = 0x7fffffff,
} D3DSHADEMODE;

/* D3DCULL */
typedef enum _D3DCULL {
    D3DCULL_NONE        = 1,
    D3DCULL_CW          = 2,
    D3DCULL_CCW         = 3,
    D3DCULL_FORCE_DWORD = 0x7fffffff,
} D3DCULL;

/* D3DTEXTUREADDRESS */
typedef enum _D3DTEXTUREADDRESS {
    D3DTADDRESS_WRAP        = 1,
    D3DTADDRESS_MIRROR      = 2,
    D3DTADDRESS_CLAMP       = 3,
    D3DTADDRESS_BORDER      = 4,
    D3DTADDRESS_MIRRORONCE  = 5,
    D3DTADDRESS_FORCE_DWORD = 0x7fffffff,
} D3DTEXTUREADDRESS;

/* D3DTEXTUREFILTERTYPE */
typedef enum _D3DTEXTUREFILTERTYPE {
    D3DTEXF_NONE            = 0,
    D3DTEXF_POINT           = 1,
    D3DTEXF_LINEAR          = 2,
    D3DTEXF_ANISOTROPIC     = 3,
    D3DTEXF_PYRAMIDALQUAD   = 6,
    D3DTEXF_GAUSSIANQUAD    = 7,
    D3DTEXF_CONVOLUTIONMONO = 8,
    D3DTEXF_FORCE_DWORD     = 0x7fffffff,
} D3DTEXTUREFILTERTYPE;

/* D3DTEXTUREOP */
typedef enum _D3DTEXTUREOP {
    D3DTOP_DISABLE                  = 1,
    D3DTOP_SELECTARG1               = 2,
    D3DTOP_SELECTARG2               = 3,
    D3DTOP_MODULATE                 = 4,
    D3DTOP_MODULATE2X               = 5,
    D3DTOP_MODULATE4X               = 6,
    D3DTOP_ADD                      = 7,
    D3DTOP_ADDSIGNED                = 8,
    D3DTOP_ADDSIGNED2X              = 9,
    D3DTOP_SUBTRACT                 = 10,
    D3DTOP_ADDSMOOTH                = 11,
    D3DTOP_BLENDDIFFUSEALPHA        = 12,
    D3DTOP_BLENDTEXTUREALPHA        = 13,
    D3DTOP_BLENDFACTORALPHA         = 14,
    D3DTOP_BLENDTEXTUREALPHAPM      = 15,
    D3DTOP_BLENDCURRENTALPHA        = 16,
    D3DTOP_PREMODULATE              = 17,
    D3DTOP_MODULATEALPHA_ADDCOLOR   = 18,
    D3DTOP_MODULATECOLOR_ADDALPHA   = 19,
    D3DTOP_MODULATEINVALPHA_ADDCOLOR = 20,
    D3DTOP_MODULATEINVCOLOR_ADDALPHA = 21,
    D3DTOP_BUMPENVMAP               = 22,
    D3DTOP_BUMPENVMAPLUMINANCE      = 23,
    D3DTOP_DOTPRODUCT3              = 24,
    D3DTOP_MULTIPLYADD              = 25,
    D3DTOP_LERP                     = 26,
    D3DTOP_FORCE_DWORD              = 0x7fffffff,
} D3DTEXTUREOP;

/* D3DTEXTURESTAGESTATETYPE */
typedef enum _D3DTEXTURESTAGESTATETYPE {
    D3DTSS_COLOROP              = 1,
    D3DTSS_COLORARG1            = 2,
    D3DTSS_COLORARG2            = 3,
    D3DTSS_ALPHAOP              = 4,
    D3DTSS_ALPHAARG1            = 5,
    D3DTSS_ALPHAARG2            = 6,
    D3DTSS_BUMPENVMAT00         = 7,
    D3DTSS_BUMPENVMAT01         = 8,
    D3DTSS_BUMPENVMAT10         = 9,
    D3DTSS_BUMPENVMAT11         = 10,
    D3DTSS_TEXCOORDINDEX        = 11,
    D3DTSS_BUMPENVLSCALE        = 22,
    D3DTSS_BUMPENVLOFFSET       = 23,
    D3DTSS_TEXTURETRANSFORMFLAGS = 24,
    D3DTSS_COLORARG0            = 26,
    D3DTSS_ALPHAARG0            = 27,
    D3DTSS_RESULTARG            = 28,
    D3DTSS_CONSTANT             = 32,
    D3DTSS_FORCE_DWORD          = 0x7fffffff,
} D3DTEXTURESTAGESTATETYPE;

/* D3DSAMPLERSTATETYPE */
typedef enum _D3DSAMPLERSTATETYPE {
    D3DSAMP_ADDRESSU        = 1,
    D3DSAMP_ADDRESSV        = 2,
    D3DSAMP_ADDRESSW        = 3,
    D3DSAMP_BORDERCOLOR     = 4,
    D3DSAMP_MAGFILTER       = 5,
    D3DSAMP_MINFILTER       = 6,
    D3DSAMP_MIPFILTER       = 7,
    D3DSAMP_MIPMAPLODBIAS   = 8,
    D3DSAMP_MAXMIPLEVEL     = 9,
    D3DSAMP_MAXANISOTROPY   = 10,
    D3DSAMP_SRGBTEXTURE     = 11,
    D3DSAMP_ELEMENTINDEX    = 12,
    D3DSAMP_DMAPOFFSET      = 13,
    D3DSAMP_FORCE_DWORD     = 0x7fffffff,
} D3DSAMPLERSTATETYPE;

/* D3DFOGMODE */
typedef enum _D3DFOGMODE {
    D3DFOG_NONE         = 0,
    D3DFOG_EXP          = 1,
    D3DFOG_EXP2         = 2,
    D3DFOG_LINEAR       = 3,
    D3DFOG_FORCE_DWORD  = 0x7fffffff,
} D3DFOGMODE;

/* D3DZBUFFERTYPE */
typedef enum _D3DZBUFFERTYPE {
    D3DZB_FALSE         = 0,
    D3DZB_TRUE          = 1,
    D3DZB_USEW          = 2,
    D3DZB_FORCE_DWORD   = 0x7fffffff,
} D3DZBUFFERTYPE;

/* D3DANTIALIASMODE (legacy) */
typedef enum _D3DANTIALIASMODE {
    D3DANTIALIAS_NONE           = 0,
    D3DANTIALIAS_SORTDEPENDENT  = 1,
    D3DANTIALIAS_SORTINDEPENDENT = 2,
    D3DANTIALIAS_FORCE_DWORD    = 0x7fffffff,
} D3DANTIALIASMODE;

/* D3DVERTEXBLENDFLAGS */
typedef enum _D3DVERTEXBLENDFLAGS {
    D3DVBF_DISABLE      = 0,
    D3DVBF_1WEIGHTS     = 1,
    D3DVBF_2WEIGHTS     = 2,
    D3DVBF_3WEIGHTS     = 3,
    D3DVBF_TWEENING     = 255,
    D3DVBF_0WEIGHTS     = 256,
    D3DVBF_FORCE_DWORD  = 0x7fffffff,
} D3DVERTEXBLENDFLAGS;

/* D3DTEXTURETRANSFORMFLAGS */
typedef enum _D3DTEXTURETRANSFORMFLAGS {
    D3DTTFF_DISABLE         = 0,
    D3DTTFF_COUNT1          = 1,
    D3DTTFF_COUNT2          = 2,
    D3DTTFF_COUNT3          = 3,
    D3DTTFF_COUNT4          = 4,
    D3DTTFF_PROJECTED       = 256,
    D3DTTFF_FORCE_DWORD     = 0x7fffffff,
} D3DTEXTURETRANSFORMFLAGS;

/* D3DMATERIALCOLORSOURCE */
typedef enum _D3DMATERIALCOLORSOURCE {
    D3DMCS_MATERIAL     = 0,
    D3DMCS_COLOR1       = 1,
    D3DMCS_COLOR2       = 2,
    D3DMCS_FORCE_DWORD  = 0x7fffffff,
} D3DMATERIALCOLORSOURCE;

/* D3DPATCHEDGESTYLE */
typedef enum _D3DPATCHEDGESTYLE {
    D3DPATCHEDGE_DISCRETE   = 0,
    D3DPATCHEDGE_CONTINUOUS = 1,
    D3DPATCHEDGE_FORCE_DWORD = 0x7fffffff,
} D3DPATCHEDGESTYLE;

/* D3DQUERYTYPE */
typedef enum _D3DQUERYTYPE {
    D3DQUERYTYPE_VCACHE             = 4,
    D3DQUERYTYPE_RESOURCEMANAGER    = 5,
    D3DQUERYTYPE_VERTEXSTATS        = 6,
    D3DQUERYTYPE_EVENT              = 8,
    D3DQUERYTYPE_OCCLUSION          = 9,
    D3DQUERYTYPE_TIMESTAMP          = 10,
    D3DQUERYTYPE_TIMESTAMPDISJOINT  = 11,
    D3DQUERYTYPE_TIMESTAMPFREQ      = 12,
    D3DQUERYTYPE_PIPELINETIMINGS    = 13,
    D3DQUERYTYPE_INTERFACETIMINGS   = 14,
    D3DQUERYTYPE_VERTEXTIMINGS      = 15,
    D3DQUERYTYPE_PIXELTIMINGS       = 16,
    D3DQUERYTYPE_BANDWIDTHTIMINGS   = 17,
    D3DQUERYTYPE_CACHEUTILIZATION   = 18,
    D3DQUERYTYPE_MEMORYPRESSURE     = 19,
} D3DQUERYTYPE;

/* D3DBACKBUFFER_TYPE */
typedef enum _D3DBACKBUFFER_TYPE {
    D3DBACKBUFFER_TYPE_MONO         = 0,
    D3DBACKBUFFER_TYPE_LEFT         = 1,
    D3DBACKBUFFER_TYPE_RIGHT        = 2,
    D3DBACKBUFFER_TYPE_FORCE_DWORD  = 0x7fffffff,
} D3DBACKBUFFER_TYPE;

/* D3DSTATEBLOCKTYPE */
typedef enum _D3DSTATEBLOCKTYPE {
    D3DSBT_ALL          = 1,
    D3DSBT_PIXELSTATE   = 2,
    D3DSBT_VERTEXSTATE  = 3,
    D3DSBT_FORCE_DWORD  = 0xffffffff,
} D3DSTATEBLOCKTYPE;

/* D3DVERTEXBLEND (legacy alias) */
#define D3DVOP_TRANSFORM    0x00000001L
#define D3DVOP_LIGHT        0x00000004L
#define D3DVOP_CLIP         0x00000008L
#define D3DVOP_EXTENTS      0x00000020L

/* D3DDECLTYPE */
typedef enum _D3DDECLTYPE {
    D3DDECLTYPE_FLOAT1      = 0,
    D3DDECLTYPE_FLOAT2      = 1,
    D3DDECLTYPE_FLOAT3      = 2,
    D3DDECLTYPE_FLOAT4      = 3,
    D3DDECLTYPE_D3DCOLOR    = 4,
    D3DDECLTYPE_UBYTE4      = 5,
    D3DDECLTYPE_SHORT2      = 6,
    D3DDECLTYPE_SHORT4      = 7,
    D3DDECLTYPE_UBYTE4N     = 8,
    D3DDECLTYPE_SHORT2N     = 9,
    D3DDECLTYPE_SHORT4N     = 10,
    D3DDECLTYPE_USHORT2N    = 11,
    D3DDECLTYPE_USHORT4N    = 12,
    D3DDECLTYPE_UDEC3       = 13,
    D3DDECLTYPE_DEC3N       = 14,
    D3DDECLTYPE_FLOAT16_2   = 15,
    D3DDECLTYPE_FLOAT16_4   = 16,
    D3DDECLTYPE_UNUSED      = 17,
    D3DDECLTYPE_FORCE_DWORD = 0x7fffffff,
} D3DDECLTYPE;

/* D3DDECLMETHOD */
typedef enum _D3DDECLMETHOD {
    D3DDECLMETHOD_DEFAULT           = 0,
    D3DDECLMETHOD_PARTIALU          = 1,
    D3DDECLMETHOD_PARTIALV          = 2,
    D3DDECLMETHOD_CROSSUV           = 3,
    D3DDECLMETHOD_UV                = 4,
    D3DDECLMETHOD_LOOKUP            = 5,
    D3DDECLMETHOD_LOOKUPPRESAMPLED  = 6,
    D3DDECLMETHOD_FORCE_DWORD       = 0x7fffffff,
} D3DDECLMETHOD;

/* D3DDECLUSAGE */
typedef enum _D3DDECLUSAGE {
    D3DDECLUSAGE_POSITION       = 0,
    D3DDECLUSAGE_BLENDWEIGHT    = 1,
    D3DDECLUSAGE_BLENDINDICES   = 2,
    D3DDECLUSAGE_NORMAL         = 3,
    D3DDECLUSAGE_PSIZE          = 4,
    D3DDECLUSAGE_TEXCOORD       = 5,
    D3DDECLUSAGE_TANGENT        = 6,
    D3DDECLUSAGE_BINORMAL       = 7,
    D3DDECLUSAGE_TESSFACTOR     = 8,
    D3DDECLUSAGE_POSITIONT      = 9,
    D3DDECLUSAGE_COLOR          = 10,
    D3DDECLUSAGE_FOG            = 11,
    D3DDECLUSAGE_DEPTH          = 12,
    D3DDECLUSAGE_SAMPLE         = 13,
    D3DDECLUSAGE_FORCE_DWORD    = 0x7fffffff,
} D3DDECLUSAGE;

/* D3DSAMPLER_TEXTURE_TYPE */
typedef enum _D3DSAMPLER_TEXTURE_TYPE {
    D3DSTT_UNKNOWN  = 0 << 4,
    D3DSTT_2D       = 2 << 4,
    D3DSTT_CUBE     = 3 << 4,
    D3DSTT_VOLUME   = 4 << 4,
    D3DSTT_FORCE_DWORD = 0x7fffffff,
} D3DSAMPLER_TEXTURE_TYPE;

/* D3DCOLORWRITEENABLE */
#define D3DCOLORWRITEENABLE_RED     (1 << 0)
#define D3DCOLORWRITEENABLE_GREEN   (1 << 1)
#define D3DCOLORWRITEENABLE_BLUE    (1 << 2)
#define D3DCOLORWRITEENABLE_ALPHA   (1 << 3)

/* D3DLOCKFLAGS */
#define D3DLOCK_READONLY        0x00000010L
#define D3DLOCK_DISCARD         0x00002000L
#define D3DLOCK_NOOVERWRITE     0x00001000L
#define D3DLOCK_NOSYSLOCK       0x00000800L
#define D3DLOCK_DONOTWAIT       0x00004000L
#define D3DLOCK_NO_DIRTY_UPDATE 0x00008000L

/* D3DUSAGE flags */
#define D3DUSAGE_RENDERTARGET       0x00000001L
#define D3DUSAGE_DEPTHSTENCIL       0x00000002L
#define D3DUSAGE_WRITEONLY          0x00000008L
#define D3DUSAGE_SOFTWAREPROCESSING 0x00000010L
#define D3DUSAGE_DONOTCLIP          0x00000020L
#define D3DUSAGE_POINTS             0x00000040L
#define D3DUSAGE_RTPATCHES          0x00000080L
#define D3DUSAGE_NPATCHES           0x00000100L
#define D3DUSAGE_DYNAMIC            0x00000200L
#define D3DUSAGE_AUTOGENMIPMAP      0x00000400L
#define D3DUSAGE_RESTRICTED_CONTENT 0x00000800L
#define D3DUSAGE_RESTRICT_SHARED_RESOURCE 0x00002000L
#define D3DUSAGE_RESTRICT_SHARED_RESOURCE_DRIVER 0x00004000L
#define D3DUSAGE_NONSECURE          0x00800000L
#define D3DUSAGE_TEXTAPI            0x10000000L
#define D3DUSAGE_QUERY_LEGACYBUMPMAP        0x00008000L
#define D3DUSAGE_QUERY_SRGBREAD             0x00010000L
#define D3DUSAGE_QUERY_FILTER               0x00020000L
#define D3DUSAGE_QUERY_SRGBWRITE            0x00040000L
#define D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING 0x00080000L
#define D3DUSAGE_QUERY_VERTEXTEXTURE        0x00100000L
#define D3DUSAGE_QUERY_WRAPANDMIP           0x00200000L

/* D3DCREATE flags */
#define D3DCREATE_FPU_PRESERVE                  0x00000002L
#define D3DCREATE_MULTITHREADED                 0x00000004L
#define D3DCREATE_PUREDEVICE                    0x00000010L
#define D3DCREATE_SOFTWARE_VERTEXPROCESSING     0x00000020L
#define D3DCREATE_HARDWARE_VERTEXPROCESSING     0x00000040L
#define D3DCREATE_MIXED_VERTEXPROCESSING        0x00000080L
#define D3DCREATE_DISABLE_DRIVER_MANAGEMENT     0x00000100L
#define D3DCREATE_ADAPTERGROUP_DEVICE           0x00000200L
#define D3DCREATE_NOWINDOWCHANGES               0x00000800L
#define D3DCREATE_SCREENSAVER                   0x10000000L
#define D3DCREATE_DISABLE_PRINTSCREEN           0x00008000L
#define D3DCREATE_DISABLE_PSGP_THREADING        0x00002000L

/* D3DPRESENT flags */
#define D3DPRESENT_RATE_DEFAULT                 0x00000000
#define D3DPRESENT_INTERVAL_DEFAULT             0x00000000
#define D3DPRESENT_INTERVAL_ONE                 0x00000001
#define D3DPRESENT_INTERVAL_TWO                 0x00000002
#define D3DPRESENT_INTERVAL_THREE               0x00000004
#define D3DPRESENT_INTERVAL_FOUR                0x00000008
#define D3DPRESENT_INTERVAL_IMMEDIATE           0x80000000

/* D3DTA (texture argument) */
#define D3DTA_SELECTMASK        0x0000000f
#define D3DTA_DIFFUSE           0x00000000
#define D3DTA_CURRENT           0x00000001
#define D3DTA_TEXTURE           0x00000002
#define D3DTA_TFACTOR           0x00000003
#define D3DTA_SPECULAR          0x00000004
#define D3DTA_TEMP              0x00000005
#define D3DTA_CONSTANT          0x00000006
#define D3DTA_COMPLEMENT        0x00000010
#define D3DTA_ALPHAREPLICATE    0x00000020

/* D3DWRAP flags */
#define D3DWRAP_U   0x00000001L
#define D3DWRAP_V   0x00000002L
#define D3DWRAP_W   0x00000004L
#define D3DWRAP_UV  (D3DWRAP_U | D3DWRAP_V)
#define D3DWRAP_UVW (D3DWRAP_U | D3DWRAP_V | D3DWRAP_W)

/* FVF flags */
#define D3DFVF_RESERVED0        0x001
#define D3DFVF_POSITION_MASK    0x400E
#define D3DFVF_XYZ             0x002
#define D3DFVF_XYZRHW           0x004
#define D3DFVF_XYZB1           0x006
#define D3DFVF_XYZB2           0x008
#define D3DFVF_XYZB3           0x00a
#define D3DFVF_XYZB4           0x00c
#define D3DFVF_XYZB5           0x00e
#define D3DFVF_XYZW            0x4002
#define D3DFVF_NORMAL           0x010
#define D3DFVF_PSIZE            0x020
#define D3DFVF_DIFFUSE          0x040
#define D3DFVF_SPECULAR         0x080
#define D3DFVF_TEX0             0x000
#define D3DFVF_TEX1             0x100
#define D3DFVF_TEX2             0x200
#define D3DFVF_TEX3             0x300
#define D3DFVF_TEX4             0x400
#define D3DFVF_TEX5             0x500
#define D3DFVF_TEX6             0x600
#define D3DFVF_TEX7             0x700
#define D3DFVF_TEX8             0x800
#define D3DFVF_TEXCOUNT_MASK    0xf00
#define D3DFVF_TEXCOUNT_SHIFT   8
#define D3DFVF_LASTBETA_UBYTE4  0x1000
#define D3DFVF_LASTBETA_D3DCOLOR 0x8000
#define D3DFVF_RESERVED2        0x6000

/* D3DSTREAMSOURCE flags */
#define D3DSTREAMSOURCE_INDEXEDDATA     (1 << 30)
#define D3DSTREAMSOURCE_INSTANCEDATA    (2 << 30)

/* Sampler remapping */
#define D3DVERTEXTEXTURESAMPLER0    (D3DDMAPSAMPLER + 1)
#define D3DVERTEXTEXTURESAMPLER1    (D3DDMAPSAMPLER + 2)
#define D3DVERTEXTEXTURESAMPLER2    (D3DDMAPSAMPLER + 3)
#define D3DVERTEXTEXTURESAMPLER3    (D3DDMAPSAMPLER + 4)
#define D3DDMAPSAMPLER              256
#define D3DVERTEXTEXTURESAMPLER     0x100

/* Maximum values */
#define D3D9_MAX_SIMULTANEOUS_RENDERTARGETS 4
#define D3DMAXUSERCLIPPLANES                32
#define D3DCLIPPLANE0                       (1 << 0)
#define D3DCLIPPLANE1                       (1 << 1)
#define D3DCLIPPLANE2                       (1 << 2)
#define D3DCLIPPLANE3                       (1 << 3)
#define D3DCLIPPLANE4                       (1 << 4)
#define D3DCLIPPLANE5                       (1 << 5)

/* =========================================================================
 * D3DXVECTOR / D3DXMATRIX aliases (commonly used alongside d3d9types)
 * ========================================================================= */
typedef D3DVECTOR D3DXVECTOR3;

typedef struct _D3DXVECTOR2 { float x, y; } D3DXVECTOR2;
typedef struct _D3DXVECTOR4 { float x, y, z, w; } D3DXVECTOR4;
typedef struct _D3DXQUATERNION { float x, y, z, w; } D3DXQUATERNION;
typedef struct _D3DXPLANE { float a, b, c, d; } D3DXPLANE;
typedef struct _D3DXCOLOR { float r, g, b, a; } D3DXCOLOR;
typedef D3DMATRIX D3DXMATRIX;

struct IDirect3DStateBlock9 {
    virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj) {  }
    virtual ULONG   STDMETHODCALLTYPE AddRef()  { return 0; }
    virtual ULONG   STDMETHODCALLTYPE Release() { return 0; }
    virtual HRESULT STDMETHODCALLTYPE GetDevice(void** ppDevice) {  }
    virtual HRESULT STDMETHODCALLTYPE Capture()  { }
    virtual HRESULT STDMETHODCALLTYPE Apply()    { }
};

#endif /* __D3D9TYPES_H__ */