#pragma once
#ifndef __D3D10_1_H__
#define __D3D10_1_H__

/*
 * d3d10_1.h - Linux stub header for compilation purposes only.
 * All functions are empty stubs and do not provide actual DirectX functionality.
 */

#include <stdint.h>
#include <stddef.h>

/* =========================================================================
 * Basic Windows type compatibility
 * ========================================================================= */
#ifndef _WINDOWS_
typedef void*           HANDLE;
typedef void*           HDC;
typedef void*           HINSTANCE;
typedef void*           HMONITOR;
typedef unsigned char   BYTE;
typedef int             BOOL;
typedef int             INT;
typedef unsigned int    UINT;
typedef long            LONG;
typedef unsigned long   ULONG;
typedef long long       LONGLONG;
typedef unsigned long long ULONGLONG;
typedef float           FLOAT;
typedef size_t          SIZE_T;
typedef unsigned char   UCHAR;
typedef unsigned short  USHORT;
typedef signed char     INT8;
typedef short           INT16;
typedef int             INT32;
typedef long long       INT64;
typedef unsigned char   UINT8;
typedef unsigned short  UINT16;
typedef unsigned int    UINT32;
typedef unsigned long long UINT64;
typedef char            CHAR;
typedef wchar_t         WCHAR;
typedef const char*     LPCSTR;
typedef const wchar_t*  LPCWSTR;
typedef char*           LPSTR;
typedef wchar_t*        LPWSTR;
typedef const void*     LPCVOID;
typedef unsigned int    UINT_PTR;
typedef size_t          ULONG_PTR;
typedef RECT*           LPRECT;
typedef struct { long cx, cy; } SIZE_STRUCT;
typedef uint64_t        LUID_TYPE;

#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

#ifndef NULL
#define NULL  0
#endif
#endif /* _WINDOWS_ */

/* =========================================================================
 * GUID / IID / CLSID
 * ========================================================================= */
#ifndef GUID_DEFINED
#define GUID_DEFINED

#endif

typedef GUID IID;
typedef GUID CLSID;
typedef const IID* REFIID;

#ifndef DEFINE_GUID
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern const GUID name
#endif

#ifndef __IID_DEFINED__
#define __IID_DEFINED__
#endif

/* =========================================================================
 * HRESULT codes
 * ========================================================================= */
#define S_OK                    ((HRESULT)0x00000000L)
#define S_FALSE                 ((HRESULT)0x00000001L)
#define E_NOTIMPL               ((HRESULT)0x80004001L)
#define E_NOINTERFACE           ((HRESULT)0x80004002L)
#define E_POINTER               ((HRESULT)0x80004003L)
#define E_ABORT                 ((HRESULT)0x80004004L)
#define E_FAIL                  ((HRESULT)0x80004005L)
#define E_UNEXPECTED            ((HRESULT)0x8000FFFFL)
#define E_ACCESSDENIED          ((HRESULT)0x80070005L)
#define E_HANDLE                ((HRESULT)0x80070006L)
#define E_OUTOFMEMORY           ((HRESULT)0x8007000EL)
#define E_INVALIDARG            ((HRESULT)0x80070057L)

#define DXGI_ERROR_NOT_FOUND    ((HRESULT)0x887A0002L)
#define DXGI_ERROR_MORE_DATA    ((HRESULT)0x887A0003L)
#define DXGI_ERROR_UNSUPPORTED  ((HRESULT)0x887A0004L)
#define DXGI_ERROR_DEVICE_REMOVED ((HRESULT)0x887A0005L)
#define DXGI_ERROR_DEVICE_HUNG  ((HRESULT)0x887A0006L)
#define DXGI_ERROR_DEVICE_RESET ((HRESULT)0x887A0007L)
#define DXGI_ERROR_WAS_STILL_DRAWING ((HRESULT)0x887A000AL)
#define DXGI_ERROR_INVALID_CALL ((HRESULT)0x887A0001L)

#define SUCCEEDED(hr)           (((HRESULT)(hr)) >= 0)
#define FAILED(hr)              (((HRESULT)(hr)) < 0)

/* =========================================================================
 * Calling convention / linkage macros
 * ========================================================================= */
#ifndef STDMETHODCALLTYPE
#define STDMETHODCALLTYPE
#endif
#ifndef STDMETHODVCALLTYPE
#define STDMETHODVCALLTYPE
#endif
#ifndef STDAPICALLTYPE
#define STDAPICALLTYPE
#endif
#ifndef WINAPI
#define WINAPI
#endif
#ifndef CALLBACK
#define CALLBACK
#endif
#ifndef DECLSPEC_UUID
#define DECLSPEC_UUID(x)
#endif
#ifndef DECLSPEC_NOVTABLE
#define DECLSPEC_NOVTABLE
#endif
#ifndef __declspec
#define __declspec(x)
#endif
#ifndef __cdecl
#define __cdecl
#endif

#ifndef STDMETHOD
#define STDMETHOD(method)        virtual HRESULT STDMETHODCALLTYPE method
#endif
#ifndef STDMETHOD_
#define STDMETHOD_(type, method) virtual type STDMETHODCALLTYPE method
#endif
#ifndef PURE
#define PURE = 0
#endif
#ifndef THIS_
#define THIS_
#endif
#ifndef THIS
#define THIS void
#endif

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif
#endif

/* =========================================================================
 * D3D10 Feature Level
 * ========================================================================= */
typedef enum D3D10_FEATURE_LEVEL1 {
    D3D10_FEATURE_LEVEL_10_0 = 0xa000,
    D3D10_FEATURE_LEVEL_10_1 = 0xa100,
    D3D10_FEATURE_LEVEL_9_1  = 0x9100,
    D3D10_FEATURE_LEVEL_9_2  = 0x9200,
    D3D10_FEATURE_LEVEL_9_3  = 0x9300,
} D3D10_FEATURE_LEVEL1;

/* =========================================================================
 * D3D10 Enumerations
 * ========================================================================= */
typedef enum D3D10_DRIVER_TYPE {
    D3D10_DRIVER_TYPE_HARDWARE  = 0,
    D3D10_DRIVER_TYPE_REFERENCE = 1,
    D3D10_DRIVER_TYPE_NULL      = 2,
    D3D10_DRIVER_TYPE_SOFTWARE  = 3,
    D3D10_DRIVER_TYPE_WARP      = 5,
} D3D10_DRIVER_TYPE;

typedef enum D3D10_CREATE_DEVICE_FLAG {
    D3D10_CREATE_DEVICE_SINGLETHREADED                  = 0x1,
    D3D10_CREATE_DEVICE_DEBUG                           = 0x2,
    D3D10_CREATE_DEVICE_SWITCH_TO_REF                   = 0x4,
    D3D10_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS = 0x8,
    D3D10_CREATE_DEVICE_ALLOW_NULL_FROM_MAP             = 0x10,
    D3D10_CREATE_DEVICE_BGRA_SUPPORT                    = 0x20,
    D3D10_CREATE_DEVICE_STRICT_VALIDATION               = 0x200,
} D3D10_CREATE_DEVICE_FLAG;

typedef enum D3D10_USAGE {
    D3D10_USAGE_DEFAULT   = 0,
    D3D10_USAGE_IMMUTABLE = 1,
    D3D10_USAGE_DYNAMIC   = 2,
    D3D10_USAGE_STAGING   = 3,
} D3D10_USAGE;

typedef enum D3D10_BIND_FLAG {
    D3D10_BIND_VERTEX_BUFFER    = 0x1,
    D3D10_BIND_INDEX_BUFFER     = 0x2,
    D3D10_BIND_CONSTANT_BUFFER  = 0x4,
    D3D10_BIND_SHADER_RESOURCE  = 0x8,
    D3D10_BIND_STREAM_OUTPUT    = 0x10,
    D3D10_BIND_RENDER_TARGET    = 0x20,
    D3D10_BIND_DEPTH_STENCIL    = 0x40,
} D3D10_BIND_FLAG;

typedef enum D3D10_CPU_ACCESS_FLAG {
    D3D10_CPU_ACCESS_WRITE = 0x10000,
    D3D10_CPU_ACCESS_READ  = 0x20000,
} D3D10_CPU_ACCESS_FLAG;

typedef enum D3D10_RESOURCE_MISC_FLAG {
    D3D10_RESOURCE_MISC_GENERATE_MIPS      = 0x1,
    D3D10_RESOURCE_MISC_SHARED             = 0x2,
    D3D10_RESOURCE_MISC_TEXTURECUBE        = 0x4,
    D3D10_RESOURCE_MISC_SHARED_KEYEDMUTEX  = 0x10,
    D3D10_RESOURCE_MISC_GDI_COMPATIBLE     = 0x20,
} D3D10_RESOURCE_MISC_FLAG;

