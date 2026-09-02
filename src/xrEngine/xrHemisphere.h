#ifndef xrHemisphereH
#define xrHemisphereH

typedef void __stdcall xrHemisphereIterator(float x, float y, float z, float energy, void* param);

void ECORE_API xrHemisphereBuild(int quality, float energy, xrHemisphereIterator* it, void* param);
int ECORE_API xrHemisphereVertices(int quality, const Fvector*& verts);
int ECORE_API xrHemisphereIndices(int quality, const u16*& indices);

#endif //xrHemisphereH
