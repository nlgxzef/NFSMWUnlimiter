#pragma once
#include "stdio.h"
#include "InGameFunctions.h"

void __fastcall Showcase_ctor_Hook(DWORD* _Showcase, void* EDX_Unused, DWORD* _ScreenConstructorData)
{
	Showcase_ctor(_Showcase, _ScreenConstructorData);
	InShowcase = 1;
}

void __fastcall Showcase_dtor_Hook(DWORD* _Showcase, void* EDX_Unused)
{
	InShowcase = 0;
	Showcase_dtor(_Showcase);
}