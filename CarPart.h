#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

unsigned int PreviousCarTypeNameHash;
bool Result;

bool GetForceLODA(unsigned int CarTypeNameHash)
{
    if (PreviousCarTypeNameHash == CarTypeNameHash) return Result; // If checked before for this car type, just return the result
    else PreviousCarTypeNameHash = CarTypeNameHash;

    DWORD* CarTypeInfo = GetCarTypeInfoFromHash(CarTypeNameHash);
    sprintf(CarININame, "UnlimiterData\\%s.ini", (char*)CarTypeInfo);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    Result = (CarINI.ReadInteger("Main", "ForceLODA", GeneralINI.ReadInteger("Main", "ForceLODA", 0)) != 0);
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

    LevelOfDetail = LOD;
    MasterCarPartPack = *(int*)_MasterCarPartPack;

    CarPartID = *((WORD*)CarPart + 6);
    if (CarPartID == -1)
        return 0;
    _CarPartModelTable = (DWORD*)(*(DWORD*)(MasterCarPartPack + 44) + 24 * CarPartID);
    PartType = *((BYTE*)CarPart + 6);
    if (!PartType) return CarPartModelTable_GetModelNameHash(_CarPartModelTable, -1, a5, LevelOfDetail); // Global Parts??
    if (PartType == 1)  // Car-Specific Parts
    {
        CarTypeNameHash = CarPart_GetCarTypeNameHash(CarPart);
        if (GetForceLODA(CarTypeNameHash)) LevelOfDetail = 0;
        return CarPartModelTable_GetModelNameHash(_CarPartModelTable, CarTypeNameHash, a5, LevelOfDetail);
    }
    BrandName = CarPart_GetBrandName(CarPart);
    return CarPartModelTable_GetModelNameHash(_CarPartModelTable, BrandName, a5, LevelOfDetail); // Branded parts
}