#include "rv.hpp"


CRender RImplementation;


// void CRender::create()
// {
// 	Device.seqFrame.Add(this,REG_PRIORITY_HIGH + 0x12345678);

// 	m_skinning = -1;
// 	m_MSAASample = -1;

// 	// hardware
// 	o.smapsize = 2048;
// 	//o.mrt = (HW.Caps.raster.dwMRT_count >= 3);
// 	//o.mrtmixdepth = (HW.Caps.raster.b_MRT_mixdepth);

// 	// Check for NULL render target support
// 	//	DX10 disabled
// 	//D3DFORMAT	nullrt	= (D3DFORMAT)MAKEFOURCC('N','U','L','L');
// 	//o.nullrt			= HW.support	(nullrt,			D3DRTYPE_SURFACE, D3DUSAGE_RENDERTARGET);
// 	o.nullrt = false;
// 	/*
// 	if (o.nullrt)		{
// 	Msg				("* NULLRT supported and used");
// 	};
// 	*/
// 	if (o.nullrt)
// 	{
// 		Msg("* NULLRT supported");

// 		//.	    _tzset			();
// 		//.		??? _strdate	( date, 128 );	???
// 		//.		??? if (date < 22-march-07)		
// 		if (0)
// 		{
// 			u32 device_id = HW.Caps.id_device;
// 			bool disable_nullrt = false;
// 			switch (device_id)
// 			{
// 			case 0x190:
// 			case 0x191:
// 			case 0x192:
// 			case 0x193:
// 			case 0x194:
// 			case 0x197:
// 			case 0x19D:
// 			case 0x19E:
// 				{
// 					disable_nullrt = true; //G80
// 					break;
// 				}
// 			case 0x400:
// 			case 0x401:
// 			case 0x402:
// 			case 0x403:
// 			case 0x404:
// 			case 0x405:
// 			case 0x40E:
// 			case 0x40F:
// 				{
// 					disable_nullrt = true; //G84
// 					break;
// 				}
// 			case 0x420:
// 			case 0x421:
// 			case 0x422:
// 			case 0x423:
// 			case 0x424:
// 			case 0x42D:
// 			case 0x42E:
// 			case 0x42F:
// 				{
// 					disable_nullrt = true; // G86
// 					break;
// 				}
// 			}
// 			if (disable_nullrt) o.nullrt = false;
// 		};
// 		if (o.nullrt) Msg("* ...and used");
// 	};


// 	// SMAP / DST
// 	o.HW_smap_FETCH4 = FALSE;
// 	//	DX10 disabled
// 	//o.HW_smap			= HW.support	(D3DFMT_D24X8,			D3DRTYPE_TEXTURE,D3DUSAGE_DEPTHSTENCIL);
// 	o.HW_smap = true;
// 	o.HW_smap_PCF = o.HW_smap;
// 	if (o.HW_smap)
// 	{
// 		//	For ATI it's much faster on DX10 to use D32F format
// 		if (HW.Caps.id_vendor == 0x1002)
// 			o.HW_smap_FORMAT = D3DFMT_D32F_LOCKABLE;
// 		else
// 			o.HW_smap_FORMAT = D3DFMT_D24X8;
// 		Msg("* HWDST/PCF supported and used");
// 	}

// 	//	DX10 disabled
// 	//o.fp16_filter		= HW.support	(D3DFMT_A16B16G16R16F,	D3DRTYPE_TEXTURE,D3DUSAGE_QUERY_FILTER);
// 	//o.fp16_blend		= HW.support	(D3DFMT_A16B16G16R16F,	D3DRTYPE_TEXTURE,D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING);
// 	o.fp16_filter = true;
// 	o.fp16_blend = true;

// 	// search for ATI formats
// 	if (!o.HW_smap && (0 == strstr(Core.Params, "-nodf24")))
// 	{
// 		o.HW_smap = HW.support((D3DFORMAT)(MAKEFOURCC('D', 'F', '2', '4')), D3DRTYPE_TEXTURE,D3DUSAGE_DEPTHSTENCIL);
// 		if (o.HW_smap)
// 		{
// 			o.HW_smap_FORMAT = MAKEFOURCC('D', 'F', '2', '4');
// 			o.HW_smap_PCF = FALSE;
// 			o.HW_smap_FETCH4 = TRUE;
// 		}
// 		Msg("* DF24/F4 supported and used [%X]", o.HW_smap_FORMAT);
// 	}