typedef enum D3D10_RESOURCE_DIMENSION {
    D3D10_RESOURCE_DIMENSION_UNKNOWN   = 0,
    D3D10_RESOURCE_DIMENSION_BUFFER    = 1,
    D3D10_RESOURCE_DIMENSION_TEXTURE1D = 2,
    D3D10_RESOURCE_DIMENSION_TEXTURE2D = 3,
    D3D10_RESOURCE_DIMENSION_TEXTURE3D = 4,
} D3D10_RESOURCE_DIMENSION;

typedef enum D3D10_MAP {
    D3D10_MAP_READ              = 1,
    D3D10_MAP_WRITE             = 2,
    D3D10_MAP_READ_WRITE        = 3,
    D3D10_MAP_WRITE_DISCARD     = 4,
    D3D10_MAP_WRITE_NO_OVERWRITE = 5,
} D3D10_MAP;

typedef enum D3D10_MAP_FLAG {
    D3D10_MAP_FLAG_DO_NOT_WAIT = 0x100000,
} D3D10_MAP_FLAG;

typedef enum D3D10_PRIMITIVE_TOPOLOGY {
    D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED         = 0,
    D3D10_PRIMITIVE_TOPOLOGY_POINTLIST         = 1,
    D3D10_PRIMITIVE_TOPOLOGY_LINELIST          = 2,
    D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP         = 3,
    D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST      = 4,
    D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP     = 5,
    D3D10_PRIMITIVE_TOPOLOGY_LINELIST_ADJ      = 10,
    D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ     = 11,
    D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ  = 12,
    D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = 13,
} D3D10_PRIMITIVE_TOPOLOGY;

typedef enum D3D10_FILL_MODE {
    D3D10_FILL_WIREFRAME = 2,
    D3D10_FILL_SOLID     = 3,
} D3D10_FILL_MODE;

typedef enum D3D10_CULL_MODE {
    D3D10_CULL_NONE  = 1,
    D3D10_CULL_FRONT = 2,
    D3D10_CULL_BACK  = 3,
} D3D10_CULL_MODE;

typedef enum D3D10_DEPTH_WRITE_MASK {
    D3D10_DEPTH_WRITE_MASK_ZERO = 0,
    D3D10_DEPTH_WRITE_MASK_ALL  = 1,
} D3D10_DEPTH_WRITE_MASK;

typedef enum D3D10_COMPARISON_FUNC {
    D3D10_COMPARISON_NEVER         = 1,
    D3D10_COMPARISON_LESS          = 2,
    D3D10_COMPARISON_EQUAL         = 3,
    D3D10_COMPARISON_LESS_EQUAL    = 4,
    D3D10_COMPARISON_GREATER       = 5,
    D3D10_COMPARISON_NOT_EQUAL     = 6,
    D3D10_COMPARISON_GREATER_EQUAL = 7,
    D3D10_COMPARISON_ALWAYS        = 8,
} D3D10_COMPARISON_FUNC;

typedef enum D3D10_STENCIL_OP {
    D3D10_STENCIL_OP_KEEP     = 1,
    D3D10_STENCIL_OP_ZERO     = 2,
    D3D10_STENCIL_OP_REPLACE  = 3,
    D3D10_STENCIL_OP_INCR_SAT = 4,
    D3D10_STENCIL_OP_DECR_SAT = 5,
    D3D10_STENCIL_OP_INVERT   = 6,
    D3D10_STENCIL_OP_INCR     = 7,
    D3D10_STENCIL_OP_DECR     = 8,
} D3D10_STENCIL_OP;

typedef enum D3D10_BLEND {
    D3D10_BLEND_ZERO             = 1,
    D3D10_BLEND_ONE              = 2,
    D3D10_BLEND_SRC_COLOR        = 3,
    D3D10_BLEND_INV_SRC_COLOR    = 4,
    D3D10_BLEND_SRC_ALPHA        = 5,
    D3D10_BLEND_INV_SRC_ALPHA    = 6,
    D3D10_BLEND_DEST_ALPHA       = 7,
    D3D10_BLEND_INV_DEST_ALPHA   = 8,
    D3D10_BLEND_DEST_COLOR       = 9,
    D3D10_BLEND_INV_DEST_COLOR   = 10,
    D3D10_BLEND_SRC_ALPHA_SAT    = 11,
    D3D10_BLEND_BLEND_FACTOR     = 14,
    D3D10_BLEND_INV_BLEND_FACTOR = 15,
    D3D10_BLEND_SRC1_COLOR       = 16,
    D3D10_BLEND_INV_SRC1_COLOR   = 17,
    D3D10_BLEND_SRC1_ALPHA       = 18,
    D3D10_BLEND_INV_SRC1_ALPHA   = 19,
} D3D10_BLEND;

typedef enum D3D10_BLEND_OP {
    D3D10_BLEND_OP_ADD          = 1,
    D3D10_BLEND_OP_SUBTRACT     = 2,
    D3D10_BLEND_OP_REV_SUBTRACT = 3,
    D3D10_BLEND_OP_MIN          = 4,
    D3D10_BLEND_OP_MAX          = 5,
} D3D10_BLEND_OP;

typedef enum D3D10_COLOR_WRITE_ENABLE {
    D3D10_COLOR_WRITE_ENABLE_RED   = 1,
    D3D10_COLOR_WRITE_ENABLE_GREEN = 2,
    D3D10_COLOR_WRITE_ENABLE_BLUE  = 4,
    D3D10_COLOR_WRITE_ENABLE_ALPHA = 8,
    D3D10_COLOR_WRITE_ENABLE_ALL   = (D3D10_COLOR_WRITE_ENABLE_RED | D3D10_COLOR_WRITE_ENABLE_GREEN |
                                      D3D10_COLOR_WRITE_ENABLE_BLUE | D3D10_COLOR_WRITE_ENABLE_ALPHA),
} D3D10_COLOR_WRITE_ENABLE;

typedef enum D3D10_FILTER {
    D3D10_FILTER_MIN_MAG_MIP_POINT                          = 0,
    D3D10_FILTER_MIN_MAG_POINT_MIP_LINEAR                   = 0x1,
    D3D10_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT             = 0x4,
    D3D10_FILTER_MIN_POINT_MAG_MIP_LINEAR                   = 0x5,
    D3D10_FILTER_MIN_LINEAR_MAG_MIP_POINT                   = 0x10,
    D3D10_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR            = 0x11,
    D3D10_FILTER_MIN_MAG_LINEAR_MIP_POINT                   = 0x14,
    D3D10_FILTER_MIN_MAG_MIP_LINEAR                         = 0x15,
    D3D10_FILTER_ANISOTROPIC                                = 0x55,
    D3D10_FILTER_COMPARISON_MIN_MAG_MIP_POINT               = 0x80,
    D3D10_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR              = 0x95,
    D3D10_FILTER_COMPARISON_ANISOTROPIC                     = 0xd5,
    D3D10_FILTER_TEXT_1BIT                                  = 0x80000000,
} D3D10_FILTER;

typedef enum D3D10_TEXTURE_ADDRESS_MODE {
    D3D10_TEXTURE_ADDRESS_WRAP        = 1,
    D3D10_TEXTURE_ADDRESS_MIRROR      = 2,
    D3D10_TEXTURE_ADDRESS_CLAMP       = 3,
    D3D10_TEXTURE_ADDRESS_BORDER      = 4,
    D3D10_TEXTURE_ADDRESS_MIRROR_ONCE = 5,
} D3D10_TEXTURE_ADDRESS_MODE;

typedef enum D3D10_INPUT_CLASSIFICATION {
    D3D10_INPUT_PER_VERTEX_DATA   = 0,
    D3D10_INPUT_PER_INSTANCE_DATA = 1,
} D3D10_INPUT_CLASSIFICATION;

typedef enum D3D10_QUERY {
    D3D10_QUERY_EVENT                      = 0,
    D3D10_QUERY_OCCLUSION                  = 1,
    D3D10_QUERY_TIMESTAMP                  = 2,
    D3D10_QUERY_TIMESTAMP_DISJOINT         = 3,
    D3D10_QUERY_PIPELINE_STATISTICS        = 4,
    D3D10_QUERY_OCCLUSION_PREDICATE        = 5,
    D3D10_QUERY_SO_STATISTICS              = 6,
    D3D10_QUERY_SO_OVERFLOW_PREDICATE      = 7,
} D3D10_QUERY;

