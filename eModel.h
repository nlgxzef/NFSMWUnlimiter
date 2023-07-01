#include "stdio.h"
#include "InGameFunctions.h"

void __fastcall eModel_ReplaceLightMaterial(DWORD* eModel, void* EDX_Unused, int NameHash, int LightMaterial)
{
    DWORD* Solid; // ecx
    DWORD* LightMaterialTable; // eax
    int NumLightMaterials; // ecx

    if (eModel) // Check if there is actually a model to begin with (to work around crashes)
    {
        Solid = (DWORD*)eModel[3];                              // eSolid
        if (Solid)
        {
            if (LightMaterial)
            {
                LightMaterialTable = (DWORD*)Solid[15];// eLightMaterialEntry
                NumLightMaterials = *((char*)Solid + 26);
                if (NumLightMaterials > 0)
                {
                    do
                    {
                        if (*LightMaterialTable == NameHash)
                            LightMaterialTable[1] = LightMaterial;
                        LightMaterialTable += 2;
                        --NumLightMaterials;
                    } while (NumLightMaterials);
                }
            }
        }
    }
}