#pragma once
#ifndef __D3D11_H__
#define __D3D11_H__

/*
 * d3d11.h - Linux stub header for compilation purposes only.
 * All functions are empty stubs and do not provide actual DirectX functionality.
 */

#include <stdint.h>
#include <stddef.h>

#include "d3d10_1.h"

/* =========================================================================
 * Basic Windows type compatibility
 * ========================================================================= */
#ifndef _WINDOWS_


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

typedef GUID        IID;
typedef GUID        CLSID;
typedef const IID*  REFIID;

#ifndef DEFINE_GUID
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
    extern const GUID name
#endif

/* =========================================================================
 * HRESULT codes
 * ========================================================================= */
#define S_OK                        ((HRESULT)0x00000000L)
#define S_FALSE                     ((HRESULT)0x00000001L)
#define E_NOTIMPL                   ((HRESULT)0x80004001L)
#define E_NOINTERFACE               ((HRESULT)0x80004002L)
#define E_POINTER                   ((HRESULT)0x80004003L)
#define E_ABORT                     ((HRESULT)0x80004004L)
#define E_FAIL                      ((HRESULT)0x80004005L)
#define E_UNEXPECTED                ((HRESULT)0x8000FFFFL)
#define E_ACCESSDENIED              ((HRESULT)0x80070005L)
#define E_HANDLE                    ((HRESULT)0x80070006L)
#define E_OUTOFMEMORY               ((HRESULT)0x8007000EL)
#define E_INVALIDARG                ((HRESULT)0x80070057L)

#define DXGI_ERROR_NOT_FOUND        ((HRESULT)0x887A0002L)
#define DXGI_ERROR_MORE_DATA        ((HRESULT)0x887A0003L)
#define DXGI_ERROR_UNSUPPORTED      ((HRESULT)0x887A0004L)
#define DXGI_ERROR_DEVICE_REMOVED   ((HRESULT)0x887A0005L)
#define DXGI_ERROR_DEVICE_HUNG      ((HRESULT)0x887A0006L)
#define DXGI_ERROR_DEVICE_RESET     ((HRESULT)0x887A0007L)
#define DXGI_ERROR_WAS_STILL_DRAWING ((HRESULT)0x887A000AL)
#define DXGI_ERROR_INVALID_CALL     ((HRESULT)0x887A0001L)

#define D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS   ((HRESULT)0x887C0001L)
#define D3D11_ERROR_FILE_NOT_FOUND                  ((HRESULT)0x887C0002L)
#define D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS    ((HRESULT)0x887C0003L)
#define D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD ((HRESULT)0x887C0004L)

#define SUCCEEDED(hr)   (((HRESULT)(hr)) >= 0)
#define FAILED(hr)      (((HRESULT)(hr)) < 0)

/* =========================================================================
 * Calling convention / linkage macros
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
#define STDMETHOD(method)         virtual HRESULT STDMETHODCALLTYPE method
#endif
#ifndef STDMETHOD_
#define STDMETHOD_(type, method)  virtual type STDMETHODCALLTYPE method
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

typedef enum _D3D_PRIMITIVE {
    D3D_PRIMITIVE_UNDEFINED             = 0,
    D3D_PRIMITIVE_POINT                 = 1,
    D3D_PRIMITIVE_LINE                  = 2,
    D3D_PRIMITIVE_TRIANGLE              = 3,
    D3D_PRIMITIVE_LINE_ADJ              = 6,
    D3D_PRIMITIVE_TRIANGLE_ADJ          = 7,
    D3D_PRIMITIVE_1_CONTROL_POINT_PATCH = 8,
    D3D_PRIMITIVE_32_CONTROL_POINT_PATCH = 39,
    D3D11_PRIMITIVE_UNDEFINED           = D3D_PRIMITIVE_UNDEFINED,
    D3D11_PRIMITIVE_POINT               = D3D_PRIMITIVE_POINT,
    D3D11_PRIMITIVE_LINE                = D3D_PRIMITIVE_LINE,
    D3D11_PRIMITIVE_TRIANGLE            = D3D_PRIMITIVE_TRIANGLE,
    D3D11_PRIMITIVE_LINE_ADJ            = D3D_PRIMITIVE_LINE_ADJ,
    D3D11_PRIMITIVE_TRIANGLE_ADJ        = D3D_PRIMITIVE_TRIANGLE_ADJ,
    D3D_PRIMITIVE_FORCE_DWORD           = 0x7fffffff,
} D3D_PRIMITIVE;

typedef enum D3D11_SRV_DIMENSION {
    D3D11_SRV_DIMENSION_UNKNOWN           = 0,
    D3D11_SRV_DIMENSION_BUFFER            = 1,
    D3D11_SRV_DIMENSION_TEXTURE1D         = 2,
    D3D11_SRV_DIMENSION_TEXTURE1DARRAY    = 3,
    D3D11_SRV_DIMENSION_TEXTURE2D         = 4,
    D3D11_SRV_DIMENSION_TEXTURE2DARRAY    = 5,
    D3D11_SRV_DIMENSION_TEXTURE2DMS       = 6,
    D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY  = 7,
    D3D11_SRV_DIMENSION_TEXTURE3D         = 8,
    D3D11_SRV_DIMENSION_TEXTURECUBE       = 9,
    D3D11_SRV_DIMENSION_TEXTURECUBEARRAY  = 10,
    D3D11_SRV_DIMENSION_BUFFEREX          = 11,
} D3D11_SRV_DIMENSION;

typedef enum D3D11_CONTEXT_TYPE {
    D3D11_CONTEXT_TYPE_ALL       = 0,
    D3D11_CONTEXT_TYPE_3D        = 1,
    D3D11_CONTEXT_TYPE_COMPUTE   = 2,
    D3D11_CONTEXT_TYPE_COPY      = 3,
    D3D11_CONTEXT_TYPE_VIDEO     = 4,
} D3D11_CONTEXT_TYPE;

typedef D3D11_SRV_DIMENSION D3D_SRV_DIMENSION;

/* =========================================================================
 * D3D11 Feature Level
 * ========================================================================= */
typedef enum D3D_FEATURE_LEVEL {
    D3D_FEATURE_LEVEL_1_0_CORE = 0x1000,
    D3D_FEATURE_LEVEL_9_1      = 0x9100,
    D3D_FEATURE_LEVEL_9_2      = 0x9200,
    D3D_FEATURE_LEVEL_9_3      = 0x9300,
    D3D_FEATURE_LEVEL_10_0     = 0xa000,
    D3D_FEATURE_LEVEL_10_1     = 0xa100,
    D3D_FEATURE_LEVEL_11_0     = 0xb000,
    D3D_FEATURE_LEVEL_11_1     = 0xb100,
    D3D_FEATURE_LEVEL_12_0     = 0xc000,
    D3D_FEATURE_LEVEL_12_1     = 0xc100,
} D3D_FEATURE_LEVEL;

/* =========================================================================
 * D3D Driver Type
 * ========================================================================= */
typedef enum D3D_DRIVER_TYPE {
    D3D_DRIVER_TYPE_UNKNOWN   = 0,
    D3D_DRIVER_TYPE_HARDWARE  = 1,
    D3D_DRIVER_TYPE_REFERENCE = 2,
    D3D_DRIVER_TYPE_NULL      = 3,
    D3D_DRIVER_TYPE_SOFTWARE  = 4,
    D3D_DRIVER_TYPE_WARP      = 5,
} D3D_DRIVER_TYPE;

/* =========================================================================
 * DXGI Format (complete)
 * ========================================================================= */
// typedef struct DXGI_SAMPLE_DESC {
//     UINT Count;
//     UINT Quality;
// } DXGI_SAMPLE_DESC;

// typedef struct DXGI_RATIONAL {
//     UINT Numerator;
//     UINT Denominator;
// } DXGI_RATIONAL;

/* =========================================================================
 * D3D11 Enumerations
 * ========================================================================= */
typedef enum D3D11_USAGE {
    D3D11_USAGE_DEFAULT   = 0,
    D3D11_USAGE_IMMUTABLE = 1,
    D3D11_USAGE_DYNAMIC   = 2,
    D3D11_USAGE_STAGING   = 3,
} D3D11_USAGE;

typedef enum D3D11_BIND_FLAG {
    D3D11_BIND_VERTEX_BUFFER    = 0x1,
    D3D11_BIND_INDEX_BUFFER     = 0x2,
    D3D11_BIND_CONSTANT_BUFFER  = 0x4,
    D3D11_BIND_SHADER_RESOURCE  = 0x8,
    D3D11_BIND_STREAM_OUTPUT    = 0x10,
    D3D11_BIND_RENDER_TARGET    = 0x20,
    D3D11_BIND_DEPTH_STENCIL    = 0x40,
    D3D11_BIND_UNORDERED_ACCESS = 0x80,
    D3D11_BIND_DECODER          = 0x200,
    D3D11_BIND_VIDEO_ENCODER    = 0x400,
} D3D11_BIND_FLAG;

typedef enum D3D11_CPU_ACCESS_FLAG {
    D3D11_CPU_ACCESS_WRITE = 0x10000,
    D3D11_CPU_ACCESS_READ  = 0x20000,
} D3D11_CPU_ACCESS_FLAG;

typedef enum D3D11_RESOURCE_MISC_FLAG {
    D3D11_RESOURCE_MISC_GENERATE_MIPS                   = 0x1,
    D3D11_RESOURCE_MISC_SHARED                          = 0x2,
    D3D11_RESOURCE_MISC_TEXTURECUBE                     = 0x4,
    D3D11_RESOURCE_MISC_DRAWINDIRECT_ARGS               = 0x10,
    D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS          = 0x20,
    D3D11_RESOURCE_MISC_BUFFER_STRUCTURED               = 0x40,
    D3D11_RESOURCE_MISC_RESOURCE_CLAMP                  = 0x80,
    D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX               = 0x100,
    D3D11_RESOURCE_MISC_GDI_COMPATIBLE                  = 0x200,
    D3D11_RESOURCE_MISC_SHARED_NTHANDLE                 = 0x800,
    D3D11_RESOURCE_MISC_RESTRICTED_CONTENT              = 0x1000,
    D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE        = 0x2000,
    D3D11_RESOURCE_MISC_RESTRICT_SHARED_RESOURCE_DRIVER = 0x4000,
    D3D11_RESOURCE_MISC_GUARDED                         = 0x8000,
    D3D11_RESOURCE_MISC_TILE_POOL                       = 0x20000,
    D3D11_RESOURCE_MISC_TILED                           = 0x40000,
    D3D11_RESOURCE_MISC_HW_PROTECTED                    = 0x80000,
} D3D11_RESOURCE_MISC_FLAG;

typedef enum D3D11_RESOURCE_DIMENSION {
    D3D11_RESOURCE_DIMENSION_UNKNOWN   = 0,
    D3D11_RESOURCE_DIMENSION_BUFFER    = 1,
    D3D11_RESOURCE_DIMENSION_TEXTURE1D = 2,
    D3D11_RESOURCE_DIMENSION_TEXTURE2D = 3,
    D3D11_RESOURCE_DIMENSION_TEXTURE3D = 4,
} D3D11_RESOURCE_DIMENSION;

typedef enum D3D11_MAP {
    D3D11_MAP_READ              = 1,
    D3D11_MAP_WRITE             = 2,
    D3D11_MAP_READ_WRITE        = 3,
    D3D11_MAP_WRITE_DISCARD     = 4,
    D3D11_MAP_WRITE_NO_OVERWRITE = 5,
} D3D11_MAP;

typedef enum D3D11_MAP_FLAG {
    D3D11_MAP_FLAG_DO_NOT_WAIT = 0x100000,
} D3D11_MAP_FLAG;

typedef enum D3D11_PRIMITIVE_TOPOLOGY {
    D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED          = 0,
    D3D11_PRIMITIVE_TOPOLOGY_POINTLIST          = 1,
    D3D11_PRIMITIVE_TOPOLOGY_LINELIST           = 2,
    D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP          = 3,
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST       = 4,
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP      = 5,
    D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ       = 10,
    D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ      = 11,
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ   = 12,
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ  = 13,
    D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST  = 33,
    D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST  = 34,
    D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST  = 35,
    D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST  = 36,
    D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST = 64,
} D3D11_PRIMITIVE_TOPOLOGY;

typedef enum D3D11_FILL_MODE {
    D3D11_FILL_WIREFRAME = 2,
    D3D11_FILL_SOLID     = 3,
} D3D11_FILL_MODE;

typedef enum D3D11_CULL_MODE {
    D3D11_CULL_NONE  = 1,
    D3D11_CULL_FRONT = 2,
    D3D11_CULL_BACK  = 3,
} D3D11_CULL_MODE;

typedef enum D3D11_DEPTH_WRITE_MASK {
    D3D11_DEPTH_WRITE_MASK_ZERO = 0,
    D3D11_DEPTH_WRITE_MASK_ALL  = 1,
} D3D11_DEPTH_WRITE_MASK;

typedef enum D3D11_COMPARISON_FUNC {
    D3D11_COMPARISON_NEVER          = 1,
    D3D11_COMPARISON_LESS           = 2,
    D3D11_COMPARISON_EQUAL          = 3,
    D3D11_COMPARISON_LESS_EQUAL     = 4,
    D3D11_COMPARISON_GREATER        = 5,
    D3D11_COMPARISON_NOT_EQUAL      = 6,
    D3D11_COMPARISON_GREATER_EQUAL  = 7,
    D3D11_COMPARISON_ALWAYS         = 8,
} D3D11_COMPARISON_FUNC;

typedef enum D3D11_STENCIL_OP {
    D3D11_STENCIL_OP_KEEP     = 1,
    D3D11_STENCIL_OP_ZERO     = 2,
    D3D11_STENCIL_OP_REPLACE  = 3,
    D3D11_STENCIL_OP_INCR_SAT = 4,
    D3D11_STENCIL_OP_DECR_SAT = 5,
    D3D11_STENCIL_OP_INVERT   = 6,
    D3D11_STENCIL_OP_INCR     = 7,
    D3D11_STENCIL_OP_DECR     = 8,
} D3D11_STENCIL_OP;

typedef enum D3D11_BLEND {
    D3D11_BLEND_ZERO             = 1,
    D3D11_BLEND_ONE              = 2,
    D3D11_BLEND_SRC_COLOR        = 3,
    D3D11_BLEND_INV_SRC_COLOR    = 4,
    D3D11_BLEND_SRC_ALPHA        = 5,
    D3D11_BLEND_INV_SRC_ALPHA    = 6,
    D3D11_BLEND_DEST_ALPHA       = 7,
    D3D11_BLEND_INV_DEST_ALPHA   = 8,
    D3D11_BLEND_DEST_COLOR       = 9,
    D3D11_BLEND_INV_DEST_COLOR   = 10,
    D3D11_BLEND_SRC_ALPHA_SAT    = 11,
    D3D11_BLEND_BLEND_FACTOR     = 14,
    D3D11_BLEND_INV_BLEND_FACTOR = 15,
    D3D11_BLEND_SRC1_COLOR       = 16,
    D3D11_BLEND_INV_SRC1_COLOR   = 17,
    D3D11_BLEND_SRC1_ALPHA       = 18,
    D3D11_BLEND_INV_SRC1_ALPHA   = 19,
} D3D11_BLEND;

typedef enum D3D11_BLEND_OP {
    D3D11_BLEND_OP_ADD          = 1,
    D3D11_BLEND_OP_SUBTRACT     = 2,
    D3D11_BLEND_OP_REV_SUBTRACT = 3,
    D3D11_BLEND_OP_MIN          = 4,
    D3D11_BLEND_OP_MAX          = 5,
} D3D11_BLEND_OP;

typedef enum D3D11_COLOR_WRITE_ENABLE {
    D3D11_COLOR_WRITE_ENABLE_RED   = 1,
    D3D11_COLOR_WRITE_ENABLE_GREEN = 2,
    D3D11_COLOR_WRITE_ENABLE_BLUE  = 4,
    D3D11_COLOR_WRITE_ENABLE_ALPHA = 8,
    D3D11_COLOR_WRITE_ENABLE_ALL   = (D3D11_COLOR_WRITE_ENABLE_RED | D3D11_COLOR_WRITE_ENABLE_GREEN |
                                      D3D11_COLOR_WRITE_ENABLE_BLUE | D3D11_COLOR_WRITE_ENABLE_ALPHA),
} D3D11_COLOR_WRITE_ENABLE;

typedef enum D3D11_FILTER {
    D3D11_FILTER_MIN_MAG_MIP_POINT                          = 0,
    D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR                   = 0x1,
    D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT             = 0x4,
    D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR                   = 0x5,
    D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT                   = 0x10,
    D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR            = 0x11,
    D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT                   = 0x14,
    D3D11_FILTER_MIN_MAG_MIP_LINEAR                         = 0x15,
    D3D11_FILTER_ANISOTROPIC                                = 0x55,
    D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT               = 0x80,
    D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR              = 0x95,
    D3D11_FILTER_COMPARISON_ANISOTROPIC                     = 0xd5,
    D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT                  = 0x100,
    D3D11_FILTER_MINIMUM_ANISOTROPIC                        = 0x155,
    D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT                  = 0x180,
    D3D11_FILTER_MAXIMUM_ANISOTROPIC                        = 0x1d5,
} D3D11_FILTER;

