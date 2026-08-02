#include "vkRenderDeviceRender.hpp"
#include "render_stub.hpp"

#include <Render.h>

static const char* filename = "vkRenderDeviceRender";

// Done
vkRenderDeviceRender::vkRenderDeviceRender() : Resources(nullptr) {}

void vkRenderDeviceRender::Copy(IRenderDeviceRender& _in) {*this = *(vkRenderDeviceRender*)&_in;}


void vkRenderDeviceRender::Create(SDL_Window* window, u32& dwWidth, u32& dwHeight, float& fWidth_2, float& fHeight_2,
                                  bool move_window) {
    this->window = window;
    HW.CreateDevice(window, {dwWidth, dwHeight});
	fWidth_2 = float(dwWidth / 2);
	fHeight_2 = float(dwHeight / 2);
    Resources = xr_new<CResourceManager>();
}

void vkRenderDeviceRender::OnDeviceCreate(LPCSTR shName) {
    //RCache.OnDeviceCreate();
	Resources->OnDeviceCreate(shName);
	::Render->create();
	Device.Statistic->OnDeviceCreate();


	//m_WireShader.create("editor\\wire");
	//m_SelectionShader.create("editor\\selection");

	//DUImpl.OnDeviceCreate();
}

void vkRenderDeviceRender::Begin() {
	HW.BeginRendering();

	//CHK_DX(HW.pDevice->BeginScene()); eq to glBegin or vkCmdBeginRendering
	// RCache.OnFrameBegin();
	// RCache.set_CullMode(CULL_CW);
	// RCache.set_CullMode(CULL_CCW);
	//if (HW.Caps.SceneMode) overdrawBegin();
	
	render_stub_unimpl();

}

void vkRenderDeviceRender::End() {
	// 	VERIFY(HW.pDevice);

	// if (HW.Caps.SceneMode) overdrawEnd();

	// RCache.OnFrameEnd();
	// Memory.dbg_check();

	// DoAsyncScreenshot();
	HW.EndRendering();


#if defined(USE_DX10) || defined(USE_DX11)
    // UINT present_flags = 0;
	// bool use_vsync = !!psDeviceFlags.test(rsVSync);
	// UINT present_interval = (use_vsync) ? 1 : 0;

# if defined(USE_DX11)
	// NOTE: https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/variable-refresh-rate-displays
    // BOOL is_windowed = HW.m_ChainDescFullscreen.Windowed;
	// if (is_windowed && !use_vsync && HW.m_SupportsVRR) {
    //     present_flags |= DXGI_PRESENT_ALLOW_TEARING;
	// }
# endif

	// if (!Device.m_SecondViewport.IsSVPFrame() && !Device.m_SecondViewport.isCamReady) {
	// 	HW.m_pSwapChain->Present(present_interval, present_flags);
	//}
#else //!USE_DX10 || USE_DX11
	// CHK_DX(HW.pDevice->EndScene());

	// if (!Device.m_SecondViewport.IsSVPFrame() && !Device.m_SecondViewport.isCamReady)
	// 	HW.pDevice->Present(NULL, NULL, NULL, NULL);
#endif //-USE_DX10
	//HRESULT _hr		= HW.pDevice->Present( NULL, NULL, NULL, NULL );
	//if				(D3DERR_DEVICELOST==_hr)	return;			// we will handle this later
	render_stub_unimpl();
}
void vkRenderDeviceRender::SetCacheXform(Fmatrix& mView, Fmatrix& mProject) {render_stub();}
void vkRenderDeviceRender::SetCacheXform_prev(Fmatrix& mView, Fmatrix& mProject) {render_stub();}


IRenderDeviceRender::DeviceState vkRenderDeviceRender::GetDeviceState() {return IRenderDeviceRender::dsOK;}
// no overdraw
void vkRenderDeviceRender::overdrawBegin() {}
void vkRenderDeviceRender::overdrawEnd() {}




void vkRenderDeviceRender::Clear() {

	if(!HW.IsReady) return;

	HW.immediateSubmit([](VkCommandBuffer cmd) {
		VkClearValue cl{0.0f, 0.0f, 0.0f, 1.0f};
		// stencil, depth and color
		//vkCmdClearColorImage(cmd, HW.drawImage, HW.drawImageLayout, &cl, 0, nullptr);
	});
}


// Not yet

void vkRenderDeviceRender::SetupGPU(BOOL bForceGPU_SW, BOOL bForceGPU_NonPure, BOOL bForceGPU_REF)
{
    render_stub();
	// HW.Caps.bForceGPU_SW = bForceGPU_SW;
	// HW.Caps.bForceGPU_NonPure = bForceGPU_NonPure;
	// HW.Caps.bForceGPU_REF = bForceGPU_REF;
}

void vkRenderDeviceRender::OnDeviceDestroy(BOOL bKeepTextures) {render_stub();}
void vkRenderDeviceRender::ValidateHW() {render_stub();}
void vkRenderDeviceRender::DestroyHW() {render_stub();}
void vkRenderDeviceRender::Reset(SDL_Window* window, u32& dwWidth, u32& dwHeight, float& fWidth_2, float& fHeight_2) {render_stub();}

void vkRenderDeviceRender::SetupStates() {render_stub();}

void vkRenderDeviceRender::DeferredLoad(BOOL E) {render_stub();}
void vkRenderDeviceRender::ResourcesDeferredUpload() {render_stub();}
void vkRenderDeviceRender::ResourcesDeferredUnload() {render_stub();}
void vkRenderDeviceRender::ResourcesDestroyNecessaryTextures() {render_stub();}
void vkRenderDeviceRender::ResourcesStoreNecessaryTextures() {render_stub();}
void vkRenderDeviceRender::ResourcesDumpMemoryUsage() {render_stub();}
void vkRenderDeviceRender::ResourcesPrefetchCreateTexture(LPCSTR name) {render_stub();}

bool vkRenderDeviceRender::HWSupportsShaderYUV2RGB() { render_stub(); }

BOOL        vkRenderDeviceRender::GetForceGPU_REF() { render_stub(); }
u32         vkRenderDeviceRender::GetCacheStatPolys() { render_stub(); }

void vkRenderDeviceRender::ClearTarget() {render_stub();}
void vkRenderDeviceRender::OnAssetsChanged() {render_stub();}
void vkRenderDeviceRender::ResourcesGetMemoryUsage(u32& m_base, u32& c_base, u32& m_lmaps, u32& c_lmaps) {render_stub();};