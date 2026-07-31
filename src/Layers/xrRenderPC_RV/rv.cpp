#include "rv.hpp"
#include "vulkan_main.hpp"

CRender RImplementation;


void CRender::OnFrame() {
    render_stub_unimpl();

    g_pGamePersistent->GrassBendersUpdateAnimations();
}

void CRender::create() {
    Device.seqFrame.Add(this,REG_PRIORITY_HIGH + 0x12345678);

    // TODO: query graphics caps here.
    // o.ssfx_core = FS.exist(fn, "$game_shaders$", "r3\\screenspace_common", ".h") ? 1 : 0;
	// o.ssfx_rain = FS.exist(fn, "$game_shaders$", "r3\\effects_rain_splash", ".ps") ? 1 : 0;
	// o.ssfx_blood = FS.exist(fn, "$game_shaders$", "r3\\effects_wallmark_blood", ".ps") ? 1 : 0;
	// o.ssfx_branches = FS.exist(fn, "$game_shaders$", "r3\\deffer_tree_branch_aref_bump-hq", ".ps") ? 1 : 0;
	// o.ssfx_hud_raindrops = FS.exist(fn, "$game_shaders$", "r3\\deffer_base_hud_bump", ".ps") ? 1 : 0;
	// o.ssfx_ssr = FS.exist(fn, "$game_shaders$", "r3\\ssfx_ssr", ".ps") ? 1 : 0;
	// o.ssfx_terrain = FS.exist(fn, "$game_shaders$", "r3\\deffer_terrain_high_flat_d", ".ps") ? 1 : 0;
	// o.ssfx_volumetric = FS.exist(fn, "$game_shaders$", "r3\\ssfx_volumetric_blur", ".ps") ? 1 : 0;
	// o.ssfx_water = FS.exist(fn, "$game_shaders$", "r3\\ssfx_water", ".ps") ? 1 : 0;
	// o.ssfx_ao = FS.exist(fn, "$game_shaders$", "r3\\ssfx_ao", ".ps") ? 1 : 0;
	// o.ssfx_il = FS.exist(fn, "$game_shaders$", "r3\\ssfx_il", ".ps") ? 1 : 0;
	// o.ssfx_sss = FS.exist(fn, "$game_shaders$", "r3\\ssfx_sss", ".ps") ? 1 : 0;
	// o.ssfx_bloom = FS.exist(fn, "$game_shaders$", "r3\\ssfx_bloom", ".ps") ? 1 : 0;
	// o.ssfx_taa = FS.exist(fn, "$game_shaders$", "r3\\ssfx_taa", ".ps") ? 1 : 0;
	// o.ssfx_fog = FS.exist(fn, "$game_shaders$", "r3\\ssfx_fog_scattering", ".ps") ? 1 : 0;
	// o.ssfx_motionblur = FS.exist(fn, "$game_shaders$", "r3\\ssfx_motion_blur", ".ps") ? 1 : 0;
	// o.ssfx_motionvectors = FS.exist(fn, "$game_shaders$", "r3\\screenspace_mvectors", ".h") ? 1 : 0;
	// o.ssfx_glass = FS.exist(fn, "$game_shaders$", "r3\\ssfx_glass", ".ps") ? 1 : 0;

    // CResourceManager* RM = dxRenderDeviceRender::Instance().Resources;
	// RM->RegisterConstantSetup("parallax", &binder_parallax);
	// RM->RegisterConstantSetup("water_intensity", &binder_water_intensity);
	// RM->RegisterConstantSetup("sun_shafts_intensity", &binder_sun_shafts_intensity);
	// RM->RegisterConstantSetup("m_AlphaRef", &binder_alpha_ref);
	// RM->RegisterConstantSetup("pos_decompression_params", &binder_pos_decompress_params);
	// RM->RegisterConstantSetup("pos_decompression_params2", &binder_pos_decompress_params2);
	// RM->RegisterConstantSetup("triLOD", &binder_LOD);
	// RM->RegisterConstantSetup("hmodel_stuff", &binder_meatchunks_stuff);


    render_stub_unimpl();
}

void CRender::destroy() 
{
    Device.seqFrame.Remove(this);
}

void CRender::Render() {

	bool _menu_pp = g_pGamePersistent ? g_pGamePersistent->OnRenderPPUI_query() : false;
	if (_menu_pp)
	{
		render_menu();
		return;
	};

	IMainMenu* pMainMenu = g_pGamePersistent ? g_pGamePersistent->m_pMainMenu : 0;
	bool bMenu = pMainMenu ? pMainMenu->CanSkipSceneRendering() : false;

	// if (!(g_pGameLevel && g_hud)
	// 	|| bMenu)
	// {
	// 	//Target->u_setrt(Device.dwWidth, Device.dwHeight, HW.pBaseRT,NULL,NULL, HW.pBaseZB);
	// 	return;
	// }


	// postprocess
	CEnvDescriptorMixer& envdesc = *g_pGamePersistent->Environment().CurrentEnv;
	g_pGamePersistent->OnRenderPPUI_PP();


	render_stub_unimpl();
}

void CRender::render_menu() {
	g_pGamePersistent->OnRenderPPUI_main(); // PP-UI
			g_pGamePersistent->OnRenderPPUI_PP(); // PP-UI

}



