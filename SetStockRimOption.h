#pragma once
#include "stdio.h"
#include "InGameFunctions.h"

void __fastcall SetStockRimOption_React(DWORD* SetStockPartOption, void* EDX_Unused, const char* a4, unsigned int MessageHash, DWORD* FEObject, unsigned int param1, unsigned int param2)
{
	DWORD* TheSelectablePart; // eax

	TheSelectablePart = (DWORD*)SetStockPartOption[22];
	if ((TheSelectablePart[8] & 0xF0) != 16 )
	{
        switch (RimsToCustomize)
        {
        case -1: // Rear
            TheSelectablePart[4] = CAR_SLOT_ID::REAR_WHEEL;
            CarCustomizeManager_AddToCart((DWORD*)_gCarCustomizeManager, TheSelectablePart);
            break;
        case 0: // All
        default:
            CarCustomizeManager_AddToCart((DWORD*)_gCarCustomizeManager, TheSelectablePart);
            TheSelectablePart[4] = CAR_SLOT_ID::REAR_WHEEL;
            CarCustomizeManager_AddToCart((DWORD*)_gCarCustomizeManager, TheSelectablePart);
            break;
        case 1: // Front
            CarCustomizeManager_AddToCart((DWORD*)_gCarCustomizeManager, TheSelectablePart);
            break;
        }

		*(DWORD*)(SetStockPartOption[22] + 32) = *(DWORD*)(SetStockPartOption[22] + 32) & 0xF | 0x20;
	}
}

DWORD SetStockRimOption_vTable[] =
{
	0x7AA0D0,			// SetStockPartOption_dtor
	(DWORD)&SetStockRimOption_React,	// React
	0x7AA0C0			// SetStockPartOption::IsStockOption
};