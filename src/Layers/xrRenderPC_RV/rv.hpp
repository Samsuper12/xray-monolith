#pragma once 
#include <device.h>
#include <Render.h>
#include <IGame_Persistent.h>
#include <IRenderDetailModel.h>
#include <Kinematics.h>
#include "render_stub.hpp"


class CRender : public IRender_interface, public pureFrame
{

public:
	bool is_sun();

public:
	virtual void OnFrame();

	IRender_Sector* rimp_detectSector(Fvector& P, Fvector& D)  {render_stub(); return nullptr;}
	void render_main(Fmatrix& mCombined, bool _fportals)  {render_stub();}
	void render_forward()  {render_stub();}
	void render_Reticle()  {render_stub();}
	void render_smap_direct(Fmatrix& mCombined)  {render_stub();}
	void render_indirect(light* L)  {render_stub();}
	//void render_lights(light_Package& LP)  {render_stub();}
	void render_sun()  {render_stub();}
	void render_sun_near()  {render_stub();}
	void render_sun_filtered()  {render_stub();}
	void render_menu();
	void render_rain()  {render_stub();}

	void render_sun_cascade(u32 cascade_ind)  {render_stub();}
	void init_cacades()  {render_stub();}
	void render_sun_cascades()  {render_stub();}

	IRender_Portal* getPortal(int id)  {render_stub();}
	IRender_Sector* getSectorActive()  {render_stub();}
	IRenderVisual* model_CreatePE(LPCSTR name)  {render_stub();}
	IRender_Sector* detectSector(const Fvector& P, Fvector& D)  {render_stub();}
	int translateSector(IRender_Sector* pSector)  {render_stub();}

	// HW-occlusion culling
	IC u32 occq_begin(u32& ID)  {render_stub();} 
	IC void occq_end(u32& ID)  {render_stub();} 


	ICF void apply_object(IRenderable* O) { {render_stub();}}
	
	IC void apply_lmaterial() {{render_stub();}}

	// feature level
	virtual GenerationLevel get_generation() override   {render_stub();}

	virtual bool is_sun_static() override  {render_stub();}
	virtual DWORD get_dx_level() override  {render_stub();}

	// Loading / Unloading
	virtual void create();
	virtual void destroy();
	virtual void reset_begin() override  {render_stub();}
	virtual void reset_end() override  {render_stub();}

	virtual void level_Load(IReader*) override  {render_stub();}
	virtual void level_Unload() override  {render_stub();}


	// Information
	virtual void Statistics(CGameFont* F) override  {render_stub();}
	virtual LPCSTR getShaderPath() override {render_stub();}// { return "r3\\"; }
	// virtual ref_shader getShader(int id)  {render_stub();}
	virtual IRender_Sector* getSector(int id) override  {render_stub();}
	virtual IRenderVisual* getVisual(int id) override  {render_stub();}
	virtual IRender_Sector* detectSector(const Fvector& P) override  {render_stub();}
	virtual IRender_Target* getTarget() override  {render_stub();}
	virtual u32 memory_usage() {render_stub();}


	// Main 
	virtual void flush() override  {render_stub();}
	virtual void set_Object(IRenderable* O) override {render_stub();} 
	virtual void add_Occluder(Fbox2& bb_screenspace) override {render_stub();} // mask screen region as oclluded
	virtual void add_Visual(IRenderVisual* V) override {render_stub();} // add visual leaf	(no culling performed at all)
	virtual void add_Geometry(IRenderVisual* V) override {render_stub();} // add visual(s)	(all culling performed)

	virtual void add_StaticWallmark(IWallMarkArray* pArray, const Fvector& P, float s, CDB::TRI* T, Fvector* V, float ttl, bool ignore_opt, float rotation) override {render_stub();}

	virtual void add_StaticWallmark(const wm_shader& S, const Fvector& P, float s, CDB::TRI* T, Fvector* V) override {render_stub();}
	virtual void clear_static_wallmarks() override {render_stub();}

	virtual void add_SkeletonWallmark(const Fmatrix* xf, IKinematics* obj, IWallMarkArray* pArray, const Fvector& start,
	                                  const Fvector& dir, float size, float ttl = 0.f, bool ignore_opt = false) override {render_stub();}
	
