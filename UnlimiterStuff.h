#include "stdafx.h"
#include "stdio.h"
#include <string>
#include <windows.h>
#include "includes\injector\injector.hpp"
#include "includes\IniReader.h"

int ManuID, CarArraySize, CarCount, CarPartCount, CarPartPartsTableSize, ReplacementCar, TrafficCarCount, RacerNamesCount, FrameDelay;
bool ManuHook, ExtraCustomization, DisappearingWheelsFix, SecondaryLogoFix, ExpandMemoryPools, AddOnCopsDamageFix, ForceStockPartsOnAddOnOpponents, ChallengeSeriesOpponentNameFix, CopDestroyedStringHook, DisableTextureReplacement, MyCarsBackroom, FNGFix, RandomHook, RideHeightFix, BonusCarsHook, CarSkinFix, LightMaterialCrashFix, DisableNeon, DisableLightFlareColors, DisableKitWheelModifications, ExitWorkaround, Presitter, TestCareerCustomization, LimitAdjusterCompatibility;

#include "InGameFunctions.h"
#include "CustomizeMain.h"
#include "CustomizeSub.h"
#include "CustomizeParts.h"
#include "CustomizePerformance.h"
#include "CustomizeRims.h"
#include "CustomizeSpoiler.h"
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
#include "FECarRecord.h"
#include "FECustomizationRecord.h"
#include "UIQRCarSelect.h"
#include "QuickRaceUnlocker.h"
#include "UnlockSystem.h"
#include "eModel.h"
#include "FrontEndRenderingCar.h"
#include "TireState.h"
#include "CarRenderConn.h"
#include "CompositeSkin.h"
#include "Presitter.h"
#include "UserProfile.h"
#include "MemcardCallbacks.h"
#include "Game.h"
#include "Helpers.h"
#include "CodeCaves.h"

