#pragma once

#include "VkHW.hpp"
#include <RenderDeviceRender.h>
#include <device.h>
#include "ResourceManager.hpp"

#define DEV = vkRenderDeviceRender::Instance().Resources

class CResourceManager;

class vkRenderDeviceRender : public IRenderDeviceRender
{
public:
	static vkRenderDeviceRender& Instance() { return *((vkRenderDeviceRender*)(&*Device.m_pRender)); }

	vkRenderDeviceRender();

	virtual void Copy(IRenderDeviceRender& _in);

	//	Gamma correction functions
	// DXGI shit. Ignore it.
	virtual void setGamma(float fGamma) {render_stub();}
	virtual void setBrightness(float fGamma) {render_stub();}
	virtual void setContrast(float fGamma) {render_stub();}
	virtual void updateGamma() {render_stub();}

	//	Destroy
	virtual void OnDeviceDestroy(BOOL bKeepTextures);
	virtual void ValidateHW();
	virtual void DestroyHW();
	virtual void Reset(SDL_Window* window, u32& dwWidth, u32& dwHeight, float& fWidth_2, float& fHeight_2);
	//	Init
	virtual void SetupStates();
	virtual void OnDeviceCreate(LPCSTR shName);
	virtual void Create(SDL_Window* window, u32& dwWidth, u32& dwHeight, float& fWidth_2, float& fHeight_2, bool);
	virtual void SetupGPU(BOOL bForceGPU_SW, BOOL bForceGPU_NonPure, BOOL bForceGPU_REF);
	//	Overdraw
	virtual void overdrawBegin();
	virtual void overdrawEnd();

	//	Resources control
	virtual void DeferredLoad(BOOL E);
	virtual void ResourcesDeferredUpload();
	virtual void ResourcesDeferredUnload();
	virtual void ResourcesGetMemoryUsage(u32& m_base, u32& c_base, u32& m_lmaps, u32& c_lmaps);
	virtual void ResourcesDestroyNecessaryTextures();
	virtual void ResourcesStoreNecessaryTextures();
	virtual void ResourcesDumpMemoryUsage();
	virtual void ResourcesPrefetchCreateTexture(LPCSTR name);

	//	HWSupport
	virtual bool HWSupportsShaderYUV2RGB();

	//	Device state
	virtual DeviceState GetDeviceState();
	virtual BOOL GetForceGPU_REF();
	virtual u32 GetCacheStatPolys();
	virtual void Begin();
	virtual void Clear();
	virtual void End();
	virtual void ClearTarget();
	virtual void SetCacheXform(Fmatrix& mView, Fmatrix& mProject);
	virtual void SetCacheXform_prev(Fmatrix& mView, Fmatrix& mProject);
	virtual void OnAssetsChanged();

public:
	CResourceManager* Resources;
	SDL_Window* window;
};


// #endif //ifndef _EDITOR


// #endif	//	RenderDeviceRender_included
