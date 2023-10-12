#include "stdio.h"
#include "InGameFunctions.h"

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
	case CAR_SLOT_ID::BASE: // BASE
		if (!CarPart)
		{
			InvalidBasePart:
			RideInfo[18 + CAR_SLOT_ID::FRONT_LEFT_WINDOW] = 0;
			RideInfo[18 + CAR_SLOT_ID::FRONT_RIGHT_WINDOW] = 0;
			RideInfo[18 + CAR_SLOT_ID::FRONT_WINDOW] = 0;
			RideInfo[18 + CAR_SLOT_ID::REAR_LEFT_WINDOW] = 0;
			RideInfo[18 + CAR_SLOT_ID::REAR_RIGHT_WINDOW] = 0;
			RideInfo[18 + CAR_SLOT_ID::REAR_WINDOW] = 0;
			RideInfo[18 + CAR_SLOT_ID::DECAL_FRONT_WINDOW_WIDE_MEDIUM] = 0;
			RideInfo[18 + CAR_SLOT_ID::DECAL_REAR_WINDOW_WIDE_MEDIUM] = 0;

			goto SetSinglePart;
		}
		
		// Apply glass and decal parts according to the base style
		sprintf(KitName, "%s_", GetCarTypeName(RideInfo[0]));
		KitNameHash = bStringHash(KitName);
		PartHash = bStringHash2((char*)"BASE", KitNameHash);

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
				PartHash = bStringHash2((char*)"BASE", KitNameHash);
				if (*(unsigned int*)CarPart == PartHash)
				{
					break;
				}
				if (i == 99) goto InvalidBasePart;
			}
		}
		
		RideInfo[18 + CAR_SLOT_ID::FRONT_LEFT_WINDOW] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::FRONT_LEFT_WINDOW, bStringHash2((char*)"FRONT_LEFT_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + CAR_SLOT_ID::FRONT_RIGHT_WINDOW] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::FRONT_RIGHT_WINDOW, bStringHash2((char*)"FRONT_RIGHT_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + CAR_SLOT_ID::FRONT_WINDOW] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::FRONT_WINDOW, bStringHash2((char*)"FRONT_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + CAR_SLOT_ID::REAR_LEFT_WINDOW] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::REAR_LEFT_WINDOW, bStringHash2((char*)"REAR_LEFT_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + CAR_SLOT_ID::REAR_RIGHT_WINDOW] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::REAR_RIGHT_WINDOW, bStringHash2((char*)"REAR_RIGHT_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + CAR_SLOT_ID::REAR_WINDOW] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::REAR_WINDOW, bStringHash2((char*)"REAR_WINDOW", KitNameHash), 0, -1);
		RideInfo[18 + CAR_SLOT_ID::DECAL_FRONT_WINDOW_WIDE_MEDIUM] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DECAL_FRONT_WINDOW_WIDE_MEDIUM, bStringHash2((char*)"DECAL_FRONT_WINDOW_WIDE_MEDIUM", KitNameHash), 0, -1);
		RideInfo[18 + CAR_SLOT_ID::DECAL_REAR_WINDOW_WIDE_MEDIUM] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DECAL_REAR_WINDOW_WIDE_MEDIUM, bStringHash2((char*)"DECAL_REAR_WINDOW_WIDE_MEDIUM", KitNameHash), 0, -1);

		goto SetSinglePart;

	case CAR_SLOT_ID::BODY: // BODY
		if (!CarPart)
		{
			RideInfo[18 + CAR_SLOT_ID::DAMAGE0_FRONT] = 0; // DAMAGE0_FRONT
			RideInfo[18 + CAR_SLOT_ID::DAMAGE0_FRONTLEFT] = 0; // DAMAGE0_FRONTLEFT
			RideInfo[18 + CAR_SLOT_ID::DAMAGE0_FRONTRIGHT] = 0; // DAMAGE0_FRONTRIGHT
			RideInfo[18 + CAR_SLOT_ID::DAMAGE0_REAR] = 0; // DAMAGE0_REAR
			RideInfo[18 + CAR_SLOT_ID::DAMAGE0_REARLEFT] = 0; // DAMAGE0_REARLEFT
			RideInfo[18 + CAR_SLOT_ID::DAMAGE0_REARRIGHT] = 0; // DAMAGE0_REARRIGHT
			RideInfo[18 + CAR_SLOT_ID::DECAL_LEFT_DOOR_RECT_MEDIUM] = 0; // DECAL_LEFT_DOOR_RECT_MEDIUM
			RideInfo[18 + CAR_SLOT_ID::DECAL_RIGHT_DOOR_RECT_MEDIUM] = 0; // DECAL_RIGHT_DOOR_RECT_MEDIUM
			RideInfo[18 + CAR_SLOT_ID::DECAL_LEFT_QUARTER_RECT_MEDIUM] = 0; // DECAL_LEFT_QUARTER_RECT_MEDIUM
			RideInfo[18 + CAR_SLOT_ID::DECAL_RIGHT_QUARTER_RECT_MEDIUM] = 0; // DECAL_RIGHT_QUARTER_RECT_MEDIUM

			goto SetSinglePart;
		}
		KitNumber = CarPart_GetAppliedAttributeIParam((void*)CarPart, bStringHash((char*)"KITNUMBER"), 0);
		
		// Apply damage and decal parts according to the kit number
		sprintf(KitName, "%s_KIT%02d_", GetCarTypeName(RideInfo[0]), KitNumber);
		KitNameHash = bStringHash(KitName);
		RideInfo[18 + CAR_SLOT_ID::DAMAGE0_FRONT] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DAMAGE0_FRONT, bStringHash2((char*)"DAMAGE0_FRONT", KitNameHash), 0, -1); // DAMAGE0_FRONT
		RideInfo[18 + CAR_SLOT_ID::DAMAGE0_FRONTLEFT] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DAMAGE0_FRONTLEFT, bStringHash2((char*)"DAMAGE0_FRONTLEFT", KitNameHash), 0, -1); // DAMAGE0_FRONTLEFT
		RideInfo[18 + CAR_SLOT_ID::DAMAGE0_FRONTRIGHT] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DAMAGE0_FRONTRIGHT, bStringHash2((char*)"DAMAGE0_FRONTRIGHT", KitNameHash), 0, -1); // DAMAGE0_FRONTRIGHT
		RideInfo[18 + CAR_SLOT_ID::DAMAGE0_REAR] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DAMAGE0_REAR, bStringHash2((char*)"DAMAGE0_REAR", KitNameHash), 0, -1); // DAMAGE0_REAR
		RideInfo[18 + CAR_SLOT_ID::DAMAGE0_REARLEFT] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DAMAGE0_REARLEFT, bStringHash2((char*)"DAMAGE0_REARLEFT", KitNameHash), 0, -1); // DAMAGE0_REARLEFT
		RideInfo[18 + CAR_SLOT_ID::DAMAGE0_REARRIGHT] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DAMAGE0_REARRIGHT, bStringHash2((char*)"DAMAGE0_REARRIGHT", KitNameHash), 0, -1); // DAMAGE0_REARRIGHT
		RideInfo[18 + CAR_SLOT_ID::DECAL_LEFT_DOOR_RECT_MEDIUM] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DECAL_LEFT_DOOR_RECT_MEDIUM, bStringHash2((char*)"DECAL_LEFT_DOOR_RECT_MEDIUM", KitNameHash), 0, -1); // DECAL_LEFT_DOOR_RECT_MEDIUM
		RideInfo[18 + CAR_SLOT_ID::DECAL_RIGHT_DOOR_RECT_MEDIUM] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DECAL_RIGHT_DOOR_RECT_MEDIUM, bStringHash2((char*)"DECAL_RIGHT_DOOR_RECT_MEDIUM", KitNameHash), 0, -1); // DECAL_RIGHT_DOOR_RECT_MEDIUM
		RideInfo[18 + CAR_SLOT_ID::DECAL_LEFT_QUARTER_RECT_MEDIUM] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DECAL_LEFT_QUARTER_RECT_MEDIUM, bStringHash2((char*)"DECAL_LEFT_QUARTER_RECT_MEDIUM", KitNameHash), 0, -1); // DECAL_LEFT_QUARTER_RECT_MEDIUM
		RideInfo[18 + CAR_SLOT_ID::DECAL_RIGHT_QUARTER_RECT_MEDIUM] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::DECAL_RIGHT_QUARTER_RECT_MEDIUM, bStringHash2((char*)"DECAL_RIGHT_QUARTER_RECT_MEDIUM", KitNameHash), 0, -1); // DECAL_RIGHT_QUARTER_RECT_MEDIUM
		
		goto SetSinglePart;

	case CAR_SLOT_ID::FRONT_BRAKE: // FRONT_BRAKE
		if (!CarPart)
		{
		InvalidBrakePart:
			RideInfo[18 + CAR_SLOT_ID::REAR_BRAKE] = 0; // REAR_BRAKE

			goto SetSinglePart;
		}

		// Apply rear brake according to the front brake style
		sprintf(KitName, "%s_", GetCarTypeName(RideInfo[0]));
		KitNameHash = bStringHash(KitName);
		PartHash = bStringHash2((char*)"FRONT_BRAKE", KitNameHash);

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
				PartHash = bStringHash2((char*)"FRONT_BRAKE", KitNameHash);
				if (*(unsigned int*)CarPart == PartHash)
				{
					break;
				}
				if (i == 99) goto GlobalBrakePart;
			}
		}

		RideInfo[18 + CAR_SLOT_ID::REAR_BRAKE] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::REAR_BRAKE, bStringHash2((char*)"REAR_BRAKE", KitNameHash), 0, -1);
		goto SetSinglePart;

		// Global (BRAKES)
	GlobalBrakePart:
		PartHash = bStringHash((char*)"BRAKE_KIT00");
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

		RideInfo[18 + CAR_SLOT_ID::REAR_BRAKE] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::FRONT_BRAKE, PartHash, 0, -1);
		goto SetSinglePart;

	case CAR_SLOT_ID::LEFT_BRAKELIGHT: // LEFT_BRAKELIGHT
		if (!CarPart)
		{
		InvalidBrakelightPart:
			RideInfo[18 + CAR_SLOT_ID::LEFT_BRAKELIGHT_GLASS] = 0; // LEFT_BRAKELIGHT_GLASS
			RideInfo[18 + CAR_SLOT_ID::RIGHT_BRAKELIGHT] = 0; // RIGHT_BRAKELIGHT
			RideInfo[18 + CAR_SLOT_ID::RIGHT_BRAKELIGHT_GLASS] = 0; // RIGHT_BRAKELIGHT_GLASS

			goto SetSinglePart;
		}

		// Apply glass and decal parts according to the base style
		sprintf(KitName, "%s_", GetCarTypeName(RideInfo[0]));
		KitNameHash = bStringHash(KitName);
		PartHash = bStringHash2((char*)"LEFT_BRAKELIGHT", KitNameHash);

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
				PartHash = bStringHash2((char*)"LEFT_BRAKELIGHT", KitNameHash);
				if (*(unsigned int*)CarPart == PartHash)
				{
					break;
				}
				if (i == 99) goto InvalidBrakelightPart;
			}
		}

		RideInfo[18 + CAR_SLOT_ID::LEFT_BRAKELIGHT_GLASS] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::LEFT_BRAKELIGHT_GLASS, bStringHash2((char*)"LEFT_BRAKELIGHT_GLASS", KitNameHash), 0, -1);
		RideInfo[18 + CAR_SLOT_ID::RIGHT_BRAKELIGHT] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::RIGHT_BRAKELIGHT, bStringHash2((char*)"RIGHT_BRAKELIGHT", KitNameHash), 0, -1);
		RideInfo[18 + CAR_SLOT_ID::RIGHT_BRAKELIGHT_GLASS] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::RIGHT_BRAKELIGHT_GLASS, bStringHash2((char*)"RIGHT_BRAKELIGHT_GLASS", KitNameHash), 0, -1);

		goto SetSinglePart;

	case CAR_SLOT_ID::LEFT_HEADLIGHT: // LEFT_HEADLIGHT
		if (!CarPart)
		{
		InvalidHeadlightPart:
			RideInfo[18 + CAR_SLOT_ID::LEFT_HEADLIGHT_GLASS] = 0; // LEFT_HEADLIGHT_GLASS
			RideInfo[18 + CAR_SLOT_ID::RIGHT_HEADLIGHT] = 0; // RIGHT_HEADLIGHT
			RideInfo[18 + CAR_SLOT_ID::RIGHT_HEADLIGHT_GLASS] = 0; // RIGHT_HEADLIGHT_GLASS

			goto SetSinglePart;
		}

		// Apply glass and decal parts according to the base style
		sprintf(KitName, "%s_", GetCarTypeName(RideInfo[0]));
		KitNameHash = bStringHash(KitName);
		PartHash = bStringHash2((char*)"LEFT_HEADLIGHT", KitNameHash);

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
				PartHash = bStringHash2((char*)"LEFT_HEADLIGHT", KitNameHash);
				if (*(unsigned int*)CarPart == PartHash)
				{
					break;
				}
				if (i == 99) goto InvalidHeadlightPart;
			}
		}

		RideInfo[18 + CAR_SLOT_ID::LEFT_HEADLIGHT_GLASS] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::LEFT_HEADLIGHT_GLASS, bStringHash2((char*)"LEFT_HEADLIGHT_GLASS", KitNameHash), 0, -1);
		RideInfo[18 + CAR_SLOT_ID::RIGHT_HEADLIGHT] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::RIGHT_HEADLIGHT, bStringHash2((char*)"RIGHT_HEADLIGHT", KitNameHash), 0, -1);
		RideInfo[18 + CAR_SLOT_ID::RIGHT_HEADLIGHT_GLASS] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::RIGHT_HEADLIGHT_GLASS, bStringHash2((char*)"RIGHT_HEADLIGHT_GLASS", KitNameHash), 0, -1);
		
		goto SetSinglePart;

	case CAR_SLOT_ID::LEFT_SIDE_MIRROR: // LEFT_SIDE_MIRROR
		if (!CarPart)
		{
		InvalidMirrorPart:
			RideInfo[18 + CAR_SLOT_ID::RIGHT_SIDE_MIRROR] = 0; // RIGHT_SIDE_MIRROR

			goto SetSinglePart;
		}

		// Apply glass and decal parts according to the base style
		sprintf(KitName, "%s_", GetCarTypeName(RideInfo[0]));
		KitNameHash = bStringHash(KitName);
		PartHash = bStringHash2((char*)"LEFT_SIDE_MIRROR", KitNameHash);

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
				PartHash = bStringHash2((char*)"LEFT_SIDE_MIRROR", KitNameHash);
				if (*(unsigned int*)CarPart == PartHash)
				{
					break;
				}
				if (i == 99) goto InvalidMirrorPart;
			}
		}

		RideInfo[18 + CAR_SLOT_ID::RIGHT_SIDE_MIRROR] = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::RIGHT_SIDE_MIRROR, bStringHash2((char*)"RIGHT_SIDE_MIRROR", KitNameHash), 0, -1);

		goto SetSinglePart;

	case CAR_SLOT_ID::REAR_WHEEL: // REAR_WHEEL
		if (!CarPart)
		{
			RideInfo[18 + CAR_SLOT_ID::REAR_WHEEL] = 0; // REAR_WHEEL

			goto SetSinglePart;
		}

		// Apply rear wheel according to the front wheel style
		PartHash = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CAR_SLOT_ID::REAR_WHEEL, bStringHash2((char*)"_REAR", *(unsigned int*)CarPart), 0, -1); // If it has rear wheel
		if (PartHash) CarPart = PartHash;

		goto SetSinglePart;

		// BODY
	case CAR_SLOT_ID::DAMAGE0_FRONT:
	case CAR_SLOT_ID::DAMAGE0_FRONTLEFT:
	case CAR_SLOT_ID::DAMAGE0_FRONTRIGHT:
	case CAR_SLOT_ID::DAMAGE0_REAR:
	case CAR_SLOT_ID::DAMAGE0_REARLEFT:
	case CAR_SLOT_ID::DAMAGE0_REARRIGHT:
	case CAR_SLOT_ID::DECAL_LEFT_DOOR_RECT_MEDIUM:
	case CAR_SLOT_ID::DECAL_RIGHT_DOOR_RECT_MEDIUM:
	case CAR_SLOT_ID::DECAL_LEFT_QUARTER_RECT_MEDIUM:
	case CAR_SLOT_ID::DECAL_RIGHT_QUARTER_RECT_MEDIUM:
		// BASE
	case CAR_SLOT_ID::FRONT_LEFT_WINDOW:
	case CAR_SLOT_ID::FRONT_RIGHT_WINDOW:
	case CAR_SLOT_ID::FRONT_WINDOW:
	case CAR_SLOT_ID::REAR_LEFT_WINDOW:
	case CAR_SLOT_ID::REAR_RIGHT_WINDOW:
	case CAR_SLOT_ID::REAR_WINDOW:
	case CAR_SLOT_ID::DECAL_FRONT_WINDOW_WIDE_MEDIUM:
	case CAR_SLOT_ID::DECAL_REAR_WINDOW_WIDE_MEDIUM:
		// LEFT_HEADLIGHT
	case CAR_SLOT_ID::LEFT_HEADLIGHT_GLASS:
	case CAR_SLOT_ID::RIGHT_HEADLIGHT:
	case CAR_SLOT_ID::RIGHT_HEADLIGHT_GLASS:
		// LEFT_BRAKELIGHT
	case CAR_SLOT_ID::LEFT_BRAKELIGHT_GLASS:
	case CAR_SLOT_ID::RIGHT_BRAKELIGHT:
	case CAR_SLOT_ID::RIGHT_BRAKELIGHT_GLASS:
		// LEFT_SIDE_MIRROR
	case CAR_SLOT_ID::RIGHT_SIDE_MIRROR:
		// FRONT_BRAKE
	case CAR_SLOT_ID::REAR_BRAKE:
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
			if (BrandNameHash == bStringHash((char*)"NUMBER_LEFT")) IsNumberLeft = true;
			if (BrandNameHash == bStringHash((char*)"NUMBER_RIGHT")) IsNumberRight = true;

			if (!IsNumberLeft && !IsNumberRight) return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, (DWORD)NewPart, 1);
		}
	}

	return 0;
}

