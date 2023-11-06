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
			case CAR_SLOT_ID::VINYL_COLOUR0_0:
            case CAR_SLOT_ID::VINYL_COLOUR0_1:
            case CAR_SLOT_ID::VINYL_COLOUR0_2:
            case CAR_SLOT_ID::VINYL_COLOUR0_3:
			case CAR_SLOT_ID::HUD_BACKING_COLOUR:
			case CAR_SLOT_ID::HUD_NEEDLE_COLOUR:
			case CAR_SLOT_ID::HUD_CHARACTER_COLOUR:
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

DWORD* __fastcall CarCustomizeManager_GetRealStockCarPart(DWORD* _CarCustomizeManager, void* EDX_Unused, int CarSlotID)
{
	int CarType = FECarRecord_GetType(*(void**)_FECarRecord);
	return FindPartWithLevel(CarType, CarSlotID, 0);
}

bool __fastcall CarCustomizeManager_IsFrontRimStock(DWORD* _CarCustomizeManager, void* EDX_Unused)
{
	DWORD* StockFrontWheel = CarCustomizeManager_GetRealStockCarPart((DWORD*)_gCarCustomizeManager, EDX_Unused, CAR_SLOT_ID::FRONT_WHEEL);
	DWORD* InstalledFrontWheel = CarCustomizeManager_GetInstalledCarPart((DWORD*)_gCarCustomizeManager, CAR_SLOT_ID::FRONT_WHEEL);
	return StockFrontWheel == InstalledFrontWheel;
}

bool __fastcall CarCustomizeManager_IsRearRimStock(DWORD* _CarCustomizeManager, void* EDX_Unused)
{
	DWORD* StockRearWheel = CarCustomizeManager_GetRealStockCarPart((DWORD*)_gCarCustomizeManager, EDX_Unused, CAR_SLOT_ID::REAR_WHEEL);
	DWORD* InstalledRearWheel = CarCustomizeManager_GetInstalledCarPart((DWORD*)_gCarCustomizeManager, CAR_SLOT_ID::REAR_WHEEL);
	return StockRearWheel == InstalledRearWheel;
}

bool __fastcall CarCustomizeManager_IsRearRimInstalled(DWORD* _CarCustomizeManager, void* EDX_Unused)
{
	DWORD* InstalledRearWheel = CarCustomizeManager_GetInstalledCarPart((DWORD*)_gCarCustomizeManager, CAR_SLOT_ID::REAR_WHEEL);
	return InstalledRearWheel;
}