int Init()
{
	CIniReader Settings("NFSMWUnlimiterSettings.ini");

	// Main
	ReplacementCar = Settings.ReadInteger("Main", "ReplacementModel", 1);
	//TrafficCarCount = Settings.ReadInteger("Main", "TrafficCarCount", 10);
	ManuHook = Settings.ReadInteger("Main", "EnableManufacturerHook", 1) != 0;
	ExtraCustomization = Settings.ReadInteger("Main", "EnableExtraCustomization", 1) != 0;
	MyCarsBackroom = Settings.ReadInteger("Main", "MyCarsBackroom", 1) != 0;
	CopDestroyedStringHook = Settings.ReadInteger("Main", "EnableCopDestroyedStringHook", 1) != 0;
	RandomHook = Settings.ReadInteger("Main", "EnableRandomPartsHook", 1) != 0;
	BonusCarsHook = Settings.ReadInteger("Main", "EnableBonusCarsHook", 0) != 0;
	Presitter = Settings.ReadInteger("Main", "EnablePresitter", 1) != 0;

	// Fixes
	DisappearingWheelsFix = Settings.ReadInteger("Fixes", "DisappearingWheelsFix", 1) != 0;
	SecondaryLogoFix = Settings.ReadInteger("Fixes", "SecondaryLogoFix", 1) != 0;
	AddOnCopsDamageFix = Settings.ReadInteger("Fixes", "AddOnCopsDamageFix", 1) != 0;
	ChallengeSeriesOpponentNameFix = Settings.ReadInteger("Fixes", "ChallengeSeriesOpponentNameFix", 1) != 0;
	LightMaterialCrashFix = Settings.ReadInteger("Fixes", "LightMaterialCrashFix", 0) != 0;
	RideHeightFix = Settings.ReadInteger("Fixes", "RideHeightFix", 0) != 0;
	FNGFix = Settings.ReadInteger("Fixes", "FNGFix", 0) != 0;
	CarSkinFix = Settings.ReadInteger("Fixes", "CarSkinFix", 0) != 0;

	// Misc
	ExpandMemoryPools = Settings.ReadInteger("Misc", "ExpandMemoryPools", 0) != 0;
	FrameDelay = Settings.ReadInteger("Misc", "FrameDelay", -1);
	//BETACompatibility = Settings.ReadInteger("Misc", "BETACompatibility", 0) != 0;
	//HPCCompatibility = Settings.ReadInteger("Misc", "HPCCompatibility", 0) != 0;
	ForceStockPartsOnAddOnOpponents = Settings.ReadInteger("Misc", "ForceStockPartsOnAddOnOpponents", 0) != 0;
	// Debug
	DisableTextureReplacement = Settings.ReadInteger("Debug", "DisableTextureReplacement", 0) != 0;
	DisableNeon = Settings.ReadInteger("Debug", "DisableNeon", 0) != 0;
	DisableLightFlareColors = Settings.ReadInteger("Debug", "DisableLightFlareColors", 0) != 0;
	DisableKitWheelModifications = Settings.ReadInteger("Debug", "DisableKitWheelModifications", 0) != 0;
	ExitWorkaround = Settings.ReadInteger("Debug", "ExitWorkaround", 0) != 0;
	TestCareerCustomization = Settings.ReadInteger("Debug", "TestCareerCustomization", 0) != 0;

	// Check compatibility
	BETACompatibility = GetModuleHandleA("NFSMWBeta.asi") ? 1 : 0;
	HPCCompatibility = GetModuleHandleA("NFSMWHPC.asi") ? 1 : 0;
	LimitAdjusterCompatibility = GetModuleHandleA("NFSMWLimitAdjuster.asi") ? 1 : 0;

	// Count Cars Automatically
	injector::MakeJMP(0x756AA7, DoUnlimiterStuffCodeCave, true); // LoaderCarInfo
	injector::MakeJMP(0x756BC7, DoUnlimiterStuffCodeCave2, true); // LoaderCarInfo

	// Car Type Unlimiter
	injector::MakeJMP(0x6690BB, CarCountCodeCave_PVehicle_Resource_Resource, true);
	injector::MakeJMP(0x7398A6, CarCountCodeCave_sub_7398A0, true);
	injector::MakeJMP(0x73995B, CarCountCodeCave_GetCarTypeInfoFromHash, true);
	injector::MakeJMP(0x7515FB, CarCountCodeCave_sub_7515D0, true);
	injector::MakeJMP(0x759913, CarCountCodeCave_RideInfo_FillWithPreset, true);
	injector::MakeJMP(0x75E6F4, CarCountCodeCave_CarRenderConn_Construct, true);
	injector::MakeJMP(0x75E7B4, CarCountCodeCave_HeliRenderConn_Construct, true);

	// Fix crash if the model doesn't exist (Model will be invisible)
	injector::MakeJMP(0x75C712, ReplacementCarCodeCave_CarLoader_Load, true);

	// Traffic Pattern Unlimiter (disabled due to instability and fixed size arrays)
	/*
	if (TrafficCarCount > 10) TrafficCarCount = 10;
	injector::WriteMemory<BYTE>(0x439B79, TrafficCarCount, true); // AITrafficManager::SpawnTraffic
	injector::WriteMemory<BYTE>(0x410962, TrafficCarCount, true); // AITrafficManager::SetTrafficPattern
	injector::WriteMemory<BYTE>(0x4265C2, TrafficCarCount, true); // AITrafficManager::FlushAllTraffic
	injector::WriteMemory<BYTE>(0x426254, TrafficCarCount, true); // AITrafficManager::NextSpawn
	injector::WriteMemory<int>(0x426256, TrafficCarCount, true); // AITrafficManager::NextSpawn
	*/

	// Manufacturer logo hook
	if (ManuHook)
	{
		//injector::MakeJMP(0x5817C1, CarManuCodeCave, true);
		//injector::MakeRangedNOP(0x581B69, 0x581B6E, true); // Prevent returning null
		injector::MakeCALL(0x591337, FECarRecord_GetManufacturerName, true); // FECarRecord::GetManuLogoHash
		injector::MakeCALL(0x59125E, FECarRecord_GetManufacturerName, true); // FECarRecord::GetLogoHash
		injector::MakeCALL(0x59117F, FECarRecord_GetManufacturerName, true); // FECarRecord::GetNameHash
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

		injector::WriteMemory(0x8B8058, &CustomizeSub_NotificationMessage, true); // CustomizeSub::vtable
		injector::WriteMemory(0x8B8064, &CustomizeSub_Setup, true);
		injector::MakeCALL(0x7C29D7, CustomizeSub_Setup, true); // Add new options
		injector::MakeJMP(0x7A5F40, FEShoppingCartItem_GetCarPartCatHash, true); // Add the new names for shopping cart, 18 calls

		// Camera Hook
		//injector::MakeCALL(0x7B9FDC, FindScreenInfo, true); // GarageMainScreen::HandleTick
		//injector::MakeCALL(0x7A8D73, FindScreenInfo, true); // FindScreenInfo (recursive)
		//injector::MakeCALL(0x7B9FE4, FindScreenCameraInfo, true); // GarageMainScreen::HandleTick

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
		injector::MakeJMP(0x7594A0, RideInfo_SetStockParts, true); // (9 references)

		// Customization setup for new ids
		injector::WriteMemory(0x8B7EA8, &CustomizeParts_NotificationMessage, true); // CustomizeParts::vtable
		injector::WriteMemory(0x8B7EB0, &CustomizeParts_RefreshHeader, true); // CustomizeParts::vtable
		injector::WriteMemory(0x8B7EB4, &CustomizeParts_Setup, true); // CustomizeParts::vtable
		injector::MakeCALL(0x7C01D3, CustomizeParts_dtor_Hook, true); // CustomizeParts::~CustomizeParts(bool)
		injector::MakeCALL(0x7C01B0, CustomizeParts_Setup, true); // CustomizeParts::CustomizeParts

		// Spoiler
		injector::WriteMemory(0x8B7FCC, &CustomizeSpoiler_Setup, true); // CustomizeSpoiler::vtable
		injector::MakeCALL(0x7C0248, CustomizeSpoiler_Setup, true); // CustomizeSpoiler::CustomizeSpoiler
		injector::MakeJMP(0x7B76C0, CustomizeSpoiler_BuildPartOptionListFromFilter, true); // 4 references

		// Performance
		injector::MakeCALL(0x7B3277, CustomizePerformance_GetPerfPkgDesc, true); // CustomizePerformance::RefreshHeader
		injector::WriteMemory(0x8B7F30, &CustomizePerformance_RefreshHeader, true); // CustomizePerformance::vtable
		injector::WriteMemory(0x8B7F34, &CustomizePerformance_Setup, true); // CustomizePerformance::vtable
		injector::MakeCALL(0x7BE470, CustomizePerformance_Setup, true); // CustomizePerformance::CustomizePerformance

		// Remove locked & new status from new categories
		injector::MakeNOP(0x7A50F9, 6, true); // CarCustomizeManager::IsCategoryNew, Parts category
		injector::MakeJMP(0x7A50F9, IsNewCodeCaveParts, true); // CarCustomizeManager::IsCategoryNew, Parts category
		injector::MakeNOP(0x7A51D9, 6, true); // CarCustomizeManager::IsCategoryNew, Visual category
		injector::MakeJMP(0x7A51D9, IsNewCodeCaveVisual, true); // CarCustomizeManager::IsCategoryNew, Visual category
		injector::MakeNOP(0x7BAD34, 6, true); // CarCustomizeManager::IsCategoryLocked, Parts category
		injector::MakeJMP(0x7BAD34, IsLockedCodeCaveParts, true); // CarCustomizeManager::IsCategoryLocked, Parts category
		injector::MakeNOP(0x7BAEE0, 6, true); // CarCustomizeManager::IsCategoryLocked, Visual category
		injector::MakeJMP(0x7BAEE0, IsLockedCodeCaveVisual, true); // CarCustomizeManager::IsCategoryLocked, Visual category

		// Paint related fixes
		injector::WriteMemory(0x8B8074, CustomizePaint_RefreshHeader, true);

		// Decals
		injector::MakeJMP(0x7A7030, CustomizeDecals_GetSlotIDFromCategory, true); // 3 references
		injector::WriteMemory<int>(0x7BCF14, 0x608, true); // CustomizationScreen::CustomizationScreen

		// Shopping Cart Text
		injector::MakeCALL(0x7BB17B, FEShoppingCartItem_DrawPartName, true); // FEShoppingCartItem::Draw

		// LOD Forcing option
		injector::MakeJMP(0x751540, CarPart_GetModelNameHash, true); // 6 references

		// Rims
		CIniReader RimBrandsINI("UnlimiterData\\_RimBrands.ini");
		int RimBrandsCount = RimBrandsINI.ReadInteger("RimBrands", "NumberOfRimBrands", DefaultRimBrandCount);
		RimBrandsCount += 0x702;
		injector::WriteMemory<short>(0x7A587D, RimBrandsCount, true); // TranslateCustomizeCatToMarker
		injector::WriteMemory<short>(0x7AFEAD, RimBrandsCount, true); // GetMarkerNameFromCategory
		injector::WriteMemory<short>(0x7B6098, RimBrandsCount, true); // CarCustomizeManager::GetUnlockHash
		injector::WriteMemory<short>(0x7BAD74, RimBrandsCount, true); // CarCustomizeManager::IsCategoryLocked
		injector::WriteMemory<short>(0x7BAF96, RimBrandsCount, true); // CarCustomizeManager::IsCategoryLocked
		injector::MakeNOP(0x7A539F, 6, true); // CarCustomizeManager::IsCategoryNew, Rims category
		injector::MakeJMP(0x7A539F, IsNewCodeCaveRims, true); // CarCustomizeManager::IsCategoryNew, Rims category
		injector::WriteMemory(0x8B7FE0, &CustomizeRims_NotificationMessage, true); // CustomizeRims::vtable
		injector::WriteMemory(0x8B7FE8, &CustomizeRims_RefreshHeader, true); // CustomizeRims::vtable
		injector::WriteMemory(0x8B7FEC, &CustomizeRims_Setup, true); // CustomizeRims::vtable
		injector::MakeCALL(0x7C039E, CustomizeRims_Setup, true); // CustomizeRims::CustomizeRims
		injector::MakeCALL(0x7BDB3A, CustomizeRims_BuildRimsList, true); // CustomizeRims::ScrollRimSizes
		injector::MakeCALL(0x7BDB4F, CustomizeRims_BuildRimsList, true); // CustomizeRims::ScrollRimSizes
		
		// Vinyls
		CIniReader VinylGroupsINI("UnlimiterData\\_VinylGroups.ini");
		int VinylGroupsCount = VinylGroupsINI.ReadInteger("VinylGroups", "NumberOfVinylGroups", DefaultVinylGroupCount);
		VinylGroupsCount += 0x402;
		injector::WriteMemory<short>(0x7A5823, VinylGroupsCount, true); // TranslateCustomizeCatToMarker
		injector::WriteMemory<short>(0x7AFE90, VinylGroupsCount, true); // GetMarkerNameFromCategory
		injector::WriteMemory<short>(0x7B600C, VinylGroupsCount, true); // CarCustomizeManager::GetUnlockHash
		injector::WriteMemory<short>(0x7BAEC3, VinylGroupsCount, true); // CarCustomizeManager::IsCategoryLocked
		injector::WriteMemory<short>(0x7BAF10, VinylGroupsCount, true); // CarCustomizeManager::IsCategoryLocked
		injector::WriteMemory<short>(0x7c0ae7, VinylGroupsCount, true); // CustomizePaint::Setup

		// Fix rear rims
		injector::MakeCALL(0x7498D0, CompositeRim, true); // CompositeSkin
		injector::MakeCALL(0x751A85, GetTempCarSkinTextures, true); // GetUsedCarTextureInfo
		injector::WriteMemory<DWORD>(0x7529CD, 0x154, true); // LoadedWheel::LoadedWheel, Seperate rear rims and fix them in game
		injector::MakeJMP(0x74F40B, RearWheelLightMaterialCodeCave, true); // CarRenderInfo::Render

		// Custom part costs
		injector::MakeJMP(0x7AEF70, CarCustomizeManager_GetPartPrice, true); // 4 references
		injector::MakeCALL(0x7B16BE, UnlockSystem_GetCarPartCost, true); // CustomizationScreen::RefreshHeader

		// Custom FECooling (heat level multipliers)
		injector::MakeJMP(0x7AF330, CarCustomizeManager_UpdateHeatOnVehicle, true); // 4 references

		// Fix Service Crash
		injector::MakeJMP(0x6E9E40, SimConnectionService, true); //Sim::Connection::Service

		// Neon
		if (!DisableNeon)
		{
			injector::MakeJMP(0x75FC83, CarShadowCave, true); // CarRenderInfo::CarRenderInfo
			injector::MakeCALL(0x74E839, CarRenderInfo_DrawAmbientShadow_Hook, true); // CarRenderInfo::Render
			injector::MakeJMP(0x744491, ShadowColorCave, true);

			injector::WriteMemory<float*>(0x743F4E, &CarDistMax, true); // CarRenderInfo::DrawAmbientShadow
			injector::WriteMemory<float*>(0x743F75, &CarDistMax, true);
			injector::WriteMemory<float*>(0x743F61, &CarDistMult, true);
			injector::WriteMemory<float*>(0x744462, &CarDistBright, true);
			injector::WriteMemory<float*>(0x74446A, &CarShadBright, true);
			injector::WriteMemory<float*>(0x744021, &FrontShadowSize, true);
			injector::WriteMemory<float*>(0x744013, &RearShadowSize, true);
			injector::WriteMemory<float*>(0x744003, &LeftShadowSize, true); // left
			injector::WriteMemory<float*>(0x743FF2, &RightShadowSize, true); // right
			injector::WriteMemory<float*>(0x74406A, &ShadowSunMultiplier, true);
		}

		// Light Flare Colors
		if (!DisableLightFlareColors)
		{
			hb_eRenderLightFlare.fun = injector::MakeJMP(0x743235, RenderLightFlareCodeCave, true).get(); // CarRenderInfo::RenderFlaresOnCar

			injector::MakeCALL(0x6DAF96, RenderFEFlares, true); // sub_6DAE20
			injector::MakeCALL(0x6DE616, RenderFEFlares, true); // sub_6DE300
			hb_RenderFEFlares.fun = injector::MakeCALL(0x6DF34F, RenderFEFlares, true).get(); // sub_6DE300
			
			injector::MakeCALL(0x7429EB, CarRenderInfo_RenderTextureHeadlights_Hook, true); // CarRenderInfo::Render

			// CarRenderInfo::RenderTextureHeadlights
			injector::MakeRangedNOP(0x738241, 0x73826D, true);
			injector::MakeJMP(0x738241, RenderTextureHeadlightsColorCave, true);
		}

		if (!DisableKitWheelModifications)
		{
			// Apply attributes by hooking CarRenderInfo functions
			injector::MakeCALL(0x760187, CarRenderInfo_UpdateWheelYRenderOffset, true); // CarRenderInfo::CarRenderInfo
			injector::MakeJMP(0x76018C, 0x76020A, true); // Disable vanilla brake markers code as it's now handled in UpdateWheelYRenderOffset

			// Fix tire skid offset and width
			injector::MakeJMP(0x746F33, DoSkidsCave, true); // CarRenderConn::UpdateTires (Fix skid width)

			// Camber
			injector::MakeJMP(0x74EFCF, CamberFrontCave, true); // CarRenderInfo::Render
			injector::MakeJMP(0x74EFE8, CamberRearCave, true); // CarRenderInfo::Render

			// FECompressions
			injector::MakeCALL(0x007A9748, FrontEndRenderingCar_LookupWheelPosition, true);

			// Ride Height
			injector::MakeJMP(0x007471AD, RideHeightCave, true); // CarRenderConn::UpdateRenderMatrix
		}
		
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
	if ((ExpandMemoryPools || CarSkinFix) && !LimitAdjusterCompatibility)
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
		injector::MakeRangedNOP(0x7603EE, 0x760419, true); // CarRenderInfo::CarRenderInfo
		injector::MakeJMP(0x7603EE, AddOnCopsDamageFixCodeCave, true);
	}

	// Always add both ride height values, not just when it's close enough (from chassis and ecar) (ty rx)
	if (RideHeightFix)
	{
		injector::MakeRangedNOP(0x7470AC, 0x7470B2, true); // CarRenderConn::UpdateRenderMatrix
	}

	// (Attempt to) fix a crash with replacing light materials
	if (LightMaterialCrashFix)
	{
		injector::MakeJMP(0x501640, eModel_ReplaceLightMaterial, true); // eModel::ReplaceLightMaterial (18 references)
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

	if (ExitWorkaround)
	{
		injector::WriteMemory<BYTE>(0x6C21FC, 0xEB, true);
	}

	if (TestCareerCustomization)
	{
		injector::WriteMemory<BYTE>(g_bTestCareerCustomization, 1, true);
		injector::MakeJMP(0x7BABDD, 0x7BAC6D, true); // CarCustomizeManager::Checkout (Don't deduct user's cash)
		injector::MakeJMP(0x7BB594, 0x7BB5C8, true); // CustomizeCategoryScreen::AddCustomOption (Ignore backroom parts without markers)
		injector::WriteMemory<BYTE>(0x7B0185, 0xEB, true); // CustomizeShoppingCart::CanCheckout (Allow checkout when there isn't enough cash)
	}

	// Presitter: Dump/load presets when the profile is saved/loaded to work issues around with DBCarPart changes.
	if (Presitter)
	{
		// Get SHGetFolderPathA
		hb_SHGetFolderPathA.fun = injector::GetBranchDestination(0x6CBF17, true).get();

		// Saving
		injector::WriteMemory(0x89CD88, &MemcardCallbacks_SaveDone, true); // MemcardCallbacks::vtable
		hb_MemcardCallbacks_SaveDone.fun = injector::MakeCALL(0x560EC9, MemcardCallbacks_SaveDone, true).get(); // IJoyHelper::EmulateMemoryCardLibrary

		// Loading
		injector::MakeCALL(0x5ACDEB, UserProfile_LoadFromBuffer, true); // cFrontendDatabase::LoadUserProfileFromBuffer
		injector::MakeCALL(0x5ACE01, UserProfile_LoadFromBuffer, true); // cFrontendDatabase::LoadUserProfileFromBuffer
		hb_UserProfile_LoadFromBuffer.fun = injector::MakeCALL(0x5ACE74, UserProfile_LoadFromBuffer, true).get(); // cFrontendDatabase::RestoreFromBackupDB
	}

	// Car Skin Fix (Requires CarSkinCount (20) x dummy skin and wheel textures in CARS\TEXTURES.BIN)
	if (CarSkinFix && !LimitAdjusterCompatibility && !HPCCompatibility)
	{
		// VehicleRenderConn::Load
		injector::MakeNOP(0x75D29E, 2, true); // Skip precomposite skins
		injector::MakeRangedNOP(0x75D2BB, 0x75D2D6, true);
		injector::WriteMemory<unsigned char>(0x75D2B6, CarSkinCount, true); // 4 -> 20

		// RideInfo::SetCompositeNameHash
		injector::MakeRangedNOP(0x747F2B, 0x747F3B, true); // Skip precomposite skins
		injector::MakeJMP(0x747F2B, 0x747F3B, true);
		injector::WriteMemory<unsigned char>(0x747F22, CarSkinCount, true); // 4 -> 20
	}

#ifdef _DEBUG
	injector::WriteMemory<BYTE>(_EnableReleasePrintf, 1, true); //Enable release printf
#endif

	return 0;
}