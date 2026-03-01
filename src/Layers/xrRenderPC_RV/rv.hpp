#pragma once 

#include <r__dsgraph_structure.h>
#include <r__occlusion.h>
//#include <R_Backend_Runtime.h>
#include <xrRender_console.h>

#include <PSLibrary.h>
#include <light_db.h>
#include <LightTrack.h>
#include <r_sun_cascades.h>
#include "IRenderDetailModel.h"
#include "stream_reader.h"
#include "SkeletonCustom.h"

inline void stub() {
	Msg("Stub");
	std::runtime_error("stub!");
}

class CRender : public R_dsgraph_structure
{
public:
	enum
	{
		PHASE_NORMAL = 0,
		// E[0]
		PHASE_SMAP = 1,
		// E[1]
	};

	enum
	{
		MSAA_ATEST_NONE = 0x0,
		//	Hi bit - DX10.1 mode
		MSAA_ATEST_DX10_0_ATOC = 0x1,
		//	Lo bit - ATOC mode
		MSAA_ATEST_DX10_1_NATIVE = 0x2,
		MSAA_ATEST_DX10_1_ATOC = 0x3,
	};

	enum
	{
		MMSM_OFF = 0,
		MMSM_ON,
		MMSM_AUTO,
		MMSM_AUTODETECT
	};

public:
	struct _options
	{
		u32 ssfx_branches : 1;
		u32 ssfx_blood : 1;
		u32 ssfx_rain : 1;
		u32 ssfx_hud_raindrops : 1;
		u32 ssfx_ssr : 1;
		u32 ssfx_terrain : 1;
		u32 ssfx_volumetric : 1;
		u32 ssfx_water : 1;
		u32 ssfx_ao : 1;
		u32 ssfx_il : 1;
		u32 ssfx_core : 1;
		u32 ssfx_bloom : 1;
		u32 ssfx_sss : 1;
		u32 ssfx_fog : 1;
		u32 ssfx_motionblur : 1;
		u32 ssfx_taa : 1;
		u32 ssfx_motionvectors : 1;
		u32 ssfx_glass : 1;

		u32 bug : 1;

		u32 ssao_blur_on : 1;
		u32 ssao_opt_data : 1;
		u32 ssao_half_data : 1;
		u32 ssao_hbao : 1;
		u32 ssao_hdao : 1;
		u32 ssao_ultra : 1;
		u32 hbao_vectorized : 1;

		u32 smapsize : 16;
		u32 depth16 : 1;
		u32 mrt : 1;
		u32 mrtmixdepth : 1;
		u32 fp16_filter : 1;
		u32 fp16_blend : 1;
		u32 albedo_wo : 1; // work-around albedo on less capable HW
		u32 HW_smap : 1;
		u32 HW_smap_PCF : 1;
		u32 HW_smap_FETCH4 : 1;

		u32 HW_smap_FORMAT : 32;

		u32 nvstencil : 1;
		u32 nvdbt : 1;

		u32 nullrt : 1;
		u32 no_ram_textures : 1; // don't keep textures in RAM

		u32 distortion : 1;
		u32 distortion_enabled : 1;

		u32 sunfilter : 1;
		u32 sunstatic : 1;
		u32 sjitter : 1;
		u32 noshadows : 1;
		u32 Tshadows : 1; // transluent shadows
		u32 disasm : 1;
		u32 advancedpp : 1; //	advanced post process (DOF, SSAO, volumetrics, etc.)
		u32 volumetricfog : 1;

		u32 dx10_msaa : 1; //	DX10.0 path
		u32 dx10_msaa_hybrid : 1; //	DX10.0 main path with DX10.1 A-test msaa allowed
		u32 dx10_msaa_opt : 1; //	DX10.1 path
		u32 dx10_sm4_1 : 1; //	DX10.1 path
		u32 dx10_msaa_alphatest : 2; //	A-test mode
		u32 dx10_msaa_samples : 4;

		u32 dx10_minmax_sm : 2;
		u32 dx10_minmax_sm_screenarea_threshold;

		u32 dx11_enable_tessellation : 1;

