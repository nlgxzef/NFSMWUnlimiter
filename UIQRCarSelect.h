#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

// TODO: make both read from ini and call vanilla functions if can't find anything

unsigned int __fastcall UIQRCarSelect_GetBonusUnlockText(DWORD* UIQRCarSelect, void* EDX_Unused, DWORD* FECarRecord)
{
    unsigned int PresetHash = FECarRecord[0];

	char* PresetName;
	DWORD CustomUnlockStringHash;

	int NumberOfBonusCars = BonusCars.size();

	// Check if any of our custom bonus cars are marked as CE only
	for (int i = 0; i < NumberOfBonusCars; i++)
	{
		if (BonusCars[i].Category == 0xF0008) // Is a bonus car
		{
			PresetName = BonusCars[i].PresetName;
			if (FEHashUpper(PresetName) == PresetHash) // If it's the preset we are checking
			{
				// Check if user has given a custom unlock condition string
				CustomUnlockStringHash = BonusCars[i].UnlockConditionStringHash;
				if (CustomUnlockStringHash != -1)
				{
					if (DoesStringExist(CustomUnlockStringHash))
						return CustomUnlockStringHash;
				}
				// or else...
				// Check if the car is CE only but the game is not CE
				if (BonusCars[i].CEOnly && (*(bool*)_IsCollectorsEdition == 0))
				{
					return bStringHash((char*)"CARLOT_BONUSCAR_UNLOCK_MSG_05");
				}
				
				// Get and check the condition
				int UnlockConditionType = BonusCars[i].UnlockConditionType;

				switch (UnlockConditionType)
				{
				case 0: // Initially unlocked
					return bStringHash((char*)"CARLOT_BONUSCAR_UNLOCK_MSG_06");
					break;
				case 1: // Beat Blacklist member
					return bStringHash((char*)"CARLOT_UNLOCK_MSG_01");
					break;
				case 2: // Complete CS Event #68 (special flag)
					return bStringHash((char*)"CARLOT_BONUSCAR_UNLOCK_MSG_01");
					break;
				case 3: // Enter "castrol" cheat code (special flag)
					return bStringHash((char*)"CARLOT_BONUSCAR_UNLOCK_MSG_07");
					break;
				case 4: // Complete CS 100% (special flag)
					return bStringHash((char*)"CARLOT_BONUSCAR_UNLOCK_MSG_02");
					break;
				case 5: // Complete Career mode at least once (special flag)
					return bStringHash((char*)"CARLOT_BONUSCAR_UNLOCK_MSG_03");
					break;
				case 6: // Complete Game 100% (special flag, same as 5??)
					return bStringHash((char*)"CARLOT_BONUSCAR_UNLOCK_MSG_04");
					break;
				case -1: // None (Use in game function for a hardcoded value instead)
				default:
					goto _InGameFunction;
					break;
				}
			}
		}
	}
	// If not found, check in game function
_InGameFunction:
	return UIQRCarSelect_GetBonusUnlockText_Game(UIQRCarSelect, FECarRecord);
}

int __fastcall UIQRCarSelect_GetBonusUnlockBinNumber(DWORD* UIQRCarSelect, void* EDX_Unused, DWORD* FECarRecord)
{
    unsigned int PresetHash = FECarRecord[0];
    char* PresetName;

    int NumberOfBonusCars = BonusCars.size();

    for (int i = 0; i < NumberOfBonusCars; i++)
    {
		if (BonusCars[i].Category == 0xF0008) // Is a bonus car
        {
			PresetName = BonusCars[i].PresetName;
            if (FEHashUpper(PresetName) == PresetHash) // If it's the preset we are checking
            {
                // Get and check if the condition is met
                int UnlockConditionType = BonusCars[i].UnlockConditionType;

				if (UnlockConditionType == 1)
					return BonusCars[i].Blacklist;
                else break;
            }
        }
    }

    return UIQRCarSelect_GetBonusUnlockBinNumber_Game(UIQRCarSelect, FECarRecord);
}