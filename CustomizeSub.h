#include "stdio.h"
#include "InGameFunctions.h"
#include "CarCustomizeManager.h"
#include "CustomizeShoppingCart.h"
#include "Helpers.h"
#include "UnlimiterData.h"
#include "IconScroller.h"

// TODO: Reimplement the spoiler and vinyl categories functions to support v4+ custom icons and names

int __fastcall CustomizeSub_SetupParts(DWORD* _CustomizeSub, void* EDX_Unused)
{
    DWORD* _CustomizeCategoryScreen; // esi
    unsigned int InitialPosition; // eax
    
    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    _CustomizeCategoryScreen = _CustomizeSub;
    _CustomizeSub[108] = CustomizeIsInBackRoom() != 0
        ? CarConfigs[CarTypeID].Names.BackroomParts
        : CarConfigs[CarTypeID].Names.Parts;
    CustomizeSetInParts(1);
    _CustomizeCategoryScreen[83] = *(DWORD*)g_pCustomizeMainPkg;

    if (CustomizeIsInBackRoom())
    {
        if (CarConfigs[CarTypeID].Parts.BodyKits)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.BackroomPartsBodyKits,
            CarConfigs[CarTypeID].Names.PartsBodyKits,
            0x101);
        if (CarConfigs[CarTypeID].Parts.Spoilers)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSpoilerPkg,
            CarConfigs[CarTypeID].Icons.BackroomPartsSpoilers,
            CarConfigs[CarTypeID].Names.PartsSpoilers,
            0x102);
        if (CarConfigs[CarTypeID].Parts.Rims)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSubTopPkg,
            CarConfigs[CarTypeID].Icons.BackroomPartsRims,
            CarConfigs[CarTypeID].Names.PartsRims,
            0x103);
        if (CarConfigs[CarTypeID].Parts.Hoods)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.BackroomPartsHoods,
            CarConfigs[CarTypeID].Names.PartsHoods,
            0x104);
        if (CarConfigs[CarTypeID].Parts.RoofScoops)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.BackroomPartsRoofScoops,
            CarConfigs[CarTypeID].Names.PartsRoofScoops,
            0x105);
        if (BETACompatibility && CarConfigs[CarTypeID].Visual.CustomGauges)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeHudPkg,
            CarConfigs[CarTypeID].Icons.BackroomVisualCustomGauges,
            CarConfigs[CarTypeID].Names.VisualCustomGauges,
            0x307);
    }
    else
    {
        if (CarConfigs[CarTypeID].Parts.BodyKits)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsBodyKits,
            CarConfigs[CarTypeID].Names.PartsBodyKits,
            0x101);
        if (CarConfigs[CarTypeID].Parts.Spoilers)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSpoilerPkg,
            CarConfigs[CarTypeID].Icons.PartsSpoilers,
            CarConfigs[CarTypeID].Names.PartsSpoilers,
            0x102);
        if (CarConfigs[CarTypeID].Parts.Rims)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSubTopPkg,
            CarConfigs[CarTypeID].Icons.PartsRims,
            CarConfigs[CarTypeID].Names.PartsRims,
            0x103);
        if (CarConfigs[CarTypeID].Parts.Hoods)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsHoods,
            CarConfigs[CarTypeID].Names.PartsHoods,
            0x104);
        if (CarConfigs[CarTypeID].Parts.RoofScoops)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsRoofScoops,
            CarConfigs[CarTypeID].Names.PartsRoofScoops,
            0x105);
        // New options
        if (CarConfigs[CarTypeID].Parts.Interior)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsInterior,
            CarConfigs[CarTypeID].Names.PartsInterior,
            0x106);
        if (CarConfigs[CarTypeID].Parts.Roof)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsRoof,
            CarConfigs[CarTypeID].Names.PartsRoof,
            0x107);
        if (CarConfigs[CarTypeID].Parts.Brakes)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsBrakes,
            CarConfigs[CarTypeID].Names.PartsBrakes,
            0x108);
        if (CarConfigs[CarTypeID].Parts.Headlights)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsHeadlights,
            CarConfigs[CarTypeID].Names.PartsHeadlights,
            0x109);
        if (CarConfigs[CarTypeID].Parts.Taillights)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsTaillights,
            CarConfigs[CarTypeID].Names.PartsTaillights,
            0x10A);
        if (CarConfigs[CarTypeID].Parts.Mirrors)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsMirrors,
            CarConfigs[CarTypeID].Names.PartsMirrors,
            0x10B);
        if (CarConfigs[CarTypeID].Parts.Attachments >= 1)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSubTopPkg,
            CarConfigs[CarTypeID].Icons.PartsAttachments,
            CarConfigs[CarTypeID].Names.PartsAttachments,
            0x10C);
        if (BETACompatibility && CarConfigs[CarTypeID].Visual.CustomGauges)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeHudPkg,
            CarConfigs[CarTypeID].Icons.VisualCustomGauges,
            CarConfigs[CarTypeID].Names.VisualCustomGauges,
            0x307);
    }
    InitialPosition = IconScroller_GetOptionIndexWithID(_CustomizeCategoryScreen + 11, EDX_Unused, _CustomizeCategoryScreen[85]);

    if (*((BYTE*)_CustomizeCategoryScreen + 0x129))
    {
        *((BYTE*)_CustomizeCategoryScreen + 0x11C) = 0;
        *((BYTE*)_CustomizeCategoryScreen + 0x119) = 1;
        *((BYTE*)_CustomizeCategoryScreen + 0x11A) = 0;
        _CustomizeCategoryScreen[68] = 0;
    }
    return (*(int(__thiscall**)(DWORD*, unsigned int))(_CustomizeCategoryScreen[11] + 0x40))( // IconScroller::SetInitialPos(int)
        _CustomizeCategoryScreen + 0xB,
        InitialPosition);
}

