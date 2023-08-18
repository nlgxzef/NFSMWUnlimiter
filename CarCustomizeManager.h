#pragma once

#include "stdafx.h"
#include "stdio.h"
#include "UnlockSystem.h"
#include "InGameFunctions.h"
#include "Helpers.h"

bool __fastcall CarCustomizeManager_IsCastrolCar(DWORD* CarCustomizeManager, int edx_unused)
{
    bool result; // al

    int CarType; // eax
    CarType = FECarRecord_GetType(*(void**)_FECarRecord);

    int EngineType = CarConfigs[CarType].Main.EngineType;

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

    int EngineType = CarConfigs[CarType].Main.EngineType;

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

bool CarCustomizeManager_IsCareerMode_CheckTCC()
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
            CustomFECoolingValue = CarConfigs[CarType].FECooling.BodyKits;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnBodyKitApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 44: // SPOILER
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Spoilers;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnSpoilerApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 62: // ROOF
            CustomFECoolingValue = CarConfigs[CarType].FECooling.RoofScoops;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnRoofScoopApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 63: // HOOD
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Hoods;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnHoodApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 66: // FRONT_WHEEL
        case 67: // REAR_WHEEL
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Rims;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnRimApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 76: // BASE_PAINT
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Paint;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnPaintApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 77: // VINYL_LAYER0
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Vinyls;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnVinylApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 78: // PAINT_RIM
            CustomFECoolingValue = CarConfigs[CarType].FECooling.RimPaint;
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
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Decals;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnDecalApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 131: // WINDOW_TINT
            CustomFECoolingValue = CarConfigs[CarType].FECooling.WindowTint;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnWindowTintApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case 28: // INTERIOR
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Interior;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 0: // BASE
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Roof;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 24: // FRONT_BRAKE
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Brakes;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 31: // LEFT_HEADLIGHT
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Headlights;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 29: // LEFT_BRAKELIGHT
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Taillights;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 33: // LEFT_SIDE_MIRROR
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Mirrors;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 52: // ATTACHMENT0
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment0;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 53: // ATTACHMENT1
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment1;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 54: // ATTACHMENT2
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment2;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 55: // ATTACHMENT3
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment3;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 56: // ATTACHMENT4
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment4;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 57: // ATTACHMENT5
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment5;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 58: // ATTACHMENT6
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment6;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 59: // ATTACHMENT7
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment7;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 60: // ATTACHMENT8
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment8;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 61: // ATTACHMENT9
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment9;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 43: // DRIVER
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Driver;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 69: // LICENSE_PLATE
            CustomFECoolingValue = CarConfigs[CarType].FECooling.LicensePlate;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 64: // HEADLIGHT
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Tires;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        case 65: // BRAKELIGHT
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Neon;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
        default:
            return;
        }
    }
}

