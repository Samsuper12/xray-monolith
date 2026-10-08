module;

#define VOLK_IMPLEMENTATION
#include "volk.h"
#define VMA_IMPLEMENTATION
#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 0
#include "vk_mem_alloc.h"

#include "render_stub.hpp"
#include "vulkan_main.hpp"
#include <CustomHUD.h>
#include <FS.h>
#include <IGame_Level.h>
#include <IGame_Persistent.h>
#include <IRenderDetailModel.h>
#include <Kinematics.h>
#include <LocatorAPI.h>
#include <Render.h>
#include <device.h>

export module xr.RV;
export import RV.Utils;
export import RV.HW;
export import RV.ResourceManager;
export import RV.RenderFactory;

export class CRender : public IRender_interface, public pureFrame {

public:
  bool is_sun();

public:
  virtual void OnFrame();

  IRender_Sector *rimp_detectSector(Fvector &P, Fvector &D) {
    render_stub();
    return nullptr;
  }
  void render_main(Fmatrix &mCombined, bool _fportals) { render_stub(); }
  void render_forward() { render_stub(); }
  void render_Reticle() { render_stub(); }
  void render_smap_direct(Fmatrix &mCombined) { render_stub(); }
  void render_indirect(light *L) { render_stub(); }
  // void render_lights(light_Package& LP)  {render_stub();}
  void render_sun() { render_stub(); }
  void render_sun_near() { render_stub(); }
  void render_sun_filtered() { render_stub(); }
  void render_menu();
  void render_rain() { render_stub(); }

  void render_sun_cascade(u32 cascade_ind) { render_stub(); }
  void init_cacades() { render_stub(); }
  void render_sun_cascades() { render_stub(); }

  IRender_Portal *getPortal(int id) { render_stub(); }
  IRender_Sector *getSectorActive() { render_stub(); }
  IRenderVisual *model_CreatePE(LPCSTR name) { render_stub(); }
  IRender_Sector *detectSector(const Fvector &P, Fvector &D) { render_stub(); }
  int translateSector(IRender_Sector *pSector) { render_stub(); }

  // HW-occlusion culling
  inline u32 occq_begin(u32 &ID) { render_stub(); }
  inline void occq_end(u32 &ID) { render_stub(); }

  inline void apply_object(IRenderable *O) {
    {
      render_stub();
    }
  }

  inline void apply_lmaterial() {
    {
      render_stub();
    }
  }

  // feature level
  virtual GenerationLevel get_generation() override { render_stub(); }

  virtual bool is_sun_static() override { render_stub(); }
  virtual uint32_t get_dx_level() override { render_stub(); }

  // Loading / Unloading
  virtual void create();
  virtual void destroy();
  virtual void reset_begin() override { render_stub(); }
  virtual void reset_end() override { render_stub(); }

  virtual void level_Load(IReader *) override { render_stub(); }
  virtual void level_Unload() override { render_stub(); }

  // Information
  virtual void Statistics(CGameFont *F) override { render_stub(); }
  virtual std::string getShaderPath() override { return "rv/"; }
  // virtual ref_shader getShader(int id)  {render_stub();}
  virtual IRender_Sector *getSector(int id) override { render_stub(); }
  virtual IRenderVisual *getVisual(int id) override { render_stub(); }
  virtual IRender_Sector *detectSector(const Fvector &P) override {
    render_stub();
  }
  virtual IRender_Target *getTarget() override { render_stub(); }
  auto getRenderTargetSize() -> glm::vec2 override;
  virtual u32 memory_usage() { render_stub(); }

  // Main
  virtual void flush() override { render_stub(); }
  virtual void set_Object(IRenderable *O) override { render_stub(); }
  virtual void add_Occluder(Fbox2 &bb_screenspace) override {
    render_stub();
  } // mask screen region as oclluded
  virtual void add_Visual(IRenderVisual *V) override {
    render_stub();
  } // add visual leaf	(no culling performed at all)
  virtual void add_Geometry(IRenderVisual *V) override {
    render_stub();
  } // add visual(s)	(all culling performed)

  virtual void add_StaticWallmark(IWallMarkArray *pArray, const Fvector &P,
                                  float s, CDB::TRI *T, Fvector *V, float ttl,
                                  bool ignore_opt, float rotation) override {
    render_stub();
  }

