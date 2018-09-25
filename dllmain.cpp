#include "stdafx.h"
#include "stdio.h"
#include <string>
#include <windows.h>
#include "includes\injector\injector.hpp"
#include "includes\IniReader.h"

int CarCount, ReplacementCar;
bool ManuHook, DisappearingWheelsFix, SecondaryLogoFix, ExpandMemoryPools;
int ManuID;

DWORD Attrib_Instance_dtInstance = 0x45A430;

char* GetManuNameFromID()
{
	CIniReader Manu("NFSMWUnlimiterSettings.ini");
	char* num;
	sprintf(num, "%d", ManuID);

	return Manu.ReadString("Manufacturers", num, "DEFAULT");
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

int Init()
{
	CIniReader Settings("NFSMWUnlimiterSettings.ini");

	// Main
	CarCount = Settings.ReadInteger("Main", "CarModelIDLimit", 127);
	ReplacementCar = Settings.ReadInteger("Main", "ReplacementModel", 127);
	ManuHook = Settings.ReadInteger("Main", "EnableManufacturerHook", 1) == 1;
	// Fixes
	DisappearingWheelsFix = Settings.ReadInteger("Fixes", "DisappearingWheelsFix", 1) == 1;
	SecondaryLogoFix = Settings.ReadInteger("Fixes", "SecondaryLogoFix", 1) == 1;
	// Misc
	ExpandMemoryPools = Settings.ReadInteger("Misc", "ExpandMemoryPools", 0) == 1;

	// Wrap around values if over limtis
	CarCount = CarCount %= 128;
	ReplacementCar = ReplacementCar %= 128;

	// Actual code
	injector::WriteMemory<BYTE>(0x6690BD, CarCount, true); // PVehicle::Resource::Resource
	injector::WriteMemory<BYTE>(0x7398A8, CarCount, true);
	injector::WriteMemory<int>(0x739900, CarCount * 0xD0, true); // CarPartDatabase::GetCarType
	injector::WriteMemory<int>(0x739909, ReplacementCar, true); // Replacement model if model not found
	injector::WriteMemory<BYTE>(0x73995D, CarCount, true); // GetCarTypeInfoFromHash
	injector::WriteMemory<BYTE>(0x7515FD, CarCount, true);
	injector::WriteMemory<BYTE>(0x759915, CarCount, true); // RideInfo::FillWithPreset
	injector::WriteMemory<unsigned char>(0x75E6F6, CarCount, true); // CarRenderConn::Construct
	injector::WriteMemory<unsigned char>(0x75E7B6, CarCount, true); // HeliRenderConn::Construct
	injector::WriteMemory<int>(0x7B3879, CarCount * 0xD0, true); // DebugCarCustomizeScreen::BuildOptionsLists
	
	// Manufacturer logo hook
	if (ManuHook)
	{
		injector::MakeJMP(0x005817C1, CarManuCodeCave, true);
		injector::MakeRangedNOP(0x581B69, 0x581B6E, true); // Prevent returning null
	}

	if (DisappearingWheelsFix) // Fix Invisible Wheels
		injector::WriteMemory<unsigned char>(0x74251D, 0x01, true);

	// 2nd logo fix
	if (SecondaryLogoFix)
	{
		injector::MakeRangedNOP(0x591273, 0x591279, true);
	}

	// Expand Memory Pools (ty Berkay)
	if (ExpandMemoryPools)
	{
		injector::WriteMemory<short>(0x5F7396, 0x2C80, true); // GManager::PreloadTransientVaults (0x2C8000)
		injector::WriteMemory<short>(0x5F73B2, 0x2C80, true);

		injector::WriteMemory<unsigned char>(0x665FDC, 0x80, true); // InitializeEverything (0x8000)

		injector::WriteMemory<DWORD>(0x8F5790, 0x0BE6E0, true); // FEngMemoryPoolSize (InitFEngMemoryPool)
		injector::WriteMemory<DWORD>(0x8F7EF0, 0x01CC00, true); // CarLoaderPoolSizes
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
