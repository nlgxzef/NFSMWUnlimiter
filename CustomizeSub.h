#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

char AttachmentString[24];
char CarTypeName[15];
char CarININame[MAX_PATH];
char RimBrandID[15];
char RimBrandString[64];
char RimBrandIcon[64];
void* _CustomizeCategoryScreen;

int __fastcall CustomizeSub_SetupParts(DWORD* _CustomizeSub, void* EDX_Unused)
{
    DWORD* _CustomizeCategoryScreen; // esi
    unsigned int InitialPosition; // eax
    
    _CustomizeCategoryScreen = _CustomizeSub;
    _CustomizeSub[108] = CustomizeIsInBackRoom() != 0 ? bStringHash("CO_BACKROOM_PARTS") : bStringHash("CO_PARTS");
    CustomizeSetInParts(1);
    _CustomizeCategoryScreen[83] = *(DWORD*)g_pCustomizeMainPkg;

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));
    //printf("NFSMWUnlimiter/ExtraCustomization: Entering parts menu, CarType: %s\n", CarTypeName);

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    if (CustomizeIsInBackRoom())
    {
        if (CarINI.ReadInteger("Parts", "BodyKits", GeneralINI.ReadInteger("Parts", "BodyKits", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("MARKER_ICON_PARTS_BODYKITS"),
            bStringHash("CO_BODY_KITS"),
            0x101);
        if (CarINI.ReadInteger("Parts", "Spoilers", GeneralINI.ReadInteger("Parts", "Spoilers", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSpoilerPkg,
            bStringHash("MARKER_ICON_PARTS_SPOILERS"),
            bStringHash("CO_SPOILERS"),
            0x102);
        if (CarINI.ReadInteger("Parts", "Rims", GeneralINI.ReadInteger("Parts", "Rims", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSubTopPkg,
            bStringHash("MARKER_ICON_PARTS_RIMS"),
            bStringHash("CO_RIMS"),
            0x103);
        if (CarINI.ReadInteger("Parts", "Hoods", GeneralINI.ReadInteger("Parts", "Hoods", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("MARKER_ICON_PARTS_HOODS"),
            bStringHash("CO_HOODS"),
            0x104);
        if (CarINI.ReadInteger("Parts", "RoofScoops", GeneralINI.ReadInteger("Parts", "RoofScoops", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("MARKER_ICON_PARTS_ROOFSCOOPS"),
            bStringHash("CO_ROOF_SCOOPS"),
            0x105);
        if (BETACompatibility && (CarINI.ReadInteger("Visual", "CustomGauges", GeneralINI.ReadInteger("Visual", "CustomGauges", 1)) != 0))
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeHudPkg,
            bStringHash("MARKER_ICON_VISUAL_HUD"),
            bStringHash("CO_CUSTOM_HUD"),
            0x307);
    }
    else
    {
        if (CarINI.ReadInteger("Parts", "BodyKits", GeneralINI.ReadInteger("Parts", "BodyKits", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("VISUAL_PART_BODY"),
            bStringHash("CO_BODY_KITS"),
            0x101);
        if (CarINI.ReadInteger("Parts", "Spoilers", GeneralINI.ReadInteger("Parts", "Spoilers", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSpoilerPkg,
            bStringHash("VISUAL_PART_SPOILER"),
            bStringHash("CO_SPOILERS"),
            0x102);
        if (CarINI.ReadInteger("Parts", "Rims", GeneralINI.ReadInteger("Parts", "Rims", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSubTopPkg,
            bStringHash("VISUAL_PART_RIMS"),
            bStringHash("CO_RIMS"),
            0x103);
        if (CarINI.ReadInteger("Parts", "Hoods", GeneralINI.ReadInteger("Parts", "Hoods", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("VISUAL_PART_HOOD"),
            bStringHash("CO_HOODS"),
            0x104);
        if (CarINI.ReadInteger("Parts", "RoofScoops", GeneralINI.ReadInteger("Parts", "RoofScoops", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("VISUAL_PART_ROOF_SCOOP"),
            bStringHash("CO_ROOF_SCOOPS"),
            0x105);
        // New options
        if (CarINI.ReadInteger("Parts", "Interior", GeneralINI.ReadInteger("Parts", "Interior", 0)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("VISUAL_PART_INTERIOR"),
            bStringHash("CO_INTERIOR"),
            0x106);
        if (CarINI.ReadInteger("Parts", "Roof", GeneralINI.ReadInteger("Parts", "Roof", 0)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("VISUAL_PART_ROOF"),
            bStringHash("CO_ROOF"),
            0x107);
        if (CarINI.ReadInteger("Parts", "Brakes", GeneralINI.ReadInteger("Parts", "Brakes", 0)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("VISUAL_PART_BRAKE"),
            bStringHash("CO_BRAKES"),
            0x108);
        if (CarINI.ReadInteger("Parts", "Headlights", GeneralINI.ReadInteger("Parts", "Headlights", 0)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("VISUAL_PART_HEAD_LIGHTS"),
            bStringHash("CO_HEADLIGHTS"),
            0x109);
        if (CarINI.ReadInteger("Parts", "Taillights", GeneralINI.ReadInteger("Parts", "Taillights", 0)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("VISUAL_PART_TAIL_LIGHTS"),
            bStringHash("CO_TAILLIGHTS"),
            0x10A);
        if (CarINI.ReadInteger("Parts", "Mirrors", GeneralINI.ReadInteger("Parts", "Mirrors", 0)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("VISUAL_PART_SIDE_MIRROR"),
            bStringHash("CO_SIDE_MIRROR"),
            0x10B);
        if (CarINI.ReadInteger("Parts", "Attachments", GeneralINI.ReadInteger("Parts", "Attachments", 0)) >= 1)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeSubTopPkg,
            bStringHash("VISUAL_PART_ATTACHMENT"),
            bStringHash("CO_ATTACHMENTS"),
            0x10C);
        if (BETACompatibility && (CarINI.ReadInteger("Visual", "CustomGauges", GeneralINI.ReadInteger("Visual", "CustomGauges", 1)) != 0))
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeHudPkg,
            bStringHash("VISUAL_PART_HUDS"),
            bStringHash("CO_CUSTOM_HUD"),
            0x307);
    }
    InitialPosition = _CustomizeCategoryScreen[85] & 0xFFFF00FF;
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

    _CustomizeCategoryScreen = _CustomizeSub;
    _CustomizeSub[108] = bStringHash("CO_ATTACHMENTS");
    _CustomizeCategoryScreen[83] = *(DWORD*)g_pCustomizeSubPkg;
    
    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));
    //printf("NFSMWUnlimiter/ExtraCustomization: Entering attachments menu, CarType: %s\n", CarTypeName);

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    int AttachmentCount = CarINI.ReadInteger("Parts", "Attachments", GeneralINI.ReadInteger("Parts", "Attachments", 0)) % 11;
    
    for (int i = 1; i <= AttachmentCount; i++)
    {
        sprintf(AttachmentString, "CO_ATTACHMENT_%d", i);
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePartsPkg,
            bStringHash("VISUAL_PART_ATTACHMENT"),
            bStringHash(AttachmentString),
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
        InitialPosition = (_CustomizeCategoryScreen[85] - 0xC) & 0xFFFF00FF;
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

void SetupRimBrandsHook(void* _CustomizeCategoryScreen)
{
    CIniReader RimBrandsINI("UnlimiterData\\_RimBrands.ini");

    int RimBrandsCount = RimBrandsINI.ReadInteger("RimBrands", "NumberOfRimBrands", -1);

    for (int i = 0; i <= RimBrandsCount; i++)
    {
        sprintf(RimBrandID, "Brand%d", i);
        sprintf(RimBrandIcon, RimBrandsINI.ReadString(RimBrandID, "Texture", ""));
        sprintf(RimBrandString, RimBrandsINI.ReadString(RimBrandID, "String", ""));
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizeRimsPkg,
            bStringHash(RimBrandIcon),
            bStringHash(RimBrandString),
            0x702 + i);
    }
}

void __declspec(naked) SetupRimBrandsCodeCave()
{
    _asm pushad;
    _asm mov _CustomizeCategoryScreen, esi;

    SetupRimBrandsHook(_CustomizeCategoryScreen);

    _asm popad;
    _asm push 0x7BC5D6;
    _asm retn;
}

int __fastcall CustomizeSub_SetupVisual(DWORD* _CustomizeSub, void *EDX_Unused)
{
    DWORD* _CustomizeCategoryScreen; // esi
    unsigned int InitialPosition; // eax

    _CustomizeCategoryScreen = _CustomizeSub;
    _CustomizeSub[108] = CustomizeIsInBackRoom() != 0 ? bStringHash("CO_BACKROOM_VISUAL") : bStringHash("CO_VISUAL");
    _CustomizeCategoryScreen[83] = *(DWORD*)g_pCustomizeMainPkg;

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));
    //printf("NFSMWUnlimiter/ExtraCustomization: Entering parts menu, CarType: %s\n", CarTypeName);

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    if (CustomizeIsInBackRoom())
    {
        if (CarINI.ReadInteger("Visual", "Paint", GeneralINI.ReadInteger("Visual", "Paint", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePaintPkg,
            bStringHash("MARKER_ICON_VISUAL_PAINT"),
            bStringHash("CO_PAINT"),
            0x301);
        if (!HPCCompatibility)
        {
            if (CarINI.ReadInteger("Visual", "Vinyls", GeneralINI.ReadInteger("Visual", "Vinyls", 1)) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    bStringHash("MARKER_ICON_VISUAL_VINYLS"),
                    bStringHash("CO_VINYLS"),
                    0x302);
            if (CarINI.ReadInteger("Visual", "Decals", GeneralINI.ReadInteger("Visual", "Decals", 1)) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    bStringHash("MARKER_ICON_VISUAL_DECALS"),
                    bStringHash("CO_DECALS"),
                    0x305);
            if (!BETACompatibility && (CarINI.ReadInteger("Visual", "CustomGauges", GeneralINI.ReadInteger("Visual", "CustomGauges", 1)) != 0))
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeHudPkg,
                    bStringHash("MARKER_ICON_VISUAL_HUD"),
                    bStringHash("CO_CUSTOM_HUD"),
                    0x307);
        }
    }
    else
    {
        if (CarINI.ReadInteger("Visual", "Paint", GeneralINI.ReadInteger("Visual", "Paint", 1)) != 0)
        CustomizeCategoryScreen_AddCustomOption(
            _CustomizeCategoryScreen,
            *(char**)g_pCustomizePaintPkg,
            bStringHash("PAINT_MOD_BASE"),
            bStringHash("CO_PAINT"),
            0x301);
        if (!HPCCompatibility)
        {
            if (CarINI.ReadInteger("Visual", "Vinyls", GeneralINI.ReadInteger("Visual", "Vinyls", 1)) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    bStringHash("VISUAL_PART_VINYL"),
                    bStringHash("CO_VINYLS"),
                    0x302);
            if (CarINI.ReadInteger("Visual", "RimPaint", GeneralINI.ReadInteger("Visual", "RimPaint", 1)) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePaintPkg,
                    bStringHash("PAINT_MOD_PART_RIMS"),
                    bStringHash("CO_RIM_PAINT"),
                    0x303);
            if (CarINI.ReadInteger("Visual", "WindowTint", GeneralINI.ReadInteger("Visual", "WindowTint", 1)) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    bStringHash("VISUAL_PART_WINDOW_TINTING"),
                    bStringHash("CO_WINDOW_TINT"),
                    0x304);
            if (CarINI.ReadInteger("Visual", "Decals", GeneralINI.ReadInteger("Visual", "Decals", 1)) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeSubTopPkg,
                    bStringHash("VISUAL_PART_DECALS"),
                    bStringHash("CO_DECALS"),
                    0x305);
            if (CarINI.ReadInteger("Visual", "Numbers", GeneralINI.ReadInteger("Visual", "Numbers", 1)) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    "Numbers.fng",
                    bStringHash("VISUAL_PART_NUMBERS"),
                    bStringHash("CO_NUMBERS"),
                    0x306);
            if (!BETACompatibility && (CarINI.ReadInteger("Visual", "CustomGauges", GeneralINI.ReadInteger("Visual", "CustomGauges", 1)) != 0))
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizeHudPkg,
                    bStringHash("VISUAL_PART_HUDS"),
                    bStringHash("CO_CUSTOM_HUD"),
                    0x307);
            if (CarINI.ReadInteger("Visual", "Driver", GeneralINI.ReadInteger("Visual", "Driver", 0)) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    bStringHash("VISUAL_PART_DRIVER"),
                    bStringHash("CO_DRIVER"),
                    0x308);
            if (CarINI.ReadInteger("Visual", "LicensePlate", GeneralINI.ReadInteger("Visual", "LicensePlate", 0)) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    bStringHash("VISUAL_PART_LICENSE_PLATE"),
                    bStringHash("CO_LICENSE_PLATE"),
                    0x309);
            if (CarINI.ReadInteger("Visual", "Tires", GeneralINI.ReadInteger("Visual", "Tires", 0)) != 0)
                CustomizeCategoryScreen_AddCustomOption(
                    _CustomizeCategoryScreen,
                    *(char**)g_pCustomizePartsPkg,
                    bStringHash("VISUAL_PART_TIRE"),
                    bStringHash("CO_TIRES"),
                    0x314);
        }
    }
    InitialPosition = _CustomizeCategoryScreen[85] & 0xFFFF00FF;
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

int __fastcall CustomizeSub_GetRimBrandIndex(DWORD* CustomizeSub, void* EDX_Unused, unsigned int WheelManufacturerHash)
{
    CIniReader RimBrandsINI("UnlimiterData\\_RimBrands.ini");

    int RimBrandsCount = RimBrandsINI.ReadInteger("RimBrands", "NumberOfRimBrands", -1);

    for (int i = 0; i <= RimBrandsCount; i++)
    {
        sprintf(RimBrandID, "Brand%d", i);
        if (bStringHash(RimBrandsINI.ReadString(RimBrandID, "BrandName", "")) == WheelManufacturerHash) return i + 2;
    }

    return 1;
}

void __fastcall CustomizeSub_SetupDecalLocations(DWORD* CustomizeSub, void* EDX_Unused)
{
    DWORD PreviousMenu; // eax
    unsigned int InitialPosition; // eax

    CustomizeSub[108] = bStringHash("CO_DECAL_LOCATION");
    CustomizeSub[83] = *(DWORD*)g_pCustomizeSubPkg;

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);
    sprintf(CarTypeName, GetCarTypeName(CarTypeID));

    // Read Part Options for the car
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    if (CarINI.ReadInteger("Visual", "DecalsWindshield", GeneralINI.ReadInteger("Visual", "DecalsWindshield", 1)) != 0) CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg, bStringHash("DECAL_ZONE_WINDSHIELD"), bStringHash("CO_DECAL_WINDSHIELD"), 0x501);
    if (CarINI.ReadInteger("Visual", "DecalsRearWindow", GeneralINI.ReadInteger("Visual", "DecalsRearWindow", 1)) != 0) CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg, bStringHash("DECAL_ZONE_REARWINDOW"), bStringHash("CO_DECAL_REAR_WINDOW"), 0x502);
    if (CarINI.ReadInteger("Visual", "DecalsLeftDoor", GeneralINI.ReadInteger("Visual", "DecalsLeftDoor", 1)) != 0) CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg, bStringHash("DECAL_ZONE_LEFTDOOR"), bStringHash("CO_DECAL_LEFT_DOOR"), 0x503);
    if (CarINI.ReadInteger("Visual", "DecalsRightDoor", GeneralINI.ReadInteger("Visual", "DecalsRightDoor", 1)) != 0) CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg, bStringHash("DECAL_ZONE_RIGHTDOOR"), bStringHash("CO_DECAL_RIGHT_DOOR"), 0x504);
    if (CarINI.ReadInteger("Visual", "DecalsLeftQuarter", GeneralINI.ReadInteger("Visual", "DecalsLeftQuarter", 1)) != 0) CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg, bStringHash("DECAL_ZONE_LEFTPANEL"), bStringHash("CO_DECAL_LEFT_QUARTER"), 0x505);
    if (CarINI.ReadInteger("Visual", "DecalsRightQuarter", GeneralINI.ReadInteger("Visual", "DecalsRightQuarter", 1)) != 0) CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeSubTopPkg, bStringHash("DECAL_ZONE_RIGHTPANEL"), bStringHash("CO_DECAL_RIGHT_QUARTER"), 0x506);
    
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
        InitialPosition = PreviousMenu & 0xFFFF00FF;
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
    char DecalMenuTexture[64];
    char DecalMenuString[64];

    CustomizeSub[108] = bStringHash("CO_DECAL_POSITION");
    CustomizeSub[83] = *(DWORD*)g_pCustomizeSubTopPkg;

    // Get car and customization record
    DWORD* FEDatabase = *(DWORD**)_FEDatabase;
    DWORD* FECarRecord = *(DWORD**)_FECarRecord;
    DWORD* CustomizationRecord = FEPlayerCarDB_GetCustomizationRecordByHandle((DWORD*)(*((DWORD*)FEDatabase + 4) + 0x414),*((BYTE*)FECarRecord + 16));

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
            sprintf(DecalMenuString, "CO_DECAL_SLOT_%d", i);
            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg, bStringHash("DECAL_ZONE_WINDSHIELD"), bStringHash(DecalMenuString), 0x600 + i);
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
            sprintf(DecalMenuString, "CO_DECAL_SLOT_%d", i);
            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg, bStringHash("DECAL_ZONE_REARWINDOW"), bStringHash(DecalMenuString), 0x600 + i);
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
            sprintf(DecalMenuTexture, "DECAL_LEFTDOOR_SLOT%d", i);
            sprintf(DecalMenuString, "CO_DECAL_SLOT_%d", i);
            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg, bStringHash(DecalMenuTexture), bStringHash(DecalMenuString), 0x600 + i);
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
            sprintf(DecalMenuTexture, "DECAL_RIGHTDOOR_SLOT%d", i);
            sprintf(DecalMenuString, "CO_DECAL_SLOT_%d", i);
            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg, bStringHash(DecalMenuTexture), bStringHash(DecalMenuString), 0x600 + i);
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
            sprintf(DecalMenuString, "CO_DECAL_SLOT_%d", i);
            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg, bStringHash("DECAL_ZONE_LEFTPANEL"), bStringHash(DecalMenuString), 0x600 + i);
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
            sprintf(DecalMenuString, "CO_DECAL_SLOT_%d", i);
            CustomizeCategoryScreen_AddCustomOption(CustomizeSub, *(char**)g_pCustomizeDecalsPkg, bStringHash("DECAL_ZONE_RIGHTPANEL"), bStringHash(DecalMenuString), 0x600 + i);
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
        InitialPosition = PreviousMenu & 0xFFFF00FF;
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
        CustomizeSub_SetupPerformance(_CustomizeSub);
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
        CustomizeSub_SetupRimBrands(_CustomizeSub);
        break;

        // Attachments
    case 0x10C:
        CustomizeSub_SetupAttachments(_CustomizeSub, EDX_Unused);
        break;

        // Vinyl Groups
    case 0x302:
        CustomizeSub_SetupVinylGroups(_CustomizeSub);
        break;

        // Decal Locations
    case 0x305:
        CustomizeSub_SetupDecalLocations(_CustomizeSub, EDX_Unused);
        break;
    }

    return CustomizeSub_RefreshHeader(_CustomizeSub);
}