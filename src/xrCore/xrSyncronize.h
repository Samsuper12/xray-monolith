#pragma once

#include <mutex>
#include <shared_mutex>
#include "_noncopyable.h"

// Desc: Simple wrapper for critical section
class XRCORE_API xrCriticalSection : xray::noncopyable
{
public:
	class XRCORE_API raii
	{
	public:
		raii(xrCriticalSection*);
		~raii();

	private:
		xrCriticalSection* critical_section;
	};

private:
	std::recursive_mutex mutex;
public:
	xrCriticalSection();
	~xrCriticalSection();

	void Enter();
	void Leave();
	BOOL TryEnter();

	bool IsValid() { return true; }
};

class xrCriticalSectionGuard : xray::noncopyable
{
private:
	xrCriticalSection* critical_section;

public:
	void Enter()
	{
		critical_section->Enter();
	}
	void Leave()
	{
		critical_section->Leave();
	}
	xrCriticalSectionGuard(xrCriticalSection* cs) : critical_section(cs) { Enter(); }
	xrCriticalSectionGuard(xrCriticalSection& cs) : critical_section(&cs) { Enter(); }

	~xrCriticalSectionGuard() { Leave(); }
};


