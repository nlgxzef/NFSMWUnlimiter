#pragma once

#include "stdio.h"
#include "InGameFunctions.h"



static injector::hook_back<int(__fastcall*)(DWORD*, void*, char const*)> hb_MemoryCardSave;
int __fastcall MemoryCard_Save(DWORD* Memcard, void* EDX_Unused, char const* ProfileName)
{
	int result = hb_MemoryCardSave.fun(Memcard, EDX_Unused, ProfileName);

	return result;
}

static injector::hook_back<int(__fastcall*)(DWORD*, void*, char const*)> hb_MemoryCardLoad;
int __fastcall MemoryCard_Load(DWORD* Memcard, void* EDX_Unused, char const* ProfileName)
{
	int result = hb_MemoryCardLoad.fun(Memcard, EDX_Unused, ProfileName);

	

	return result;
}