int __fastcall CustomizeSub_SetupAttachments(DWORD* _CustomizeSub, void* EDX_Unused)
{
    DWORD* _CustomizeCategoryScreen; // esi
    unsigned int InitialPosition; // eax
    int result;

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    _CustomizeCategoryScreen = _CustomizeSub;
    _CustomizeSub[108] = CarConfigs[CarTypeID].Names.PartsAttachments;
    _CustomizeCategoryScreen[83] = *(DWORD*)g_pCustomizeSubPkg;

    int CurrAttachment = 1;
    int NumAttachments = CarConfigs[CarTypeID].Parts.Attachments;
    
    if (CurrAttachment <= NumAttachments)
    {
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsAttachment0,
            CarConfigs[CarTypeID].Names.PartsAttachment0,
            0x10C + CurrAttachment++);
    }
    if (CurrAttachment <= NumAttachments)
    {
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsAttachment1,
            CarConfigs[CarTypeID].Names.PartsAttachment1,
            0x10C + CurrAttachment++);
    }
    if (CurrAttachment <= NumAttachments)
    {
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsAttachment2,
            CarConfigs[CarTypeID].Names.PartsAttachment2,
            0x10C + CurrAttachment++);
    }
    if (CurrAttachment <= NumAttachments)
    {
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsAttachment3,
            CarConfigs[CarTypeID].Names.PartsAttachment3,
            0x10C + CurrAttachment++);
    }
    if (CurrAttachment <= NumAttachments)
    {
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsAttachment4,
            CarConfigs[CarTypeID].Names.PartsAttachment4,
            0x10C + CurrAttachment++);
    }
    if (CurrAttachment <= NumAttachments)
    {
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsAttachment5,
            CarConfigs[CarTypeID].Names.PartsAttachment5,
            0x10C + CurrAttachment++);
    }
    if (CurrAttachment <= NumAttachments)
    {
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsAttachment6,
            CarConfigs[CarTypeID].Names.PartsAttachment6,
            0x10C + CurrAttachment++);
    }
    if (CurrAttachment <= NumAttachments)
    {
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsAttachment7,
            CarConfigs[CarTypeID].Names.PartsAttachment7,
            0x10C + CurrAttachment++);
    }
    if (CurrAttachment <= NumAttachments)
    {
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsAttachment8,
            CarConfigs[CarTypeID].Names.PartsAttachment8,
            0x10C + CurrAttachment++);
    }
    if (CurrAttachment <= NumAttachments)
    {
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            CarConfigs[CarTypeID].Icons.PartsAttachment9,
            CarConfigs[CarTypeID].Names.PartsAttachment9,
            0x10C + CurrAttachment++);
    }

    if (_CustomizeCategoryScreen[85] == 0x801)
    {
        result = (*(int(__thiscall**)(DWORD*, unsigned int))(_CustomizeCategoryScreen[11] + 0x40))( // IconScroller::SetInitialPos(int)
            _CustomizeCategoryScreen + 0xB,
            1);
    }
    else
    {
        InitialPosition = IconScroller_GetOptionIndexWithID(_CustomizeCategoryScreen + 11, EDX_Unused, _CustomizeCategoryScreen[85]);
        result = (*(int(__thiscall**)(DWORD*, unsigned int))(_CustomizeCategoryScreen[11] + 0x40))( // IconScroller::SetInitialPos(int)
            _CustomizeCategoryScreen + 0xB,
            InitialPosition);
        _CustomizeCategoryScreen[85] = 0x801;
    }

    if (*((BYTE*)_CustomizeCategoryScreen + 0x129))
    {
        *((BYTE*)_CustomizeCategoryScreen + 0x11C) = 0;
        *((BYTE*)_CustomizeCategoryScreen + 0x119) = 1;
        *((BYTE*)_CustomizeCategoryScreen + 0x11A) = 0;
        _CustomizeCategoryScreen[68] = 0;
    }

    return result;
}

int __fastcall CustomizeSub_GetRimBrandIndex(DWORD* CustomizeSub, void* EDX_Unused, unsigned int WheelManufacturerHash)
{
    int RimBrandsCount = RimBrands.size();

    for (int i = 0; i < RimBrandsCount; i++)
    {
        if (RimBrands[i].BrandNameHash == WheelManufacturerHash) return i + 2;
    }

    return 1;
}

int __fastcall CustomizeSub_SetupRimBrands(DWORD* _CustomizeSub, void* EDX_Unused)
{
    DWORD* StockPart;
    DWORD* RimSelectablePart; // eax
    DWORD* InstalledRim; // ebp
    DWORD* StockRimIconOption; // eax MAPDST
    int TheRimShoppingCartItem; // eax
    unsigned int RimBrandName;
    DWORD* CustomizationRecord; // edi
    int CarType; // eax
    DWORD* InstalledPart; // eax
    DWORD PreviousMenu; // eax
    unsigned int InitialPosition; // eax
    int result; // eax
    DWORD ARimPart[11]; // [esp+10h] [ebp-38h] BYREF
    //int v16; // [esp+44h] [ebp-4h]

    int RimBrandsCount = RimBrands.size();

    DWORD* FEDatabase = *(DWORD**)_FEDatabase;

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    _CustomizeSub[108] = CarConfigs[CarTypeID].Names.PartsRimsBrand;
    _CustomizeSub[83] = *(DWORD*)g_pCustomizeSubPkg;

    StockPart = CarCustomizeManager_GetStockCarPart((DWORD*)_gCarCustomizeManager, RimsToCustomize == -1 ? 67 : 66); // FRONT_WHEEL

    RimSelectablePart = (DWORD*)j_malloc(0x2C);
    if (RimSelectablePart)
    {
        RimSelectablePart[0] = SelectablePart_vtable;
        RimSelectablePart[3] = (DWORD)StockPart;
        RimSelectablePart[4] = RimsToCustomize == -1 ? 67 : 66; // FRONT_WHEEL
        RimSelectablePart[5] = 0;
        RimSelectablePart[6] = 7;
        *((BYTE*)RimSelectablePart + 0x1C) = 0;
        RimSelectablePart[8] = 1;
        RimSelectablePart[9] = 0;
        *((BYTE*)RimSelectablePart + 40) = 0;
        InstalledRim = RimSelectablePart;
    }
    else
    {
        InstalledRim = 0;
    }
    
    //if (CarCustomizeManager_IsPartInstalled((DWORD*)_gCarCustomizeManager, InstalledRim)) InstalledRim[8] = 16; // For some reason, this breaks stock rim option

    StockRimIconOption = (DWORD*)j_malloc(0x5C);
    //v16 = 0;
    if (StockRimIconOption)
    {
        IconOption_Create(StockRimIconOption, 0xF3990B6, 0x60A662F5, 0); // VISUAL_RIMS_BRAND_STOCK, CO_RETURN_TO_STOCK
        StockRimIconOption[19] = _nullString;
        StockRimIconOption[21] = 1;
        StockRimIconOption[20] = 0x7010701;
        StockRimIconOption[0] = SetStockPartOption_vtable;
        StockRimIconOption[22] = (DWORD)InstalledRim;
        *((BYTE*)StockRimIconOption + 69) = 1;
    }
    else
    {
        StockRimIconOption = 0;
    }
    //v16 = -1;

    // Add stock rims option
    IconScrollerMenu_AddOption(_CustomizeSub, StockRimIconOption);

    // Check if the car has OEM rims
    bool HasNoCustomRims = CarConfigs[CarTypeID].Parts.RimsCustom == 0;

    DWORD RimBrandIconHash = -1;
    DWORD RimBrandNameHash = -1;

    // Add the brands from ini
    for (int i = 0; i < RimBrandsCount; i++)
    {
        if (i == 0)
        {
            if (HasNoCustomRims) continue;

            RimBrandIconHash = CarConfigs[CarTypeID].Icons.PartsRimsCustom;
            RimBrandNameHash = CarConfigs[CarTypeID].Names.PartsRimsCustom;

            if (RimBrandIconHash == -1) RimBrandIconHash = RimBrands[i].TextureHash;
            if (RimBrandNameHash == -1) RimBrandNameHash = RimBrands[i].StringHash;
        }
        else
        {
            RimBrandIconHash = RimBrands[i].TextureHash;
            RimBrandNameHash = RimBrands[i].StringHash;
        }

        CustomizeCategoryScreen_AddCustomOption(_CustomizeSub, *(char**)g_pCustomizeRimsPkg, RimBrandIconHash, RimBrandNameHash, 0x702 + i);
    }

    ARimPart[0] = SelectablePart_vtable;
    ARimPart[3] = 0;
    ARimPart[4] = RimsToCustomize == -1 ? 67 : 66; // FRONT_WHEEL
    ARimPart[5] = 0;
    ARimPart[6] = 7;
    *((BYTE*)ARimPart + 0x1C) = 0;
    ARimPart[8] = 1;
    ARimPart[9] = 0;
    *((BYTE*)ARimPart + 40) = 0;

    TheRimShoppingCartItem = CarCustomizeManager_IsPartTypeInCart((DWORD*)_gCarCustomizeManager, ARimPart);

    if (TheRimShoppingCartItem)
    {
        RimBrandName = CarPart_GetAppliedAttributeUParam(*(DWORD**)(*(DWORD*)(TheRimShoppingCartItem + 12) + 12), 0xEBB03E66, 0);
        _CustomizeSub[107] = CustomizeSub_GetRimBrandIndex(_CustomizeSub, 0, RimBrandName) - HasNoCustomRims;
    }
    CustomizationRecord = FEPlayerCarDB_GetCustomizationRecordByHandle((DWORD*)(*((DWORD*)FEDatabase + 4) + 0x414), *((BYTE*)FECarRecord + 16));
    CarType = FECarRecord_GetType(FECarRecord);
    InstalledPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, CarType, RimsToCustomize == -1 ? 67 : 66); // FRONT_WHEEL
    if (InstalledPart)
    {
        RimBrandName = CarPart_GetAppliedAttributeUParam(InstalledPart, 0xEBB03E66, 0);
        _CustomizeSub[106] = CustomizeSub_GetRimBrandIndex(_CustomizeSub, 0, RimBrandName) - HasNoCustomRims;
    }
    PreviousMenu = _CustomizeSub[85];
    if (PreviousMenu == 0x801)
    {
        InitialPosition = _CustomizeSub[107];
        if (!InitialPosition)
        {
            if (_CustomizeSub[106])
                IconScrollerMenu_SetInitialOption(_CustomizeSub, _CustomizeSub[106]);
            else
                IconScrollerMenu_SetInitialOption(_CustomizeSub, 1);
            goto LABEL_26;
        }
    }
    else
    {
        InitialPosition = IconScroller_GetOptionIndexWithID(_CustomizeSub + 11, EDX_Unused, PreviousMenu);
    }
    if (*((BYTE*)_CustomizeSub + 297))
    {
        _CustomizeSub[68] = 0;
        *((BYTE*)_CustomizeSub + 284) = 0;
        *((BYTE*)_CustomizeSub + 281) = 1;
        *((BYTE*)_CustomizeSub + 282) = 0;
    }
    (*(void(__thiscall**)(DWORD*, unsigned int))(_CustomizeSub[11] + 64))(_CustomizeSub + 11, InitialPosition);