		u32 forcegloss : 1;
		u32 forceskinw : 1;
		
		// HDR10
		u32 dx11_hdr10 : 1;
		
		float forcegloss_v;
	} o;

	struct _stats
	{
		u32 l_total, l_visible;
		u32 l_shadowed, l_unshadowed;
		s32 s_used, s_merged, s_finalclip;
		u32 o_queries, o_culled;
		u32 ic_total, ic_culled;
	} stats;

public:
	bool is_sun();
	// Sector detection and visibility
	CSector* pLastSector;
	Fvector vLastCameraPos;
	u32 uLastLTRACK;
	xr_vector<IRender_Portal*> Portals;
	xr_vector<IRender_Sector*> Sectors;
	xrXRC Sectors_xrc;
	CDB::MODEL* rmPortals;
	//CHOM HOM;
	R_occlusion HWOCC;

	// Global vertex-buffer container
	//xr_vector<FSlideWindowItem> SWIs;
	xr_vector<ref_shader> Shaders;
	typedef svector<D3DVERTEXELEMENT9,MAXD3DDECLLENGTH + 1> VertexDeclarator;
	xr_vector<VertexDeclarator> nDC, xDC;
	xr_vector<ID3DVertexBuffer*> nVB, xVB;
	xr_vector<ID3DIndexBuffer*> nIB, xIB;
	xr_vector<dxRender_Visual*> Visuals;
	CPSLibrary PSLibrary;

	//CDetailManager* Details;
	//CModelPool* Models;
	//CWallmarksEngine* Wallmarks;

	//CRenderTarget* Target; // Render-target

	CLight_DB Lights;
	//CLight_Compute_XFORM_and_VIS LR;
	xr_vector<light*> Lights_LastFrame;
	//SMAP_Allocator LP_smap_pool;
	light_Package LP_normal;
	light_Package LP_pending;

	xr_vector<Fbox3,render_alloc<Fbox3>> main_coarse_structure;

	shared_str c_sbase;
	shared_str c_lmaterial;
	float o_hemi;
	float o_hemi_cube[CROS_impl::NUM_FACES];
	float o_sun;
	//ID3DQuery* q_sync_point[CHWCaps::MAX_GPUS];
	u32 q_sync_count;

	bool m_bMakeAsyncSS;
	bool m_bFirstFrameAfterReset; // Determines weather the frame is the first after resetting device.
	xr_vector<sun::cascade> m_sun_cascades;

private:
	// Loading / Unloading
	void LoadBuffers(CStreamReader* fs, BOOL _alternative) {stub();}
	void LoadVisuals(IReader* fs)  {stub();}
	void LoadLights(IReader* fs) {stub();}
	void LoadPortals(IReader* fs) {stub();}
	void LoadSectors(IReader* fs) {stub();}
	void LoadSWIs(CStreamReader* fs) {stub();}
	void Load3DFluid() {stub();}

	BOOL add_Dynamic(dxRender_Visual* pVisual, u32 planes) {stub();} // normal processing
	void add_Static(dxRender_Visual* pVisual, u32 planes) {stub();}
	void add_leafs_Dynamic(dxRender_Visual* pVisual) {stub();} // if detected node's full visibility
	void add_leafs_Static(dxRender_Visual* pVisual) {stub();} // if detected node's full visibility

public:
	IRender_Sector* rimp_detectSector(Fvector& P, Fvector& D)  {stub(); return nullptr;}
	void render_main(Fmatrix& mCombined, bool _fportals)  {stub();}
	void render_forward()  {stub();}
	void render_Reticle()  {stub();}
	void render_smap_direct(Fmatrix& mCombined)  {stub();}
	void render_indirect(light* L)  {stub();}
	void render_lights(light_Package& LP)  {stub();}
	void render_sun()  {stub();}
	void render_sun_near()  {stub();}
	void render_sun_filtered()  {stub();}
	void render_menu()  {stub();}
	void render_rain()  {stub();}