typedef enum D3D10_COUNTER {
    D3D10_COUNTER_GPU_IDLE                          = 0,
    D3D10_COUNTER_VERTEX_PROCESSING                 = 1,
    D3D10_COUNTER_GEOMETRY_PROCESSING               = 2,
    D3D10_COUNTER_PIXEL_PROCESSING                  = 3,
    D3D10_COUNTER_OTHER_GPU_PROCESSING              = 4,
    D3D10_COUNTER_HOST_ADAPTER_BANDWIDTH_UTILIZATION = 5,
    D3D10_COUNTER_LOCAL_VIDMEM_BANDWIDTH_UTILIZATION = 6,
    D3D10_COUNTER_VERTEX_THROUGHPUT_UTILIZATION      = 7,
    D3D10_COUNTER_TRIANGLE_SETUP_THROUGHPUT_UTILIZATION = 8,
    D3D10_COUNTER_FILLRATE_THROUGHPUT_UTILIZATION   = 9,
    D3D10_COUNTER_VS_MEMORY_LIMITED                 = 10,
    D3D10_COUNTER_VS_COMPUTATION_LIMITED            = 11,
    D3D10_COUNTER_GS_MEMORY_LIMITED                 = 12,
    D3D10_COUNTER_GS_COMPUTATION_LIMITED            = 13,
    D3D10_COUNTER_PS_MEMORY_LIMITED                 = 14,
    D3D10_COUNTER_PS_COMPUTATION_LIMITED            = 15,
    D3D10_COUNTER_POST_TRANSFORM_CACHE_HIT_RATE     = 16,
    D3D10_COUNTER_TEXTURE_CACHE_HIT_RATE            = 17,
    D3D10_COUNTER_DEVICE_DEPENDENT_0                = 0x40000000,
} D3D10_COUNTER;

typedef enum D3D10_COUNTER_TYPE {
    D3D10_COUNTER_TYPE_FLOAT32  = 0,
    D3D10_COUNTER_TYPE_UINT16   = 1,
    D3D10_COUNTER_TYPE_UINT32   = 2,
    D3D10_COUNTER_TYPE_UINT64   = 3,
} D3D10_COUNTER_TYPE;

typedef enum D3D10_RAISE_FLAG {
    D3D10_RAISE_FLAG_DRIVER_INTERNAL_ERROR = 0x1,
} D3D10_RAISE_FLAG;

typedef enum D3D10_CLEAR_FLAG {
    D3D10_CLEAR_DEPTH   = 0x1,
    D3D10_CLEAR_STENCIL = 0x2,
} D3D10_CLEAR_FLAG;

typedef enum D3D10_TEXTURECUBE_FACE {
    D3D10_TEXTURECUBE_FACE_POSITIVE_X = 0,
    D3D10_TEXTURECUBE_FACE_NEGATIVE_X = 1,
    D3D10_TEXTURECUBE_FACE_POSITIVE_Y = 2,
    D3D10_TEXTURECUBE_FACE_NEGATIVE_Y = 3,
    D3D10_TEXTURECUBE_FACE_POSITIVE_Z = 4,
    D3D10_TEXTURECUBE_FACE_NEGATIVE_Z = 5,
} D3D10_TEXTURECUBE_FACE;

typedef enum D3D10_SRV_DIMENSION1 {
    D3D10_1_SRV_DIMENSION_UNKNOWN          = 0,
    D3D10_1_SRV_DIMENSION_BUFFER           = 1,
    D3D10_1_SRV_DIMENSION_TEXTURE1D        = 2,
    D3D10_1_SRV_DIMENSION_TEXTURE1DARRAY   = 3,
    D3D10_1_SRV_DIMENSION_TEXTURE2D        = 4,
    D3D10_1_SRV_DIMENSION_TEXTURE2DARRAY   = 5,
    D3D10_1_SRV_DIMENSION_TEXTURE2DMS      = 6,
    D3D10_1_SRV_DIMENSION_TEXTURE2DMSARRAY = 7,
    D3D10_1_SRV_DIMENSION_TEXTURE3D        = 8,
    D3D10_1_SRV_DIMENSION_TEXTURECUBE      = 9,
    D3D10_1_SRV_DIMENSION_TEXTURECUBEARRAY = 10,
} D3D10_SRV_DIMENSION1;

/* =========================================================================
 * DXGI Format (subset)
 * ========================================================================= */
typedef enum DXGI_FORMAT {
    DXGI_FORMAT_UNKNOWN                    = 0,
    DXGI_FORMAT_R32G32B32A32_TYPELESS      = 1,
    DXGI_FORMAT_R32G32B32A32_FLOAT         = 2,
    DXGI_FORMAT_R32G32B32A32_UINT          = 3,
    DXGI_FORMAT_R32G32B32A32_SINT          = 4,
    DXGI_FORMAT_R32G32B32_TYPELESS         = 5,
    DXGI_FORMAT_R32G32B32_FLOAT            = 6,
    DXGI_FORMAT_R32G32B32_UINT             = 7,
    DXGI_FORMAT_R32G32B32_SINT             = 8,
    DXGI_FORMAT_R16G16B16A16_TYPELESS      = 9,
    DXGI_FORMAT_R16G16B16A16_FLOAT         = 10,
    DXGI_FORMAT_R16G16B16A16_UNORM         = 11,
    DXGI_FORMAT_R16G16B16A16_UINT          = 12,
    DXGI_FORMAT_R16G16B16A16_SNORM         = 13,
    DXGI_FORMAT_R16G16B16A16_SINT          = 14,
    DXGI_FORMAT_R32G32_TYPELESS            = 15,
    DXGI_FORMAT_R32G32_FLOAT               = 16,
    DXGI_FORMAT_R32G32_UINT                = 17,
    DXGI_FORMAT_R32G32_SINT                = 18,
    DXGI_FORMAT_R8G8B8A8_TYPELESS          = 27,
    DXGI_FORMAT_R8G8B8A8_UNORM             = 28,
    DXGI_FORMAT_R8G8B8A8_UNORM_SRGB        = 29,
    DXGI_FORMAT_R8G8B8A8_UINT              = 30,
    DXGI_FORMAT_R8G8B8A8_SNORM             = 31,
    DXGI_FORMAT_R8G8B8A8_SINT              = 32,
    DXGI_FORMAT_R16G16_TYPELESS            = 33,
    DXGI_FORMAT_R16G16_FLOAT               = 34,
    DXGI_FORMAT_R16G16_UNORM               = 35,
    DXGI_FORMAT_R32_TYPELESS               = 39,
    DXGI_FORMAT_D32_FLOAT                  = 40,
    DXGI_FORMAT_R32_FLOAT                  = 41,
    DXGI_FORMAT_R32_UINT                   = 42,
    DXGI_FORMAT_R32_SINT                   = 43,
    DXGI_FORMAT_R16_TYPELESS               = 54,
    DXGI_FORMAT_R16_FLOAT                  = 55,
    DXGI_FORMAT_D16_UNORM                  = 56,
    DXGI_FORMAT_R16_UNORM                  = 57,
    DXGI_FORMAT_R16_UINT                   = 58,
    DXGI_FORMAT_R16_SNORM                  = 59,
    DXGI_FORMAT_R16_SINT                   = 60,
    DXGI_FORMAT_R8_TYPELESS                = 61,
    DXGI_FORMAT_R8_UNORM                   = 62,
    DXGI_FORMAT_R8_UINT                    = 63,
    DXGI_FORMAT_R8_SNORM                   = 64,
    DXGI_FORMAT_R8_SINT                    = 65,
    DXGI_FORMAT_B8G8R8A8_UNORM             = 87,
    DXGI_FORMAT_B8G8R8X8_UNORM             = 88,
    DXGI_FORMAT_B8G8R8A8_TYPELESS          = 90,
    DXGI_FORMAT_B8G8R8A8_UNORM_SRGB        = 91,
    DXGI_FORMAT_B8G8R8X8_TYPELESS          = 92,
    DXGI_FORMAT_B8G8R8X8_UNORM_SRGB        = 93,
    DXGI_FORMAT_FORCE_UINT                 = 0xffffffff,
} DXGI_FORMAT;

typedef enum DXGI_SAMPLE_DESC_DUMMY { _DXGI_SAMPLE_DUMMY = 0 } DXGI_SAMPLE_DESC_DUMMY;

/* =========================================================================
 * Structures
 * ========================================================================= */
typedef struct DXGI_SAMPLE_DESC {
    UINT Count;
    UINT Quality;
} DXGI_SAMPLE_DESC;

typedef struct DXGI_RATIONAL {
    UINT Numerator;
    UINT Denominator;
} DXGI_RATIONAL;

typedef struct D3D10_BUFFER_DESC {
    UINT      ByteWidth;
    D3D10_USAGE Usage;
    UINT      BindFlags;
    UINT      CPUAccessFlags;
    UINT      MiscFlags;
} D3D10_BUFFER_DESC;

