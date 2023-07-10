#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

unsigned int __fastcall RideInfo_SetPart(DWORD* RideInfo, void* EDX_Unused, int CarSlotID, unsigned int CarPart, bool UpdateEnabled)
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
/*
	case 67: // REAR_WHEEL
		if (!CarPart)
		{
		InvalidRearWheelPart:
			RideInfo[18 + 67] = 0; // REAR_WHEEL

			goto SetSinglePart;
		}

		// Apply rear wheel according to the front wheel style
		PartHash = bStringHash2("_REAR", *(unsigned int*)CarPart);

		PreviousPart = RideInfo[18 + 67];
		RideInfo[18 + 67] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], 67, PartHash, 0, -1); // If it has rear wheel
		if (!RideInfo[18 + 67)) RideInfo[18 + 67] = PreviousPart; // Or else, reapply the previous part

		goto SetSinglePart;*/

		// BODY
	case 46:	// DAMAGE0_FRONT
	case 47:	// DAMAGE0_FRONTLEFT
	case 48:	// DAMAGE0_FRONTRIGHT
	case 49:	// DAMAGE0_REAR
	case 50:	// DAMAGE0_REARLEFT
	case 51:	// DAMAGE0_REARRIGHT
	//case 67:	// REAR_WHEEL
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

unsigned int __fastcall RideInfo_SetRandomDecal(DWORD* RideInfo, void* EDX_Unused, int CarSlotID, int UpgradeLevel)
{
	DWORD* NewPart = 0, * LeftNumberPart = 0;
	int NumCarParts = CarPartDatabase_NewGetNumCarParts((DWORD*)_CarPartDB, RideInfo[0], CarSlotID, 0, UpgradeLevel);
	int rnd, ctr;
	DWORD BrandNameHash;
	bool IsNumberLeft = false, IsNumberRight = false;

	if (NumCarParts)
	{
		rnd = bRandom(NumCarParts) + 1;
		if (rnd > 0)
		{
			for (ctr = rnd; ctr; --ctr)
			{
				NewPart = (DWORD*)CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CarSlotID, 0, (DWORD)NewPart, UpgradeLevel);
			}
		}

		if (NewPart)
		{
			BrandNameHash = CarPart_GetBrandName(NewPart);
			if (BrandNameHash == bStringHash("NUMBER_LEFT")) IsNumberLeft = true;
			if (BrandNameHash == bStringHash("NUMBER_RIGHT")) IsNumberRight = true;

			// 105, 106, 113, 114 (DECAL_[LEFT/RIGHT]_DOOR_TEX[6/7])
			switch (CarSlotID)
			{
			case 105: // DECAL_LEFT_DOOR_TEX6
				if (IsNumberLeft) return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, (DWORD)NewPart, 1);
				return 0;
				break;

			case 106: // DECAL_LEFT_DOOR_TEX7
				LeftNumberPart = RideInfo_GetPart(RideInfo, 105);

				if (LeftNumberPart && IsNumberRight) return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, (DWORD)NewPart, 1);
				RideInfo_SetPart(RideInfo, EDX_Unused, 105, 0, 1);
				return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, 0, 1);
				break;

			case 113: // DECAL_RIGHT_DOOR_TEX6
				return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, (DWORD)RideInfo_GetPart(RideInfo, 105), 1);
				break;

			case 114: // DECAL_RIGHT_DOOR_TEX7
				return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, (DWORD)RideInfo_GetPart(RideInfo, 106), 1);
				break;

			default:
				if (!IsNumberLeft && !IsNumberRight) return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, (DWORD)NewPart, 1);
				return 0;
				break;
			}
		}
	}

	return 0;
}

