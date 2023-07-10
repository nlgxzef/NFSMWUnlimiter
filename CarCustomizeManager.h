#pragma once

#include "stdio.h"
#include "UnlockSystem.h"
#include "InGameFunctions.h"
#include "Helpers.h"

bool __fastcall CarCustomizeManager_IsCastrolCar(DWORD* CarCustomizeManager, int edx_unused)
{
    bool result; // al

    int CarType; // eax
    CarType = FECarRecord_GetType(*(void**)_FECarRecord);

    // Get config files
    sprintf(CarTypeName, GetCarTypeName(CarType));
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    int EngineType = GetCarIntOption(CarINI, GeneralINI, "Main", "EngineType", -1);

    if ((EngineType == -1 && CarType == 52) || EngineType == 1) // FORDGT
        result = EasterEggs_IsEasterEggUnlocked((DWORD*)gEasterEggs, 4);
    else
        result = 0;
    return result;
}

bool __fastcall CarCustomizeManager_IsRotaryCar(DWORD* CarCustomizeManager, int edx_unused)
{
    int CarType; // eax
    CarType = FECarRecord_GetType(*(void**)_FECarRecord);

    // Get config files
    sprintf(CarTypeName, GetCarTypeName(CarType));
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    int EngineType = GetCarIntOption(CarINI, GeneralINI, "Main", "EngineType", -1);

    if (EngineType == -1) return CarType == 5 || CarType == 56; // RX7, RX8
    else return EngineType == 2;
}

int __fastcall CarCustomizeManager_GetPartPrice(DWORD* _CarCustomizeManager, void* EDX_Unused, DWORD* TheSelectablePart)
{
    int PerfPartType; // ebx MAPDST
    int MaxLevel; // eax MAPDST
    int MaxPackages; // eax
    int PerfPartLevel; // edx
    int UnlockFilter; // eax MAPDST
    int CarSlotID; // [esp-Ch] [ebp-18h]
    int UpgradeLevel; // [esp-8h] [ebp-14h] MAPDST

    int Cost = 0;
    if (TheSelectablePart && !CustomizeIsInBackRoom())
    {
        if (*((BYTE*)TheSelectablePart + 28))   // Performance Parts
        {
            PerfPartType = TheSelectablePart[6];
            MaxLevel = Physics_Upgrades_GetMaxLevel(_CarCustomizeManager + 2, PerfPartType);
            PerfPartLevel = TheSelectablePart[5];
            MaxPackages = CarCustomizeManager_GetMaxPackages(_CarCustomizeManager, PerfPartType);
            UpgradeLevel = PerfPartLevel - MaxLevel + MaxPackages;
            UnlockFilter = CarCustomizeManager_GetUnlockFilter();
            return UnlockSystem_GetPerfPackageCost(UnlockFilter, PerfPartType, UpgradeLevel, 0);
        }
        else
        {
            DWORD* TheCarPart = (DWORD*)TheSelectablePart[3];
            CarSlotID = TheSelectablePart[4];

            switch (CarSlotID)// Body and Visual Parts
            {
            case 79:                                  // VINYL_COLOUR0_0
            case 80:                                  // VINYL_COLOUR0_1
            case 81:                                  // VINYL_COLOUR0_2
            case 82:                                  // VINYL_COLOUR0_3
            case 133:                                 // HUD_BACKING_COLOUR
            case 134:                                 // HUD_NEEDLE_COLOUR
            case 135:                                 // HUD_CHARACTER_COLOUR
                break;
            default:
                UnlockFilter = CarCustomizeManager_GetUnlockFilter();
                Cost = UnlockSystem_GetCarPartCost(UnlockFilter, CarSlotID, TheCarPart, 0);
                break;
            }
        }
    }
    return Cost;
}

void __declspec(naked) IsNewCodeCaveParts()
{
    _asm
    {
        ja IsNotNew
        push 0x7A50FF
        retn

        IsNotNew:
            xor al,al
            pop edi
            pop esi
            retn 4
    }
}

void __declspec(naked) IsNewCodeCaveRims()
{
    _asm
    {
        xor al, al
        pop edi
        pop esi
        retn 4
    }
}