unsigned int __fastcall RideInfo_SetRandomNumber(DWORD* RideInfo, void* EDX_Unused, int CarSlotID, int UpgradeLevel)
{
	char bufL[32];
	char bufR[32];
	int RndNum;
	DWORD NewPart;
	DWORD* LeftNumberPart;

	switch (CarSlotID)
	{
		case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX6:
			RndNum = bRandom(10);
			sprintf(bufL, "NUMBER_LEFT_%d", RndNum);
			NewPart = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CarSlotID, bStringHash(bufL), 0, -1);
			if (NewPart) return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, NewPart, 1);
			return 0;
			break;

		case CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX7:
			LeftNumberPart = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX6);
			if (LeftNumberPart)
			{
				RndNum = bRandom(10);
				sprintf(bufR, "NUMBER_RIGHT_%d", RndNum);
				NewPart = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, RideInfo[0], CarSlotID, bStringHash(bufR), 0, -1);
				if (NewPart) return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, NewPart, 1);
				else RideInfo_SetPart(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX6, 0, 1);
			}
			else
			{
				RideInfo_SetPart(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX6, 0, 1);
			}
			return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, 0, 1);
			break;

		case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX6:
			return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, (DWORD)RideInfo_GetPart(RideInfo, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX6), 1);
			break;

		case CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX7:
			return RideInfo_SetPart(RideInfo, EDX_Unused, CarSlotID, (DWORD)RideInfo_GetPart(RideInfo, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX7), 1);
			break;
	}
	return 0;
}

