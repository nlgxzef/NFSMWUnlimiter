#include "stdafx.h"
#include "stdio.h"
#include <string>
#include <windows.h>
#include "includes\injector\injector.hpp"
#include "includes\IniReader.h"

int ManuID, CarArraySize, CarCount, ReplacementCar, TrafficCarCount, RacerNamesCount;
bool ManuHook, ExtraCustomization, DisappearingWheelsFix, SecondaryLogoFix, ExpandMemoryPools, AddOnCopsDamageFix, AddOnOpponentsPartsFix, ChallengeSeriesOpponentNameFix, BETACompatibility, CopDestroyedStringHook, DisableTextureReplacement, MyCarsBackroom, FNGFix;

#include "InGameFunctions.h"
#include "CustomizeMain.h"
#include "CustomizeSub.h"
#include "CustomizeParts.h"
#include "CustomizeRims.h"
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

char num[4];

char* GetManuNameFromID()
{
	CIniReader Manu("UnlimiterData\\_CarManufacturers.ini");
	sprintf(num, "%d", ManuID);

	return Manu.ReadString("Manufacturers", num, "DEFAULT");
}

bool IsCop(BYTE CarTypeID)
{
	return *(BYTE*)((*(DWORD*)CarTypeInfoArray) + CarTypeID * SingleCarTypeInfoBlockSize + 0x94) == 1;
}

void __declspec(naked) CarManuCodeCave()
{
	__asm
	{
		mov ManuID, eax // Get manu Id to global var

		lea ecx, [esp]
		mov dword ptr ds : [esp + 0x1C] , 0xFFFFFFFF
		call Attrib_Instance_dtInstance
		mov ecx, [esp + 14]
		call GetManuNameFromID
		mov fs : [00000000] , ecx
		add esp, 0x20
		ret
	}
}

void __declspec(naked) CarCountCodeCave_PVehicle_Resource_Resource()
{
	__asm
	{
		cmp eax, CarCount
		jnl jump_66910D

		caveexit :
		push 0x6690C0
			retn

			jump_66910D :
		push 0x66910D
			retn
	}
}

void __declspec(naked) CarCountCodeCave_sub_7398A0()
{
	__asm
	{
		cmp ecx, CarCount
		je jump_7398CB

		caveexit :
		push 0x7398AB
			retn

			jump_7398CB :
		push 0x7398CB
			retn
	}
}

void __declspec(naked) CarCountCodeCave_GetCarTypeInfoFromHash()
{
	__asm
	{
		cmp eax, CarCount
		jl jump_739950

		caveexit :
		push 0x739960
			retn

			jump_739950 :
		push 0x739950
			retn
	}
}

void __declspec(naked) CarCountCodeCave_sub_7515D0()
{
	__asm
	{
		cmp eax, CarCount
		jl jump_7515F0

		caveexit :
		push 0x751600
			retn

			jump_7515F0 :
		push 0x7515F0
			retn
	}
}

void __declspec(naked) CarCountCodeCave_RideInfo_FillWithPreset()
{
	__asm
	{
		cmp ecx, CarCount
		jl jump_759908

		caveexit :
		push 0x759918
			retn

			jump_759908 :
		push 0x759908
			retn
	}
}

void __declspec(naked) CarCountCodeCave_CarRenderConn_Construct()
{
	__asm
	{
		cmp esi, CarCount
		jnl jump_75E736

		caveexit :
		push 0x75E6F9
			retn

			jump_75E736 :
		push 0x75E736
			retn
	}
}

void __declspec(naked) CarCountCodeCave_HeliRenderConn_Construct()
{
	__asm
	{
		cmp esi, CarCount
		jnl jump_75E7F6

		caveexit :
		push 0x75E7B9
			retn

			jump_75E7F6 :
		push 0x75E7F6
			retn
	}
}

void __declspec(naked) DoUnlimiterStuffCodeCave()
{
	// Get count
	__asm
	{
		mov dword ptr ds : [CarTypeInfoArray] , esi
		sub esi, 0x0C
		mov esi, [esi]
		mov CarArraySize, esi
		mov esi, dword ptr ds : [CarTypeInfoArray]
		pushad
	}

	CarArraySize -= 8;
	CarCount = CarArraySize / SingleCarTypeInfoBlockSize;

	// Do required stuff
	injector::WriteMemory<int>(0x739900, CarCount * SingleCarTypeInfoBlockSize, true); // CarPartDatabase::GetCarType
	injector::WriteMemory<int>(0x7B3879, CarCount * SingleCarTypeInfoBlockSize, true); // DebugCarCustomizeScreen::BuildOptionsLists

	// Continue
	__asm
	{
		popad
		push 0x756AAD
		retn
	}
}

