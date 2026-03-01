#include "vkR_Backend_Runtime.hpp"

// ShaderElement* CRender::rimp_select_sh_dynamic(dxRender_Visual* pVisual, float cdist_sq)
// {
//     stub();
// }

// ShaderElement* CRender::rimp_select_sh_static(dxRender_Visual* pVisual, float cdist_sq)
// {
// 	stub();
// }

#include "dxRenderFactory.h"

void __cdecl dxRenderFactory::DestroyApplicationRender(class IApplicationRender *) { stub(); }
int __cdecl DllMainXrRenderRV(void *, unsigned long, void *) { stub(); }
void __cdecl xrRender_initconsole(void) { stub(); }
void __cdecl dxRenderFactory::DestroyUIShader(class IUIShader *) { stub(); }
IUIShader *__cdecl dxRenderFactory::CreateUIShader(void) { stub(); }
IFontRender *__cdecl dxRenderFactory::CreateFontRender(void) { stub(); }
void __cdecl dxRenderFactory::DestroyFontRender(class IFontRender *) { stub(); }
_vector4<float> ps_ssfx_grass_interactive;
_flags<unsigned int> psDeviceFlags2;
struct _vector4<float> ps_ssfx_wind_trees;

IRenderDeviceRender *__cdecl dxRenderFactory::CreateRenderDeviceRender(void) { stub(); }
void __cdecl dxRenderFactory::DestroyRenderDeviceRender(class IRenderDeviceRender *) { stub(); }
__cdecl R_occlusion::R_occlusion(void) { stub(); }
__cdecl CLight_DB::CLight_DB(void) { stub(); }
__cdecl CLight_DB::~CLight_DB(void) { stub(); }
__cdecl R_occlusion::~R_occlusion(void) { stub(); }

void __cdecl CRender::add_SkeletonWallmark(struct _matrix<float> const *, class CKinematics *, class resptr_core<struct Shader, struct resptrcode_shader> &, struct _vector3<float> const &, struct _vector3<float> const &, float, float, bool) { stub(); }

void __cdecl dxRenderFactory::DestroyStatsRender(class IStatsRender *) { stub(); }
IStatsRender *__cdecl dxRenderFactory::CreateStatsRender(void) { stub(); }
void __cdecl dxRenderFactory::DestroyFlareRender(class IFlareRender *) { stub(); }
IFlareRender *__cdecl dxRenderFactory::CreateFlareRender(void) { stub(); }
void __cdecl dxRenderFactory::DestroyEnvDescriptorRender(class IEnvDescriptorRender *) { stub(); }
void __cdecl dxRenderFactory::DestroyEnvDescriptorMixerRender(class IEnvDescriptorMixerRender *) { stub(); }
void __cdecl dxRenderFactory::DestroyEnvironmentRender(class IEnvironmentRender *) { stub(); }
IEnvironmentRender *__cdecl dxRenderFactory::CreateEnvironmentRender(void) { stub(); }
void __cdecl dxRenderFactory::DestroyImGuiRender(class IImGuiRender *) { stub(); }
IImGuiRender *__cdecl dxRenderFactory::CreateImGuiRender(void) { stub(); }
__cdecl Shader::~Shader(void) { stub(); }
float hud_fov_aim_factor;
float sil_glow_cool_temp_rate;

__cdecl ShaderElement::~ShaderElement(void) { stub(); }
void __cdecl CPSLibrary::particles_group_next(class PS::CPGDef const *const *&) const { stub(); }
shared_str const &__cdecl CPSLibrary::particles_group_id(class PS::CPGDef const &) const { stub(); }
IEnvDescriptorRender *__cdecl dxRenderFactory::CreateEnvDescriptorRender(void) { stub(); }
IEnvDescriptorMixerRender *__cdecl dxRenderFactory::CreateEnvDescriptorMixerRender(void) { stub(); }
int r_optimize_calculate_bones;
float wallmark_range_static;
float wallmark_range_skeleton;
_vector4<float> ps_ssfx_int_grass_params_2;
float sil_glow_shot_temp;
float sil_glow_max_temp;
_flags<unsigned int> ps_actor_shadow_flags;
int ps_r4_hdr10_pda;
ILensFlareRender *__cdecl dxRenderFactory::CreateLensFlareRender(void) { stub(); }
void __cdecl dxRenderFactory::DestroyLensFlareRender(class ILensFlareRender *) { stub(); }
IThunderboltDescRender *__cdecl dxRenderFactory::CreateThunderboltDescRender(void) { stub(); }
IApplicationRender *dxRenderFactory::CreateApplicationRender(void)
{
    stub();
}

IThunderboltRender *dxRenderFactory::CreateThunderboltRender(void)
{
    stub();
}

void dxRenderFactory::DestroyThunderboltRender(IThunderboltRender *)
{
    stub();
}

IRainRender *dxRenderFactory::CreateRainRender(void)
{
    stub();
}

void dxRenderFactory::DestroyRainRender(IRainRender *)
{
    stub();
}

IWallMarkArray *dxRenderFactory::CreateWallMarkArray(void)
{
    stub();
}

void dxRenderFactory::DestroyWallMarkArray(IWallMarkArray *)
{
    stub();
}

IStatGraphRender *dxRenderFactory::CreateStatGraphRender(void)
{
    stub();
}

void dxRenderFactory::DestroyStatGraphRender(IStatGraphRender *)
{
    stub();
}

IUISequenceVideoItem *dxRenderFactory::CreateUISequenceVideoItem(void)
{
    stub();
}

void dxRenderFactory::DestroyThunderboltDescRender(IThunderboltDescRender *)
{
    stub();
}

dxRenderFactory RenderFactoryImpl;

SPass::~SPass(void)
{
    stub();
}

PS::CPGDef const *const *CPSLibrary::particles_group_begin(void) const
{
    stub();
}

PS::CPGDef const *const *CPSLibrary::particles_group_end(void) const
{
    stub();
}

int heat_vision_cooldown;
float heat_vision_cooldown_time;
int ps_r2_heatvision;
int heat_vision_zombie_cold;

_vector4<float> ps_ssfx_int_grass_params_1;

SState::~SState(void)
{
    stub();
}

SPS::~SPS(void)
{
    stub();
}

SVS::~SVS(void)
{
    stub();
}

SGS::~SGS(void)
{
    stub();
}

SHS::~SHS(void)
{
    stub();
}

SDS::~SDS(void)
{
    stub();
}

SCS::~SCS(void)
{
    stub();
}

R_constant_table::~R_constant_table(void)
{
    stub();
}

STextureList::~STextureList(void)
{
    stub();
}

SConstantList::~SConstantList(void)
{
    stub();
}

void dxRenderFactory::DestroyUISequenceVideoItem(IUISequenceVideoItem *)
{
    stub();
}

void STextureList::clear(void)
{
    stub();
}

void STextureList::clear_not_free(void)
{
    stub();
}

dx10ConstantBuffer::~dx10ConstantBuffer(void)
{
    stub();
}

SInputSignature::~SInputSignature(void)
{
    stub();
}