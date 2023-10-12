#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

bool UnlockSystem_IsBonusCarCEOnly(int PresetNameHash)
{
	char* PresetName;

	int NumberOfBonusCars = BonusCars.size();

	// Check if any of our custom bonus cars are marked as CE only
	for (int i = 0; i < NumberOfBonusCars; i++)
	{
		if (BonusCars[i].Category == 0xF0008)
		{
			PresetName = BonusCars[i].PresetName;
			if (FEHashUpper(PresetName) == PresetNameHash)
			{
				return BonusCars[i].CEOnly;
			}
		}
	}

	// If the bonus car preset isn't in the custom list, also try the in-game function
	return UnlockSystem_IsBonusCarCEOnly_Game(PresetNameHash);
}

int UnlockSystem_GetPerfPackageCost(int UnlockFilter, int PackageType, int PackageLevel, int UpgradeLevel)
{
	return UnlockSystem_GetPerfPackageCost_Game(UnlockFilter, PackageType, PackageLevel, UpgradeLevel);
}

int UnlockSystem_GetCarPartCost(int UnlockFilter, int CarSlotID, DWORD* CarPart, int UpgradeLevel)
{
	int Unlockable = MapCarPartToUnlockable(CarSlotID);
	float Cost = 0.0f;

	if (Unlockable)
	{
		float* FEPartInfo = (float*)LookupFEPartInfo(Unlockable, ((BYTE*)CarPart)[5] >> 5);
		if (FEPartInfo) Cost = FEPartInfo[2];
	}
	
	return CarPart_GetAppliedAttributeIParam(CarPart, bStringHash((char*)"COST"), (int)Cost);
}

bool UnlockSystem_IsCarPartUnlocked(int eUnlockFilters, int CarSlotID, DWORD* CarPart, int UpgradeLevel, bool IsInBackroom)
{
	bool UAT = *(bool*)_UnlockAllThings;
	DWORD* FEDatabase = *(DWORD**)_FEDatabase;
	int BinToBeat;

	if (UAT) return 1;

	DWORD* UserProfile = (DWORD*)*((DWORD*)FEDatabase + 4);
	BYTE CurrentBin = *((BYTE*)UserProfile + 176);   // UserProfile->CareerSettings->CurrentBin

	if (!IsInBackroom) // If not in backroom
	{
        // Get and check if the condition is met
        int UnlockConditionType = CarPart_GetAppliedAttributeIParam(CarPart, bStringHash((char*)"UNLOCK_TYPE"), -1);

		switch (UnlockConditionType)
		{
		case 0: // Initially unlocked
			return 1;
		case 1: // Beat Blacklist member
			BinToBeat = CarPart_GetAppliedAttributeIParam(CarPart, bStringHash((char*)"UNLOCK_AT"), 17);
			if (BinToBeat < 2 || BinToBeat > 17) BinToBeat = 17;
			if (CurrentBin < BinToBeat) return 1;
			return 0;
		case 2: // Complete CS Event #68 (special flag)
			if (UserProfile[43] & 0x8000) return 1;
			return 0;
		case 3: // Enter "castrol" cheat code (special flag)
			if (UserProfile[43] & 0x40000) return 1;
			return 0;
		case 4: // Complete CS 100% (special flag)
			if (*((BYTE*)UserProfile + 174) & 1) return 1;
			return 0;
		case 5: // Complete Career mode at least once  (special flag)
		case 6: // Complete Game 100% (same as 5??)
			if (UserProfile[43] & 0x4000) return 1;
			return 0;
		case -1: // None (Use in game function instead)
		default:
			break;
		}
	}

	return UnlockSystem_IsCarPartUnlocked_Game(eUnlockFilters, CarSlotID, CarPart, UpgradeLevel, IsInBackroom);
}