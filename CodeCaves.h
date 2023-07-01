#pragma once

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

// 0x756AA7
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

	// Fix quantizers
	injector::WriteMemory<int>(0x9B1334, CarCount, true); // QuantCarType
	injector::WriteMemory<int>(0x9B1338, CarCount + 1, true);

	// Replacement model if model not found in array
	if (ReplacementCar > CarCount) ReplacementCar = 1;
	injector::WriteMemory<int>(0x739909, ReplacementCar, true);

	// Continue
	__asm
	{
		popad
		push 0x756AAD
		retn
	}
}

// 0x756BC7
void __declspec(naked) DoUnlimiterStuffCodeCave2()
{
	// Get count
	__asm
	{
		mov dword ptr ds : [_CarPartPartsTable] , edx
		sub edx, 4
		mov edx, [edx]
		mov CarPartPartsTableSize, edx
		mov edx, dword ptr ds : [_CarPartPartsTable]
		pushad
	}

	CarPartCount = CarPartPartsTableSize / SingleCarPartSize;

	if (CarPartCount > 16000)
	{
		// Fix quantizers
		injector::WriteMemory<int>(0x9B1478, CarPartCount, true); // QuantPartIndex
		injector::WriteMemory<int>(0x9B147C, CarPartCount + 1, true);
	}

	// Continue
	__asm
	{
		popad
		push 0x756BCD
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

void __declspec(naked) CustomFrameDelayCodeCave()
{
	_asm
	{
		mov eax, [FrameDelay]
		push eax
		call j_bThreadYield
		add esp, 4
		push 0x642EDA
		retn
	}
}