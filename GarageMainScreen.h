#pragma once
#include "stdio.h"
#include "InGameFunctions.h"

// 0x7A2380
void __declspec(naked) CamUserRotateCodeCave_GarageMainScreen_HandleJoyEvents()
{
	_asm
	{
		mov al, byte ptr ds: [InShowcase] // check showcase mode
		test al,al
		jz loc_7A25DD
		
		mov al, byte ptr ds: [esi+0x78] // check cam_user_rotate
		test al, al
		jnz loc_7A2394 // Allow controller to rotate the camera
		
		loc_7A25DD:
		push 0x7A25DD
		retn

		loc_7A2394:
		push 0x7A2394
		retn
	}
}