// 	// emulate ATI-R4xx series
// 	if (strstr(Core.Params, "-r4xx"))
// 	{
// 		o.mrtmixdepth = FALSE;
// 		o.HW_smap = FALSE;
// 		o.HW_smap_PCF = FALSE;
// 		o.fp16_filter = FALSE;
// 		o.fp16_blend = FALSE;
// 	}

// 	VERIFY2(o.mrt && (HW.Caps.raster.dwInstructions>=256), "Hardware doesn't meet minimum feature-level");
// 	if (o.mrtmixdepth) o.albedo_wo = FALSE;
// 	else if (o.fp16_blend) o.albedo_wo = FALSE;
// 	else o.albedo_wo = TRUE;

// 	// nvstencil on NV40 and up
// 	o.nvstencil = FALSE;
// 	//if ((HW.Caps.id_vendor==0x10DE)&&(HW.Caps.id_device>=0x40))	o.nvstencil = TRUE;
// 	if (strstr(Core.Params, "-nonvs")) o.nvstencil = FALSE;

// 	// nv-dbt
// 	//	DX10 disabled
// 	//o.nvdbt				= HW.support	((D3DFORMAT)MAKEFOURCC('N','V','D','B'), D3DRTYPE_SURFACE, 0);
// 	o.nvdbt = false;
// 	if (o.nvdbt) Msg("* NV-DBT supported and used");

// 	o.no_ram_textures = (strstr(Core.Params, "-noramtex")) ? TRUE : ps_r__common_flags.test(RFLAG_NO_RAM_TEXTURES);
// 	if (o.no_ram_textures)
// 		Msg("* Managed textures disabled");
// 	else
// 		Msg("* Managed textures enabled");

// 	// options (smap-pool-size)
// 	if (strstr(Core.Params, "-smap1536")) o.smapsize = 1536;
// 	if (strstr(Core.Params, "-smap2048")) o.smapsize = 2048;
// 	if (strstr(Core.Params, "-smap2560")) o.smapsize = 2560;
// 	if (strstr(Core.Params, "-smap3072")) o.smapsize = 3072;
// 	if (strstr(Core.Params, "-smap4096")) o.smapsize = 4096;

// 	// gloss
// 	char* g = strstr(Core.Params, "-gloss ");
// 	o.forcegloss = g ? TRUE : FALSE;
// 	if (g)
// 	{
// 		o.forcegloss_v = float(atoi(g + xr_strlen("-gloss "))) / 255.f;
// 	}

// 	// options
// 	o.bug = (strstr(Core.Params, "-bug")) ? TRUE : FALSE;
// 	o.sunfilter = (strstr(Core.Params, "-sunfilter")) ? TRUE : FALSE;
// 	//.	o.sunstatic			= (strstr(Core.Params,"-sunstatic"))?	TRUE	:FALSE	;
// 	o.sunstatic = r2_sun_static;
// 	o.advancedpp = r2_advanced_pp;
// 	o.volumetricfog = ps_r2_ls_flags.test(R3FLAG_VOLUMETRIC_SMOKE);
// 	o.sjitter = (strstr(Core.Params, "-sjitter")) ? TRUE : FALSE;
// 	o.depth16 = (strstr(Core.Params, "-depth16")) ? TRUE : FALSE;
// 	if (strstr(Core.Params, "-noshadows") || strstr(Core.Params, "-r4_dev"))
// 		o.noshadows = TRUE;
// 	else
// 		o.noshadows = FALSE;
// 	o.Tshadows = (strstr(Core.Params, "-tsh")) ? TRUE : FALSE;

// 	o.distortion_enabled = (strstr(Core.Params, "-nodistort")) ? FALSE : TRUE;
// 	o.distortion = o.distortion_enabled;
// 	o.disasm = (strstr(Core.Params, "-disasm")) ? TRUE : FALSE;
// 	o.forceskinw = (strstr(Core.Params, "-skinw")) ? TRUE : FALSE;

