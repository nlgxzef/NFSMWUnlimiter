#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

void __declspec(naked) CustomizePartsIDCodeCave()
{
	_asm
	{
		dec eax
		jz RoofScoops // 0x105
		dec eax
		jz Interiors // 0x106
		dec eax
		jz Roofs // 0x107
		dec eax
		jz Brakes // 0x108
		dec eax
		jz Headlights // 0x109
		dec eax
		jz Brakelights // 0x10A
		dec eax
		jz Mirrors // 0x10B
		dec eax
		// 0x10C = Attachments submenu
		dec eax
		jz Attachment1 // 0x10D
		dec eax
		jz Attachment2 // 0x10E
		dec eax
		jz Attachment3 // 0x10F
		dec eax
		jz Attachment4 // 0x110
		dec eax
		jz Attachment5 // 0x111
		dec eax
		jz Attachment6 // 0x112
		dec eax
		jz Attachment7 // 0x113
		dec eax
		jz Attachment8 // 0x114
		dec eax
		jz Attachment9 // 0x115
		dec eax
		jz Attachment10 // 0x116
		
		jmp CaveExit

		RoofScoops :
		push 0x7BD0D4
			retn

		Interiors :
			mov dword ptr ds : [edi + 0x15C] , 0xCBC529DC // CO_INTERIOR
			mov eax, 0x524B1D74 // VISUAL_PART_INTERIOR
			mov esi, 28 // INTERIOR
			mov ebp, eax
			jmp CaveExit

		Roofs :
			mov dword ptr ds : [edi + 0x15C] , 0xF86904C6 // CO_ROOF
			mov eax, 0x294EC5E // VISUAL_PART_ROOF
			mov esi, 0 // BASE
			mov ebp, eax
			jmp CaveExit

		Brakes :
			mov dword ptr ds : [edi + 0x15C] , 0x91997EE8 // CO_BRAKES
			mov eax, 0x54125A8D // VISUAL_PART_BRAKE
			mov esi, 24 // FRONT_BRAKE
			mov ebp, eax
			jmp CaveExit

		Headlights :
			mov dword ptr ds : [edi + 0x15C] , 0xD16C070D // CO_HEADLIGHTS
			mov eax, 0xF69AC384 // VISUAL_PART_HEAD_LIGHTS
			mov esi, 31 // LEFT_HEADLIGHT
			mov ebp, eax
			jmp CaveExit

		Brakelights :
			mov dword ptr ds : [edi + 0x15C] , 0xF9D99DA5 // CO_TAILLIGHTS
			mov eax, 0x2CBB2D1C // VISUAL_PART_TAIL_LIGHTS
			mov esi, 29 // LEFT_BRAKELIGHT
			mov ebp, eax
			jmp CaveExit

		

		Attachment1 :
			mov dword ptr ds : [edi + 0x15C] , 0xB81F39E9 // CO_ATTACHMENT_1
			mov eax, 0x5524B4D1 // VISUAL_PART_ATTACHMENT
			mov esi, 52 // ATTACHMENT0
			mov ebp, eax
			jmp CaveExit

		Attachment2 :
			mov dword ptr ds : [edi + 0x15C] , 0xB81F39EA // CO_ATTACHMENT_2
			mov eax, 0x5524B4D1 // VISUAL_PART_ATTACHMENT
			mov esi, 53 // ATTACHMENT1
			mov ebp, eax
			jmp CaveExit

		Attachment3 :
			mov dword ptr ds : [edi + 0x15C] , 0xB81F39EB // CO_ATTACHMENT_3
			mov eax, 0x5524B4D1 // VISUAL_PART_ATTACHMENT
			mov esi, 54 // ATTACHMENT2
			mov ebp, eax
			jmp CaveExit

		Attachment4 :
			mov dword ptr ds : [edi + 0x15C] , 0xB81F39EC // CO_ATTACHMENT_4
			mov eax, 0x5524B4D1 // VISUAL_PART_ATTACHMENT
			mov esi, 55 // ATTACHMENT3
			mov ebp, eax
			jmp CaveExit

		Attachment5 :
			mov dword ptr ds : [edi + 0x15C] , 0xB81F39ED // CO_ATTACHMENT_5
			mov eax, 0x5524B4D1 // VISUAL_PART_ATTACHMENT
			mov esi, 56 // ATTACHMENT4
			mov ebp, eax
			jmp CaveExit

		Attachment6 :
			mov dword ptr ds : [edi + 0x15C] , 0xB81F39EE // CO_ATTACHMENT_6
			mov eax, 0x5524B4D1 // VISUAL_PART_ATTACHMENT
			mov esi, 57 // ATTACHMENT5
			mov ebp, eax
			jmp CaveExit

		Attachment7 :
			mov dword ptr ds : [edi + 0x15C] , 0xB81F39EF // CO_ATTACHMENT_7
			mov eax, 0x5524B4D1 // VISUAL_PART_ATTACHMENT
			mov esi, 58 // ATTACHMENT6
			mov ebp, eax
			jmp CaveExit

		Attachment8 :
			mov dword ptr ds : [edi + 0x15C] , 0xB81F39F0 // CO_ATTACHMENT_8
			mov eax, 0x5524B4D1 // VISUAL_PART_ATTACHMENT
			mov esi, 59 // ATTACHMENT7
			mov ebp, eax
			jmp CaveExit

		Attachment9 :
			mov dword ptr ds : [edi + 0x15C] , 0xB81F39F1 // CO_ATTACHMENT_9
			mov eax, 0x5524B4D1 // VISUAL_PART_ATTACHMENT
			mov esi, 60 // ATTACHMENT8
			mov ebp, eax
			jmp CaveExit

		Attachment10 :
			mov dword ptr ds : [edi + 0x15C] , 0xBC067739 // CO_ATTACHMENT_10
			mov eax, 0x5524B4D1 // VISUAL_PART_ATTACHMENT
			mov esi, 61 // ATTACHMENT9
			mov ebp, eax
			jmp CaveExit

		Mirrors :
			mov dword ptr ds : [edi + 0x15C] , 0xD3DAE7CF // CO_SIDE_MIRROR
			mov eax, 0x0DD35467 // VISUAL_PART_SIDE_MIRROR
			mov esi, 33 // LEFT_SIDE_MIRROR
			mov ebp, eax
			jmp CaveExit

		CaveExit :
			push 0x7BD210
			retn
	}
}