void __declspec(naked) IsNewCodeCaveVisual()
{
    _asm
    {
        ja IsNotNew
        push 0x7A51DF
        retn

        IsNotNew :
            xor al, al
            pop edi
            pop esi
            retn 4
    }
}

void __declspec(naked) IsLockedCodeCaveParts()
{
    _asm
    {
        ja IsNotLocked
        push 0x7BAD3A
        retn

        IsNotLocked :
            xor al, al
            pop edi
            pop esi
            pop ebx
            retn 8
    }
}

void __declspec(naked) IsLockedCodeCaveVisual()
{
    _asm
    {
        ja IsNotLocked
        push 0x7BAEE6
        retn

        IsNotLocked :
            xor al, al
            pop edi
            pop esi
            pop ebx
            retn 8
    }
}

bool __fastcall CarCustomizeManager_AreAllRimsStock(DWORD* _CarCustomizeManager, void* EDX_Unused)
{
    DWORD* StockFrontWheel = CarCustomizeManager_GetStockCarPart((DWORD*)_gCarCustomizeManager, 66); // FRONT_WHEEL
    DWORD* StockRearWheel = CarCustomizeManager_GetStockCarPart((DWORD*)_gCarCustomizeManager, 67); // FRONT_WHEEL

    DWORD* InstalledFrontWheel = CarCustomizeManager_GetInstalledCarPart((DWORD*)_gCarCustomizeManager, 66);
    DWORD* InstalledRearWheel = CarCustomizeManager_GetInstalledCarPart((DWORD*)_gCarCustomizeManager, 67);

    bool IsFrontStock = StockFrontWheel == InstalledFrontWheel;
    bool IsRearStock = !InstalledRearWheel || StockRearWheel == InstalledRearWheel;

    return IsFrontStock && IsRearStock;
}

bool __fastcall CarCustomizeManager_IsCareerMode_CheckTCC(DWORD* _CarCustomizeManager, void* EDX_Unused)
{
    bool result = 1;
    bool Test = !*(bool*)g_bTestCareerCustomization;
    DWORD* FEDatabase = *(DWORD**)_FEDatabase;

    if (TestCareerCustomization) Test = 1;

    if ((*((BYTE*)FEDatabase + 300) & 1) == 0 && Test) result = 0;
    return result;
}

