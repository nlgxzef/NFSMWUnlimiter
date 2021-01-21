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

bool IsNoRimSize(int BrandID)
{
    sprintf(RimBrandID, "Brand%d", (BrandID - 0x702));
    CIniReader RimBrandsINI("UnlimiterData\\_RimBrands.ini");
    return RimBrandsINI.ReadInteger(RimBrandID, "NoRimSize", 0) != 0;
}

// 0x7B7E90
void __declspec(naked) NoRimSizeCodeCave()
{
    _asm
    {
        push edx
        mov eax, [edi + 0x148] // brand id
        push eax
        call IsNoRimSize
        add esp,4
        test al, al
        pop edx
        jnz loc_7B7E98

        cmp edx, [edi + 0x1BC]
        jnz loc_7B7EFD

        loc_7B7E98:
            push 0x7B7E98
            retn

        loc_7B7EFD:
            push 0x7B7EFD
            retn
    }
    
}

void __fastcall CustomizeRims_RefreshHeader(DWORD* CustomizeRims, void* EDX_Unused)
{
    char RimNameBuffer[64]; // [esp+4h] [ebp-40h] BYREF

    CustomizationScreen_RefreshHeader(CustomizeRims);
    if (bList_TraversebList(CustomizeRims + 12, 0) == CustomizeRims[59]) // No rims in brand??
    {
        DWORD* SomeObj1 = FEngFindObject((char const*)CustomizeRims[4], 0x8D1559A4);
        FEngSetInvisible(SomeObj1);
        DWORD* RimNameObj = FEngFindObject((char const*)CustomizeRims[4], 0x5E7B09C9);
        FEngSetInvisible(RimNameObj);
        DWORD* SomeObj2 = FEngFindObject((char const*)CustomizeRims[4], 0xF2492598);
        FEngSetInvisible(SomeObj2);
    }
    else
    {
        DWORD* SelectedPart = (*(DWORD * (__thiscall**)(DWORD*))(*CustomizeRims + 0x14))(CustomizeRims); // CustomizationScreen::GetSelectedPart
        CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, SelectedPart[4], (DWORD*)(SelectedPart[3]));
        FEPrintf((char const*)CustomizeRims[4], 0xE6782841, "%$d\"", CustomizeRims[111]); // inch
        
        DWORD LanguageHash = CarPart_GetAppliedAttributeUParam((DWORD*)(SelectedPart[3]), bStringHash("LANGUAGEHASH"), 0);
        if (LanguageHash)
        {
            FEngSetLanguageHash((char const*)CustomizeRims[4], 0x5E7B09C9, LanguageHash);
        }
        else
        {
            bSNPrintf(RimNameBuffer, 64, "%s", CarPart_GetName((DWORD*)(SelectedPart[3]))); // Get part debug name
            if ((strlen(RimNameBuffer) > 6) && !IsNoRimSize(CustomizeRims[82])) RimNameBuffer[strlen(RimNameBuffer) - 6] = '\0'; // Trim last 6 characters if the rim has size
            FEPrintf((char const*)CustomizeRims[4], 0x5E7B09C9, "%s", RimNameBuffer);
        }
    }

    if (IsNoRimSize(CustomizeRims[82]))
    {
        DWORD* Inch = FEngFindObject((char const*)CustomizeRims[4], 0x4BF687BF); // Customize Rims
        if (!Inch) Inch = FEngFindObject((char const*)CustomizeRims[4], 0x4BF5F2DC); // Backroom
        FEngSetInvisible(Inch);
    }
}