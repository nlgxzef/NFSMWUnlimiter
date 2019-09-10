#include "stdafx.h"
#include "stdio.h"
#include <string>
#include <windows.h>
#include "includes\injector\injector.hpp"
#include "includes\IniReader.h"

#define CarTypeInfoArray 0x9B09D8
#define SingleCarTypeInfoBlockSize 0xD0

int CarArraySize, CarCount, ReplacementCar, TrafficCarCount;
bool ManuHook, DisappearingWheelsFix, SecondaryLogoFix, ExpandMemoryPools, AddOnCopsDamageFix, AddOnOpponentsPartsFix;
int ManuID;

DWORD Attrib_Instance_dtInstance = 0x45A430;
DWORD RideInfo_SetStockParts = 0x7594A0;

char* GetManuNameFromID()
{
	CIniReader Manu("NFSMWUnlimiterSettings.ini");
	char* num;
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
		mov dword ptr ds : [esp + 0x1C], 0xFFFFFFFF
		call Attrib_Instance_dtInstance
		mov ecx, [esp + 14]
		call GetManuNameFromID
		mov fs : [00000000], ecx
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

		caveexit:
			push 0x6690C0
			retn

		jump_66910D:
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
		cmp eax,4 // COPHELI
		je jWindowDamage
		cmp eax,0x33 // COPMIDSIZEINT
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
		cmp [esi], 84
		jge jLessRandomParts // 84+ = Add-On
		jmp jNormalRandomParts

		jLessRandomParts:
			push 0x75B2EF
			retn

		jNormalRandomParts:
			push 0x75B228
			retn
	}
}

int Init()
{
	CIniReader Settings("NFSMWUnlimiterSettings.ini");

	// Main
	//CarCount = Settings.ReadInteger("Main", "CarModelIDLimit", 127);
	ReplacementCar = Settings.ReadInteger("Main", "ReplacementModel", 127);
	TrafficCarCount = Settings.ReadInteger("Main", "TrafficCarCount", 20);
	ManuHook = Settings.ReadInteger("Main", "EnableManufacturerHook", 1) == 1;
	// Fixes
	DisappearingWheelsFix = Settings.ReadInteger("Fixes", "DisappearingWheelsFix", 1) == 1;
	SecondaryLogoFix = Settings.ReadInteger("Fixes", "SecondaryLogoFix", 1) == 1;
	AddOnCopsDamageFix = Settings.ReadInteger("Fixes", "AddOnCopsDamageFix", 1) == 1;
	AddOnOpponentsPartsFix = Settings.ReadInteger("Fixes", "AddOnOpponentsPartsFix", 1) == 1;
	// Misc
	ExpandMemoryPools = Settings.ReadInteger("Misc", "ExpandMemoryPools", 0) == 1;

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

	// Traffic Pattern Unlimiter
	injector::WriteMemory<BYTE>(0x439B79, TrafficCarCount, true); // AITrafficManager::SpawnTraffic
	injector::WriteMemory<BYTE>(0x410962, TrafficCarCount, true); // AITrafficManager::SetTrafficPattern
	injector::WriteMemory<BYTE>(0x4265C0, TrafficCarCount, true); // AITrafficManager::FlushAllTraffic
	injector::WriteMemory<BYTE>(0x426254, TrafficCarCount, true); // AITrafficManager::NextSpawn
	injector::WriteMemory<int>(0x426256, TrafficCarCount, true); // AITrafficManager::NextSpawn
	
	// Manufacturer logo hook
	if (ManuHook)
	{
		injector::MakeJMP(0x005817C1, CarManuCodeCave, true);
		injector::MakeRangedNOP(0x581B69, 0x581B6E, true); // Prevent returning null
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

	return 0;
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
		IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
		IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

		if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x7C4040) // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
		{
			Init();
		}
		else
		{
			MessageBoxA(NULL, "This .exe is not supported.\nPlease use v1.3 speed.exe (5,75 MB (6.029.312 bytes)).", "NFSMW Unlimiter", MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;
}
