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

void __fastcall RideInfo_SetRandomParts(DWORD* RideInfo, void* EDX_Unused)
{
	int CustomizationLevel;

	// Set all parts as stock first
	RideInfo_SetStockParts(RideInfo);

	// If HPC is present, only randomize the car paint
	if (HPCCompatibility)
	{
		RideInfo_SetRandomPart(RideInfo, 76, -1); // BASE_PAINT
		return;
	}

	// Check UnlimiterData\\CARNAME.ini for custom random parts
	// Get CarType Info
	sprintf(CarTypeName, GetCarTypeName(RideInfo[0]));
	sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
	CIniReader CarINI(CarININame);
	CIniReader GeneralINI("UnlimiterData\\_General.ini");

	int CustomRandomParts = CarINI.ReadInteger("RandomParts", "CustomRandomParts", GeneralINI.ReadInteger("RandomParts", "CustomRandomParts", 0));
	if (CustomRandomParts)
	{
		if (CarINI.ReadInteger("RandomParts", "BodyKits", GeneralINI.ReadInteger("RandomParts", "BodyKits", 1)) != 0) RideInfo_SetRandomPart(RideInfo, 23, -1); // BODY
		if (CarINI.ReadInteger("RandomParts", "Spoilers", GeneralINI.ReadInteger("RandomParts", "Spoilers", 1)) != 0) RideInfo_SetRandomPart(RideInfo, 44, -1); // SPOILER
		if (CarINI.ReadInteger("RandomParts", "Rims", GeneralINI.ReadInteger("RandomParts", "Rims", 1)) != 0) RideInfo_SetRandomPart(RideInfo, 66, -1); // FRONT_WHEEL
		if (CarINI.ReadInteger("RandomParts", "Hoods", GeneralINI.ReadInteger("RandomParts", "Hoods", 1)) != 0) RideInfo_SetRandomPart(RideInfo, 63, -1); // HOOD
		if (CarINI.ReadInteger("RandomParts", "RoofScoops", GeneralINI.ReadInteger("RandomParts", "RoofScoops", 1)) != 0) RideInfo_SetRandomPart(RideInfo, 62, -1); // ROOF
		if (CarINI.ReadInteger("RandomParts", "Interior", GeneralINI.ReadInteger("RandomParts", "Interior", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 28, -1); // INTERIOR
		if (CarINI.ReadInteger("RandomParts", "Roof", GeneralINI.ReadInteger("RandomParts", "Roof", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 0, -1); // BASE
		if (CarINI.ReadInteger("RandomParts", "Brakes", GeneralINI.ReadInteger("RandomParts", "Brakes", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 24, -1); // FRONT_BRAKE
		if (CarINI.ReadInteger("RandomParts", "Headlights", GeneralINI.ReadInteger("RandomParts", "Headlights", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 31, -1); // LEFT_HEADLIGHT
		if (CarINI.ReadInteger("RandomParts", "Taillights", GeneralINI.ReadInteger("RandomParts", "Taillights", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 29, -1); // LEFT_BRAKELIGHT
		if (CarINI.ReadInteger("RandomParts", "Mirrors", GeneralINI.ReadInteger("RandomParts", "Mirrors", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 33, -1); // LEFT_SIDE_MIRROR
		if (CarINI.ReadInteger("RandomParts", "Attachment0", GeneralINI.ReadInteger("RandomParts", "Attachment0", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 52, -1); // ATTACHMENT0
		if (CarINI.ReadInteger("RandomParts", "Attachment1", GeneralINI.ReadInteger("RandomParts", "Attachment1", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 53, -1); // ATTACHMENT1
		if (CarINI.ReadInteger("RandomParts", "Attachment2", GeneralINI.ReadInteger("RandomParts", "Attachment2", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 54, -1); // ATTACHMENT2
		if (CarINI.ReadInteger("RandomParts", "Attachment3", GeneralINI.ReadInteger("RandomParts", "Attachment3", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 55, -1); // ATTACHMENT3
		if (CarINI.ReadInteger("RandomParts", "Attachment4", GeneralINI.ReadInteger("RandomParts", "Attachment4", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 56, -1); // ATTACHMENT4
		if (CarINI.ReadInteger("RandomParts", "Attachment5", GeneralINI.ReadInteger("RandomParts", "Attachment5", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 57, -1); // ATTACHMENT5
		if (CarINI.ReadInteger("RandomParts", "Attachment6", GeneralINI.ReadInteger("RandomParts", "Attachment6", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 58, -1); // ATTACHMENT6
		if (CarINI.ReadInteger("RandomParts", "Attachment7", GeneralINI.ReadInteger("RandomParts", "Attachment7", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 59, -1); // ATTACHMENT7
		if (CarINI.ReadInteger("RandomParts", "Attachment8", GeneralINI.ReadInteger("RandomParts", "Attachment8", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 60, -1); // ATTACHMENT8
		if (CarINI.ReadInteger("RandomParts", "Attachment9", GeneralINI.ReadInteger("RandomParts", "Attachment9", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 61, -1); // ATTACHMENT9
		if (CarINI.ReadInteger("RandomParts", "Paint", GeneralINI.ReadInteger("RandomParts", "Paint", 1)) != 0) RideInfo_SetRandomPart(RideInfo, 76, -1); // BASE_PAINT
		if (CarINI.ReadInteger("RandomParts", "Vinyls", GeneralINI.ReadInteger("RandomParts", "Vinyls", 1)) != 0)
		{
			RideInfo_SetRandomPart(RideInfo, 77, -1); // VINYL_LAYER0
			RideInfo_SetRandomPart(RideInfo, 79, -1); // VINYL_COLOUR0_0
			RideInfo_SetRandomPart(RideInfo, 80, -1); // VINYL_COLOUR0_1
			RideInfo_SetRandomPart(RideInfo, 81, -1); // VINYL_COLOUR0_2
			RideInfo_SetRandomPart(RideInfo, 82, -1); // VINYL_COLOUR0_3
		}
		if (CarINI.ReadInteger("RandomParts", "RimPaint", GeneralINI.ReadInteger("RandomParts", "RimPaint", 1)) != 0) RideInfo_SetRandomPart(RideInfo, 78, -1); // PAINT_RIM
		if (CarINI.ReadInteger("RandomParts", "WindowTint", GeneralINI.ReadInteger("RandomParts", "WindowTint", 1)) != 0) RideInfo_SetRandomPart(RideInfo, 131, -1); // WINDOW_TINT
		if (CarINI.ReadInteger("RandomParts", "DecalsWindshield1", GeneralINI.ReadInteger("RandomParts", "DecalsWindshield1", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 83, -1); // DECAL_FRONT_WINDOW_TEX0
		if (CarINI.ReadInteger("RandomParts", "DecalsWindshield2", GeneralINI.ReadInteger("RandomParts", "DecalsWindshield2", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 84, -1); // DECAL_FRONT_WINDOW_TEX1
		if (CarINI.ReadInteger("RandomParts", "DecalsWindshield3", GeneralINI.ReadInteger("RandomParts", "DecalsWindshield3", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 85, -1); // DECAL_FRONT_WINDOW_TEX2
		if (CarINI.ReadInteger("RandomParts", "DecalsWindshield4", GeneralINI.ReadInteger("RandomParts", "DecalsWindshield4", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 86, -1); // DECAL_FRONT_WINDOW_TEX3
		if (CarINI.ReadInteger("RandomParts", "DecalsWindshield5", GeneralINI.ReadInteger("RandomParts", "DecalsWindshield5", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 87, -1); // DECAL_FRONT_WINDOW_TEX4
		if (CarINI.ReadInteger("RandomParts", "DecalsWindshield6", GeneralINI.ReadInteger("RandomParts", "DecalsWindshield6", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 88, -1); // DECAL_FRONT_WINDOW_TEX5
		if (CarINI.ReadInteger("RandomParts", "DecalsWindshield7", GeneralINI.ReadInteger("RandomParts", "DecalsWindshield7", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 89, -1); // DECAL_FRONT_WINDOW_TEX6
		if (CarINI.ReadInteger("RandomParts", "DecalsWindshield8", GeneralINI.ReadInteger("RandomParts", "DecalsWindshield8", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 90, -1); // DECAL_FRONT_WINDOW_TEX7
		if (CarINI.ReadInteger("RandomParts", "DecalsRearWindow1", GeneralINI.ReadInteger("RandomParts", "DecalsRearWindow1", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 91, -1); // DECAL_REAR_WINDOW_TEX0
		if (CarINI.ReadInteger("RandomParts", "DecalsRearWindow2", GeneralINI.ReadInteger("RandomParts", "DecalsRearWindow2", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 92, -1); // DECAL_REAR_WINDOW_TEX1
		if (CarINI.ReadInteger("RandomParts", "DecalsRearWindow3", GeneralINI.ReadInteger("RandomParts", "DecalsRearWindow3", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 93, -1); // DECAL_REAR_WINDOW_TEX2
		if (CarINI.ReadInteger("RandomParts", "DecalsRearWindow4", GeneralINI.ReadInteger("RandomParts", "DecalsRearWindow4", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 94, -1); // DECAL_REAR_WINDOW_TEX3
		if (CarINI.ReadInteger("RandomParts", "DecalsRearWindow5", GeneralINI.ReadInteger("RandomParts", "DecalsRearWindow5", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 95, -1); // DECAL_REAR_WINDOW_TEX4
		if (CarINI.ReadInteger("RandomParts", "DecalsRearWindow6", GeneralINI.ReadInteger("RandomParts", "DecalsRearWindow6", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 96, -1); // DECAL_REAR_WINDOW_TEX5
		if (CarINI.ReadInteger("RandomParts", "DecalsRearWindow7", GeneralINI.ReadInteger("RandomParts", "DecalsRearWindow7", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 97, -1); // DECAL_REAR_WINDOW_TEX6
		if (CarINI.ReadInteger("RandomParts", "DecalsRearWindow8", GeneralINI.ReadInteger("RandomParts", "DecalsRearWindow8", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 98, -1); // DECAL_REAR_WINDOW_TEX7
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftDoor1", GeneralINI.ReadInteger("RandomParts", "DecalsLeftDoor1", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 99, -1); // DECAL_LEFT_DOOR_TEX0
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftDoor2", GeneralINI.ReadInteger("RandomParts", "DecalsLeftDoor2", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 100, -1); // DECAL_LEFT_DOOR_TEX1
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftDoor3", GeneralINI.ReadInteger("RandomParts", "DecalsLeftDoor3", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 101, -1); // DECAL_LEFT_DOOR_TEX2
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftDoor4", GeneralINI.ReadInteger("RandomParts", "DecalsLeftDoor4", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 102, -1); // DECAL_LEFT_DOOR_TEX3
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftDoor5", GeneralINI.ReadInteger("RandomParts", "DecalsLeftDoor5", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 103, -1); // DECAL_LEFT_DOOR_TEX4
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftDoor6", GeneralINI.ReadInteger("RandomParts", "DecalsLeftDoor6", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 104, -1); // DECAL_LEFT_DOOR_TEX5
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftDoor7", GeneralINI.ReadInteger("RandomParts", "DecalsLeftDoor7", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 105, -1); // DECAL_LEFT_DOOR_TEX6
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftDoor8", GeneralINI.ReadInteger("RandomParts", "DecalsLeftDoor8", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 106, -1); // DECAL_LEFT_DOOR_TEX7
		if (CarINI.ReadInteger("RandomParts", "DecalsRightDoor1", GeneralINI.ReadInteger("RandomParts", "DecalsRightDoor1", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 107, -1); // DECAL_RIGHT_DOOR_TEX0
		if (CarINI.ReadInteger("RandomParts", "DecalsRightDoor2", GeneralINI.ReadInteger("RandomParts", "DecalsRightDoor2", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 108, -1); // DECAL_RIGHT_DOOR_TEX1
		if (CarINI.ReadInteger("RandomParts", "DecalsRightDoor3", GeneralINI.ReadInteger("RandomParts", "DecalsRightDoor3", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 109, -1); // DECAL_RIGHT_DOOR_TEX2
		if (CarINI.ReadInteger("RandomParts", "DecalsRightDoor4", GeneralINI.ReadInteger("RandomParts", "DecalsRightDoor4", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 110, -1); // DECAL_RIGHT_DOOR_TEX3
		if (CarINI.ReadInteger("RandomParts", "DecalsRightDoor5", GeneralINI.ReadInteger("RandomParts", "DecalsRightDoor5", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 111, -1); // DECAL_RIGHT_DOOR_TEX4
		if (CarINI.ReadInteger("RandomParts", "DecalsRightDoor6", GeneralINI.ReadInteger("RandomParts", "DecalsRightDoor6", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 112, -1); // DECAL_RIGHT_DOOR_TEX5
		if (CarINI.ReadInteger("RandomParts", "DecalsRightDoor7", GeneralINI.ReadInteger("RandomParts", "DecalsRightDoor7", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 113, -1); // DECAL_RIGHT_DOOR_TEX6
		if (CarINI.ReadInteger("RandomParts", "DecalsRightDoor8", GeneralINI.ReadInteger("RandomParts", "DecalsRightDoor8", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 114, -1); // DECAL_RIGHT_DOOR_TEX7
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftQuarter1", GeneralINI.ReadInteger("RandomParts", "DecalsLeftQuarter1", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 115, -1); // DECAL_LEFT_QUARTER_TEX0
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftQuarter2", GeneralINI.ReadInteger("RandomParts", "DecalsLeftQuarter2", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 116, -1); // DECAL_LEFT_QUARTER_TEX1
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftQuarter3", GeneralINI.ReadInteger("RandomParts", "DecalsLeftQuarter3", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 117, -1); // DECAL_LEFT_QUARTER_TEX2
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftQuarter4", GeneralINI.ReadInteger("RandomParts", "DecalsLeftQuarter4", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 118, -1); // DECAL_LEFT_QUARTER_TEX3
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftQuarter5", GeneralINI.ReadInteger("RandomParts", "DecalsLeftQuarter5", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 119, -1); // DECAL_LEFT_QUARTER_TEX4
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftQuarter6", GeneralINI.ReadInteger("RandomParts", "DecalsLeftQuarter6", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 120, -1); // DECAL_LEFT_QUARTER_TEX5
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftQuarter7", GeneralINI.ReadInteger("RandomParts", "DecalsLeftQuarter7", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 121, -1); // DECAL_LEFT_QUARTER_TEX6
		if (CarINI.ReadInteger("RandomParts", "DecalsLeftQuarter8", GeneralINI.ReadInteger("RandomParts", "DecalsLeftQuarter8", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 122, -1); // DECAL_LEFT_QUARTER_TEX7
		if (CarINI.ReadInteger("RandomParts", "DecalsRightQuarter1", GeneralINI.ReadInteger("RandomParts", "DecalsRightQuarter1", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 123, -1); // DECAL_RIGHT_QUARTER_TEX0
		if (CarINI.ReadInteger("RandomParts", "DecalsRightQuarter2", GeneralINI.ReadInteger("RandomParts", "DecalsRightQuarter2", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 124, -1); // DECAL_RIGHT_QUARTER_TEX1
		if (CarINI.ReadInteger("RandomParts", "DecalsRightQuarter3", GeneralINI.ReadInteger("RandomParts", "DecalsRightQuarter3", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 125, -1); // DECAL_RIGHT_QUARTER_TEX2
		if (CarINI.ReadInteger("RandomParts", "DecalsRightQuarter4", GeneralINI.ReadInteger("RandomParts", "DecalsRightQuarter4", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 126, -1); // DECAL_RIGHT_QUARTER_TEX3
		if (CarINI.ReadInteger("RandomParts", "DecalsRightQuarter5", GeneralINI.ReadInteger("RandomParts", "DecalsRightQuarter5", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 127, -1); // DECAL_RIGHT_QUARTER_TEX4
		if (CarINI.ReadInteger("RandomParts", "DecalsRightQuarter6", GeneralINI.ReadInteger("RandomParts", "DecalsRightQuarter6", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 128, -1); // DECAL_RIGHT_QUARTER_TEX5
		if (CarINI.ReadInteger("RandomParts", "DecalsRightQuarter7", GeneralINI.ReadInteger("RandomParts", "DecalsRightQuarter7", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 129, -1); // DECAL_RIGHT_QUARTER_TEX6
		if (CarINI.ReadInteger("RandomParts", "DecalsRightQuarter8", GeneralINI.ReadInteger("RandomParts", "DecalsRightQuarter8", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 130, -1); // DECAL_RIGHT_QUARTER_TEX7
		if (CarINI.ReadInteger("RandomParts", "Driver", GeneralINI.ReadInteger("RandomParts", "Driver", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 43, -1); // DRIVER
		if (CarINI.ReadInteger("RandomParts", "LicensePlate", GeneralINI.ReadInteger("RandomParts", "LicensePlate", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 69, -1); // LICENSE_PLATE
		if (CarINI.ReadInteger("RandomParts", "Tires", GeneralINI.ReadInteger("RandomParts", "Tires", 0)) != 0) RideInfo_SetRandomPart(RideInfo, 64, -1); // HEADLIGHT

		return;
	}

	// Or, check the customization level for vanilla randomization
	int ForceCustomizationLevel = CarINI.ReadInteger("RandomParts", "ForceCustomizationLevel", GeneralINI.ReadInteger("RandomParts", "ForceCustomizationLevel", -2));

	// -2 = Random customization level
	// -1 = Nothing
	// 0 = Body, Spoiler, Rims and Paint (Carbon)
	// 1 = Paint and Vinyls
	// 2 = Body, Spoiler, Rims, Window Tint, Roof Scoops, Hood + Level 1
	if (ForceCustomizationLevel == -2) CustomizationLevel = bRandom(3u);
	else CustomizationLevel = ForceCustomizationLevel;

	if (ForceStockPartsOnAddOnOpponents && RideInfo[0] >= 84)
	{
		switch (CustomizationLevel) // Add-On with stock body parts
		{
		case 2:
			// Body parts
			RideInfo_SetRandomPart(RideInfo, 66, -1); // FRONT_WHEEL
			RideInfo_SetRandomPart(RideInfo, 78, -1); // PAINT_RIM
			RideInfo_SetRandomPart(RideInfo, 131, -1); // WINDOW_TINT
		case 1:
			// Paint and vinyls
			RideInfo_SetRandomPart(RideInfo, 76, -1); // BASE_PAINT
			RideInfo_SetRandomPart(RideInfo, 77, -1); // VINYL_LAYER0
			RideInfo_SetRandomPart(RideInfo, 79, -1); // VINYL_COLOUR0_0
			RideInfo_SetRandomPart(RideInfo, 80, -1); // VINYL_COLOUR0_1
			RideInfo_SetRandomPart(RideInfo, 81, -1); // VINYL_COLOUR0_2
			RideInfo_SetRandomPart(RideInfo, 82, -1); // VINYL_COLOUR0_3
			break;
		case 0:
		default:
			// Pretty much Carbon.
			RideInfo_SetRandomPart(RideInfo, 76, -1); // BASE_PAINT
			RideInfo_SetRandomPart(RideInfo, 66, -1); // FRONT_WHEEL
			RideInfo_SetRandomPart(RideInfo, 78, -1); // PAINT_RIM
			break;
		case -1:
			// Nothing. Bone stock.
			break;
		}
	}
	else
	{
		switch (CustomizationLevel)
		{
		case 2:
			// Body parts
			RideInfo_SetRandomPart(RideInfo, 23, -1); // BODY
			RideInfo_SetRandomPart(RideInfo, 44, -1); // SPOILER
			RideInfo_SetRandomPart(RideInfo, 66, -1); // FRONT_WHEEL
			RideInfo_SetRandomPart(RideInfo, 78, -1); // PAINT_RIM
			RideInfo_SetRandomPart(RideInfo, 131, -1); // WINDOW_TINT
			RideInfo_SetRandomPart(RideInfo, 62, -1); // ROOF
			RideInfo_SetRandomPart(RideInfo, 63, -1); // HOOD
		case 1:
			// Paint and vinyls
			RideInfo_SetRandomPart(RideInfo, 76, -1); // BASE_PAINT
			RideInfo_SetRandomPart(RideInfo, 77, -1); // VINYL_LAYER0
			RideInfo_SetRandomPart(RideInfo, 79, -1); // VINYL_COLOUR0_0
			RideInfo_SetRandomPart(RideInfo, 80, -1); // VINYL_COLOUR0_1
			RideInfo_SetRandomPart(RideInfo, 81, -1); // VINYL_COLOUR0_2
			RideInfo_SetRandomPart(RideInfo, 82, -1); // VINYL_COLOUR0_3
			break;
		case 0:
		default:
			// Pretty much Carbon.
			RideInfo_SetRandomPart(RideInfo, 23, -1); // BODY
			RideInfo_SetRandomPart(RideInfo, 44, -1); // SPOILER
			RideInfo_SetRandomPart(RideInfo, 76, -1); // BASE_PAINT
			RideInfo_SetRandomPart(RideInfo, 66, -1); // FRONT_WHEEL
			RideInfo_SetRandomPart(RideInfo, 78, -1); // PAINT_RIM
			break;
		case -1:
			// Nothing. Bone stock.
			break;
		}
	}
}