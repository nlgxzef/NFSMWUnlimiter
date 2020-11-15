#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

unsigned int __fastcall CustomizeRims_GetCategoryBrandHash(DWORD* CustomizeRims, int EDX_Unused)
{
    CIniReader RimBrandsINI("UnlimiterData\\_RimBrands.ini");

    int RimBrandsCount = RimBrandsINI.ReadInteger("RimBrands", "NumberOfRimBrands", -1);
    if (RimBrandsCount == -1) return 0;
    
    sprintf(RimBrandID, "Brand%d", (CustomizeRims[82] - 0x702));
    return bStringHash(RimBrandsINI.ReadString(RimBrandID, "BrandName", ""));
}