DWORD __fastcall RideInfo_GetStockPartNameHash(DWORD* RideInfo, void* EDX_Unused, int CarSlotID)
{
	return CarConfigs[RideInfo[0]].StockParts.CustomStockParts 
		? CarConfigs[RideInfo[0]].StockParts.Parts[CarSlotID] 
		: -1;
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

	DefaultVinylColors[0] = bStringHash((char*)"VINYL_L1_COLOR01"); // 255, 255, 255, 100
	DefaultVinylColors[1] = bStringHash((char*)"VINYL_L1_COLOR03"); // 255, 251, 224, 100
	DefaultVinylColors[2] = bStringHash((char*)"VINYL_L1_COLOR61"); // VINYL_L2_COLOR11 (129, 130, 120, 100) Doesn't exist in vanilla game
	DefaultVinylColors[3] = bStringHash((char*)"VINYL_L1_COLOR01"); // 255, 255, 255, 100

	for (int CarSlotID = 0; CarSlotID < NumCarSlots; ++CarSlotID)
	{
		// (Type != COPHELI || != ATTACHMENT6) && (!VINYL_LAYER0) && (< VINYL_LAYER0 || > DECAL_RIGHT_QUARTER_TEX7)
		if ((CarType != 4 || CarSlotID != CAR_SLOT_ID::ATTACHMENT6) && (CarSlotID != CAR_SLOT_ID::VINYL_LAYER0) && (CarSlotID < CAR_SLOT_ID::VINYL_LAYER0 || CarSlotID > CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX7))
		{
			switch (CarSlotID)
			{
			case CAR_SLOT_ID::BASE_PAINT:
				PartNameHash = *(DWORD*)(208 * CarType + *(DWORD*)CarTypeInfoArray + 204);
				TheCarPart = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, CarType, CarSlotID, PartNameHash, 0, -1);
				if (TheCarPart) RideInfo_SetPart(TheRideInfo, EDX_Unused, CarSlotID, TheCarPart, 1);
				else // If the paint is invalid
				{
					PartNameHash = bStringHash((char*)"GLOSS_L1_COLOR01");
					TheCarPart = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, CarType, CarSlotID, PartNameHash, 0, -1);
					if (TheCarPart) RideInfo_SetPart(TheRideInfo, EDX_Unused, CarSlotID, TheCarPart, 1);
				}
				break;

			case CAR_SLOT_ID::ROOF:
				PartNameHash = bStringHash((char*)"ROOF_STYLE00");
				goto ApplyPart;
				break;
				/*
			case 64: // HEADLIGHT (Tires)
				PartNameHash = bStringHash("TIRE_STYLE01");
				goto ApplyPart;
				break;*/

			case CAR_SLOT_ID::BRAKELIGHT: //Neon
				PartNameHash = bStringHash((char*)"NEON_NONE");
				goto ApplyPart;
				break;

			case CAR_SLOT_ID::HUD_BACKING_COLOUR:
			case CAR_SLOT_ID::HUD_NEEDLE_COLOUR:
				PartNameHash = bStringHash((char*)"ORANGE");
					goto ApplyPart;
					break;

			case CAR_SLOT_ID::HUD_CHARACTER_COLOUR:
				PartNameHash = bStringHash((char*)"WHITE");

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

		// Check if ini has a custom stock part
		PartNameHash = RideInfo_GetStockPartNameHash(TheRideInfo, EDX_Unused, CarSlotID);
		if (PartNameHash != -1) // apply the part
		{
			TheCarPart = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, CarType, CarSlotID, PartNameHash, 0, -1);
			if (TheCarPart) RideInfo_SetPart(TheRideInfo, EDX_Unused, CarSlotID, TheCarPart, 1);
			else RideInfo_SetUpgradePart(TheRideInfo, CarSlotID, 0);
		}
	}

	VinylColorSlotID = CAR_SLOT_ID::VINYL_COLOUR0_0;
	VinylColorRef = DefaultVinylColors;
	NumVinylLayers = 4;
	do
	{
		PartNameHash = RideInfo_GetStockPartNameHash(TheRideInfo, EDX_Unused, VinylColorSlotID);
		if (PartNameHash == -1)
		{
			TheCarPart = CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, CarType, VinylColorSlotID, *VinylColorRef, 0, -1);
			RideInfo_SetPart(TheRideInfo, EDX_Unused, VinylColorSlotID, TheCarPart, 1);
		}
		++VinylColorRef;
		++VinylColorSlotID;
		--NumVinylLayers;
	} while (NumVinylLayers);
}