LABEL_26:
    result = _CustomizeSub[85];
    if (result >= 0x701 && result <= 0x702 + RimBrandsCount)
        _CustomizeSub[85] = 0x801;
    return result;
}

int __fastcall CustomizeSub_SetupPerformance(DWORD* _CustomizeSub, void* EDX_Unused)
{
    DWORD* _CustomizeCategoryScreen; // esi
    unsigned int InitialPosition; // eax

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    _CustomizeCategoryScreen = _CustomizeSub;
    _CustomizeSub[108] = CustomizeIsInBackRoom() != 0
        ? CarConfigs[CarTypeID].Names.BackroomPerformance
        : CarConfigs[CarTypeID].Names.Performance;

    _CustomizeSub[83] = *(DWORD*)g_pCustomizeMainPkg;
    CustomizeSetInPerformance(1);

    if (CustomizeIsInBackRoom())
    {
        if (CarConfigs[CarTypeID].Performance.Engine)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.BackroomPerformanceEngine,
                CarConfigs[CarTypeID].Names.PerformanceEngine,
                0x201);

        if (CarConfigs[CarTypeID].Performance.Transmission)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.BackroomPerformanceTransmission,
                CarConfigs[CarTypeID].Names.PerformanceTransmission,
                0x202);

        if (CarConfigs[CarTypeID].Performance.Chassis)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.BackroomPerformanceChassis,
                CarConfigs[CarTypeID].Names.PerformanceChassis,
                0x203);

        if (CarConfigs[CarTypeID].Performance.Nitrous)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.BackroomPerformanceNitrous,
                CarConfigs[CarTypeID].Names.PerformanceNitrous,
                0x204);

        if (CarConfigs[CarTypeID].Performance.Tires)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.BackroomPerformanceTires,
                CarConfigs[CarTypeID].Names.PerformanceTires,
                0x205);

        if (CarConfigs[CarTypeID].Performance.Brakes)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.BackroomPerformanceBrakes,
                CarConfigs[CarTypeID].Names.PerformanceBrakes,
                0x206);

        if (CarConfigs[CarTypeID].Performance.Induction)
        {
            if (CarCustomizeManager_IsTurbo((DWORD*)_gCarCustomizeManager))
            {
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeSub,
                    *(char**)g_pCustomizePerfPkg,
                    CarConfigs[CarTypeID].Icons.BackroomPerformanceTurbo,
                    CarConfigs[CarTypeID].Names.PerformanceTurbo,
                    0x207);
            }
            else
            {
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeSub,
                    *(char**)g_pCustomizePerfPkg,
                    CarConfigs[CarTypeID].Icons.BackroomPerformanceSupercharger,
                    CarConfigs[CarTypeID].Names.PerformanceSupercharger,
                    0x207);
            }
        }
    }

    else
    {
        if (CarConfigs[CarTypeID].Performance.Engine)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.PerformanceEngine,
                CarConfigs[CarTypeID].Names.PerformanceEngine,
                0x201);

        if (CarConfigs[CarTypeID].Performance.Transmission)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.PerformanceTransmission,
                CarConfigs[CarTypeID].Names.PerformanceTransmission,
                0x202);

        if (CarConfigs[CarTypeID].Performance.Chassis)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.PerformanceChassis,
                CarConfigs[CarTypeID].Names.PerformanceChassis,
                0x203);

        if (CarConfigs[CarTypeID].Performance.Nitrous)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.PerformanceNitrous,
                CarConfigs[CarTypeID].Names.PerformanceNitrous,
                0x204);

        if (CarConfigs[CarTypeID].Performance.Tires)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.PerformanceTires,
                CarConfigs[CarTypeID].Names.PerformanceTires,
                0x205);

        if (CarConfigs[CarTypeID].Performance.Brakes)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                CarConfigs[CarTypeID].Icons.PerformanceBrakes,
                CarConfigs[CarTypeID].Names.PerformanceBrakes,
                0x206);

        if (CarConfigs[CarTypeID].Performance.Induction)
        {
            if (CarCustomizeManager_IsTurbo((DWORD*)_gCarCustomizeManager))
            {
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeSub,
                    *(char**)g_pCustomizePerfPkg,
                    CarConfigs[CarTypeID].Icons.PerformanceTurbo,
                    CarConfigs[CarTypeID].Names.PerformanceTurbo,
                    0x207);
            }
            else
            {
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeSub,
                    *(char**)g_pCustomizePerfPkg,
                    CarConfigs[CarTypeID].Icons.PerformanceSupercharger,
                    CarConfigs[CarTypeID].Names.PerformanceSupercharger,
                    0x207);
            }
        }
    }

    InitialPosition = IconScroller_GetOptionIndexWithID(_CustomizeCategoryScreen + 11, EDX_Unused, _CustomizeCategoryScreen[85]);
    if (*((BYTE*)_CustomizeCategoryScreen + 0x129))
    {
        *((BYTE*)_CustomizeCategoryScreen + 0x11C) = 0;
        *((BYTE*)_CustomizeCategoryScreen + 0x119) = 1;
        *((BYTE*)_CustomizeCategoryScreen + 0x11A) = 0;
        _CustomizeCategoryScreen[68] = 0;
    }
    return (*(int(__thiscall**)(DWORD*, unsigned int))(_CustomizeCategoryScreen[11] + 0x40))(
        _CustomizeCategoryScreen + 0xB,
        InitialPosition);
}

