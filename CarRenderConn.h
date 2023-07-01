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
void __declspec(naked) DoSkidsCave()
{
	_asm
	{
		mov edx, edi // CarRenderConn
		call TireState_DoSkids_Hook // fastcall
		push 0x0746F38
		retn
	}
}