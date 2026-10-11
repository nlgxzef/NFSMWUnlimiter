#pragma once

#include "stdio.h"
#include "InGameFunctions.h"
#include "GlobalVariables.h"

#include "CarPart.h"

struct CarPartIndex
{
	CarPart* Part;
	int NumParts;
};

struct CarPartPack
{
	int Padding_1605[2];
	unsigned int Version;
	const char* StringTable;
	unsigned int StringTableSize;
	/*CarPartAttributeTable*/ DWORD* AttributeTableTable;
	unsigned int NumAttributeTables;
	/*CarPartAttribute*/ DWORD* AttributesTable;
	unsigned int NumAttributes;
	unsigned int* TypeNameTable;
	unsigned int NumTypeNames;
	/*CarPartModelTable*/ DWORD* ModelTable;
	unsigned int NumModelTables;
	CarPart* PartsTable;
	unsigned int NumParts;
};

struct CarPartDatabase
{
	bTList<CarPartPack> CarPartPackList;
	int NumPacks;
	int NumParts;
	int NumBytes;
	CarPartIndex PaintPart_Gloss[3];
	CarPartIndex PaintPart_Metallic[3];
	CarPartIndex PaintPart_Pearl[3];
	CarPartIndex PaintPart_Vinyl[3];
	CarPartIndex PaintPart_Rims[3];
	CarPartIndex PaintPart_Caliper[3];
	CarPartIndex VinylPart_All[3];
	CarPartIndex VinylPart_Body[3];
	CarPartIndex VinylPart_Hood[3];
	CarPartIndex VinylPart_Side[3];
	CarPartIndex VinylPart_Manufacturer[3];
};

CarPartDatabase* DBCarPart;

DWORD* __fastcall CarPartDatabase_NewGetCarPart_Hook(DWORD* CarPartDB, void* EDX_Unused, int car_type, int car_slot_id, DWORD car_part_namehash, DWORD *prev_part, int upg_level)
{
	DWORD* TheCarPart;

	switch (car_slot_id)
	{
	case CARSLOTID_BASE_PAINT:
	case CARSLOTID_PAINT_RIM:
	case CARSLOTID_VINYL_COLOUR0_0:
	case CARSLOTID_VINYL_COLOUR0_1:
	case CARSLOTID_VINYL_COLOUR0_2:
	case CARSLOTID_VINYL_COLOUR0_3:
	case CARSLOTID_HUD_BACKING_COLOUR:
	case CARSLOTID_HUD_CHARACTER_COLOUR:
	case CARSLOTID_HUD_NEEDLE_COLOUR:
		for (int i = 0; i < 4; i++)
		{
			TheCarPart = (DWORD*)CarPartDatabase_NewGetCarPart(CarPartDB, car_type, PaintCarSlotIDsToLookFor[i], car_part_namehash, (int)prev_part, upg_level);
			if (TheCarPart) break;
		}
		break;
	default:
		TheCarPart = (DWORD*)CarPartDatabase_NewGetCarPart(CarPartDB, car_type, car_slot_id, car_part_namehash, (int)prev_part, upg_level);
		break;
	}

	return TheCarPart;
}