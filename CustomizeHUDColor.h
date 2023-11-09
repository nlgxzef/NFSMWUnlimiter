#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

int CustomizeHUDColor_NumColors = 10;
int CustomizeHUDColor_ColorStartIndex = 1;
int CustomizeHUDColor_ColorEndIndex = 10;

int __fastcall CustomizeHUDColor_GetSelectedColorIndex(DWORD* _CustomizeHUDColor, void* EDX_Unused)
{
	DWORD* CurrItem = (DWORD*)_CustomizeHUDColor[113];
	DWORD* ListItem = (DWORD*)_CustomizeHUDColor[111];
	int Index = 1;

	while (ListItem != (DWORD*)_CustomizeHUDColor[112])
	{
		ListItem--; // back to vtable
		if (CurrItem == ListItem) break; // found

		ListItem = (DWORD*)ListItem[1]; // Next
		Index++;
	}

	return Index;
}

DWORD* __fastcall CustomizeHUDColor_GetColorOptionAt(DWORD* _CustomizeHUDColor, void* EDX_Unused, int Index)
{
	DWORD* ListItem = (DWORD*)_CustomizeHUDColor[111];
	int i = 1;

	while (ListItem != (DWORD*)_CustomizeHUDColor[112])
	{
		if (i == Index) break; // found

		ListItem--; // back to vtable
		ListItem = (DWORD*)ListItem[1]; // Next
		i++;
	}

	if (i < Index) return 0; // not found, index out of bounds or something

	ListItem--; // back to vtable
	return ListItem;
}

int __fastcall CustomizeHUDColor_GetNumColors(DWORD* _CustomizeHUDColor, void* EDX_Unused)
{
	DWORD* CurrItem = (DWORD*)_CustomizeHUDColor[113];
	DWORD* ListItem = (DWORD*)_CustomizeHUDColor[111];
	int Num = 1;

	while (ListItem != (DWORD*)_CustomizeHUDColor[112])
	{
		ListItem--; // back to vtable
		ListItem = (DWORD*)ListItem[1]; // Next
		Num++;
	}

	return Num;
}

void __fastcall CustomizeHUDColor_RefreshColors(DWORD* _CustomizeHUDColor, void* EDX_Unused)
{
	char ColorObjNameBuf[16];
	DWORD* ColorObj;
	DWORD* ColorOption;

	DWORD* CurrItem = (DWORD*)_CustomizeHUDColor[113];
	DWORD* CurrItemSelectablePart = (DWORD*)CurrItem[19];

	for (int i = 1; i <= 10; i++)
	{
		sprintf(ColorObjNameBuf, "COLOR_%d", i);

		ColorOption = CustomizeHUDColor_GetColorOptionAt(_CustomizeHUDColor, EDX_Unused, CustomizeHUDColor_ColorStartIndex + i - 1);
		ColorObj = FEngFindObject((char const*)_CustomizeHUDColor[4], bStringHash(ColorObjNameBuf));
		if (ColorOption)
		{
			IconOption_SetFEngObject(ColorOption, ColorObj);
			FEngSetColor_obj(ColorObj, ColorOption[20]); // New color
		}
		else FEngSetColor_obj(ColorObj, 0); // New color
		FEngSetScript_obj(ColorObj, 0x7AB5521A, 1); // UNHIGHLIGHT
	}
}

void __fastcall CustomizeHUDColor_ScrollIndexes(DWORD* _CustomizeHUDColor, void* EDX_Unused, int Direction)
{
	int CurrColor = CustomizeHUDColor_GetSelectedColorIndex(_CustomizeHUDColor, EDX_Unused);

	if (Direction == -1) // Up
	{
		if (CurrColor < CustomizeHUDColor_ColorStartIndex)
		{
			CustomizeHUDColor_ColorStartIndex--;
			CustomizeHUDColor_ColorEndIndex--;
		}
		else if (CurrColor > CustomizeHUDColor_ColorEndIndex) // Jumps
		{
			CustomizeHUDColor_ColorEndIndex = CustomizeHUDColor_NumColors;
			CustomizeHUDColor_ColorStartIndex = CustomizeHUDColor_NumColors > 10 ? (CustomizeHUDColor_ColorEndIndex - 9) : 1;
		}

	}
	else if (Direction == 1) // Down
	{
		if (CurrColor > CustomizeHUDColor_ColorEndIndex)
		{
			CustomizeHUDColor_ColorStartIndex++;
			CustomizeHUDColor_ColorEndIndex++;
		}
		else if (CurrColor < CustomizeHUDColor_ColorStartIndex) // Jumps
		{
			CustomizeHUDColor_ColorStartIndex = 1;
			CustomizeHUDColor_ColorEndIndex = CustomizeHUDColor_NumColors > 10 ? (CustomizeHUDColor_ColorStartIndex + 9) : CustomizeHUDColor_NumColors;
		}
	}
}