void __fastcall RideInfo_SetRandomParts(DWORD* RideInfo, void* EDX_Unused)
{
	int CustomizationLevel, RearRimsHeadsOrTails, NumbersHeadsOrTails;
	int CarTypeID = RideInfo[0];

	// Set all parts as stock first
	RideInfo_SetStockParts(RideInfo, EDX_Unused);

	// If HPC is present, only randomize the car paint
	if (HPCCompatibility)
	{
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::BASE_PAINT, -1); // BASE_PAINT
		return;
	}

	// Flip coins
	RearRimsHeadsOrTails = bRandom(2);
	NumbersHeadsOrTails = bRandom(2);

	// Get num attachments
	int NumAttachments = CarConfigs[CarTypeID].Parts.Attachments;

	int CustomRandomParts = CarConfigs[CarTypeID].RandomParts.CustomRandomParts;
	if (CustomRandomParts)
	{
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::BODY]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::BODY, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::SPOILER]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::SPOILER, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::FRONT_WHEEL])
		{
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::FRONT_WHEEL, -1);
			if (RearRimsHeadsOrTails) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::REAR_WHEEL, -1);
			else RideInfo_SetPart(RideInfo, EDX_Unused, CAR_SLOT_ID::REAR_WHEEL, (DWORD)RideInfo_GetPart(RideInfo, CAR_SLOT_ID::FRONT_WHEEL), 1);
		}
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::HOOD]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::HOOD, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::ROOF]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ROOF, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::INTERIOR]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::INTERIOR, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::BASE]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::BASE, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::FRONT_BRAKE]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::FRONT_BRAKE, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::LEFT_HEADLIGHT]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::LEFT_HEADLIGHT, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::LEFT_BRAKELIGHT]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::LEFT_BRAKELIGHT, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::LEFT_SIDE_MIRROR]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::LEFT_SIDE_MIRROR, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::ATTACHMENT0]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ATTACHMENT0, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::ATTACHMENT1]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ATTACHMENT1, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::ATTACHMENT2]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ATTACHMENT2, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::ATTACHMENT3]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ATTACHMENT3, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::ATTACHMENT4]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ATTACHMENT4, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::ATTACHMENT5]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ATTACHMENT5, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::ATTACHMENT6]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ATTACHMENT6, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::ATTACHMENT7]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ATTACHMENT7, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::ATTACHMENT8]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ATTACHMENT8, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::ATTACHMENT9]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ATTACHMENT9, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::BASE_PAINT]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::BASE_PAINT, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::VINYL_LAYER0])
		{
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::VINYL_LAYER0, -1);
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::VINYL_COLOUR0_0, -1);
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::VINYL_COLOUR0_1, -1);
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::VINYL_COLOUR0_2, -1);
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::VINYL_COLOUR0_3, -1);
		}
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::PAINT_RIM]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::PAINT_RIM, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::WINDOW_TINT]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::WINDOW_TINT, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX0]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX0, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX1]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX1, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX2]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX2, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX3]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX3, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX4]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX4, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX5]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX5, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX6]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX6, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX7]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX7, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX0]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX0, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX1]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX1, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX2]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX2, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX3]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX3, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX4]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX4, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX5]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX5, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX6]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX6, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX7]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX7, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX0]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX0, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX1]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX1, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX2]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX2, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX3]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX3, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX4]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX4, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX5]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX5, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX6] && NumbersHeadsOrTails) RideInfo_SetRandomNumber(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX6, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX7] && NumbersHeadsOrTails) RideInfo_SetRandomNumber(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX7, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX0]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX0, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX1]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX1, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX2]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX2, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX3]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX3, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX4]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX4, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX5]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX5, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX6] && NumbersHeadsOrTails) RideInfo_SetRandomNumber(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX6, -1);  
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX7] && NumbersHeadsOrTails) RideInfo_SetRandomNumber(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX7, -1);  
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX0]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX0, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX1]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX1, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX2]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX2, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX3]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX3, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX4]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX4, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX5]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX5, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX6]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX6, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX7]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX7, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX0]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX0, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX1]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX1, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX2]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX2, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX3]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX3, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX4]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX4, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX5]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX5, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX6]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX6, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX7]) RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX7, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::CUSTOM_HUD]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::CUSTOM_HUD, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::HUD_BACKING_COLOUR]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::HUD_BACKING_COLOUR, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::HUD_NEEDLE_COLOUR]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::HUD_NEEDLE_COLOUR, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::HUD_CHARACTER_COLOUR]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::HUD_CHARACTER_COLOUR, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::DRIVER]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::DRIVER, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::LICENSE_PLATE]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::LICENSE_PLATE, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::HEADLIGHT]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::HEADLIGHT, -1);
		if (CarConfigs[CarTypeID].RandomParts.Parts[CAR_SLOT_ID::BRAKELIGHT]) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::BRAKELIGHT, -1);

		return;
	}

	// Or, check the customization level for vanilla randomization
	int ForceCustomizationLevel = CarConfigs[CarTypeID].RandomParts.ForceCustomizationLevel;

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
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX0, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX1, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX2, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX3, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX4, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX5, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX6, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX7, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX0, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX1, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX2, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX3, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX4, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX5, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX6, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX7, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX0, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX1, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX2, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX3, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX4, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX5, -1);
		if (NumbersHeadsOrTails) RideInfo_SetRandomNumber(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX6, -1);
		if (NumbersHeadsOrTails) RideInfo_SetRandomNumber(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX7, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX0, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX1, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX2, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX3, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX4, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX5, -1);
		if (NumbersHeadsOrTails) RideInfo_SetRandomNumber(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX6, -1);
		if (NumbersHeadsOrTails) RideInfo_SetRandomNumber(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX7, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX0, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX1, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX2, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX3, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX4, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX5, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX6, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX7, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX0, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX1, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX2, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX3, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX4, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX5, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX6, -1);
		RideInfo_SetRandomDecal(RideInfo, EDX_Unused, CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX7, -1);
		
		// Gauges
		if (CarConfigs[CarTypeID].Visual.CustomGauges)
		{
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::CUSTOM_HUD, -1);
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::HUD_BACKING_COLOUR, -1);
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::HUD_NEEDLE_COLOUR, -1);
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::HUD_CHARACTER_COLOUR, -1);
		}

	case 3:
		// Unlimiter parts
		if (CarConfigs[CarTypeID].Parts.RoofScoops) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ROOF, -1);
		if (CarConfigs[CarTypeID].Parts.Interior) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::INTERIOR, -1);
		if (CarConfigs[CarTypeID].Parts.Roof) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::BASE, -1);
		if (CarConfigs[CarTypeID].Parts.Brakes) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::FRONT_BRAKE, -1);
		if (CarConfigs[CarTypeID].Parts.Headlights) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::LEFT_HEADLIGHT, -1);
		if (CarConfigs[CarTypeID].Parts.Taillights) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::LEFT_BRAKELIGHT, -1);
		if (CarConfigs[CarTypeID].Parts.Mirrors) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::LEFT_SIDE_MIRROR, -1);

		for (int i = 0; i < NumAttachments; i++)
		{
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ATTACHMENT0 + i, -1);
		}

		if (CarConfigs[CarTypeID].Visual.Driver) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::DRIVER, -1);
		if (CarConfigs[CarTypeID].Visual.LicensePlate) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::LICENSE_PLATE, -1);
		if (CarConfigs[CarTypeID].Visual.Tires) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::HEADLIGHT, -1); // Tires
		if (CarConfigs[CarTypeID].Visual.Neon) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::BRAKELIGHT, -1); // Neon
		
	case 2:
		// Body parts
		if (!NeedsStockBodyParts)
		{
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::BODY, -1);
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::SPOILER, -1);
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::ROOF, -1);
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::HOOD, -1);
		}
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::FRONT_WHEEL, -1);
		if (RearRimsHeadsOrTails) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::REAR_WHEEL, -1);
		else RideInfo_SetPart(RideInfo, EDX_Unused, CAR_SLOT_ID::REAR_WHEEL, (DWORD)RideInfo_GetPart(RideInfo, CAR_SLOT_ID::FRONT_WHEEL), 1);

		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::PAINT_RIM, -1);
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::WINDOW_TINT, -1);

	case 1:
		// Paint and vinyls
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::BASE_PAINT, -1);
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::VINYL_LAYER0, -1);
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::VINYL_COLOUR0_0, -1);
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::VINYL_COLOUR0_1, -1);
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::VINYL_COLOUR0_2, -1);
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::VINYL_COLOUR0_3, -1);
		break;
	case 0:
	default:
		// Pretty much Carbon.
		if (!NeedsStockBodyParts)
		{
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::BODY, -1);
			RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::SPOILER, -1);
		}
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::BASE_PAINT, -1);
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::FRONT_WHEEL, -1);
		if (RearRimsHeadsOrTails) RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::REAR_WHEEL, -1);
		else RideInfo_SetPart(RideInfo, EDX_Unused, CAR_SLOT_ID::REAR_WHEEL, (DWORD)RideInfo_GetPart(RideInfo, CAR_SLOT_ID::FRONT_WHEEL), 1);
		RideInfo_SetRandomPart(RideInfo, CAR_SLOT_ID::PAINT_RIM, -1);
		break;
	case -1:
		// Nothing. Bone stock.
		break;
	}

}