// 	o.ssao_blur_on = ps_r2_ls_flags_ext.test(R2FLAGEXT_SSAO_BLUR) && (ps_r_ssao != 0);
// 	o.ssao_opt_data = ps_r2_ls_flags_ext.test(R2FLAGEXT_SSAO_OPT_DATA) && (ps_r_ssao != 0);
// 	o.ssao_half_data = ps_r2_ls_flags_ext.test(R2FLAGEXT_SSAO_HALF_DATA) && o.ssao_opt_data && (ps_r_ssao != 0);
// 	o.ssao_hdao = ps_r2_ls_flags_ext.test(R2FLAGEXT_SSAO_HDAO) && (ps_r_ssao != 0);
// 	o.ssao_hbao = !o.ssao_hdao && ps_r2_ls_flags_ext.test(R2FLAGEXT_SSAO_HBAO) && (ps_r_ssao != 0);

// 	//	TODO: fix hbao shader to allow to perform per-subsample effect!
// 	o.hbao_vectorized = false;
// 	if (o.ssao_hbao)
// 	{
// 		if (HW.Caps.id_vendor == 0x1002)
// 			o.hbao_vectorized = true;
// 		o.ssao_opt_data = true;
// 	}

// 	if (o.ssao_hdao)
// 		o.ssao_opt_data = false;

// 	o.dx10_sm4_1 = ps_r2_ls_flags.test((u32)R3FLAG_USE_DX10_1);
// 	o.dx10_sm4_1 = o.dx10_sm4_1 && (HW.FeatureLevel >= D3D_FEATURE_LEVEL_10_1);

// 	// HDR10
// 	o.dx11_hdr10 = !!ps_r4_hdr10_on;

// 	//	MSAA option dependencies
// 	o.dx10_msaa = ps_r3_msaa && !o.dx11_hdr10;
// 	o.dx10_msaa_samples = o.dx11_hdr10 ? 1 : (1 << ps_r3_msaa);

// 	o.dx10_msaa_opt = ps_r2_ls_flags.test(R3FLAG_MSAA_OPT);
// 	o.dx10_msaa_opt = o.dx10_msaa_opt && o.dx10_msaa && (HW.FeatureLevel >= D3D_FEATURE_LEVEL_10_1)
// 		|| o.dx10_msaa && (HW.FeatureLevel >= D3D_FEATURE_LEVEL_11_0);

// 	//o.dx10_msaa_hybrid	= ps_r2_ls_flags.test(R3FLAG_MSAA_HYBRID);
// 	o.dx10_msaa_hybrid = ps_r2_ls_flags.test((u32)R3FLAG_USE_DX10_1);
// 	o.dx10_msaa_hybrid &= !o.dx10_msaa_opt && o.dx10_msaa && (HW.FeatureLevel >= D3D_FEATURE_LEVEL_10_1);

// 	//	Allow alpha test MSAA for DX10.0

// 	//o.dx10_msaa_alphatest= ps_r2_ls_flags.test((u32)R3FLAG_MSAA_ALPHATEST);
// 	//o.dx10_msaa_alphatest= o.dx10_msaa_alphatest && o.dx10_msaa;

// 	//o.dx10_msaa_alphatest_atoc= (o.dx10_msaa_alphatest && !o.dx10_msaa_opt && !o.dx10_msaa_hybrid);

// 	o.dx10_msaa_alphatest = 0;
// 	if (o.dx10_msaa)
// 	{
// 		if (o.dx10_msaa_opt || o.dx10_msaa_hybrid)
// 		{
// 			if (ps_r3_msaa_atest == 1)
// 				o.dx10_msaa_alphatest = MSAA_ATEST_DX10_1_ATOC;
// 			else if (ps_r3_msaa_atest == 2)
// 				o.dx10_msaa_alphatest = MSAA_ATEST_DX10_1_NATIVE;
// 		}
// 		else
// 		{
// 			if (ps_r3_msaa_atest)
// 				o.dx10_msaa_alphatest = MSAA_ATEST_DX10_0_ATOC;
// 		}
// 	}


// 	o.dx10_minmax_sm = ps_r3_minmax_sm;
// 	o.dx10_minmax_sm_screenarea_threshold = 1600 * 1200;

// 	o.dx11_enable_tessellation = HW.FeatureLevel >= D3D_FEATURE_LEVEL_11_0 && ps_r2_ls_flags_ext.test(
// 		R2FLAGEXT_ENABLE_TESSELLATION);