void __fastcall CustomizeHUDColor_ScrollColors(DWORD* _CustomizeHUDColor, void* EDX_Unused, int Direction)
{
	DWORD* CurrItem = (DWORD*)_CustomizeHUDColor[113];
	DWORD* NewItem = CurrItem;
	float x, y;

	if (Direction == -1) // Up
	{
		NewItem = (DWORD*)CurrItem[2]; // Previous
		if (NewItem == _CustomizeHUDColor + 111) NewItem = (DWORD*)_CustomizeHUDColor[112]; // If first, jump to last
		if (NewItem) NewItem--;
	}
	else if (Direction == 1) // Down
	{
		NewItem = (DWORD*)CurrItem[1]; // Next
		if (NewItem == _CustomizeHUDColor + 111) NewItem = (DWORD*)_CustomizeHUDColor[111]; // If last, jump to first
		if (NewItem) NewItem--;
	}

	_CustomizeHUDColor[113] = (DWORD)NewItem;

	if (NewItem && NewItem != CurrItem)
	{
		*(DWORD*)(_CustomizeHUDColor[14] + 96) = NewItem[19]; // CurrentLayer SelectablePart = NewItem SelectablePart

		CustomizeHUDColor_ScrollIndexes(_CustomizeHUDColor, EDX_Unused, Direction);
		CustomizeHUDColor_RefreshColors(_CustomizeHUDColor, EDX_Unused);

		FEngSetScript_obj((DWORD*)NewItem[4], 0x249DB7B7, 1); // HIGHLIGHT
		FEngGetTopLeft_obj((DWORD*)NewItem[4], &x, &y);
		y += *(float*)0x8B7A78; // 56
		x += *(float*)0x8B7A74; // 69
		FEngSetTopLeft_obj((DWORD*)_CustomizeHUDColor[114], x, y); // Highlight obj pos
		
		(*(void(__thiscall**)(DWORD*))(*_CustomizeHUDColor + 12))(_CustomizeHUDColor); // RefreshHeader
	}
}

void __fastcall CustomizeHUDColor_RefreshHeader(DWORD* _CustomizeHUDColor, void* EDX_Unused)
{
	CustomizationScreen_RefreshHeader(_CustomizeHUDColor);
	DWORD* CurrItem = (DWORD*)_CustomizeHUDColor[113];
	DWORD* CurrItemSelectablePart = (DWORD*)CurrItem[19];
	DWORD ItemColor = CurrItem[20];
	DWORD* ObjToColor;

	switch (CurrItemSelectablePart[4]) // CarSlotID
	{
		case CAR_SLOT_ID::HUD_BACKING_COLOUR:
			ObjToColor = FEngFindObject((char const*)_CustomizeHUDColor[4], 0x5D19F25); // TAC_FILL_00.tga
			FEngSetColor_obj(ObjToColor, ItemColor);
			break;

		case CAR_SLOT_ID::HUD_NEEDLE_COLOUR:
			ObjToColor = FEngFindObject((char const*)_CustomizeHUDColor[4], 0xD312F0CB); // RPM_NEEDLE.tga
			FEngSetColor_obj(ObjToColor, ItemColor);
			ObjToColor = FEngFindObject((char const*)_CustomizeHUDColor[4], 0x8FE2A217); // TURBO_NEEDLE.tga
			FEngSetColor_obj(ObjToColor, ItemColor);
			break;

		case CAR_SLOT_ID::HUD_CHARACTER_COLOUR:
			ObjToColor = FEngFindObject((char const*)_CustomizeHUDColor[4], 0xC0721EB9); // 7500_LINES_00.tga
			FEngSetColor_obj(ObjToColor, ItemColor);
			ObjToColor = FEngFindObject((char const*)_CustomizeHUDColor[4], 0xC62AD685); // TURBO_LINES
			FEngSetColor_obj(ObjToColor, ItemColor);
			ObjToColor = FEngFindObject((char const*)_CustomizeHUDColor[4], 0xB8F1F802); // "KM/H"
			FEngSetColor_obj(ObjToColor, ItemColor);
			break;
	}
}

void __fastcall CustomizeHUDColor_BuildColorOptions_Hook(DWORD* _CustomizeHUDColor, void* EDX_Unused)
{
	CustomizeHUDColor_BuildColorOptions_Game(_CustomizeHUDColor);

	float x, y;

	int CurrColor = CustomizeHUDColor_GetSelectedColorIndex(_CustomizeHUDColor, EDX_Unused);

	CustomizeHUDColor_NumColors = CustomizeHUDColor_GetNumColors(_CustomizeHUDColor, EDX_Unused);

	if (CurrColor > 10)
	{
		CustomizeHUDColor_ColorEndIndex = CurrColor;
		CustomizeHUDColor_ColorStartIndex = CurrColor - 9;
	}
	else
	{
		CustomizeHUDColor_ColorStartIndex = 1;
		CustomizeHUDColor_ColorEndIndex = CustomizeHUDColor_NumColors > 10 ? (CustomizeHUDColor_ColorStartIndex + 9) : CustomizeHUDColor_NumColors;
	}

	CustomizeHUDColor_RefreshColors(_CustomizeHUDColor, EDX_Unused);

	DWORD* CurrItem = (DWORD*)_CustomizeHUDColor[113];
	FEngSetScript_obj((DWORD*)CurrItem[4], 0x249DB7B7, 1); // HIGHLIGHT
	FEngGetTopLeft_obj((DWORD*)CurrItem[4], &x, &y);
	y += *(float*)0x8B7A78; // 56
	x += *(float*)0x8B7A74; // 69
	FEngSetTopLeft_obj((DWORD*)_CustomizeHUDColor[114], x, y); // Highlight obj pos
}