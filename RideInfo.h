#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

unsigned int __fastcall RideInfo_SetPart(DWORD* RideInfo, int EDX_Unused, int CarSlotID, unsigned int CarPart, bool UpdateEnabled)
{
	unsigned int PreviousPart;
	unsigned int KitNumber;
	unsigned int KitNameHash;
	unsigned int PartHash;
	char KitName[64];
	char PartName[255];

	switch (CarSlotID)
	{
	case 0: // BASE
		if (!CarPart)
		{
			InvalidBasePart:
			RideInfo[18 + 25] = 0; // FRONT_LEFT_WINDOW
			RideInfo[18 + 26] = 0; // FRONT_RIGHT_WINDOW
			RideInfo[18 + 27] = 0; // FRONT_WINDOW
			RideInfo[18 + 35] = 0; // REAR_LEFT_WINDOW
			RideInfo[18 + 36] = 0; // REAR_RIGHT_WINDOW
			RideInfo[18 + 37] = 0; // REAR_WINDOW
			RideInfo[18 + 70] = 0; // DECAL_FRONT_WINDOW_WIDE_MEDIUM
			RideInfo[18 + 71] = 0; // DECAL_REAR_WINDOW_WIDE_MEDIUM

			goto SetSinglePart;
		}
		
		// Apply glass and decal parts according to the base style
		sprintf(KitName, "%s_", GetCarTypeName(RideInfo[0]));
		KitNameHash = bStringHash(KitName);
		PartHash = bStringHash2("BASE", KitNameHash);

		if (*(unsigned int*)CarPart == PartHash)
		{
			// do nothing
		}
		else
		{
			for (int i = 0; i <= 99; i++)
			{
				sprintf(KitName, "%s_STYLE%02d_", GetCarTypeName(RideInfo[0]), i);
				KitNameHash = bStringHash(KitName);
				PartHash = bStringHash2("BASE", KitNameHash);
				if (*(unsigned int*)CarPart == PartHash)
				{
					break;
				}
				if (i == 99) goto InvalidBasePart;
			}
		}
		
		RideInfo[18 + 25] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 25, bStringHash2("FRONT_LEFT_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + 26] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 26, bStringHash2("FRONT_RIGHT_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + 27] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 27, bStringHash2("FRONT_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + 35] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 35, bStringHash2("REAR_LEFT_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + 36] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 36, bStringHash2("REAR_RIGHT_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + 37] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 37, bStringHash2("REAR_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + 70] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 70, bStringHash2("DECAL_FRONT_WINDOW_WIDE_MEDIUM", KitNameHash), 0, -1);
		RideInfo[18 + 71] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 71, bStringHash2("DECAL_REAR_WINDOW_WIDE_MEDIUM", KitNameHash), 0, -1);

		goto SetSinglePart;

	case 23: // BODY
		if (!CarPart)
		{
			RideInfo[18 + 46] = 0; // DAMAGE0_FRONT
			RideInfo[18 + 47] = 0; // DAMAGE0_FRONTLEFT
			RideInfo[18 + 48] = 0; // DAMAGE0_FRONTRIGHT
			RideInfo[18 + 49] = 0; // DAMAGE0_REAR
			RideInfo[18 + 50] = 0; // DAMAGE0_REARLEFT
			RideInfo[18 + 51] = 0; // DAMAGE0_REARRIGHT
			RideInfo[18 + 72] = 0; // DECAL_LEFT_DOOR_RECT_MEDIUM
			RideInfo[18 + 73] = 0; // DECAL_RIGHT_DOOR_RECT_MEDIUM
			RideInfo[18 + 74] = 0; // DECAL_LEFT_QUARTER_RECT_MEDIUM
			RideInfo[18 + 75] = 0; // DECAL_RIGHT_QUARTER_RECT_MEDIUM

			goto SetSinglePart;
		}
		KitNumber = CarPart_GetAppliedAttributeIParam((void*)CarPart, bStringHash("KITNUMBER"), 0);
		
		// Apply damage and decal parts according to the kit number
		sprintf(KitName, "%s_KIT%02d_", GetCarTypeName(RideInfo[0]), KitNumber);
		KitNameHash = bStringHash(KitName);
		RideInfo[18 + 46] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 46, bStringHash2("DAMAGE0_FRONT", KitNameHash), 0, -1); // DAMAGE0_FRONT
		RideInfo[18 + 47] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 47, bStringHash2("DAMAGE0_FRONTLEFT", KitNameHash), 0, -1); // DAMAGE0_FRONTLEFT
		RideInfo[18 + 48] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 48, bStringHash2("DAMAGE0_FRONTRIGHT", KitNameHash), 0, -1); // DAMAGE0_FRONTRIGHT
		RideInfo[18 + 49] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 49, bStringHash2("DAMAGE0_REAR", KitNameHash), 0, -1); // DAMAGE0_REAR
		RideInfo[18 + 50] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 50, bStringHash2("DAMAGE0_REARLEFT", KitNameHash), 0, -1); // DAMAGE0_REARLEFT
		RideInfo[18 + 51] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 51, bStringHash2("DAMAGE0_REARRIGHT", KitNameHash), 0, -1); // DAMAGE0_REARRIGHT
		RideInfo[18 + 72] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 72, bStringHash2("DECAL_LEFT_DOOR_RECT_MEDIUM", KitNameHash), 0, -1); // DECAL_LEFT_DOOR_RECT_MEDIUM
		RideInfo[18 + 73] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 73, bStringHash2("DECAL_RIGHT_DOOR_RECT_MEDIUM", KitNameHash), 0, -1); // DECAL_RIGHT_DOOR_RECT_MEDIUM
		RideInfo[18 + 74] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 74, bStringHash2("DECAL_LEFT_QUARTER_RECT_MEDIUM", KitNameHash), 0, -1); // DECAL_LEFT_QUARTER_RECT_MEDIUM
		RideInfo[18 + 75] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 75, bStringHash2("DECAL_RIGHT_QUARTER_RECT_MEDIUM", KitNameHash), 0, -1); // DECAL_RIGHT_QUARTER_RECT_MEDIUM
		
		goto SetSinglePart;

	case 24: // FRONT_BRAKE
		if (!CarPart)
		{
		InvalidBrakePart:
			RideInfo[18 + 34] = 0; // REAR_BRAKE

			goto SetSinglePart;
		}

		// Apply rear brake according to the front brake style
		sprintf(KitName, "%s_", GetCarTypeName(RideInfo[0]));
		KitNameHash = bStringHash(KitName);
		PartHash = bStringHash2("FRONT_BRAKE", KitNameHash);

		if (*(unsigned int*)CarPart == PartHash)
		{
			// do nothing
		}
		else
		{
			for (int i = 0; i <= 99; i++)
			{
				sprintf(KitName, "%s_STYLE%02d_", GetCarTypeName(RideInfo[0]), i);
				KitNameHash = bStringHash(KitName);
				PartHash = bStringHash2("FRONT_BRAKE", KitNameHash);
				if (*(unsigned int*)CarPart == PartHash)
				{
					break;
				}
				if (i == 99) goto GlobalBrakePart;
			}
		}

		RideInfo[18 + 34] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 34, bStringHash2("REAR_BRAKE", KitNameHash), 0, -1);
		goto SetSinglePart;

		// Global (BRAKES)
	GlobalBrakePart:
		PartHash = bStringHash("BRAKE_KIT00");
		if (*(unsigned int*)CarPart == PartHash)
		{
			// Do nothing
		}
		else
		{
			for (int i = 0; i <= 99; i++)
			{
				sprintf(KitName, "BRAKE_STYLE%02d", i);
				PartHash = bStringHash(KitName);
				if (*(unsigned int*)CarPart == PartHash)
				{
					break;
				}
				if (i == 99) goto InvalidBrakePart;
			}
		}

		RideInfo[18 + 34] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 33, PartHash, 0, -1);
		goto SetSinglePart;

	case 29: // LEFT_BRAKELIGHT
		if (!CarPart)
		{
		InvalidBrakelightPart:
			RideInfo[18 + 30] = 0; // LEFT_BRAKELIGHT_GLASS
			RideInfo[18 + 38] = 0; // RIGHT_BRAKELIGHT
			RideInfo[18 + 39] = 0; // RIGHT_BRAKELIGHT_GLASS

			goto SetSinglePart;
		}

		// Apply glass and decal parts according to the base style
		sprintf(KitName, "%s_", GetCarTypeName(RideInfo[0]));
		KitNameHash = bStringHash(KitName);
		PartHash = bStringHash2("LEFT_BRAKELIGHT", KitNameHash);

		if (*(unsigned int*)CarPart == PartHash)
		{
			// do nothing
		}
		else
		{
			for (int i = 0; i <= 99; i++)
			{
				sprintf(KitName, "%s_STYLE%02d_", GetCarTypeName(RideInfo[0]), i);
				KitNameHash = bStringHash(KitName);
				PartHash = bStringHash2("LEFT_BRAKELIGHT", KitNameHash);
				if (*(unsigned int*)CarPart == PartHash)
				{
					break;
				}
				if (i == 99) goto InvalidBrakelightPart;
			}
		}

		RideInfo[18 + 30] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 30, bStringHash2("LEFT_BRAKELIGHT_GLASS", KitNameHash), 0, -1);
		RideInfo[18 + 38] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 38, bStringHash2("RIGHT_BRAKELIGHT", KitNameHash), 0, -1);
		RideInfo[18 + 39] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 39, bStringHash2("RIGHT_BRAKELIGHT_GLASS", KitNameHash), 0, -1);

		goto SetSinglePart;

	case 31: // LEFT_HEADLIGHT
		if (!CarPart)
		{
		InvalidHeadlightPart:
			RideInfo[18 + 32] = 0; // LEFT_HEADLIGHT_GLASS
			RideInfo[18 + 40] = 0; // RIGHT_HEADLIGHT
			RideInfo[18 + 41] = 0; // RIGHT_HEADLIGHT_GLASS

			goto SetSinglePart;
		}

		// Apply glass and decal parts according to the base style
		sprintf(KitName, "%s_", GetCarTypeName(RideInfo[0]));
		KitNameHash = bStringHash(KitName);
		PartHash = bStringHash2("LEFT_HEADLIGHT", KitNameHash);

		if (*(unsigned int*)CarPart == PartHash)
		{
			// do nothing
		}
		else
		{
			for (int i = 0; i <= 99; i++)
			{
				sprintf(KitName, "%s_STYLE%02d_", GetCarTypeName(RideInfo[0]), i);
				KitNameHash = bStringHash(KitName);
				PartHash = bStringHash2("LEFT_HEADLIGHT", KitNameHash);
				if (*(unsigned int*)CarPart == PartHash)
				{
					break;
				}
				if (i == 99) goto InvalidHeadlightPart;
			}
		}

		RideInfo[18 + 32] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 32, bStringHash2("LEFT_HEADLIGHT_GLASS", KitNameHash), 0, -1);
		RideInfo[18 + 40] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 40, bStringHash2("RIGHT_HEADLIGHT", KitNameHash), 0, -1);
		RideInfo[18 + 41] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 41, bStringHash2("RIGHT_HEADLIGHT_GLASS", KitNameHash), 0, -1);
		
		goto SetSinglePart;

	case 33: // LEFT_SIDE_MIRROR
		if (!CarPart)
		{
		InvalidMirrorPart:
			RideInfo[18 + 42] = 0; // RIGHT_SIDE_MIRROR

			goto SetSinglePart;
		}

		// Apply glass and decal parts according to the base style
		sprintf(KitName, "%s_", GetCarTypeName(RideInfo[0]));
		KitNameHash = bStringHash(KitName);
		PartHash = bStringHash2("LEFT_SIDE_MIRROR", KitNameHash);

		if (*(unsigned int*)CarPart == PartHash)
		{
			// do nothing
		}
		else
		{
			for (int i = 0; i <= 99; i++)
			{
				sprintf(KitName, "%s_STYLE%02d_", GetCarTypeName(RideInfo[0]), i);
				KitNameHash = bStringHash(KitName);
				PartHash = bStringHash2("LEFT_SIDE_MIRROR", KitNameHash);
				if (*(unsigned int*)CarPart == PartHash)
				{
					break;
				}
				if (i == 99) goto InvalidMirrorPart;
			}
		}

		RideInfo[18 + 42] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 42, bStringHash2("RIGHT_SIDE_MIRROR", KitNameHash), 0, -1);

		goto SetSinglePart;

		// BODY
	case 46:	// DAMAGE0_FRONT
	case 47:	// DAMAGE0_FRONTLEFT
	case 48:	// DAMAGE0_FRONTRIGHT
	case 49:	// DAMAGE0_REAR
	case 50:	// DAMAGE0_REARLEFT
	case 51:	// DAMAGE0_REARRIGHT
	case 67:	// REAR_WHEEL
	case 72:	// DECAL_LEFT_DOOR_RECT_MEDIUM
	case 73:	// DECAL_RIGHT_DOOR_RECT_MEDIUM
	case 74:	// DECAL_LEFT_QUARTER_RECT_MEDIUM
	case 75:	// DECAL_RIGHT_QUARTER_RECT_MEDIUM
		// BASE
	case 25:	// FRONT_LEFT_WINDOW
	case 26:	// FRONT_RIGHT_WINDOW
	case 27:	// FRONT_WINDOW
	case 35:	// REAR_LEFT_WINDOW
	case 36:	// REAR_RIGHT_WINDOW
	case 37:	// REAR_WINDOW
	case 70:	// DECAL_FRONT_WINDOW_WIDE_MEDIUM
	case 71:	// DECAL_REAR_WINDOW_WIDE_MEDIUM
		// LEFT_HEADLIGHT
	case 32:	// LEFT_HEADLIGHT_GLASS
	case 40:	// RIGHT_HEADLIGHT
	case 41:	// RIGHT_HEADLIGHT_GLASS
		// LEFT_BRAKELIGHT
	case 30:	// LEFT_BRAKELIGHT_GLASS
	case 38:	// RIGHT_BRAKELIGHT
	case 39:	// RIGHT_BRAKELIGHT_GLASS
		// LEFT_SIDE_MIRROR
	case 42:	// RIGHT_SIDE_MIRROR
		// FRONT_BRAKE
	case 34:	// REAR_BRAKE
		return RideInfo[18 + CarSlotID];

	default:
	SetSinglePart:
		PreviousPart = RideInfo[18 + CarSlotID];
		RideInfo[18 + CarSlotID] = CarPart;
		if (UpdateEnabled)
			RideInfo_UpdatePartsEnabled(RideInfo);
		break;
	}

	return PreviousPart;
}
