#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

static injector::hook_back<int(__fastcall*)(DWORD*, void*, char const*)> hb_MemcardCallbacks_SaveDone;
int __fastcall MemcardCallbacks_SaveDone(DWORD* MemcardCallbacks, void* EDX_Unused, char const* ProfileName)
{
	Presitter_Save(ProfileName);
	
	return hb_MemcardCallbacks_SaveDone.fun(MemcardCallbacks, EDX_Unused, ProfileName);
}