// 	if (o.dx10_minmax_sm == MMSM_AUTODETECT)
// 	{
// 		o.dx10_minmax_sm = MMSM_OFF;

// 		//	AMD device
// 		if (HW.Caps.id_vendor == 0x1002)
// 		{
// 			if (ps_r_sun_quality >= 3)
// 				o.dx10_minmax_sm = MMSM_AUTO;
// 			else if (ps_r_sun_shafts >= 2)
// 			{
// 				o.dx10_minmax_sm = MMSM_AUTODETECT;
// 				//	Check resolution in runtime in use_minmax_sm_this_frame
// 				o.dx10_minmax_sm_screenarea_threshold = 1600 * 1200;
// 			}
// 		}

// 		//	NVidia boards
// 		if (HW.Caps.id_vendor == 0x10DE)
// 		{
// 			if ((ps_r_sun_shafts >= 2))
// 			{
// 				o.dx10_minmax_sm = MMSM_AUTODETECT;
// 				//	Check resolution in runtime in use_minmax_sm_this_frame
// 				o.dx10_minmax_sm_screenarea_threshold = 1280 * 1024;
// 			}
// 		}
// 	}

// 	// Check if SSS shaders exist
// 	string_path fn;
// 	o.ssfx_core = FS.exist(fn, "$game_shaders$", "r3\\screenspace_common", ".h") ? 1 : 0;
// 	o.ssfx_rain = FS.exist(fn, "$game_shaders$", "r3\\effects_rain_splash", ".ps") ? 1 : 0;
// 	o.ssfx_blood = FS.exist(fn, "$game_shaders$", "r3\\effects_wallmark_blood", ".ps") ? 1 : 0;
// 	o.ssfx_branches = FS.exist(fn, "$game_shaders$", "r3\\deffer_tree_branch_aref_bump-hq", ".ps") ? 1 : 0;
// 	o.ssfx_hud_raindrops = FS.exist(fn, "$game_shaders$", "r3\\deffer_base_hud_bump", ".ps") ? 1 : 0;
// 	o.ssfx_ssr = FS.exist(fn, "$game_shaders$", "r3\\ssfx_ssr", ".ps") ? 1 : 0;
// 	o.ssfx_terrain = FS.exist(fn, "$game_shaders$", "r3\\deffer_terrain_high_flat_d", ".ps") ? 1 : 0;
// 	o.ssfx_volumetric = FS.exist(fn, "$game_shaders$", "r3\\ssfx_volumetric_blur", ".ps") ? 1 : 0;
// 	o.ssfx_water = FS.exist(fn, "$game_shaders$", "r3\\ssfx_water", ".ps") ? 1 : 0;
// 	o.ssfx_ao = FS.exist(fn, "$game_shaders$", "r3\\ssfx_ao", ".ps") ? 1 : 0;
// 	o.ssfx_il = FS.exist(fn, "$game_shaders$", "r3\\ssfx_il", ".ps") ? 1 : 0;
// 	o.ssfx_sss = FS.exist(fn, "$game_shaders$", "r3\\ssfx_sss", ".ps") ? 1 : 0;
// 	o.ssfx_bloom = FS.exist(fn, "$game_shaders$", "r3\\ssfx_bloom", ".ps") ? 1 : 0;
// 	o.ssfx_taa = FS.exist(fn, "$game_shaders$", "r3\\ssfx_taa", ".ps") ? 1 : 0;
// 	o.ssfx_fog = FS.exist(fn, "$game_shaders$", "r3\\ssfx_fog_scattering", ".ps") ? 1 : 0;
// 	o.ssfx_motionblur = FS.exist(fn, "$game_shaders$", "r3\\ssfx_motion_blur", ".ps") ? 1 : 0;
// 	o.ssfx_motionvectors = FS.exist(fn, "$game_shaders$", "r3\\screenspace_mvectors", ".h") ? 1 : 0;
// 	o.ssfx_glass = FS.exist(fn, "$game_shaders$", "r3\\ssfx_glass", ".ps") ? 1 : 0; 