  virtual void add_StaticWallmark(const wm_shader &S, const Fvector &P, float s,
                                  CDB::TRI *T, Fvector *V) override {
    render_stub();
  }
  virtual void clear_static_wallmarks() override { render_stub(); }

  virtual void add_SkeletonWallmark(const Fmatrix *xf, IKinematics *obj,
                                    IWallMarkArray *pArray,
                                    const Fvector &start, const Fvector &dir,
                                    float size, float ttl = 0.f,
                                    bool ignore_opt = false) override {
    render_stub();
  }

  virtual void add_StaticWallmark(IWallMarkArray *pArray, const Fvector &P,
                                  float s, CDB::TRI *T, Fvector *V,
                                  float ttl = 0.f, bool ignore_opt = false,
                                  bool random_rotation = true) {
    render_stub();
  }

  virtual void set_Transform(Fmatrix *M) { render_stub(); }

  virtual void set_HUD(BOOL V) { render_stub(); }
  virtual BOOL get_HUD() { render_stub(); }
  virtual void set_CamAttached(BOOL V) { render_stub(); }
  virtual BOOL get_CamAttached() { render_stub(); }
  virtual void set_Invisible(BOOL V) { render_stub(); }

  virtual bool shader_compile(LPCSTR name, uint32_t const *pSrcData,
                              uint SrcDataLen, LPCSTR pFunctionName,
                              LPCSTR pTarget, uint32_t Flags, void *&result) {
    render_stub();
  }

  //
  virtual IRender_ObjectSpecific *ros_create(IRenderable *parent) override {
    render_stub();
  }
  virtual void ros_destroy(IRender_ObjectSpecific *&) override {
    render_stub();
  }

  // Lighting
  virtual IRender_Light *light_create() override { render_stub(); }
  virtual IRender_Glow *glow_create() override { render_stub(); }

  // Models
  virtual IRenderVisual *model_CreateParticles(LPCSTR name) override {
    render_stub();
  }
  virtual IRender_DetailModel *model_CreateDM(IReader *F) { render_stub(); }
  virtual IRenderVisual *model_Create(LPCSTR name, IReader *data = nullptr);
  virtual IRenderVisual *model_CreateChild(LPCSTR name,
                                           IReader *data) override {
    render_stub();
  }
  virtual IRenderVisual *model_Duplicate(IRenderVisual *V) override {
    render_stub();
  }
  virtual void model_Delete(IRenderVisual *&V, BOOL bDiscard) override {
    render_stub();
  }
  virtual void model_Delete(IRender_DetailModel *&F) { render_stub(); }
  virtual void model_Logging(BOOL bEnable) override {
    render_stub();
  } // { Models->Logging(bEnable); }
  virtual void models_Prefetch() override { render_stub(); }
  virtual void models_PrefetchOne(LPCSTR name, bool assert = true) override {
    render_stub();
  }
  virtual void models_Clear(BOOL b_complete) override { render_stub(); }
  virtual bool models_Exists(LPCSTR name) override { render_stub(); }

  // anglobes: Sun Values
  virtual Fvector GetSunPosition() override{{render_stub();
}
}
;
virtual Fcolor GetSunColor() override{{render_stub();
}
}
;
virtual float GetSunIntensity() override{{render_stub();
}
}
;
virtual bool IsSun() override { render_stub(); }

// Occlusion culling
virtual BOOL occ_visible(vis_data &V) override { render_stub(); }
virtual BOOL occ_visible(Fbox &B) override { render_stub(); }
virtual BOOL occ_visible(sPoly &P) override { render_stub(); }

// Main
virtual void Calculate() override { render_stub(); }
virtual void Render();
virtual void Screenshot(ScreenshotMode mode = SM_NORMAL,
                        LPCSTR name = 0) override {
  render_stub();
}
virtual void Screenshot(ScreenshotMode mode,
                        CMemoryWriter &memory_writer) override {
  render_stub();
}
virtual void ScreenshotAsyncBegin() override { render_stub(); }
virtual void ScreenshotAsyncEnd(CMemoryWriter &memory_writer) override {
  render_stub();
}

// Particles
virtual void ExportParticles() override { render_stub(); }
virtual void ImportParticles() override { render_stub(); }

// Render mode
virtual void rmNear() override { render_stub(); }
virtual void rmFar() override { render_stub(); }
virtual void rmNormal() override { render_stub(); }
virtual u32 active_phase() override {
  render_stub();
} // { return phase; }; //Swartz: actor shadow
void RenderToTarget(RRT target) override { render_stub(); }
// Constructor/destructor/loader
CRender() { render_stub(); }
virtual ~CRender() { render_stub(); }

void addShaderOption(const char *name, const char *value) { render_stub(); }
void clearAllShaderOptions() { render_stub(); } // { m_ShaderOptions.clear(); }

protected:
virtual void ScreenshotImpl(ScreenshotMode mode, LPCSTR name,
                            CMemoryWriter *memory_writer) override {
  render_stub();
}
}
;