typedef enum D3D11_FILTER_TYPE {
    D3D11_FILTER_TYPE_POINT  = 0,
    D3D11_FILTER_TYPE_LINEAR = 1,
} D3D11_FILTER_TYPE;

typedef enum D3D11_FILTER_REDUCTION_TYPE {
    D3D11_FILTER_REDUCTION_TYPE_STANDARD   = 0,
    D3D11_FILTER_REDUCTION_TYPE_COMPARISON = 1,
    D3D11_FILTER_REDUCTION_TYPE_MINIMUM    = 2,
    D3D11_FILTER_REDUCTION_TYPE_MAXIMUM    = 3,
} D3D11_FILTER_REDUCTION_TYPE;

typedef enum D3D11_TEXTURE_ADDRESS_MODE {
    D3D11_TEXTURE_ADDRESS_WRAP        = 1,
    D3D11_TEXTURE_ADDRESS_MIRROR      = 2,
    D3D11_TEXTURE_ADDRESS_CLAMP       = 3,
    D3D11_TEXTURE_ADDRESS_BORDER      = 4,
    D3D11_TEXTURE_ADDRESS_MIRROR_ONCE = 5,
} D3D11_TEXTURE_ADDRESS_MODE;

typedef enum D3D11_INPUT_CLASSIFICATION {
    D3D11_INPUT_PER_VERTEX_DATA   = 0,
    D3D11_INPUT_PER_INSTANCE_DATA = 1,
} D3D11_INPUT_CLASSIFICATION;

typedef enum D3D11_QUERY {
    D3D11_QUERY_EVENT                      = 0,
    D3D11_QUERY_OCCLUSION                  = 1,
    D3D11_QUERY_TIMESTAMP                  = 2,
    D3D11_QUERY_TIMESTAMP_DISJOINT         = 3,
    D3D11_QUERY_PIPELINE_STATISTICS        = 4,
    D3D11_QUERY_OCCLUSION_PREDICATE        = 5,
    D3D11_QUERY_SO_STATISTICS              = 6,
    D3D11_QUERY_SO_OVERFLOW_PREDICATE      = 7,
    D3D11_QUERY_SO_STATISTICS_STREAM0      = 8,
    D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM0 = 9,
    D3D11_QUERY_SO_STATISTICS_STREAM1      = 10,
    D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM1 = 11,
    D3D11_QUERY_SO_STATISTICS_STREAM2      = 12,
    D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM2 = 13,
    D3D11_QUERY_SO_STATISTICS_STREAM3      = 14,
    D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM3 = 15,
} D3D11_QUERY;

typedef enum D3D11_QUERY_MISC_FLAG {
    D3D11_QUERY_MISC_PREDICATEHINT = 0x1,
} D3D11_QUERY_MISC_FLAG;

typedef enum D3D11_COUNTER {
    D3D11_COUNTER_DEVICE_DEPENDENT_0 = 0x40000000,
} D3D11_COUNTER;

typedef enum D3D11_COUNTER_TYPE {
    D3D11_COUNTER_TYPE_FLOAT32 = 0,
    D3D11_COUNTER_TYPE_UINT16  = 1,
    D3D11_COUNTER_TYPE_UINT32  = 2,
    D3D11_COUNTER_TYPE_UINT64  = 3,
} D3D11_COUNTER_TYPE;

typedef enum D3D11_STANDARD_MULTISAMPLE_QUALITY_LEVELS {
    D3D11_STANDARD_MULTISAMPLE_PATTERN = 0xffffffff,
    D3D11_CENTER_MULTISAMPLE_PATTERN   = 0xfffffffe,
} D3D11_STANDARD_MULTISAMPLE_QUALITY_LEVELS;

typedef enum D3D11_DEVICE_CONTEXT_TYPE {
    D3D11_DEVICE_CONTEXT_IMMEDIATE = 0,
    D3D11_DEVICE_CONTEXT_DEFERRED  = 1,
} D3D11_DEVICE_CONTEXT_TYPE;

typedef enum D3D11_CLEAR_FLAG {
    D3D11_CLEAR_DEPTH   = 0x1,
    D3D11_CLEAR_STENCIL = 0x2,
} D3D11_CLEAR_FLAG;

typedef enum D3D11_COPY_FLAGS {
    D3D11_COPY_NO_OVERWRITE = 0x1,
    D3D11_COPY_DISCARD      = 0x2,
} D3D11_COPY_FLAGS;

typedef enum D3D11_RAISE_FLAG {
    D3D11_RAISE_FLAG_DRIVER_INTERNAL_ERROR = 0x1,
} D3D11_RAISE_FLAG;

typedef enum D3D11_CREATE_DEVICE_FLAG {
    D3D11_CREATE_DEVICE_SINGLETHREADED                          = 0x1,
    D3D11_CREATE_DEVICE_DEBUG                                   = 0x2,
    D3D11_CREATE_DEVICE_SWITCH_TO_REF                           = 0x4,
    D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS = 0x8,
    D3D11_CREATE_DEVICE_BGRA_SUPPORT                            = 0x20,
    D3D11_CREATE_DEVICE_DEBUGGABLE                              = 0x40,
    D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY = 0x80,
    D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT                     = 0x100,
    D3D11_CREATE_DEVICE_VIDEO_SUPPORT                           = 0x800,
} D3D11_CREATE_DEVICE_FLAG;

typedef enum D3D11_TEXTURECUBE_FACE {
    D3D11_TEXTURECUBE_FACE_POSITIVE_X = 0,
    D3D11_TEXTURECUBE_FACE_NEGATIVE_X = 1,
    D3D11_TEXTURECUBE_FACE_POSITIVE_Y = 2,
    D3D11_TEXTURECUBE_FACE_NEGATIVE_Y = 3,
    D3D11_TEXTURECUBE_FACE_POSITIVE_Z = 4,
    D3D11_TEXTURECUBE_FACE_NEGATIVE_Z = 5,
} D3D11_TEXTURECUBE_FACE;

typedef enum D3D11_UAV_FLAG {
    D3D11_BUFFER_UAV_FLAG_RAW     = 0x1,
    D3D11_BUFFER_UAV_FLAG_APPEND  = 0x2,
    D3D11_BUFFER_UAV_FLAG_COUNTER = 0x4,
} D3D11_UAV_FLAG;



typedef enum D3D11_RTV_DIMENSION {
    D3D11_RTV_DIMENSION_UNKNOWN          = 0,
    D3D11_RTV_DIMENSION_BUFFER           = 1,
    D3D11_RTV_DIMENSION_TEXTURE1D        = 2,
    D3D11_RTV_DIMENSION_TEXTURE1DARRAY   = 3,
    D3D11_RTV_DIMENSION_TEXTURE2D        = 4,
    D3D11_RTV_DIMENSION_TEXTURE2DARRAY   = 5,
    D3D11_RTV_DIMENSION_TEXTURE2DMS      = 6,
    D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY = 7,
    D3D11_RTV_DIMENSION_TEXTURE3D        = 8,
} D3D11_RTV_DIMENSION;

typedef enum D3D11_DSV_DIMENSION {
    D3D11_DSV_DIMENSION_UNKNOWN           = 0,
    D3D11_DSV_DIMENSION_TEXTURE1D         = 1,
    D3D11_DSV_DIMENSION_TEXTURE1DARRAY    = 2,
    D3D11_DSV_DIMENSION_TEXTURE2D         = 3,
    D3D11_DSV_DIMENSION_TEXTURE2DARRAY    = 4,
    D3D11_DSV_DIMENSION_TEXTURE2DMS       = 5,
    D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY  = 6,
} D3D11_DSV_DIMENSION;

typedef enum D3D11_UAV_DIMENSION {
    D3D11_UAV_DIMENSION_UNKNOWN        = 0,
    D3D11_UAV_DIMENSION_BUFFER         = 1,
    D3D11_UAV_DIMENSION_TEXTURE1D      = 2,
    D3D11_UAV_DIMENSION_TEXTURE1DARRAY = 3,
    D3D11_UAV_DIMENSION_TEXTURE2D      = 4,
    D3D11_UAV_DIMENSION_TEXTURE2DARRAY = 5,
    D3D11_UAV_DIMENSION_TEXTURE3D      = 8,
} D3D11_UAV_DIMENSION;

typedef enum D3D11_DSV_FLAG {
    D3D11_DSV_READ_ONLY_DEPTH   = 0x1,
    D3D11_DSV_READ_ONLY_STENCIL = 0x2,
} D3D11_DSV_FLAG;

typedef enum D3D11_ASYNC_GETDATA_FLAG {
    D3D11_ASYNC_GETDATA_DONOTFLUSH = 0x1,
} D3D11_ASYNC_GETDATA_FLAG;

typedef enum D3D11_FORMAT_SUPPORT {
    D3D11_FORMAT_SUPPORT_BUFFER                      = 0x1,
    D3D11_FORMAT_SUPPORT_IA_VERTEX_BUFFER            = 0x2,
    D3D11_FORMAT_SUPPORT_IA_INDEX_BUFFER             = 0x4,
    D3D11_FORMAT_SUPPORT_SO_BUFFER                   = 0x8,
    D3D11_FORMAT_SUPPORT_TEXTURE1D                   = 0x10,
    D3D11_FORMAT_SUPPORT_TEXTURE2D                   = 0x20,
    D3D11_FORMAT_SUPPORT_TEXTURE3D                   = 0x40,
    D3D11_FORMAT_SUPPORT_TEXTURECUBE                 = 0x80,
    D3D11_FORMAT_SUPPORT_SHADER_LOAD                 = 0x100,
    D3D11_FORMAT_SUPPORT_SHADER_SAMPLE               = 0x200,
    D3D11_FORMAT_SUPPORT_SHADER_SAMPLE_COMPARISON    = 0x400,
    D3D11_FORMAT_SUPPORT_SHADER_SAMPLE_MONO_TEXT     = 0x800,
    D3D11_FORMAT_SUPPORT_MIP                         = 0x1000,
    D3D11_FORMAT_SUPPORT_MIP_AUTOGEN                 = 0x2000,
    D3D11_FORMAT_SUPPORT_RENDER_TARGET               = 0x4000,
    D3D11_FORMAT_SUPPORT_BLENDABLE                   = 0x8000,
    D3D11_FORMAT_SUPPORT_DEPTH_STENCIL               = 0x10000,
    D3D11_FORMAT_SUPPORT_CPU_LOCKABLE                = 0x20000,
    D3D11_FORMAT_SUPPORT_MULTISAMPLE_RESOLVE         = 0x40000,
    D3D11_FORMAT_SUPPORT_DISPLAY                     = 0x80000,
    D3D11_FORMAT_SUPPORT_CAST_WITHIN_BIT_LAYOUT      = 0x100000,
    D3D11_FORMAT_SUPPORT_MULTISAMPLE_RENDERTARGET    = 0x200000,
    D3D11_FORMAT_SUPPORT_MULTISAMPLE_LOAD            = 0x400000,
    D3D11_FORMAT_SUPPORT_SHADER_GATHER               = 0x800000,
    D3D11_FORMAT_SUPPORT_BACK_BUFFER_CAST            = 0x1000000,
    D3D11_FORMAT_SUPPORT_TYPED_UNORDERED_ACCESS_VIEW = 0x2000000,
    D3D11_FORMAT_SUPPORT_SHADER_GATHER_COMPARISON    = 0x4000000,
    D3D11_FORMAT_SUPPORT_DECODER_OUTPUT              = 0x8000000,
    D3D11_FORMAT_SUPPORT_VIDEO_PROCESSOR_OUTPUT      = 0x10000000,
    D3D11_FORMAT_SUPPORT_VIDEO_PROCESSOR_INPUT       = 0x20000000,
    D3D11_FORMAT_SUPPORT_VIDEO_ENCODER               = 0x40000000,
} D3D11_FORMAT_SUPPORT;

typedef enum D3D11_FORMAT_SUPPORT2 {
    D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_ADD                       = 0x1,
    D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_BITWISE_OPS               = 0x2,
    D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_COMPARE_STORE_OR_COMPARE_EXCHANGE = 0x4,
    D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_EXCHANGE                  = 0x8,
    D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_SIGNED_MIN_OR_MAX         = 0x10,
    D3D11_FORMAT_SUPPORT2_UAV_ATOMIC_UNSIGNED_MIN_OR_MAX       = 0x20,
    D3D11_FORMAT_SUPPORT2_UAV_TYPED_LOAD                       = 0x40,
    D3D11_FORMAT_SUPPORT2_UAV_TYPED_STORE                      = 0x80,
    D3D11_FORMAT_SUPPORT2_OUTPUT_MERGER_LOGIC_OP               = 0x100,
    D3D11_FORMAT_SUPPORT2_TILED                                = 0x200,
    D3D11_FORMAT_SUPPORT2_SHAREABLE                            = 0x400,
    D3D11_FORMAT_SUPPORT2_MULTIPLANE_OVERLAY                   = 0x4000,
} D3D11_FORMAT_SUPPORT2;

typedef enum D3D11_FEATURE {
    D3D11_FEATURE_THREADING                       = 0,
    D3D11_FEATURE_DOUBLES                         = 1,
    D3D11_FEATURE_FORMAT_SUPPORT                  = 2,
    D3D11_FEATURE_FORMAT_SUPPORT2                 = 3,
    D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS        = 4,
    D3D11_FEATURE_D3D11_OPTIONS                   = 5,
    D3D11_FEATURE_ARCHITECTURE_INFO               = 6,
    D3D11_FEATURE_D3D9_OPTIONS                    = 7,
    D3D11_FEATURE_SHADER_MIN_PRECISION_SUPPORT    = 8,
    D3D11_FEATURE_D3D9_SHADOW_SUPPORT             = 9,
    D3D11_FEATURE_D3D11_OPTIONS1                  = 10,
    D3D11_FEATURE_D3D9_SIMPLE_INSTANCING_SUPPORT  = 11,
    D3D11_FEATURE_MARKER_SUPPORT                  = 12,
    D3D11_FEATURE_D3D9_OPTIONS1                   = 13,
    D3D11_FEATURE_D3D11_OPTIONS2                  = 14,
    D3D11_FEATURE_D3D11_OPTIONS3                  = 15,
    D3D11_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT     = 16,
    D3D11_FEATURE_D3D11_OPTIONS4                  = 17,
    D3D11_FEATURE_SHADER_CACHE                    = 18,
    D3D11_FEATURE_D3D11_OPTIONS5                  = 19,
} D3D11_FEATURE;

typedef enum D3D11_LOGIC_OP {
    D3D11_LOGIC_OP_CLEAR         = 0,
    D3D11_LOGIC_OP_SET           = 1,
    D3D11_LOGIC_OP_COPY          = 2,
    D3D11_LOGIC_OP_COPY_INVERTED = 3,
    D3D11_LOGIC_OP_NOOP          = 4,
    D3D11_LOGIC_OP_INVERT        = 5,
    D3D11_LOGIC_OP_AND           = 6,
    D3D11_LOGIC_OP_NAND          = 7,
    D3D11_LOGIC_OP_OR            = 8,
    D3D11_LOGIC_OP_NOR           = 9,
    D3D11_LOGIC_OP_XOR           = 10,
    D3D11_LOGIC_OP_EQUIV         = 11,
    D3D11_LOGIC_OP_AND_REVERSE   = 12,
    D3D11_LOGIC_OP_AND_INVERTED  = 13,
    D3D11_LOGIC_OP_OR_REVERSE    = 14,
    D3D11_LOGIC_OP_OR_INVERTED   = 15,
} D3D11_LOGIC_OP;

typedef enum D3D11_CONSERVATIVE_RASTERIZATION_MODE {
    D3D11_CONSERVATIVE_RASTERIZATION_MODE_OFF = 0,
    D3D11_CONSERVATIVE_RASTERIZATION_MODE_ON  = 1,
} D3D11_CONSERVATIVE_RASTERIZATION_MODE;

typedef enum D3D11_SHADER_MIN_PRECISION_SUPPORT {
    D3D11_SHADER_MIN_PRECISION_10_BIT = 0x1,
    D3D11_SHADER_MIN_PRECISION_16_BIT = 0x2,
} D3D11_SHADER_MIN_PRECISION_SUPPORT;

typedef enum D3D11_TILED_RESOURCES_TIER {
    D3D11_TILED_RESOURCES_NOT_SUPPORTED = 0,
    D3D11_TILED_RESOURCES_TIER_1        = 1,
    D3D11_TILED_RESOURCES_TIER_2        = 2,
    D3D11_TILED_RESOURCES_TIER_3        = 3,
} D3D11_TILED_RESOURCES_TIER;

typedef enum D3D11_CONSERVATIVE_RASTERIZATION_TIER {
    D3D11_CONSERVATIVE_RASTERIZATION_NOT_SUPPORTED = 0,
    D3D11_CONSERVATIVE_RASTERIZATION_TIER_1        = 1,
    D3D11_CONSERVATIVE_RASTERIZATION_TIER_2        = 2,
    D3D11_CONSERVATIVE_RASTERIZATION_TIER_3        = 3,
} D3D11_CONSERVATIVE_RASTERIZATION_TIER;

/* =========================================================================
 * Structures
 * ========================================================================= */
