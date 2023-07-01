#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

static injector::hook_back<bool(__fastcall*)(DWORD*, void*, DWORD*, int, bool, int)> hb_UserProfile_LoadFromBuffer;
bool __fastcall UserProfile_LoadFromBuffer(DWORD* UserProfile, void* EDX_Unused, DWORD* Memcard, int unk0, bool unk1, int unk2)
{
	bool result = hb_UserProfile_LoadFromBuffer.fun(UserProfile, EDX_Unused, Memcard, unk0, unk1, unk2);
	BYTE IsProfileNamed = ((BYTE*)UserProfile)[32];

	if (result && IsProfileNamed) // Profile loaded successfully and has a name
	{
		Presitter_Load((char const*)UserProfile); // Do presitter stuff
	}

	return result;
}