bool __fastcall CarCustomizeManager_AreAllRimsStock(DWORD* _CarCustomizeManager, void* EDX_Unused)
{
    return CarCustomizeManager_IsFrontRimStock(_CarCustomizeManager, 0) && 
		(!CarCustomizeManager_IsRearRimInstalled(_CarCustomizeManager, 0) || CarCustomizeManager_IsRearRimStock(_CarCustomizeManager, 0));
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

bool CarCustomizeManager_CanEnterBackroom()
{
	DWORD* FEDatabase = *(DWORD**)_FEDatabase;
	int NumMarkers;

	if (CustomizeIsInBackRoom()) return 0; // Already in backroom
	if ((*((BYTE*)FEDatabase + 300) & 1)) // Career mode
	{
		// If in career mode, check number of markers
		NumMarkers = FEMarkerManager_GetNumCustomizeMarkers((DWORD*)TheFEMarkerManager);
		if (!NumMarkers) return 0;
	}
	else // My Cars
	{
		if (!MyCarsBackroom) return 0;
	}

	return 1;
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
		case CAR_SLOT_ID::BODY:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.BodyKits;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnBodyKitApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
		case CAR_SLOT_ID::SPOILER:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Spoilers;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnSpoilerApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
		case CAR_SLOT_ID::ROOF:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.RoofScoops;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnRoofScoopApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
		case CAR_SLOT_ID::HOOD:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Hoods;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnHoodApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
		case CAR_SLOT_ID::FRONT_WHEEL:
		case CAR_SLOT_ID::REAR_WHEEL:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Rims;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnRimApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
		case CAR_SLOT_ID::BASE_PAINT:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Paint;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnPaintApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
		case CAR_SLOT_ID::VINYL_LAYER0:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Vinyls;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnVinylApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
		case CAR_SLOT_ID::PAINT_RIM:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.RimPaint;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnRimPaintApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
        case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX0:
        case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX1:
        case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX2:
        case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX3:
        case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX4:
        case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX5:
        case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX6:
        case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX7:
        case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX0:
        case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX1:
        case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX2:
        case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX3:
        case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX4:
        case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX5:
        case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX6:
        case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX7:
        case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX0:
        case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX1:
        case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX2:
        case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX3:
        case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX4:
        case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX5:
        case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX6:
        case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX7:
        case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX0:
        case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX1:
        case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX2:
        case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX3:
        case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX4:
        case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX5:
        case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX6:
        case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX7:
        case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX0:
        case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX1:
        case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX2:
        case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX3:
        case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX4:
        case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX5:
        case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX6:
        case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX7:
        case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX0:
        case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX1:
        case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX2:
        case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX3:
        case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX4:
        case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX5:
        case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX6:
        case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX7:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Decals;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnDecalApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
		case CAR_SLOT_ID::WINDOW_TINT:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.WindowTint;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            else FECareerRecord_AdjustHeatOnWindowTintApplied(FECareerRecord, HeatAdjustMultiplier);
            break;
		case CAR_SLOT_ID::INTERIOR:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Interior;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::BASE:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Roof;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::FRONT_BRAKE:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Brakes;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::LEFT_HEADLIGHT:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Headlights;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::LEFT_BRAKELIGHT:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Taillights;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::LEFT_SIDE_MIRROR:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Mirrors;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::ATTACHMENT0:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment0;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::ATTACHMENT1:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment1;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::ATTACHMENT2:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment2;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::ATTACHMENT3:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment3;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::ATTACHMENT4:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment4;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::ATTACHMENT5:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment5;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::ATTACHMENT6:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment6;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::ATTACHMENT7:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment7;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::ATTACHMENT8:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment8;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::ATTACHMENT9:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Attachment9;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::DRIVER:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Driver;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::LICENSE_PLATE:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.LicensePlate;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::HEADLIGHT:
            CustomFECoolingValue = CarConfigs[CarType].FECooling.Tires;
            if (CustomFECoolingValue != 0.0f) FECareerRecord[3] = FECareerRecord[3] * CustomFECoolingValue * HeatAdjustMultiplier;
            break;
		case CAR_SLOT_ID::BRAKELIGHT:
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
	case MenuID::CustomizeCategory_Parts:
		SubMenuID = MenuID::Customize_Parts_Bodykits;
		SubMenuIDMax = MenuID::Customize_Parts_Attachments;
		break;

	case MenuID::CustomizeCategory_Performance:
		SubMenuID = MenuID::Customize_Performance_Engine;
		SubMenuIDMax = MenuID::Customize_Performance_Induction;
		break;

	case MenuID::CustomizeCategory_Visual:
		SubMenuID = MenuID::Customize_Visual_Paint;
		SubMenuIDMax = MenuID::Customize_Visual_Neon;
		break;

	case MenuID::Customize_Parts_Rims: // Rims
		SubMenuID = MenuID::Customize_Rims_First;
		SubMenuIDMax = MenuID::Customize_Rims_Min + RimBrands.size();
		break;

	case MenuID::Customize_Parts_Attachments: // Attachments
		SubMenuID = MenuID::Customize_Parts_Attachment0;
		SubMenuIDMax = MenuID::Customize_Parts_Attachment9;
		break;

	case MenuID::Customize_Visual_Vinyls: // Vinyls
		SubMenuID = MenuID::Customize_Vinyls_First;
		SubMenuIDMax = MenuID::Customize_Vinyls_Min + VinylGroups.size();
		break;

	case MenuID::Customize_Visual_Decals: // Decals
		SubMenuID = MenuID::Customize_Decals_Windshield;
		SubMenuIDMax = MenuID::Customize_Decals_RightQuarter;
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
		if (MenuID >= MenuID::Customize_Rims_First && MenuID <= MenuID::Customize_Rims_Last) // Rims
		{
			UnlockableID = 25;
		}
		else if (MenuID >= MenuID::Customize_Vinyls_First && MenuID <= MenuID::Customize_Vinyls_Last) // Vinyls
		{
			UnlockableID = 35;
		}
		else // Part Menus
		{
			switch (MenuID)
			{
				// Body Parts
			case MenuID::Customize_Parts_Bodykits: // Body kits
				UnlockableID = 11;
				break;
			case MenuID::Customize_Parts_Spoilers: // Spoilers
				UnlockableID = 12;
				break;
			case MenuID::Customize_Parts_Hoods: // Hoods
				UnlockableID = 14;
				break;
			case MenuID::Customize_Parts_RoofScoops: // Roof Scoops
				UnlockableID = 15;
				break;
				// unlimiter parts??

			// Performance Parts
			case MenuID::Customize_Performance_Engine: // Engine
				UnlockableID = 8;
				break;
			case MenuID::Customize_Performance_Transmission: // Transmission
				UnlockableID = 7;
				break;
			case MenuID::Customize_Performance_Chassis: // Chassis
				UnlockableID = 6;
				break;
			case MenuID::Customize_Performance_Nitrous: // Nitrous
				UnlockableID = 10;
				break;
			case MenuID::Customize_Performance_Tires: // Tires
				UnlockableID = 4;
				break;
			case MenuID::Customize_Performance_Brakes: // Brakes
				UnlockableID = 5;
				break;
			case MenuID::Customize_Performance_Induction: // Induction
				UnlockableID = 9;
				break;

				// Visual Parts
			case MenuID::Customize_Visual_Paint:
				UnlockableID = 23; // Paint
				break;
			case MenuID::Customize_Visual_RimPaint: // Rim Paint
				UnlockableID = 24;
				break;
			case MenuID::Customize_Visual_WindowTint: // Window Tint
				UnlockableID = 18;
				break;
			case MenuID::Customize_Visual_Numbers: // Numbers
				UnlockableID = 43;
				break;
			case MenuID::Customize_Visual_CustomGauges: // Custom Gauges
				UnlockableID = 17;
				break;
				// unlimiter parts??

			// Decals
			case MenuID::Customize_Decals_Windshield:
			case MenuID::Customize_Decals_RearWindow:
				UnlockableID = 44;
				break;
			case MenuID::Customize_Decals_LeftQuarter:
			case MenuID::Customize_Decals_RightQuarter:
				UnlockableID = 48;
				break;
			case MenuID::Customize_Decals_LeftDoor:
			case MenuID::Customize_Decals_RightDoor:
			case MenuID::Customize_Decals_Slot1:
			case MenuID::Customize_Decals_Slot2:
			case MenuID::Customize_Decals_Slot3:
			case MenuID::Customize_Decals_Slot4:
			case MenuID::Customize_Decals_Slot5:
			case MenuID::Customize_Decals_Slot6:
			case MenuID::Customize_Decals_Slot7:
			case MenuID::Customize_Decals_Slot8:
				UnlockableID = 46;
				break;

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
		case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX0: // Window Decals
		case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX1:
		case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX2:
		case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX3:
		case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX4:
		case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX5:
		case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX6:
		case CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX7:
		case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX0:
		case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX1:
		case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX2:
		case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX3:
		case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX4:
		case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX5:
		case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX6:
		case CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX7:
			IsInBackroom = CustomizeIsInBackRoom();
			UnlockFilter = CarCustomizeManager_GetUnlockFilter();
			result = UnlockSystem_IsUnlockableUnlocked(UnlockFilter, 44, 1, 0, IsInBackroom) == 0;
			break;
		case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX0: // Door Decals
		case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX1:
		case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX2:
		case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX3:
		case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX4:
		case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX5:
		case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX0:
		case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX1:
		case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX2:
		case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX3:
		case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX4:
		case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX5:
			IsInBackroom = CustomizeIsInBackRoom();
			UnlockFilter = CarCustomizeManager_GetUnlockFilter();
			result = UnlockSystem_IsUnlockableUnlocked(UnlockFilter, 46, 2, 0, IsInBackroom) == 0;
			break;
		case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX0: // Quarter decals
		case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX1:
		case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX2:
		case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX3:
		case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX4:
		case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX5:
		case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX6:
		case CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX7:
		case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX0:
		case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX1:
		case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX2:
		case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX3:
		case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX4:
		case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX5:
		case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX6:
		case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX7:
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

	int CurrCategoryID = MenuID - MenuID::Customize_Rims_First; 

	int RimBrandsCount = RimBrands.size();
	if (RimBrandsCount <= CurrCategoryID) return 1;

	RimBrandHash = RimBrands[CurrCategoryID].BrandNameHash;

	PartList[0] = (DWORD)PartList;
	PartList[1] = (DWORD)PartList;
	CarCustomizeManager_GetCarPartList(_CarCustomizeManager, CAR_SLOT_ID::FRONT_WHEEL, PartList, RimBrandHash);

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

	int CurrCategoryID = MenuID - MenuID::Customize_Vinyls_First;

	int VinylGroupsCount = VinylGroups.size();
	if (VinylGroupsCount <= CurrCategoryID) return 1;

	VinylGroupIndex = VinylGroups[CurrCategoryID].Index;

	PartList[0] = (DWORD)PartList;
	PartList[1] = (DWORD)PartList;
	CarCustomizeManager_GetCarPartList(_CarCustomizeManager, CAR_SLOT_ID::VINYL_LAYER0, PartList, VinylGroupIndex);

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
	case MenuID::Customize_Parts_Rims: // Rims
		SubMenuID = MenuID::Customize_Rims_First;
		SubMenuIDMax = MenuID::Customize_Rims_Min + RimBrands.size();
		break;

	case MenuID::Customize_Parts_Attachments: // Attachments
		SubMenuID = MenuID::Customize_Parts_Attachment0;
		SubMenuIDMax = MenuID::Customize_Parts_Attachment9;
		break;

	case MenuID::Customize_Visual_Vinyls: // Vinyls
		SubMenuID = MenuID::Customize_Vinyls_First;
		SubMenuIDMax = MenuID::Customize_Vinyls_Min + VinylGroups.size();
		break;

	case MenuID::Customize_Visual_Decals: // Decals
		SubMenuID = MenuID::Customize_Decals_Windshield;
		SubMenuIDMax = MenuID::Customize_Decals_RightQuarter;
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
		if (MenuID >= MenuID::Customize_Rims_First && MenuID <= MenuID::Customize_Rims_Last) // Rims
		{
			return CarCustomizeManager_IsRimCategoryLocked(_CarCustomizeManager, EDX_Unused, MenuID, Backroom);
		}
		else if (MenuID >= MenuID::Customize_Vinyls_First && MenuID <= MenuID::Customize_Vinyls_Last) // Vinyls
		{
			return CarCustomizeManager_IsVinylCategoryLocked(_CarCustomizeManager, EDX_Unused, MenuID, Backroom);
		}
		else // Part Menus
		{
			switch (MenuID)
			{
				// Body Parts
			case MenuID::Customize_Parts_Bodykits: // Body kits
				UnlockableID = 11;
				break;
			case MenuID::Customize_Parts_Spoilers: // Spoilers
				UnlockableID = 12;
				break;
			case MenuID::Customize_Parts_Hoods: // Hoods
				UnlockableID = 14;
				break;
			case MenuID::Customize_Parts_RoofScoops: // Roof Scoops
				UnlockableID = 15;
				break;
				// unlimiter parts??

			// Performance Parts
			case MenuID::Customize_Performance_Engine: // Engine
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 4)) return 1;
				UnlockableID = 8;
				break;
			case MenuID::Customize_Performance_Transmission: // Transmission
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 3)) return 1;
				UnlockableID = 7;
				break;
			case MenuID::Customize_Performance_Chassis: // Chassis
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 2)) return 1;
				UnlockableID = 6;
				break;
			case MenuID::Customize_Performance_Nitrous: // Nitrous
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 6)) return 1;
				UnlockableID = 10;
				break;
			case MenuID::Customize_Performance_Tires: // Tires
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 0)) return 1;
				UnlockableID = 4;
				break;
			case MenuID::Customize_Performance_Brakes: // Brakes
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 1)) return 1;
				UnlockableID = 5;
				break;
			case MenuID::Customize_Performance_Induction: // Induction
				if (Backroom && !Physics_Upgrades_CanInstallJunkman(_CarCustomizeManager + 2, 5)) return 1;
				UnlockableID = 9;
				break;

				// Visual Parts
			case MenuID::Customize_Visual_Paint:
				UnlockableID = 23; // Paint
				break;
			case MenuID::Customize_Visual_RimPaint: // Rim Paint
				UnlockableID = 24;
				break;
			case MenuID::Customize_Visual_WindowTint: // Window Tint
				UnlockableID = 18;
				break;
			case MenuID::Customize_Visual_Numbers: // Numbers
				UnlockableID = 43;
				break;
			case MenuID::Customize_Visual_CustomGauges: // Custom Gauges
				UnlockableID = 17;
				break;
				// unlimiter parts??

			// Decals
			case MenuID::Customize_Decals_Windshield:
			case MenuID::Customize_Decals_RearWindow:
				v3 = 1;
				UnlockableID = 44;
				break;
			case MenuID::Customize_Decals_LeftQuarter:
			case MenuID::Customize_Decals_RightQuarter:
				v3 = 3;
				UnlockableID = 48;
				break;
			case MenuID::Customize_Decals_LeftDoor:
			case MenuID::Customize_Decals_RightDoor:
			case MenuID::Customize_Decals_Slot1:
			case MenuID::Customize_Decals_Slot2:
			case MenuID::Customize_Decals_Slot3:
			case MenuID::Customize_Decals_Slot4:
			case MenuID::Customize_Decals_Slot5:
			case MenuID::Customize_Decals_Slot6:
			case MenuID::Customize_Decals_Slot7:
			case MenuID::Customize_Decals_Slot8:
				v3 = 2;
				UnlockableID = 46;
				break;

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