// 	Msg("- Supports SSS UPDATE 23");
// 	Msg("- SSS CORE INSTALLED %i", o.ssfx_core);
// 	Msg("- SSS HUD SHADER INSTALLED %i", o.ssfx_hud_raindrops);
// 	Msg("- SSS MOTION VECTORS SHADER INSTALLED %i", o.ssfx_motionvectors);
// 	Msg("- SSS RAIN SHADER INSTALLED %i", o.ssfx_rain);
// 	Msg("- SSS BLOOD SHADER INSTALLED %i", o.ssfx_blood);
// 	Msg("- SSS BRANCHES SHADER INSTALLED %i", o.ssfx_branches);
// 	Msg("- SSS SSR SHADER INSTALLED %i", o.ssfx_ssr);
// 	Msg("- SSS TERRAIN SHADER INSTALLED %i", o.ssfx_terrain);
// 	Msg("- SSS VOLUMETRIC SHADER INSTALLED %i", o.ssfx_volumetric);
// 	Msg("- SSS WATER SHADER INSTALLED %i", o.ssfx_water);
// 	Msg("- SSS AO SHADER INSTALLED %i", o.ssfx_ao);
// 	Msg("- SSS IL SHADER INSTALLED %i", o.ssfx_il);
// 	Msg("- SSS SSS SHADER INSTALLED %i", o.ssfx_sss);
// 	Msg("- SSS BLOOM SHADER INSTALLED %i", o.ssfx_bloom);
// 	Msg("- SSS FOG SHADER INSTALLED %i", o.ssfx_fog);
// 	Msg("- SSS GLASS SHADER INSTALLED %i", o.ssfx_glass);
// 	Msg("- SSS MOTION BLUR SHADER INSTALLED %i", o.ssfx_motionblur);
// 	Msg("- SSS TAA SHADER INSTALLED %i", o.ssfx_taa);

// 	// constants
// 	CResourceManager* RM = dxRenderDeviceRender::Instance().Resources;
// 	RM->RegisterConstantSetup("parallax", &binder_parallax);
// 	RM->RegisterConstantSetup("water_intensity", &binder_water_intensity);
// 	RM->RegisterConstantSetup("sun_shafts_intensity", &binder_sun_shafts_intensity);
// 	RM->RegisterConstantSetup("m_AlphaRef", &binder_alpha_ref);
// 	RM->RegisterConstantSetup("pos_decompression_params", &binder_pos_decompress_params);
// 	RM->RegisterConstantSetup("pos_decompression_params2", &binder_pos_decompress_params2);
// 	RM->RegisterConstantSetup("triLOD", &binder_LOD);
// 	RM->RegisterConstantSetup("hmodel_stuff", &binder_meatchunks_stuff);

// 	c_lmaterial = "L_material";
// 	c_sbase = "s_base";

// 	m_bMakeAsyncSS = false;

// 	Target = xr_new<CRenderTarget>(); // Main target

// 	Models = xr_new<CModelPool>();
// 	PSLibrary.OnCreate();
// 	HWOCC.occq_create(occq_size);

// 	rmNormal();
// 	marker = 0;
// 	D3D_QUERY_DESC qdesc;
// 	qdesc.MiscFlags = 0;
// 	qdesc.Query = D3D_QUERY_EVENT;
// 	ZeroMemory(q_sync_point, sizeof(q_sync_point));
// 	//R_CHK						(HW.pDevice->CreateQuery(&qdesc,&q_sync_point[0]));
// 	//R_CHK						(HW.pDevice->CreateQuery(&qdesc,&q_sync_point[1]));
// 	//	Prevent error on first get data
// 	//q_sync_point[0]->End();
// 	//q_sync_point[1]->End();
// 	//R_CHK						(HW.pDevice->CreateQuery(D3DQUERYTYPE_EVENT,&q_sync_point[0]));
// 	//R_CHK						(HW.pDevice->CreateQuery(D3DQUERYTYPE_EVENT,&q_sync_point[1]));
// 	for (u32 i = 0; i < HW.Caps.iGPUNum; ++i)
// 		R_CHK(HW.pDevice->CreateQuery(&qdesc,&q_sync_point[i]));
// 	HW.pContext->End(q_sync_point[0]);

// 	::PortalTraverser.initialize();
// 	FluidManager.Initialize(70, 70, 70);
// 	//	FluidManager.Initialize( 100, 100, 100 );
// 	FluidManager.SetScreenSize(Device.dwWidth, Device.dwHeight);
// }