void __declspec(naked) CustomizeVisualsIDCodeCave()
{
	_asm
	{
		cmp eax, 0x307
		jz CustomGauges
		cmp eax, 0x308
		jz Drivers
		cmp eax, 0x309
		jz Plates
		push 0x7BD16F // Other Options
		retn

		CustomGauges:
			push 0x7BD192
			retn

		Drivers :
			mov dword ptr ds : [edi + 0x15C] , 0x964861FC // CO_DRIVER
			mov eax, 0xDB0C8F94 // VISUAL_PART_DRIVER
			mov esi, 43 // DRIVER
			mov ebp, eax
			jmp CaveExit

		Plates :
			mov dword ptr ds : [edi + 0x15C] , 0x3CC9A5C8 // CO_LICENSE_PLATE
			mov eax, 0xD68F9860 // VISUAL_PART_LICENSE_PLATE
			mov esi, 69 // LICENSE_PLATE
			mov ebp, eax
			jmp CaveExit

		CaveExit :
			push 0x7BD210
			retn
	}
}

void __declspec(naked) CustomizePartsPackageSwitchCodeCave()
{
	_asm
	{
		cmp eax, 0x116
		ja originalcode
		cmp eax, 0x10D
		jb loc_7B75E1
		jmp loc_7B75A8

		originalcode :
			cmp eax, 0x401
			push 0x7B759F
			retn

		loc_7B75E1 :
			push 0x7B75E1
			retn

		loc_7B75A8 :
			push 0x7B75A8
			retn
	}
}