typedef struct D3D10_TEXTURE1D_DESC {
    UINT             Width;
    UINT             MipLevels;
    UINT             ArraySize;
    DXGI_FORMAT      Format;
    D3D10_USAGE      Usage;
    UINT             BindFlags;
    UINT             CPUAccessFlags;
    UINT             MiscFlags;
} D3D10_TEXTURE1D_DESC;

typedef struct D3D10_TEXTURE2D_DESC {
    UINT             Width;
    UINT             Height;
    UINT             MipLevels;
    UINT             ArraySize;
    DXGI_FORMAT      Format;
    DXGI_SAMPLE_DESC SampleDesc;
    D3D10_USAGE      Usage;
    UINT             BindFlags;
    UINT             CPUAccessFlags;
    UINT             MiscFlags;
} D3D10_TEXTURE2D_DESC;

typedef struct D3D10_TEXTURE3D_DESC {
    UINT             Width;
    UINT             Height;
    UINT             Depth;
    UINT             MipLevels;
    DXGI_FORMAT      Format;
    D3D10_USAGE      Usage;
    UINT             BindFlags;
    UINT             CPUAccessFlags;
    UINT             MiscFlags;
} D3D10_TEXTURE3D_DESC;

typedef struct D3D10_SUBRESOURCE_DATA {
    const void* pSysMem;
    UINT        SysMemPitch;
    UINT        SysMemSlicePitch;
} D3D10_SUBRESOURCE_DATA;

typedef struct D3D10_MAPPED_TEXTURE2D {
    void* pData;
    UINT  RowPitch;
} D3D10_MAPPED_TEXTURE2D;

typedef struct D3D10_MAPPED_TEXTURE3D {
    void* pData;
    UINT  RowPitch;
    UINT  DepthPitch;
} D3D10_MAPPED_TEXTURE3D;

typedef struct D3D10_BOX {
    UINT left;
    UINT top;
    UINT front;
    UINT right;
    UINT bottom;
    UINT back;
} D3D10_BOX;

typedef struct D3D10_VIEWPORT {
    INT   TopLeftX;
    INT   TopLeftY;
    UINT  Width;
    UINT  Height;
    FLOAT MinDepth;
    FLOAT MaxDepth;
} D3D10_VIEWPORT;

typedef struct D3D10_RECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} D3D10_RECT;

typedef struct D3D10_INPUT_ELEMENT_DESC {
    LPCSTR                     SemanticName;
    UINT                       SemanticIndex;
    DXGI_FORMAT                Format;
    UINT                       InputSlot;
    UINT                       AlignedByteOffset;
    D3D10_INPUT_CLASSIFICATION InputSlotClass;
    UINT                       InstanceDataStepRate;
} D3D10_INPUT_ELEMENT_DESC;

typedef struct D3D10_SO_DECLARATION_ENTRY {
    LPCSTR SemanticName;
    UINT   SemanticIndex;
    BYTE   StartComponent;
    BYTE   ComponentCount;
    BYTE   OutputSlot;
} D3D10_SO_DECLARATION_ENTRY;

typedef struct D3D10_RASTERIZER_DESC {
    D3D10_FILL_MODE FillMode;
    D3D10_CULL_MODE CullMode;
    BOOL            FrontCounterClockwise;
    INT             DepthBias;
    FLOAT           DepthBiasClamp;
    FLOAT           SlopeScaledDepthBias;
    BOOL            DepthClipEnable;
    BOOL            ScissorEnable;
    BOOL            MultisampleEnable;
    BOOL            AntialiasedLineEnable;
} D3D10_RASTERIZER_DESC;

typedef struct D3D10_DEPTH_STENCILOP_DESC {
    D3D10_STENCIL_OP    StencilFailOp;
    D3D10_STENCIL_OP    StencilDepthFailOp;
    D3D10_STENCIL_OP    StencilPassOp;
    D3D10_COMPARISON_FUNC StencilFunc;
} D3D10_DEPTH_STENCILOP_DESC;

typedef struct D3D10_DEPTH_STENCIL_DESC {
    BOOL                      DepthEnable;
    D3D10_DEPTH_WRITE_MASK    DepthWriteMask;
    D3D10_COMPARISON_FUNC     DepthFunc;
    BOOL                      StencilEnable;
    UINT8                     StencilReadMask;
    UINT8                     StencilWriteMask;
    D3D10_DEPTH_STENCILOP_DESC FrontFace;
    D3D10_DEPTH_STENCILOP_DESC BackFace;
} D3D10_DEPTH_STENCIL_DESC;

typedef struct D3D10_RENDER_TARGET_BLEND_DESC1 {
    BOOL           BlendEnable;
    D3D10_BLEND    SrcBlend;
    D3D10_BLEND    DestBlend;
    D3D10_BLEND_OP BlendOp;
    D3D10_BLEND    SrcBlendAlpha;
    D3D10_BLEND    DestBlendAlpha;
    D3D10_BLEND_OP BlendOpAlpha;
    UINT8          RenderTargetWriteMask;
} D3D10_RENDER_TARGET_BLEND_DESC1;

typedef struct D3D10_BLEND_DESC1 {
    BOOL                          AlphaToCoverageEnable;
    BOOL                          IndependentBlendEnable;
    D3D10_RENDER_TARGET_BLEND_DESC1 RenderTarget[8];
} D3D10_BLEND_DESC1;

typedef struct D3D10_SAMPLER_DESC {
    D3D10_FILTER               Filter;
    D3D10_TEXTURE_ADDRESS_MODE AddressU;
    D3D10_TEXTURE_ADDRESS_MODE AddressV;
    D3D10_TEXTURE_ADDRESS_MODE AddressW;
    FLOAT                      MipLODBias;
    UINT                       MaxAnisotropy;
    D3D10_COMPARISON_FUNC      ComparisonFunc;
    FLOAT                      BorderColor[4];
    FLOAT                      MinLOD;
    FLOAT                      MaxLOD;
} D3D10_SAMPLER_DESC;

typedef struct D3D10_QUERY_DESC {
    D3D10_QUERY Query;
    UINT        MiscFlags;
} D3D10_QUERY_DESC;

typedef struct D3D10_COUNTER_DESC {
    D3D10_COUNTER Counter;
    UINT          MiscFlags;
} D3D10_COUNTER_DESC;

typedef struct D3D10_COUNTER_INFO {
    D3D10_COUNTER LastDeviceDependentCounter;
    UINT          NumSimultaneousCounters;
    UINT8         NumDetectableParallelUnits;
} D3D10_COUNTER_INFO;

typedef struct D3D10_QUERY_DATA_TIMESTAMP_DISJOINT {
    UINT64 Frequency;
    BOOL   Disjoint;
} D3D10_QUERY_DATA_TIMESTAMP_DISJOINT;

typedef struct D3D10_QUERY_DATA_PIPELINE_STATISTICS {
    UINT64 IAVertices;
    UINT64 IAPrimitives;
    UINT64 VSInvocations;
    UINT64 GSInvocations;
    UINT64 GSPrimitives;
    UINT64 CInvocations;
    UINT64 CPrimitives;
    UINT64 PSInvocations;
} D3D10_QUERY_DATA_PIPELINE_STATISTICS;

typedef struct D3D10_QUERY_DATA_SO_STATISTICS {
    UINT64 NumPrimitivesWritten;
    UINT64 PrimitivesStorageNeeded;
} D3D10_QUERY_DATA_SO_STATISTICS;

/* Shader resource view descriptions */
typedef struct D3D10_BUFFER_SRV {
    union { UINT FirstElement; UINT ElementOffset; };
    union { UINT NumElements;  UINT ElementWidth;  };
} D3D10_BUFFER_SRV;

typedef struct D3D10_TEX1D_SRV {
    UINT MostDetailedMip;
    UINT MipLevels;
} D3D10_TEX1D_SRV;

typedef struct D3D10_TEX1D_ARRAY_SRV {
    UINT MostDetailedMip;
    UINT MipLevels;
    UINT FirstArraySlice;
    UINT ArraySize;
} D3D10_TEX1D_ARRAY_SRV;

typedef struct D3D10_TEX2D_SRV {
    UINT MostDetailedMip;
    UINT MipLevels;
} D3D10_TEX2D_SRV;

typedef struct D3D10_TEX2D_ARRAY_SRV {
    UINT MostDetailedMip;
    UINT MipLevels;
    UINT FirstArraySlice;
    UINT ArraySize;
} D3D10_TEX2D_ARRAY_SRV;

typedef struct D3D10_TEX2DMS_SRV {
    UINT UnusedField_NothingToDefine;
} D3D10_TEX2DMS_SRV;

typedef struct D3D10_TEX2DMS_ARRAY_SRV {
    UINT FirstArraySlice;
    UINT ArraySize;
} D3D10_TEX2DMS_ARRAY_SRV;

