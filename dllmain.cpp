#include "stdafx.h"
#include "stdio.h"
#include <windows.h>
#include "..\includes\injector\injector.hpp"
#include "..\includes\IniReader.h"

#define CarCount 127 // MAX = 127
#define ReplacecmentCar 1 // CARRERAGT

int Init()
{
	injector::WriteMemory<BYTE>(0x6690BD, CarCount, true); // PVehicle::Resource::Resource
	injector::WriteMemory<BYTE>(0x7398A8, CarCount, true);
	injector::WriteMemory<int>(0x739900, CarCount * 0xD0, true); // CarPartDatabase::GetCarType
	injector::WriteMemory<int>(0x739909, ReplacecmentCar, true); // Replacement model if model not found
	injector::WriteMemory<BYTE>(0x73995D, CarCount, true); // GetCarTypeInfoFromHash
	injector::WriteMemory<BYTE>(0x7515FD, CarCount, true);
	injector::WriteMemory<BYTE>(0x759915, CarCount, true); // RideInfo::FillWithPreset
	injector::WriteMemory<unsigned char>(0x75E6F6, CarCount, true); // CarRenderConn::Construct
	injector::WriteMemory<unsigned char>(0x75E7B6, CarCount, true); // HeliRenderConn::Construct
	injector::WriteMemory<int>(0x7B3879, CarCount * 0xD0, true); // DebugCarCustomizeScreen::BuildOptionsLists
	return 0;
}

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}
	return TRUE;
}

