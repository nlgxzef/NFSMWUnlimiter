#include "stdafx.h"
#include "stdio.h"
#include <string>
#include <windows.h>
#include "includes\injector\injector.hpp"
#include "includes\IniReader.h"

int ManuID, CarArraySize, CarCount, ReplacementCar, TrafficCarCount, RacerNamesCount, FrameDelay;
bool ManuHook, ExtraCustomization, DisappearingWheelsFix, SecondaryLogoFix, ExpandMemoryPools, AddOnCopsDamageFix, ForceStockPartsOnAddOnOpponents, ChallengeSeriesOpponentNameFix, CopDestroyedStringHook, DisableTextureReplacement, MyCarsBackroom, FNGFix, RandomHook, PaintMenuFix, BonusCarsHook, CarSkinFix;

#include "InGameFunctions.h"
#include "CustomizeMain.h"
#include "CustomizeSub.h"
#include "CustomizeParts.h"
#include "CustomizeRims.h"
#include "CustomizePaint.h"
#include "CustomizeDecals.h"
#include "CustomizeShoppingCart.h"
#include "FEShoppingCartItem.h"
#include "CarRenderInfo.h"
#include "RideInfo.h"
#include "PursuitBoard.h"
#include "GRacerInfo.h"
#include "CarCustomizeManager.h"
#include "CarPart.h"
#include "SimConnection.h"
#include "FEPackage.h"
#include "FEPlayerCarDB.h"
#include "UIQRCarSelect.h"
#include "QuickRaceUnlocker.h"
#include "UnlockSystem.h"
#include "CompositeSkin.h"
//#include "CarRenderConn.h"
#include "Helpers.h"
#include "CodeCaves.h"