int __fastcall CustomizeSub_SetupVisual(DWORD* _CustomizeSub, void *EDX_Unused)
{
    DWORD* _CustomizeCategoryScreen; // esi
    unsigned int InitialPosition; // eax

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    _CustomizeCategoryScreen = _CustomizeSub;
    _CustomizeSub[108] = CustomizeIsInBackRoom() != 0
        ? CarConfigs[CarTypeID].Names.BackroomVisual
        : CarConfigs[CarTypeID].Names.Visual;

    _CustomizeCategoryScreen[83] = *(DWORD*)g_pCustomizeMainPkg;

    if (CustomizeIsInBackRoom())
    {
        if (CarConfigs[CarTypeID].Visual.Paint)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePaintPkg,
            CarConfigs[CarTypeID].Icons.BackroomVisualPaint,
            CarConfigs[CarTypeID].Names.VisualPaint,
            0x301);
        if (!HPCCompatibility)
        {
            if (CarConfigs[CarTypeID].Visual.Vinyls)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    CarConfigs[CarTypeID].Icons.BackroomVisualVinyls,
                    CarConfigs[CarTypeID].Names.VisualVinyls,
                    0x302);
            if (CarConfigs[CarTypeID].Visual.Decals && !IsMenuEmpty_Decals(CarTypeID))
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    CarConfigs[CarTypeID].Icons.BackroomVisualDecals,
                    CarConfigs[CarTypeID].Names.VisualDecals,
                    0x305);
            if (!BETACompatibility && CarConfigs[CarTypeID].Visual.CustomGauges)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeHudPkg,
                    CarConfigs[CarTypeID].Icons.BackroomVisualCustomGauges,
                    CarConfigs[CarTypeID].Names.VisualCustomGauges,
                    0x307);
        }
    }
    else
    {
        if (CarConfigs[CarTypeID].Visual.Paint)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePaintPkg,
            CarConfigs[CarTypeID].Icons.VisualPaint,
            CarConfigs[CarTypeID].Names.VisualPaint,
            0x301);
        if (!HPCCompatibility)
        {
            if (CarConfigs[CarTypeID].Visual.Vinyls)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    CarConfigs[CarTypeID].Icons.VisualVinyls,
                    CarConfigs[CarTypeID].Names.VisualVinyls,
                    0x302);
            if (CarConfigs[CarTypeID].Visual.RimPaint)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePaintPkg,
                    CarConfigs[CarTypeID].Icons.VisualRimPaint,
                    CarConfigs[CarTypeID].Names.VisualRimPaint,
                    0x303);
            if (CarConfigs[CarTypeID].Visual.WindowTint)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    CarConfigs[CarTypeID].Icons.VisualWindowTint,
                    CarConfigs[CarTypeID].Names.VisualWindowTint,
                    0x304);
            if (CarConfigs[CarTypeID].Visual.Decals && !IsMenuEmpty_Decals(CarTypeID))
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    CarConfigs[CarTypeID].Icons.VisualDecals,
                    CarConfigs[CarTypeID].Names.VisualDecals,
                    0x305);
            if (CarConfigs[CarTypeID].Visual.Numbers)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    "Numbers.fng",
                    CarConfigs[CarTypeID].Icons.VisualNumbers,
                    CarConfigs[CarTypeID].Names.VisualNumbers,
                    0x306);
            if (!BETACompatibility && CarConfigs[CarTypeID].Visual.CustomGauges)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeHudPkg,
                    CarConfigs[CarTypeID].Icons.VisualCustomGauges,
                    CarConfigs[CarTypeID].Names.VisualCustomGauges,
                    0x307);
            if (CarConfigs[CarTypeID].Visual.Driver)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    CarConfigs[CarTypeID].Icons.VisualDriver,
                    CarConfigs[CarTypeID].Names.VisualDriver,
                    0x308);
            if (CarConfigs[CarTypeID].Visual.LicensePlate)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    CarConfigs[CarTypeID].Icons.VisualLicensePlate,
                    CarConfigs[CarTypeID].Names.VisualLicensePlate,
                    0x309);
            if (CarConfigs[CarTypeID].Visual.Tires)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    CarConfigs[CarTypeID].Icons.VisualTires,
                    CarConfigs[CarTypeID].Names.VisualTires,
                    0x314);
            if (CarConfigs[CarTypeID].Visual.Neon)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    CarConfigs[CarTypeID].Icons.VisualNeon,
                    CarConfigs[CarTypeID].Names.VisualNeon,
                    0x315);
        }
    }
    InitialPosition = IconScroller_GetOptionIndexWithID(_CustomizeCategoryScreen + 11, EDX_Unused, _CustomizeCategoryScreen[85]);
    if (*((BYTE*)_CustomizeCategoryScreen + 0x129))
    {
        *((BYTE*)_CustomizeCategoryScreen + 0x11C) = 0;
        *((BYTE*)_CustomizeCategoryScreen + 0x119) = 1;
        *((BYTE*)_CustomizeCategoryScreen + 0x11A) = 0;
        _CustomizeCategoryScreen[68] = 0;
    }
    return (*(int(__thiscall**)(DWORD*, unsigned int))(_CustomizeCategoryScreen[11] + 0x40))(
        _CustomizeCategoryScreen + 0xB,
        InitialPosition);
}

void __fastcall CustomizeSub_SetupDecalLocations(DWORD* CustomizeSub, void* EDX_Unused)
{
    DWORD PreviousMenu; // eax
    unsigned int InitialPosition; // eax

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    CustomizeSub[108] = CarConfigs[CarTypeID].Names.VisualDecalsLocation;
    CustomizeSub[83] = *(DWORD*)g_pCustomizeSubPkg;

    if (CarConfigs[CarTypeID].Visual.DecalsWindshield)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            CarConfigs[CarTypeID].Icons.VisualDecalsWindshield,
            CarConfigs[CarTypeID].Names.VisualDecalsWindshield,
            0x501);
    if (CarConfigs[CarTypeID].Visual.DecalsRearWindow)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            CarConfigs[CarTypeID].Icons.VisualDecalsRearWindow,
            CarConfigs[CarTypeID].Names.VisualDecalsRearWindow,
            0x502);
    if (CarConfigs[CarTypeID].Visual.DecalsLeftDoor)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            CarConfigs[CarTypeID].Icons.VisualDecalsLeftDoor,
            CarConfigs[CarTypeID].Names.VisualDecalsLeftDoor,
            0x503);
    if (CarConfigs[CarTypeID].Visual.DecalsRightDoor)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            CarConfigs[CarTypeID].Icons.VisualDecalsRightDoor,
            CarConfigs[CarTypeID].Names.VisualDecalsRightDoor,
            0x504);
    if (CarConfigs[CarTypeID].Visual.DecalsLeftQuarter)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            CarConfigs[CarTypeID].Icons.VisualDecalsLeftQuarter,
            CarConfigs[CarTypeID].Names.VisualDecalsLeftQuarter,
            0x505);
    if (CarConfigs[CarTypeID].Visual.DecalsRightQuarter)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            CarConfigs[CarTypeID].Icons.VisualDecalsRightQuarter,
            CarConfigs[CarTypeID].Names.VisualDecalsRightQuarter,
            0x506);
    
    PreviousMenu = CustomizeSub[85];
    if (PreviousMenu == 0x803)
    {
        if (*((BYTE*)CustomizeSub + 297))
        {
            *((BYTE*)CustomizeSub + 284) = 0;
            *((BYTE*)CustomizeSub + 281) = 1;
            *((BYTE*)CustomizeSub + 282) = 0;
            CustomizeSub[68] = 0;
        }
        (*(void(__thiscall**)(DWORD*, int))(CustomizeSub[11] + 64))(CustomizeSub + 11, 1);
    }
    else
    {
        InitialPosition = IconScroller_GetOptionIndexWithID(CustomizeSub + 11, EDX_Unused, PreviousMenu);
        if (*((BYTE*)CustomizeSub + 297))
        {
            *((BYTE*)CustomizeSub + 284) = 0;
            *((BYTE*)CustomizeSub + 281) = 1;
            *((BYTE*)CustomizeSub + 282) = 0;
            CustomizeSub[68] = 0;
        }
        (*(void(__thiscall**)(DWORD*, unsigned int))(CustomizeSub[11] + 64))(CustomizeSub + 11, InitialPosition);
    }

    if (PreviousMenu >= 0x501 && PreviousMenu <= 0x506)
        CustomizeSub[85] = 0x803;
}

