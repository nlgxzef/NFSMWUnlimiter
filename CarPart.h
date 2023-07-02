#pragma once

#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

unsigned int PreviousCarTypeNameHash;
bool Result;

float __fastcall CarPart_GetAppliedAttributeFParam(DWORD* _CarPart, void* EDX_Unused, DWORD namehash, float default_value)
{
    float* Attribute = (float*)CarPart_GetAttribute(_CarPart, namehash, 0);
    if (Attribute) return Attribute[1];
    return default_value;
}

bool GetForceLODA(unsigned int CarTypeNameHash)
{
    if (PreviousCarTypeNameHash == CarTypeNameHash) return Result; // If checked before for this car type, just return the result
    else PreviousCarTypeNameHash = CarTypeNameHash;

    DWORD* CarTypeInfo = GetCarTypeInfoFromHash(CarTypeNameHash);
    if (!CarTypeInfo)
    {
        Result = 0;
        return Result;
    }

    sprintf(CarININame, "UnlimiterData\\%s.ini", (char*)CarTypeInfo);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    Result = GetCarIntOption(CarINI, GeneralINI, "Main", "ForceLODA", 0) != 0;
    return Result;
}

int __fastcall CarPart_GetModelNameHash(DWORD* CarPart, int edx_unused, int a5, int LOD)
{
    short CarPartID; // ax
    DWORD* _CarPartModelTable; // esi
    char PartType; // al
    int MasterCarPartPack;
    int LevelOfDetail;
    int BrandName; // eax
    unsigned int CarTypeNameHash; // eax

    CarTypeNameHash = CarPart_GetCarTypeNameHash(CarPart);
    LevelOfDetail = GetForceLODA(CarTypeNameHash) ? 0 : LOD;
    MasterCarPartPack = *(int*)_MasterCarPartPack;

    CarPartID = *((WORD*)CarPart + 6);
    if (CarPartID == -1) return 0;

    _CarPartModelTable = (DWORD*)(*(DWORD*)(MasterCarPartPack + 44) + 24 * CarPartID);
    PartType = *((BYTE*)CarPart + 6);
    if (!PartType) return CarPartModelTable_GetModelNameHash(_CarPartModelTable, -1, a5, LevelOfDetail); // Global Parts??
    if (PartType == 1) return CarPartModelTable_GetModelNameHash(_CarPartModelTable, CarTypeNameHash, a5, LevelOfDetail); // Car-Specific Parts 
    
    BrandName = CarPart_GetBrandName(CarPart);
    return CarPartModelTable_GetModelNameHash(_CarPartModelTable, BrandName, a5, LevelOfDetail); // Branded parts
}