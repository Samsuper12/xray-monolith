#pragma once

#include <xrAPI.h>
#include <xrDebug.h>

class CGameMtlLibrary;
inline CGameMtlLibrary& GMLibrary()
{
	VERIFY(PGMLib);
	return *PGMLib;
}