void __fastcall CustomizeSub_SetupDecalPositions(DWORD* CustomizeSub, void* EDX_Unused)
{
    DWORD PreviousMenu; // eax
    unsigned int InitialPosition; // eax
    DWORD* DecalPart;
    int NumDecals;
    int CurrDecal = 1;

    // Get car and customization record
    DWORD* FEDatabase = *(DWORD**)_FEDatabase;
    DWORD* FECarRecord = *(DWORD**)_FECarRecord;
    DWORD* CustomizationRecord = FEPlayerCarDB_GetCustomizationRecordByHandle((DWORD*)(*((DWORD*)FEDatabase + 4) + 0x414), *((BYTE*)FECarRecord + 16));

    int CarTypeID = FECarRecord_GetType(FECarRecord);

    CustomizeSub[108] = CarConfigs[CarTypeID].Names.VisualDecalsPosition;
    CustomizeSub[83] = *(DWORD*)g_pCustomizeSubTopPkg;
    
    switch (CustomizeSub[84])
    {
    case 0x501: // Windshield
        // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 70); // DECAL_FRONT_WINDOW_WIDE_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash((char*)"NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 8) NumDecals = 1;
        }
        else NumDecals = 1;

        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsWindshield1,
                CarConfigs[CarTypeID].Names.VisualDecalsWindshield1,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsWindshield2,
                CarConfigs[CarTypeID].Names.VisualDecalsWindshield2,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsWindshield3,
                CarConfigs[CarTypeID].Names.VisualDecalsWindshield3,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsWindshield4,
                CarConfigs[CarTypeID].Names.VisualDecalsWindshield4,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsWindshield5,
                CarConfigs[CarTypeID].Names.VisualDecalsWindshield5,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsWindshield6,
                CarConfigs[CarTypeID].Names.VisualDecalsWindshield6,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsWindshield7,
                CarConfigs[CarTypeID].Names.VisualDecalsWindshield7,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsWindshield8,
                CarConfigs[CarTypeID].Names.VisualDecalsWindshield8,
                0x600 + CurrDecal++);
        }
        break;
    case 0x502: // Rear Window
        // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 71); // DECAL_REAR_WINDOW_WIDE_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash((char*)"NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 8) NumDecals = 1;
        }
        else NumDecals = 1;

        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRearWindow1,
                CarConfigs[CarTypeID].Names.VisualDecalsRearWindow1,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRearWindow2,
                CarConfigs[CarTypeID].Names.VisualDecalsRearWindow2,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRearWindow3,
                CarConfigs[CarTypeID].Names.VisualDecalsRearWindow3,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRearWindow4,
                CarConfigs[CarTypeID].Names.VisualDecalsRearWindow4,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRearWindow5,
                CarConfigs[CarTypeID].Names.VisualDecalsRearWindow5,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRearWindow6,
                CarConfigs[CarTypeID].Names.VisualDecalsRearWindow6,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRearWindow7,
                CarConfigs[CarTypeID].Names.VisualDecalsRearWindow7,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRearWindow8,
                CarConfigs[CarTypeID].Names.VisualDecalsRearWindow8,
                0x600 + CurrDecal++);
        }
        break;
    case 0x503: // Left Door
    // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 72); // DECAL_LEFT_DOOR_RECT_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash((char*)"NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 6) NumDecals = 6;
        }
        else NumDecals = 6;

        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftDoor1,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftDoor1,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftDoor2,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftDoor2,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftDoor3,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftDoor3,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftDoor4,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftDoor4,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftDoor5,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftDoor5,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftDoor6,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftDoor6,
                0x600 + CurrDecal++);
        }

        break;
    case 0x504: // Left Door
    // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 73); // DECAL_RIGHT_DOOR_RECT_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash((char*)"NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 6) NumDecals = 6;
        }
        else NumDecals = 6;

        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightDoor1,
                CarConfigs[CarTypeID].Names.VisualDecalsRightDoor1,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightDoor2,
                CarConfigs[CarTypeID].Names.VisualDecalsRightDoor2,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightDoor3,
                CarConfigs[CarTypeID].Names.VisualDecalsRightDoor3,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightDoor4,
                CarConfigs[CarTypeID].Names.VisualDecalsRightDoor4,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightDoor5,
                CarConfigs[CarTypeID].Names.VisualDecalsRightDoor5,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightDoor6,
                CarConfigs[CarTypeID].Names.VisualDecalsRightDoor6,
                0x600 + CurrDecal++);
        }

        break;
    case 0x505: // Left Quarter
    // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 74); // DECAL_LEFT_QUARTER_RECT_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash((char*)"NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 8) NumDecals = 1;
        }
        else NumDecals = 1;

        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftQuarter1,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftQuarter1,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftQuarter2,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftQuarter2,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftQuarter3,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftQuarter3,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftQuarter4,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftQuarter4,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftQuarter5,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftQuarter5,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftQuarter6,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftQuarter6,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftQuarter7,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftQuarter7,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsLeftQuarter8,
                CarConfigs[CarTypeID].Names.VisualDecalsLeftQuarter8,
                0x600 + CurrDecal++);
        }
        break;
    case 0x506: // Right Quarter
        // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 75); // DECAL_RIGHT_QUARTER_RECT_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash((char*)"NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 8) NumDecals = 1;
        }
        else NumDecals = 1;

        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightQuarter1,
                CarConfigs[CarTypeID].Names.VisualDecalsRightQuarter1,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightQuarter2,
                CarConfigs[CarTypeID].Names.VisualDecalsRightQuarter2,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightQuarter3,
                CarConfigs[CarTypeID].Names.VisualDecalsRightQuarter3,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightQuarter4,
                CarConfigs[CarTypeID].Names.VisualDecalsRightQuarter4,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightQuarter5,
                CarConfigs[CarTypeID].Names.VisualDecalsRightQuarter5,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightQuarter6,
                CarConfigs[CarTypeID].Names.VisualDecalsRightQuarter6,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightQuarter7,
                CarConfigs[CarTypeID].Names.VisualDecalsRightQuarter7,
                0x600 + CurrDecal++);
        }
        if (CurrDecal <= NumDecals)
        {
            CustomizeCategoryScreen_AddCustomOption(
                CustomizeSub,
                *(char**)g_pCustomizeDecalsPkg,
                CarConfigs[CarTypeID].Icons.VisualDecalsRightQuarter8,
                CarConfigs[CarTypeID].Names.VisualDecalsRightQuarter8,
                0x600 + CurrDecal++);
        }
        break;
    }

    PreviousMenu = CustomizeSub[85];
    if (PreviousMenu == 0x305)
    {
        if (*((BYTE*)CustomizeSub + 297))
        {
            *((BYTE*)CustomizeSub + 284) = 0;
            *((BYTE*)CustomizeSub + 281) = 1;
            *((BYTE*)CustomizeSub + 282) = 0;
            CustomizeSub[68] = 0;
        }
        (*(void(__thiscall**)(DWORD*, int))(CustomizeSub[11] + 64))(CustomizeSub + 11, 1);
    }
    else
    {
        InitialPosition = IconScroller_GetOptionIndexWithID(CustomizeSub + 11, EDX_Unused, PreviousMenu);
        if (*((BYTE*)CustomizeSub + 297))
        {
            *((BYTE*)CustomizeSub + 284) = 0;
            *((BYTE*)CustomizeSub + 281) = 1;
            *((BYTE*)CustomizeSub + 282) = 0;
            CustomizeSub[68] = 0;
        }
        (*(void(__thiscall**)(DWORD*, unsigned int))(CustomizeSub[11] + 64))(CustomizeSub + 11, InitialPosition);
        CustomizeSub[85] = 0x305;
    }
}