bool __fastcall CarCustomizeManager_IsCategoryNew(DWORD* _CarCustomizeManager, void* EDX_Unused, int MenuID)
{
	int UnlockableID = -1; // esi
	bool result = 0; // al
	int SubMenuID = -1; // esi MAPDST
	int SubMenuIDMax = -1; // esi MAPDST
	char UnlockFilter; // al

	if (*(bool*)_UnlockAllThings) return 0;

	// submenus
	switch (MenuID)
	{
	case 0x801: // Parts
		SubMenuID = 0x101;
		SubMenuIDMax = 0x10D;
		break;

	case 0x802: // Performance
		SubMenuID = 0x201;
		SubMenuIDMax = 0x207;
		break;

	case 0x803: // Visual
		SubMenuID = 0x301;
		SubMenuIDMax = 0x315;
		break;

	case 0x103: // Rims
		SubMenuID = 0x702;
		SubMenuIDMax = 0x701 + RimBrands.size();
		break;

	case 0x10C: // Attachments
		SubMenuID = 0x10D;
		SubMenuIDMax = 0x116;
		break;

	case 0x302: // Vinyls
		SubMenuID = 0x402;
		SubMenuIDMax = 0x401 + VinylGroups.size();
		break;

	case 0x305: // Decals
		SubMenuID = 0x501;
		SubMenuIDMax = 0x506;
		break;
	}

	if (SubMenuID != -1 && SubMenuIDMax != -1)
	{
		while (1)
		{
			result = CarCustomizeManager_IsCategoryNew(_CarCustomizeManager, EDX_Unused, SubMenuID);
			if (result)
				break;
			if ((int)++SubMenuID > SubMenuIDMax)
				return result;
		}
		return 1;
	}
	else
	{
		if (MenuID >= 0x702 && MenuID <= 0x7FF) // Rims
		{
			UnlockableID = 25;
		}
		else if (MenuID >= 0x402 && MenuID <= 0x4FF) // Vinyls
		{
			UnlockableID = 35;
		}
		else // Part Menus
		{
			switch (MenuID)
			{
				// Body Parts
			case 0x101: // Body kits
				UnlockableID = 11;
				break;
			case 0x102: // Spoilers
				UnlockableID = 12;
				break;
			case 0x104: // Hoods
				UnlockableID = 14;
				break;
			case 0x105: // Roof Scoops
				UnlockableID = 15;
				break;
				// unlimiter parts??

			// Performance Parts
			case 0x201: // Engine
				UnlockableID = 8;
				break;
			case 0x202: // Transmission
				UnlockableID = 7;
				break;
			case 0x203: // Chassis
				UnlockableID = 6;
				break;
			case 0x204: // Nitrous
				UnlockableID = 10;
				break;
			case 0x205: // Tires
				UnlockableID = 4;
				break;
			case 0x206: // Brakes
				UnlockableID = 5;
				break;
			case 0x207: // Induction
				UnlockableID = 9;
				break;

				// Visual Parts
			case 0x301:
				UnlockableID = 23; // Paint
				break;
			case 0x303: // Rim Paint
				UnlockableID = 24;
				break;
			case 0x304: // Window Tint
				UnlockableID = 18;
				break;
			case 0x306: // Numbers
				UnlockableID = 43;
				break;
			case 0x307: // Custom Gauges
				UnlockableID = 17;
				break;
				// unlimiter parts??

			// Vinyls
			/*
			case 0x402: // Flame
				UnlockableID = 35;
				break;
			case 0x403: // Tribal
				UnlockableID = 36;
				break;
			case 0x404: // Stripes
				UnlockableID = 37;
				break;
			case 0x405: // Racing Flag
				UnlockableID = 38;
				break;
			case 0x406: // National Flag
				UnlockableID = 39;
				break;
			case 0x407: // Body
				UnlockableID = 40;
				break;
			case 0x408: // Unique
				UnlockableID = 41;
				break;
			case 0x409: // Contest Winners
				UnlockableID = 42;
				break;
			*/
			// Decals
			case 0x501:
			case 0x502:
				UnlockableID = 44;
				break;
			case 0x505:
			case 0x506:
				UnlockableID = 48;
				break;
			case 0x503:
			case 0x504:
			case 0x601:
			case 0x602:
			case 0x603:
			case 0x604:
			case 0x605:
			case 0x606:
			case 0x607:
			case 0x608:
				UnlockableID = 46;
				break;

				// Rims
				/*
				case 0x702: // 5ZIGEN
					UnlockableID = 25;
					break;
				case 0x703: // ADR
					UnlockableID = 26;
					break;
				case 0x704: // BBS
					UnlockableID = 27;
					break;
				case 0x705: // Enkei
					UnlockableID = 28;
					break;
				case 0x706: // König
					UnlockableID = 29;
					break;
				case 0x707: // Löwenhart
					UnlockableID = 30;
					break;
				case 0x708: // Racing Hart
					UnlockableID = 31;
					break;
				case 0x709: // OZ
					UnlockableID = 32;
					break;
				case 0x70A: // Volk
					UnlockableID = 33;
					break;
				case 0x70B: // Ro-Ja
					UnlockableID = 34;
					break;
				*/
			default:
				UnlockableID = 0;
				break;
			}
		}

		if (UnlockableID != -1)
		{
			UnlockFilter = CarCustomizeManager_GetUnlockFilter();
			result = UnlockSystem_IsUnlockableNew(UnlockFilter, UnlockableID, -2);
		}
	}

	return result;
}

