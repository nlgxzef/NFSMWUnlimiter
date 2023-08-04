#include "stdio.h"
#include "InGameFunctions.h"

char StringBuffer[64];

int __fastcall PursuitBoard_SetNumCopsDestroyed(DWORD* PursuitBoard, int EDX_Unused, int NumberOfCopsDestroyed, unsigned int PVehicleHash, int ComboMultiplier, int BountyAward)
{
	int CopDestroyedStringCount = CopDestroyedStrings.size();

	int result = PursuitBoard[11];
	const char* CopDestroyedString = 0;
	DWORD* LocalPlayerPtr, * HudPtr, * GenericMessageHandle;

	if (NumberOfCopsDestroyed != result)
	{
		if (NumberOfCopsDestroyed > result)
		{
			for (int i = 1; i < CopDestroyedStringCount; i++)
			{
				if (CopDestroyedStrings[i].PVehicle == PVehicleHash)
				{
					CopDestroyedString = GetLocalizedString(CopDestroyedStrings[i].StringHash);
					break;
				}
			}

			if (!CopDestroyedString) // if doesn't exist
			{
				CopDestroyedString = GetLocalizedString(CopDestroyedStrings[0].StringHash); // use default one instead
			}

			if (CopDestroyedString)
			{
				if (BETACompatibility) bSNPrintf(StringBuffer, 63, CopDestroyedString, BountyAward, ComboMultiplier); // Bounty x Multiplier (500 x 2)
				else bSNPrintf(StringBuffer, 63, CopDestroyedString, BountyAward * ComboMultiplier); // Bounty*Multiplier (1000)

				// create onscreen message
				if (*(DWORD*)0x92D884) LocalPlayerPtr = *(DWORD**)0x92D87C;
				if (LocalPlayerPtr)
				{
					HudPtr = LocalPlayer_GetHud(*(DWORD**)LocalPlayerPtr);
					if (HudPtr)
					{
						GenericMessageHandle = UTL_COM_Object__IList_Find((DWORD*)HudPtr[1], IGenericMessage_IHandle);
						if (GenericMessageHandle) result = GenericMessage_RequestGenericMessage(GenericMessageHandle, (char const*)StringBuffer, 0, 0x8AB83EDB, bStringHash((char*)"COPS_TAKENOUT_ICON"), bStringHash((char*)"COPS"), 2);
					}
				}
			}
		}
		PursuitBoard[11] = NumberOfCopsDestroyed;
	}
	return result;
}