#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

DWORD* _FEPlayerCarDB;

void __fastcall FEPlayerCarDB_Default_CreateBonusCars(DWORD* FEPlayerCarDB, void* EDX_Unused)
{
	char BonusCarNameBuf[16];
	CIniReader BonusCars("UnlimiterData\\_BonusCars.ini");
	char* PresetName;

	int NumberOfBonusCars = BonusCars.ReadInteger("BonusCars", "NumberOfBonusCars", -1);

	// Read ini entries to create bonus cars

	for (int i = -1; i <= NumberOfBonusCars; i++)
	{
		sprintf(BonusCarNameBuf, "BonusCar%d", i);
		PresetName = BonusCars.ReadString(BonusCarNameBuf, "PresetName", "");

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
					int CarRecordID = BonusCars.ReadInteger(BonusCarNameBuf, "CarRecordID", -1);
					if (CarRecordID != -1) NewPresetCar[0] = CarRecordID;

					// Check if the preset car needs to be in a specific category
					NewPresetCar[3] = BonusCars.ReadInteger(BonusCarNameBuf, "Category", 0xF0008); // If no category is set, default to Bonus
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