typedef struct D3D11_BUFFER_DESC {
    UINT        ByteWidth;
    D3D11_USAGE Usage;
    UINT        BindFlags;
    UINT        CPUAccessFlags;
    UINT        MiscFlags;
    UINT        StructureByteStride;
} D3D11_BUFFER_DESC;

typedef struct D3D11_TEXTURE1D_DESC {
    UINT        Width;
    UINT        MipLevels;
    UINT        ArraySize;
    DXGI_FORMAT Format;
    D3D11_USAGE Usage;
    UINT        BindFlags;
    UINT        CPUAccessFlags;
    UINT        MiscFlags;
} D3D11_TEXTURE1D_DESC;

typedef struct D3D11_TEXTURE2D_DESC {
    UINT             Width;
    UINT             Height;
    UINT             MipLevels;
    UINT             ArraySize;
    DXGI_FORMAT      Format;
    DXGI_SAMPLE_DESC SampleDesc;
    D3D11_USAGE      Usage;
    UINT             BindFlags;
    UINT             CPUAccessFlags;
    UINT             MiscFlags;
} D3D11_TEXTURE2D_DESC;

typedef struct D3D11_TEXTURE3D_DESC {
    UINT        Width;
    UINT        Height;
    UINT        Depth;
    UINT        MipLevels;
    DXGI_FORMAT Format;
    D3D11_USAGE Usage;
    UINT        BindFlags;
    UINT        CPUAccessFlags;
    UINT        MiscFlags;
} D3D11_TEXTURE3D_DESC;

typedef struct D3D11_SUBRESOURCE_DATA {
    const void* pSysMem;
    UINT        SysMemPitch;
    UINT        SysMemSlicePitch;
} D3D11_SUBRESOURCE_DATA;

typedef struct D3D11_MAPPED_SUBRESOURCE {
    void* pData;
    UINT  RowPitch;
    UINT  DepthPitch;
} D3D11_MAPPED_SUBRESOURCE;

typedef struct D3D11_BOX {
    UINT left;
    UINT top;
    UINT front;
    UINT right;
    UINT bottom;
    UINT back;
} D3D11_BOX;

typedef struct D3D11_VIEWPORT {
    FLOAT TopLeftX;
    FLOAT TopLeftY;
    FLOAT Width;
    FLOAT Height;
    FLOAT MinDepth;
    FLOAT MaxDepth;
} D3D11_VIEWPORT;

typedef struct D3D11_RECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} D3D11_RECT;

typedef struct D3D11_INPUT_ELEMENT_DESC {
    LPCSTR                     SemanticName;
    UINT                       SemanticIndex;
    DXGI_FORMAT                Format;
    UINT                       InputSlot;
    UINT                       AlignedByteOffset;
    D3D11_INPUT_CLASSIFICATION InputSlotClass;
    UINT                       InstanceDataStepRate;
} D3D11_INPUT_ELEMENT_DESC;

typedef struct D3D11_SO_DECLARATION_ENTRY {
    UINT   Stream;
    LPCSTR SemanticName;
    UINT   SemanticIndex;
    BYTE   StartComponent;
    BYTE   ComponentCount;
    BYTE   OutputSlot;
} D3D11_SO_DECLARATION_ENTRY;

typedef struct D3D11_RASTERIZER_DESC {
    D3D11_FILL_MODE FillMode;
    D3D11_CULL_MODE CullMode;
    BOOL            FrontCounterClockwise;
    INT             DepthBias;
    FLOAT           DepthBiasClamp;
    FLOAT           SlopeScaledDepthBias;
    BOOL            DepthClipEnable;
    BOOL            ScissorEnable;
    BOOL            MultisampleEnable;
    BOOL            AntialiasedLineEnable;
} D3D11_RASTERIZER_DESC;

typedef struct D3D11_RASTERIZER_DESC1 {
    D3D11_FILL_MODE FillMode;
    D3D11_CULL_MODE CullMode;
    BOOL            FrontCounterClockwise;
    INT             DepthBias;
    FLOAT           DepthBiasClamp;
    FLOAT           SlopeScaledDepthBias;
    BOOL            DepthClipEnable;
    BOOL            ScissorEnable;
    BOOL            MultisampleEnable;
    BOOL            AntialiasedLineEnable;
    UINT            ForcedSampleCount;
} D3D11_RASTERIZER_DESC1;

typedef struct D3D11_RASTERIZER_DESC2 {
    D3D11_FILL_MODE                       FillMode;
    D3D11_CULL_MODE                       CullMode;
    BOOL                                  FrontCounterClockwise;
    INT                                   DepthBias;
    FLOAT                                 DepthBiasClamp;
    FLOAT                                 SlopeScaledDepthBias;
    BOOL                                  DepthClipEnable;
    BOOL                                  ScissorEnable;
    BOOL                                  MultisampleEnable;
    BOOL                                  AntialiasedLineEnable;
    UINT                                  ForcedSampleCount;
    D3D11_CONSERVATIVE_RASTERIZATION_MODE ConservativeRaster;
} D3D11_RASTERIZER_DESC2;

typedef struct D3D11_DEPTH_STENCILOP_DESC {
    D3D11_STENCIL_OP      StencilFailOp;
    D3D11_STENCIL_OP      StencilDepthFailOp;
    D3D11_STENCIL_OP      StencilPassOp;
    D3D11_COMPARISON_FUNC StencilFunc;
} D3D11_DEPTH_STENCILOP_DESC;

typedef struct D3D11_DEPTH_STENCIL_DESC {
    BOOL                       DepthEnable;
    D3D11_DEPTH_WRITE_MASK     DepthWriteMask;
    D3D11_COMPARISON_FUNC      DepthFunc;
    BOOL                       StencilEnable;
    UINT8                      StencilReadMask;
    UINT8                      StencilWriteMask;
    D3D11_DEPTH_STENCILOP_DESC FrontFace;
    D3D11_DEPTH_STENCILOP_DESC BackFace;
} D3D11_DEPTH_STENCIL_DESC;

typedef struct D3D11_RENDER_TARGET_BLEND_DESC {
    BOOL           BlendEnable;
    D3D11_BLEND    SrcBlend;
    D3D11_BLEND    DestBlend;
    D3D11_BLEND_OP BlendOp;
    D3D11_BLEND    SrcBlendAlpha;
    D3D11_BLEND    DestBlendAlpha;
    D3D11_BLEND_OP BlendOpAlpha;
    UINT8          RenderTargetWriteMask;
} D3D11_RENDER_TARGET_BLEND_DESC;

typedef struct D3D11_RENDER_TARGET_BLEND_DESC1 {
    BOOL           BlendEnable;
    BOOL           LogicOpEnable;
    D3D11_BLEND    SrcBlend;
    D3D11_BLEND    DestBlend;
    D3D11_BLEND_OP BlendOp;
    D3D11_BLEND    SrcBlendAlpha;
    D3D11_BLEND    DestBlendAlpha;
    D3D11_BLEND_OP BlendOpAlpha;
    D3D11_LOGIC_OP LogicOp;
    UINT8          RenderTargetWriteMask;
} D3D11_RENDER_TARGET_BLEND_DESC1;

typedef struct D3D11_BLEND_DESC {
    BOOL                          AlphaToCoverageEnable;
    BOOL                          IndependentBlendEnable;
    D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];
} D3D11_BLEND_DESC;

typedef struct D3D11_BLEND_DESC1 {
    BOOL                           AlphaToCoverageEnable;
    BOOL                           IndependentBlendEnable;
    D3D11_RENDER_TARGET_BLEND_DESC1 RenderTarget[8];
} D3D11_BLEND_DESC1;

typedef struct D3D11_SAMPLER_DESC {
    D3D11_FILTER               Filter;
    D3D11_TEXTURE_ADDRESS_MODE AddressU;
    D3D11_TEXTURE_ADDRESS_MODE AddressV;
    D3D11_TEXTURE_ADDRESS_MODE AddressW;
    FLOAT                      MipLODBias;
    UINT                       MaxAnisotropy;
    D3D11_COMPARISON_FUNC      ComparisonFunc;
    FLOAT                      BorderColor[4];
    FLOAT                      MinLOD;
    FLOAT                      MaxLOD;
} D3D11_SAMPLER_DESC;

typedef struct D3D11_QUERY_DESC {
    D3D11_QUERY Query;
    UINT        MiscFlags;
} D3D11_QUERY_DESC;

typedef struct D3D11_COUNTER_DESC {
    D3D11_COUNTER Counter;
    UINT          MiscFlags;
} D3D11_COUNTER_DESC;

typedef struct D3D11_COUNTER_INFO {
    D3D11_COUNTER LastDeviceDependentCounter;
    UINT          NumSimultaneousCounters;
    UINT8         NumDetectableParallelUnits;
} D3D11_COUNTER_INFO;

typedef struct D3D11_QUERY_DATA_TIMESTAMP_DISJOINT {
    UINT64 Frequency;
    BOOL   Disjoint;
} D3D11_QUERY_DATA_TIMESTAMP_DISJOINT;

typedef struct D3D11_QUERY_DATA_PIPELINE_STATISTICS {
    UINT64 IAVertices;
    UINT64 IAPrimitives;
    UINT64 VSInvocations;
    UINT64 GSInvocations;
    UINT64 GSPrimitives;
    UINT64 CInvocations;
    UINT64 CPrimitives;
    UINT64 PSInvocations;
    UINT64 HSInvocations;
    UINT64 DSInvocations;
    UINT64 CSInvocations;
} D3D11_QUERY_DATA_PIPELINE_STATISTICS;

typedef struct D3D11_QUERY_DATA_SO_STATISTICS {
    UINT64 NumPrimitivesWritten;
    UINT64 PrimitivesStorageNeeded;
} D3D11_QUERY_DATA_SO_STATISTICS;

typedef struct D3D11_CLASS_INSTANCE_DESC {
    UINT InstanceId;
    UINT InstanceIndex;
    UINT TypeId;
    UINT ConstantBuffer;
    UINT BaseConstantBufferOffset;
    UINT BaseTexture;
    UINT BaseSampler;
    BOOL Created;
} D3D11_CLASS_INSTANCE_DESC;

typedef struct D3D11_DRAW_INSTANCED_INDIRECT_ARGS {
    UINT VertexCountPerInstance;
    UINT InstanceCount;
    UINT StartVertexLocation;
    UINT StartInstanceLocation;
} D3D11_DRAW_INSTANCED_INDIRECT_ARGS;

typedef struct D3D11_DRAW_INDEXED_INSTANCED_INDIRECT_ARGS {
    UINT IndexCountPerInstance;
    UINT InstanceCount;
    UINT StartIndexLocation;
    INT  BaseVertexLocation;
    UINT StartInstanceLocation;
} D3D11_DRAW_INDEXED_INSTANCED_INDIRECT_ARGS;

typedef struct D3D11_DISPATCH_INDIRECT_ARGS {
    UINT ThreadGroupCountX;
    UINT ThreadGroupCountY;
    UINT ThreadGroupCountZ;
} D3D11_DISPATCH_INDIRECT_ARGS;

/* Feature data structs */
typedef struct D3D11_FEATURE_DATA_THREADING {
    BOOL DriverConcurrentCreates;
    BOOL DriverCommandLists;
} D3D11_FEATURE_DATA_THREADING;

typedef struct D3D11_FEATURE_DATA_DOUBLES {
    BOOL DoublePrecisionFloatShaderOps;
} D3D11_FEATURE_DATA_DOUBLES;

typedef struct D3D11_FEATURE_DATA_FORMAT_SUPPORT {
    DXGI_FORMAT InFormat;
    UINT        OutFormatSupport;
} D3D11_FEATURE_DATA_FORMAT_SUPPORT;

typedef struct D3D11_FEATURE_DATA_FORMAT_SUPPORT2 {
    DXGI_FORMAT InFormat;
    UINT        OutFormatSupport2;
} D3D11_FEATURE_DATA_FORMAT_SUPPORT2;

typedef struct D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS {
    BOOL ComputeShaders_Plus_RawAndStructuredBuffers_Via_Shader_4_x;
} D3D11_FEATURE_DATA_D3D10_X_HARDWARE_OPTIONS;

typedef struct D3D11_FEATURE_DATA_D3D11_OPTIONS {
    BOOL OutputMergerLogicOp;
    BOOL UAVOnlyRenderingForcedSampleCount;
    BOOL DiscardAPIsSeenByDriver;
    BOOL FlagsForUpdateAndCopySeenByDriver;
    BOOL ClearView;
    BOOL CopyWithOverlap;
    BOOL ConstantBufferPartialUpdate;
    BOOL ConstantBufferOffsetting;
    BOOL MapNoOverwriteOnDynamicConstantBuffer;
    BOOL MapNoOverwriteOnDynamicBufferSRV;
    BOOL MultisampleRTVWithForcedSampleCountOne;
    BOOL SAD4ShaderInstructions;
    BOOL ExtendedDoublesShaderInstructions;
    BOOL ExtendedResourceSharing;
} D3D11_FEATURE_DATA_D3D11_OPTIONS;

typedef struct D3D11_FEATURE_DATA_ARCHITECTURE_INFO {
    BOOL TileBasedDeferredRenderer;
} D3D11_FEATURE_DATA_ARCHITECTURE_INFO;

typedef struct D3D11_FEATURE_DATA_D3D11_OPTIONS1 {
    D3D11_TILED_RESOURCES_TIER TiledResourcesTier;
    BOOL                       MinMaxFiltering;
    BOOL                       ClearViewAlsoSupportsDepthOnlyFormats;
    BOOL                       MapOnDefaultBuffers;
} D3D11_FEATURE_DATA_D3D11_OPTIONS1;

typedef struct D3D11_FEATURE_DATA_D3D11_OPTIONS2 {
    BOOL                                    PSSpecifiedStencilRefSupported;
    BOOL                                    TypedUAVLoadAdditionalFormats;
    BOOL                                    ROVsSupported;
    D3D11_CONSERVATIVE_RASTERIZATION_TIER   ConservativeRasterizationTier;
    D3D11_TILED_RESOURCES_TIER              TiledResourcesTier;
    BOOL                                    MapOnDefaultTextures;
    BOOL                                    StandardSwizzle;
    BOOL                                    UnifiedMemoryArchitecture;
} D3D11_FEATURE_DATA_D3D11_OPTIONS2;

typedef struct D3D11_FEATURE_DATA_D3D11_OPTIONS3 {
    BOOL VPAndRTArrayIndexFromAnyShaderFeedingRasterizer;
} D3D11_FEATURE_DATA_D3D11_OPTIONS3;

typedef struct D3D11_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT {
    UINT MaxGPUVirtualAddressBitsPerResource;
    UINT MaxGPUVirtualAddressBitsPerProcess;
} D3D11_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT;

typedef struct D3D11_FEATURE_DATA_SHADER_MIN_PRECISION_SUPPORT {
    UINT PixelShaderMinPrecision;
    UINT AllOtherShaderStagesMinPrecision;
} D3D11_FEATURE_DATA_SHADER_MIN_PRECISION_SUPPORT;

typedef struct D3D11_FEATURE_DATA_D3D9_SHADOW_SUPPORT {
    BOOL SupportsDepthAsTextureWithLessEqualComparisonFilter;
} D3D11_FEATURE_DATA_D3D9_SHADOW_SUPPORT;

/* SRV sub-structs */
typedef struct D3D11_BUFFER_SRV  { union { UINT FirstElement; UINT ElementOffset; }; union { UINT NumElements; UINT ElementWidth; }; } D3D11_BUFFER_SRV;
typedef struct D3D11_BUFFEREX_SRV { UINT FirstElement; UINT NumElements; UINT Flags; } D3D11_BUFFEREX_SRV;
typedef struct D3D11_TEX1D_SRV         { UINT MostDetailedMip; UINT MipLevels; } D3D11_TEX1D_SRV;
typedef struct D3D11_TEX1D_ARRAY_SRV   { UINT MostDetailedMip; UINT MipLevels; UINT FirstArraySlice; UINT ArraySize; } D3D11_TEX1D_ARRAY_SRV;
typedef struct D3D11_TEX2D_SRV         { UINT MostDetailedMip; UINT MipLevels; } D3D11_TEX2D_SRV;
typedef struct D3D11_TEX2D_ARRAY_SRV   { UINT MostDetailedMip; UINT MipLevels; UINT FirstArraySlice; UINT ArraySize; } D3D11_TEX2D_ARRAY_SRV;
typedef struct D3D11_TEX2DMS_SRV       { UINT UnusedField_NothingToDefine; } D3D11_TEX2DMS_SRV;
typedef struct D3D11_TEX2DMS_ARRAY_SRV { UINT FirstArraySlice; UINT ArraySize; } D3D11_TEX2DMS_ARRAY_SRV;
typedef struct D3D11_TEX3D_SRV         { UINT MostDetailedMip; UINT MipLevels; } D3D11_TEX3D_SRV;
typedef struct D3D11_TEXCUBE_SRV       { UINT MostDetailedMip; UINT MipLevels; } D3D11_TEXCUBE_SRV;
typedef struct D3D11_TEXCUBE_ARRAY_SRV { UINT MostDetailedMip; UINT MipLevels; UINT First2DArrayFace; UINT NumCubes; } D3D11_TEXCUBE_ARRAY_SRV;