void __fastcall RideInfo_SetStockParts(DWORD* TheRideInfo, void* EDX_Unused)
{
	DWORD PartNameHash; // eax MAPDST
	DWORD TheCarPart; // eax MAPDST
	int VinylColorSlotID; // edi
	DWORD* VinylColorRef; // ebx
	int NumVinylLayers; // ebp
	DWORD DefaultVinylColors[4]; // [esp+8h] [ebp-18h] BYREF

	int CarType = TheRideInfo[0];

	DefaultVinylColors[0] = bStringHash("VINYL_L1_COLOR01"); // 255, 255, 255, 100
	DefaultVinylColors[1] = bStringHash("VINYL_L1_COLOR03"); // 255, 251, 224, 100
	DefaultVinylColors[2] = bStringHash("VINYL_L1_COLOR61"); // VINYL_L2_COLOR11 (129, 130, 120, 100) Doesn't exist in vanilla game
	DefaultVinylColors[3] = bStringHash("VINYL_L1_COLOR01"); // 255, 255, 255, 100

	for (int CarSlotID = 0; CarSlotID < 139; ++CarSlotID)
	{
		// (Type != COPHELI || != ATTACHMENT6) && (!VINYL_LAYER0) && (< VINYL_LAYER0 || > DECAL_RIGHT_QUARTER_TEX7)
		if ((CarType != 4 || CarSlotID != 58) && (CarSlotID != 77) && (CarSlotID < 77 || CarSlotID > 130))
		{
			switch (CarSlotID)
			{
			case 76: // BASE_PAINT
				PartNameHash = *(DWORD*)(208 * CarType + *(DWORD*)CarTypeInfoArray + 204);
				TheCarPart = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, CarType, CarSlotID, PartNameHash, 0, -1);
				if (TheCarPart) RideInfo_SetPart(TheRideInfo, EDX_Unused, CarSlotID, TheCarPart, 1);
				else // If the paint is invalid
				{
					PartNameHash = bStringHash("GLOSS_L1_COLOR01");
					TheCarPart = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, CarType, CarSlotID, PartNameHash, 0, -1);
					if (TheCarPart) RideInfo_SetPart(TheRideInfo, EDX_Unused, CarSlotID, TheCarPart, 1);
				}
				break;

			case 62: // ROOF
				PartNameHash = bStringHash("ROOF_STYLE00");
				goto ApplyPart;
				break;

			case 64: // HEADLIGHT (Tires)
				PartNameHash = bStringHash("TIRE_STYLE01");
				goto ApplyPart;
				break;

			case 65: // BRAKELIGHT (Neon)
				PartNameHash = bStringHash("NEON_NONE");
				goto ApplyPart;
				break;

			case 133: // HUD_BACKING_COLOUR
			case 134: // HUD_NEEDLE_COLOUR
				PartNameHash = bStringHash("ORANGE");
					goto ApplyPart;
					break;

			case 135: // HUD_CHARACTER_COLOUR
				PartNameHash = bStringHash("WHITE");

			ApplyPart:
				TheCarPart = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, CarType, CarSlotID, PartNameHash, 0, -1);
				if (TheCarPart) RideInfo_SetPart(TheRideInfo, EDX_Unused, CarSlotID, TheCarPart, 1);
				else RideInfo_SetUpgradePart(TheRideInfo, CarSlotID, 0);
				break;

			default: // Apply the first available part with upgrade level 0
				RideInfo_SetUpgradePart(TheRideInfo, CarSlotID, 0);
				break;
			}
		}
		// else: No need to assign, RideInfo inits them with 0
	}

	VinylColorSlotID = 79; // VINYL_COLOUR0_0
	VinylColorRef = DefaultVinylColors;
	NumVinylLayers = 4;
	do
	{
		TheCarPart = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, CarType, VinylColorSlotID, *VinylColorRef, 0, -1);
		RideInfo_SetPart(TheRideInfo, EDX_Unused, VinylColorSlotID, TheCarPart, 1);
		++VinylColorRef;
		++VinylColorSlotID;
		--NumVinylLayers;
	} while (NumVinylLayers);
}

