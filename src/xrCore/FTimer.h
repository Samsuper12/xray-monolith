#ifndef FTimerH
#define FTimerH
#pragma once

#include <log.h>
#include <chrono>


class CTimer_paused;

class XRCORE_API pauseMngr
{
	xr_vector<CTimer_paused*> m_timers;
	bool m_paused;
public:
	pauseMngr();
	bool Paused() { return m_paused; };
	void Pause(bool b);
	void Register(CTimer_paused& t);
	void UnRegister(CTimer_paused& t);
};

extern XRCORE_API pauseMngr& g_pauseMngr();

class XRCORE_API CTimerBase
{
public:
	using duration_t = std::chrono::high_resolution_clock::duration;
	using time_point_t = std::chrono::high_resolution_clock::time_point;
	using clock = std::chrono::high_resolution_clock;

protected:
	time_point_t qwStartTime;
	duration_t qwPausedTime;
	duration_t qwPauseAccum;
	bool bPause;
public:

	CTimerBase() : qwStartTime{}, qwPausedTime{}, qwPauseAccum{}, bPause(false)
	{
	}

	inline void Start()
	{
		if (bPause) return;
		qwStartTime = (clock::now() - qwPauseAccum);
	}

	inline duration_t GetElapsed_ticks() const
	{
		if (bPause) return qwPausedTime;
		else return ((clock::now() - qwStartTime) - qwPauseAccum);
	}

	inline long long GetElapsed_ms() const { 
		return std::chrono::duration_cast<std::chrono::milliseconds>(GetElapsed_ticks()).count();
	}
	inline float GetElapsed_sec() const
	{
		std::chrono::duration<float> t = std::chrono::duration_cast<std::chrono::seconds>(GetElapsed_ticks());
		return t.count();
	}

	inline void Dump() const
	{
		Msg("* Elapsed time (sec): %f", GetElapsed_sec());
	}
};

class CTimer : public CTimerBase
{
private:
	using inherited = CTimerBase;

protected:
	float m_time_factor;
	duration_t m_real_ticks;
	duration_t m_ticks;

private:
	inline duration_t modif_ticks(duration_t current) const
	{
		auto delta = current - m_real_ticks;
		auto time_factor_d = time_factor();
		auto time = delta * time_factor_d + std::chrono::nanoseconds{5};
		return m_ticks + std::chrono::duration_cast<duration_t>(time);
	}

public:
	inline CTimer() : m_time_factor(1.f), m_real_ticks(0), m_ticks(0)
	{
	}

	inline void Start()
	{
		if (bPause)
			return;

		inherited::Start();

		m_real_ticks = {};
		m_ticks = {};
	}

	inline const float& time_factor() const
	{
		return (m_time_factor);
	}

	inline void time_factor(const float& time_factor)
	{
		auto current = inherited::GetElapsed_ticks();
		m_ticks = modif_ticks(current);
		m_real_ticks = current;
		m_time_factor = time_factor;
	}

	inline duration_t GetElapsed_ticks() const
	{
		return modif_ticks(inherited::GetElapsed_ticks());
	}

	inline long long GetElapsed_ms() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(GetElapsed_ticks()).count();
	}

	inline float GetElapsed_sec() const
	{
		std::chrono::duration<float> t = std::chrono::duration_cast<std::chrono::seconds>(GetElapsed_ticks());
		return t.count();
	}

	inline void Dump() const
	{
		Msg("* Elapsed time (sec): %f", GetElapsed_sec());
	}
};

class XRCORE_API CTimer_paused_ex : public CTimer
{
	time_point_t save_clock;
public:
	CTimer_paused_ex()
	{
	}

	virtual ~CTimer_paused_ex()
	{
	}

	inline bool Paused() const { return bPause; }
	inline void Pause(const bool b)
	{
		if (bPause == b) return;

		auto _current = clock::now();
		if (b)
		{
			save_clock = _current;
			qwPausedTime = CTimerBase::GetElapsed_ticks();
		}
		else
		{
			qwPauseAccum += _current - save_clock;
			m_real_ticks = CTimer::GetElapsed_ticks(); 
		}
		bPause = b;
	}
};

class XRCORE_API CTimer_paused : public CTimer_paused_ex
{
public:
	CTimer_paused() { g_pauseMngr().Register(*this); }
	virtual ~CTimer_paused() { g_pauseMngr().UnRegister(*this); }
};

extern XRCORE_API BOOL g_bEnableStatGather;

class XRCORE_API CStatTimer
{
	using duration_t = std::chrono::high_resolution_clock::duration;
	using time_point_t = std::chrono::high_resolution_clock::time_point;
	using clock = std::chrono::high_resolution_clock;

public:
	CTimer T;
	duration_t accum;
	float result;
	u32 count;
public:
	CStatTimer();
	void FrameStart();
	void FrameEnd();

	inline void Begin()
	{
		if (!g_bEnableStatGather) return;
		count++;
		T.Start();
	}

	inline void End()
	{
		if (!g_bEnableStatGather) return;
		accum += T.GetElapsed_ticks();
	}

	inline duration_t GetElapsed_ticks() const { return accum; }

	inline long long GetElapsed_ms() const { return std::chrono::duration_cast<std::chrono::milliseconds>(GetElapsed_ticks()).count(); }
	inline float GetElapsed_sec() const
	{
		std::chrono::duration<float> _result = std::chrono::duration_cast<std::chrono::seconds>(GetElapsed_ticks());
		return _result.count();
	}
};

#endif // FTimerH