typedef struct D3D11_SHADER_RESOURCE_VIEW_DESC {
    DXGI_FORMAT          Format;
    D3D11_SRV_DIMENSION  ViewDimension;
    union {
        D3D11_BUFFER_SRV         Buffer;
        D3D11_TEX1D_SRV          Texture1D;
        D3D11_TEX1D_ARRAY_SRV    Texture1DArray;
        D3D11_TEX2D_SRV          Texture2D;
        D3D11_TEX2D_ARRAY_SRV    Texture2DArray;
        D3D11_TEX2DMS_SRV        Texture2DMS;
        D3D11_TEX2DMS_ARRAY_SRV  Texture2DMSArray;
        D3D11_TEX3D_SRV          Texture3D;
        D3D11_TEXCUBE_SRV        TextureCube;
        D3D11_TEXCUBE_ARRAY_SRV  TextureCubeArray;
        D3D11_BUFFEREX_SRV       BufferEx;
    };
} D3D11_SHADER_RESOURCE_VIEW_DESC;

/* RTV sub-structs */
typedef struct D3D11_BUFFER_RTV          { union { UINT FirstElement; UINT ElementOffset; }; union { UINT NumElements; UINT ElementWidth; }; } D3D11_BUFFER_RTV;
typedef struct D3D11_TEX1D_RTV           { UINT MipSlice; } D3D11_TEX1D_RTV;
typedef struct D3D11_TEX1D_ARRAY_RTV     { UINT MipSlice; UINT FirstArraySlice; UINT ArraySize; } D3D11_TEX1D_ARRAY_RTV;
typedef struct D3D11_TEX2D_RTV           { UINT MipSlice; } D3D11_TEX2D_RTV;
typedef struct D3D11_TEX2D_ARRAY_RTV     { UINT MipSlice; UINT FirstArraySlice; UINT ArraySize; } D3D11_TEX2D_ARRAY_RTV;
typedef struct D3D11_TEX2DMS_RTV         { UINT UnusedField_NothingToDefine; } D3D11_TEX2DMS_RTV;
typedef struct D3D11_TEX2DMS_ARRAY_RTV   { UINT FirstArraySlice; UINT ArraySize; } D3D11_TEX2DMS_ARRAY_RTV;
typedef struct D3D11_TEX3D_RTV           { UINT MipSlice; UINT FirstWSlice; UINT WSize; } D3D11_TEX3D_RTV;

typedef struct D3D11_RENDER_TARGET_VIEW_DESC {
    DXGI_FORMAT         Format;
    D3D11_RTV_DIMENSION ViewDimension;
    union {
        D3D11_BUFFER_RTV          Buffer;
        D3D11_TEX1D_RTV           Texture1D;
        D3D11_TEX1D_ARRAY_RTV     Texture1DArray;
        D3D11_TEX2D_RTV           Texture2D;
        D3D11_TEX2D_ARRAY_RTV     Texture2DArray;
        D3D11_TEX2DMS_RTV         Texture2DMS;
        D3D11_TEX2DMS_ARRAY_RTV   Texture2DMSArray;
        D3D11_TEX3D_RTV           Texture3D;
    };
} D3D11_RENDER_TARGET_VIEW_DESC;

/* DSV sub-structs */
typedef struct D3D11_TEX1D_DSV           { UINT MipSlice; } D3D11_TEX1D_DSV;
typedef struct D3D11_TEX1D_ARRAY_DSV     { UINT MipSlice; UINT FirstArraySlice; UINT ArraySize; } D3D11_TEX1D_ARRAY_DSV;
typedef struct D3D11_TEX2D_DSV           { UINT MipSlice; } D3D11_TEX2D_DSV;
typedef struct D3D11_TEX2D_ARRAY_DSV     { UINT MipSlice; UINT FirstArraySlice; UINT ArraySize; } D3D11_TEX2D_ARRAY_DSV;
typedef struct D3D11_TEX2DMS_DSV         { UINT UnusedField_NothingToDefine; } D3D11_TEX2DMS_DSV;
typedef struct D3D11_TEX2DMS_ARRAY_DSV   { UINT FirstArraySlice; UINT ArraySize; } D3D11_TEX2DMS_ARRAY_DSV;

typedef struct D3D11_DEPTH_STENCIL_VIEW_DESC {
    DXGI_FORMAT         Format;
    D3D11_DSV_DIMENSION ViewDimension;
    UINT                Flags;
    union {
        D3D11_TEX1D_DSV         Texture1D;
        D3D11_TEX1D_ARRAY_DSV   Texture1DArray;
        D3D11_TEX2D_DSV         Texture2D;
        D3D11_TEX2D_ARRAY_DSV   Texture2DArray;
        D3D11_TEX2DMS_DSV       Texture2DMS;
        D3D11_TEX2DMS_ARRAY_DSV Texture2DMSArray;
    };
} D3D11_DEPTH_STENCIL_VIEW_DESC;

/* UAV sub-structs */
typedef struct D3D11_BUFFER_UAV          { UINT FirstElement; UINT NumElements; UINT Flags; } D3D11_BUFFER_UAV;
typedef struct D3D11_TEX1D_UAV           { UINT MipSlice; } D3D11_TEX1D_UAV;
typedef struct D3D11_TEX1D_ARRAY_UAV     { UINT MipSlice; UINT FirstArraySlice; UINT ArraySize; } D3D11_TEX1D_ARRAY_UAV;
typedef struct D3D11_TEX2D_UAV           { UINT MipSlice; } D3D11_TEX2D_UAV;
typedef struct D3D11_TEX2D_ARRAY_UAV     { UINT MipSlice; UINT FirstArraySlice; UINT ArraySize; } D3D11_TEX2D_ARRAY_UAV;
typedef struct D3D11_TEX3D_UAV           { UINT MipSlice; UINT FirstWSlice; UINT WSize; } D3D11_TEX3D_UAV;

typedef struct D3D11_UNORDERED_ACCESS_VIEW_DESC {
    DXGI_FORMAT         Format;
    D3D11_UAV_DIMENSION ViewDimension;
    union {
        D3D11_BUFFER_UAV        Buffer;
        D3D11_TEX1D_UAV         Texture1D;
        D3D11_TEX1D_ARRAY_UAV   Texture1DArray;
        D3D11_TEX2D_UAV         Texture2D;
        D3D11_TEX2D_ARRAY_UAV   Texture2DArray;
        D3D11_TEX3D_UAV         Texture3D;
    };
} D3D11_UNORDERED_ACCESS_VIEW_DESC;

typedef struct D3D11_COMMAND_LIST_DESC { UINT NodeMask; } D3D11_COMMAND_LIST_DESC;

/* =========================================================================
 * Forward declarations
 * ========================================================================= */
#ifdef __cplusplus

struct ID3D11Device;
struct ID3D11Device1;
struct ID3D11Device2;
struct ID3D11Device3;
struct ID3D11Device4;
struct ID3D11Device5;
struct ID3D11DeviceContext;
struct ID3D11DeviceContext1;
struct ID3D11DeviceContext2;
struct ID3D11DeviceContext3;
struct ID3D11DeviceContext4;
struct ID3D11DeviceChild;
struct ID3D11Resource;
struct ID3D11Buffer;
struct ID3D11Texture1D;
struct ID3D11Texture2D;
struct ID3D11Texture2D1;
struct ID3D11Texture3D;
struct ID3D11Texture3D1;
struct ID3D11View;
struct ID3D11ShaderResourceView;
struct ID3D11ShaderResourceView1;
struct ID3D11RenderTargetView;
struct ID3D11RenderTargetView1;
struct ID3D11DepthStencilView;
struct ID3D11UnorderedAccessView;
struct ID3D11UnorderedAccessView1;
struct ID3D11VertexShader;
struct ID3D11HullShader;
struct ID3D11DomainShader;
struct ID3D11GeometryShader;
struct ID3D11PixelShader;
struct ID3D11ComputeShader;
struct ID3D11InputLayout;
struct ID3D11BlendState;
struct ID3D11BlendState1;
struct ID3D11DepthStencilState;
struct ID3D11RasterizerState;
struct ID3D11RasterizerState1;
struct ID3D11RasterizerState2;
struct ID3D11SamplerState;
struct ID3D11Asynchronous;
struct ID3D11Query;
struct ID3D11Query1;
struct ID3D11Predicate;
struct ID3D11Counter;
struct ID3D11ClassInstance;
struct ID3D11ClassLinkage;
struct ID3D11CommandList;
struct ID3D11Multithread;
struct ID3DDeviceContextState;

/* =========================================================================
 * IUnknown
 * ========================================================================= */
 struct IUnknown;
/* =========================================================================
 * ID3D11DeviceChild
 * ========================================================================= */
struct ID3D11DeviceChild : public IUnknown {
    virtual void    STDMETHODCALLTYPE GetDevice(ID3D11Device** ppDevice) {}
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) {   }
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) {   }
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) {   }
};

/* =========================================================================
 * ID3D11Resource
 * ========================================================================= */
struct ID3D11Resource : public ID3D11DeviceChild {
    virtual void STDMETHODCALLTYPE GetType(D3D11_RESOURCE_DIMENSION* pResourceDimension) {}
    virtual void STDMETHODCALLTYPE SetEvictionPriority(UINT EvictionPriority) {}
    virtual UINT STDMETHODCALLTYPE GetEvictionPriority() { return 0; }
};

/* =========================================================================
 * Buffers & Textures
 * ========================================================================= */
struct ID3D11Buffer : public ID3D11Resource {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_BUFFER_DESC* pDesc) {}
};

struct ID3D11Texture1D : public ID3D11Resource {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_TEXTURE1D_DESC* pDesc) {}
};

struct ID3D11Texture2D : public ID3D11Resource {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_TEXTURE2D_DESC* pDesc) {}
};

struct ID3D11Texture2D1 : public ID3D11Texture2D {
    virtual void STDMETHODCALLTYPE GetDesc1(D3D11_TEXTURE2D_DESC* pDesc) {}
};

struct ID3D11Texture3D : public ID3D11Resource {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_TEXTURE3D_DESC* pDesc) {}
};

struct ID3D11Texture3D1 : public ID3D11Texture3D {
    virtual void STDMETHODCALLTYPE GetDesc1(D3D11_TEXTURE3D_DESC* pDesc) {}
};

/* =========================================================================
 * Views
 * ========================================================================= */
struct ID3D11View : public ID3D11DeviceChild {
    virtual void STDMETHODCALLTYPE GetResource(ID3D11Resource** ppResource) {}
};

struct ID3D11ShaderResourceView : public ID3D11View {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc) {}
};

struct ID3D11ShaderResourceView1 : public ID3D11ShaderResourceView {
    virtual void STDMETHODCALLTYPE GetDesc1(D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc) {}
};

struct ID3D11RenderTargetView : public ID3D11View {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_RENDER_TARGET_VIEW_DESC* pDesc) {}
};

struct ID3D11RenderTargetView1 : public ID3D11RenderTargetView {
    virtual void STDMETHODCALLTYPE GetDesc1(D3D11_RENDER_TARGET_VIEW_DESC* pDesc) {}
};

struct ID3D11DepthStencilView : public ID3D11View {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc) {}
};

struct ID3D11UnorderedAccessView : public ID3D11View {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc) {}
};

struct ID3D11UnorderedAccessView1 : public ID3D11UnorderedAccessView {
    virtual void STDMETHODCALLTYPE GetDesc1(D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc) {}
};

/* =========================================================================
 * Shaders
 * ========================================================================= */
struct ID3D11VertexShader   : public ID3D11DeviceChild {};
struct ID3D11HullShader     : public ID3D11DeviceChild {};
struct ID3D11DomainShader   : public ID3D11DeviceChild {};
struct ID3D11GeometryShader : public ID3D11DeviceChild {};
struct ID3D11PixelShader    : public ID3D11DeviceChild {};
struct ID3D11ComputeShader  : public ID3D11DeviceChild {};
struct ID3D11InputLayout    : public ID3D11DeviceChild {};

/* =========================================================================
 * State objects
 * ========================================================================= */
struct ID3D11BlendState : public ID3D11DeviceChild {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_BLEND_DESC* pDesc) {}
};
struct ID3D11BlendState1 : public ID3D11BlendState {
    virtual void STDMETHODCALLTYPE GetDesc1(D3D11_BLEND_DESC1* pDesc) {}
};

struct ID3D11DepthStencilState : public ID3D11DeviceChild {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_DEPTH_STENCIL_DESC* pDesc) {}
};

struct ID3D11RasterizerState : public ID3D11DeviceChild {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_RASTERIZER_DESC* pDesc) {}
};
struct ID3D11RasterizerState1 : public ID3D11RasterizerState {
    virtual void STDMETHODCALLTYPE GetDesc1(D3D11_RASTERIZER_DESC1* pDesc) {}
};
struct ID3D11RasterizerState2 : public ID3D11RasterizerState1 {
    virtual void STDMETHODCALLTYPE GetDesc2(D3D11_RASTERIZER_DESC2* pDesc) {}
};

struct ID3D11SamplerState : public ID3D11DeviceChild {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_SAMPLER_DESC* pDesc) {}
};

/* =========================================================================
 * Async / Query / Predicate / Counter
 * ========================================================================= */
struct ID3D11Asynchronous : public ID3D11DeviceChild {
    virtual UINT STDMETHODCALLTYPE GetDataSize() { return 0; }
};

struct ID3D11Query : public ID3D11Asynchronous {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_QUERY_DESC* pDesc) {}
};

struct ID3D11Query1 : public ID3D11Query {
    virtual void STDMETHODCALLTYPE GetDesc1(D3D11_QUERY_DESC* pDesc) {}
};

struct ID3D11Predicate  : public ID3D11Query {};
struct ID3D11Counter    : public ID3D11Asynchronous {
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_COUNTER_DESC* pDesc) {}
};

/* =========================================================================
 * Class linkage
 * ========================================================================= */
struct ID3D11ClassInstance : public ID3D11DeviceChild {
    virtual void STDMETHODCALLTYPE GetClassLinkage(ID3D11ClassLinkage** ppLinkage) {}
    virtual void STDMETHODCALLTYPE GetDesc(D3D11_CLASS_INSTANCE_DESC* pDesc) {}
    virtual void STDMETHODCALLTYPE GetInstanceName(LPSTR pInstanceName, SIZE_T* pBufferLength) {}
    virtual void STDMETHODCALLTYPE GetTypeName(LPSTR pTypeName, SIZE_T* pBufferLength) {}
};

struct ID3D11ClassLinkage : public ID3D11DeviceChild {
    virtual HRESULT STDMETHODCALLTYPE GetClassInstance(LPCSTR pClassInstanceName, UINT InstanceIndex, ID3D11ClassInstance** ppInstance) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateClassInstance(LPCSTR pClassTypeName, UINT ConstantBufferOffset, UINT ConstantVectorOffset, UINT TextureOffset, UINT SamplerOffset, ID3D11ClassInstance** ppInstance) {   }
};

/* =========================================================================
 * CommandList
 * ========================================================================= */
struct ID3D11CommandList : public ID3D11DeviceChild {
    virtual UINT STDMETHODCALLTYPE GetContextFlags() { return 0; }
};

/* =========================================================================
 * ID3D11DeviceContext
 * ========================================================================= */
