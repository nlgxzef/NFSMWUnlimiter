#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

unsigned int __fastcall CustomizeRims_GetCategoryBrandHash(DWORD* CustomizeRims, int EDX_Unused)
{
    CIniReader RimBrandsINI("UnlimiterData\\_RimBrands.ini");

    int CurrCategoryID = (CustomizeRims[82] - 0x702);

    int RimBrandsCount = RimBrandsINI.ReadInteger("RimBrands", "NumberOfRimBrands", DefaultRimBrandCount);
    if (RimBrandsCount < CurrCategoryID) return 0;
    
    sprintf(RimBrandID, "Brand%d", CurrCategoryID);
    return bStringHash(RimBrandsINI.ReadString(RimBrandID, "BrandName", GetDefaultRimBrandName(CurrCategoryID)));
}

bool IsNoRimSize(int BrandID)
{
    CIniReader RimBrandsINI("UnlimiterData\\_RimBrands.ini");
    
    int CurrCategoryID = (BrandID - 0x702);

    int RimBrandsCount = RimBrandsINI.ReadInteger("RimBrands", "NumberOfRimBrands", DefaultRimBrandCount);
    if (RimBrandsCount < CurrCategoryID) return 0;

    sprintf(RimBrandID, "Brand%d", CurrCategoryID);
    
    return RimBrandsINI.ReadInteger(RimBrandID, "NoRimSize", CurrCategoryID ? 0 : 1) != 0;
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

        // Fix cost and trade in display
        if (CarCustomizeManager_IsCareerMode())
        {
            if (!CustomizeIsInBackRoom())
            {
                // Recalculate cost and trade in values
                DWORD* InstalledFrontRim = CarCustomizeManager_GetInstalledCarPart((DWORD*)_gCarCustomizeManager, 66);
                DWORD* InstalledRearRim = CarCustomizeManager_GetInstalledCarPart((DWORD*)_gCarCustomizeManager, 67);
                int UnlockFilter = CarCustomizeManager_GetUnlockFilter();
                int TradeIn = 0;
                //int CartTotal = CarCustomizeManager_GetCartTotal((DWORD*)_gCarCustomizeManager, 2);
                int Cost = UnlockSystem_GetCarPartCost(UnlockFilter, 66, (DWORD*)(SelectedPart[3]), 0);

                if (InstalledFrontRim && RimsToCustomize != -1)
                {
                    TradeIn += UnlockSystem_GetCarPartCost(UnlockFilter, 66, InstalledFrontRim, 0);
                }

                if (InstalledRearRim && RimsToCustomize != 1)
                {
                    TradeIn += UnlockSystem_GetCarPartCost(UnlockFilter, 67, InstalledRearRim, 0);
                }

                if (RimsToCustomize == 0) Cost *= 2;

                TradeIn = TradeIn * *(float*)_gTradeInFactor;

                FEPrintf((char const*)CustomizeRims[4], 0xDBB80EDD, "%$d", Cost); // Total cost amount
                FEPrintf((char const*)CustomizeRims[4], 0xA91EDA8A, "%$d", TradeIn); // Trade in amount
                //FEPrintf((char const*)CustomizeRims[4], 0x7A6D2F71, "%$d", CartTotal); // Total
            }
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
        if (!IsNoRimSize(_CustomizeRims[82])) CustomizeRims_ScrollRimSizes(_CustomizeRims, -1);
        break;

    case 0xD9FEEC59:  // PAD_RTRIGGER
        if (!IsNoRimSize(_CustomizeRims[82])) CustomizeRims_ScrollRimSizes(_CustomizeRims, 1);
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

void __fastcall CustomizeRims_BuildRimsList(DWORD* _CustomizeRims, void* EDX_Unused, int Index)
{
    DWORD* TheIconScroller; // ebx MAPDST
    DWORD* v4; // eax
    int v6; // ecx
    DWORD* v7; // esi
    DWORD* v8; // eax
    int v9; // eax
    DWORD* TheSelectablePart; // esi
    DWORD* TheCarPart; // ebx
    DWORD PartIcon; // ebp
    char PartName; // bl
    bool IsLocked; // al
    DWORD CategoryBrandHash; // edx
    DWORD InitialOption; // eax MAPDST
    DWORD i; // [esp+Ch] [ebp-20h]
    unsigned int UnlockHash; // [esp+14h] [ebp-18h]
    DWORD PartList[2]; // [esp+18h] [ebp-14h] BYREF
    int v20; // [esp+28h] [ebp-4h]

    TheIconScroller = _CustomizeRims + 11;
    (*(void(__thiscall**)(DWORD*))(_CustomizeRims[11] + 12))(_CustomizeRims + 11);
    (*(void(__thiscall**)(DWORD*))(*TheIconScroller + 60))(TheIconScroller);
    PartList[0] = (DWORD)PartList;
    PartList[1] = (DWORD)PartList;
    v20 = 0;
    CategoryBrandHash = CustomizeRims_GetCategoryBrandHash(_CustomizeRims, (int)EDX_Unused);
    CarCustomizeManager_GetCarPartList((DWORD*)_gCarCustomizeManager, 66, PartList, CategoryBrandHash); // 67 doesn't filter by brand
    int IndexActive = 0;
    DWORD* TheActivePart = 0;
    v4 = (DWORD*)PartList[0];
    if (Index == -1) TheActivePart = (DWORD*)CarCustomizeManager_GetActivePartFromSlot((DWORD*)_gCarCustomizeManager, RimsToCustomize == -1 ? 67 : 66); // REAR/FRONT_WHEEL

    for (i = 1; (DWORD*)PartList[0] != PartList; v4 = (DWORD*)PartList[0])
    {
        v6 = *v4;
        v7 = v4;
        v8 = (DWORD*)v4[1];
        *v8 = v6;
        *(DWORD**)(v6 + 4) = v8;
        v9 = v7[2];
        TheSelectablePart = v7 - 1;
        if (IsNoRimSize(_CustomizeRims[82]) || (_CustomizeRims[111] == CarPart_GetAppliedAttributeIParam((DWORD*)v9, 0xEB0101E2, 0))) // Inner Radius || IsNoRimSize
        {
            UnlockHash = CarCustomizeManager_GetUnlockHash((DWORD*)_gCarCustomizeManager, _CustomizeRims[82], TheSelectablePart[5]);
            TheCarPart = (DWORD*)TheSelectablePart[3];
            PartIcon = CarPart_GetAppliedAttributeIParam(TheCarPart, bStringHash("TEXTUREHASH"), 0x294D2A3);
            PartName = *(BYTE*)(TheSelectablePart[3] + 5) >> 5;
            IsLocked = CarCustomizeManager_IsPartLocked((DWORD*)_gCarCustomizeManager, TheSelectablePart, 0);
            CustomizationScreen_AddPartOption(_CustomizeRims, TheSelectablePart, PartIcon, PartName, 0, UnlockHash, IsLocked);
            if (TheActivePart && *((DWORD**)TheSelectablePart + 3) == TheActivePart) IndexActive = i;
            ++i;
        }
        else
        {
            (**(void(__thiscall***)(DWORD*, int))TheSelectablePart)(TheSelectablePart, 1);
        }
    }

    if (Index == -1) Index = TheActivePart ? IndexActive : 1;
    InitialOption = *(int*)_Showcase_FromIndex;
    if (*(int*)_Showcase_FromIndex)
    {
        if (*((BYTE*)_CustomizeRims + 297))
        {
            *((BYTE*)TheIconScroller + 240) = 0;
            *((BYTE*)TheIconScroller + 237) = 1;
            *((BYTE*)TheIconScroller + 238) = 0;
            TheIconScroller[57] = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD))(*TheIconScroller + 64))(TheIconScroller, InitialOption);
        *(int*)_Showcase_FromIndex = 0;
    }
    else
    {
        if (*((BYTE*)_CustomizeRims + 297))
        {
            *((BYTE*)TheIconScroller + 240) = 0;
            *((BYTE*)TheIconScroller + 237) = 1;
            *((BYTE*)TheIconScroller + 238) = 0;
            TheIconScroller[57] = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD))(*TheIconScroller + 64))(TheIconScroller, Index);
    }
    v20 = -1;
    bTList_SelectablePart_dtor((int**)PartList);
}

