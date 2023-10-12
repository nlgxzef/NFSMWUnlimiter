#include "stdio.h"
#include "InGameFunctions.h"

// 0x7471AD
void __declspec(naked) RideHeightCave()
{
	_asm
	{
		pushad
		mov eax, dword ptr ds: [eax + 0xFC]
		push eax // original
		mov esi, dword ptr ds : [esi + 0x44]
		push esi // render info
		call GetRideHeight

		popad
		push 0x007471B3
		retn
	}
}

// 0x746F33
void __declspec(naked) DoSkidsCave_CarRenderConn_UpdateTires()
{
	_asm
	{
		mov edx, edi // CarRenderConn
		call TireState_DoSkids_Hook // fastcall
		push 0x0746F38
		retn
	}
}

// 0x74717A
void __declspec(naked) ExtraPitchCave_CarRenderConn_UpdateRenderMatrix()
{
	_asm
	{
		pushad
		mov eax, dword ptr ds : [eax]
		push eax // original
		mov esi, dword ptr ds : [esi + 0x44]
		push esi // render info
		call CarRenderInfo_GetExtraPitch

		popad
		mov eax, dword ptr ds: [esi + 0x1C]
		push 0x74717F
		retn
	}
}

DWORD* __fastcall CarRenderConn_OnLoaded(DWORD* _CarRenderConn, void* EDX_Unused, DWORD* CarRenderInfo)
{
	CarRenderConn_OnLoaded_Game(_CarRenderConn, CarRenderInfo);
	
	if (CarRenderInfo)
	{
		for (int WheelID = 0; WheelID < 4; WheelID++)
		{
			bVector4 TireOffsets = CarRenderInfo_GetTireOffset(CarRenderInfo, 0, WheelID); // Get wheel offsets

			// Write new offsets into CarRenderConn
			*(float*)(_CarRenderConn + 37 + WheelID * 4) = TireOffsets.y;
		}
	}

	return _CarRenderConn;
}