void __fastcall RideInfo_SetStockParts_Traffic(DWORD* TheRideInfo, void* EDX_Unused)
{
	RideInfo_SetStockParts_Game(TheRideInfo);

	int CarTypeID = TheRideInfo[0];
	int NumAttemptsPearl = 0;

	if (ShouldRandomizeInTraffic(CarTypeID) && TheRideInfo[194] == 4)
	{
		RideInfo_SetRandomPart(TheRideInfo, CAR_SLOT_ID::BASE_PAINT, -1); // BASE_PAINT

		DWORD* Part = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BASE_PAINT);

		while (CarPart_GetAppliedAttributeUParam(Part, 0xEBB03E66, 0) == 0x03797533) // BRAND_NAME == PEARL
		{
			RideInfo_SetRandomPart(TheRideInfo, CAR_SLOT_ID::BASE_PAINT, -1); // BASE_PAINT
			NumAttemptsPearl++;
			if (NumAttemptsPearl > 10) break;
		}
	}
}

void __fastcall RideInfo_SetCompositeNameHash(DWORD* RideInfo, void* EDX_Unused, int id)
{
	DWORD result; // eax
	char CompNameBuf[64]; // [esp+Ch] [ebp-40h] BYREF

	if (id < 1 || id > CarSkinCount)
	{
		*((BYTE*)RideInfo + 7) = 0;
	}
	else
	{
		*((BYTE*)RideInfo + 7) = 1;
	}
	sprintf(CompNameBuf, "DUMMY_SKIN%d", id);
	RideInfo[15] = IsSkinnable(RideInfo[0]) ? bStringHash(CompNameBuf) : 0;
	sprintf(CompNameBuf, "DUMMY_WHEEL%d", id);
	RideInfo[16] = bStringHash(CompNameBuf);
	sprintf(CompNameBuf, "DUMMY_SPINNER%d", id);
	result = bStringHash(CompNameBuf);
	RideInfo[17] = result;
}