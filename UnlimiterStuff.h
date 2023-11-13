#include "stdafx.h"
#include "stdio.h"
#include <string>
#include "includes\injector\injector.hpp"
#include "includes\ini.h"

int ManuID, CarArraySize, CarCount, CarPartCount, CarPartPartsTableSize, ReplacementCar, TrafficCarCount, RacerNamesCount, FrameDelay, CarSkinCount;
bool ManuHook, ExtraCustomization, DisappearingWheelsFix, SecondaryLogoFix, ExpandMemoryPools, AddOnCopsDamageFix, ForceStockPartsOnAddOnOpponents, ChallengeSeriesOpponentNameFix, CopDestroyedStringHook, DisableTextureReplacement, MyCarsBackroom, EnableFNGFixes, RandomHook, RideHeightFix, BonusCarsHook, CarSkinFix, LightMaterialCrashFix, DisableNeon, DisableLightFlareColors, DisableKitWheelModifications, ExitWorkaround, Presitter, TestCareerCustomization, LimitAdjusterCompatibility, RandomizeTraffic, ForceSignalsOn, ForceLightsOnInFE, ScalingLightFix, LightTextureSwapInFE, SeperateRims, DisableCameraAutoCenter;

#include "InGameFunctions.h"
#include "GlobalVariables.h"
#include "CustomizeMain.h"
#include "CustomizeSub.h"
#include "CustomizeParts.h"
#include "CustomizePerformance.h"
#include "CustomizeRims.h"
#include "CustomizeSpoiler.h"
#include "CustomizePaint.h"
#include "CustomizeDecals.h"
#include "CustomizeHUDColor.h"
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
#include "GarageMainScreen.h"
#include "Showcase.h"
#include "TireState.h"
#include "CarRenderConn.h"
#include "VehicleRenderConn.h"
#include "Presitter.h"
#include "UserProfile.h"
#include "MemcardCallbacks.h"
#include "Game.h"
#include "Helpers.h"
#include "UnlimiterData.h"
#include "CodeCaves.h"