void __fastcall CarCustomizeManager_UpdateHeatOnVehicle(DWORD* CarCustomizeManager, void* EDX_Unused, DWORD* TheSelectablePart, DWORD* FECareerRecord)
{
    DWORD* FEDatabase = *(DWORD**)_FEDatabase;

    int CarType; // eax
    CarType = FECarRecord_GetType(*(void**)_FECarRecord);

    // Get config files
    sprintf(CarTypeName, GetCarTypeName(CarType));
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    if (TheSelectablePart && FECareerRecord
        && !*((BYTE*)TheSelectablePart + 28) // Is not performance part
        && ((*((BYTE*)FEDatabase + 300) & 1) != 0 || *(bool*)g_bTestCareerCustomization)) // Career mode
    {
        float HeatAdjustMultiplier = CustomizeIsInBackRoom() ? 0.75f : 1.0f;
        float CustomFECoolingValue = 0.0f;
        //FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;

        switch (TheSelectablePart[4]) // CarSlotID
        {
        case 23: // BODY
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "BodyKits", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnBodyKitApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 44: // SPOILER
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Spoilers", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnSpoilerApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 62: // ROOF
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "RoofScoops", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnRoofScoopApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 63: // HOOD
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Hoods", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnHoodApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 66: // FRONT_WHEEL
        case 67: // REAR_WHEEL
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Rims", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnRimApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 76: // BASE_PAINT
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Paint", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnPaintApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 77: // VINYL_LAYER0
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Vinyls", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnVinylApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 78: // PAINT_RIM
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "RimPaint", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnRimPaintApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 83: // DECAL_FRONT_WINDOW_TEX0
        case 84: // DECAL_FRONT_WINDOW_TEX1
        case 85: // DECAL_FRONT_WINDOW_TEX2
        case 86: // DECAL_FRONT_WINDOW_TEX3
        case 87: // DECAL_FRONT_WINDOW_TEX4
        case 88: // DECAL_FRONT_WINDOW_TEX5
        case 89: // DECAL_FRONT_WINDOW_TEX6
        case 90: // DECAL_FRONT_WINDOW_TEX7
        case 91: // DECAL_REAR_WINDOW_TEX0
        case 92: // DECAL_REAR_WINDOW_TEX1
        case 93: // DECAL_REAR_WINDOW_TEX2
        case 94: // DECAL_REAR_WINDOW_TEX3
        case 95: // DECAL_REAR_WINDOW_TEX4
        case 96: // DECAL_REAR_WINDOW_TEX5
        case 97: // DECAL_REAR_WINDOW_TEX6
        case 98: // DECAL_REAR_WINDOW_TEX7
        case 99: // DECAL_LEFT_DOOR_TEX0
        case 100: // DECAL_LEFT_DOOR_TEX1
        case 101: // DECAL_LEFT_DOOR_TEX2
        case 102: // DECAL_LEFT_DOOR_TEX3
        case 103: // DECAL_LEFT_DOOR_TEX4
        case 104: // DECAL_LEFT_DOOR_TEX5
        case 105: // DECAL_LEFT_DOOR_TEX6
        case 106: // DECAL_LEFT_DOOR_TEX7
        case 107: // DECAL_RIGHT_DOOR_TEX0
        case 108: // DECAL_RIGHT_DOOR_TEX1
        case 109: // DECAL_RIGHT_DOOR_TEX2
        case 110: // DECAL_RIGHT_DOOR_TEX3
        case 111: // DECAL_RIGHT_DOOR_TEX4
        case 112: // DECAL_RIGHT_DOOR_TEX5
        case 113: // DECAL_RIGHT_DOOR_TEX6
        case 114: // DECAL_RIGHT_DOOR_TEX7
        case 115: // DECAL_LEFT_QUARTER_TEX0
        case 116: // DECAL_LEFT_QUARTER_TEX1
        case 117: // DECAL_LEFT_QUARTER_TEX2
        case 118: // DECAL_LEFT_QUARTER_TEX3
        case 119: // DECAL_LEFT_QUARTER_TEX4
        case 120: // DECAL_LEFT_QUARTER_TEX5
        case 121: // DECAL_LEFT_QUARTER_TEX6
        case 122: // DECAL_LEFT_QUARTER_TEX7
        case 123: // DECAL_RIGHT_QUARTER_TEX0
        case 124: // DECAL_RIGHT_QUARTER_TEX1
        case 125: // DECAL_RIGHT_QUARTER_TEX2
        case 126: // DECAL_RIGHT_QUARTER_TEX3
        case 127: // DECAL_RIGHT_QUARTER_TEX4
        case 128: // DECAL_RIGHT_QUARTER_TEX5
        case 129: // DECAL_RIGHT_QUARTER_TEX6
        case 130: // DECAL_RIGHT_QUARTER_TEX7
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Decals", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnDecalApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 131: // WINDOW_TINT
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "WindowTint", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnWindowTintApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 28: // INTERIOR
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Interior", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 0: // BASE
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Roof", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 24: // FRONT_BRAKE
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Brakes", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 31: // LEFT_HEADLIGHT
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Headlights", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 29: // LEFT_BRAKELIGHT
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Taillights", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 33: // LEFT_SIDE_MIRROR
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Mirrors", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 52: // ATTACHMENT0
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Attachment1", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 53: // ATTACHMENT1
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Attachment2", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 54: // ATTACHMENT2
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Attachment3", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 55: // ATTACHMENT3
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Attachment4", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 56: // ATTACHMENT4
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Attachment5", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 57: // ATTACHMENT5
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Attachment6", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 58: // ATTACHMENT6
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Attachment7", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 59: // ATTACHMENT7
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Attachment8", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 60: // ATTACHMENT8
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Attachment9", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 61: // ATTACHMENT9
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Attachment10", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 43: // DRIVER
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Driver", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 69: // LICENSE_PLATE
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "LicensePlate", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 64: // HEADLIGHT
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Tires", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 65: // BRAKELIGHT
            CustomFECoolingValue = GetCarFloatOption(CarINI, GeneralINI, "FECooling", "Neon", 0.0f);
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        default:
            return;
        }
    }
}