struct ID3D11DeviceContext : public ID3D11DeviceChild {
    /* Input Assembler */
    virtual void STDMETHODCALLTYPE IASetInputLayout(ID3D11InputLayout* pInputLayout) {}
    virtual void STDMETHODCALLTYPE IASetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets) {}
    virtual void STDMETHODCALLTYPE IASetIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset) {}
    virtual void STDMETHODCALLTYPE IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology) {}
    virtual void STDMETHODCALLTYPE IAGetInputLayout(ID3D11InputLayout** ppInputLayout) {}
    virtual void STDMETHODCALLTYPE IAGetVertexBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppVertexBuffers, UINT* pStrides, UINT* pOffsets) {}
    virtual void STDMETHODCALLTYPE IAGetIndexBuffer(ID3D11Buffer** pIndexBuffer, DXGI_FORMAT* Format, UINT* Offset) {}
    virtual void STDMETHODCALLTYPE IAGetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY* pTopology) {}
    /* Vertex Shader */
    virtual void STDMETHODCALLTYPE VSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE VSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE VSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {}
    virtual void STDMETHODCALLTYPE VSSetShader(ID3D11VertexShader* pVertexShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {}
    virtual void STDMETHODCALLTYPE VSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE VSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE VSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {}
    virtual void STDMETHODCALLTYPE VSGetShader(ID3D11VertexShader** ppVertexShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {}
    /* Hull Shader */
    virtual void STDMETHODCALLTYPE HSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE HSSetShader(ID3D11HullShader* pHullShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {}
    virtual void STDMETHODCALLTYPE HSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {}
    virtual void STDMETHODCALLTYPE HSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE HSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE HSGetShader(ID3D11HullShader** ppHullShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {}
    virtual void STDMETHODCALLTYPE HSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {}
    virtual void STDMETHODCALLTYPE HSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {}
    /* Domain Shader */
    virtual void STDMETHODCALLTYPE DSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE DSSetShader(ID3D11DomainShader* pDomainShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {}
    virtual void STDMETHODCALLTYPE DSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {}
    virtual void STDMETHODCALLTYPE DSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE DSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE DSGetShader(ID3D11DomainShader** ppDomainShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {}
    virtual void STDMETHODCALLTYPE DSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {}
    virtual void STDMETHODCALLTYPE DSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {}
    /* Geometry Shader */
    virtual void STDMETHODCALLTYPE GSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE GSSetShader(ID3D11GeometryShader* pShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {}
    virtual void STDMETHODCALLTYPE GSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE GSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {}
    virtual void STDMETHODCALLTYPE GSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE GSGetShader(ID3D11GeometryShader** ppGeometryShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {}
    virtual void STDMETHODCALLTYPE GSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE GSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {}
    /* Pixel Shader */
    virtual void STDMETHODCALLTYPE PSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE PSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE PSSetShader(ID3D11PixelShader* pPixelShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {}
    virtual void STDMETHODCALLTYPE PSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {}
    virtual void STDMETHODCALLTYPE PSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE PSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE PSGetShader(ID3D11PixelShader** ppPixelShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {}
    virtual void STDMETHODCALLTYPE PSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {}
    /* Compute Shader */
    virtual void STDMETHODCALLTYPE CSSetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE CSSetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE CSSetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts) {}
    virtual void STDMETHODCALLTYPE CSSetShader(ID3D11ComputeShader* pComputeShader, ID3D11ClassInstance* const* ppClassInstances, UINT NumClassInstances) {}
    virtual void STDMETHODCALLTYPE CSSetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers) {}
    virtual void STDMETHODCALLTYPE CSGetConstantBuffers(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers) {}
    virtual void STDMETHODCALLTYPE CSGetShaderResources(UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView** ppShaderResourceViews) {}
    virtual void STDMETHODCALLTYPE CSGetUnorderedAccessViews(UINT StartSlot, UINT NumUAVs, ID3D11UnorderedAccessView** ppUnorderedAccessViews) {}
    virtual void STDMETHODCALLTYPE CSGetShader(ID3D11ComputeShader** ppComputeShader, ID3D11ClassInstance** ppClassInstances, UINT* pNumClassInstances) {}
    virtual void STDMETHODCALLTYPE CSGetSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState** ppSamplers) {}
    /* Stream Output */
    virtual void STDMETHODCALLTYPE SOSetTargets(UINT NumBuffers, ID3D11Buffer* const* ppSOTargets, const UINT* pOffsets) {}
    virtual void STDMETHODCALLTYPE SOGetTargets(UINT NumBuffers, ID3D11Buffer** ppSOTargets) {}
    /* Rasterizer */
    virtual void STDMETHODCALLTYPE RSSetState(ID3D11RasterizerState* pRasterizerState) {}
    virtual void STDMETHODCALLTYPE RSSetViewports(UINT NumViewports, const D3D11_VIEWPORT* pViewports) {}
    virtual void STDMETHODCALLTYPE RSSetScissorRects(UINT NumRects, const D3D11_RECT* pRects) {}
    virtual void STDMETHODCALLTYPE RSGetState(ID3D11RasterizerState** ppRasterizerState) {}
    virtual void STDMETHODCALLTYPE RSGetViewports(UINT* pNumViewports, D3D11_VIEWPORT* pViewports) {}
    virtual void STDMETHODCALLTYPE RSGetScissorRects(UINT* pNumRects, D3D11_RECT* pRects) {}
    /* Output Merger */
    virtual void STDMETHODCALLTYPE OMSetRenderTargets(UINT NumViews, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView) {}
    virtual void STDMETHODCALLTYPE OMSetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView* const* ppUnorderedAccessViews, const UINT* pUAVInitialCounts) {}
    virtual void STDMETHODCALLTYPE OMSetBlendState(ID3D11BlendState* pBlendState, const FLOAT BlendFactor[4], UINT SampleMask) {}
    virtual void STDMETHODCALLTYPE OMSetDepthStencilState(ID3D11DepthStencilState* pDepthStencilState, UINT StencilRef) {}
    virtual void STDMETHODCALLTYPE OMGetRenderTargets(UINT NumViews, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView** ppDepthStencilView) {}
    virtual void STDMETHODCALLTYPE OMGetRenderTargetsAndUnorderedAccessViews(UINT NumRTVs, ID3D11RenderTargetView** ppRenderTargetViews, ID3D11DepthStencilView** ppDepthStencilView, UINT UAVStartSlot, UINT NumUAVs, ID3D11UnorderedAccessView** ppUnorderedAccessViews) {}
    virtual void STDMETHODCALLTYPE OMGetBlendState(ID3D11BlendState** ppBlendState, FLOAT BlendFactor[4], UINT* pSampleMask) {}
    virtual void STDMETHODCALLTYPE OMGetDepthStencilState(ID3D11DepthStencilState** ppDepthStencilState, UINT* pStencilRef) {}
    /* Draw */
    virtual void STDMETHODCALLTYPE Draw(UINT VertexCount, UINT StartVertexLocation) {}
    virtual void STDMETHODCALLTYPE DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {}
    virtual void STDMETHODCALLTYPE DrawInstanced(UINT VertexCountPerInstance, UINT InstanceCount, UINT StartVertexLocation, UINT StartInstanceLocation) {}
    virtual void STDMETHODCALLTYPE DrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation) {}
    virtual void STDMETHODCALLTYPE DrawIndexedInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs) {}
    virtual void STDMETHODCALLTYPE DrawInstancedIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs) {}
    virtual void STDMETHODCALLTYPE DrawAuto() {}
    /* Compute */
    virtual void STDMETHODCALLTYPE Dispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ) {}
    virtual void STDMETHODCALLTYPE DispatchIndirect(ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs) {}
    /* Resource */
    virtual HRESULT STDMETHODCALLTYPE Map(ID3D11Resource* pResource, UINT Subresource, D3D11_MAP MapType, UINT MapFlags, D3D11_MAPPED_SUBRESOURCE* pMappedResource) {   }
    virtual void    STDMETHODCALLTYPE Unmap(ID3D11Resource* pResource, UINT Subresource) {}
    virtual void    STDMETHODCALLTYPE UpdateSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) {}
    virtual void    STDMETHODCALLTYPE CopySubresourceRegion(ID3D11Resource* pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox) {}
    virtual void    STDMETHODCALLTYPE CopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource) {}
    virtual void    STDMETHODCALLTYPE CopyStructureCount(ID3D11Buffer* pDstBuffer, UINT DstAlignedByteOffset, ID3D11UnorderedAccessView* pSrcView) {}
    virtual void    STDMETHODCALLTYPE ResolveSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, ID3D11Resource* pSrcResource, UINT SrcSubresource, DXGI_FORMAT Format) {}
    virtual void    STDMETHODCALLTYPE GenerateMips(ID3D11ShaderResourceView* pShaderResourceView) {}
    virtual void    STDMETHODCALLTYPE SetResourceMinLOD(ID3D11Resource* pResource, FLOAT MinLOD) {}
    virtual FLOAT   STDMETHODCALLTYPE GetResourceMinLOD(ID3D11Resource* pResource) { return 0.0f; }
    /* Clear */
    virtual void STDMETHODCALLTYPE ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView, const FLOAT ColorRGBA[4]) {}
    virtual void STDMETHODCALLTYPE ClearUnorderedAccessViewUint(ID3D11UnorderedAccessView* pUnorderedAccessView, const UINT Values[4]) {}
    virtual void STDMETHODCALLTYPE ClearUnorderedAccessViewFloat(ID3D11UnorderedAccessView* pUnorderedAccessView, const FLOAT Values[4]) {}
    virtual void STDMETHODCALLTYPE ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView, UINT ClearFlags, FLOAT Depth, UINT8 Stencil) {}
    virtual void STDMETHODCALLTYPE ClearState() {}
    virtual void STDMETHODCALLTYPE Flush() {}
    /* Predication */
    virtual void STDMETHODCALLTYPE SetPredication(ID3D11Predicate* pPredicate, BOOL PredicateValue) {}
    virtual void STDMETHODCALLTYPE GetPredication(ID3D11Predicate** ppPredicate, BOOL* pPredicateValue) {}
    /* Async */
    virtual void    STDMETHODCALLTYPE Begin(ID3D11Asynchronous* pAsync) {}
    virtual void    STDMETHODCALLTYPE End(ID3D11Asynchronous* pAsync) {}
    virtual HRESULT STDMETHODCALLTYPE GetData(ID3D11Asynchronous* pAsync, void* pData, UINT DataSize, UINT GetDataFlags) {   }
    /* Execute */
    virtual void    STDMETHODCALLTYPE ExecuteCommandList(ID3D11CommandList* pCommandList, BOOL RestoreContextState) {}
    virtual HRESULT STDMETHODCALLTYPE FinishCommandList(BOOL RestoreDeferredContextState, ID3D11CommandList** ppCommandList) {   }
    /* Context info */
    virtual D3D11_DEVICE_CONTEXT_TYPE STDMETHODCALLTYPE GetType() { return D3D11_DEVICE_CONTEXT_IMMEDIATE; }
    virtual UINT STDMETHODCALLTYPE GetContextFlags() { return 0; }
};

/* =========================================================================
 * ID3D11DeviceContext1/2/3/4
 * ========================================================================= */
struct ID3D11DeviceContext1 : public ID3D11DeviceContext {
    virtual void    STDMETHODCALLTYPE CopySubresourceRegion1(ID3D11Resource* pDstResource, UINT DstSubresource, UINT DstX, UINT DstY, UINT DstZ, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox, UINT CopyFlags) {}
    virtual void    STDMETHODCALLTYPE UpdateSubresource1(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch, UINT CopyFlags) {}
    virtual void    STDMETHODCALLTYPE DiscardResource(ID3D11Resource* pResource) {}
    virtual void    STDMETHODCALLTYPE DiscardView(ID3D11View* pResourceView) {}
    virtual void    STDMETHODCALLTYPE VSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE HSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE DSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE GSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE PSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE CSSetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer* const* ppConstantBuffers, const UINT* pFirstConstant, const UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE VSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE HSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE DSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE GSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE PSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE CSGetConstantBuffers1(UINT StartSlot, UINT NumBuffers, ID3D11Buffer** ppConstantBuffers, UINT* pFirstConstant, UINT* pNumConstants) {}
    virtual void    STDMETHODCALLTYPE SwapDeviceContextState(ID3DDeviceContextState* pState, ID3DDeviceContextState** ppPreviousState) {}
    virtual void    STDMETHODCALLTYPE ClearView(ID3D11View* pView, const FLOAT Color[4], const D3D11_RECT* pRect, UINT NumRects) {}
    virtual void    STDMETHODCALLTYPE DiscardView1(ID3D11View* pResourceView, const D3D11_RECT* pRects, UINT NumRects) {}
};

struct ID3D11DeviceContext2 : public ID3D11DeviceContext1 {
    virtual HRESULT STDMETHODCALLTYPE UpdateTileMappings(ID3D11Resource* pTiledResource, UINT NumTiledResourceRegions, const void* pTiledResourceRegionStartCoordinates, const void* pTiledResourceRegionSizes, ID3D11Buffer* pTilePool, UINT NumRanges, const UINT* pRangeFlags, const UINT* pTilePoolStartOffsets, const UINT* pRangeTileCounts, UINT Flags) {   }
    virtual HRESULT STDMETHODCALLTYPE CopyTileMappings(ID3D11Resource* pDestTiledResource, const void* pDestRegionStartCoordinate, ID3D11Resource* pSourceTiledResource, const void* pSourceRegionStartCoordinate, const void* pTileRegionSize, UINT Flags) {   }
    virtual void    STDMETHODCALLTYPE CopyTiles(ID3D11Resource* pTiledResource, const void* pTileRegionStartCoordinate, const void* pTileRegionSize, ID3D11Buffer* pBuffer, UINT64 BufferStartOffsetInBytes, UINT Flags) {}
    virtual void    STDMETHODCALLTYPE UpdateTiles(ID3D11Resource* pDestTiledResource, const void* pDestTileRegionStartCoordinate, const void* pDestTileRegionSize, const void* pSourceTileData, UINT Flags) {}
    virtual HRESULT STDMETHODCALLTYPE ResizeTilePool(ID3D11Buffer* pTilePool, UINT64 NewSizeInBytes) {   }
    virtual void    STDMETHODCALLTYPE TiledResourceBarrier(ID3D11DeviceChild* pTiledResourceOrViewAccessBeforeBarrier, ID3D11DeviceChild* pTiledResourceOrViewAccessAfterBarrier) {}
    virtual BOOL    STDMETHODCALLTYPE IsAnnotationEnabled() { return FALSE; }
    virtual void    STDMETHODCALLTYPE SetMarkerInt(LPCWSTR pLabel, INT Data) {}
    virtual void    STDMETHODCALLTYPE BeginEventInt(LPCWSTR pLabel, INT Data) {}
    virtual void    STDMETHODCALLTYPE EndEvent() {}
};

struct ID3D11DeviceContext3 : public ID3D11DeviceContext2 {
    virtual void    STDMETHODCALLTYPE Flush1(D3D11_CONTEXT_TYPE ContextType, HANDLE hEvent) {}
    virtual void    STDMETHODCALLTYPE SetHardwareProtectionState(BOOL HwProtectionEnable) {}
    virtual void    STDMETHODCALLTYPE GetHardwareProtectionState(BOOL* pHwProtectionEnable) {}
};

struct ID3D11DeviceContext4 : public ID3D11DeviceContext3 {
    virtual HRESULT STDMETHODCALLTYPE Signal(void* pFence, UINT64 Value) {   }
    virtual HRESULT STDMETHODCALLTYPE Wait(void* pFence, UINT64 Value) {   }
};

/* =========================================================================
 * ID3DDeviceContextState
 * ========================================================================= */
struct ID3DDeviceContextState : public IUnknown {};

/* =========================================================================
 * D3D11_CONTEXT_TYPE (for ID3D11DeviceContext3)
 * ========================================================================= */


/* =========================================================================
 * ID3D11Multithread
 * ========================================================================= */
struct ID3D11Multithread : public IUnknown {
    virtual void STDMETHODCALLTYPE Enter() {}
    virtual void STDMETHODCALLTYPE Leave() {}
    virtual BOOL STDMETHODCALLTYPE SetMultithreadProtected(BOOL bMTProtect) { return FALSE; }
    virtual BOOL STDMETHODCALLTYPE GetMultithreadProtected() { return FALSE; }
};

/* =========================================================================
 * ID3D11Device
 * ========================================================================= */
struct ID3D11Device : public IUnknown {
    /* Resource creation */
    virtual HRESULT STDMETHODCALLTYPE CreateBuffer(const D3D11_BUFFER_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Buffer** ppBuffer) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateTexture1D(const D3D11_TEXTURE1D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture1D** ppTexture1D) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D** ppTexture2D) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateTexture3D(const D3D11_TEXTURE3D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture3D** ppTexture3D) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateUnorderedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11VertexShader** ppVertexShader) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateGeometryShaderWithStreamOutput(const void* pShaderBytecode, SIZE_T BytecodeLength, const D3D11_SO_DECLARATION_ENTRY* pSODeclaration, UINT NumEntries, const UINT* pBufferStrides, UINT NumStrides, UINT RasterizedStream, ID3D11ClassLinkage* pClassLinkage, ID3D11GeometryShader** ppGeometryShader) {   }
    virtual HRESULT STDMETHODCALLTYPE CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11PixelShader** ppPixelShader) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateHullShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11HullShader** ppHullShader) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateDomainShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11DomainShader** ppDomainShader) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ClassLinkage* pClassLinkage, ID3D11ComputeShader** ppComputeShader) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateClassLinkage(ID3D11ClassLinkage** ppLinkage) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateQuery(const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query** ppQuery) {   }
    virtual HRESULT STDMETHODCALLTYPE CreatePredicate(const D3D11_QUERY_DESC* pPredicateDesc, ID3D11Predicate** ppPredicate) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateCounter(const D3D11_COUNTER_DESC* pCounterDesc, ID3D11Counter** ppCounter) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext(UINT ContextFlags, ID3D11DeviceContext** ppDeferredContext) {   }
    virtual HRESULT STDMETHODCALLTYPE OpenSharedResource(HANDLE hResource, REFIID ReturnedInterface, void** ppResource) {   }
    /* Checks */
    virtual HRESULT STDMETHODCALLTYPE CheckFormatSupport(DXGI_FORMAT Format, UINT* pFormatSupport) {   }
    virtual HRESULT STDMETHODCALLTYPE CheckMultisampleQualityLevels(DXGI_FORMAT Format, UINT SampleCount, UINT* pNumQualityLevels) {   }
    virtual void    STDMETHODCALLTYPE CheckCounterInfo(D3D11_COUNTER_INFO* pCounterInfo) {}
    virtual HRESULT STDMETHODCALLTYPE CheckCounter(const D3D11_COUNTER_DESC* pDesc, D3D11_COUNTER_TYPE* pType, UINT* pActiveCounters, LPSTR szName, UINT* pNameLength, LPSTR szUnits, UINT* pUnitsLength, LPSTR szDescription, UINT* pDescriptionLength) {   }
    virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport(D3D11_FEATURE Feature, void* pFeatureSupportData, UINT FeatureSupportDataSize) {   }
    /* Private data */
    virtual HRESULT STDMETHODCALLTYPE GetPrivateData(REFGUID guid, UINT* pDataSize, void* pData) {   }
    virtual HRESULT STDMETHODCALLTYPE SetPrivateData(REFGUID guid, UINT DataSize, const void* pData) {   }
    virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(REFGUID guid, const IUnknown* pData) {   }
    /* Feature level / flags */
    virtual D3D_FEATURE_LEVEL STDMETHODCALLTYPE GetFeatureLevel() { return D3D_FEATURE_LEVEL_11_0; }
    virtual UINT              STDMETHODCALLTYPE GetCreationFlags() { return 0; }
    virtual HRESULT           STDMETHODCALLTYPE GetDeviceRemovedReason() {   }
    /* Immediate context */
    virtual void STDMETHODCALLTYPE GetImmediateContext(ID3D11DeviceContext** ppImmediateContext) {}
    virtual HRESULT STDMETHODCALLTYPE SetExceptionMode(UINT RaiseFlags) {   }
    virtual UINT    STDMETHODCALLTYPE GetExceptionMode() { return 0; }
};

