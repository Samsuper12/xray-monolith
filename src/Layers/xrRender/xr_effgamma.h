#ifndef __XR_GAMMA_H__
#define __XR_GAMMA_H__

//#include <d3d9types.h>

#include <_color.h>

//-----------------------------------------------------------------------------------------------------------
//Gamma control
//-----------------------------------------------------------------------------------------------------------
class CGammaControl
{
	float fGamma;
	float fBrightness;
	float fContrast;
	Fcolor cBalance;

public:
	CGammaControl() :
		fGamma(1.f)
	{
		Brightness(1.f);
		Contrast(1.f);
		Balance(1.f, 1.f, 1.f);
	};

	inline void Balance(float _r, float _g, float _b)
	{
		cBalance.set(_r, _g, _b, 1);
	}

	inline void Balance(Fcolor& C)
	{
		Balance(C.r, C.g, C.b);
	}

	inline void Gamma(float G) { fGamma = G; }
	inline void Brightness(float B) { fBrightness = B; }
	inline void Contrast(float C) { fContrast = C; }

	void GetIP(float& G, float& B, float& C, Fcolor& Balance)
	{
		G = fGamma;
		B = fBrightness;
		C = fContrast;
		Balance.set(cBalance);
	}

	void Update();

private:

#if defined(USE_DX10) || defined(USE_DX11)
	void GenLUT(const DXGI_GAMMA_CONTROL_CAPABILITIES& GC, DXGI_GAMMA_CONTROL& G);
#else	//	USE_DX10
	void GenLUT(D3DGAMMARAMP& G);
#endif	//	USE_DX10
};

#endif