bool __fastcall CarCustomizeManager_IsPartNew(DWORD* _CarCustomizeManager, void* EDX_Unused, DWORD* TheSelectablePart, int PackageLevel)
{
	int UnlockableID; // esi MAPDST
	bool result; // eax
	char UnlockFilter; // al MAPDST
	int UpgradeLevel; // esi

	if (*(bool*)_UnlockAllThings) return 0;

	if (*((BYTE*)TheSelectablePart + 28)) // Performance Part
	{
		UnlockableID = MapPerfPkgToUnlockable(TheSelectablePart[6]);
		UnlockFilter = CarCustomizeManager_GetUnlockFilter();
		result = UnlockSystem_IsUnlockableNew(UnlockFilter, UnlockableID, PackageLevel);
	}
	else // Visual Part
	{
		UnlockableID = MapCarPartToUnlockable(TheSelectablePart[4]);
		UpgradeLevel = TheSelectablePart[5];
		UnlockFilter = CarCustomizeManager_GetUnlockFilter();
		result = UnlockSystem_IsUnlockableNew(UnlockFilter, UnlockableID, UpgradeLevel);
	}
	return result;
}

bool __fastcall CarCustomizeManager_IsPartLocked(DWORD* _CarCustomizeManager, void* EDX_Unused, DWORD* TheSelectablePart, int PackageLevel)
{
	int PerformancePartType; // edi
	int UnlockFilter; // esi MAPDST
	bool IsInBackroom; // al MAPDST
	bool result; // eax
	int CarSlotID; // ebx
	DWORD* TheCarPart; // edi

	if (*(bool*)_UnlockAllThings) return 0;

	if (*((BYTE*)TheSelectablePart + 28)) // Performance Part
	{
		PerformancePartType = TheSelectablePart[6];
		UnlockFilter = CarCustomizeManager_GetUnlockFilter();
		IsInBackroom = CustomizeIsInBackRoom();
		result = UnlockSystem_IsPerfPackageUnlocked(UnlockFilter, PerformancePartType, PackageLevel, 0, IsInBackroom) == 0;
	}
	else // Visual Part
	{
		CarSlotID = TheSelectablePart[4];
		switch (CarSlotID)
		{
		case 83: // Window Decals
		case 84:
		case 85:
		case 86:
		case 87:
		case 88:
		case 89:
		case 90:
		case 91:
		case 92:
		case 93:
		case 94:
		case 95:
		case 96:
		case 97:
		case 98:
			IsInBackroom = CustomizeIsInBackRoom();
			UnlockFilter = CarCustomizeManager_GetUnlockFilter();
			result = UnlockSystem_IsUnlockableUnlocked(UnlockFilter, 44, 1, 0, IsInBackroom) == 0;
			break;
		case 99: // Door Decals
		case 100:
		case 101:
		case 102:
		case 103:
		case 104:
		case 107:
		case 108:
		case 109:
		case 110:
		case 111:
		case 112:
			IsInBackroom = CustomizeIsInBackRoom();
			UnlockFilter = CarCustomizeManager_GetUnlockFilter();
			result = UnlockSystem_IsUnlockableUnlocked(UnlockFilter, 46, 2, 0, IsInBackroom) == 0;
			break;
		case 115: // Quarter decals
		case 116:
		case 117:
		case 118:
		case 119:
		case 120:
		case 121:
		case 122:
		case 123:
		case 124:
		case 125:
		case 126:
		case 127:
		case 128:
		case 129:
		case 130:
			IsInBackroom = CustomizeIsInBackRoom();
			UnlockFilter = CarCustomizeManager_GetUnlockFilter();
			result = UnlockSystem_IsUnlockableUnlocked(UnlockFilter, 48, 3, 0, IsInBackroom) == 0;
			break;
		default: // Anything else
			TheCarPart = (DWORD*)TheSelectablePart[3];
			UnlockFilter = CarCustomizeManager_GetUnlockFilter();
			IsInBackroom = CustomizeIsInBackRoom();
			result = UnlockSystem_IsCarPartUnlocked(UnlockFilter, CarSlotID, TheCarPart, 0, IsInBackroom) == 0;
			break;
		}
	}
	return result;
}

