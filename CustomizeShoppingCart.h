#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

// 0x7B0744
void __declspec(naked) MyCarsBackroomShoppingCartFixCodeCave2()
{
	_asm
	{
		call CustomizeIsInBackRoom
		test al, al
		jz loc_7B093E // Skip marker stuff

		mov edx, [_FEDatabase]
		test byte ptr ds : [edx + 0x12C] , 1 // check if in career mode
		jnz caveexit
		mov al, byte ptr ds : [g_bTestCareerCustomization]
		test al, al
		jz loc_7B09D2

		caveexit :
			push 0x7B076D
			retn

		loc_7B09D2 :
			push 0x7B09D2
			retn

		loc_7B093E :
			push 0x7B093E
			retn
	}
}

void CustomizeShoppingCart_ExitShoppingCart()
{
	if (CustomizeIsInBackRoom())
	{
		CustomizeSetInBackRoom(0);
		DWORD* TheFEManager = FEManager_Get();
		FEManager_SetGarageType(TheFEManager, CarCustomizeManager_IsCareerMode_CheckTCC() ? 3 : 1);
	}
	cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizeMainPkg, 0, 0, 0);
}