int Init()
{
	CurrentWorkingDirectory = std::filesystem::current_path();

	auto UnlimiterSettings = CurrentWorkingDirectory / "NFSMWUnlimiterSettings.ini";
	mINI::INIFile NFSMWUnlimiterSettingsINIFile(UnlimiterSettings.string());
	mINI::INIStructure Settings;
	NFSMWUnlimiterSettingsINIFile.read(Settings);

	// Main
	ReplacementCar = mINI_ReadInteger(Settings, "Main", "ReplacementModel", 1);
	//TrafficCarCount = mINI_ReadInteger(Settings, "Main", "TrafficCarCount", 10);
	ManuHook = mINI_ReadInteger(Settings, "Main", "EnableManufacturerHook", 1) != 0;
	ExtraCustomization = mINI_ReadInteger(Settings, "Main", "EnableExtraCustomization", 1) != 0;
	MyCarsBackroom = mINI_ReadInteger(Settings, "Main", "MyCarsBackroom", 1) != 0;
	CopDestroyedStringHook = mINI_ReadInteger(Settings, "Main", "EnableCopDestroyedStringHook", 1) != 0;
	RandomHook = mINI_ReadInteger(Settings, "Main", "EnableRandomPartsHook", 1) != 0;
	BonusCarsHook = mINI_ReadInteger(Settings, "Main", "EnableBonusCarsHook", 0) != 0;
	Presitter = mINI_ReadInteger(Settings, "Main", "EnablePresitter", 1) != 0;
	RandomizeTraffic = mINI_ReadInteger(Settings, "Main", "RandomizeTraffic", 1) != 0;
	SeperateRims = mINI_ReadInteger(Settings, "Main", "SeperateRims", 1) != 0;

	// Fixes
	DisappearingWheelsFix = mINI_ReadInteger(Settings, "Fixes", "DisappearingWheelsFix", 1) != 0;
	SecondaryLogoFix = mINI_ReadInteger(Settings, "Fixes", "SecondaryLogoFix", 1) != 0;
	AddOnCopsDamageFix = mINI_ReadInteger(Settings, "Fixes", "AddOnCopsDamageFix", 1) != 0;
	ChallengeSeriesOpponentNameFix = mINI_ReadInteger(Settings, "Fixes", "ChallengeSeriesOpponentNameFix", 1) != 0;
	LightMaterialCrashFix = mINI_ReadInteger(Settings, "Fixes", "LightMaterialCrashFix", 0) != 0;
	RideHeightFix = mINI_ReadInteger(Settings, "Fixes", "RideHeightFix", 1) != 0;
	EnableFNGFixes = mINI_ReadInteger(Settings, "Fixes", "FNGFix", 0) != 0;
	CarSkinFix = mINI_ReadInteger(Settings, "Fixes", "CarSkinFix", 1) != 0;
	ScalingLightFix = mINI_ReadInteger(Settings, "Fixes", "ScalingLightFix", 1) != 0;

	// Misc
	ExpandMemoryPools = mINI_ReadInteger(Settings, "Misc", "ExpandMemoryPools", 1) != 0;
	FrameDelay = mINI_ReadInteger(Settings, "Misc", "FrameDelay", -1);
	ForceStockPartsOnAddOnOpponents = mINI_ReadInteger(Settings, "Misc", "ForceStockPartsOnAddOnOpponents", 0) != 0;
	ForceLightsOnInFE = mINI_ReadInteger(Settings, "Misc", "ForceLightsOnInFE", 0) != 0;
	LightTextureSwapInFE = mINI_ReadInteger(Settings, "Misc", "LightTextureSwapInFE", 1) != 0;
	CarSkinCount = mINI_ReadInteger(Settings, "Misc", "CarSkinCount", 20);
	DisableCameraAutoCenter = mINI_ReadInteger(Settings, "Misc", "DisableCameraAutoCenter", 0) != 0;

	// Debug
	DisableTextureReplacement = mINI_ReadInteger(Settings, "Debug", "DisableTextureReplacement", 0) != 0;
	DisableNeon = mINI_ReadInteger(Settings, "Debug", "DisableNeon", 0) != 0;
	DisableLightFlareColors = mINI_ReadInteger(Settings, "Debug", "DisableLightFlareColors", 0) != 0;
	DisableKitWheelModifications = mINI_ReadInteger(Settings, "Debug", "DisableKitWheelModifications", 0) != 0;
	ExitWorkaround = mINI_ReadInteger(Settings, "Debug", "ExitWorkaround", 1) != 0;
	TestCareerCustomization = mINI_ReadInteger(Settings, "Debug", "TestCareerCustomization", 0) != 0;
	ForceSignalsOn = mINI_ReadInteger(Settings, "Debug", "ForceSignalsOn", 0) != 0;

	// Check compatibility
	BETACompatibility = GetModuleHandleA("NFSMWBeta.asi") ? 1 : 0;
	HPCCompatibility = GetModuleHandleA("NFSMWHPC.asi") ? 1 : 0;
	LimitAdjusterCompatibility = GetModuleHandleA("NFSMWLimitAdjuster.asi") ? 1 : 0;

	// Count Cars Automatically
	injector::MakeJMP(0x756AA7, DoUnlimiterStuffCodeCave, true); // LoaderCarInfo
	injector::MakeJMP(0x756BC7, DoUnlimiterStuffCodeCave2, true); // LoaderCarInfo

	injector::MakeJMP(0x7398D0, CarPartDatabase_GetCarType, true); // 9 references

	// Car Type Unlimiter
	injector::MakeJMP(0x6690BB, CarCountCodeCave_PVehicle_Resource_Resource, true);
	injector::MakeJMP(0x7398A6, CarCountCodeCave_sub_7398A0, true);
	injector::MakeJMP(0x73995B, CarCountCodeCave_GetCarTypeInfoFromHash, true);
	injector::MakeJMP(0x7515FB, CarCountCodeCave_sub_7515D0, true);
	injector::MakeJMP(0x759913, CarCountCodeCave_RideInfo_FillWithPreset, true);
	injector::MakeJMP(0x75E6F4, CarCountCodeCave_CarRenderConn_Construct, true);
	injector::MakeJMP(0x75E7B4, CarCountCodeCave_HeliRenderConn_Construct, true);
	injector::MakeJMP(0x7B3877, CarCountCodeCave_DebugCarCustomizeScreen_BuildOptionsLists, true);

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
	if (MyCarsBackroom && !ExtraCustomization)
	{
		injector::MakeNOP(0x7BFF28, 6, true); // CustomizeMain::NotificationMessage - Switch to Backroom Menu
		injector::MakeNOP(0x7BFD56, 2, true); // CustomizeMain::NotificationMessage - Fix backing out by checking for backroom instead of career mode
		injector::WriteMemory(0x7BFD52, g_bCustomizeInBackRoom, true); // CustomizeMain::NotificationMessage - Fix backing out by checking for backroom instead of career mode
		injector::MakeJMP(0x7B1226, MyCarsBackroomWidgetCodeCave, true); // CustomizeMain::RefreshHeader
		injector::MakeJMP(0x7BFE2F, MyCarsBackroomEscCodeCave, true); // CustomizeMain::NotificationMessage
		injector::MakeJMP(0x7BFCC2, MyCarsBackroomRoomChangeCodeCave, true); // CustomizeMain::SwitchRooms
		injector::MakeJMP(0x7A60F0, MyCarsBackroomRoomChangeCodeCave2, true); // CustomizeShoppingCart::ExitShoppingCart
		injector::MakeNOP(0x7B92C8, 6, true); // CustomizePerformance::Setup - Fix Junkman Parts
	}
	
	// Extra Customization Stuff
	if (ExtraCustomization || HPCCompatibility)
	{
		// Hook customize main
		injector::MakeCALL(0x7BFCEC, CustomizeMain_BuildOptionsList, true); // CustomizeMain::SwitchRooms
		injector::MakeCALL(0x7C0055, CustomizeMain_BuildOptionsList, true); // CustomizeMain::Setup
		injector::WriteMemory(0x8B808C, &CustomizeMain_NotificationMessage, true); // CustomizeMain::vtable
		injector::WriteMemory(0x8B8094, &CustomizeMain_RefreshHeader, true); // CustomizeMain::vtable

		//injector::MakeNOP(0x7B123D, 2, true); // CustomizeMain::RefreshHeader - Backroom HUD Widget (BMWM3GTRE46)
		//injector::MakeNOP(0x7BFF49, 6, true); // CustomizeMain::NotificationMessage - Switch to Backroom Menu (BMWM3GTRE46)
		//injector::MakeNOP(0x7B92DC, 6, true); // CustomizePerformance::Setup - Backroom Performance Parts (BMWM3GTRE46)
		//injector::MakeNOP(0x7BC28C, 2, true); // CustomizeSub::SetupVisual - Rim Paint (BMWM3GTRE46)

		injector::WriteMemory(0x8B8058, &CustomizeSub_NotificationMessage, true); // CustomizeSub::vtable
		injector::WriteMemory(0x8B8064, &CustomizeSub_Setup, true);
		injector::MakeCALL(0x7C29D7, CustomizeSub_Setup, true); // Add new options
		injector::MakeJMP(0x7A5F40, FEShoppingCartItem_GetCarPartCatHash, true); // Add the new names for shopping cart, 18 calls

		// Camera Hook
		injector::MakeCALL(0x7B9FDC, FindScreenInfo, true); // GarageMainScreen::HandleTick
		injector::MakeCALL(0x7B9FE4, FindScreenCameraInfo, true); // GarageMainScreen::HandleTick
		injector::MakeJMP(0x7A2380, CamUserRotateCodeCave_GarageMainScreen_HandleJoyEvents, true); // Disable cam rotation via keyboard, GarageMainScreen::HandleJoyEvents
		injector::WriteMemory<BYTE>(0x7BA070, 0x4B, true); // Check angle's (ebx+5a) cam_user_rotate instead of screen's (eax+5a), GarageMainScreen::HandleTick

		// Showcase mode check
		injector::MakeCALL(0x570D56, Showcase_ctor_Hook, true); // CreateShowcase
		injector::MakeCALL(0x7AEA93, Showcase_dtor_Hook, true); // Showcase::~Showcase

		// Texture caves
		if (!DisableTextureReplacement)
		{
			//injector::MakeJMP(0x737E26, TextureReplacementCodeCave, true); // Add texture replacements to the table
			//injector::MakeJMP(0x75230D, UsedCarTextureInfoCodeCave, true); // Allow custom texture names for interior in UsedCarTexture table
			injector::MakeCALL(0x74E49B, CarRenderInfo_UpdateLightStateTextures, true); // CarRenderInfo::Render
			injector::MakeCALL(0x75FC48, CarRenderInfo_UpdateCarReplacementTextures, true); // CarRenderInfo::ctor
			injector::MakeJMP(0x751860, GetUsedCarTextureInfo, true); // 5 references

			injector::MakeJMP(0x74DA9F, 0x74DADD, true); // Free up texture replacement slots #47-72 instead of assigning unused leftover decal stuff, CarRenderInfo::UpdateDecalTextures
			// Resize TexturesToLoadPerm and Temp
			injector::WriteMemory<int>(0x739F0C, MaxPermTex * 4, true); // PrintUsedCarTextureInfo (0 references)
			injector::WriteMemory<int>(0x752917, 12 + MaxPermTex * 4, true); // LoadedSkin::GetTextureHashes (esp+0x168)
			injector::WriteMemory<int>(0x75BD7F, 1576 + MaxPermTex * 4, true); // CarLoader::AllocateRideInfo (esp+0x784)
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

		// CarCustomizeManager
		injector::MakeJMP(0x7A50E0, CarCustomizeManager_IsCategoryNew, true); // 10 references
		injector::MakeJMP(0x7A4FF0, CarCustomizeManager_IsPartNew, true); // 3 references
		injector::MakeJMP(0x7A4E50, CarCustomizeManager_IsPartLocked, true); // 11 references
		injector::MakeJMP(0x7B60E0, CarCustomizeManager_IsRimCategoryLocked, true); // 2 references
		injector::MakeJMP(0x7B6250, CarCustomizeManager_IsVinylCategoryLocked, true); // 2 references
		injector::MakeJMP(0x7BAD10, CarCustomizeManager_IsCategoryLocked, true); // 8 references

		// Remove locked & new status from new categories
		// injector::MakeNOP(0x7A50F9, 6, true); // CarCustomizeManager::IsCategoryNew, Parts category
		// injector::MakeJMP(0x7A50F9, IsNewCodeCaveParts, true); // CarCustomizeManager::IsCategoryNew, Parts category
		// injector::MakeNOP(0x7A51D9, 6, true); // CarCustomizeManager::IsCategoryNew, Visual category
		// injector::MakeJMP(0x7A51D9, IsNewCodeCaveVisual, true); // CarCustomizeManager::IsCategoryNew, Visual category
		// injector::MakeNOP(0x7BAD34, 6, true); // CarCustomizeManager::IsCategoryLocked, Parts category
		// injector::MakeJMP(0x7BAD34, IsLockedCodeCaveParts, true); // CarCustomizeManager::IsCategoryLocked, Parts category
		// injector::MakeNOP(0x7BAEE0, 6, true); // CarCustomizeManager::IsCategoryLocked, Visual category
		// injector::MakeJMP(0x7BAEE0, IsLockedCodeCaveVisual, true); // CarCustomizeManager::IsCategoryLocked, Visual category

		// Paint
		injector::WriteMemory(0x8B806C, &CustomizePaint_NotificationMessage, true); // CustomizePaint::vtable
		injector::WriteMemory(0x8B8074, &CustomizePaint_RefreshHeader, true); // CustomizePaint::vtable
		injector::MakeCALL(0x7C2ADF, CustomizePaint_Setup, true); // CustomizePaint::CustomizePaint
		injector::WriteMemory(0x8B8078, &CustomizePaint_Setup, true); // CustomizePaint::vtable
		injector::MakeJMP(0x7B8040, CustomizePaint_BuildSwatchList, true); // 6 references
		//injector::MakeCALL(0x7C0612, CustomizePaint_ScrollFilters, true); // CustomizePaint::NotificationMessage
		//injector::MakeCALL(0x7C0926, CustomizePaint_ScrollFilters, true); // CustomizePaint::NotificationMessage
		injector::MakeCALL(0x7C0AF9, CustomizePaint_SetupVinylColor, true); // CustomizePaint::Setup
		injector::WriteMemory(0x7AEB22, &Showcase_FromColor, true); // CarCustomizeManager::RelinquishControl
		injector::WriteMemory(0x7C3784, &Showcase_FromColor, true); // CarCustomizeManager::TakeControl


		// Decals
		injector::MakeJMP(0x7A7030, CustomizeDecals_GetSlotIDFromCategory, true); // 3 references
		injector::WriteMemory<int>(0x7BCF14, 0x608, true); // CustomizationScreen::CustomizationScreen

		// HUD Color
		injector::WriteMemory(0x8B7ED0, &CustomizeHUDColor_RefreshHeader, true); // CustomizeHUDColor::vtable
		injector::MakeCALL(0x7BD874, CustomizeHUDColor_ScrollColors, true); // CustomizeHUDColor::NotificationMessage
		injector::MakeCALL(0x7BD8B9, CustomizeHUDColor_ScrollColors, true); // CustomizeHUDColor::NotificationMessage
		injector::MakeCALL(0x7BD8F7, CustomizeHUDColor_BuildColorOptions_Hook, true); // CustomizeHUDColor::NotificationMessage
		injector::MakeCALL(0x7BDABA, CustomizeHUDColor_BuildColorOptions_Hook, true); // CustomizeHUDColor::NotificationMessage

		// Shopping Cart Text
		injector::MakeCALL(0x7BB17B, FEShoppingCartItem_DrawPartName, true); // FEShoppingCartItem::Draw

		// LOD Forcing option
		injector::MakeJMP(0x751540, CarPart_GetModelNameHash, true); // 6 references

		// Rims (Counts are initialized in UnlimiterData.h)
		injector::MakeNOP(0x7A539F, 6, true); // CarCustomizeManager::IsCategoryNew, Rims category
		injector::MakeJMP(0x7A539F, IsNewCodeCaveRims, true); // CarCustomizeManager::IsCategoryNew, Rims category
		injector::WriteMemory(0x8B7FE0, &CustomizeRims_NotificationMessage, true); // CustomizeRims::vtable
		injector::WriteMemory(0x8B7FE8, &CustomizeRims_RefreshHeader, true); // CustomizeRims::vtable
		injector::WriteMemory(0x8B7FEC, &CustomizeRims_Setup, true); // CustomizeRims::vtable
		injector::MakeCALL(0x7C039E, CustomizeRims_Setup, true); // CustomizeRims::CustomizeRims
		injector::MakeCALL(0x7BDB3A, CustomizeRims_BuildRimsList, true); // CustomizeRims::ScrollRimSizes
		injector::MakeCALL(0x7BDB4F, CustomizeRims_BuildRimsList, true); // CustomizeRims::ScrollRimSizes
		
		// Vinyls (Counts are initialized in UnlimiterData.h)

		// Fix rear rims
		injector::MakeCALL(0x7498D0, CompositeRim, true); // CompositeSkin
		injector::MakeCALL(0x751A85, GetTempCarSkinTextures, true); // GetUsedCarTextureInfo
		injector::WriteMemory<DWORD>(0x7529CD, 0x154, true); // LoadedWheel::LoadedWheel, Seperate rear rims and fix them in game
		injector::MakeJMP(0x74F40B, RearWheelLightMaterialCodeCave, true); // CarRenderInfo::Render

		// Custom part costs
		injector::MakeJMP(0x7AEF70, CarCustomizeManager_GetPartPrice, true); // 4 references
		injector::MakeCALL(0x7B16BE, UnlockSystem_GetCarPartCost, true); // CustomizationScreen::RefreshHeader

		// Custom unlock conditions
		injector::MakeCALL(0x7A4F96, UnlockSystem_IsCarPartUnlocked, true); // CarCustomizeManager::IsPartLocked
		injector::MakeCALL(0x7AF673, UnlockSystem_IsCarPartUnlocked, true); // CarCustomizeManager::GetCarPartList

		// Text
		injector::MakeJMP(0x7B8556, GetUnlockHashCodeCave_CustomizeDecals_BuildDecalList, true); // CustomizeDecals::BuildDecalList
		// Parts, Spoilers, Rims, Paints and Decals are done in their respective build functions
		// Performance parts cannot have CarPart attributes

		// Custom FECooling (heat level multipliers)
		injector::MakeJMP(0x7AF330, CarCustomizeManager_UpdateHeatOnVehicle, true); // 4 references

		// Damage lights
		injector::MakeCALL(0x74293C, CarRenderInfo_SetPlayerDamage_Hook, true); // CarRenderInfo::SetDamageInfo

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
			injector::MakeCALL(0x75FD31, CarRenderInfo_CreateCarLightFlares, true); // CarRenderInfo::CarRenderInfo
			injector::MakeCALL(0x744EEA, CarRenderInfo_RenderFlaresOnCar, true); // VehicleRenderConn::RenderFlares
			injector::MakeCALL(0x7450E8, CarRenderInfo_RenderFlaresOnCar, true); // VehicleRenderConn::RenderFlares

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
			injector::WriteMemory(0x8B5268, &CarRenderConn_OnLoaded, true); // CarRenderConn::vtable (Fix offsets)
			injector::MakeJMP(0x746F33, DoSkidsCave_CarRenderConn_UpdateTires, true); // CarRenderConn::UpdateTires (Fix skid width)

			// Camber
			injector::MakeJMP(0x74EFCF, CamberFrontCave, true); // CarRenderInfo::Render
			injector::MakeJMP(0x74EFE8, CamberRearCave, true); // CarRenderInfo::Render
			injector::MakeNOP(0x74EFC3, 2, true); // CarRenderInfo::Render, Allow camber for LODs

			// FECompressions
			injector::MakeCALL(0x7A9748, FrontEndRenderingCar_LookupWheelPosition, true);

			// Radius
			injector::MakeCALL(0x7A9769, FrontEndRenderingCar_LookupWheelRadius, true);

			// Ride Height
			injector::MakeJMP(0x007471AD, RideHeightCave, true); // CarRenderConn::UpdateRenderMatrix

			// Extra Pitch
			injector::MakeJMP(0x74717A, ExtraPitchCave_CarRenderConn_UpdateRenderMatrix, true); // CarRenderConn::UpdateRenderMatrix
			
			// Extra Rear Tire Offset
			injector::MakeJMP(0x74F2FF, ExtraRearTireOffsetCave_CarRenderInfo_Render, true); // CarRenderInfo::Render

			// Reflection Offset & Extra Pitch pt.2
			injector::MakeCALL(0x6DEF16, RenderFrontEndCars, true);
			injector::MakeCALL(0x6DEF96, RenderFrontEndCars, true);

			// Fix lighting
			if (ScalingLightFix)
			{
				injector::MakeCALL(0x74F62E, elCloneLightContext, true); // CarRenderInfo::Render
				injector::MakeCALL(0x74F7D6, elCloneLightContext, true); // CarRenderInfo::Render
				injector::MakeCALL(0x74F968, elCloneLightContext, true); // CarRenderInfo::Render
				injector::MakeCALL(0x74FBC4, elCloneLightContext, true); // CarRenderInfo::Render
			}

			// Scale brakes with rims
			injector::MakeJMP(0x74FFD1, ScaleBrakesCave_FrontLeft_eViewPlatInterface_Render, true); // CarRenderInfo::Render
			injector::MakeJMP(0x750181, ScaleBrakesCave_FrontRight_eViewPlatInterface_Render, true); // CarRenderInfo::Render
			injector::MakeJMP(0x75033B, ScaleBrakesCave_RearRight_eViewPlatInterface_Render, true); // CarRenderInfo::Render
			injector::MakeJMP(0x7504AC, ScaleBrakesCave_RearLeft_eViewPlatInterface_Render, true); // CarRenderInfo::Render
			injector::MakeJMP(0x75051A, ScaleBrakesCave_RearLeftFE_eViewPlatInterface_Render, true); // CarRenderInfo::Render
		}
		
	}

	if (ExtraCustomization || MyCarsBackroom || TestCareerCustomization)
	{
		injector::MakeJMP(0x7A65C0, CustomizeMain_SetScreenNames, true); // 2 references

		// Shopping cart screen switching fix
		injector::MakeJMP(0x7A60E0, CustomizeShoppingCart_ExitShoppingCart, true); // 3 references
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
	if ((ExpandMemoryPools || CarSkinFix || RandomizeTraffic) && !LimitAdjusterCompatibility)
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
	if (EnableFNGFixes)
	{
		injector::MakeCALL(0x5C4D64, CloneObjectstoShowMoreItemsInMenu, true); // FEPackageReader::Load
	}

	// Bonus Cars Hook
	if (BonusCarsHook)
	{
		// Done in UnlimiterData.h, LoadBonusCars

		// Skip RefreshBonusCarsList function, use regular checks instead. (Fixes crashes)
		injector::WriteMemory<BYTE>(0x7BF7E5, 0xEB, true); // UIQRCarSelect::RefreshCarList
		injector::WriteMemory<BYTE>(0x7BF95B, 0x01, true); // UIQRCarSelect::RefreshCarList, skip sorting by unlocks if the category is Bonus
		// LAN / Online
		injector::WriteMemory<BYTE>(0x55657D, 0xEB, true); // UIOLGameRoomCarSelect::RefreshCarList
		injector::WriteMemory<BYTE>(0x556677, 0x01, true); // UIOLGameRoomCarSelect::RefreshCarList, skip sorting by unlocks if the category is Bonus

	}

	if (ExitWorkaround)
	{
		injector::WriteMemory<BYTE>(0x6C21FC, 0xEB, true);
	}

	if (TestCareerCustomization)
	{
		injector::WriteMemory<BYTE>(g_bTestCareerCustomization, 1, true);
		injector::MakeJMP(0x7BABDD, 0x7BAC6D, true); // CarCustomizeManager::Checkout (Don't deduct user's cash)
		injector::WriteMemory<BYTE>(0x7BB594, 0xEB, true); // CustomizeCategoryScreen::AddCustomOption (Ignore backroom parts without markers)
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

		// Deleting
		hb_rmdir.fun = injector::MakeCALL(0x7F58EB, Presitter_Delete, true).get(); // RealmcIface::MemcardInterfaceImpl::ProcessDelete
	}

	// Random Traffic Colors
	if (RandomizeTraffic)
	{
		injector::MakeCALL(0x75D2F6, RideInfo_SetStockParts_Traffic, true); // VehicleRenderConn::Load
		injector::MakeCALL(0x6690C1, CarInfo_IsSkinned_Traffic, true); // PVehicle::Resource::Resource
		injector::MakeCALL(0x75D285, CarInfo_IsSkinned_Traffic, true); // VehicleRenderConn::Load
	}

	// Car Skin Fix (Requires CarSkinCount (20) x dummy skin and wheel textures in CARS\TEXTURES.BIN)
	if ((CarSkinFix || RandomizeTraffic) && !LimitAdjusterCompatibility)
	{
		// VehicleRenderConn::Load
		injector::MakeRangedNOP(0x75D291, 0x75D298, true); // Skip precomposite skins
		injector::MakeRangedNOP(0x75D29E, 0x75D2D6, true);
		//injector::WriteMemory<unsigned char>(0x75D2B6, CarSkinCount, true); // 4 -> 20
		injector::MakeJMP(0x75D29E, CarSkinCountCodeCave_VehicleRenderConn_Load, true);

		/*
		// RideInfo::SetCompositeNameHash
		injector::MakeRangedNOP(0x747F2B, 0x747F3B, true); // Skip precomposite skins
		injector::MakeJMP(0x747F2B, 0x747F3B, true);
		injector::WriteMemory<unsigned char>(0x747F22, CarSkinCount, true); // 4 -> 20
		*/

		injector::MakeCALL(0x75D2EE, RideInfo_SetCompositeNameHash, true); // VehicleRenderConn::Load
		injector::MakeCALL(0x7A27CB, RideInfo_SetCompositeNameHash, true); // GarageCarLoader::LoadRideInfo
	}

	if (DisableCameraAutoCenter)
	{
		injector::MakeJMP(0x476FFA, DisableAutoCenterCodeCave_SelectCarCameraMover_SetZoomSpeed, true); // Disable rotation before user's input
	}

#ifdef _DEBUG
	injector::WriteMemory<BYTE>(_EnableReleasePrintf, 1, true); //Enable release printf
#endif

	return 0;
}