bool __fastcall CarCustomizeManager_IsRimCategoryLocked(DWORD* _CarCustomizeManager, void* EDX_Unused, unsigned int MenuID, bool Backroom)
{
	DWORD* TheSelectablePart = 0;
	DWORD* NextSelectablePart = 0;
	DWORD RimBrandHash = 0;
	bool result = 1;
	DWORD PartList[2];

	if (*(bool*)_UnlockAllThings) return 0;

	int CurrCategoryID = MenuID - 0x702;

	int RimBrandsCount = RimBrands.size();
	if (RimBrandsCount <= CurrCategoryID) return 1;

	RimBrandHash = RimBrands[CurrCategoryID].BrandNameHash;

	PartList[0] = (DWORD)PartList;
	PartList[1] = (DWORD)PartList;
	CarCustomizeManager_GetCarPartList(_CarCustomizeManager, 66, PartList, RimBrandHash);

	if (PartList[0]) TheSelectablePart = (DWORD*)(PartList[0] - 4);

	while (TheSelectablePart + 1 != PartList)
	{
		if (CarPart_GetAppliedAttributeUParam((DWORD*)TheSelectablePart[3], 0xEBB03E66, 0) == RimBrandHash
			&& !CarCustomizeManager_IsPartLocked(_CarCustomizeManager, EDX_Unused, TheSelectablePart, 0))
		{
			result = 0;
			break;
		}
		NextSelectablePart = (DWORD*)TheSelectablePart[1];
		if (NextSelectablePart) TheSelectablePart = NextSelectablePart - 1;
		else TheSelectablePart = 0;
	}
	sub_7B3F30(PartList);

	if (Backroom && !result) result = FEMarkerManager_GetNumMarkers((DWORD*)TheFEMarkerManager, 11, 0) <= 0;

	bTList_SelectablePart_dtor(PartList);
	return result;
}

bool __fastcall CarCustomizeManager_IsVinylCategoryLocked(DWORD* _CarCustomizeManager, void* EDX_Unused, unsigned int MenuID, bool Backroom)
{
	DWORD* TheSelectablePart = 0;
	DWORD* NextSelectablePart = 0;
	int VinylGroupIndex = 0;
	bool result = 1;
	DWORD PartList[2];

	if (*(bool*)_UnlockAllThings) return 0;

	int CurrCategoryID = MenuID - 0x402;

	int VinylGroupsCount = VinylGroups.size();
	if (VinylGroupsCount <= CurrCategoryID) return 1;

	VinylGroupIndex = VinylGroups[CurrCategoryID].Index;

	PartList[0] = (DWORD)PartList;
	PartList[1] = (DWORD)PartList;
	CarCustomizeManager_GetCarPartList(_CarCustomizeManager, 77, PartList, VinylGroupIndex);

	if (PartList[0]) TheSelectablePart = (DWORD*)(PartList[0] - 4);

	while (TheSelectablePart + 1 != PartList)
	{
		if (((*(BYTE*)TheSelectablePart[3] + 5) & 0x1F) == VinylGroupIndex
			&& !CarCustomizeManager_IsPartLocked(_CarCustomizeManager, EDX_Unused, TheSelectablePart, 0))
		{
			result = 0;
			break;
		}
		NextSelectablePart = (DWORD*)TheSelectablePart[1];
		if (NextSelectablePart) TheSelectablePart = NextSelectablePart - 1;
		else TheSelectablePart = 0;
	}
	sub_7B3F30(PartList);

	if (Backroom && !result) result = FEMarkerManager_GetNumMarkers((DWORD*)TheFEMarkerManager, 14, 0) <= 0;

	bTList_SelectablePart_dtor(PartList);
	return result;
}