int CustomizeSub_GetVinylGroupIndex(int group)
{
    int VinylGroupsCount = VinylGroups.size();

    for (int i = 0; i < VinylGroupsCount; i++)
    {
        if (VinylGroups[i].Index == group) return i + 2;
    }

    return 1;
}

int __fastcall CustomizeSub_SetupVinylGroups(DWORD* _CustomizeSub, void* EDX_Unused)
{
    DWORD* VinylSelectablePart; // eax
    DWORD* InstalledVinyl; // ebp
    DWORD* StockVinylIconOption; // eax MAPDST
    int VinylShoppingCartItem; // eax
    int SelectablePartInCart; // eax
    int TheVinylPart; // eax
    DWORD* CustomizationRecord; // edi
    int CarType; // eax
    DWORD* InstalledPart; // eax
    DWORD PreviousMenu; // eax
    unsigned int InitialPosition; // eax
    int result; // eax
    DWORD AVinylPart[11]; // [esp+10h] [ebp-38h] BYREF
    //int v16; // [esp+44h] [ebp-4h]

    int VinylGroupsCount = VinylGroups.size();

    DWORD* FEDatabase = *(DWORD**)_FEDatabase;

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    _CustomizeSub[108] = CarConfigs[CarTypeID].Names.VisualVinylsGroup;
    _CustomizeSub[83] = *(DWORD*)g_pCustomizeSubPkg;

    VinylSelectablePart = (DWORD*)j_malloc(0x2C);
    if (VinylSelectablePart)
    {
        VinylSelectablePart[0] = SelectablePart_vtable;
        VinylSelectablePart[3] = 0;
        VinylSelectablePart[4] = 77; // VINYL_LAYER0
        VinylSelectablePart[5] = 0;
        VinylSelectablePart[6] = 7;
        *((BYTE*)VinylSelectablePart + 0x1C) = 0;
        VinylSelectablePart[8] = 1;
        VinylSelectablePart[9] = 0;
        *((BYTE*)VinylSelectablePart + 40) = 0;
        InstalledVinyl = VinylSelectablePart;
    }
    else
    {
        InstalledVinyl = 0;
    }
    //if (CarCustomizeManager_IsPartInstalled((DWORD*)_gCarCustomizeManager, InstalledVinyl)) InstalledVinyl[8] = 16;

    StockVinylIconOption = (DWORD*)j_malloc(0x5C);
    //v16 = 0;
    if (StockVinylIconOption)
    {
        IconOption_Create(StockVinylIconOption, 0x21F3D114, 0x60A662F5, 0); // VINYL_STOCK, CO_RETURN_TO_STOCK
        StockVinylIconOption[19] = _nullString;
        StockVinylIconOption[21] = 1;
        StockVinylIconOption[20] = 0x4010401;
        StockVinylIconOption[0] = SetStockPartOption_vtable;
        StockVinylIconOption[22] = (DWORD)InstalledVinyl;
        *((BYTE*)StockVinylIconOption + 69) = 1;
    }
    else
    {
        StockVinylIconOption = 0;
    }
    //v16 = -1;

    // Stock vinyl
    IconScrollerMenu_AddOption(_CustomizeSub, StockVinylIconOption);

    // Check if the car has OEM vinyls
    bool HasNoCustomVinyls = CarConfigs[CarTypeID].Visual.VinylsCustom == 0;

    DWORD VinylBrandIconHash = -1;
    DWORD VinylBrandNameHash = -1;

    // Add the brands from ini
    for (int i = 0; i < VinylGroupsCount; i++)
    {
        if (i == 0)
        {
            if (HasNoCustomVinyls) continue;

            VinylBrandIconHash = CarConfigs[CarTypeID].Icons.VisualVinylsCustom;
            VinylBrandNameHash = CarConfigs[CarTypeID].Names.VisualVinylsCustom;

            if (VinylBrandIconHash == -1) VinylBrandIconHash = VinylGroups[i].TextureHash;
            if (VinylBrandNameHash == -1) VinylBrandNameHash = VinylGroups[i].StringHash;
        }
        else
        {
            VinylBrandIconHash = VinylGroups[i].TextureHash;
            VinylBrandNameHash = VinylGroups[i].StringHash;
        }

        CustomizeCategoryScreen_AddCustomOption(_CustomizeSub, *(char**)g_pCustomizePartsPkg, VinylBrandIconHash, VinylBrandNameHash, 0x402 + i);
    }

    AVinylPart[0] = SelectablePart_vtable;
    AVinylPart[3] = 0;
    AVinylPart[4] = 77; // VINYL_LAYER0
    AVinylPart[5] = 0;
    AVinylPart[6] = 7;
    *((BYTE*)AVinylPart + 0x1C) = 0;
    AVinylPart[8] = 1;
    AVinylPart[9] = 0;
    *((BYTE*)AVinylPart + 40) = 0;

    VinylShoppingCartItem = CarCustomizeManager_IsPartTypeInCart((DWORD*)_gCarCustomizeManager, AVinylPart); // ShoppingCartItem

    if (VinylShoppingCartItem)
    {
        SelectablePartInCart = *(DWORD*)(VinylShoppingCartItem + 12); // SelectablePart
        if (SelectablePartInCart)
        {
            TheVinylPart = *(DWORD*)(SelectablePartInCart + 12); // CarPart
            if (TheVinylPart)
                _CustomizeSub[107] = CustomizeSub_GetVinylGroupIndex(*((BYTE*)TheVinylPart + 5) & 0x1F) - HasNoCustomVinyls;
            else
                _CustomizeSub[107] = 1;
        }
    }
    CustomizationRecord = FEPlayerCarDB_GetCustomizationRecordByHandle((DWORD*)(*((DWORD*)FEDatabase + 4) + 0x414), *((BYTE*)FECarRecord + 16));
    CarType = FECarRecord_GetType(FECarRecord);
    InstalledPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, CarType, 77); // VINYL_LAYER0
    if (InstalledPart)
        _CustomizeSub[106] = CustomizeSub_GetVinylGroupIndex(*((BYTE*)InstalledPart + 5) & 0x1F) - HasNoCustomVinyls;
    else
        _CustomizeSub[106] = 1;
    PreviousMenu = _CustomizeSub[85];
    if (PreviousMenu == 0x803)
    {
        InitialPosition = _CustomizeSub[107];
        if (!InitialPosition)
        {
            if (_CustomizeSub[106])
                IconScrollerMenu_SetInitialOption(_CustomizeSub, _CustomizeSub[106]);
            else
                IconScrollerMenu_SetInitialOption(_CustomizeSub, 1);
            goto LABEL_26;
        }
    }
    else
    {
        InitialPosition = IconScroller_GetOptionIndexWithID(_CustomizeSub + 11, EDX_Unused, PreviousMenu);
    }
    if (*((BYTE*)_CustomizeSub + 297))
    {
        _CustomizeSub[68] = 0;
        *((BYTE*)_CustomizeSub + 284) = 0;
        *((BYTE*)_CustomizeSub + 281) = 1;
        *((BYTE*)_CustomizeSub + 282) = 0;
    }
    (*(void(__thiscall**)(DWORD*, unsigned int))(_CustomizeSub[11] + 64))(_CustomizeSub + 11, InitialPosition);
