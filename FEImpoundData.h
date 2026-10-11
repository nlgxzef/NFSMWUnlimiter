#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

struct FEImpoundData
{
	BYTE MaxBusted;
	char TimesBusted;
	char ImpoundedState;
	BYTE DaysBeforeRelease;
	char EvadeCount;
	BYTE Pad1;
	WORD Pad2;
};