typedef struct D3D10_TEX3D_SRV {
    UINT MostDetailedMip;
    UINT MipLevels;
} D3D10_TEX3D_SRV;

typedef struct D3D10_TEXCUBE_SRV {
    UINT MostDetailedMip;
    UINT MipLevels;
} D3D10_TEXCUBE_SRV;

typedef struct D3D10_TEXCUBE_ARRAY_SRV1 {
    UINT MostDetailedMip;
    UINT MipLevels;
    UINT First2DArrayFace;
    UINT NumCubes;
} D3D10_TEXCUBE_ARRAY_SRV1;

typedef struct D3D10_SHADER_RESOURCE_VIEW_DESC1 {
    DXGI_FORMAT           Format;
    D3D10_SRV_DIMENSION1  ViewDimension;
    union {
        D3D10_BUFFER_SRV          Buffer;
        D3D10_TEX1D_SRV           Texture1D;
        D3D10_TEX1D_ARRAY_SRV     Texture1DArray;
        D3D10_TEX2D_SRV           Texture2D;
        D3D10_TEX2D_ARRAY_SRV     Texture2DArray;
        D3D10_TEX2DMS_SRV         Texture2DMS;
        D3D10_TEX2DMS_ARRAY_SRV   Texture2DMSArray;
        D3D10_TEX3D_SRV           Texture3D;
        D3D10_TEXCUBE_SRV         TextureCube;
        D3D10_TEXCUBE_ARRAY_SRV1  TextureCubeArray;
    };
} D3D10_SHADER_RESOURCE_VIEW_DESC1;

/* Render target view descriptions */
typedef struct D3D10_BUFFER_RTV  { UINT FirstElement; UINT NumElements; } D3D10_BUFFER_RTV;
typedef struct D3D10_TEX1D_RTV   { UINT MipSlice; } D3D10_TEX1D_RTV;
typedef struct D3D10_TEX1D_ARRAY_RTV { UINT MipSlice; UINT FirstArraySlice; UINT ArraySize; } D3D10_TEX1D_ARRAY_RTV;
typedef struct D3D10_TEX2D_RTV   { UINT MipSlice; } D3D10_TEX2D_RTV;
typedef struct D3D10_TEX2D_ARRAY_RTV { UINT MipSlice; UINT FirstArraySlice; UINT ArraySize; } D3D10_TEX2D_ARRAY_RTV;
typedef struct D3D10_TEX2DMS_RTV { UINT UnusedField_NothingToDefine; } D3D10_TEX2DMS_RTV;
typedef struct D3D10_TEX2DMS_ARRAY_RTV { UINT FirstArraySlice; UINT ArraySize; } D3D10_TEX2DMS_ARRAY_RTV;
typedef struct D3D10_TEX3D_RTV   { UINT MipSlice; UINT FirstWSlice; UINT WSize; } D3D10_TEX3D_RTV;

typedef enum D3D10_RTV_DIMENSION {
    D3D10_RTV_DIMENSION_UNKNOWN          = 0,
    D3D10_RTV_DIMENSION_BUFFER           = 1,
    D3D10_RTV_DIMENSION_TEXTURE1D        = 2,
    D3D10_RTV_DIMENSION_TEXTURE1DARRAY   = 3,
    D3D10_RTV_DIMENSION_TEXTURE2D        = 4,
    D3D10_RTV_DIMENSION_TEXTURE2DARRAY   = 5,
    D3D10_RTV_DIMENSION_TEXTURE2DMS      = 6,
    D3D10_RTV_DIMENSION_TEXTURE2DMSARRAY = 7,
    D3D10_RTV_DIMENSION_TEXTURE3D        = 8,
} D3D10_RTV_DIMENSION;

typedef struct D3D10_RENDER_TARGET_VIEW_DESC {
    DXGI_FORMAT         Format;
    D3D10_RTV_DIMENSION ViewDimension;
    union {
        D3D10_BUFFER_RTV          Buffer;
        D3D10_TEX1D_RTV           Texture1D;
        D3D10_TEX1D_ARRAY_RTV     Texture1DArray;
        D3D10_TEX2D_RTV           Texture2D;
        D3D10_TEX2D_ARRAY_RTV     Texture2DArray;
        D3D10_TEX2DMS_RTV         Texture2DMS;
        D3D10_TEX2DMS_ARRAY_RTV   Texture2DMSArray;
        D3D10_TEX3D_RTV           Texture3D;
    };
} D3D10_RENDER_TARGET_VIEW_DESC;

/* Depth stencil view */
typedef enum D3D10_DSV_DIMENSION {
    D3D10_DSV_DIMENSION_UNKNOWN          = 0,
    D3D10_DSV_DIMENSION_TEXTURE1D        = 1,
    D3D10_DSV_DIMENSION_TEXTURE1DARRAY   = 2,
    D3D10_DSV_DIMENSION_TEXTURE2D        = 3,
    D3D10_DSV_DIMENSION_TEXTURE2DARRAY   = 4,
    D3D10_DSV_DIMENSION_TEXTURE2DMS      = 5,
    D3D10_DSV_DIMENSION_TEXTURE2DMSARRAY = 6,
} D3D10_DSV_DIMENSION;

typedef struct D3D10_TEX1D_DSV           { UINT MipSlice; } D3D10_TEX1D_DSV;
typedef struct D3D10_TEX1D_ARRAY_DSV     { UINT MipSlice; UINT FirstArraySlice; UINT ArraySize; } D3D10_TEX1D_ARRAY_DSV;
typedef struct D3D10_TEX2D_DSV           { UINT MipSlice; } D3D10_TEX2D_DSV;
typedef struct D3D10_TEX2D_ARRAY_DSV     { UINT MipSlice; UINT FirstArraySlice; UINT ArraySize; } D3D10_TEX2D_ARRAY_DSV;
typedef struct D3D10_TEX2DMS_DSV         { UINT UnusedField_NothingToDefine; } D3D10_TEX2DMS_DSV;
typedef struct D3D10_TEX2DMS_ARRAY_DSV   { UINT FirstArraySlice; UINT ArraySize; } D3D10_TEX2DMS_ARRAY_DSV;

typedef struct D3D10_DEPTH_STENCIL_VIEW_DESC {
    DXGI_FORMAT         Format;
    D3D10_DSV_DIMENSION ViewDimension;
    UINT                Flags;
    union {
        D3D10_TEX1D_DSV         Texture1D;
        D3D10_TEX1D_ARRAY_DSV   Texture1DArray;
        D3D10_TEX2D_DSV         Texture2D;
        D3D10_TEX2D_ARRAY_DSV   Texture2DArray;
        D3D10_TEX2DMS_DSV       Texture2DMS;
        D3D10_TEX2DMS_ARRAY_DSV Texture2DMSArray;
    };
} D3D10_DEPTH_STENCIL_VIEW_DESC;

typedef struct D3D10_SHADER_RESOURCE_VIEW_DESC {
    DXGI_FORMAT              Format;
    D3D10_SRV_DIMENSION1     ViewDimension;
    union {
        D3D10_BUFFER_SRV        Buffer;
        D3D10_TEX1D_SRV         Texture1D;
        D3D10_TEX1D_ARRAY_SRV   Texture1DArray;
        D3D10_TEX2D_SRV         Texture2D;
        D3D10_TEX2D_ARRAY_SRV   Texture2DArray;
        D3D10_TEX2DMS_SRV       Texture2DMS;
        D3D10_TEX2DMS_ARRAY_SRV Texture2DMSArray;
        D3D10_TEX3D_SRV         Texture3D;
        D3D10_TEXCUBE_SRV       TextureCube;
    };
} D3D10_SHADER_RESOURCE_VIEW_DESC;

/* =========================================================================
 * Forward declarations
 * ========================================================================= */
#ifdef __cplusplus

struct ID3D10Device1;
struct ID3D10DeviceChild;
struct ID3D10Resource;
struct ID3D10Buffer;
struct ID3D10Texture1D;
struct ID3D10Texture2D;
struct ID3D10Texture3D;
struct ID3D10View;
struct ID3D10ShaderResourceView;
struct ID3D10ShaderResourceView1;
struct ID3D10RenderTargetView;
struct ID3D10DepthStencilView;
struct ID3D10VertexShader;
struct ID3D10GeometryShader;
struct ID3D10PixelShader;
struct ID3D10InputLayout;
struct ID3D10BlendState;
struct ID3D10BlendState1;
struct ID3D10DepthStencilState;
struct ID3D10RasterizerState;
struct ID3D10SamplerState;
struct ID3D10Asynchronous;
struct ID3D10Query;
struct ID3D10Predicate;
struct ID3D10Counter;
struct ID3D10StateBlock;
struct ID3D10Multithread;