int Init()
{
	CIniReader Settings("NFSMWUnlimiterSettings.ini");

	// Main
	ReplacementCar = Settings.ReadInteger("Main", "ReplacementModel", 1);
	TrafficCarCount = Settings.ReadInteger("Main", "TrafficCarCount", 10);
	ManuHook = Settings.ReadInteger("Main", "EnableManufacturerHook", 1) != 0;
	ExtraCustomization = Settings.ReadInteger("Main", "EnableExtraCustomization", 1) != 0;
	MyCarsBackroom = Settings.ReadInteger("Main", "MyCarsBackroom", 1) != 0;
	CopDestroyedStringHook = Settings.ReadInteger("Main", "EnableCopDestroyedStringHook", 1) != 0;
	RandomHook = Settings.ReadInteger("Main", "EnableRandomPartsHook", 1) != 0;
	BonusCarsHook = Settings.ReadInteger("Main", "EnableBonusCarsHook", 0) != 0;

	// Fixes
	DisappearingWheelsFix = Settings.ReadInteger("Fixes", "DisappearingWheelsFix", 1) != 0;
	SecondaryLogoFix = Settings.ReadInteger("Fixes", "SecondaryLogoFix", 1) != 0;
	AddOnCopsDamageFix = Settings.ReadInteger("Fixes", "AddOnCopsDamageFix", 1) != 0;
	ChallengeSeriesOpponentNameFix = Settings.ReadInteger("Fixes", "ChallengeSeriesOpponentNameFix", 1) != 0;
	PaintMenuFix = Settings.ReadInteger("Fixes", "PaintMenuFix", 1) != 0;
	FNGFix = Settings.ReadInteger("Fixes", "FNGFix", 1) != 0;
	CarSkinFix = Settings.ReadInteger("Fixes", "CarSkinFix", 0) != 0;

	// Misc
	ExpandMemoryPools = Settings.ReadInteger("Misc", "ExpandMemoryPools", 0) != 0;
	FrameDelay = Settings.ReadInteger("Misc", "FrameDelay", -1);
	//BETACompatibility = Settings.ReadInteger("Misc", "BETACompatibility", 0) != 0;
	//HPCCompatibility = Settings.ReadInteger("Misc", "HPCCompatibility", 0) != 0;
	ForceStockPartsOnAddOnOpponents = Settings.ReadInteger("Misc", "ForceStockPartsOnAddOnOpponents", 0) != 0;
	// Debug
	DisableTextureReplacement = Settings.ReadInteger("Debug", "DisableTextureReplacement", 0) != 0;

	// Check compatibility
	BETACompatibility = GetModuleHandleA("NFSMWBeta.asi") ? 1 : 0;
	HPCCompatibility = GetModuleHandleA("NFSMWHPC.asi") ? 1 : 0;

	// Count Cars Automatically
	injector::MakeJMP(0x756AA7, DoUnlimiterStuffCodeCave, true);

	// Car Type Unlimiter
	injector::MakeJMP(0x6690BB, CarCountCodeCave_PVehicle_Resource_Resource, true);
	injector::MakeJMP(0x7398A6, CarCountCodeCave_sub_7398A0, true);
	injector::MakeJMP(0x73995B, CarCountCodeCave_GetCarTypeInfoFromHash, true);
	injector::MakeJMP(0x7515FB, CarCountCodeCave_sub_7515D0, true);
	injector::MakeJMP(0x759913, CarCountCodeCave_RideInfo_FillWithPreset, true);
	injector::MakeJMP(0x75E6F4, CarCountCodeCave_CarRenderConn_Construct, true);
	injector::MakeJMP(0x75E7B4, CarCountCodeCave_HeliRenderConn_Construct, true);

	// Replacement model if model not found in array
	injector::WriteMemory<int>(0x739909, ReplacementCar, true);

	// Fix crash if the model doesn't exist (Model will be invisible)
	injector::MakeJMP(0x75C712, ReplacementCarCodeCave_CarLoader_Load, true);

	// Traffic Pattern Unlimiter
	injector::WriteMemory<BYTE>(0x439B79, TrafficCarCount, true); // AITrafficManager::SpawnTraffic
	injector::WriteMemory<BYTE>(0x410962, TrafficCarCount, true); // AITrafficManager::SetTrafficPattern
	injector::WriteMemory<BYTE>(0x4265C2, TrafficCarCount, true); // AITrafficManager::FlushAllTraffic
	injector::WriteMemory<BYTE>(0x426254, TrafficCarCount, true); // AITrafficManager::NextSpawn
	injector::WriteMemory<int>(0x426256, TrafficCarCount, true); // AITrafficManager::NextSpawn

	// Manufacturer logo hook
	if (ManuHook)
	{
		injector::MakeJMP(0x5817C1, CarManuCodeCave, true);
		injector::MakeRangedNOP(0x581B69, 0x581B6E, true); // Prevent returning null
	}

	// Show Backroom Parts on Customization
	if (MyCarsBackroom)
	{
		injector::MakeNOP(0x7BFF28, 6, true); // CustomizeMain::NotificationMessage - Switch to Backroom Menu
		injector::MakeJMP(0x7B1226, MyCarsBackroomWidgetCodeCave, true); // CustomizeMain::RefreshHeader
		injector::MakeJMP(0x7BFE2F, MyCarsBackroomEscCodeCave, true); // CustomizeMain::NotificationMessage
		injector::MakeJMP(0x7BFCC2, MyCarsBackroomRoomChangeCodeCave, true); // CustomizeMain::SwitchRooms
		injector::MakeJMP(0x7A60F0, MyCarsBackroomRoomChangeCodeCave2, true); // CustomizeMain::SwitchRooms_0 (0x7A60E0)
		injector::MakeJMP(0x7A65C0, CustomizeMain_SetScreenNames, true); // CustomizeMain::SetScreenNames
		injector::MakeNOP(0x7B92C8, 6, true); // CustomizePerformance::Setup - Fix Junkman Parts
	}
	
	// Extra Customization Stuff
	if (ExtraCustomization || HPCCompatibility)
	{
		// Hook customize main
		injector::MakeCALL(0x7BFCEC, CustomizeMain_BuildOptionsList, true); // CustomizeMain::SwitchRooms
		injector::MakeCALL(0x7C0055, CustomizeMain_BuildOptionsList, true); // CustomizeMain::Setup

		injector::MakeNOP(0x7B123D, 2, true); // CustomizeMain::RefreshHeader - Backroom HUD Widget (BMWM3GTRE46)
		injector::MakeNOP(0x7BFF49, 6, true); // CustomizeMain::NotificationMessage - Switch to Backroom Menu (BMWM3GTRE46)
		injector::MakeNOP(0x7B92DC, 6, true); // CustomizePerformance::Setup - Backroom Performance Parts (BMWM3GTRE46)
		injector::MakeNOP(0x7BC28C, 2, true); // CustomizeSub::SetupVisual - Rim Paint (BMWM3GTRE46)

		injector::MakeJMP(0x7BFBD0, CustomizeSub_Setup, true); // Add new options
		injector::MakeJMP(0x7A5F40, FEShoppingCartItem_GetCarPartCatHash, true); // Add the new names for shopping cart, 18 calls
		injector::MakeJMP(0x7B759A, CustomizePartsPackageSwitchCodeCave, true); // Fix package switching for attachments

		// Texture caves
		if (!DisableTextureReplacement)
		{
			injector::MakeJMP(0x737E26, TextureReplacementCodeCave, true); // Add texture replacements to the table
			injector::MakeJMP(0x75230D, UsedCarTextureInfoCodeCave, true); // Allow custom texture names for interior in UsedCarTexture table
		}
		
		// Fix headlight and taillight texture changing
		injector::WriteMemory<int>(0x751B8B, 0xC4, true); // RideInfo + 0xC4 = LEFT_HEADLIGHT
		injector::WriteMemory<int>(0x751B91, 0xBC, true); // RideInfo + 0xBC = LEFT_BRAKELIGHT

		// Implement new part changing
		injector::MakeJMP(0x756E90, RideInfo_SetPart, true); // RideInfo::SetPart

		// Customization setup for new ids
		injector::MakeJMP(0x7BD0CD, CustomizePartsIDCodeCave, true); // CustomizeParts::Setup
		injector::MakeJMP(0x7BD168, CustomizeVisualsIDCodeCave, true); // CustomizeParts::Setup

		// Remove locked & new status from new categories
		injector::MakeNOP(0x7A50F9, 6, true); // CarCustomizeManager::IsCategoryNew, Parts category
		injector::MakeJMP(0x7A50F9, IsNewCodeCaveParts, true); // CarCustomizeManager::IsCategoryNew, Parts category
		injector::MakeNOP(0x7A51D9, 6, true); // CarCustomizeManager::IsCategoryNew, Visual category
		injector::MakeJMP(0x7A51D9, IsNewCodeCaveVisual, true); // CarCustomizeManager::IsCategoryNew, Visual category
		injector::MakeNOP(0x7BAD34, 6, true); // CarCustomizeManager::IsCategoryLocked, Parts category
		injector::MakeJMP(0x7BAD34, IsLockedCodeCaveParts, true); // CarCustomizeManager::IsCategoryLocked, Parts category
		injector::MakeNOP(0x7BAEE0, 6, true); // CarCustomizeManager::IsCategoryLocked, Visual category
		injector::MakeJMP(0x7BAEE0, IsLockedCodeCaveVisual, true); // CarCustomizeManager::IsCategoryLocked, Visual category

		// Decals
		injector::MakeJMP(0x7A7030, CustomizeDecals_GetSlotIDFromCategory, true); // 3 references
		injector::WriteMemory<int>(0x7BCF14, 0x608, true); // CustomizationScreen::CustomizationScreen

		// Shopping Cart Text
		injector::MakeCALL(0x7BB17B, FEShoppingCartItem_DrawPartName, true); // FEShoppingCartItem::Draw

		// LOD Forcing option
		injector::MakeJMP(0x751540, CarPart_GetModelNameHash, true);

		// Rims
		CIniReader RimBrandsINI("UnlimiterData\\_RimBrands.ini");
		int RimBrandsCount = RimBrandsINI.ReadInteger("RimBrands", "NumberOfRimBrands", -1);
		if (RimBrandsCount != -1)
		{
			RimBrandsCount += 0x702;
			injector::MakeJMP(0x7BC4B7, SetupRimBrandsCodeCave, true); // CustomizeSub::SetupRimBrands
			injector::MakeJMP(0x7B7E90, NoRimSizeCodeCave, true); // CustomizeSub::BuildRimsList
			injector::MakeCALL(0x7B7E17, CustomizeRims_GetCategoryBrandHash, true); // CustomizeRims::BuildRimsList
			injector::WriteMemory<short>(0x7BC704, RimBrandsCount, true); // CustomizeSub::SetupRimBrands, expand for new brands (Default: 0x70B)
			injector::WriteMemory<short>(0x7A587D, RimBrandsCount, true); // TranslateCustomizeCatToMarker
			injector::WriteMemory<short>(0x7AFEAD, RimBrandsCount, true); // GetMarkerNameFromCategory
			injector::WriteMemory<short>(0x7B6098, RimBrandsCount, true); // CarCustomizeManager::GetUnlockHash
			injector::WriteMemory<short>(0x7BAD74, RimBrandsCount, true); // CarCustomizeManager::IsCategoryLocked
			injector::WriteMemory<short>(0x7BAF96, RimBrandsCount, true); // CarCustomizeManager::IsCategoryLocked
			injector::MakeJMP(0x7A6490, CustomizeSub_GetRimBrandIndex, true); // CustomizeSub::GetRimBrandIndex
			injector::MakeNOP(0x7A539F, 6, true); // CarCustomizeManager::IsCategoryNew, Rims category
			injector::MakeJMP(0x7A539F, IsNewCodeCaveRims, true); // CarCustomizeManager::IsCategoryNew, Rims category
			injector::WriteMemory(0x8B7FE8, &CustomizeRims_RefreshHeader, true); // CustomizeRims::vtable
		}

		// Apply attributes by hooking CarRenderInfo functions
		injector::MakeCALL(0x760187, CarRenderInfo_UpdateWheelYRenderOffset, true); // CarRenderInfo::CarRenderInfo

		// TODO: Fix tire skid offset in CarRenderConn

		// Fix Service Crash
		injector::MakeJMP(0x6E9E40, SimConnectionService, true); //Sim::Connection::Service
	}
	
	// Check the ini file for destroyed cops messages
	if (CopDestroyedStringHook)
	{
		injector::WriteMemory(0x8A2454, &PursuitBoard_SetNumCopsDestroyed, true);
	}

	// Hook SetRandomParts function to allow randomization for new parts
	if (RandomHook)
	{
		injector::MakeCALL(0x5E8FE0, RideInfo_SetRandomParts, true); // GRacerInfo::CreateVehicle
		injector::MakeCALL(0x7B4907, RideInfo_SetRandomParts, true); // UIQRBrief::NotificationMessage
	}

	// Fix Invisible Wheels
	if (DisappearingWheelsFix)
		injector::WriteMemory<BYTE>(0x74251D, 0x01, true);

	// 2nd logo fix
	if (SecondaryLogoFix)
	{
		injector::MakeRangedNOP(0x591273, 0x591279, true);
	}

	// Expand Memory Pools (ty Berkay and Aero_)
	if (ExpandMemoryPools)
	{
		injector::WriteMemory<short>(0x5F7396, 0x2C80, true); // GManager::PreloadTransientVaults (0x2C8000)
		injector::WriteMemory<short>(0x5F73B2, 0x2C80, true);

		injector::WriteMemory<BYTE>(0x665FDC, 0x80, true); // InitializeEverything (0x8000)

		injector::WriteMemory<DWORD>(0x8F5790, 0x0BE6E0, true); // FEngMemoryPoolSize (InitFEngMemoryPool)
		injector::WriteMemory<DWORD>(0x8F7EF0, 0x01CC00, true); // CarLoaderPoolSizes

		// Fixes disappearing objects
		injector::WriteMemory<uint32_t>(0x5009D2, 0xFA000, true);
		injector::WriteMemory<uint32_t>(0x5009DC, 0xFA000, true);
		injector::WriteMemory<uint32_t>(0x500A01, 0xFA000, true);
		injector::WriteMemory<uint32_t>(0x500A12, 0xFA000, true);
	}

	// Custom Frame Delay
	if (FrameDelay > -1)
	{
		injector::MakeJMP(0x642EB1, CustomFrameDelayCodeCave, true);
	}

	// Damage Parts Fix for Add-On Cop Cars
	if (AddOnCopsDamageFix)
	{
		injector::MakeRangedNOP(0x7603EE, 0x760419, true);
		injector::MakeJMP(0x7603EE, AddOnCopsDamageFixCodeCave, true);
	}

	// Paint related fixes
	if (PaintMenuFix)
	{
		injector::WriteMemory(0x8B8074, CustomizePaint_RefreshHeader, true);
	}
	
	// Racer names count
	injector::MakeCALL(0x66617F, GRacerInfo_CountRandomNames, true);  // InitializeEverything

	// Fix challenge series character names
	if (ChallengeSeriesOpponentNameFix)
	{
		injector::MakeRangedNOP(0x601FD9, 0x601FE2, true); // GRaceStatus::AddRacer
	}

	// Engine Types
	injector::MakeCALL(0x7A727B, CarCustomizeManager_IsCastrolCar, true); // CustomizePerformance::GetPerfPkgDesc
	injector::MakeCALL(0x7A72AB, CarCustomizeManager_IsRotaryCar, true);

	// Clone objects in FNG where needed
	if (FNGFix)
	{
		injector::MakeCALL(0x5C4D64, CloneObjectstoShowMoreItemsInMenu, true); // FEPackageReader::Load
	}

	// Bonus Cars Hook
	if (BonusCarsHook)
	{
		CIniReader BonusCars("UnlimiterData\\_BonusCars.ini");
		int BonusCarsCount = BonusCars.ReadInteger("BonusCars", "NumberOfBonusCars", -1);
		if (BonusCarsCount != -1)
		{
			/* Replace cover car
			char* CoverCarPresetName = BonusCars.ReadString("BonusCar0", "PresetName", "M3GTRCAREERSTART"); // get car preset name
			// Point any cover car name to the new name we have
			// injector::WriteMemory(0x57F60E, CoverCarPresetName, true); // CareerSettings::ResumeCareer
			injector::WriteMemory(0x58FF63, CoverCarPresetName, true); // sub_58FF60
			injector::WriteMemory(0x7C2918, CoverCarPresetName, true); // UIQRCarSelect::Setup
			injector::WriteMemory(0x7A3E4F, CoverCarPresetName, true); // IsValidMikeMannCar
			injector::WriteMemory(0x590DA0, CoverCarPresetName, true); // FEPlayerCarDB::Default
			injector::WriteMemory(0x590E8C, CoverCarPresetName, true); // FEPlayerCarDB::Default
			*/
			// Use hooked bonus cars on new save games
			injector::MakeJMP(0x590D9F, FEPlayerCarDB_Default_BonusCarsCodeCave, true); // FEPlayerCarDB::Default

			// Hook unlockers to check for new bonus cars
			injector::MakeCALL(0x58AA63, UnlockSystem_IsBonusCarCEOnly, true); // UnlockSystem::IsCarUnlocked
			injector::MakeCALL(0x58ADB5, UnlockSystem_IsBonusCarCEOnly, true); // UnlockSystem::IsBonusCarAvailable

			// Hooks to get custom unlock conditions and texts from ini
			injector::MakeCALL(0x58A55C, QuickRaceUnlocker_IsCarUnlocked, true); // OnlineUnlocker::IsCarUnlocked
			injector::MakeCALL(0x58AA19, QuickRaceUnlocker_IsCarUnlocked, true); // UnlockSystem::IsCarUnlocked
			injector::MakeCALL(0x58AA47, QuickRaceUnlocker_IsCarUnlocked, true); // UnlockSystem::IsCarUnlocked
			injector::MakeCALL(0x7ADD80, UIQRCarSelect_GetBonusUnlockText, true); // UIQRCarSelect::RefreshHeader
			injector::MakeCALL(0x7ADD8D, UIQRCarSelect_GetBonusUnlockBinNumber, true); // UIQRCarSelect::RefreshHeader
		}

		// Skip RefreshBonusCarsList function, use regular checks instead. (Fixes crashes)
		injector::WriteMemory<BYTE>(0x7BF7E5, 0xEB, true); // UIQRCarSelect::RefreshCarList
		injector::WriteMemory<BYTE>(0x7BF95B, 0x01, true); // UIQRCarSelect::RefreshCarList, skip sorting by unlocks if the category is Bonus
	}

	// Car Skin Fix (Requires CarSkinCount (20) x dummy skin and wheel textures in CARS\TEXTURES.BIN)
	if (CarSkinFix)
	{
		// VehicleRenderConn::Load
		//injector::MakeNOP(0x75D29E, 2, true);
		//injector::MakeRangedNOP(0x75D2BB, 0x75D2D6, true);
		//injector::WriteMemory<unsigned char>(0x75D2B6, CarSkinCount, true); 

		// RideInfo::SetCompositeNameHash
		//injector::MakeRangedNOP(0x747F2B, 0x747F3B, true);
		//injector::WriteMemory<unsigned char>(0x747F22, CarSkinCount, true);

		//injector::MakeRangedNOP(0x73B324, 0x73B328, true); //CompositeSkin32, crash fix??

		// Relocate Swatch Offset arrays
		//injector::WriteMemory(0x73B082, SwatchOffsetCache, true); //CompositeSkin32
		//injector::WriteMemory(0x73B0EB, SwatchOffsetCache, true); //CompositeSkin32
		//injector::WriteMemory(0x73B2F4, SwatchOffsetCache, true); //CompositeSkin32
		//injector::WriteMemory(0x748CC9, SwatchOffsetCache, true); //CompositeSkin
		//injector::WriteMemory(0x748D0F, SwatchOffsetCache, true); //CompositeSkin
		//injector::WriteMemory(0x749280, SwatchOffsetCache, true); //CompositeSkin
		//
		//injector::WriteMemory(0x73B0D5, SwatchOffsetCount, true); //CompositeSkin32
		//injector::WriteMemory(0x73B0F2, SwatchOffsetCount, true); //CompositeSkin32
		//injector::WriteMemory(0x73B2F9, SwatchOffsetCount, true); //CompositeSkin32
		//injector::WriteMemory(0x748D00, SwatchOffsetCount, true); //CompositeSkin
		//injector::WriteMemory(0x748D1A, SwatchOffsetCount, true); //CompositeSkin
		//injector::WriteMemory(0x74928E, SwatchOffsetCount, true); //CompositeSkin

		// Expand Swatch Offset arrays
		//injector::WriteMemory<BYTE>(0x73B0CD, CarSkinCount, true); //CompositeSkin32
		//injector::WriteMemory<BYTE>(0x748D20, CarSkinCount, true); //CompositeSkin32

		//injector::WriteMemory<BYTE>(0x748CEF, CarSkinCount, true); //CompositeSkin
		//injector::WriteMemory<BYTE>(0x748D20, CarSkinCount, true); //CompositeSkin

		// CompositeSkin, Expand and Relocate cache arrays
		//injector::MakeJMP(0x73AB50, GetSkinCompositeParams, true); // 0 references??
		//injector::MakeCALL(0x749922, IsInSkinCompositeCache, true);
		//injector::MakeCALL(0x749933, UpdateSkinCompositeCache, true);

		// TexturePack::UnAssignTextureData
		//injector::MakeRangedNOP(0x4FCF3E, 0x4FCF5A, true);
		//injector::MakeCALL(0x4FCF5B, FlushFromSkinCompositeCache, true);
	}

	return 0;
}