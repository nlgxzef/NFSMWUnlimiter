#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

bool UnlockSystem_IsBonusCarCEOnly(int PresetNameHash)
{
	char BonusCarNameBuf[16];
	CIniReader BonusCars("UnlimiterData\\_BonusCars.ini");
	char* PresetName;

	int NumberOfBonusCars = BonusCars.ReadInteger("BonusCars", "NumberOfBonusCars", -1);

	// Check if any of our custom bonus cars are marked as CE only
	for (int i = 0; i <= NumberOfBonusCars; i++)
	{
		sprintf(BonusCarNameBuf, "BonusCar%d", i);
		if (BonusCars.ReadInteger(BonusCarNameBuf, "Category", 0xF0008) == 0xF0008)
		{
			PresetName = BonusCars.ReadString(BonusCarNameBuf, "PresetName", "");
			if (FEHashUpper(PresetName) == PresetNameHash)
			{
				return BonusCars.ReadInteger(BonusCarNameBuf, "CEOnly", 0) != 0;
			}
		}
	}

	// If the bonus car preset isn't in the custom list, also try the in-game function
	return UnlockSystem_IsBonusCarCEOnly_Game(PresetNameHash);
}
