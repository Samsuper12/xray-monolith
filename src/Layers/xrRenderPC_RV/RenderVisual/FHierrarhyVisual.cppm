module;
// import vkRenderVisual;
export module FHierrarhyVisual;

class FHierrarhyVisual : public vkRender_Visual {
public:
  xr_vector<IRenderVisual *> children;
  xr_vector<IRenderVisual *> children_invisible;
  BOOL bDontDelete;

public:
  FHierrarhyVisual::FHierrarhyVisual() : vkRender_Visual() {}

  virtual ~FHierrarhyVisual() {
    if (!bDontDelete) {
      for (auto i = 0; i < children.size(); i++)
        ::Render->model_Delete((IRenderVisual *&)children[i]);
    }
    children.clear();
  }

  virtual void Load(const char *N, IReader *data, u32 dwFlags) {
    vkRender_Visual::Load(N, data, dwFlags);

    if (data->find_chunk(OGF_CHILDREN)) {
      // From stream
      IReader *OBJ = data->open_chunk(OGF_CHILDREN);
      if (OBJ) {
        IReader *O = OBJ->open_chunk(0);
        for (int count = 1; O; count++) {
          string_path name_load, short_name, num;
          xr_strcpy(short_name, N);
          if (strext(short_name))
            *strext(short_name) = 0;
          strconcat(sizeof(name_load), name_load, short_name, ":",
                    _itoa(count, num, 10));
          auto &c = dynamic_cast<vkRender_Visual &>(
              children.emplace_back(::Render->model_CreateChild(name_load, O)));
          c.setID(count);
          O->close();
          O = OBJ->open_chunk(count);
        }
        OBJ->close();
      }
      bDontDelete = FALSE;
    } else {
      FATAL("Invalid visual");
    }
  }

  virtual void Copy(dxRender_Visual *pSrc) {
    dxRender_Visual::Copy(pSrc);

    FHierrarhyVisual *pFrom = (FHierrarhyVisual *)pSrc;

    children.clear();
    children.reserve(pFrom->children.size());
    for (u32 i = 0; i < pFrom->children.size(); i++) {
      IRenderVisual *p = ::Render->model_Duplicate(pFrom->children[i]);
      children.push_back(p);
    }
    bDontDelete = FALSE;
  }
  virtual void Release() {
    if (!bDontDelete) {
      for (auto i = 0; i < children.size(); i++)
        ((vkRender_Visual *)children[i])->Release();
    }
  }
  //--DSR-- HeatVision_start
  virtual void MarkAsHot(bool is_hot);
  //--DSR-- HeatVision_end

  virtual xr_vector<IRenderVisual *> *get_children() { return &children; };
  virtual xr_vector<IRenderVisual *> *get_children_invisible() {
    return &children_invisible;
  };
};