LABEL_26:
    result = _CustomizeSub[85];
    if (result >= 0x401 && result <= VinylGroupsCount + 0x402)
        _CustomizeSub[85] = 0x803;
    return result;
}

int __fastcall CustomizeSub_Setup(DWORD* _CustomizeSub, void* EDX_Unused)
{
    DWORD* CustomizeSub;
    unsigned int MenuID;

    CustomizeSub = _CustomizeSub;
    MenuID = *((DWORD*)_CustomizeSub + 84);

    switch (MenuID)
    {
        // Main Categories
    case 0x801:
        CustomizeSub_SetupParts(_CustomizeSub, EDX_Unused);
        break;
    case 0x802:
        CustomizeSub_SetupPerformance(_CustomizeSub, EDX_Unused);
        break;
    case 0x803:
        CustomizeSub_SetupVisual(_CustomizeSub, EDX_Unused);
        break;

        // Decal Slots
    case 0x501:
    case 0x502:
    case 0x503:
    case 0x504:
    case 0x505:
    case 0x506:
        CustomizeSub_SetupDecalPositions(_CustomizeSub, EDX_Unused);
        break;

        // Rims
    case 0x103:
        CustomizeSub_SetupRimBrands(_CustomizeSub, EDX_Unused);
        break;

        // Attachments
    case 0x10C:
        CustomizeSub_SetupAttachments(_CustomizeSub, EDX_Unused);
        break;

        // Vinyl Groups
    case 0x302:
        CustomizeSub_SetupVinylGroups(_CustomizeSub, EDX_Unused);
        break;

        // Decal Locations
    case 0x305:
        CustomizeSub_SetupDecalLocations(_CustomizeSub, EDX_Unused);
        break;
    }

    return CustomizeSub_RefreshHeader(_CustomizeSub);
}