		virtual void add_StaticWallmark(IWallMarkArray* pArray, const Fvector& P, float s, CDB::TRI* T, Fvector* V, float ttl = 0.f, bool ignore_opt = false, bool random_rotation = true) {render_stub();}


			virtual void set_Transform(Fmatrix* M)  {render_stub();}

		virtual void set_HUD(BOOL V) {render_stub();}
	virtual BOOL get_HUD() {render_stub();}
	virtual void set_CamAttached(BOOL V) {render_stub();}
	virtual BOOL get_CamAttached() {render_stub();}
	virtual void set_Invisible(BOOL V) {render_stub();}

	virtual bool shader_compile(
		LPCSTR name,
		DWORD const* pSrcData,
		UINT SrcDataLen,
		LPCSTR pFunctionName,
		LPCSTR pTarget,
		DWORD Flags,
		void*& result
	) {render_stub();}

	//
	virtual IRender_ObjectSpecific* ros_create(IRenderable* parent) override {render_stub();}
	virtual void ros_destroy(IRender_ObjectSpecific* &) override {render_stub();}

	// Lighting
	virtual IRender_Light* light_create() override {render_stub();}
	virtual IRender_Glow* glow_create() override {render_stub();}

	// Models
	virtual IRenderVisual* model_CreateParticles(LPCSTR name) override {render_stub();}
	virtual IRender_DetailModel* model_CreateDM(IReader* F) {render_stub();}
	virtual IRenderVisual* model_Create(LPCSTR name, IReader* data = 0) override {render_stub();}
	virtual IRenderVisual* model_CreateChild(LPCSTR name, IReader* data) override {render_stub();}
	virtual IRenderVisual* model_Duplicate(IRenderVisual* V) override {render_stub();}
	virtual void model_Delete(IRenderVisual* & V, BOOL bDiscard) override {render_stub();}
	virtual void model_Delete(IRender_DetailModel* & F) {render_stub();}
	virtual void model_Logging(BOOL bEnable) override {render_stub();}// { Models->Logging(bEnable); }
	virtual void models_Prefetch() override{render_stub();}
	virtual void models_PrefetchOne(LPCSTR name, bool assert = true) override {render_stub();}
	virtual void models_Clear(BOOL b_complete) override {render_stub();}
	virtual bool models_Exists(LPCSTR name) override {render_stub();}
	
	// anglobes: Sun Values
	virtual Fvector GetSunPosition() override{{render_stub();}};
	virtual Fcolor GetSunColor() override{{render_stub();}};
	virtual float GetSunIntensity() override {{render_stub();}};
	virtual bool IsSun() override{render_stub();}

	// Occlusion culling
	virtual BOOL occ_visible(vis_data& V) override {render_stub();}
	virtual BOOL occ_visible(Fbox& B) override {render_stub();}
	virtual BOOL occ_visible(sPoly& P) override {render_stub();}

	// Main
	virtual void Calculate() override {render_stub();}
	virtual void Render();
	virtual void Screenshot(ScreenshotMode mode = SM_NORMAL, LPCSTR name = 0) override {render_stub();}
	virtual void Screenshot(ScreenshotMode mode, CMemoryWriter& memory_writer) override {render_stub();}
	virtual void ScreenshotAsyncBegin() override {render_stub();}
	virtual void ScreenshotAsyncEnd(CMemoryWriter& memory_writer) override {render_stub();}

	// Particles
	virtual void ExportParticles() override {render_stub();}
	virtual void ImportParticles() override {render_stub();}

	// Render mode
	virtual void rmNear() override {render_stub();}
	virtual void rmFar() override {render_stub();}
	virtual void rmNormal() override {render_stub();}
	virtual u32 active_phase() override {render_stub();}// { return phase; }; //Swartz: actor shadow
	void RenderToTarget(RRT target) override{render_stub();}
	// Constructor/destructor/loader
	CRender() {render_stub();}
	virtual ~CRender() {render_stub();}

	void addShaderOption(const char* name, const char* value) {render_stub();}
	void clearAllShaderOptions() {render_stub();}// { m_ShaderOptions.clear(); }

protected:
	virtual void ScreenshotImpl(ScreenshotMode mode, LPCSTR name, CMemoryWriter* memory_writer) override {render_stub();}

};

extern CRender RImplementation;
