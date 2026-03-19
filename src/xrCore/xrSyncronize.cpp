#include "xrSyncronize.h"
#include "xrDebug.h"
#include "xrMemory.h"

xrCriticalSection::xrCriticalSection() {}

xrCriticalSection::~xrCriticalSection() {}

void xrCriticalSection::Enter()
{
	mutex.lock();
}

void xrCriticalSection::Leave()
{
	mutex.unlock();
}

BOOL xrCriticalSection::TryEnter()
{
	return mutex.try_lock();
}

xrCriticalSection::raii::raii(xrCriticalSection* critical_section)
	: critical_section(critical_section)
{
	VERIFY(critical_section);
	critical_section->Enter();
}

xrCriticalSection::raii::~raii()
{
	critical_section->Leave();
}