/* =========================================================================
 * IUnknown
 * ========================================================================= */
struct IUnknown;//{
//     virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) {  }
//     virtual ULONG   STDMETHODCALLTYPE AddRef()  { return 0; }
//     virtual ULONG   STDMETHODCALLTYPE Release() { return 0; }
//     virtual ~IUnknown() {}
// };

/* =========================================================================
 * ID3D10DeviceChild
 * ========================================================================= */
struct ID3D10DeviceChild : public IUnknown {
    virtual void   STDMETHODCALLTYPE GetDevice(ID3D10Device1** ppDevice) {}
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) {    }
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) {    }
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) {    }
};

/* =========================================================================
 * ID3D10Resource
 * ========================================================================= */
struct ID3D10Resource : public ID3D10DeviceChild {
    virtual void STDMETHODCALLTYPE GetType(D3D10_RESOURCE_DIMENSION* rType) {}
    virtual void STDMETHODCALLTYPE SetEvictionPriority(UINT EvictionPriority) {}
    virtual UINT STDMETHODCALLTYPE GetEvictionPriority() { return 0; }
};

/* =========================================================================
 * ID3D10Buffer
 * ========================================================================= */
struct ID3D10Buffer : public ID3D10Resource {
    virtual HRESULT STDMETHODCALLTYPE Map(D3D10_MAP MapType, UINT MapFlags, void** ppData) {    }
    virtual void    STDMETHODCALLTYPE Unmap() {}
    virtual void    STDMETHODCALLTYPE GetDesc(D3D10_BUFFER_DESC* pDesc) {}
};

/* =========================================================================
 * ID3D10Texture1D
 * ========================================================================= */
struct ID3D10Texture1D : public ID3D10Resource {
    virtual HRESULT STDMETHODCALLTYPE Map(UINT Subresource, D3D10_MAP MapType, UINT MapFlags, void** ppData) {    }
    virtual void    STDMETHODCALLTYPE Unmap(UINT Subresource) {}
    virtual void    STDMETHODCALLTYPE GetDesc(D3D10_TEXTURE1D_DESC* pDesc) {}
};

/* =========================================================================
 * ID3D10Texture2D
 * ========================================================================= */
struct ID3D10Texture2D : public ID3D10Resource {
    virtual HRESULT STDMETHODCALLTYPE Map(UINT Subresource, D3D10_MAP MapType, UINT MapFlags, D3D10_MAPPED_TEXTURE2D* pMappedTex2D) {    }
    virtual void    STDMETHODCALLTYPE Unmap(UINT Subresource) {}
    virtual void    STDMETHODCALLTYPE GetDesc(D3D10_TEXTURE2D_DESC* pDesc) {}
};

/* =========================================================================
 * ID3D10Texture3D
 * ========================================================================= */
struct ID3D10Texture3D : public ID3D10Resource {
    virtual HRESULT STDMETHODCALLTYPE Map(UINT Subresource, D3D10_MAP MapType, UINT MapFlags, D3D10_MAPPED_TEXTURE3D* pMappedTex3D) {    }
    virtual void    STDMETHODCALLTYPE Unmap(UINT Subresource) {}
    virtual void    STDMETHODCALLTYPE GetDesc(D3D10_TEXTURE3D_DESC* pDesc) {}
};

/* =========================================================================
 * Views
 * ========================================================================= */
struct ID3D10View : public ID3D10DeviceChild {
    virtual void STDMETHODCALLTYPE GetResource(ID3D10Resource** ppResource) {}
};

struct ID3D10ShaderResourceView : public ID3D10View {
    virtual void STDMETHODCALLTYPE GetDesc(D3D10_SHADER_RESOURCE_VIEW_DESC* pDesc) {}
};

struct ID3D10ShaderResourceView1 : public ID3D10View {
    virtual void STDMETHODCALLTYPE GetDesc1(D3D10_SHADER_RESOURCE_VIEW_DESC1* pDesc) {}
};

struct ID3D10RenderTargetView : public ID3D10View {
    virtual void STDMETHODCALLTYPE GetDesc(D3D10_RENDER_TARGET_VIEW_DESC* pDesc) {}
};

struct ID3D10DepthStencilView : public ID3D10View {
    virtual void STDMETHODCALLTYPE GetDesc(D3D10_DEPTH_STENCIL_VIEW_DESC* pDesc) {}
};

/* =========================================================================
 * Shaders
 * ========================================================================= */
struct ID3D10VertexShader   : public ID3D10DeviceChild {};
struct ID3D10GeometryShader : public ID3D10DeviceChild {};
struct ID3D10PixelShader    : public ID3D10DeviceChild {};
struct ID3D10InputLayout    : public ID3D10DeviceChild {};

/* =========================================================================
 * State objects
 * ========================================================================= */
struct ID3D10BlendState : public ID3D10DeviceChild {
    virtual void STDMETHODCALLTYPE GetDesc(D3D10_BLEND_DESC1* pDesc) {}
};

struct ID3D10BlendState1 : public ID3D10BlendState {
    virtual void STDMETHODCALLTYPE GetDesc1(D3D10_BLEND_DESC1* pDesc) {}
};

struct ID3D10DepthStencilState : public ID3D10DeviceChild {
    virtual void STDMETHODCALLTYPE GetDesc(D3D10_DEPTH_STENCIL_DESC* pDesc) {}
};

struct ID3D10RasterizerState : public ID3D10DeviceChild {
    virtual void STDMETHODCALLTYPE GetDesc(D3D10_RASTERIZER_DESC* pDesc) {}
};

struct ID3D10SamplerState : public ID3D10DeviceChild {
    virtual void STDMETHODCALLTYPE GetDesc(D3D10_SAMPLER_DESC* pDesc) {}
};

/* =========================================================================
 * Asynchronous / Query / Predicate / Counter
 * ========================================================================= */
struct ID3D10Asynchronous : public ID3D10DeviceChild {
    virtual void    STDMETHODCALLTYPE Begin() {}
    virtual void    STDMETHODCALLTYPE End() {}
    virtual HRESULT STDMETHODCALLTYPE GetData(void* pData, UINT DataSize, UINT GetDataFlags) {    }
    virtual UINT    STDMETHODCALLTYPE GetDataSize() { return 0; }
};

struct ID3D10Query : public ID3D10Asynchronous {
    virtual void STDMETHODCALLTYPE GetDesc(D3D10_QUERY_DESC* pDesc) {}
};

struct ID3D10Predicate : public ID3D10Query {};

struct ID3D10Counter : public ID3D10Asynchronous {
    virtual void STDMETHODCALLTYPE GetDesc(D3D10_COUNTER_DESC* pDesc) {}
};

/* =========================================================================
 * ID3D10Multithread
 * ========================================================================= */
struct ID3D10Multithread : public IUnknown {
    virtual void STDMETHODCALLTYPE Enter() {}
    virtual void STDMETHODCALLTYPE Leave() {}
    virtual BOOL STDMETHODCALLTYPE SetMultithreadProtected(BOOL bMTProtect) { return FALSE; }
    virtual BOOL STDMETHODCALLTYPE GetMultithreadProtected() { return FALSE; }
};

/* =========================================================================
 * ID3D10Device1
 * ========================================================================= */