DWORD __fastcall CarCustomizeManager_GetUnlockHash_CarPart(DWORD* _CarCustomizeManager, DWORD* CarPart, int MenuID, int UpgradeLevel)
{
	bool UAT = *(bool*)_UnlockAllThings;
	DWORD UnlockHash = 0x9BB9CCC3; // ERROR_DEFAULT_STRING
	int BinToBeat;
	char UnlockStringBuf[100];
	const char* UnlockString;

	if (UAT) return UnlockHash;

	// Check for a custom string hash
	UnlockHash = CarPart_GetAppliedAttributeUParam(CarPart, bStringHash((char*)"UNLOCK_HASH"), -1);
	if (UnlockHash != -1)
	{
		if (DoesStringExist(UnlockHash)) return UnlockHash;
	}
	// Or get the unlock string according to the unlock condition type
	// Get and check if the condition is met
	int UnlockConditionType = CarPart_GetAppliedAttributeIParam(CarPart, bStringHash((char*)"UNLOCK_TYPE"), -1);

	switch (UnlockConditionType)
	{
	case 0: // Initially unlocked
		return bStringHash((char*)"CUSTOMIZATION_PART_UNLOCK_MSG_06");
	case 1: // Beat Blacklist member
		BinToBeat = CarPart_GetAppliedAttributeIParam(CarPart, bStringHash((char*)"UNLOCK_AT"), 17);
		if (BinToBeat < 2 || BinToBeat > 17) BinToBeat = 17;
		if (BinToBeat == 17) return bStringHash((char*)"CUSTOMIZATION_PART_UNLOCK_MSG_06");
		sprintf(UnlockStringBuf, "CUSTOMIZATION_PART_UNLOCK_MSG_BL_%02d", BinToBeat);
		return bStringHash(UnlockStringBuf);
	case 2: // Complete CS Event #68 (special flag)
		return bStringHash((char*)"CUSTOMIZATION_PART_UNLOCK_MSG_01");
	case 3: // Enter "castrol" cheat code (special flag)
		return bStringHash((char*)"CUSTOMIZATION_PART_UNLOCK_MSG_07");
	case 4: // Complete CS 100% (special flag)
		return bStringHash((char*)"CUSTOMIZATION_PART_UNLOCK_MSG_02");
	case 5: // Complete Career mode at least once  (special flag)
		return bStringHash((char*)"CUSTOMIZATION_PART_UNLOCK_MSG_03");
	case 6: // Complete Game 100% (same as 5??)
		return bStringHash((char*)"CUSTOMIZATION_PART_UNLOCK_MSG_04");
	case -1: // None (Use in game function instead)
	default:
		break;
	}

	//return CarCustomizeManager_GetUnlockHash(_CarCustomizeManager, MenuID, UpgradeLevel);
	if (MenuID >= MenuID::Customize_Rims_Min && MenuID <= MenuID::Customize_Rims_Last) UnlockString = "PARTS_RIMS";
	else if (MenuID >= MenuID::Customize_Decals_Slot1 && MenuID <= MenuID::Customize_Decals_Slot8) UnlockString = "VISUAL_DECALS";
	else if (MenuID >= MenuID::Customize_Decals_Windshield && MenuID <= MenuID::Customize_Decals_RightQuarter) UnlockString = "VISUAL_DECALS";
	else if (MenuID >= MenuID::Customize_Vinyls_Min && MenuID <= MenuID::Customize_Vinyls_Last) UnlockString = "VISUAL_VINYLS";
	else
	{
		switch (MenuID)
		{
			// Parts
		case MenuID::Customize_Parts_Bodykits:
			UnlockString = "PARTS_BODYKITS";
			break;
		case MenuID::Customize_Parts_Spoilers:
			UnlockString = "PARTS_SPOILERS";
			break;
		case MenuID::Customize_Parts_Hoods:
			UnlockString = "PARTS_HOODS";
			break;
		case MenuID::Customize_Parts_RoofScoops:
			UnlockString = "PARTS_ROOFSCOOPS";
			break;

			// Performance
		case MenuID::Customize_Performance_Engine:
			UnlockString = "PERF_ENGINE";
			break;
		case MenuID::Customize_Performance_Transmission:
			UnlockString = "PERF_TRANSMISSION";
			break;
		case MenuID::Customize_Performance_Chassis:
			UnlockString = "PERF_SUSPENSION";
			break;
		case MenuID::Customize_Performance_Nitrous:
			UnlockString = "PERF_NITROUS";
			break;
		case MenuID::Customize_Performance_Tires:
			UnlockString = "PERF_TIRES";
			break;
		case MenuID::Customize_Performance_Brakes:
			UnlockString = "PERF_BRAKES";
			break;
		case MenuID::Customize_Performance_Induction:
			UnlockString = CarCustomizeManager_IsTurbo(_CarCustomizeManager)
				? "PERF_TURBO"
				: "PERF_SUPERCHARGER";
			break;

			// Visual
		case MenuID::Customize_Visual_Paint:
		case MenuID::Customize_Visual_RimPaint:
			UnlockString = "VISUAL_PAINT"; // Rim paints use the same Unlock ID as body paints
			break;
		case MenuID::Customize_Visual_WindowTint:
			UnlockString = "VISUAL_WINDOWTINT";
			break;
		case MenuID::Customize_Visual_Numbers:
			UnlockString = "VISUAL_NUMBERS";
			break;
		case MenuID::Customize_Visual_CustomGauges:
			UnlockString = "VISUAL_HUDS";
			break;

		default:
			return 0x9BB9CCC3;
		}
	}

	if (!UpgradeLevel) return 0x9BB9CCC3;

	snprintf(UnlockStringBuf, 100, "CUSTOMIZATION_%s_%d", UnlockString, UpgradeLevel);
	UnlockHash = bStringHash(UnlockStringBuf);

	if (DoesStringExist(UnlockHash)) return UnlockHash;

	return 0x9BB9CCC3;
}