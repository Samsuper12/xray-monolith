#ifndef _XRCORE_MATH_FUNCS_INLINE_
#define _XRCORE_MATH_FUNCS_INLINE_

// comparisions
inline BOOL fsimilar(float a, float b, float cmp = EPS) { return _abs(a - b) < cmp; }
inline BOOL dsimilar(double a, double b, double cmp = EPS) { return _abs(a - b) < cmp; }

inline BOOL fis_zero(float val, float cmp = EPS_S) { return _abs(val) < cmp; }
inline BOOL dis_zero(double val, double cmp = EPS_S) { return _abs(val) < cmp; }

// degree 2 radians and vice-versa
namespace implement
{
	template <class T>
	inline T deg2rad(T val) { return (val * T(M_PI) / T(180)); };

	template <class T>
	inline T rad2deg(T val) { return (val * T(180) / T(M_PI)); };
};

inline float deg2rad(float val) { return implement::deg2rad(val); }
inline double deg2rad(double val) { return implement::deg2rad(val); }
inline float rad2deg(float val) { return implement::rad2deg(val); }
inline double rad2deg(double val) { return implement::rad2deg(val); }

// clamping/snapping
template <class T>
inline void clamp(T& val, const T& _low, const T& _high)
{
	if (val < _low) val = _low;
	else if (val > _high) val = _high;
};

template <class T>
inline T clampr(const T& val, const T& _low, const T& _high)
{
	if (val < _low) return _low;
	else if (val > _high) return _high;
	else return val;
};

inline float snapto(float value, float snap)
{
	if (snap <= 0.f)
		return value;

	return float(static_cast<int>(std::floor((value + (snap * 0.5f)) / snap))) * snap;
}

#endif //_XRCORE_MATH_FUNCS_INLINE_