struct ID3D10Device1 : public IUnknown {
    /* VS */
    virtual void STDMETHODCALLTYPE VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D10Buffer* const* ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE PSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D10ShaderResourceView* const* ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE PSSetShader(ID3D10PixelShader* pPixelShader) {}
    virtual void STDMETHODCALLTYPE PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D10SamplerState* const* ppSamplers) {}
    virtual void STDMETHODCALLTYPE VSSetShader(ID3D10VertexShader* pVertexShader) {}
    virtual void STDMETHODCALLTYPE DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {}
    virtual void STDMETHODCALLTYPE Draw(UINT VertexCount, UINT StartVertexLocation) {}
    virtual void STDMETHODCALLTYPE PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D10Buffer* const* ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE IASetInputLayout(ID3D10InputLayout* pInputLayout) {}
    virtual void STDMETHODCALLTYPE IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D10Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets) {}
    virtual void STDMETHODCALLTYPE IASetIndexBuffer(ID3D10Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset) {}
    virtual void STDMETHODCALLTYPE DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation) {}
    virtual void STDMETHODCALLTYPE DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation) {}
    virtual void STDMETHODCALLTYPE GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D10Buffer* const* ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE GSSetShader(ID3D10GeometryShader* pShader) {}
    virtual void STDMETHODCALLTYPE IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY Topology) {}
    virtual void STDMETHODCALLTYPE VSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D10ShaderResourceView* const* ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE VSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D10SamplerState* const* ppSamplers) {}
    virtual void STDMETHODCALLTYPE SetPredication(ID3D10Predicate* pPredicate, BOOL PredicateValue) {}
    virtual void STDMETHODCALLTYPE GSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D10ShaderResourceView* const* ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE GSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D10SamplerState* const* ppSamplers) {}
    virtual void STDMETHODCALLTYPE OMSetRenderTargets(UINT NumViews, ID3D10RenderTargetView* const* ppRenderTargetViews, ID3D10DepthStencilView* pDepthStencilView) {}
    virtual void STDMETHODCALLTYPE OMSetBlendState(ID3D10BlendState* pBlendState, const FLOAT BlendFactor[4], UINT SampleMask) {}
    virtual void STDMETHODCALLTYPE OMSetDepthStencilState(ID3D10DepthStencilState* pDepthStencilState, UINT StencilRef) {}
    virtual void STDMETHODCALLTYPE SOSetTargets(UINT NumBuffers, ID3D10Buffer* const* ppSOTargets, const UINT* pOffsets) {}
    virtual void STDMETHODCALLTYPE DrawAuto() {}
    virtual void STDMETHODCALLTYPE RSSetState(ID3D10RasterizerState* pRasterizerState) {}
    virtual void STDMETHODCALLTYPE RSSetViewports(UINT NumViewports, const D3D10_VIEWPORT* pViewports) {}
    virtual void STDMETHODCALLTYPE RSSetScissorRects(UINT NumRects, const D3D10_RECT* pRects) {}
    virtual void STDMETHODCALLTYPE CopySubresourceRegion(ID3D10Resource* pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D10Resource* pSrcResource, UINT SrcSubresource, const D3D10_BOX* pSrcBox) {}
    virtual void STDMETHODCALLTYPE CopyResource(ID3D10Resource* pDstResource, ID3D10Resource* pSrcResource) {}
    virtual void STDMETHODCALLTYPE UpdateSubresource(ID3D10Resource* pDstResource, UINT DstSubresource, const D3D10_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) {}
    virtual void STDMETHODCALLTYPE ClearRenderTargetView(ID3D10RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4]) {}
    virtual void STDMETHODCALLTYPE ClearDepthStencilView(ID3D10DepthStencilView* pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil) {}
    virtual void STDMETHODCALLTYPE GenerateMips(ID3D10ShaderResourceView* pShaderResourceView) {}
    virtual void STDMETHODCALLTYPE ResolveSubresource(ID3D10Resource* pDstResource, UINT DstSubresource, ID3D10Resource* pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format) {}
    virtual void STDMETHODCALLTYPE VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D10Buffer** ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE PSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D10ShaderResourceView** ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE PSGetShader(ID3D10PixelShader** ppPixelShader) {}
    virtual void STDMETHODCALLTYPE PSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D10SamplerState** ppSamplers) {}
    virtual void STDMETHODCALLTYPE VSGetShader(ID3D10VertexShader** ppVertexShader) {}
    virtual void STDMETHODCALLTYPE PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D10Buffer** ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE IAGetInputLayout(ID3D10InputLayout** ppInputLayout) {}
    virtual void STDMETHODCALLTYPE IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D10Buffer** ppVertexBuffers, UINT* pStrides, UINT* pOffsets) {}
    virtual void STDMETHODCALLTYPE IAGetIndexBuffer(ID3D10Buffer** pIndexBuffer, DXGI_FORMAT* Format, UINT* Offset) {}
    virtual void STDMETHODCALLTYPE GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D10Buffer** ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE GSGetShader(ID3D10GeometryShader** ppGeometryShader) {}
    virtual void STDMETHODCALLTYPE IAGetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY* pTopology) {}
    virtual void STDMETHODCALLTYPE VSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D10ShaderResourceView** ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE VSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D10SamplerState** ppSamplers) {}
    virtual void STDMETHODCALLTYPE GetPredication(ID3D10Predicate** ppPredicate, BOOL* pPredicateValue) {}
    virtual void STDMETHODCALLTYPE GSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D10ShaderResourceView** ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE GSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D10SamplerState** ppSamplers) {}
    virtual void STDMETHODCALLTYPE OMGetRenderTargets(UINT NumViews, ID3D10RenderTargetView** ppRenderTargetViews, ID3D10DepthStencilView** ppDepthStencilView) {}
    virtual void STDMETHODCALLTYPE OMGetBlendState(ID3D10BlendState** ppBlendState, FLOAT BlendFactor[4], UINT* pSampleMask) {}
    virtual void STDMETHODCALLTYPE OMGetDepthStencilState(ID3D10DepthStencilState** ppDepthStencilState, UINT* pStencilRef) {}
    virtual void STDMETHODCALLTYPE SOGetTargets(UINT NumBuffers, ID3D10Buffer** ppSOTargets, UINT* pOffsets) {}
    virtual void STDMETHODCALLTYPE RSGetState(ID3D10RasterizerState** ppRasterizerState) {}
    virtual void STDMETHODCALLTYPE RSGetViewports(UINT* NumViewports, D3D10_VIEWPORT* pViewports) {}
    virtual void STDMETHODCALLTYPE RSGetScissorRects(UINT* NumRects, D3D10_RECT* pRects) {}
    virtual HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason() {    }
    virtual HRESULT STDMETHODCALLTYPE SetExceptionMode(UINT RaiseFlags) {    }
    virtual UINT    STDMETHODCALLTYPE GetExceptionMode() { return 0; }
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) {    }
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) {    }
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) {    }
    virtual void    STDMETHODCALLTYPE ClearState() {}
    virtual void    STDMETHODCALLTYPE Flush() {}

    /* Resource creation */
    virtual HRESULT STDMETHODCALLTYPE CreateBuffer(const D3D10_BUFFER_DESC* pDesc, const D3D10_SUBRESOURCE_DATA* pInitialData, ID3D10Buffer** ppBuffer) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateTexture1D(const D3D10_TEXTURE1D_DESC* pDesc, const D3D10_SUBRESOURCE_DATA* pInitialData, ID3D10Texture1D** ppTexture1D) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateTexture2D(const D3D10_TEXTURE2D_DESC* pDesc, const D3D10_SUBRESOURCE_DATA* pInitialData, ID3D10Texture2D** ppTexture2D) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateTexture3D(const D3D10_TEXTURE3D_DESC* pDesc, const D3D10_SUBRESOURCE_DATA* pInitialData, ID3D10Texture3D** ppTexture3D) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView(ID3D10Resource* pResource, const D3D10_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D10ShaderResourceView** ppSRView) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView1(ID3D10Resource* pResource, const D3D10_SHADER_RESOURCE_VIEW_DESC1* pDesc, ID3D10ShaderResourceView1** ppSRView) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateRenderTargetView(ID3D10Resource* pResource, const D3D10_RENDER_TARGET_VIEW_DESC* pDesc, ID3D10RenderTargetView** ppRTView) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilView(ID3D10Resource* pResource, const D3D10_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D10DepthStencilView** ppDepthStencilView) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateInputLayout(const D3D10_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D10InputLayout** ppInputLayout) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D10VertexShader** ppVertexShader) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D10GeometryShader** ppGeometryShader) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateGeometryShaderWithStreamOutput(const void* pShaderBytecode, SIZE_T BytecodeLength, const D3D10_SO_DECLARATION_ENTRY* pSODeclaration, UINT NumEntries, UINT OutputStreamStride, ID3D10GeometryShader** ppGeometryShader) {    }
    virtual HRESULT STDMETHODCALLTYPE CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D10PixelShader** ppPixelShader) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateBlendState(const D3D10_BLEND_DESC1* pBlendStateDesc, ID3D10BlendState** ppBlendState) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateBlendState1(const D3D10_BLEND_DESC1* pBlendStateDesc, ID3D10BlendState1** ppBlendState) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilState(const D3D10_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D10DepthStencilState** ppDepthStencilState) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState(const D3D10_RASTERIZER_DESC* pRasterizerDesc, ID3D10RasterizerState** ppRasterizerState) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateSamplerState(const D3D10_SAMPLER_DESC* pSamplerDesc, ID3D10SamplerState** ppSamplerState) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateQuery(const D3D10_QUERY_DESC* pQueryDesc, ID3D10Query** ppQuery) {    }
    virtual HRESULT STDMETHODCALLTYPE CreatePredicate(const D3D10_QUERY_DESC* pPredicateDesc, ID3D10Predicate** ppPredicate) {    }
    virtual HRESULT STDMETHODCALLTYPE CreateCounter(const D3D10_COUNTER_DESC* pCounterDesc, ID3D10Counter** ppCounter) {    }
    virtual HRESULT STDMETHODCALLTYPE CheckFormatSupport(DXGI_FORMAT Format, UINT* pFormatSupport) {    }
    virtual HRESULT STDMETHODCALLTYPE CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT* pNumQualityLevels) {    }
    virtual void    STDMETHODCALLTYPE CheckCounterInfo(D3D10_COUNTER_INFO* pCounterInfo) {}
    virtual HRESULT STDMETHODCALLTYPE CheckCounter(const D3D10_COUNTER_DESC* pDesc, D3D10_COUNTER_TYPE* pType, UINT* pActiveCounters, LPSTR szName, UINT* pNameLength, LPSTR szUnits, UINT* pUnitsLength, LPSTR szDescription, UINT* pDescriptionLength) {    }
    virtual UINT    STDMETHODCALLTYPE GetCreationFlags() { return 0; }
    virtual HRESULT STDMETHODCALLTYPE OpenSharedResource(HANDLE hResource, REFIID ReturnedInterface, void** ppResource) {    }
    virtual D3D10_FEATURE_LEVEL1 STDMETHODCALLTYPE GetFeatureLevel() { return D3D10_FEATURE_LEVEL_10_1; }
};