void __declspec(naked) AddOnCopsDamageFixCodeCave()
{
	__asm
	{
		cmp eax, 4 // COPHELI
		je jWindowDamage
		cmp eax, 0x33 // COPMIDSIZEINT
		je jWindowDamage
		push eax // Car Type ID
		call IsCop
		add esp, 4
		cmp al, 1
		je jDamageParts
		jmp jWindowDamage

		jDamageParts :
		push 0x76041B
			retn

			jWindowDamage :
		push 0x76044F
			retn
	}
}

void __declspec(naked) ForceStockPartsOnAddOnsCodeCave()
{
	__asm
	{
		call RideInfo_SetStockParts
		cmp[esi], 84
		jge jLessRandomParts // 84+ = Add-On
		jmp jNormalRandomParts

		jLessRandomParts :
		push 0x75B2EF
			retn

			jNormalRandomParts :
		push 0x75B228
			retn
	}
}

void __declspec(naked) ReplacementCarCodeCave_CarLoader_Load()
{
	_asm
	{
		mov edx, ReplacementCar
		mov[ebx], edx
		push 0x0075C717
		retn
	}
}

int Init()
{
	CIniReader Settings("NFSMWUnlimiterSettings.ini");

	// Main
	ReplacementCar = Settings.ReadInteger("Main", "ReplacementModel", 1);
	TrafficCarCount = Settings.ReadInteger("Main", "TrafficCarCount", 10);
	ManuHook = Settings.ReadInteger("Main", "EnableManufacturerHook", 1) == 1;
	ExtraCustomization = Settings.ReadInteger("Main", "EnableExtraCustomization", 1) == 1;
	MyCarsBackroom = Settings.ReadInteger("Main", "MyCarsBackroom", 1) == 1;
	CopDestroyedStringHook = Settings.ReadInteger("Main", "EnableCopDestroyedStringHook", 1) == 1;
	// Fixes
	DisappearingWheelsFix = Settings.ReadInteger("Fixes", "DisappearingWheelsFix", 1) == 1;
	SecondaryLogoFix = Settings.ReadInteger("Fixes", "SecondaryLogoFix", 1) == 1;
	AddOnCopsDamageFix = Settings.ReadInteger("Fixes", "AddOnCopsDamageFix", 1) == 1;
	AddOnOpponentsPartsFix = Settings.ReadInteger("Fixes", "AddOnOpponentsPartsFix", 1) == 1;
	ChallengeSeriesOpponentNameFix = Settings.ReadInteger("Fixes", "ChallengeSeriesOpponentNameFix", 1) == 1;
	FNGFix = Settings.ReadInteger("Fixes", "FNGFix", 1) == 1;
	// Misc
	ExpandMemoryPools = Settings.ReadInteger("Misc", "ExpandMemoryPools", 0) == 1;
	BETACompatibility = Settings.ReadInteger("Misc", "BETACompatibility", 0) == 1;
	// Debug
	DisableTextureReplacement = Settings.ReadInteger("Debug", "DisableTextureReplacement", 0) == 1;

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
	if (ExtraCustomization)
	{
		// Enable All Customizations For All Cars
		injector::MakeNOP(0x7BCDD0, 2, true); // CustomizeMain::BuildOptionsList - My Cars (BMWM3GTRE46)
		injector::MakeNOP(0x7BCE33, 2, true); // CustomizeMain::BuildOptionsList - Backroom (BMWM3GTRE46)
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

		// Fix Service Crash
		injector::MakeJMP(0x6E9E40, SimConnectionService, true); //Sim::Connection::Service
	}
	
	// Check the ini file for destroyed cops messages
	if (CopDestroyedStringHook)
	{
		injector::WriteMemory(0x8A2454, &PursuitBoard_SetNumCopsDestroyed, true);
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

	// Damage Parts Fix for Add-On Cop Cars
	if (AddOnCopsDamageFix)
	{
		injector::MakeRangedNOP(0x7603EE, 0x760419, true);
		injector::MakeJMP(0x7603EE, AddOnCopsDamageFixCodeCave, true);
	}

	// Force Stock Parts for Add-On Cars to fix Missing Parts on Opponents' Cars
	if (AddOnOpponentsPartsFix)
	{
		injector::MakeJMP(0x75B223, ForceStockPartsOnAddOnsCodeCave, true);
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

	return 0;
}