void __fastcall CustomizeRims_Setup(DWORD* _CustomizeRims, void* EDX_Unused)
{
    const char* FEPackage; // eax
    DWORD* ArrowL; // eax
    DWORD* ArrowR; // eax
    DWORD* TheActivePart; // eax

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    FEPackage = (const char*)_CustomizeRims[4];
    _CustomizeRims[87] = 0xE167F7C8; //GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsSpoilers", "CO_SPOILERS");
    ArrowL = FEngFindImage(FEPackage, 0x91C4A50u);
    FEngSetButtonTexture(ArrowL, 0x5BC); // L1
    ArrowR = FEngFindImage(FEPackage, 0x2D145BE3u);
    FEngSetButtonTexture(ArrowR, 0x682); // R1

    int MinInnerRadius = CarCustomizeManager_GetMinInnerRadius((DWORD*)_gCarCustomizeManager);
    int MaxInnerRadius = CarCustomizeManager_GetMaxInnerRadius((DWORD*)_gCarCustomizeManager);

    _CustomizeRims[111] = MinInnerRadius;
    _CustomizeRims[112] = MinInnerRadius;
    _CustomizeRims[113] = MaxInnerRadius;

    TheActivePart = (DWORD*)CarCustomizeManager_GetActivePartFromSlot((DWORD*)_gCarCustomizeManager, RimsToCustomize == -1 ? 67 : 66); // REAR/FRONT_WHEEL
    if (*(int*)_Showcase_FromFilter == -1)
    {
        if (TheActivePart)
            _CustomizeRims[111] = CarPart_GetAppliedAttributeIParam(TheActivePart, 0xEB0101E2, 0);
    }
    else
    {
        _CustomizeRims[111] = *(int*)_Showcase_FromFilter;
        *(int*)_Showcase_FromFilter = -1;
    }
    CustomizeRims_BuildRimsList(_CustomizeRims, EDX_Unused, -1);
    (*(void(__thiscall**)(DWORD*))(*_CustomizeRims + 12))(_CustomizeRims);
}