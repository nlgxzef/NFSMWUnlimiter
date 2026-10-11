#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

struct FEInfractionsData
{
	WORD Speeding;
	WORD Racing;
	WORD Reckless;
	WORD Assault;
	WORD HitAndRun;
	WORD Damage;
	WORD Resist;
	WORD OffRoad;

	int GetFineValue()
	{
		return FEInfractionsData_GetFineValue((DWORD*)this);
	}
};
