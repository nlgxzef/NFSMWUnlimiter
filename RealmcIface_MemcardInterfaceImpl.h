#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

static injector::hook_back<unsigned int(__fastcall*)(DWORD*, void*, DWORD*)> hb_RealmcIface_MemcardInterfaceImpl_ProcessDelete;
unsigned int __fastcall RealmcIface_MemcardInterfaceImpl_ProcessDelete(DWORD* RealmcIface_MemcardInterfaceImpl, void* EDX_Unused, DWORD* Message)
{
	//Presitter_Delete((char const*)RealmcIface_MemcardInterfaceImpl + 180);
	return hb_RealmcIface_MemcardInterfaceImpl_ProcessDelete.fun(RealmcIface_MemcardInterfaceImpl, EDX_Unused, Message);
}