/* =========================================================================
 * ID3D11Device1 / Device2 / Device3 / Device4 / Device5
 * ========================================================================= */
struct ID3D11Device1 : public ID3D11Device {
    virtual void    STDMETHODCALLTYPE GetImmediateContext1(ID3D11DeviceContext1** ppImmediateContext) {}
    virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext1(UINT ContextFlags, ID3D11DeviceContext1** ppDeferredContext) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateBlendState1(const D3D11_BLEND_DESC1* pBlendStateDesc, ID3D11BlendState1** ppBlendState) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState1(const D3D11_RASTERIZER_DESC1* pRasterizerDesc, ID3D11RasterizerState1** ppRasterizerState) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateDeviceContextState(UINT Flags, const D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, REFIID EmulatedInterface, D3D_FEATURE_LEVEL* pChosenFeatureLevel, ID3DDeviceContextState** ppContextState) {   }
    virtual HRESULT STDMETHODCALLTYPE OpenSharedResource1(HANDLE hResource, REFIID returnedInterface, void** ppResource) {   }
    virtual HRESULT STDMETHODCALLTYPE OpenSharedResourceByName(LPCWSTR lpName, DWORD dwDesiredAccess, REFIID returnedInterface, void** ppResource) {   }
};

struct ID3D11Device2 : public ID3D11Device1 {
    virtual void    STDMETHODCALLTYPE GetImmediateContext2(ID3D11DeviceContext2** ppImmediateContext) {}
    virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext2(UINT ContextFlags, ID3D11DeviceContext2** ppDeferredContext) {   }
    virtual void    STDMETHODCALLTYPE GetResourceTiling(ID3D11Resource* pTiledResource, UINT* pNumTilesForEntireResource, void* pPackedMipDesc, void* pStandardTileShapeForNonPackedMips, UINT* pNumSubresourceTilings, UINT FirstSubresourceTilingToGet, void* pSubresourceTilingsForNonPackedMips) {}
    virtual HRESULT STDMETHODCALLTYPE CheckMultisampleQualityLevels1(DXGI_FORMAT Format, UINT SampleCount, UINT Flags, UINT* pNumQualityLevels) {   }
};

struct ID3D11Device3 : public ID3D11Device2 {
    virtual HRESULT STDMETHODCALLTYPE CreateTexture2D1(const D3D11_TEXTURE2D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture2D1** ppTexture2D) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateTexture3D1(const D3D11_TEXTURE3D_DESC* pDesc, const D3D11_SUBRESOURCE_DATA* pInitialData, ID3D11Texture3D1** ppTexture3D) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState2(const D3D11_RASTERIZER_DESC2* pRasterizerDesc, ID3D11RasterizerState2** ppRasterizerState) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView1(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView1** ppSRView) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateUnorderedAccessView1(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView1** ppUAView) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateRenderTargetView1(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView1** ppRTView) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateQuery1(const D3D11_QUERY_DESC* pQueryDesc, ID3D11Query1** ppQuery) {   }
    virtual void    STDMETHODCALLTYPE GetImmediateContext3(ID3D11DeviceContext3** ppImmediateContext) {}
    virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext3(UINT ContextFlags, ID3D11DeviceContext3** ppDeferredContext) {   }
    virtual void    STDMETHODCALLTYPE WriteToSubresource(ID3D11Resource* pDstResource, UINT DstSubresource, const D3D11_BOX* pDstBox, const void* pSrcData, UINT SrcRowPitch, UINT SrcDepthPitch) {}
    virtual void    STDMETHODCALLTYPE ReadFromSubresource(void* pDstData, UINT DstRowPitch, UINT DstDepthPitch, ID3D11Resource* pSrcResource, UINT SrcSubresource, const D3D11_BOX* pSrcBox) {}
};

struct ID3D11Device4 : public ID3D11Device3 {
    virtual HRESULT STDMETHODCALLTYPE RegisterDeviceRemovedEvent(HANDLE hEvent, DWORD* pdwCookie) {   }
    virtual void    STDMETHODCALLTYPE UnregisterDeviceRemoved(DWORD dwCookie) {}
};

struct ID3D11Device5 : public ID3D11Device4 {
    virtual HRESULT STDMETHODCALLTYPE OpenSharedFence(HANDLE hFence, REFIID ReturnedInterface, void** ppFence) {   }
    virtual HRESULT STDMETHODCALLTYPE CreateFence(UINT64 InitialValue, UINT Flags, REFIID ReturnedInterface, void** ppFence) {   }
};

#endif /* __cplusplus */

/* =========================================================================
 * GUIDs
 * ========================================================================= */
DEFINE_GUID(IID_ID3D11DeviceChild,           0x1841e5c8, 0x16b0, 0x489b, 0xbc, 0xc8, 0x44, 0xcf, 0xb0, 0xd5, 0xde, 0xae);
DEFINE_GUID(IID_ID3D11Resource,              0xdc8e63f3, 0xd12b, 0x4952, 0xb4, 0x7b, 0x5e, 0x45, 0x02, 0x6a, 0x86, 0x2d);
DEFINE_GUID(IID_ID3D11Buffer,                0x48570b85, 0xd1ee, 0x4fcd, 0xa2, 0x50, 0xeb, 0x35, 0x07, 0x22, 0xb0, 0x37);
DEFINE_GUID(IID_ID3D11Texture1D,             0xf8fb5c27, 0xc6b3, 0x4f75, 0xa4, 0xc8, 0x43, 0x9a, 0xf2, 0xef, 0x56, 0x4c);
DEFINE_GUID(IID_ID3D11Texture2D,             0x6f15aaf2, 0xd208, 0x4e89, 0x9a, 0xb4, 0x48, 0x95, 0x35, 0xd3, 0x4f, 0x9c);
DEFINE_GUID(IID_ID3D11Texture2D1,            0x51218251, 0x1e33, 0x4617, 0x9c, 0xcb, 0x4d, 0x3a, 0x43, 0x67, 0xe7, 0xbb);
DEFINE_GUID(IID_ID3D11Texture3D,             0x037e866e, 0xf56d, 0x4357, 0xa8, 0xaf, 0x9d, 0xab, 0xbe, 0x6e, 0x25, 0x0e);
DEFINE_GUID(IID_ID3D11Texture3D1,            0x0c711683, 0x2853, 0x4846, 0x9b, 0xb0, 0xf3, 0xe6, 0x06, 0x39, 0xe4, 0x6a);
DEFINE_GUID(IID_ID3D11View,                  0x839d1216, 0xbb2e, 0x412b, 0xb7, 0xf4, 0xa9, 0xdb, 0xbe, 0xe7, 0x08, 0x26);
DEFINE_GUID(IID_ID3D11ShaderResourceView,    0xb0e06fe0, 0x8192, 0x4e1a, 0xb1, 0xca, 0x36, 0xd7, 0x41, 0x47, 0x10, 0xb2);
DEFINE_GUID(IID_ID3D11ShaderResourceView1,   0x91308b87, 0x9040, 0x411d, 0x8c, 0x67, 0xc3, 0x92, 0x53, 0xce, 0x38, 0x02);
DEFINE_GUID(IID_ID3D11RenderTargetView,      0xdfdba067, 0x0b8d, 0x4865, 0x87, 0x5b, 0xd7, 0xb4, 0x51, 0x6c, 0xc1, 0x64);
DEFINE_GUID(IID_ID3D11RenderTargetView1,     0xffbe2e23, 0xf011, 0x418a, 0xac, 0x56, 0x5c, 0xee, 0xd7, 0xc5, 0xcf, 0x69);
DEFINE_GUID(IID_ID3D11DepthStencilView,      0x9fdac92a, 0x1876, 0x48c3, 0xaf, 0xad, 0x25, 0xb9, 0x4f, 0x84, 0xa9, 0xb6);
DEFINE_GUID(IID_ID3D11UnorderedAccessView,   0x28acf509, 0x7f5c, 0x48f6, 0x86, 0x11, 0xf3, 0x16, 0x01, 0x0a, 0x63, 0x80);
DEFINE_GUID(IID_ID3D11UnorderedAccessView1,  0x7b3b6153, 0xa886, 0x4544, 0xab, 0x37, 0x65, 0x37, 0xc8, 0x50, 0x04, 0x03);
DEFINE_GUID(IID_ID3D11VertexShader,          0x3b301d64, 0xd678, 0x4289, 0x88, 0x97, 0x22, 0xf8, 0x92, 0x8b, 0x72, 0xf3);
DEFINE_GUID(IID_ID3D11HullShader,            0x8e5c6061, 0x628a, 0x4c8e, 0x82, 0x64, 0xbb, 0xe4, 0x5c, 0xb3, 0xd5, 0xdd);
DEFINE_GUID(IID_ID3D11DomainShader,          0xf582c508, 0x0f36, 0x490c, 0x99, 0x77, 0x31, 0xee, 0xce, 0x26, 0x8c, 0xfa);
DEFINE_GUID(IID_ID3D11GeometryShader,        0x38d57c53, 0x9044, 0x4857, 0x9e, 0x77, 0x0a, 0x74, 0x4b, 0xe2, 0xd6, 0x62);
DEFINE_GUID(IID_ID3D11PixelShader,           0xea82e40d, 0x51dc, 0x4f33, 0x93, 0xd4, 0xdb, 0x7c, 0x91, 0x25, 0xae, 0x8c);
DEFINE_GUID(IID_ID3D11ComputeShader,         0x4f5b196e, 0xc2bd, 0x495e, 0xbd, 0x01, 0x1f, 0xde, 0xd3, 0x8e, 0x49, 0x69);
DEFINE_GUID(IID_ID3D11InputLayout,           0xe4819ddc, 0x4cf0, 0x4025, 0xbd, 0x26, 0x5d, 0xe8, 0x2a, 0x3e, 0x07, 0xb7);
DEFINE_GUID(IID_ID3D11BlendState,            0x75b68faa, 0x347d, 0x4159, 0x8f, 0x45, 0xa0, 0x64, 0x0f, 0x01, 0xcd, 0x9a);
DEFINE_GUID(IID_ID3D11BlendState1,           0xcc86fabe, 0xda55, 0x401d, 0x85, 0xe7, 0xe3, 0xc9, 0xde, 0x28, 0x77, 0xe9);
DEFINE_GUID(IID_ID3D11DepthStencilState,     0x03823efb, 0x8d8f, 0x4e1c, 0x9a, 0xa2, 0xf6, 0x4b, 0xb2, 0xcb, 0xfd, 0xf1);
DEFINE_GUID(IID_ID3D11RasterizerState,       0x9bb4ab81, 0xab1a, 0x4d8f, 0xb5, 0x06, 0xfc, 0x04, 0x20, 0x0b, 0x6e, 0xe7);
DEFINE_GUID(IID_ID3D11RasterizerState1,      0x1217d7a6, 0x5039, 0x418c, 0xb0, 0x42, 0x9c, 0xbe, 0x25, 0x6a, 0xfd, 0x6e);
DEFINE_GUID(IID_ID3D11RasterizerState2,      0x6fbd02fb, 0x209f, 0x46c4, 0xb0, 0x59, 0x2e, 0xd1, 0x55, 0x86, 0xa6, 0xac);
DEFINE_GUID(IID_ID3D11SamplerState,          0xda6fea51, 0x564c, 0x4487, 0x98, 0x10, 0xf0, 0xd0, 0xf9, 0xb4, 0xe3, 0xa5);
DEFINE_GUID(IID_ID3D11Asynchronous,          0x4b35d0cd, 0x1e15, 0x4258, 0x9c, 0x98, 0x1b, 0x13, 0x33, 0xf6, 0xdd, 0x3b);
DEFINE_GUID(IID_ID3D11Query,                 0xd6c00747, 0x87b7, 0x425e, 0xb8, 0x4d, 0x44, 0xd1, 0x08, 0x56, 0x0a, 0xfd);
DEFINE_GUID(IID_ID3D11Query1,                0x631b4766, 0x36dc, 0x461d, 0x8d, 0xb6, 0xc4, 0x7e, 0x13, 0xe6, 0x09, 0x16);
DEFINE_GUID(IID_ID3D11Predicate,             0x9eb576dd, 0x9f77, 0x4d86, 0x81, 0xaa, 0x8b, 0xab, 0x5f, 0xe4, 0x90, 0xe2);
DEFINE_GUID(IID_ID3D11Counter,               0x6e8c49fb, 0xa371, 0x4770, 0xb4, 0x40, 0x29, 0x08, 0x60, 0x22, 0xb7, 0x41);
DEFINE_GUID(IID_ID3D11ClassInstance,         0xa6cd7faa, 0xb0b7, 0x4a2f, 0x94, 0x49, 0x5d, 0x7e, 0x9f, 0x09, 0x82, 0x16);
DEFINE_GUID(IID_ID3D11ClassLinkage,          0xddf57cba, 0x9543, 0x46e4, 0xa1, 0x2b, 0xf2, 0x07, 0xa0, 0xfe, 0x7f, 0xed);
DEFINE_GUID(IID_ID3D11CommandList,           0xa24bc4d1, 0x769e, 0x43f7, 0x80, 0x13, 0x98, 0xff, 0x56, 0x6c, 0x18, 0xe2);
DEFINE_GUID(IID_ID3D11DeviceContext,         0xc0bfa96c, 0xe089, 0x44fb, 0x8e, 0xaf, 0x26, 0xf8, 0x79, 0x61, 0x90, 0xda);
DEFINE_GUID(IID_ID3D11DeviceContext1,        0xbb2c6faa, 0xb5fb, 0x4082, 0x8e, 0x6b, 0x38, 0x8b, 0x8c, 0xfa, 0x90, 0xe1);
DEFINE_GUID(IID_ID3D11DeviceContext2,        0x420d5b32, 0xb90c, 0x4da4, 0xbe, 0xf0, 0x35, 0x9f, 0x6a, 0x24, 0xa8, 0x3a);
DEFINE_GUID(IID_ID3D11DeviceContext3,        0xb4e3c01d, 0xe79e, 0x4637, 0x91, 0xb2, 0x51, 0x0e, 0x9f, 0x4c, 0x9b, 0x8f);
DEFINE_GUID(IID_ID3D11DeviceContext4,        0x917600da, 0x67fe, 0x449e, 0xa4, 0x48, 0x7b, 0x61, 0x1b, 0xf0, 0x8e, 0x64);
DEFINE_GUID(IID_ID3D11Device,                0xdb6f6ddb, 0xac77, 0x4e88, 0x82, 0x53, 0x81, 0x9d, 0xf9, 0xbb, 0xf1, 0x40);
DEFINE_GUID(IID_ID3D11Device1,               0xa04bfb29, 0x08ef, 0x43d6, 0xa4, 0x9c, 0xa9, 0xbd, 0xbd, 0xcb, 0xe6, 0x86);
DEFINE_GUID(IID_ID3D11Device2,               0x9d06dffa, 0xd1e5, 0x4d07, 0x83, 0xa8, 0x1b, 0xb1, 0x23, 0xf2, 0xf8, 0x41);
DEFINE_GUID(IID_ID3D11Device3,               0xa05c8c37, 0xd2c6, 0x4732, 0xb3, 0xa0, 0x9c, 0xe0, 0xb0, 0xdc, 0x9a, 0xe6);
DEFINE_GUID(IID_ID3D11Device4,               0x8992ab71, 0x02e6, 0x4b8d, 0xba, 0x48, 0xb0, 0x56, 0xdc, 0xda, 0x42, 0xc4);
DEFINE_GUID(IID_ID3D11Device5,               0x8ffde202, 0xa0e7, 0x45df, 0x9e, 0x01, 0xe8, 0x37, 0x80, 0x1b, 0x5e, 0xa0);
DEFINE_GUID(IID_ID3D11Multithread,           0x9b7e4e00, 0x342c, 0x4106, 0xa1, 0x9f, 0x4f, 0x27, 0x04, 0xf6, 0x89, 0xf0);
DEFINE_GUID(IID_ID3DDeviceContextState,      0x5c1e0d8a, 0x7c23, 0x48f9, 0x8c, 0x59, 0xa9, 0x29, 0x58, 0xce, 0xff, 0x11);

