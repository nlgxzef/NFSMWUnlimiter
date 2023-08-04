#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

DWORD* _FEPlayerCarDB;

void __fastcall FEPlayerCarDB_Default_CreateBonusCars(DWORD* FEPlayerCarDB, void* EDX_Unused)
{
	char* PresetName;
	int CarRecordID;
	int Category;
	int NumberOfBonusCars = BonusCars.size();

	for (int i = -1; i < NumberOfBonusCars; i++)
	{
		if (i == -1)
		{
			PresetName = DefaultBonusCar.PresetName;
			CarRecordID = DefaultBonusCar.CarRecordID;
			Category = DefaultBonusCar.Category;
		}
		else
		{
			PresetName = BonusCars[i].PresetName;
			CarRecordID = BonusCars[i].CarRecordID;
			Category = BonusCars[i].Category;
		}

		if (strcmp(PresetName, "")) // Check the name
		{
			// Check if the preset exists in game
			int PresetNameHash = FEHashUpper(PresetName);
			if (FindFEPresetCar(PresetNameHash))
			{
				// Create preset
				DWORD* NewPresetCar = FEPlayerCarDB_CreateNewPresetCar(FEPlayerCarDB, PresetName);
				if (NewPresetCar)
				{
					// Check if the preset has a specific car record id
					if (CarRecordID != -1) NewPresetCar[0] = CarRecordID;

					// Set category
					NewPresetCar[3] = Category;
				}

				Physics_Upgrades_Flush();
			}
		}
	}
}

// 0x590D9F
void __declspec(naked) FEPlayerCarDB_Default_BonusCarsCodeCave()
{
	_asm
	{
		pushad
		mov ecx, ebx
		mov _FEPlayerCarDB, ecx
	}

	FEPlayerCarDB_Default_CreateBonusCars(_FEPlayerCarDB, 0);

	_asm
	{
		popad
		push 0x590EC1
		retn
	}
}