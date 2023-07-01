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
        switch (RimsToCustomize)
        {
        case -1:
            CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, 67, (DWORD*)(SelectedPart[3])); // Rear
            break;
        case 0:
        default:
            CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, SelectedPart[4], (DWORD*)(SelectedPart[3])); // All
            CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, 67, (DWORD*)(SelectedPart[3]));
            break;
        case 1:
            CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, SelectedPart[4], (DWORD*)(SelectedPart[3])); // Front
            break;
        }
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

void __fastcall CustomizeRims_NotificationMessage(DWORD* _CustomizeRims, void* EDX_Unused, DWORD MessageHash, DWORD* FEObject, DWORD param1, DWORD param2)
{
    DWORD* ASelectablePart, * v7; // eax

    if (MessageHash != 0x91DFDF84) // Adds to cart, we will do it our way
        CustomizationScreen_NotificationMessage(_CustomizeRims, MessageHash, FEObject, param1, param2);

    switch (MessageHash)
    {
    case 0x5073EF13: // PAD_LTRIGGER
        CustomizeRims_ScrollRimSizes(_CustomizeRims, -1);
        break;

    case 0xD9FEEC59:  // PAD_RTRIGGER
        CustomizeRims_ScrollRimSizes(_CustomizeRims, 1);
        break;

    case 0xC519BFBF: // PAD_BUTTON0
        *(int*)_Showcase_FromFilter = _CustomizeRims[111];
        break;

    case 0x911AB364: // PAD_BACK
        cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizeSubTopPkg, _CustomizeRims[83] | (_CustomizeRims[82] << 16), 0, 0);
        break;

    case 0x5A928018: // Unk (Remove from cart??)
        ASelectablePart = (*(DWORD * (__thiscall**)(DWORD*))(*_CustomizeRims + 24))(_CustomizeRims); // CustomizationScreen::FindInCartPart
        if (ASelectablePart)
        {
            if (!CarCustomizeManager_IsPartInCart((DWORD*)_gCarCustomizeManager, ASelectablePart))
            {
                *((DWORD*)ASelectablePart + 8) &= 0xFu;
                (*(void(__thiscall**)(DWORD*))(*_CustomizeRims + 12))(_CustomizeRims); // RefreshHeader
            }
        }
        break;

    case 0x91DFDF84: // AddToCart thing, copied from CustomizationScreen_NotificationMessage
        v7 = (DWORD*)_CustomizeRims[84];
        if (v7)
        {
            *(DWORD*)((v7[19]) + 32) &= 0xFu;
            _CustomizeRims[84] = 0;
        }
        ASelectablePart = (*(DWORD * (__thiscall**)(DWORD*))(*_CustomizeRims + 20))(_CustomizeRims); // CustomizationScreen::GetSelectedPart

        switch (RimsToCustomize)
        {
        case -1: // Rear
            ASelectablePart[4] = 67;
            CarCustomizeManager_AddToCart((DWORD*)_gCarCustomizeManager, ASelectablePart);
            break;
        case 0: // All
        default:
            CarCustomizeManager_AddToCart((DWORD*)_gCarCustomizeManager, ASelectablePart);
            ASelectablePart[4] = 67;
            CarCustomizeManager_AddToCart((DWORD*)_gCarCustomizeManager, ASelectablePart);
            break;
        case 1: // Front
            CarCustomizeManager_AddToCart((DWORD*)_gCarCustomizeManager, ASelectablePart);
            break;
        }

        ASelectablePart = (*(DWORD * (__thiscall**)(DWORD*))(*_CustomizeRims + 20))(_CustomizeRims); // CustomizationScreen::GetSelectedPart
        ASelectablePart[8] = ASelectablePart[8] & 0xF | 0x20;
        (*(void(__thiscall**)(DWORD*))(*_CustomizeRims + 12))(_CustomizeRims); // RefreshHeader
        break;
    }
}