bool __fastcall CarCustomizeManager_IsCategoryLocked(DWORD* _CarCustomizeManager, void* EDX_Unused, int MenuID, bool Backroom)
{
	int UnlockableID = -1; // esi
	bool result = 1; // al
	int SubMenuID = -1; // esi MAPDST
	int SubMenuIDMax = -1; // esi MAPDST
	char UnlockFilter; // al
	int v3 = 0;

	if (*(bool*)_UnlockAllThings) return 0;

	// submenus
	switch (MenuID)
	{
	case 0x103: // Rims
		SubMenuID = 0x702;
		SubMenuIDMax = 0x701 + RimBrands.size();
		break;

	case 0x10C: // Attachments
		SubMenuID = 0x10D;
		SubMenuIDMax = 0x116;
		break;

	case 0x302: // Vinyls
		SubMenuID = 0x402;
		SubMenuIDMax = 0x401 + VinylGroups.size();
		break;

	case 0x305: // Decals
		SubMenuID = 0x501;
		SubMenuIDMax = 0x506;
		break;
	}

	if (SubMenuID != -1 && SubMenuIDMax != -1)
	{
		while (CarCustomizeManager_IsCategoryLocked(_CarCustomizeManager, EDX_Unused, SubMenuID, Backroom))
		{
			if ((int)++SubMenuID > SubMenuIDMax) return 1;
		}
		return 0;
	}
	else
	{
		if (MenuID >= 0x702 && MenuID <= 0x7FF) // Rims
		{
			return CarCustomizeManager_IsRimCategoryLocked(_CarCustomizeManager, EDX_Unused, MenuID, Backroom);
		}
		else if (MenuID >= 0x402 && MenuID <= 0x4FF) // Vinyls
		{
			return CarCustomizeManager_IsVinylCategoryLocked(_CarCustomizeManager, EDX_Unused, MenuID, Backroom);
		}
		else // Part Menus
		{
			switch (MenuID)
			{
				// Body Parts
			case 0x101: // Body kits
				UnlockableID = 11;
				break;
			case 0x102: // Spoilers
				UnlockableID = 12;
				break;
			case 0x104: // Hoods
				UnlockableID = 14;
				break;
			case 0x105: // Roof Scoops
				UnlockableID = 15;
				break;
				// unlimiter parts??

			// Performance Parts
			case 0x201: // Engine
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 4)) return 1;
				UnlockableID = 8;
				break;
			case 0x202: // Transmission
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 3)) return 1;
				UnlockableID = 7;
				break;
			case 0x203: // Chassis
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 2)) return 1;
				UnlockableID = 6;
				break;
			case 0x204: // Nitrous
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 6)) return 1;
				UnlockableID = 10;
				break;
			case 0x205: // Tires
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 0)) return 1;
				UnlockableID = 4;
				break;
			case 0x206: // Brakes
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 1)) return 1;
				UnlockableID = 5;
				break;
			case 0x207: // Induction
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 5)) return 1;
				UnlockableID = 9;
				break;

				// Visual Parts
			case 0x301:
				UnlockableID = 23; // Paint
				break;
			case 0x303: // Rim Paint
				UnlockableID = 24;
				break;
			case 0x304: // Window Tint
				UnlockableID = 18;
				break;
			case 0x306: // Numbers
				UnlockableID = 43;
				break;
			case 0x307: // Custom Gauges
				UnlockableID = 17;
				break;
				// unlimiter parts??

			// Vinyls
			/*
			case 0x402: // Flame
				UnlockableID = 35;
				break;
			case 0x403: // Tribal
				UnlockableID = 36;
				break;
			case 0x404: // Stripes
				UnlockableID = 37;
				break;
			case 0x405: // Racing Flag
				UnlockableID = 38;
				break;
			case 0x406: // National Flag
				UnlockableID = 39;
				break;
			case 0x407: // Body
				UnlockableID = 40;
				break;
			case 0x408: // Unique
				UnlockableID = 41;
				break;
			case 0x409: // Contest Winners
				UnlockableID = 42;
				break;
			*/
			// Decals
			case 0x501:
			case 0x502:
				v3 = 1;
				UnlockableID = 44;
				break;
			case 0x505:
			case 0x506:
				v3 = 3;
				UnlockableID = 48;
				break;
			case 0x503:
			case 0x504:
			case 0x601:
			case 0x602:
			case 0x603:
			case 0x604:
			case 0x605:
			case 0x606:
			case 0x607:
			case 0x608:
				v3 = 2;
				UnlockableID = 46;
				break;

				// Rims
				/*
				case 0x702: // 5ZIGEN
					UnlockableID = 25;
					break;
				case 0x703: // ADR
					UnlockableID = 26;
					break;
				case 0x704: // BBS
					UnlockableID = 27;
					break;
				case 0x705: // Enkei
					UnlockableID = 28;
					break;
				case 0x706: // König
					UnlockableID = 29;
					break;
				case 0x707: // Löwenhart
					UnlockableID = 30;
					break;
				case 0x708: // Racing Hart
					UnlockableID = 31;
					break;
				case 0x709: // OZ
					UnlockableID = 32;
					break;
				case 0x70A: // Volk
					UnlockableID = 33;
					break;
				case 0x70B: // Ro-Ja
					UnlockableID = 34;
					break;
				*/
			default:
				UnlockableID = 0;
				break;
			}
		}

		if (UnlockableID != -1)
		{
			UnlockFilter = CarCustomizeManager_GetUnlockFilter();
			result = Backroom
				? !UnlockSystem_IsBackroomAvailable(UnlockFilter, UnlockableID, v3)
				: !UnlockSystem_IsUnlockableUnlocked(UnlockFilter, UnlockableID, v3, 0, 0);
		}
	}

	return result;
}