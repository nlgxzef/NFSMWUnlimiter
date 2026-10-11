#pragma once

#include "stdio.h"
#include "InGameFunctions.h"
#include "CarPartDatabase.h"

#include "RideInfo.h"
#include "Physics.h"

struct FECustomizationRecord
{
	__int16 InstalledPartIndices[NumCarSlots];
	struct Physics_Upgrades_Package InstalledPhysics;
	struct Physics_Upgrades_Tunings Tunings[eCustomTuningType::NUM_CUSTOM_TUNINGS];
	enum eCustomTuningType ActiveTuning;
	int Preset;
	unsigned __int8 Handle;

	/*CarPart*/DWORD* GetInstalledPart(int cartype,	int carslotid)
	{
		return CarPartDatabase_GetCarPartByIndex((DWORD*)_CarPartDB, InstalledPartIndices[carslotid]);
	}

	void SetInstalledPart(int carslotid, /*CarPart*/DWORD* part)
	{
		if (part)
		{
			this->InstalledPartIndices[carslotid] = CarPartDatabase_GetPartIndex((DWORD*)_CarPartDB, part);
		}
		else
		{
			this->InstalledPartIndices[carslotid] = -1;
		}
	}

	void WriteRideIntoRecord(/*RideInfo*/DWORD* ride)
	{
		int i; // r31
		/*CarPart*/DWORD* Part; // r3

		for (i = 0; i < CARSLOTID_NUM; ++i)
		{
			Part = RideInfo_GetPart(ride, i);
			SetInstalledPart(i, Part);
		}
	}

	void WriteRecordIntoRide(/*RideInfo*/DWORD* ride)
	{
		int i; // r31
		/*CarPart*/DWORD* InstalledPart; // r3

		for (i = 0; i < CARSLOTID_NUM; ++i)
		{
			InstalledPart = GetInstalledPart(ride[0], i);
			RideInfo_SetPart(ride, 0, i, (DWORD)InstalledPart, 1);
		}
	}
};


void __fastcall FECustomizationRecord_BecomePresitter(WORD* _FECustomizationRecord, void* EDX_Unused, BYTE* PresetCar)
{
	int CarTypeNameHash = bStringHash((char*)PresetCar + 8);
	DWORD PartHash;
	int CarType = CarPartDatabase_GetCarType_Game((DWORD*)_CarPartDB, CarTypeNameHash);

	for (int p = 0; p < NumCarSlots; p++)
	{
		PartHash = ((DWORD*)PresetCar)[24 + p];
		if (PartHash != 0 && PartHash != 1) // Dunno why it's not 1
		{
			DWORD* TheCarPart = (DWORD*)CarPartDatabase_NewGetCarPart_Hook((DWORD*)_CarPartDB, EDX_Unused, CarType, p, PartHash, 0, -1);
			_FECustomizationRecord[p] = CarPartDatabase_GetPartIndex((DWORD*)_CarPartDB, TheCarPart);
		}
		else _FECustomizationRecord[p] = -1;
	}
}