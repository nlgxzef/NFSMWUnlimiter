#pragma once

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

int UnlockSystem_GetPerfPackageCost(int UnlockFilter, int PackageType, int PackageLevel, int Unk)
{
	return UnlockSystem_GetPerfPackageCost_Game(UnlockFilter, PackageType, PackageLevel, Unk);
}

int UnlockSystem_GetCarPartCost(int UnlockFilter, int CarSlotID, DWORD* CarPart, int Unk)
{
	int Unlockable = MapCarPartToUnlockable(CarSlotID);
	float Cost = 0.0f;

	if (Unlockable)
	{
		float* FEPartInfo = (float*)LookupFEPartInfo(Unlockable, ((BYTE*)CarPart)[5] >> 5);
		if (FEPartInfo) Cost = FEPartInfo[2];
	}
	
	return CarPart_GetAppliedAttributeIParam(CarPart, bStringHash("COST"), (int)Cost);
}