export CRender RImplementation;

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

  // if (!(g_pGameLevel && g_hud) || bMenu)
  // return;

  // {
  // 	//Target->u_setrt(Device.dwWidth, Device.dwHeight, HW.pBaseRT,NULL,NULL,
  // HW.pBaseZB); 	return;
  // }

  // postprocess
  CEnvDescriptorMixer &envdesc = *g_pGamePersistent->Environment().CurrentEnv;
  // g_pGamePersistent->OnRenderPPUI_PP();
}

void CRender::render_menu() {
  g_pGamePersistent->OnRenderPPUI_main(); // PP-UI
  // g_pGamePersistent->OnRenderPPUI_PP();   // PP-UI
}

auto CRender::getRenderTargetSize() -> glm::vec2 {
  // TODO:
  auto ext3d = HW.get_ActiveTextureExtent();
  return glm::vec2(HW.drawExtent.width, HW.drawExtent.height);
}

IRenderVisual *CRender::model_Create(LPCSTR name,
                                     [[maybe_unused]] IReader *data) {
  std::fs::path modelPath;
  if (!FS.exist(modelPath, "$game_meshes$", name, ".ogf")) {
    if (!FS.exist(modelPath, "$level$", name, ".ogf")) {
      Msg("[RV][ERR]: model % not found", name);
      // TODO: load default instead
      return nullptr;
    }
  }

  // IRenderVisual *V = nullptr;
  // IReader *modelReader = FS.r_open(modelPath.c_str());
  // switch (H.type) {
  //   // 	case MT_NORMAL: // our base visual
  //   // 		V = xr_new<Fvisual>();
  //   // 		break;
  //   // 	case MT_HIERRARHY:
  //   // 		V = xr_new<FHierrarhyVisual>();
  //   // 		break;
  //   // 	case MT_PROGRESSIVE: // dynamic-resolution visual
  //   // 		V = xr_new<FProgressive>();
  //   // 		break;
  //   // 	case MT_SKELETON_ANIM:
  //   // 		V = xr_new<CKinematicsAnimated>();
  //   // 		break;
  //   // 	case MT_SKELETON_RIGID:
  //   // 		V = xr_new<CKinematics>();
  //   // 		break;
  //   // 	case MT_SKELETON_GEOMDEF_PM:
  //   // 		V = xr_new<CSkeletonX_PM>();
  //   // 		break;
  //   // 	case MT_SKELETON_GEOMDEF_ST:
  //   // 		V = xr_new<CSkeletonX_ST>();
  //   // 		break;
  //   // 	case MT_PARTICLE_EFFECT:
  //   // 		V = xr_new<PS::CParticleEffect>();
  //   // 		break;
  //   // 	case MT_PARTICLE_GROUP:
  //   // 		V = xr_new<PS::CParticleGroup>();
  //   // 		break;
  //   // #ifndef _EDITOR
  //   // 	case MT_LOD:
  //   // 		V = xr_new<FLOD>();
  //   // 		break;
  //   // 	case MT_TREE_ST:
  //   // 		V = xr_new<FTreeVisual_ST>();
  //   // 		break;
  //   // 	case MT_TREE_PM:
  //   // 		V = xr_new<FTreeVisual_PM>();
  //   // 		break;
  //   // #endif
  // default:
  //   Msg("[RV][ERR]: unexpected ogf model type: %d", H.type);
  //   return nullptr;
  // }

  // DEV()->CreateModel(V);
  // FS.r_close(data);
  // // return DEV->CreateModel(name);
}