void __fastcall RideInfo_SetRandomParts(DWORD* RideInfo, void* EDX_Unused)
{
	int CustomizationLevel, RearRimsHeadsOrTails;

	// Set all parts as stock first
	RideInfo_SetStockParts(RideInfo, EDX_Unused);

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

	// Flip a coin for rear rims
	RearRimsHeadsOrTails = bRandom(2);

	// Get num attachments
	int NumAttachments = GetCarIntOption(CarINI, GeneralINI, "Parts", "Attachments", 0) % 11;

	int CustomRandomParts = GetCarIntOption(CarINI, GeneralINI, "RandomParts", "CustomRandomParts", 0);
	if (CustomRandomParts)
	{
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "BodyKits", 1) != 0) RideInfo_SetRandomPart(RideInfo, 23, -1); // BODY
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Spoilers", 1) != 0) RideInfo_SetRandomPart(RideInfo, 44, -1); // SPOILER
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Rims", 1) != 0)
		{
			RideInfo_SetRandomPart(RideInfo, 66, -1); // FRONT_WHEEL
			if (RearRimsHeadsOrTails) RideInfo_SetRandomPart(RideInfo, 67, -1); // REAR_WHEEL
			else RideInfo_SetPart(RideInfo, EDX_Unused, 67, (DWORD)RideInfo_GetPart(RideInfo, 66), 1);
		}
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Hoods", 1) != 0) RideInfo_SetRandomPart(RideInfo, 63, -1); // HOOD
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "RoofScoops", 1) != 0) RideInfo_SetRandomPart(RideInfo, 62, -1); // ROOF
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Interior", 0) != 0) RideInfo_SetRandomPart(RideInfo, 28, -1); // INTERIOR
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Roof", 0) != 0) RideInfo_SetRandomPart(RideInfo, 0, -1); // BASE
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Brakes", 0) != 0) RideInfo_SetRandomPart(RideInfo, 24, -1); // FRONT_BRAKE
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Headlights", 0) != 0) RideInfo_SetRandomPart(RideInfo, 31, -1); // LEFT_HEADLIGHT
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Taillights", 0) != 0) RideInfo_SetRandomPart(RideInfo, 29, -1); // LEFT_BRAKELIGHT
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Mirrors", 0) != 0) RideInfo_SetRandomPart(RideInfo, 33, -1); // LEFT_SIDE_MIRROR
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Attachment0", 0) != 0) RideInfo_SetRandomPart(RideInfo, 52, -1); // ATTACHMENT0
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Attachment1", 0) != 0) RideInfo_SetRandomPart(RideInfo, 53, -1); // ATTACHMENT1
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Attachment2", 0) != 0) RideInfo_SetRandomPart(RideInfo, 54, -1); // ATTACHMENT2
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Attachment3", 0) != 0) RideInfo_SetRandomPart(RideInfo, 55, -1); // ATTACHMENT3
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Attachment4", 0) != 0) RideInfo_SetRandomPart(RideInfo, 56, -1); // ATTACHMENT4
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Attachment5", 0) != 0) RideInfo_SetRandomPart(RideInfo, 57, -1); // ATTACHMENT5
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Attachment6", 0) != 0) RideInfo_SetRandomPart(RideInfo, 58, -1); // ATTACHMENT6
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Attachment7", 0) != 0) RideInfo_SetRandomPart(RideInfo, 59, -1); // ATTACHMENT7
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Attachment8", 0) != 0) RideInfo_SetRandomPart(RideInfo, 60, -1); // ATTACHMENT8
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Attachment9", 0) != 0) RideInfo_SetRandomPart(RideInfo, 61, -1); // ATTACHMENT9
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Paint", 1) != 0) RideInfo_SetRandomPart(RideInfo, 76, -1); // BASE_PAINT
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Vinyls", 1) != 0)
		{
			RideInfo_SetRandomPart(RideInfo, 77, -1); // VINYL_LAYER0
			RideInfo_SetRandomPart(RideInfo, 79, -1); // VINYL_COLOUR0_0
			RideInfo_SetRandomPart(RideInfo, 80, -1); // VINYL_COLOUR0_1
			RideInfo_SetRandomPart(RideInfo, 81, -1); // VINYL_COLOUR0_2
			RideInfo_SetRandomPart(RideInfo, 82, -1); // VINYL_COLOUR0_3
		}
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "RimPaint", 1) != 0) RideInfo_SetRandomPart(RideInfo, 78, -1); // PAINT_RIM
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "WindowTint", 1) != 0) RideInfo_SetRandomPart(RideInfo, 131, -1); // WINDOW_TINT
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsWindshield1", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 83, -1); // DECAL_FRONT_WINDOW_TEX0
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsWindshield2", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 84, -1); // DECAL_FRONT_WINDOW_TEX1
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsWindshield3", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 85, -1); // DECAL_FRONT_WINDOW_TEX2
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsWindshield4", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 86, -1); // DECAL_FRONT_WINDOW_TEX3
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsWindshield5", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 87, -1); // DECAL_FRONT_WINDOW_TEX4
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsWindshield6", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 88, -1); // DECAL_FRONT_WINDOW_TEX5
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsWindshield7", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 89, -1); // DECAL_FRONT_WINDOW_TEX6
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsWindshield8", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 90, -1); // DECAL_FRONT_WINDOW_TEX7
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRearWindow1", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 91, -1); // DECAL_REAR_WINDOW_TEX0
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRearWindow2", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 92, -1); // DECAL_REAR_WINDOW_TEX1
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRearWindow3", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 93, -1); // DECAL_REAR_WINDOW_TEX2
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRearWindow4", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 94, -1); // DECAL_REAR_WINDOW_TEX3
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRearWindow5", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 95, -1); // DECAL_REAR_WINDOW_TEX4
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRearWindow6", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 96, -1); // DECAL_REAR_WINDOW_TEX5
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRearWindow7", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 97, -1); // DECAL_REAR_WINDOW_TEX6
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRearWindow8", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 98, -1); // DECAL_REAR_WINDOW_TEX7
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftDoor1", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 99, -1); // DECAL_LEFT_DOOR_TEX0
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftDoor2", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 100, -1); // DECAL_LEFT_DOOR_TEX1
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftDoor3", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 101, -1); // DECAL_LEFT_DOOR_TEX2
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftDoor4", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 102, -1); // DECAL_LEFT_DOOR_TEX3
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftDoor5", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 103, -1); // DECAL_LEFT_DOOR_TEX4
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftDoor6", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 104, -1); // DECAL_LEFT_DOOR_TEX5
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftDoor7", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 105, -1); // DECAL_LEFT_DOOR_TEX6
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftDoor8", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 106, -1); // DECAL_LEFT_DOOR_TEX7
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightDoor1", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 107, -1); // DECAL_RIGHT_DOOR_TEX0
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightDoor2", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 108, -1); // DECAL_RIGHT_DOOR_TEX1
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightDoor3", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 109, -1); // DECAL_RIGHT_DOOR_TEX2
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightDoor4", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 110, -1); // DECAL_RIGHT_DOOR_TEX3
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightDoor5", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 111, -1); // DECAL_RIGHT_DOOR_TEX4
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightDoor6", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 112, -1); // DECAL_RIGHT_DOOR_TEX5
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightDoor7", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 113, -1); // DECAL_RIGHT_DOOR_TEX6
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightDoor8", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 114, -1); // DECAL_RIGHT_DOOR_TEX7
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftQuarter1", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 115, -1); // DECAL_LEFT_QUARTER_TEX0
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftQuarter2", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 116, -1); // DECAL_LEFT_QUARTER_TEX1
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftQuarter3", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 117, -1); // DECAL_LEFT_QUARTER_TEX2
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftQuarter4", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 118, -1); // DECAL_LEFT_QUARTER_TEX3
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftQuarter5", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 119, -1); // DECAL_LEFT_QUARTER_TEX4
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftQuarter6", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 120, -1); // DECAL_LEFT_QUARTER_TEX5
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftQuarter7", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 121, -1); // DECAL_LEFT_QUARTER_TEX6
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsLeftQuarter8", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 122, -1); // DECAL_LEFT_QUARTER_TEX7
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightQuarter1", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 123, -1); // DECAL_RIGHT_QUARTER_TEX0
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightQuarter2", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 124, -1); // DECAL_RIGHT_QUARTER_TEX1
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightQuarter3", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 125, -1); // DECAL_RIGHT_QUARTER_TEX2
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightQuarter4", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 126, -1); // DECAL_RIGHT_QUARTER_TEX3
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightQuarter5", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 127, -1); // DECAL_RIGHT_QUARTER_TEX4
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightQuarter6", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 128, -1); // DECAL_RIGHT_QUARTER_TEX5
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightQuarter7", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 129, -1); // DECAL_RIGHT_QUARTER_TEX6
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "DecalsRightQuarter8", 0) != 0) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 130, -1); // DECAL_RIGHT_QUARTER_TEX7
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Driver", 0) != 0) RideInfo_SetRandomPart(RideInfo, 43, -1); // DRIVER
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "LicensePlate", 0) != 0) RideInfo_SetRandomPart(RideInfo, 69, -1); // LICENSE_PLATE
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Tires", 0) != 0) RideInfo_SetRandomPart(RideInfo, 64, -1); // HEADLIGHT
		if (GetCarIntOption(CarINI, GeneralINI, "RandomParts", "Neon", 0) != 0) RideInfo_SetRandomPart(RideInfo, 65, -1); // BRAKELIGHT

		return;
	}

	// Or, check the customization level for vanilla randomization
	int ForceCustomizationLevel = GetCarIntOption(CarINI, GeneralINI, "RandomParts", "ForceCustomizationLevel", -2);

	// -2 = Random customization level
	// -1 = Nothing
	// 0 = Body, Spoiler, Rims and Paint (Carbon)
	// 1 = Paint and Vinyls
	// 2 = (Level 1) + Body, Spoiler, Rims, Window Tint, Roof Scoops, Hood
	// 3 = (Level 2) + Unlimiter stuff
	// 4 = (Level 3) + Decals
	if (ForceCustomizationLevel == -2) CustomizationLevel = bRandom(5);
	else CustomizationLevel = ForceCustomizationLevel;

	bool NeedsStockBodyParts = ForceStockPartsOnAddOnOpponents && RideInfo[0] >= 84; // Keep BODY, SPOILER, HOOD and ROOF stock

	switch (CustomizationLevel)
	{
	case 4:
		// Decals
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 83, -1); // DECAL_FRONT_WINDOW_TEX0
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 84, -1); // DECAL_FRONT_WINDOW_TEX1
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 85, -1); // DECAL_FRONT_WINDOW_TEX2
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 86, -1); // DECAL_FRONT_WINDOW_TEX3
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 87, -1); // DECAL_FRONT_WINDOW_TEX4
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 88, -1); // DECAL_FRONT_WINDOW_TEX5
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 89, -1); // DECAL_FRONT_WINDOW_TEX6
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 90, -1); // DECAL_FRONT_WINDOW_TEX7
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 91, -1); // DECAL_REAR_WINDOW_TEX0
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 92, -1); // DECAL_REAR_WINDOW_TEX1
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 93, -1); // DECAL_REAR_WINDOW_TEX2
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 94, -1); // DECAL_REAR_WINDOW_TEX3
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 95, -1); // DECAL_REAR_WINDOW_TEX4
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 96, -1); // DECAL_REAR_WINDOW_TEX5
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 97, -1); // DECAL_REAR_WINDOW_TEX6
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 98, -1); // DECAL_REAR_WINDOW_TEX7
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 99, -1); // DECAL_LEFT_DOOR_TEX0
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 100, -1); // DECAL_LEFT_DOOR_TEX1
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 101, -1); // DECAL_LEFT_DOOR_TEX2
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 102, -1); // DECAL_LEFT_DOOR_TEX3
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 103, -1); // DECAL_LEFT_DOOR_TEX4
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 104, -1); // DECAL_LEFT_DOOR_TEX5
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 105, -1); // DECAL_LEFT_DOOR_TEX6
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 106, -1); // DECAL_LEFT_DOOR_TEX7
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 107, -1); // DECAL_RIGHT_DOOR_TEX0
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 108, -1); // DECAL_RIGHT_DOOR_TEX1
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 109, -1); // DECAL_RIGHT_DOOR_TEX2
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 110, -1); // DECAL_RIGHT_DOOR_TEX3
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 111, -1); // DECAL_RIGHT_DOOR_TEX4
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 112, -1); // DECAL_RIGHT_DOOR_TEX5
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 113, -1); // DECAL_RIGHT_DOOR_TEX6
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 114, -1); // DECAL_RIGHT_DOOR_TEX7
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 115, -1); // DECAL_LEFT_QUARTER_TEX0
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 116, -1); // DECAL_LEFT_QUARTER_TEX1
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 117, -1); // DECAL_LEFT_QUARTER_TEX2
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 118, -1); // DECAL_LEFT_QUARTER_TEX3
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 119, -1); // DECAL_LEFT_QUARTER_TEX4
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 120, -1); // DECAL_LEFT_QUARTER_TEX5
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 121, -1); // DECAL_LEFT_QUARTER_TEX6
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 122, -1); // DECAL_LEFT_QUARTER_TEX7
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 123, -1); // DECAL_RIGHT_QUARTER_TEX0
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 124, -1); // DECAL_RIGHT_QUARTER_TEX1
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 125, -1); // DECAL_RIGHT_QUARTER_TEX2
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 126, -1); // DECAL_RIGHT_QUARTER_TEX3
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 127, -1); // DECAL_RIGHT_QUARTER_TEX4
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 128, -1); // DECAL_RIGHT_QUARTER_TEX5
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 129, -1); // DECAL_RIGHT_QUARTER_TEX6
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, 130, -1); // DECAL_RIGHT_QUARTER_TEX7

	case 3:
		// Unlimiter parts
		if (GetCarIntOption(CarINI, GeneralINI, "Parts", "RoofScoops", 1) != 0) RideInfo_SetRandomPart(RideInfo, 62, -1); // ROOF
		if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Interior", 0) != 0) RideInfo_SetRandomPart(RideInfo, 28, -1); // INTERIOR
		if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Roof", 0) != 0) RideInfo_SetRandomPart(RideInfo, 0, -1); // BASE
		if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Brakes", 0) != 0) RideInfo_SetRandomPart(RideInfo, 24, -1); // FRONT_BRAKE
		if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Headlights", 0) != 0) RideInfo_SetRandomPart(RideInfo, 31, -1); // LEFT_HEADLIGHT
		if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Taillights", 0) != 0) RideInfo_SetRandomPart(RideInfo, 29, -1); // LEFT_BRAKELIGHT
		if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Mirrors", 0) != 0) RideInfo_SetRandomPart(RideInfo, 33, -1); // LEFT_SIDE_MIRROR

		for (int i = 1; i <= NumAttachments; i++)
		{
			RideInfo_SetRandomPart(RideInfo, 51 + i, -1); // ATTACHMENT0-9
		}

		if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Driver", 0) != 0) RideInfo_SetRandomPart(RideInfo, 43, -1); // DRIVER
		if (GetCarIntOption(CarINI, GeneralINI, "Visual", "LicensePlate", 0) != 0) RideInfo_SetRandomPart(RideInfo, 69, -1); // LICENSE_PLATE
		if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Tires", 0) != 0) RideInfo_SetRandomPart(RideInfo, 64, -1); // HEADLIGHT (Tires)
		if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Neon", 0) != 0) RideInfo_SetRandomPart(RideInfo, 65, -1); // BRAKELIGHT (Neon)
		
	case 2:
		// Body parts
		if (!NeedsStockBodyParts)
		{
			RideInfo_SetRandomPart(RideInfo, 23, -1); // BODY
			RideInfo_SetRandomPart(RideInfo, 44, -1); // SPOILER
			RideInfo_SetRandomPart(RideInfo, 62, -1); // ROOF
			RideInfo_SetRandomPart(RideInfo, 63, -1); // HOOD
		}
		RideInfo_SetRandomPart(RideInfo, 66, -1); // FRONT_WHEEL
		if (RearRimsHeadsOrTails) RideInfo_SetRandomPart(RideInfo, 67, -1); // REAR_WHEEL
		else RideInfo_SetPart(RideInfo, EDX_Unused, 67, (DWORD)RideInfo_GetPart(RideInfo, 66), 1);

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
		if (!NeedsStockBodyParts)
		{
			RideInfo_SetRandomPart(RideInfo, 23, -1); // BODY
			RideInfo_SetRandomPart(RideInfo, 44, -1); // SPOILER
		}
		RideInfo_SetRandomPart(RideInfo, 76, -1); // BASE_PAINT
		RideInfo_SetRandomPart(RideInfo, 66, -1); // FRONT_WHEEL
		if (RearRimsHeadsOrTails) RideInfo_SetRandomPart(RideInfo, 67, -1); // REAR_WHEEL
		else RideInfo_SetPart(RideInfo, EDX_Unused, 67, (DWORD)RideInfo_GetPart(RideInfo, 66), 1);
		RideInfo_SetRandomPart(RideInfo, 78, -1); // PAINT_RIM
		break;
	case -1:
		// Nothing. Bone stock.
		break;
	}

}