#pragma once
#ifndef __D3D_ALIASES_H__
#define __D3D_ALIASES_H__

/*
 * d3d_aliases.h - X-Ray Engine ID3D* type aliases for Linux compilation.
 * Maps renderer-agnostic ID3D* names to D3D11 types.
 */

#ifdef __cplusplus

/* --- Shaders --- */
typedef ID3D11VertexShader          ID3DVertexShader;
typedef ID3D11PixelShader           ID3DPixelShader;
typedef ID3D11GeometryShader        ID3DGeometryShader;
typedef ID3D11HullShader            ID3DHullShader;
typedef ID3D11DomainShader          ID3DDomainShader;
typedef ID3D11ComputeShader         ID3DComputeShader;

/* --- Resources --- */
typedef ID3D11Buffer                ID3DVertexBuffer;
typedef ID3D11Buffer                ID3DIndexBuffer;
typedef ID3D11Buffer                ID3DConstantBuffer;
typedef ID3D11Texture2D             ID3DTexture2D;
typedef ID3D11Texture3D             ID3DTexture3D;
typedef ID3D11Resource              ID3DBaseTexture;

/* --- Views --- */
typedef ID3D11RenderTargetView      ID3DRenderTargetView;
typedef ID3D11DepthStencilView      ID3DDepthStencilView;
typedef ID3D11ShaderResourceView    ID3DShaderResourceView;
typedef ID3D11UnorderedAccessView   ID3DUnorderedAccessView;

/* --- State objects ---
 * NOTE: ID3DState is intentionally omitted here.
 * DXCommonTypes.h defines it as dx10State — let that win. */
typedef ID3D11InputLayout           ID3DVertexDeclaration;
typedef ID3D11RasterizerState       ID3DRasterizerState;
typedef ID3D11DepthStencilState     ID3DDepthStencilState;
typedef ID3D11SamplerState          ID3DSamplerState;

/* --- Device / Context --- */
typedef ID3D11Device                ID3DDevice;
typedef ID3D11DeviceContext         ID3DDeviceContext;

/* --- Queries --- */
typedef ID3D11Query                 ID3DQuery;
typedef ID3D11Predicate             ID3DPredicate;

/* --- Descriptor aliases --- */
// #ifndef __D3D_TEXTURE2D_DESC_DEFINED__
// #define __D3D_TEXTURE2D_DESC_DEFINED__
// typedef D3D11_TEXTURE2D_DESC        D3D_TEXTURE2D_DESC;
// #endif

#ifndef __D3D_TEXTURE3D_DESC_DEFINED__
#define __D3D_TEXTURE3D_DESC_DEFINED__
typedef D3D11_TEXTURE3D_DESC        D3D_TEXTURE3D_DESC;
#endif

#ifndef __D3D_BUFFER_DESC_DEFINED__
#define __D3D_BUFFER_DESC_DEFINED__
typedef D3D11_BUFFER_DESC           D3D_BUFFER_DESC;
#endif

/* --- D3D9 interfaces needed by shared xrRender code --- */

#ifndef __IDirect3DVertexDeclaration9_DEFINED__
#define __IDirect3DVertexDeclaration9_DEFINED__
struct IDirect3DVertexDeclaration9 {
    virtual ~IDirect3DVertexDeclaration9() {}
    virtual int STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObj) { return 0x80004002; }
    virtual unsigned long STDMETHODCALLTYPE AddRef()   { return 0; }
    virtual unsigned long STDMETHODCALLTYPE Release()  { return 0; }
    virtual int STDMETHODCALLTYPE GetDevice(void** ppDevice) { return 0x80004001; }
    virtual int STDMETHODCALLTYPE GetDeclaration(D3DVERTEXELEMENT9* pElement, UINT* pNumElements) { return 0x80004001; }
};
#endif


#endif /* __cplusplus */

/* --- Vertex texture sampler indices --- */
#ifndef D3DDMAPSAMPLER
#define D3DDMAPSAMPLER              256
#endif
#ifndef D3DVERTEXTEXTURESAMPLER0
#define D3DVERTEXTEXTURESAMPLER0    (D3DDMAPSAMPLER + 1)
#define D3DVERTEXTEXTURESAMPLER1    (D3DDMAPSAMPLER + 2)
#define D3DVERTEXTEXTURESAMPLER2    (D3DDMAPSAMPLER + 3)
#define D3DVERTEXTEXTURESAMPLER3    (D3DDMAPSAMPLER + 4)
#endif

#endif /* __D3D_ALIASES_H__ */