	void render_sun_cascade(u32 cascade_ind)  {stub();}
	void init_cacades()  {stub();}
	void render_sun_cascades()  {stub();}

public:
	ShaderElement* rimp_select_sh_static(dxRender_Visual* pVisual, float cdist_sq)  {stub();}
	ShaderElement* rimp_select_sh_dynamic(dxRender_Visual* pVisual, float cdist_sq)  {stub();}
	D3DVERTEXELEMENT9* getVB_Format(int id, BOOL _alt = FALSE)  {stub();}
	ID3DVertexBuffer* getVB(int id, BOOL _alt = FALSE)  {stub();}
	ID3DIndexBuffer* getIB(int id, BOOL _alt = FALSE)  {stub();}
	//FSlideWindowItem* getSWI(int id)  {stub();}
	IRender_Portal* getPortal(int id)  {stub();}
	IRender_Sector* getSectorActive()  {stub();}
	IRenderVisual* model_CreatePE(LPCSTR name)  {stub();}
	IRender_Sector* detectSector(const Fvector& P, Fvector& D)  {stub();}
	int translateSector(IRender_Sector* pSector)  {stub();}

	// HW-occlusion culling
	IC u32 occq_begin(u32& ID)  {stub();} //{ return HWOCC.occq_begin(ID); }
	IC void occq_end(u32& ID)  {stub();} //{ HWOCC.occq_end(ID); }
	IC R_occlusion::occq_result occq_get(u32& ID)  {stub();}//{ return HWOCC.occq_get(ID); }

	ICF void apply_object(IRenderable* O)
	{
		// if (0 == O) return;
		// if (0 == O->renderable_ROS()) return;
		// CROS_impl& LT = *((CROS_impl*)O->renderable_ROS());
		// LT.update_smooth(O);
		// o_hemi = 0.75f * LT.get_hemi();
		// //o_hemi						= 0.5f*LT.get_hemi			()	;
		// o_sun = 0.75f * LT.get_sun();
		// //--DSR-- HeatVision_start
		// RCache.hemi.set_hotness(O->GetHotness(), O->GetTransparency(), 0.f, 0.f);			//--DSR-- HeatVision
		// RCache.hemi.set_glowing(															//--DSR-- SilencerOverheat
		// 	sil_glow_color.x, 
		// 	sil_glow_color.y,
		// 	sil_glow_color.z, O->GetGlowing());
		// //--DSR-- HeatVision_end
		// CopyMemory(o_hemi_cube, LT.get_hemi_cube(), CROS_impl::NUM_FACES*sizeof(float));

		 {stub();}
	}
	
	IC void apply_lmaterial()
	{
// 		ref_constant C = RCache.get_c(c_sbase); // get sampler
// 		if (0 == C) return;
// 		VERIFY(RC_dest_sampler == C->destination);
// 		VERIFY(RC_dx10texture == C->type);
// 		CTexture* T = RCache.get_ActiveTexture(u32(C->samp.index));
// 		VERIFY(T);
// 		float mtl = T ? T->m_material : 0.f;
// #ifdef	DEBUG
//         if (ps_r2_ls_flags.test(R2FLAG_GLOBALMATERIAL))	mtl=ps_r2_gmaterial;
// #endif
// 		if (!(T && T->m_is_hot))										//--DSR-- HeatVision
// 			RCache.hemi.set_hotness(0.f, 0.f, 0.f, 0.f);
// 		if (!(T && T->m_is_glowing))									//--DSR-- SilencerOverheat
// 			RCache.hemi.set_glowing(0.f, 0.f, 0.f, 0.f);

// 		RCache.hemi.set_material(o_hemi, o_sun, 0, (mtl < 5 ? (mtl + .5f) / 4.f : mtl));
// 		RCache.hemi.set_pos_faces(o_hemi_cube[CROS_impl::CUBE_FACE_POS_X],
// 		                          o_hemi_cube[CROS_impl::CUBE_FACE_POS_Y],
// 		                          o_hemi_cube[CROS_impl::CUBE_FACE_POS_Z]);
// 		RCache.hemi.set_neg_faces(o_hemi_cube[CROS_impl::CUBE_FACE_NEG_X],
// 		                          o_hemi_cube[CROS_impl::CUBE_FACE_NEG_Y],
// 		                          o_hemi_cube[CROS_impl::CUBE_FACE_NEG_Z]);

 {stub();}
	}

public:
	// feature level
	virtual GenerationLevel get_generation() override   {stub();}//{ return IRender_interface::GENERATION_R2; }

