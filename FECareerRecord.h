#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

#include "FEImpoundData.h"
#include "FEInfractionsData.h"

struct FECareerRecord // sizeof=0x38
{
    BYTE Handle;
    BYTE pad1;
    FEImpoundData TheImpoundData;
    BYTE pad2;
    BYTE pad3;
    float VehicleHeat;
    DWORD Bounty;
    WORD NumEvadedPursuits;
    WORD NumBustedPursuits;
    FEInfractionsData UnservedInfractions;
    FEInfractionsData ServedInfractions;

    float GetVehicleHeat()
    {
        return VehicleHeat;
    }
};