/* =========================================================================
 * Constants
 * ========================================================================= */
#define D3D11_SDK_VERSION                                   7
#define D3D11_APPEND_ALIGNED_ELEMENT                        0xffffffff
#define D3D11_DEFAULT_SAMPLE_MASK                           0xffffffff
#define D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT              8
#define D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT                  32
#define D3D11_FLOAT32_MAX                                   3.402823466e+38f
#define D3D11_DEFAULT_DEPTH_BIAS                            0
#define D3D11_DEFAULT_DEPTH_BIAS_CLAMP                      0.0f
#define D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS               0.0f
#define D3D11_DEFAULT_STENCIL_READ_MASK                     0xff
#define D3D11_DEFAULT_STENCIL_WRITE_MASK                    0xff
#define D3D11_DEFAULT_BLEND_FACTOR_RED                      1.0f
#define D3D11_DEFAULT_BLEND_FACTOR_GREEN                    1.0f
#define D3D11_DEFAULT_BLEND_FACTOR_BLUE                     1.0f
#define D3D11_DEFAULT_BLEND_FACTOR_ALPHA                    1.0f
#define D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT   14
#define D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT               16
#define D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT        128
#define D3D11_COMMONSHADER_TEXEL_OFFSET_MAX_NEGATIVE        -8
#define D3D11_COMMONSHADER_TEXEL_OFFSET_MAX_POSITIVE        7
#define D3D11_VS_INPUT_REGISTER_COUNT                       32
#define D3D11_VS_OUTPUT_REGISTER_COUNT                      32
#define D3D11_HS_CONTROL_POINT_PHASE_INPUT_REGISTER_COUNT   32
#define D3D11_DS_INPUT_CONTROL_POINT_REGISTER_COUNT         32
#define D3D11_GS_OUTPUT_VERTEX_COUNT_MAX                    1024
#define D3D11_PS_INPUT_REGISTER_COUNT                       32
#define D3D11_PS_OUTPUT_REGISTER_COUNT                      8
#define D3D11_CS_THREAD_GROUP_MAX_X                         1024
#define D3D11_CS_THREAD_GROUP_MAX_Y                         1024
#define D3D11_CS_THREAD_GROUP_MAX_Z                         64
#define D3D11_CS_THREAD_GROUP_MAX_THREADS_PER_GROUP         1024
#define D3D11_CS_DISPATCH_MAX_THREAD_GROUPS_PER_DIMENSION   65535
#define D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX            15
#define D3D11_SO_BUFFER_SLOT_COUNT                          4
#define D3D11_SO_OUTPUT_COMPONENT_COUNT                     128
#define D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT           32
#define D3D11_IA_INDEX_INPUT_RESOURCE_SLOT_COUNT            1
#define D3D11_MIP_LOD_BIAS_MAX                              15.99f
#define D3D11_MIP_LOD_BIAS_MIN                              -16.0f
#define D3D11_MAX_MAXANISOTROPY                             16
#define D3D11_MIN_MAXANISOTROPY                             0
#define D3D11_REQ_TEXTURE1D_U_DIMENSION                     16384
#define D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION                16384
#define D3D11_REQ_TEXTURE3D_U_V_OR_W_DIMENSION              2048
#define D3D11_REQ_TEXTURECUBE_DIMENSION                     16384
#define D3D11_REQ_TEXTURE1D_ARRAY_AXIS_DIMENSION            2048
#define D3D11_REQ_TEXTURE2D_ARRAY_AXIS_DIMENSION            2048
#define D3D11_REQ_MIP_LEVELS                                15
#define D3D11_KEEP_RENDER_TARGETS_AND_DEPTH_STENCIL         0xffffffff
#define D3D11_KEEP_UNORDERED_ACCESS_VIEWS                   0xffffffff
#define D3D11_UAV_SLOT_COUNT                                64
#define D3D11_PS_CS_UAV_REGISTER_COUNT                      8

/* =========================================================================
 * D3D11CreateDevice / D3D11CreateDeviceAndSwapChain stubs
 * ========================================================================= */
#ifdef __cplusplus
extern "C" {
#endif

static inline HRESULT D3D11CreateDevice(
    void*               pAdapter,
    D3D_DRIVER_TYPE     DriverType,
    HMODULE             Software,
    UINT                Flags,
    const D3D_FEATURE_LEVEL* pFeatureLevels,
    UINT                FeatureLevels,
    UINT                SDKVersion,
    ID3D11Device**      ppDevice,
    D3D_FEATURE_LEVEL*  pFeatureLevel,
    ID3D11DeviceContext** ppImmediateContext)
{
    (void)pAdapter; (void)DriverType; (void)Software;
    (void)Flags; (void)pFeatureLevels; (void)FeatureLevels; (void)SDKVersion;
    if (ppDevice)           *ppDevice           = 0;
    if (pFeatureLevel)      *pFeatureLevel      = D3D_FEATURE_LEVEL_11_0;
    if (ppImmediateContext) *ppImmediateContext  = 0;
     
}

static inline UINT D3D11CalcSubresource(UINT MipSlice, UINT ArraySlice, UINT MipLevels)
{
    return MipSlice + ArraySlice * MipLevels;
}

#ifdef __cplusplus
} /* extern "C" */
#endif


/* =========================================================================
 * D3D11 Shader Reflection types (d3d11shader.h / d3dcommon.h)
 * ========================================================================= */

typedef enum _D3D_CBUFFER_TYPE {
    D3D_CT_CBUFFER      = 0,
    D3D_CT_TBUFFER      = 1,
    D3D_CT_INTERFACE_POINTERS = 2,
    D3D_CT_RESOURCE_BIND_INFO = 3,
    D3D11_CT_CBUFFER    = D3D_CT_CBUFFER,
    D3D11_CT_TBUFFER    = D3D_CT_TBUFFER,
    D3D11_CT_INTERFACE_POINTERS = D3D_CT_INTERFACE_POINTERS,
    D3D11_CT_RESOURCE_BIND_INFO = D3D_CT_RESOURCE_BIND_INFO,
} D3D_CBUFFER_TYPE;
typedef D3D_CBUFFER_TYPE D3D11_CBUFFER_TYPE;

typedef enum _D3D_SHADER_VARIABLE_CLASS {
    D3D_SVC_SCALAR              = 0,
    D3D_SVC_VECTOR              = 1,
    D3D_SVC_MATRIX_ROWS         = 2,
    D3D_SVC_MATRIX_COLUMNS      = 3,
    D3D_SVC_OBJECT              = 4,
    D3D_SVC_STRUCT              = 5,
    D3D_SVC_INTERFACE_CLASS     = 6,
    D3D_SVC_INTERFACE_POINTER   = 7,
    D3D11_SVC_SCALAR            = D3D_SVC_SCALAR,
    D3D11_SVC_VECTOR            = D3D_SVC_VECTOR,
    D3D11_SVC_MATRIX_ROWS       = D3D_SVC_MATRIX_ROWS,
    D3D11_SVC_MATRIX_COLUMNS    = D3D_SVC_MATRIX_COLUMNS,
    D3D11_SVC_OBJECT            = D3D_SVC_OBJECT,
    D3D11_SVC_STRUCT            = D3D_SVC_STRUCT,
    D3D11_SVC_INTERFACE_CLASS   = D3D_SVC_INTERFACE_CLASS,
    D3D11_SVC_INTERFACE_POINTER = D3D_SVC_INTERFACE_POINTER,
    D3D_SVC_FORCE_DWORD         = 0x7fffffff,
} D3D_SHADER_VARIABLE_CLASS;

typedef enum _D3D_SHADER_VARIABLE_FLAGS {
    D3D_SVF_USERPACKED              = 1,
    D3D_SVF_USED                    = 2,
    D3D_SVF_INTERFACE_POINTER       = 4,
    D3D_SVF_INTERFACE_PARAMETER     = 8,
    D3D11_SVF_USERPACKED            = D3D_SVF_USERPACKED,
    D3D11_SVF_USED                  = D3D_SVF_USED,
    D3D_SVF_FORCE_DWORD             = 0x7fffffff,
} D3D_SHADER_VARIABLE_FLAGS;

typedef enum _D3D_SHADER_VARIABLE_TYPE {
    D3D_SVT_VOID                    = 0,
    D3D_SVT_BOOL                    = 1,
    D3D_SVT_INT                     = 2,
    D3D_SVT_FLOAT                   = 3,
    D3D_SVT_STRING                  = 4,
    D3D_SVT_TEXTURE                 = 5,
    D3D_SVT_TEXTURE1D               = 6,
    D3D_SVT_TEXTURE2D               = 7,
    D3D_SVT_TEXTURE3D               = 8,
    D3D_SVT_TEXTURECUBE             = 9,
    D3D_SVT_SAMPLER                 = 10,
    D3D_SVT_SAMPLER1D               = 11,
    D3D_SVT_SAMPLER2D               = 12,
    D3D_SVT_SAMPLER3D               = 13,
    D3D_SVT_SAMPLERCUBE             = 14,
    D3D_SVT_PIXELSHADER             = 15,
    D3D_SVT_VERTEXSHADER            = 16,
    D3D_SVT_PIXELFRAGMENT           = 17,
    D3D_SVT_VERTEXFRAGMENT          = 18,
    D3D_SVT_UINT                    = 19,
    D3D_SVT_UINT8                   = 20,
    D3D_SVT_GEOMETRYSHADER          = 21,
    D3D_SVT_RASTERIZER              = 22,
    D3D_SVT_DEPTHSTENCIL            = 23,
    D3D_SVT_BLEND                   = 24,
    D3D_SVT_BUFFER                  = 25,
    D3D_SVT_CBUFFER                 = 26,
    D3D_SVT_TBUFFER                 = 27,
    D3D_SVT_TEXTURE1DARRAY          = 28,
    D3D_SVT_TEXTURE2DARRAY          = 29,
    D3D_SVT_RENDERTARGETVIEW        = 30,
    D3D_SVT_DEPTHSTENCILVIEW        = 31,
    D3D_SVT_TEXTURE2DMS             = 32,
    D3D_SVT_TEXTURE2DMSARRAY        = 33,
    D3D_SVT_TEXTURECUBEARRAY        = 34,
    D3D_SVT_HULLSHADER              = 35,
    D3D_SVT_DOMAINSHADER            = 36,
    D3D_SVT_INTERFACE_POINTER       = 37,
    D3D_SVT_COMPUTESHADER           = 38,
    D3D_SVT_DOUBLE                  = 39,
    D3D_SVT_RWTEXTURE1D             = 40,
    D3D_SVT_RWTEXTURE1DARRAY        = 41,
    D3D_SVT_RWTEXTURE2D             = 42,
    D3D_SVT_RWTEXTURE2DARRAY        = 43,
    D3D_SVT_RWTEXTURE3D             = 44,
    D3D_SVT_RWBUFFER                = 45,
    D3D_SVT_BYTEADDRESS_BUFFER      = 46,
    D3D_SVT_RWBYTEADDRESS_BUFFER    = 47,
    D3D_SVT_STRUCTURED_BUFFER       = 48,
    D3D_SVT_RWSTRUCTURED_BUFFER     = 49,
    D3D_SVT_APPEND_STRUCTURED_BUFFER = 50,
    D3D_SVT_CONSUME_STRUCTURED_BUFFER = 51,
    D3D_SVT_MIN8FLOAT               = 52,
    D3D_SVT_MIN10FLOAT              = 53,
    D3D_SVT_MIN16FLOAT              = 54,
    D3D_SVT_MIN12INT                = 55,
    D3D_SVT_MIN16INT                = 56,
    D3D_SVT_MIN16UINT               = 57,
    D3D_SVT_FORCE_DWORD             = 0x7fffffff,
} D3D_SHADER_VARIABLE_TYPE;

typedef enum _D3D_SHADER_INPUT_FLAGS {
    D3D_SIF_USERPACKED              = 0x1,
    D3D_SIF_COMPARISON_SAMPLER      = 0x2,
    D3D_SIF_TEXTURE_COMPONENT_0     = 0x4,
    D3D_SIF_TEXTURE_COMPONENT_1     = 0x8,
    D3D_SIF_TEXTURE_COMPONENTS      = 0xc,
    D3D_SIF_UNUSED                  = 0x10,
    D3D11_SIF_USERPACKED            = D3D_SIF_USERPACKED,
    D3D11_SIF_COMPARISON_SAMPLER    = D3D_SIF_COMPARISON_SAMPLER,
    D3D11_SIF_TEXTURE_COMPONENT_0   = D3D_SIF_TEXTURE_COMPONENT_0,
    D3D11_SIF_TEXTURE_COMPONENT_1   = D3D_SIF_TEXTURE_COMPONENT_1,
    D3D11_SIF_TEXTURE_COMPONENTS    = D3D_SIF_TEXTURE_COMPONENTS,
    D3D_SIF_FORCE_DWORD             = 0x7fffffff,
} D3D_SHADER_INPUT_FLAGS;

typedef enum _D3D_SHADER_INPUT_TYPE {
    D3D_SIT_CBUFFER                     = 0,
    D3D_SIT_TBUFFER                     = 1,
    D3D_SIT_TEXTURE                     = 2,
    D3D_SIT_SAMPLER                     = 3,
    D3D_SIT_UAV_RWTYPED                 = 4,
    D3D_SIT_STRUCTURED                  = 5,
    D3D_SIT_UAV_RWSTRUCTURED            = 6,
    D3D_SIT_BYTEADDRESS                 = 7,
    D3D_SIT_UAV_RWBYTEADDRESS           = 8,
    D3D_SIT_UAV_APPEND_STRUCTURED       = 9,
    D3D_SIT_UAV_CONSUME_STRUCTURED      = 10,
    D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER = 11,
    D3D11_SIT_CBUFFER                   = D3D_SIT_CBUFFER,
    D3D11_SIT_TBUFFER                   = D3D_SIT_TBUFFER,
    D3D11_SIT_TEXTURE                   = D3D_SIT_TEXTURE,
    D3D11_SIT_SAMPLER                   = D3D_SIT_SAMPLER,
    D3D11_SIT_UAV_RWTYPED               = D3D_SIT_UAV_RWTYPED,
    D3D11_SIT_STRUCTURED                = D3D_SIT_STRUCTURED,
    D3D11_SIT_UAV_RWSTRUCTURED          = D3D_SIT_UAV_RWSTRUCTURED,
    D3D11_SIT_BYTEADDRESS               = D3D_SIT_BYTEADDRESS,
    D3D11_SIT_UAV_RWBYTEADDRESS         = D3D_SIT_UAV_RWBYTEADDRESS,
    D3D11_SIT_UAV_APPEND_STRUCTURED     = D3D_SIT_UAV_APPEND_STRUCTURED,
    D3D11_SIT_UAV_CONSUME_STRUCTURED    = D3D_SIT_UAV_CONSUME_STRUCTURED,
    D3D11_SIT_UAV_RWSTRUCTURED_WITH_COUNTER = D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER,
} D3D_SHADER_INPUT_TYPE;

typedef enum _D3D_SHADER_CBUFFER_FLAGS {
    D3D_CBF_USERPACKED      = 1,
    D3D11_CBF_USERPACKED    = D3D_CBF_USERPACKED,
    D3D_CBF_FORCE_DWORD     = 0x7fffffff,
} D3D_SHADER_CBUFFER_FLAGS;

typedef enum _D3D_RESOURCE_RETURN_TYPE {
    D3D_RETURN_TYPE_UNORM       = 1,
    D3D_RETURN_TYPE_SNORM       = 2,
    D3D_RETURN_TYPE_SINT        = 3,
    D3D_RETURN_TYPE_UINT        = 4,
    D3D_RETURN_TYPE_FLOAT       = 5,
    D3D_RETURN_TYPE_MIXED       = 6,
    D3D_RETURN_TYPE_DOUBLE      = 7,
    D3D_RETURN_TYPE_CONTINUED   = 8,
} D3D_RESOURCE_RETURN_TYPE;

typedef enum _D3D_REGISTER_COMPONENT_TYPE {
    D3D_REGISTER_COMPONENT_UNKNOWN  = 0,
    D3D_REGISTER_COMPONENT_UINT32   = 1,
    D3D_REGISTER_COMPONENT_SINT32   = 2,
    D3D_REGISTER_COMPONENT_FLOAT32  = 3,
    D3D_REGISTER_COMPONENT_FORCE_DWORD = 0x7fffffff,
} D3D_REGISTER_COMPONENT_TYPE;

typedef enum _D3D_TESSELLATOR_DOMAIN {
    D3D_TESSELLATOR_DOMAIN_UNDEFINED = 0,
    D3D_TESSELLATOR_DOMAIN_ISOLINE   = 1,
    D3D_TESSELLATOR_DOMAIN_TRI       = 2,
    D3D_TESSELLATOR_DOMAIN_QUAD      = 3,
    D3D11_TESSELLATOR_DOMAIN_UNDEFINED = D3D_TESSELLATOR_DOMAIN_UNDEFINED,
    D3D11_TESSELLATOR_DOMAIN_ISOLINE   = D3D_TESSELLATOR_DOMAIN_ISOLINE,
    D3D11_TESSELLATOR_DOMAIN_TRI       = D3D_TESSELLATOR_DOMAIN_TRI,
    D3D11_TESSELLATOR_DOMAIN_QUAD      = D3D_TESSELLATOR_DOMAIN_QUAD,
    D3D_TESSELLATOR_DOMAIN_FORCE_DWORD = 0x7fffffff,
} D3D_TESSELLATOR_DOMAIN;

