#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"
#include "CarCustomizeManager.h"
#include "Helpers.h"
#include "IconScroller.h"

// TODO: Reimplement the spoiler and vinyl categories functions to support v4+ custom icons and names

int __fastcall CustomizeSub_SetupParts(DWORD* _CustomizeSub, void* EDX_Unused)
{
    DWORD* _CustomizeCategoryScreen; // esi
    unsigned int InitialPosition; // eax
    
    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    _CustomizeCategoryScreen = _CustomizeSub;
    _CustomizeSub[108] = CustomizeIsInBackRoom() != 0
        ? GetCarTextOptionHash(CarINI, GeneralINI, "Names", "BackroomParts", "CO_BACKROOM_PARTS")
        : GetCarTextOptionHash(CarINI, GeneralINI, "Names", "Parts", "CO_PARTS");
    CustomizeSetInParts(1);
    _CustomizeCategoryScreen[83] = *(DWORD*)g_pCustomizeMainPkg;

    if (CustomizeIsInBackRoom())
    {
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "BodyKits", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPartsBodyKits", "MARKER_ICON_PARTS_BODYKITS"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsBodyKits", "CO_BODY_KITS"),
            0x101);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Spoilers", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSpoilerPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPartsSpoilers", "MARKER_ICON_PARTS_SPOILERS"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsSpoilers", "CO_SPOILERS"),
            0x102);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Rims", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSubTopPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPartsRims", "MARKER_ICON_PARTS_RIMS"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsRims", "CO_RIMS"),
            0x103);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Hoods", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPartsHoods", "MARKER_ICON_PARTS_HOODS"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsHoods", "CO_HOODS"),
            0x104);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "RoofScoops", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPartsRoofScoops", "MARKER_ICON_PARTS_ROOFSCOOPS"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsRoofScoops", "CO_ROOF_SCOOPS"),
            0x105);
        if (BETACompatibility && (GetCarIntOption(CarINI, GeneralINI, "Visual", "CustomGauges", 1) != 0))
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeHudPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomVisualCustomGauges", "MARKER_ICON_VISUAL_HUD"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualCustomGauges", "CO_CUSTOM_HUD"),
            0x307);
    }
    else
    {
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "BodyKits", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsBodyKits", "VISUAL_PART_BODY"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsBodyKits", "CO_BODY_KITS"),
            0x101);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Spoilers", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSpoilerPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsSpoilers", "VISUAL_PART_SPOILER"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsSpoilers", "CO_SPOILERS"),
            0x102);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Rims", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSubTopPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsRims", "VISUAL_PART_RIMS"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsRims", "CO_RIMS"),
            0x103);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Hoods", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsHoods", "VISUAL_PART_HOOD"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsHoods", "CO_HOODS"),
            0x104);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "RoofScoops", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsRoofScoops", "VISUAL_PART_ROOF_SCOOP"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsRoofScoops", "CO_ROOF_SCOOPS"),
            0x105);
        // New options
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Interior", 0) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsInterior", "VISUAL_PART_INTERIOR"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsInterior", "CO_INTERIOR"),
            0x106);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Roof", 0) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsRoof", "VISUAL_PART_ROOF"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsRoof", "CO_ROOF"),
            0x107);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Brakes", 0) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsBrakes", "VISUAL_PART_BRAKE"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsBrakes", "CO_BRAKES"),
            0x108);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Headlights", 0) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsHeadlights", "VISUAL_PART_HEAD_LIGHTS"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsHeadlights", "CO_HEADLIGHTS"),
            0x109);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Taillights", 0) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsTaillights", "VISUAL_PART_TAIL_LIGHTS"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsTaillights", "CO_TAILLIGHTS"),
            0x10A);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Mirrors", 0) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsMirrors", "VISUAL_PART_SIDE_MIRROR"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsMirrors", "CO_SIDE_MIRROR"),
            0x10B);
        if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Attachments", 0) >= 1)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSubTopPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsAttachments", "VISUAL_PART_ATTACHMENT"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachments", "CO_ATTACHMENTS"),
            0x10C);
        if (BETACompatibility && (GetCarIntOption(CarINI, GeneralINI, "Visual", "CustomGauges", 1) != 0))
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeHudPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualCustomGauges", "VISUAL_PART_HUDS"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualCustomGauges", "CO_CUSTOM_HUD"),
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
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));
    //printf("NFSMWUnlimiter/ExtraCustomization: Entering attachments menu, CarType: %s\n", CarTypeName);

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    _CustomizeCategoryScreen = _CustomizeSub;
    _CustomizeSub[108] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachments", "CO_ATTACHMENTS");
    _CustomizeCategoryScreen[83] = *(DWORD*)g_pCustomizeSubPkg;
    
    int AttachmentCount = GetCarIntOption(CarINI, GeneralINI, "Parts", "Attachments", 0) % 11;
    
    for (int i = 1; i <= AttachmentCount; i++)
    {
        sprintf(AttachmentString, "PartsAttachment%d", i-1);
        sprintf(AttachmentDefaultString, "CO_ATTACHMENT_%d", i);

        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", AttachmentString, "VISUAL_PART_ATTACHMENT"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", AttachmentString, AttachmentDefaultString),
            0x10C + i);
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
    CIniReader RimBrandsINI("UnlimiterData\\_RimBrands.ini");
    int RimBrandsCount = RimBrandsINI.ReadInteger("RimBrands", "NumberOfRimBrands", DefaultRimBrandCount);

    for (int i = 0; i <= RimBrandsCount; i++)
    {
        sprintf(RimBrandID, "Brand%d", i);
        if (bStringHash(RimBrandsINI.ReadString(RimBrandID, "BrandName", GetDefaultRimBrandName(i))) == WheelManufacturerHash) return i + 2;
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

    CIniReader RimBrandsINI("UnlimiterData\\_RimBrands.ini");
    int RimBrandsCount = RimBrandsINI.ReadInteger("RimBrands", "NumberOfRimBrands", DefaultRimBrandCount);

    DWORD* FEDatabase = *(DWORD**)_FEDatabase;

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    _CustomizeSub[108] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsRimsBrand", "CO_RIM_BRAND");
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
    bool HasNoCustomRims = GetCarIntOption(CarINI, GeneralINI, "Parts", "RimsCustom", 0) == 0;

    // Add the brands from ini
    for (int i = 0; i <= RimBrandsCount; i++)
    {
        if (i == 0 && HasNoCustomRims) continue;
        sprintf(RimBrandID, "Brand%d", i);
        sprintf(RimBrandIcon, RimBrandsINI.ReadString(RimBrandID, "Texture", GetDefaultRimBrandTexture(i)));
        sprintf(RimBrandString, RimBrandsINI.ReadString(RimBrandID, "String", GetDefaultRimBrandString(i)));
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeSub,
            *(char**)g_pCustomizeRimsPkg,
            bStringHash(RimBrandIcon),
            bStringHash(RimBrandString),
            0x702 + i);
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
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    _CustomizeCategoryScreen = _CustomizeSub;
    _CustomizeSub[108] = CustomizeIsInBackRoom() != 0
        ? GetCarTextOptionHash(CarINI, GeneralINI, "Names", "BackroomPerformance", "CO_BACKROOM_PERFORMANCE")
        : GetCarTextOptionHash(CarINI, GeneralINI, "Names", "Performance", "CO_PERFORMANCE");

    _CustomizeSub[83] = *(DWORD*)g_pCustomizeMainPkg;
    CustomizeSetInPerformance(1);

    if (CustomizeIsInBackRoom())
    {
        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Engine", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPerformanceEngine", "MARKER_ICON_PERFORMANCE_ENGINE"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceEngine", "CO_ENGINE"),
                0x201);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Transmission", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPerformanceTransmission", "MARKER_ICON_PERFORMANCE_TRANSMISSION"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceTransmission", "CO_TRANSMISSION"),
                0x202);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Chassis", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPerformanceChassis", "MARKER_ICON_CHASSIS"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceChassis", "CO_SUSPENSION"),
                0x203);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Nitrous", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPerformanceNitrous", "MARKER_ICON_PERFORMANCE_N2O"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceNitrous", "CO_NITROUS"),
                0x204);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Tires", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPerformanceTires", "MARKER_ICON_TIRES"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceTires", "CO_TIRES"),
                0x205);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Brakes", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPerformanceBrakes", "MARKER_ICON_PERFORMANCE_BRAKES"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceBrakes", "CO_BRAKES"),
                0x206);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Induction", 1) != 0)
        {
            if (CarCustomizeManager_IsTurbo((DWORD*)_gCarCustomizeManager))
            {
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeSub,
                    *(char**)g_pCustomizePerfPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPerformanceTurbo", "MARKER_ICON_PERFORMANCE_TURBO"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceTurbo", "CO_TURBO"),
                    0x207);
            }
            else
            {
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeSub,
                    *(char**)g_pCustomizePerfPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPerformanceSupercharger", "MARKER_ICON_PERFORMANCE_SUPERCHARGER"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceSupercharger", "CO_SUPERCHARGER"),
                    0x207);
            }
        }
    }

    else
    {
        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Engine", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceEngine", "PERFORMANCE_ENGINE"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceEngine", "CO_ENGINE"),
                0x201);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Transmission", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceTransmission", "PERFORMANCE_TRANSMISSION"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceTransmission", "CO_TRANSMISSION"),
                0x202);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Chassis", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceChassis", "PERFORMANCE_SUSPENSION"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceChassis", "CO_SUSPENSION"),
                0x203);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Nitrous", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceNitrous", "PERFORMANCE_NITROUS"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceNitrous", "CO_NITROUS"),
                0x204);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Tires", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceTires", "PERFORMANCE_TIRES"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceTires", "CO_TIRES"),
                0x205);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Brakes", 1) != 0)
            CustomizeCategoryScreen_AddCustomOption(
                _CustomizeSub,
                *(char**)g_pCustomizePerfPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceBrakes", "PERFORMANCE_BRAKES"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceBrakes", "CO_BRAKES"),
                0x206);

        if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Induction", 1) != 0)
        {
            if (CarCustomizeManager_IsTurbo((DWORD*)_gCarCustomizeManager))
            {
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeSub,
                    *(char**)g_pCustomizePerfPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceTurbo", "PERFORMANCE_TURBO"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceTurbo", "CO_TURBO"),
                    0x207);
            }
            else
            {
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeSub,
                    *(char**)g_pCustomizePerfPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PerformanceSupercharger", "PERFORMANCE_SUPERCHARGER"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PerformanceSupercharger", "CO_SUPERCHARGER"),
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
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    _CustomizeCategoryScreen = _CustomizeSub;
    _CustomizeSub[108] = CustomizeIsInBackRoom() != 0 
        ? GetCarTextOptionHash(CarINI, GeneralINI, "Names", "BackroomVisual", "CO_BACKROOM_VISUAL")
        : GetCarTextOptionHash(CarINI, GeneralINI, "Names", "Visual", "CO_VISUAL");

    _CustomizeCategoryScreen[83] = *(DWORD*)g_pCustomizeMainPkg;

    if (CustomizeIsInBackRoom())
    {
        if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Paint", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePaintPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomVisualPaint", "MARKER_ICON_VISUAL_PAINT"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualPaint", "CO_PAINT"),
            0x301);
        if (!HPCCompatibility)
        {
            if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Vinyls", 1) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomVisualVinyls", "MARKER_ICON_VISUAL_VINYLS"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualVinyls", "CO_VINYLS"),
                    0x302);
            if ((GetCarIntOption(CarINI, GeneralINI, "Visual", "Decals", 1) != 0) && !IsMenuEmpty_Decals(CarINI, GeneralINI))
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomVisualDecals", "MARKER_ICON_VISUAL_DECALS"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDecals", "CO_DECALS"),
                    0x305);
            if (!BETACompatibility && (GetCarIntOption(CarINI, GeneralINI, "Visual", "CustomGauges", 1) != 0))
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeHudPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomVisualCustomGauges", "MARKER_ICON_VISUAL_HUD"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualCustomGauges", "CO_CUSTOM_HUD"),
                    0x307);
        }
    }
    else
    {
        if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Paint", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePaintPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualPaint", "PAINT_MOD_BASE"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualPaint", "CO_PAINT"),
            0x301);
        if (!HPCCompatibility)
        {
            if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Vinyls", 1) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualVinyls", "VISUAL_PART_VINYL"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualVinyls", "CO_VINYLS"),
                    0x302);
            if (GetCarIntOption(CarINI, GeneralINI, "Visual", "RimPaint", 1) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePaintPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualRimPaint", "PAINT_MOD_PART_RIMS"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualRimPaint", "CO_RIM_PAINT"),
                    0x303);
            if (GetCarIntOption(CarINI, GeneralINI, "Visual", "WindowTint", 1) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualWindowTint", "VISUAL_PART_WINDOW_TINTING"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualWindowTint", "CO_WINDOW_TINT"),
                    0x304);
            if ((GetCarIntOption(CarINI, GeneralINI, "Visual", "Decals", 1) != 0) && !IsMenuEmpty_Decals(CarINI, GeneralINI))
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualDecals", "VISUAL_PART_DECALS"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDecals", "CO_DECALS"),
                    0x305);
            if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Numbers", 1) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    "Numbers.fng",
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualNumbers", "VISUAL_PART_NUMBERS"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualNumbers", "CO_NUMBERS"),
                    0x306);
            if (!BETACompatibility && (GetCarIntOption(CarINI, GeneralINI, "Visual", "CustomGauges", 1) != 0))
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeHudPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualCustomGauges", "VISUAL_PART_HUDS"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualCustomGauges", "CO_CUSTOM_HUD"),
                    0x307);
            if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Driver", 0) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualDriver", "VISUAL_PART_DRIVER"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDriver", "CO_DRIVER"),
                    0x308);
            if (GetCarIntOption(CarINI, GeneralINI, "Visual", "LicensePlate", 0) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualLicensePlate", "VISUAL_PART_LICENSE_PLATE"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualLicensePlate", "CO_LICENSE_PLATE"),
                    0x309);
            if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Tires", 0) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualTires", "VISUAL_PART_TIRE"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualTires", "CO_TIRES"),
                    0x314);
            if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Neon", 0) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualNeon", "VISUAL_PART_NEON"),
                    GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualNeon", "CO_NEON"),
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
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    CustomizeSub[108] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDecalsLocation", "CO_DECAL_LOCATION");
    CustomizeSub[83] = *(DWORD*)g_pCustomizeSubPkg;

    if (GetCarIntOption(CarINI, GeneralINI, "Visual", "DecalsWindshield", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualDecalsWindshield", "DECAL_ZONE_WINDSHIELD"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDecalsWindshield", "CO_DECAL_WINDSHIELD"),
            0x501);
    if (GetCarIntOption(CarINI, GeneralINI, "Visual", "DecalsRearWindow", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualDecalsRearWindow", "DECAL_ZONE_REARWINDOW"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDecalsRearWindow", "CO_DECAL_REAR_WINDOW"),
            0x502);
    if (GetCarIntOption(CarINI, GeneralINI, "Visual", "DecalsLeftDoor", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualDecalsLeftDoor", "DECAL_ZONE_LEFTDOOR"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDecalsLeftDoor", "CO_DECAL_LEFT_DOOR"),
            0x503);
    if (GetCarIntOption(CarINI, GeneralINI, "Visual", "DecalsRightDoor", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualDecalsRightDoor", "DECAL_ZONE_RIGHTDOOR"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDecalsRightDoor", "CO_DECAL_RIGHT_DOOR"),
            0x504);
    if (GetCarIntOption(CarINI, GeneralINI, "Visual", "DecalsLeftQuarter", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualDecalsLeftQuarter", "DECAL_ZONE_LEFTPANEL"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDecalsLeftQuarter", "CO_DECAL_LEFT_QUARTER"),
            0x505);
    if (GetCarIntOption(CarINI, GeneralINI, "Visual", "DecalsRightQuarter", 1) != 0)
        CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg,
            GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualDecalsRightQuarter", "DECAL_ZONE_RIGHTPANEL"),
            GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDecalsRightQuarter", "CO_DECAL_RIGHT_QUARTER"),
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

    // Get car and customization record
    DWORD* FEDatabase = *(DWORD**)_FEDatabase;
    DWORD* FECarRecord = *(DWORD**)_FECarRecord;
    DWORD* CustomizationRecord = FEPlayerCarDB_GetCustomizationRecordByHandle((DWORD*)(*((DWORD*)FEDatabase + 4) + 0x414), *((BYTE*)FECarRecord + 16));

    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    CustomizeSub[108] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDecalsPosition", "CO_DECAL_POSITION");
    CustomizeSub[83] = *(DWORD*)g_pCustomizeSubTopPkg;
    
    switch (CustomizeSub[84])
    {
    case 0x501: // Windshield
        // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 70); // DECAL_FRONT_WINDOW_WIDE_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash("NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 8) NumDecals = 1;
        }
        else NumDecals = 1;

        // Create menu options accordingly
        for (int i = 1; i <= NumDecals; i++)
        {
            sprintf(DecalMenuString, "VisualDecalsWindshield%d", i);
            sprintf(DecalMenuDefaultString, "CO_DECAL_SLOT_%d", i);

            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", DecalMenuString, "DECAL_ZONE_WINDSHIELD"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", DecalMenuString, DecalMenuDefaultString),
                0x600 + i);
        }

        break;
    case 0x502: // Rear Window
        // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 71); // DECAL_REAR_WINDOW_WIDE_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash("NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 8) NumDecals = 1;
        }
        else NumDecals = 1;

        // Create menu options accordingly
        for (int i = 1; i <= NumDecals; i++)
        {
            sprintf(DecalMenuString, "VisualDecalsRearWindow%d", i);
            sprintf(DecalMenuDefaultString, "CO_DECAL_SLOT_%d", i);

            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", DecalMenuString, "DECAL_ZONE_REARWINDOW"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", DecalMenuString, DecalMenuDefaultString),
                0x600 + i);
        }

        break;
    case 0x503: // Left Door
    // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 72); // DECAL_LEFT_DOOR_RECT_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash("NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 6) NumDecals = 6;
        }
        else NumDecals = 6;

        // Create menu options accordingly
        for (int i = 1; i <= NumDecals; i++)
        {
            sprintf(DecalMenuString, "VisualDecalsLeftDoor%d", i);
            sprintf(DecalMenuDefaultTexture, "DECAL_LEFTDOOR_SLOT%d", i);
            sprintf(DecalMenuDefaultString, "CO_DECAL_SLOT_%d", i);

            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", DecalMenuString, DecalMenuDefaultTexture),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", DecalMenuString, DecalMenuDefaultString),
                0x600 + i);
        }

        break;
    case 0x504: // Left Door
    // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 73); // DECAL_RIGHT_DOOR_RECT_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash("NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 6) NumDecals = 6;
        }
        else NumDecals = 6;

        // Create menu options accordingly
        for (int i = 1; i <= NumDecals; i++)
        {
            sprintf(DecalMenuString, "VisualDecalsRightDoor%d", i);
            sprintf(DecalMenuDefaultTexture, "DECAL_RIGHTDOOR_SLOT%d", i);
            sprintf(DecalMenuDefaultString, "CO_DECAL_SLOT_%d", i);

            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", DecalMenuString, DecalMenuDefaultTexture),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", DecalMenuString, DecalMenuDefaultString),
                0x600 + i);
        }

        break;
    case 0x505: // Left Quarter
    // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 74); // DECAL_LEFT_QUARTER_RECT_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash("NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 8) NumDecals = 1;
        }
        else NumDecals = 1;

        // Create menu options accordingly
        for (int i = 1; i <= NumDecals; i++)
        {
            sprintf(DecalMenuString, "VisualDecalsLeftQuarter%d", i);
            sprintf(DecalMenuDefaultString, "CO_DECAL_SLOT_%d", i);

            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", DecalMenuString, "DECAL_ZONE_LEFTPANEL"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", DecalMenuString, DecalMenuDefaultString),
                0x600 + i);
        }

        break;
    case 0x506: // Right Quarter
        // Get decal part
        DecalPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(FECarRecord), 75); // DECAL_RIGHT_QUARTER_RECT_MEDIUM

        // look for the NUM_DECALS attribute
        if (DecalPart)
        {
            NumDecals = CarPart_GetAppliedAttributeIParam(DecalPart, bStringHash("NUM_DECALS"), 0);
            if (NumDecals <= 0 || NumDecals >= 8) NumDecals = 1;
        }
        else NumDecals = 1;

        // Create menu options accordingly
        for (int i = 1; i <= NumDecals; i++)
        {
            sprintf(DecalMenuString, "VisualDecalsRightQuarter%d", i);
            sprintf(DecalMenuDefaultString, "CO_DECAL_SLOT_%d", i);

            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg,
                GetCarTextOptionHash(CarINI, GeneralINI, "Icons", DecalMenuString, "DECAL_ZONE_RIGHTPANEL"),
                GetCarTextOptionHash(CarINI, GeneralINI, "Names", DecalMenuString, DecalMenuDefaultString),
                0x600 + i);
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
    CIniReader VinylGroupsINI("UnlimiterData\\_VinylGroups.ini");
    int VinylGroupsCount = VinylGroupsINI.ReadInteger("VinylGroups", "NumberOfVinylGroups", DefaultVinylGroupCount);

    for (int i = 0; i <= VinylGroupsCount; i++)
    {
        sprintf(VinylBrandID, "Group%d", i);
        if (VinylGroupsINI.ReadInteger(VinylBrandID, "Index", GetDefaultVinylGroupIndex(i)) == group) return i + 2;
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

    CIniReader VinylGroupsINI("UnlimiterData\\_VinylGroups.ini");
    int VinylGroupsCount = VinylGroupsINI.ReadInteger("VinylGroups", "NumberOfVinylGroups", DefaultVinylGroupCount);

    DWORD* FEDatabase = *(DWORD**)_FEDatabase;

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    _CustomizeSub[108] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualVinylsGroup", "CO_VINYL_STYLE");
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
    bool HasNoCustomVinyls = GetCarIntOption(CarINI, GeneralINI, "Visual", "VinylsCustom", 0) == 0;

    // Add the brands from ini
    for (int i = 0; i <= VinylGroupsCount; i++)
    {
        if (i == 0 && HasNoCustomVinyls) continue;
        sprintf(VinylBrandID, "Group%d", i);
        sprintf(VinylBrandIcon, VinylGroupsINI.ReadString(VinylBrandID, "Texture", GetDefaultVinylGroupTexture(i)));
        sprintf(VinylBrandString, VinylGroupsINI.ReadString(VinylBrandID, "String", GetDefaultVinylGroupString(i)));
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeSub,
            *(char**)g_pCustomizePartsPkg,
            bStringHash(VinylBrandIcon),
            bStringHash(VinylBrandString),
            0x402 + i);
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
            for (int i = 0; i < 3; ++i)
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
                                bStringHash("CUSTOMIZE_FRONT_WHEEL"), 
                                bStringHash("CUSTOMIZE_REAR_WHEEL"), 
                                bStringHash("CUSTOMIZE_ALL_WHEELS"), 
                                bStringHash("CUSTOMIZE_FRONT_WHEEL"), 
                                bStringHash("CUSTOMIZE_REAR_WHEEL"), 
                                bStringHash("CUSTOMIZE_ALL_WHEELS"), 
                                0xB4EDEB6D,
                                2, 
                                bStringHash("CUSTOMIZE_CHOOSE_FRONT_REAR_WHEEL"));
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