void __fastcall CustomizeSub_NotificationMessage(DWORD* _CustomizeSub, void* EDX_Unused, DWORD MessageHash, DWORD* FEObject, DWORD param1, DWORD param2)
{
    DWORD* TheOption, * TheSelectablePart, * TheCarPart;
    unsigned int RimBrand;
    int OptionMenuID, CarSlotID;

    DWORD* _PartOption = (DWORD*)_CustomizeSub[14];
    short PartMenuID = _PartOption[20];
    int CurrentMenuID = _CustomizeSub[84];

    if (((CurrentMenuID == 0x801 && PartMenuID == 0x103) || (CurrentMenuID == 0x803 && (PartMenuID == 0x303 || PartMenuID == 0x314))) && MessageHash == 0xC407210)
    {
        // do nothing (A dialog is open, wait till there is a button press)
    }
    else CustomizeCategoryScreen_NotificationMessage(_CustomizeSub, MessageHash, FEObject, param1, param2);

    switch (MessageHash)
    {
    case 0xCF91AACD:
        CustomizeShoppingCart_ExitShoppingCart();
        break;

    case 0xC519BFC3: // PAD_BUTTON4
        if (/*(*((BYTE*)FEDatabase + 300) & 1) == 0 && !*(bool*)g_bTestCareerCustomization && */CurrentMenuID == 0x802) // Career Mode (canceled) & Performance Menu
        {
            DialogInterface_ShowTwoButtons((char const*)_CustomizeSub[4], "", 3, 0x70E01038, 0x417B25E4, 0x6820E23E, 0xB4EDEB6D, 0, 0x892CB612); // COMMON_YES, COMMON_NO, YesButton, NoButton, CD_MAX_PERFORMANCE_DLG
            (*(void(__thiscall**)(DWORD*))(*_CustomizeSub + 12))(_CustomizeSub); // RefreshHeader
        }
        break;

    case 0xB4EDEB6D: // NoButton
    LABEL_59:
        *((BYTE*)_CustomizeSub + 87) = 1;
        (*(void(__thiscall**)(DWORD*))(*_CustomizeSub + 12))(_CustomizeSub); // RefreshHeader
        break;

    case 0xC407210: // BUTTON_PRESSED
        if (PartMenuID >= 0x501 && PartMenuID <= 0x506)
            *(int*)CustomizeDecals_CurrentDecalLocation = PartMenuID;
        (*(void(__thiscall**)(DWORD*))(*_PartOption + 8))(_PartOption);// IsStockOption (dunno why called here)
        if (!(*(bool(__thiscall**)(DWORD*))(*_PartOption + 8))(_PartOption) // IsStockOption
            || (*(DWORD*)(_PartOption[22] + 32) & 0xF0) != 16
            || !_CustomizeSub[107])
        {
            goto LABEL_34;
        }

        if (PartMenuID == 0x401) // Stock vinyl
        {
            CarSlotID = 77; // VINYL_LAYER0
            for (int i = 0; i < 4; ++i)
            {
                TheSelectablePart = (DWORD*)CarCustomizeManager_IsPartTypeInCart_ID((DWORD*)_gCarCustomizeManager, i + 79);
                if (TheSelectablePart)
                    CarCustomizeManager_RemoveFromCart((DWORD*)_gCarCustomizeManager, TheSelectablePart);
            }
        }
        else
        {
            if (PartMenuID != 0x701)
            {
            LABEL_34:
                if (bStrICmp((char*)_CustomizeSub[4], *(char**)g_pCustomizeSubTopPkg)
                    && bStrICmp((char*)_CustomizeSub[4], *(char**)g_pCustomizeSubPkg))
                {
                    return;
                }
                CurrentMenuID = _CustomizeSub[84];
                if (CurrentMenuID != 0x103)
                {
                    if (CurrentMenuID == 0x302)
                    {
                        if (sub_50E780(_CustomizeSub + 11) == 1) // IconPanel_GetIndex??
                        {
                            TheSelectablePart = (DWORD*)CarCustomizeManager_IsPartTypeInCart_ID((DWORD*)_gCarCustomizeManager, 77);
                            if (TheSelectablePart)
                            {
                                TheCarPart = *(DWORD**)(TheSelectablePart[3] + 12);
                                if (TheCarPart)
                                    _CustomizeSub[107] = CustomizeSub_GetVinylGroupIndex(*((BYTE*)TheCarPart + 5) & 0x1F);
                                else
                                    _CustomizeSub[107] = 1;
                            }
                            TheCarPart = (DWORD*)CarCustomizeManager_GetInstalledCarPart((DWORD*)_gCarCustomizeManager, 77);
                            if (TheCarPart)
                            {
                                _CustomizeSub[106] = CustomizeSub_GetVinylGroupIndex(*((BYTE*)TheCarPart + 5) & 0x1F);
                            }
                            else
                            {
                                _CustomizeSub[106] = 1;
                            }
                            goto LABEL_59;
                        }
                    }
                    else if (CurrentMenuID == 0x803) // Visual
                    {
                        switch (PartMenuID)
                        {
                        case 0x303: // Rim paint
                            if (CarCustomizeManager_AreAllRimsStock((DWORD*)_gCarCustomizeManager, EDX_Unused)) // If both rims are stock
                            {
                                DialogInterface_ShowOneButton((char const*)_CustomizeSub[4], "", 1, 0x417B2601, 0xB4EDEB6D, 0xBDB19A9F); // COMMON_OK, NoButton, CUSTOMIZE_CANT_PAINT_STOCK_RIMS
                                return;
                            }
                            cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, (const char*)_PartOption[19], _PartOption[20], 0, 0);
                            break;
                            
                        case 0x314: // Tires
                            if (CarCustomizeManager_AreAllRimsStock((DWORD*)_gCarCustomizeManager, EDX_Unused)) // If both rims are stock
                            {
                                DialogInterface_ShowOneButton((char const*)_CustomizeSub[4], "", 1, 0x417B2601, 0xB4EDEB6D, 0x6EAD8563); // COMMON_OK, NoButton, CUSTOMIZE_CANT_CHANGE_TIRES_OF_STOCK_RIMS
                                return;
                            }

                            SwitchPackage:
                            cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, (const char*)_PartOption[19], _PartOption[20], 0, 0);
                            break;
                            
                        default:
                            return;
                        }
                    }
                    else if (CurrentMenuID == 0x801) // Parts
                    {
                        switch (PartMenuID)
                        {
                        case 0x103: // Rims
                            DialogInterface_ShowThreeButtons((char const*)_CustomizeSub[4], "", 3, 
                                bStringHash((char*)"CUSTOMIZE_FRONT_WHEEL"), 
                                bStringHash((char*)"CUSTOMIZE_REAR_WHEEL"), 
                                bStringHash((char*)"CUSTOMIZE_ALL_WHEELS"), 
                                bStringHash((char*)"CUSTOMIZE_FRONT_WHEEL"), 
                                bStringHash((char*)"CUSTOMIZE_REAR_WHEEL"), 
                                bStringHash((char*)"CUSTOMIZE_ALL_WHEELS"), 
                                0xB4EDEB6D,
                                2, 
                                bStringHash((char*)"CUSTOMIZE_CHOOSE_FRONT_REAR_WHEEL"));
                            return;
                            
                        default:
                            return;
                        }
                    }
                LABEL_44:
                    cFEng_QueuePackageMessage((int*)*(DWORD**)cFEng_mInstance, 0x587C018B, (const char*)_CustomizeSub[4], 0);
                    return;
                }
                if (!_PartOption || (*(int(__thiscall**)(DWORD*, DWORD*))(_CustomizeSub[11] + 36))(_CustomizeSub + 11, _PartOption) != 1) // IconPanel_GetOptionIndex
                {
                    goto LABEL_44;
                }
                TheSelectablePart = (DWORD*)CarCustomizeManager_IsPartTypeInCart_ID((DWORD*)_gCarCustomizeManager, RimsToCustomize < 0 ? 67 : 66); // FRONT_WHEEL
                if (TheSelectablePart)
                {
                    RimBrand = CarPart_GetAppliedAttributeUParam(*(DWORD**)(TheSelectablePart[3] + 12), 0xEBB03E66, 0);
                    _CustomizeSub[107] = CustomizeSub_GetRimBrandIndex(_CustomizeSub, EDX_Unused, RimBrand);
                }
                TheCarPart = (DWORD*)CarCustomizeManager_GetInstalledCarPart((DWORD*)_gCarCustomizeManager, RimsToCustomize < 0 ? 67 : 66); // FRONT_WHEEL
                if (TheCarPart)
                {
                    RimBrand = CarPart_GetAppliedAttributeUParam(TheCarPart, 0xEBB03E66, 0);
                    _CustomizeSub[106] = CustomizeSub_GetRimBrandIndex(_CustomizeSub, EDX_Unused, RimBrand);
                }
                goto LABEL_59;
            }
            CarSlotID = RimsToCustomize < 0 ? 67 : 66; // REAR/FRONT_WHEEL
        }
        TheSelectablePart = (DWORD*)CarCustomizeManager_IsPartTypeInCart_ID((DWORD*)_gCarCustomizeManager, CarSlotID);
        if (TheSelectablePart)
        {
            CarCustomizeManager_RemoveFromCart((DWORD*)_gCarCustomizeManager, TheSelectablePart);
            _CustomizeSub[107] = 0;
            (*(void(__thiscall**)(DWORD*))(*_CustomizeSub + 12))(_CustomizeSub); // RefreshHeader
        }
        goto LABEL_34;
    case 0x5A928018:
        if (_CustomizeSub[107])
        {
            TheOption = IconPanel_GetOption(_CustomizeSub + 11, _CustomizeSub[107]);
            if (TheOption)
            {
                OptionMenuID = TheOption[20];
                if (OptionMenuID == 0x103)
                {
                    CarSlotID = RimsToCustomize < 0 ? 67 : 66; // FRONT_WHEEL
                }
                else
                {
                    if (OptionMenuID != 0x302)
                        return;
                    CarSlotID = 77; // VINYL_LAYER0
                }
                if (!CarCustomizeManager_IsPartTypeInCart_ID((DWORD*)_gCarCustomizeManager, CarSlotID))
                {
                    _CustomizeSub[107] = 0;
                    (*(void(__thiscall**)(DWORD*))(*_CustomizeSub + 12))(_CustomizeSub); // RefreshHeader
                }
            }
        }
        break;
    
	case 0x6820E23E: // YesButton
        CarCustomizeManager_MaxOutPerformance((DWORD*)_gCarCustomizeManager);
        (*(void(__thiscall**)(DWORD*))(*_CustomizeSub + 12))(_CustomizeSub); // RefreshHeader
        break;

    case 0xCA1DB6BE: // CUSTOMIZE_FRONT_WHEEL
        RimsToCustomize = 1;
        goto SwitchPackage;
        break;

    case 0xCCB3C3DF: // CUSTOMIZE_REAR_WHEEL
        RimsToCustomize = -1;
        goto SwitchPackage;
        break;

    case 0xB3361A61: // CUSTOMIZE_ALL_WHEELS
        RimsToCustomize = 0;
        goto SwitchPackage;
        break;
    }
}