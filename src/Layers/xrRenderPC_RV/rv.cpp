///////////////// volk / vma implementation.
#define VOLK_IMPLEMENTATION
#include "volk.h"
#define VMA_IMPLEMENTATION
#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 0
#include "vk_mem_alloc.h"
/////////////////

#include "rv.hpp"
#include "VkHW.hpp"
#include "vulkan_main.hpp"
#include <CustomHUD.h>
#include <IGame_Level.h>

CRender RImplementation;

void CRender::OnFrame() {
  render_stub_unimpl();

  g_pGamePersistent->GrassBendersUpdateAnimations();
}

void CRender::create() {
  render_stub_unimpl();
  Device.seqFrame.Add(this, REG_PRIORITY_HIGH + 0x12345678);

  // TODO: query graphics caps here.
}

void CRender::destroy() { Device.seqFrame.Remove(this); }

void CRender::Render() {
  render_stub_unimpl();

  auto &frameData = HW.get_current_frame();

  VkClearColorValue cl;
  cl.float32[0] = 1.0f;
  cl.float32[1] = 1.0f;
  cl.float32[2] = 1.0f;
  cl.float32[3] = 1.0f;

  VkImageSubresourceRange range = {
      .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .baseMipLevel = 0,
      .levelCount = 1,
      .baseArrayLayer = 0,
      .layerCount = 1,
  };

  vkCmdClearColorImage(frameData.cmdBuffer, HW.drawImage.image,
                       VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, &cl, 1,
                       &range);

  bool _menu_pp =
      g_pGamePersistent ? g_pGamePersistent->OnRenderPPUI_query() : false;
  if (_menu_pp) {
    render_menu();
    return;
  };

  IMainMenu *pMainMenu = g_pGamePersistent ? g_pGamePersistent->m_pMainMenu : 0;
  bool bMenu = pMainMenu ? pMainMenu->CanSkipSceneRendering() : false;

  
   //if (!(g_pGameLevel && g_hud) || bMenu)
    //return;

  // {
  // 	//Target->u_setrt(Device.dwWidth, Device.dwHeight, HW.pBaseRT,NULL,NULL,
  // HW.pBaseZB); 	return;
  // }

  // postprocess
  CEnvDescriptorMixer &envdesc = *g_pGamePersistent->Environment().CurrentEnv;
  //g_pGamePersistent->OnRenderPPUI_PP();
}

void CRender::render_menu() {
  g_pGamePersistent->OnRenderPPUI_main(); // PP-UI
  //g_pGamePersistent->OnRenderPPUI_PP();   // PP-UI
}

auto CRender::getRenderTargetSize() -> glm::vec2 {
  // TODO: 
  auto ext3d = HW.get_ActiveTextureExtent();
  return glm::vec2(HW.drawExtent.width, HW.drawExtent.height);
}