	virtual bool is_sun_static() override  {stub();}//{ return o.sunstatic; }
	virtual DWORD get_dx_level() override  {stub();}//{ return HW.FeatureLevel >= D3D_FEATURE_LEVEL_10_1 ? 0x000A0001 : 0x000A0000; }

	// Loading / Unloading
	virtual void create() override  {stub();}
	virtual void destroy() override  {stub();}
	virtual void reset_begin() override  {stub();}
	virtual void reset_end() override  {stub();}

	virtual void level_Load(IReader*) override  {stub();}
	virtual void level_Unload() override  {stub();}

	ID3DBaseTexture* texture_load(LPCSTR fname, u32& msize, bool bStaging = false)  {stub();}
	virtual HRESULT shader_compile(
		LPCSTR name,
		DWORD const* pSrcData,
		UINT SrcDataLen,
		LPCSTR pFunctionName,
		LPCSTR pTarget,
		DWORD Flags,
		void*& result
	) override  {stub();}

	// Information
	virtual void Statistics(CGameFont* F) override  {stub();}
	virtual LPCSTR getShaderPath() override {stub();}// { return "r3\\"; }
	virtual ref_shader getShader(int id)  {stub();}
	virtual IRender_Sector* getSector(int id) override  {stub();}
	virtual IRenderVisual* getVisual(int id) override  {stub();}
	virtual IRender_Sector* detectSector(const Fvector& P) override  {stub();}
	virtual IRender_Target* getTarget() override  {stub();}

	// Main 
	virtual void flush() override  {stub();}
	virtual void set_Object(IRenderable* O) override {stub();} 
	virtual void add_Occluder(Fbox2& bb_screenspace) override {stub();} // mask screen region as oclluded
	virtual void add_Visual(IRenderVisual* V) override {stub();} // add visual leaf	(no culling performed at all)
	virtual void add_Geometry(IRenderVisual* V) override {stub();} // add visual(s)	(all culling performed)

	// wallmarks
	// demonized: add user defined rotation to wallmark
	virtual void add_StaticWallmark(ref_shader& S, const Fvector& P, float s, CDB::TRI* T, Fvector* V, float ttl = 0.f, bool ignore_opt = false, bool random_rotation = true) {stub();}
	virtual void add_StaticWallmark(ref_shader& S, const Fvector& P, float s, CDB::TRI* T, Fvector* V, float ttl, bool ignore_opt, float rotation) {stub();}
	virtual void add_StaticWallmark(IWallMarkArray* pArray, const Fvector& P, float s, CDB::TRI* T, Fvector* V, float ttl = 0.f, bool ignore_opt = false, bool random_rotation = true) override {stub();}
	virtual void add_StaticWallmark(IWallMarkArray* pArray, const Fvector& P, float s, CDB::TRI* T, Fvector* V, float ttl, bool ignore_opt, float rotation) override {stub();}

	virtual void add_StaticWallmark(const wm_shader& S, const Fvector& P, float s, CDB::TRI* T, Fvector* V) override {stub();}
	virtual void clear_static_wallmarks() override {stub();}
	virtual void add_SkeletonWallmark(intrusive_ptr<CSkeletonWallmark> wm) {stub();}
	virtual void add_SkeletonWallmark(const Fmatrix* xf, CKinematics* obj, ref_shader& sh, const Fvector& start,
	                                  const Fvector& dir, float size, float ttl = 0.f, bool ignore_opt = false);
	virtual void add_SkeletonWallmark(const Fmatrix* xf, IKinematics* obj, IWallMarkArray* pArray, const Fvector& start,
	                                  const Fvector& dir, float size, float ttl = 0.f, bool ignore_opt = false) override {stub();}

	//
	virtual IBlender* blender_create(CLASS_ID cls) {stub();}
	virtual void blender_destroy(IBlender* &) {stub();}

