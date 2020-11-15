#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

char StringID[15];
char StringBuffer[64];

int __fastcall PursuitBoard_SetNumCopsDestroyed(DWORD* PursuitBoard, int EDX_Unused, int NumberOfCopsDestroyed, unsigned int PVehicleHash, int ComboMultiplier, int BountyAward)
{
	CIniReader CopDestroyedStringsINI("UnlimiterData\\_CopDestroyedStrings.ini");
	int CopDestroyedStringCount = CopDestroyedStringsINI.ReadInteger("CopDestroyedStrings", "NumberOfCopDestroyedStrings", -1);

	if (CopDestroyedStringCount == -1) return PursuitBoard_SetNumCopsDestroyed_Game(PursuitBoard, NumberOfCopsDestroyed, PVehicleHash, ComboMultiplier, BountyAward);

	int result = PursuitBoard[11];
	const char* CopDestroyedString;
	DWORD* LocalPlayerPtr, * HudPtr, * GenericMessageHandle;

	if (NumberOfCopsDestroyed != result)
	{
		if (NumberOfCopsDestroyed > result)
		{
			for (int i = 1; i <= CopDestroyedStringCount; i++)
			{
				sprintf(StringID, "String%d", i);
				if (stringhash32(CopDestroyedStringsINI.ReadString(StringID, "PVehicle", "")) == PVehicleHash)
				{
					CopDestroyedString = GetLocalizedString(bStringHash(CopDestroyedStringsINI.ReadString(StringID, "String", "ERROR_DEFAULT_STRING")));
					break;
				}
				if (i == CopDestroyedStringCount) CopDestroyedString = 0;
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
						if (GenericMessageHandle) result = GenericMessage_RequestGenericMessage(GenericMessageHandle, (char const*)StringBuffer, 0, 0x8AB83EDB, bStringHash("COPS_TAKENOUT_ICON"), bStringHash("COPS"), 2);
					}
				}
			}
		}
		PursuitBoard[11] = NumberOfCopsDestroyed;
	}
	return result;
}