typedef enum _D3D_TESSELLATOR_PARTITIONING {
    D3D_TESSELLATOR_PARTITIONING_UNDEFINED      = 0,
    D3D_TESSELLATOR_PARTITIONING_INTEGER        = 1,
    D3D_TESSELLATOR_PARTITIONING_POW2           = 2,
    D3D_TESSELLATOR_PARTITIONING_FRACTIONAL_ODD = 3,
    D3D_TESSELLATOR_PARTITIONING_FRACTIONAL_EVEN = 4,
    D3D_TESSELLATOR_PARTITIONING_FORCE_DWORD    = 0x7fffffff,
} D3D_TESSELLATOR_PARTITIONING;

typedef enum _D3D_TESSELLATOR_OUTPUT_PRIMITIVE {
    D3D_TESSELLATOR_OUTPUT_UNDEFINED    = 0,
    D3D_TESSELLATOR_OUTPUT_POINT        = 1,
    D3D_TESSELLATOR_OUTPUT_LINE         = 2,
    D3D_TESSELLATOR_OUTPUT_TRIANGLE_CW  = 3,
    D3D_TESSELLATOR_OUTPUT_TRIANGLE_CCW = 4,
    D3D_TESSELLATOR_OUTPUT_FORCE_DWORD  = 0x7fffffff,
} D3D_TESSELLATOR_OUTPUT_PRIMITIVE;

typedef enum _D3D_MIN_PRECISION {
    D3D_MIN_PRECISION_DEFAULT   = 0,
    D3D_MIN_PRECISION_FLOAT_16  = 1,
    D3D_MIN_PRECISION_FLOAT_2_8 = 2,
    D3D_MIN_PRECISION_RESERVED  = 3,
    D3D_MIN_PRECISION_SINT_16   = 4,
    D3D_MIN_PRECISION_UINT_16   = 5,
    D3D_MIN_PRECISION_ANY_16    = 0xf0,
    D3D_MIN_PRECISION_ANY_10    = 0xf1,
    D3D_MIN_PRECISION_FORCE_DWORD = 0x7fffffff,
} D3D_MIN_PRECISION;

typedef enum _D3D_INTERPOLATION_MODE {
    D3D_INTERPOLATION_UNDEFINED                 = 0,
    D3D_INTERPOLATION_CONSTANT                  = 1,
    D3D_INTERPOLATION_LINEAR                    = 2,
    D3D_INTERPOLATION_LINEAR_CENTROID           = 3,
    D3D_INTERPOLATION_LINEAR_NOPERSPECTIVE      = 4,
    D3D_INTERPOLATION_LINEAR_NOPERSPECTIVE_CENTROID = 5,
    D3D_INTERPOLATION_LINEAR_SAMPLE             = 6,
    D3D_INTERPOLATION_LINEAR_NOPERSPECTIVE_SAMPLE = 7,
    D3D_INTERPOLATION_FORCE_DWORD               = 0x7fffffff,
} D3D_INTERPOLATION_MODE;

typedef enum _D3D_NAME {
    D3D_NAME_UNDEFINED              = 0,
    D3D_NAME_POSITION               = 1,
    D3D_NAME_CLIP_DISTANCE          = 2,
    D3D_NAME_CULL_DISTANCE          = 3,
    D3D_NAME_RENDER_TARGET_ARRAY_INDEX = 4,
    D3D_NAME_VIEWPORT_ARRAY_INDEX   = 5,
    D3D_NAME_VERTEX_ID              = 6,
    D3D_NAME_PRIMITIVE_ID           = 7,
    D3D_NAME_INSTANCE_ID            = 8,
    D3D_NAME_IS_FRONT_FACE          = 9,
    D3D_NAME_SAMPLE_INDEX           = 10,
    D3D_NAME_FINAL_QUAD_EDGE_TESSFACTOR = 11,
    D3D_NAME_FINAL_QUAD_INSIDE_TESSFACTOR = 12,
    D3D_NAME_FINAL_TRI_EDGE_TESSFACTOR = 13,
    D3D_NAME_FINAL_TRI_INSIDE_TESSFACTOR = 14,
    D3D_NAME_FINAL_LINE_DETAIL_TESSFACTOR = 15,
    D3D_NAME_FINAL_LINE_DENSITY_TESSFACTOR = 16,
    D3D_NAME_TARGET                 = 64,
    D3D_NAME_DEPTH                  = 65,
    D3D_NAME_COVERAGE               = 66,
    D3D_NAME_DEPTH_GREATER_EQUAL    = 67,
    D3D_NAME_DEPTH_LESS_EQUAL       = 68,
    D3D_NAME_STENCIL_REF            = 69,
    D3D_NAME_INNER_COVERAGE         = 70,
    D3D11_NAME_UNDEFINED            = D3D_NAME_UNDEFINED,
    D3D11_NAME_POSITION             = D3D_NAME_POSITION,
    D3D11_NAME_CLIP_DISTANCE        = D3D_NAME_CLIP_DISTANCE,
    D3D11_NAME_CULL_DISTANCE        = D3D_NAME_CULL_DISTANCE,
    D3D11_NAME_RENDER_TARGET_ARRAY_INDEX = D3D_NAME_RENDER_TARGET_ARRAY_INDEX,
    D3D11_NAME_VIEWPORT_ARRAY_INDEX = D3D_NAME_VIEWPORT_ARRAY_INDEX,
    D3D11_NAME_VERTEX_ID            = D3D_NAME_VERTEX_ID,
    D3D11_NAME_PRIMITIVE_ID         = D3D_NAME_PRIMITIVE_ID,
    D3D11_NAME_INSTANCE_ID          = D3D_NAME_INSTANCE_ID,
    D3D11_NAME_IS_FRONT_FACE        = D3D_NAME_IS_FRONT_FACE,
    D3D11_NAME_SAMPLE_INDEX         = D3D_NAME_SAMPLE_INDEX,
    D3D11_NAME_TARGET               = D3D_NAME_TARGET,
    D3D11_NAME_DEPTH                = D3D_NAME_DEPTH,
    D3D11_NAME_COVERAGE             = D3D_NAME_COVERAGE,
    D3D11_NAME_DEPTH_GREATER_EQUAL  = D3D_NAME_DEPTH_GREATER_EQUAL,
    D3D11_NAME_DEPTH_LESS_EQUAL     = D3D_NAME_DEPTH_LESS_EQUAL,
    D3D_NAME_FORCE_DWORD            = 0x7fffffff,
} D3D_NAME;

/* -------------------------------------------------------------------------
 * Shader reflection descriptor structs
 * ------------------------------------------------------------------------- */
typedef struct _D3D11_SHADER_DESC {
    UINT Version;
    LPCSTR Creator;
    UINT Flags;
    UINT ConstantBuffers;
    UINT BoundResources;
    UINT InputParameters;
    UINT OutputParameters;
    UINT InstructionCount;
    UINT TempRegisterCount;
    UINT TempArrayCount;
    UINT DefCount;
    UINT DclCount;
    UINT TextureNormalInstructions;
    UINT TextureLoadInstructions;
    UINT TextureCompInstructions;
    UINT TextureBiasInstructions;
    UINT TextureGradientInstructions;
    UINT FloatInstructionCount;
    UINT IntInstructionCount;
    UINT UintInstructionCount;
    UINT StaticFlowControlCount;
    UINT DynamicFlowControlCount;
    UINT MacroInstructionCount;
    UINT ArrayInstructionCount;
    UINT CutInstructionCount;
    UINT EmitInstructionCount;
    UINT GSOutputTopology;
    UINT GSMaxOutputVertexCount;
    UINT InputPrimitive;
    UINT PatchConstantParameters;
    UINT cGSInstanceCount;
    UINT cControlPoints;
    D3D_TESSELLATOR_OUTPUT_PRIMITIVE HSOutputPrimitive;
    D3D_TESSELLATOR_PARTITIONING    HSPartitioning;
    D3D_TESSELLATOR_DOMAIN          TessellatorDomain;
    UINT cBarrierInstructions;
    UINT cInterlockedInstructions;
    UINT cTextureStoreInstructions;
} D3D11_SHADER_DESC;

typedef struct _D3D11_SHADER_BUFFER_DESC {
    LPCSTR          Name;
    D3D_CBUFFER_TYPE Type;
    UINT            Variables;
    UINT            Size;
    UINT            uFlags;
} D3D11_SHADER_BUFFER_DESC;

typedef struct _D3D11_SHADER_VARIABLE_DESC {
    LPCSTR  Name;
    UINT    StartOffset;
    UINT    Size;
    UINT    uFlags;
    LPVOID  DefaultValue;
    UINT    StartTexture;
    UINT    TextureSize;
    UINT    StartSampler;
    UINT    SamplerSize;
} D3D11_SHADER_VARIABLE_DESC;

typedef struct _D3D11_SHADER_TYPE_DESC {
    D3D_SHADER_VARIABLE_CLASS Class;
    D3D_SHADER_VARIABLE_TYPE  Type;
    UINT                      Rows;
    UINT                      Columns;
    UINT                      Elements;
    UINT                      Members;
    UINT                      Offset;
    LPCSTR                    Name;
} D3D11_SHADER_TYPE_DESC;

typedef struct _D3D11_SHADER_INPUT_BIND_DESC {
    LPCSTR                  Name;
    D3D_SHADER_INPUT_TYPE   Type;
    UINT                    BindPoint;
    UINT                    BindCount;
    UINT                    uFlags;
    D3D_RESOURCE_RETURN_TYPE ReturnType;
    D3D_SRV_DIMENSION       Dimension;
    UINT                    NumSamples;
} D3D11_SHADER_INPUT_BIND_DESC;

typedef struct _D3D11_SIGNATURE_PARAMETER_DESC {
    LPCSTR                      SemanticName;
    UINT                        SemanticIndex;
    UINT                        Register;
    D3D_NAME                    SystemValueType;
    D3D_REGISTER_COMPONENT_TYPE ComponentType;
    BYTE                        Mask;
    BYTE                        ReadWriteMask;
    UINT                        Stream;
    D3D_MIN_PRECISION           MinPrecision;
} D3D11_SIGNATURE_PARAMETER_DESC;

/* D3D_SRV_DIMENSION - aliased from D3D11_SRV_DIMENSION */

/* -------------------------------------------------------------------------
 * Shader reflection interfaces
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus

struct ID3D11ShaderReflectionType;
struct ID3D11ShaderReflectionVariable;
struct ID3D11ShaderReflectionConstantBuffer;
struct ID3D11ShaderReflection;

struct ID3D11ShaderReflectionType {
    virtual HRESULT STDMETHODCALLTYPE GetDesc(D3D11_SHADER_TYPE_DESC* pDesc) {   }
    virtual ID3D11ShaderReflectionType* STDMETHODCALLTYPE GetMemberTypeByIndex(UINT Index) { return nullptr; }
    virtual ID3D11ShaderReflectionType* STDMETHODCALLTYPE GetMemberTypeByName(LPCSTR Name) { return nullptr; }
    virtual LPCSTR  STDMETHODCALLTYPE GetMemberTypeName(UINT Index) { return nullptr; }
    virtual HRESULT STDMETHODCALLTYPE IsEqual(ID3D11ShaderReflectionType* pType) {   }
    virtual ID3D11ShaderReflectionType* STDMETHODCALLTYPE GetSubType() { return nullptr; }
    virtual ID3D11ShaderReflectionType* STDMETHODCALLTYPE GetBaseClass() { return nullptr; }
    virtual UINT    STDMETHODCALLTYPE GetNumInterfaces() { return 0; }
    virtual ID3D11ShaderReflectionType* STDMETHODCALLTYPE GetInterfaceByIndex(UINT uIndex) { return nullptr; }
    virtual HRESULT STDMETHODCALLTYPE IsOfType(ID3D11ShaderReflectionType* pType) {   }
    virtual HRESULT STDMETHODCALLTYPE ImplementsInterface(ID3D11ShaderReflectionType* pBase) {   }
};

struct ID3D11ShaderReflectionVariable {
    virtual HRESULT STDMETHODCALLTYPE GetDesc(D3D11_SHADER_VARIABLE_DESC* pDesc) {   }
    virtual ID3D11ShaderReflectionType* STDMETHODCALLTYPE GetType() { return nullptr; }
    virtual ID3D11ShaderReflectionConstantBuffer* STDMETHODCALLTYPE GetBuffer() { return nullptr; }
    virtual UINT    STDMETHODCALLTYPE GetInterfaceSlot(UINT uArrayIndex) { return 0; }
};

struct ID3D11ShaderReflectionConstantBuffer {
    virtual HRESULT STDMETHODCALLTYPE GetDesc(D3D11_SHADER_BUFFER_DESC* pDesc) {   }
    virtual ID3D11ShaderReflectionVariable* STDMETHODCALLTYPE GetVariableByIndex(UINT Index) { return nullptr; }
    virtual ID3D11ShaderReflectionVariable* STDMETHODCALLTYPE GetVariableByName(LPCSTR Name) { return nullptr; }
};

struct ID3D11ShaderReflection : public IUnknown {
    virtual HRESULT STDMETHODCALLTYPE GetDesc(D3D11_SHADER_DESC* pDesc) {   }
    virtual ID3D11ShaderReflectionConstantBuffer* STDMETHODCALLTYPE GetConstantBufferByIndex(UINT Index) { return nullptr; }
    virtual ID3D11ShaderReflectionConstantBuffer* STDMETHODCALLTYPE GetConstantBufferByName(LPCSTR Name) { return nullptr; }
    virtual HRESULT STDMETHODCALLTYPE GetResourceBindingDesc(UINT ResourceIndex, D3D11_SHADER_INPUT_BIND_DESC* pDesc) {   }
    virtual HRESULT STDMETHODCALLTYPE GetInputParameterDesc(UINT ParameterIndex, D3D11_SIGNATURE_PARAMETER_DESC* pDesc) {   }
    virtual HRESULT STDMETHODCALLTYPE GetOutputParameterDesc(UINT ParameterIndex, D3D11_SIGNATURE_PARAMETER_DESC* pDesc) {   }
    virtual HRESULT STDMETHODCALLTYPE GetPatchConstantParameterDesc(UINT ParameterIndex, D3D11_SIGNATURE_PARAMETER_DESC* pDesc) {   }
    virtual ID3D11ShaderReflectionVariable* STDMETHODCALLTYPE GetVariableByName(LPCSTR Name) { return nullptr; }
    virtual HRESULT STDMETHODCALLTYPE GetResourceBindingDescByName(LPCSTR Name, D3D11_SHADER_INPUT_BIND_DESC* pDesc) {   }
    virtual UINT    STDMETHODCALLTYPE GetMovInstructionCount() { return 0; }
    virtual UINT    STDMETHODCALLTYPE GetMovcInstructionCount() { return 0; }
    virtual UINT    STDMETHODCALLTYPE GetConversionInstructionCount() { return 0; }
    virtual UINT    STDMETHODCALLTYPE GetBitwiseInstructionCount() { return 0; }
    virtual D3D_PRIMITIVE STDMETHODCALLTYPE GetGSInputPrimitive() {  }
    virtual BOOL    STDMETHODCALLTYPE IsSampleFrequencyShader() { return FALSE; }
    virtual UINT    STDMETHODCALLTYPE GetNumInterfaceSlots() { return 0; }
    virtual HRESULT STDMETHODCALLTYPE GetMinFeatureLevel(D3D_FEATURE_LEVEL* pLevel) {   }
    virtual UINT    STDMETHODCALLTYPE GetThreadGroupSize(UINT* pSizeX, UINT* pSizeY, UINT* pSizeZ) { return 0; }
    virtual UINT64  STDMETHODCALLTYPE GetRequiresFlags() { return 0; }
};

#endif /* __cplusplus */


/* typedef aliases expected by DXCommonTypes.h */
typedef D3D11_SHADER_DESC               D3D_SHADER_DESC;
typedef D3D11_SHADER_BUFFER_DESC        D3D_SHADER_BUFFER_DESC;
typedef D3D11_SHADER_VARIABLE_DESC      D3D_SHADER_VARIABLE_DESC;
typedef D3D11_SHADER_INPUT_BIND_DESC    D3D_SHADER_INPUT_BIND_DESC;
typedef D3D11_SHADER_TYPE_DESC          D3D_SHADER_TYPE_DESC;
typedef D3D11_CBUFFER_TYPE              D3D_CBUFFER_TYPE_ALIAS; /* use D3D_CBUFFER_TYPE directly */

#ifdef __cplusplus
typedef ID3D11ShaderReflection              ID3DShaderReflection;
typedef ID3D11ShaderReflectionConstantBuffer ID3DShaderReflectionConstantBuffer;
typedef ID3D11ShaderReflectionVariable      ID3DShaderReflectionVariable;
typedef ID3D11ShaderReflectionType          ID3DShaderReflectionType;
#endif

#include "d3d9types.h"
#include "d3d_aliases.h"

#endif /* __D3D11_H__ */