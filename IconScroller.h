#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

unsigned int __fastcall IconScroller_GetOptionIndexWithID(DWORD* _IconScroller, void* EDX_Unused, unsigned int OptionID)
{
	if (!OptionID || !_IconScroller) return 1; // return if invalid
	if (!_IconScroller[3]) return 1; // return if there is only one
	
	DWORD* Option = (DWORD*)(_IconScroller[3] + 4);

	for (int index = 1; (Option && Option[0] != _IconScroller[1]); index++)
	{
		if (((WORD*)Option)[38] == OptionID) return index; // Menu ID
		else Option = (DWORD*)Option[0]; // ->Next
	}

	return 1;
}