#endif /* __cplusplus */

/* =========================================================================
 * GUIDs
 * ========================================================================= */
DEFINE_GUID(IID_ID3D10DeviceChild,       0x9b7e4c00, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10Resource,          0x9b7e4c01, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10Buffer,            0x9b7e4c02, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10Texture1D,         0x9b7e4c03, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10Texture2D,         0x9b7e4c04, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10Texture3D,         0x9b7e4c05, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10View,              0xc902b03f, 0x60a7, 0x49ba, 0x99, 0x36, 0x2a, 0x3a, 0xb3, 0x7a, 0x7e, 0x33);
DEFINE_GUID(IID_ID3D10ShaderResourceView,0x9b7e4c07, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10ShaderResourceView1,0x9b7e4c08, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10RenderTargetView,  0x9b7e4c08, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf1);
DEFINE_GUID(IID_ID3D10DepthStencilView,  0x9b7e4c09, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10VertexShader,      0x9b7e4c0a, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10GeometryShader,    0x6316be88, 0x54cd, 0x4040, 0xab, 0x44, 0x20, 0x46, 0x1b, 0xc8, 0x1f, 0x68);
DEFINE_GUID(IID_ID3D10PixelShader,       0x4968b601, 0x9d00, 0x4cde, 0x83, 0x46, 0x8e, 0x7f, 0x67, 0x58, 0x19, 0xb6);
DEFINE_GUID(IID_ID3D10InputLayout,       0x9b7e4c0b, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10BlendState,        0xedad8d19, 0x8a35, 0x4d6d, 0x85, 0x66, 0x2e, 0xa2, 0x76, 0xcd, 0xe1, 0x61);
DEFINE_GUID(IID_ID3D10BlendState1,       0xbad68517, 0xd7b4, 0x4747, 0x86, 0x15, 0xf7, 0x77, 0x08, 0x53, 0x46, 0x50);
DEFINE_GUID(IID_ID3D10DepthStencilState, 0x2b4b1cc8, 0xa4ad, 0x41f8, 0x83, 0x22, 0xca, 0x86, 0xfc, 0x3e, 0xc6, 0x75);
DEFINE_GUID(IID_ID3D10RasterizerState,   0xa2a07292, 0x89af, 0x4345, 0xbe, 0x2e, 0xc5, 0x3d, 0x9f, 0xbb, 0x6e, 0x9f);
DEFINE_GUID(IID_ID3D10SamplerState,      0x9b7e4c0c, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10Asynchronous,      0x9b7e4c0d, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10Query,             0x9b7e4c0e, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10Predicate,         0x9b7e4c10, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10Counter,           0x9b7e4c11, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10Device1,           0x9b7e4c8f, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3D10Multithread,       0x9b7e4e00, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);

/* =========================================================================
 * D3D10CreateDevice1 stub
 * ========================================================================= */
#ifndef D3D10_SDK_VERSION
#define D3D10_SDK_VERSION 29
#endif

#define D3D10_APPEND_ALIGNED_ELEMENT    0xffffffff
#define D3D10_DEFAULT_SAMPLE_MASK       0xffffffff
#define D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT 8
#define D3D10_MAX_TEXTURE_DIMENSION_2_TO_EXP   17
#define D3D10_DEFAULT_DEPTH_BIAS        0
#define D3D10_DEFAULT_DEPTH_BIAS_CLAMP  0.0f
#define D3D10_DEFAULT_SLOPE_SCALED_DEPTH_BIAS 0.0f
#define D3D10_FLOAT32_MAX               3.402823466e+38f
#define D3D10_DEFAULT_STENCIL_READ_MASK  0xff
#define D3D10_DEFAULT_STENCIL_WRITE_MASK 0xff
#define D3D10_DEFAULT_BLEND_FACTOR_RED   1.0f
#define D3D10_DEFAULT_BLEND_FACTOR_GREEN 1.0f
#define D3D10_DEFAULT_BLEND_FACTOR_BLUE  1.0f
#define D3D10_DEFAULT_BLEND_FACTOR_ALPHA 1.0f
#define D3D10_VS_INPUT_REGISTER_COUNT    32
#define D3D10_VS_OUTPUT_REGISTER_COUNT   32
#define D3D10_PS_INPUT_REGISTER_COUNT    32
#define D3D10_PS_OUTPUT_REGISTER_COUNT   8
#define D3D10_GS_OUTPUT_VERTEX_COUNT_MAX 1024
#define D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT 14
#define D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT             16
#define D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT      128
#define D3D10_VIEWPORT_AND_SCISSORRECT_MAX_INDEX          15
#define D3D10_SO_BUFFER_SLOT_COUNT        4
#define D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT 16
#define D3D10_IA_INDEX_INPUT_RESOURCE_SLOT_COUNT  1
#define D3D10_MIP_LOD_BIAS_MAX            15.99f
#define D3D10_MIP_LOD_BIAS_MIN           -16.0f
#define D3D10_MAX_MAXANISOTROPY           16
#define D3D10_MIN_MAXANISOTROPY           0

#ifdef __cplusplus
extern "C" {
#endif

static inline HRESULT D3D10CreateDevice1(
    void*                  pAdapter,
    D3D10_DRIVER_TYPE      DriverType,
    HMODULE                Software,
    UINT                   Flags,
    D3D10_FEATURE_LEVEL1   HardwareLevel,
    UINT                   SDKVersion,
    ID3D10Device1**        ppDevice)
{
    (void)pAdapter; (void)DriverType; (void)Software;
    (void)Flags; (void)HardwareLevel; (void)SDKVersion;
    if (ppDevice) *ppDevice = 0;
      
}

static inline HRESULT D3D10CreateDevice(
    void*              pAdapter,
    D3D10_DRIVER_TYPE  DriverType,
    HMODULE            Software,
    UINT               Flags,
    UINT               SDKVersion,
    ID3D10Device1**    ppDevice)
{
    (void)pAdapter; (void)DriverType; (void)Software;
    (void)Flags; (void)SDKVersion;
    if (ppDevice) *ppDevice = 0;
      
}

static inline UINT D3D10CalcSubresource(UINT MipSlice, UINT ArraySlice, UINT MipLevels)
{
    return MipSlice + ArraySlice * MipLevels;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

typedef struct _D3D_SHADER_MACRO {
    LPCSTR Name;
    LPCSTR Definition;
} D3D_SHADER_MACRO;
typedef D3D_SHADER_MACRO D3D10_SHADER_MACRO;

typedef enum _D3D_INCLUDE_TYPE {
    D3D_INCLUDE_LOCAL        = 0,
    D3D_INCLUDE_SYSTEM       = 1,
    D3D10_INCLUDE_LOCAL      = D3D_INCLUDE_LOCAL,
    D3D10_INCLUDE_SYSTEM     = D3D_INCLUDE_SYSTEM,
    D3D_INCLUDE_FORCE_DWORD  = 0x7fffffff,
} D3D_INCLUDE_TYPE;

#ifdef __cplusplus
struct ID3D10Include {
    virtual HRESULT STDMETHODCALLTYPE Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) {  }
    virtual HRESULT STDMETHODCALLTYPE Close(LPCVOID pData) { }
    virtual ~ID3D10Include() {}
};
typedef ID3D10Include ID3DInclude;
#endif

#ifdef __cplusplus
struct ID3D10Blob : public IUnknown {
    virtual LPVOID  STDMETHODCALLTYPE GetBufferPointer() { return nullptr; }
    virtual SIZE_T  STDMETHODCALLTYPE GetBufferSize()    { return 0; }
};
typedef ID3D10Blob ID3DBlob;
#endif

#endif /* __D3D10_1_H__ */