#include "stdio.h"
#include "InGameFunctions.h"

#define NumCarSlots 139

void __fastcall FECustomizationRecord_BecomePresitter(WORD* _FECustomizationRecord, void* EDX_Unused, BYTE* PresetCar)
{
	int CarTypeNameHash = bStringHash((char*)PresetCar + 8);
	DWORD PartHash;
	int CarType = CarPartDatabase_GetCarType((DWORD*)_CarPartDB, CarTypeNameHash);

	for (int p = 0; p < NumCarSlots; p++)
	{
		PartHash = ((DWORD*)PresetCar)[24 + p];
		if (PartHash != 0 && PartHash != 1) // Dunno why it's not 1
		{
			DWORD* TheCarPart = (DWORD*)CarPartDatabase_NewGetCarPart((DWORD*)_CarPartDB, CarType, p, PartHash, 0, -1);
			_FECustomizationRecord[p] = CarPartDatabase_GetPartIndex((DWORD*)_CarPartDB, TheCarPart);
		}
		else _FECustomizationRecord[p] = -1;
	}
}