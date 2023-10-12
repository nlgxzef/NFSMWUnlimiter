#pragma once
#include "stdio.h"
#include "InGameFunctions.h"

// 0x75D29E
void __declspec(naked) CarSkinCountCodeCave_VehicleRenderConn_Load()
{
	_asm
	{
		mov edx, 1

		loc_75D2A5:
			lea ecx, dword ptr ds: [edx - 1]
			mov eax, 1
			shl eax, cl
			test eax, edi
			jnz loc_75D2D6
			inc edx
			cmp edx, CarSkinCount
			jle loc_75D2A5
			jmp loc_75D2E3

		loc_75D2D6:
			push 0x75D2D6
			retn

		loc_75D2E3:
			push 0x75D2E3
			retn
	}
}