	//
	virtual IRender_ObjectSpecific* ros_create(IRenderable* parent) override {stub();}
	virtual void ros_destroy(IRender_ObjectSpecific* &) override {stub();}

	// Lighting
	virtual IRender_Light* light_create() override {stub();}
	virtual IRender_Glow* glow_create() override {stub();}

	// Models
	virtual IRenderVisual* model_CreateParticles(LPCSTR name) override {stub();}
	virtual IRender_DetailModel* model_CreateDM(IReader* F) {stub();}
	virtual IRenderVisual* model_Create(LPCSTR name, IReader* data = 0) override {stub();}
	virtual IRenderVisual* model_CreateChild(LPCSTR name, IReader* data) override {stub();}
	virtual IRenderVisual* model_Duplicate(IRenderVisual* V) override {stub();}
	virtual void model_Delete(IRenderVisual* & V, BOOL bDiscard) override {stub();}
	virtual void model_Delete(IRender_DetailModel* & F) {stub();}
	virtual void model_Logging(BOOL bEnable) override {stub();}// { Models->Logging(bEnable); }
	virtual void models_Prefetch() override{stub();}
	virtual void models_PrefetchOne(LPCSTR name, bool assert = true) override {stub();}
	virtual void models_Clear(BOOL b_complete) override {stub();}
	virtual bool models_Exists(LPCSTR name) override {stub();}
	
	// anglobes: Sun Values
	virtual Fvector GetSunPosition() override
	{
		// static Fvector default_pos = { 0, 0, 0 };
		// light* sun = (light*)Lights.sun_adapted._get();
		// if (!sun)
		// 	return default_pos;
		// return sun->position;

		{stub();}
	};
	virtual Fcolor GetSunColor() override
	{
		// static Fcolor default_color = { 0.0f, 0.0f, 0.0f, 0.0f };
		// light* sun = (light*)Lights.sun_adapted._get();
		// if (!sun)
		// 	return default_color;
		// return sun->color;

		{stub();}
	};
	virtual float GetSunIntensity() override
	{
		// static float default_intensity = 0.0f;
		// light* sun = (light*)Lights.sun_adapted._get();
		// if (!sun)
		// 	return default_intensity;
		// return sun->color.intensity();
		{stub();}
	};
	virtual bool IsSun() override
	{
		{stub();}//return is_sun();
	};

	// Occlusion culling
	virtual BOOL occ_visible(vis_data& V) override {stub();}
	virtual BOOL occ_visible(Fbox& B) override {stub();}
	virtual BOOL occ_visible(sPoly& P) override {stub();}

	// Main
	virtual void Calculate() override {stub();}
	virtual void Render() override {stub();}
	virtual void Screenshot(ScreenshotMode mode = SM_NORMAL, LPCSTR name = 0) override {stub();}
	virtual void Screenshot(ScreenshotMode mode, CMemoryWriter& memory_writer) override {stub();}
	virtual void ScreenshotAsyncBegin() override {stub();}
	virtual void ScreenshotAsyncEnd(CMemoryWriter& memory_writer) override {stub();}
	virtual void OnFrame() override {stub();}

	// Particles
	virtual void ExportParticles() override {stub();}
	virtual void ImportParticles() override {stub();}

	// Render mode
	virtual void rmNear() override {stub();}
	virtual void rmFar() override {stub();}
	virtual void rmNormal() override {stub();}
	virtual u32 active_phase() override {stub();}// { return phase; }; //Swartz: actor shadow
	void RenderToTarget(RRT target) override{stub();}
	// Constructor/destructor/loader
	CRender() {stub();}
	virtual ~CRender() {stub();}

	void addShaderOption(const char* name, const char* value) {stub();}
	void clearAllShaderOptions() {stub();}// { m_ShaderOptions.clear(); }

private:
	xr_vector<D3D_SHADER_MACRO> m_ShaderOptions;

protected:
	virtual void ScreenshotImpl(ScreenshotMode mode, LPCSTR name, CMemoryWriter* memory_writer) override {stub();}

private:
	//FS_FileSet m_file_set;
};

extern CRender RImplementation;
