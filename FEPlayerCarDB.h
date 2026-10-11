#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

#define UnlimiterStableKey 0xCA12

#include "FECarRecord.h"
#include "FECustomizationRecord.h"
#include "FECareerRecord.h"
#include "FEInfractionsData.h"

#include "PresetCar.h"

struct FEPlayerCarDB;
FEPlayerCarDB *UnlimiterCarStable;
bool IsUnlimiterCarStableInitialized = false;

char const* DefaultCars_frontend[] = {
	"is300",
	"punto",
	"cobaltss",
	"gti"
};

char const *DefaultCars_pvehicle[] = {
	"is300",
	"punto",
	"cobaltss",
	"gti"
};

struct FEPlayerCarDB // sizeof=0x8CC8
{
    FECarRecord CarTable[NumFECarRecords];
    FECustomizationRecord Customizations[NumFECustomizationRecords];
    FECareerRecord CareerRecords[NumFECareerRecords];
    DWORD SoldHistoryBounty;
    WORD SoldHistoryNumEvadedPursuits;
    WORD SoldHistoryNumBustedPursuits;
    FEInfractionsData SoldHistoryUnservedInfractions;
    FEInfractionsData SoldHistoryServedInfractions;

	FECarRecord* GetCarByIndex(int CarIndex)
	{
		if (CarIndex >= NumFECarRecords)
			return 0;
		else
			return &(CarTable[CarIndex]);
	}

	FECarRecord* GetCarRecordByHandle(unsigned int handle)
	{
		int i = 0;
		FECarRecord* car;

		for (car = CarTable; car->Handle != handle; ++car)
		{
			if (++i >= NumFECarRecords) return 0;
		}
		
		return &(CarTable[i]);
	}

	FECustomizationRecord* GetCustomizationRecordByHandle(unsigned __int8 handle)
	{
		if (handle > NumFECustomizationRecords || Customizations[handle].Handle == 255)
			return 0;
		else
			return &(Customizations[handle]);
	}

	FECareerRecord* GetCareerRecordByHandle(unsigned __int8 handle)
	{
		if (handle > NumFECareerRecords || CareerRecords[handle].Handle == 255)
			return 0;
		else
			return &(CareerRecords[handle]);
	}

	void DeleteAllCars()
	{
		for (int i = 0; i < NumFECarRecords; i++)
		{
			CarTable[i].Handle = -1;
		}
	}

	void DeleteAllCustomizations()
	{
		for (int i = 0; i < NumFECustomizationRecords; i++)
		{
			Customizations[i].Handle = -1;
		}
	}

	void DeleteAllCareerRecords()
	{
		for (int i = 0; i < NumFECareerRecords; i++)
		{
			CareerRecords[i].Handle = -1;
		}
	}

	FECarRecord* CreateNewPresetCar(const char* preset_name)
	{
		return (FECarRecord*)FEPlayerCarDB_CreateNewPresetCar((DWORD*)this, preset_name);
	}

	FECarRecord* CreateNewCarRecord()
	{
		return (FECarRecord*)FEPlayerCarDB_CreateNewCarRecord((DWORD*)this);
	}

	FECustomizationRecord* CreateNewCustomizationRecord()
	{
		return (FECustomizationRecord*)FEPlayerCarDB_CreateNewCustomizationRecord((DWORD*)this);
	}

	FECareerRecord* CreateNewCareerRecord()
	{
		return (FECareerRecord*)FEPlayerCarDB_CreateNewCareerRecord((DWORD*)this);
	}

	bool IsBonusCar(const char* preset_name)
	{
		DWORD nameHash = FEHashUpper((char*)preset_name);

		switch (nameHash)
		{
			case CT_bStringHash("E3_DEMO_BMW"):
			case CT_bStringHash("BONUS_GT2"):
			case CT_bStringHash("CASTROLGT"):
			case CT_bStringHash("BONUS_SL65"):
			case CT_bStringHash("BONUS_C6R"):
			case CT_bStringHash("BL2"):
			case CT_bStringHash("BL3"):
			case CT_bStringHash("BL4"):
			case CT_bStringHash("BL5"):
			case CT_bStringHash("BL6"):
			case CT_bStringHash("BL7"):
			case CT_bStringHash("BL8"):
			case CT_bStringHash("BL9"):
			case CT_bStringHash("BL10"):
			case CT_bStringHash("BL11"):
			case CT_bStringHash("BL12"):
			case CT_bStringHash("BL13"):
			case CT_bStringHash("BL14"):
			case CT_bStringHash("BL15"):
			case CT_bStringHash("CE_997S"):
			case CT_bStringHash("CE_CAMARO"):
			case CT_bStringHash("CE_CORVETTE"):
			case CT_bStringHash("CE_SL65"):
			case CT_bStringHash("CE_GT2"):
			case CT_bStringHash("CE_SUPRA"):
			case CT_bStringHash("CE_GTRSTREET"):
			case CT_bStringHash("CE_C6R"):
			case CT_bStringHash("CE_ELISE"):
			case CT_bStringHash("CE_SL500"):
				return 1;
		}

		return 0;
	}

	void CreateBonusCars()
	{
		FECarRecord* car; // r3
		PresetCar* preset; // r3

		car = CreateNewPresetCar("M3GTRCAREERSTART");
		car->Handle = 0x12345678;
		car->FilterBits = 0xF0020;

		int NumPresetCars = GetNumPresetCars();

		for (int i = 0; i < NumPresetCars; i++)
		{
			preset = GetPresetCarAt(i);
			DWORD PresetNameHash = FEHashUpper(preset->PresetName);
			if (UnlockSystem_IsBonusCarCEOnly_Game(PresetNameHash) || IsBonusCar(preset->PresetName))
			{
				car = CreateNewPresetCar(preset->PresetName);
				if (car)
					car->FilterBits = 0xF0008;
			}
			else
			{
				if (!bStrICmp(preset->PresetName, (char*)"M3GTRCAREERSTART") || *(bool*)_ShowAllPresetsInFE)
					car = CreateNewPresetCar(preset->PresetName);
			}
			Physics_Upgrades_Flush();
		}
	}

	void CreateBonusCars_Hook()
	{
		char* PresetName;
		int CarRecordID;
		int Category;
		int NumberOfBonusCars = BonusCars.size();

		for (int i = -1; i < NumberOfBonusCars; i++)
		{
			if (i == -1)
			{
				PresetName = DefaultBonusCar.PresetName;
				CarRecordID = DefaultBonusCar.CarRecordID;
				Category = DefaultBonusCar.Category;
			}
			else
			{
				PresetName = BonusCars[i].PresetName;
				CarRecordID = BonusCars[i].CarRecordID;
				Category = BonusCars[i].Category;
			}

			if (strcmp(PresetName, "")) // Check the name
			{
				// Check if the preset exists in game
				int PresetNameHash = FEHashUpper(PresetName);
				if (FindFEPresetCar(PresetNameHash))
				{
					// Create preset
					FECarRecord* NewPresetCar = CreateNewPresetCar(PresetName);
					if (NewPresetCar)
					{
						// Check if the preset has a specific car record id
						if (CarRecordID != -1) NewPresetCar->Handle = CarRecordID;

						// Set category
						NewPresetCar->FilterBits = Category;
					}

					Physics_Upgrades_Flush();
				}
			}
		}
	}

	void CreateStockCars()
	{
		Attrib_Instance pvehInst;
		Attrib_Instance feInst;

		Attrib_Class* Class = Attrib_Database_GetClass(*(DWORD**)_Attrib_Database_sThis, 0x4A97EC8F);

		for (DWORD Collection = Attrib_Class_GetFirstCollection(Class);
			Collection;
			Collection = Attrib_Class_GetNextCollection(Class, Collection))
		{
			Attrib_Collection* pveh = Attrib_FindCollection(0x4A97EC8F, Collection);

			Attrib_Instance_ctInstance(&pvehInst, pveh, 0, 0);
			if (!pvehInst.mLayoutPtr) pvehInst.mLayoutPtr = Attrib_DefaultDataArea(80);

			if ((pvehInst.mFlags & 1) == 0)
			{
				Attrib_RefSpec* frontend = (Attrib_RefSpec*)Attrib_Instance_GetAttributePointer((DWORD*)&pvehInst, 0x85885722, 0);
				if (!frontend) frontend = (Attrib_RefSpec*)Attrib_DefaultDataArea(12);

				Attrib_Instance_ctInstance_RS(&feInst, frontend, 0, 0);
				feInst.mFlags = 2;
				if (!feInst.mLayoutPtr) feInst.mLayoutPtr = Attrib_DefaultDataArea(92);

				BYTE* MODEL = (BYTE*)((DWORD*)pvehInst.mLayoutPtr)[7]; // Model name
				feInst.mFlags = 3;

				DWORD* PlayerUsablePtr = (DWORD*)Attrib_Instance_GetAttributePointer((DWORD*)&pvehInst, 0xF099B6AC, 0);
				if (!PlayerUsablePtr) Attrib_DefaultDataArea(1);
				bool PlayerUsable = *(bool*)PlayerUsablePtr;

				if ((PlayerUsable || *(bool*)_ShowAllCarsInFE) && MODEL && *MODEL && (pvehInst.mFlags & 1) == 0)
				{
					FECarRecord *car = CreateNewCarRecord();

					if (car)
					{
						car->FEKey = Attrib_Instance_GetCollection((DWORD*)&feInst);
						car->VehicleKey = Attrib_Instance_GetCollection((DWORD*)&pvehInst);
						car->Default();
						if (*(bool*)_ShowAllCarsInFE) car->FilterBits = (car->FilterBits & 0xFFFF0000) | 1; // stock
					}
				}
				Physics_Upgrades_Flush();
				Attrib_Instance_dtInstance((DWORD*)&feInst);

			}
			Attrib_Instance_dtInstance((DWORD*)&pvehInst);
		}
	}

	void CreateStockCars_Hook()
	{
		// TODO: Allow custom stock cars list
		CreateStockCars();

		// Test: Sell presets
		for (int i = 0; i < NumFECarRecords; i++)
		{
			FECarRecord* car = GetCarByIndex(i);
			if (car && car->Handle != 0x12345678)
			{
				if (car->Handle == -1) continue;
				car->FilterBits |= 0xF0001; // stock
				car->Padd = UnlimiterStableKey; // Mark the car by its padding (unused by default) so we can later know it's from the Unlimiter's stable
			}
		}
	}

	void CreateStockCars_Failsafe()
	{
		// Failsafe: Add first 4 cars to the car lot in case the profile gets used without StockCarsHook
		for (int i = 0; i < 4; i++)
		{
			FECarRecord* car = CreateNewCarRecord();
			if (car)
			{
				car->FEKey = stringhash32((char*)DefaultCars_frontend[i]);
				car->VehicleKey = stringhash32((char*)DefaultCars_pvehicle[i]);
				car->Default();
				if (*(bool*)_ShowAllCarsInFE) car->FilterBits = (car->FilterBits & 0xFFFF0000) | 1; // stock
			}
		}
	}

	FECarRecord* CreateCar_Hook(unsigned int fromCar, int FilterBits)
	{
		FECarRecord *CarRecordByHandle = StockCarsHook ? UnlimiterCarStable->GetCarRecordByHandle(fromCar) : GetCarRecordByHandle(fromCar);
		FECarRecord *result = 0;
		DWORD TheRideInfo[196];

		// In case it's not present in Unlimiter's stable
		if (!CarRecordByHandle) CarRecordByHandle = GetCarRecordByHandle(fromCar);

		if (CarRecordByHandle)
		{
			FECarRecord* NewCarRecord = CreateNewCarRecord();
			result = 0;
			if (NewCarRecord)
			{
				NewCarRecord->__as(CarRecordByHandle);
				FECustomizationRecord *NewCustomizationRecord = CreateNewCustomizationRecord();

				if (NewCustomizationRecord)
				{
					DWORD filter = NewCarRecord->FilterBits & 0xFFFF0000 | FilterBits;
					NewCarRecord->Customization = NewCustomizationRecord->Handle;
					NewCarRecord->FilterBits = filter;
					RideInfo_Init(TheRideInfo, NewCarRecord->GetType(), 0, 0, 0);
					RideInfo_SetRandomPaint(TheRideInfo);
					RideInfo_SetStockParts(TheRideInfo, 0);
					if (FindFEPresetCar(fromCar)) RideInfo_FillWithPreset(TheRideInfo, fromCar); // If the car is a preset, fill the ride with the preset parts
					NewCustomizationRecord->WriteRideIntoRecord(TheRideInfo);
					return NewCarRecord;
				}
				else
				{
					result = 0;
					NewCarRecord->Handle = -1;
				}
			}
		}
		return result;
	}

	void DefaultSoldHistoryData()
	{
		SoldHistoryBounty = 0;
		SoldHistoryNumEvadedPursuits = 0;
		SoldHistoryNumBustedPursuits = 0;
		
		SoldHistoryUnservedInfractions.Assault = 0;
		SoldHistoryUnservedInfractions.Damage = 0;
		SoldHistoryUnservedInfractions.HitAndRun = 0;
		SoldHistoryUnservedInfractions.OffRoad = 0;
		SoldHistoryUnservedInfractions.Reckless = 0;
		SoldHistoryUnservedInfractions.Resist = 0;
		SoldHistoryUnservedInfractions.Racing = 0;
		SoldHistoryUnservedInfractions.Speeding = 0;

		SoldHistoryServedInfractions.Assault = 0;
		SoldHistoryServedInfractions.Damage = 0;
		SoldHistoryServedInfractions.HitAndRun = 0;
		SoldHistoryServedInfractions.OffRoad = 0;
		SoldHistoryServedInfractions.Reckless = 0;
		SoldHistoryServedInfractions.Resist = 0;
		SoldHistoryServedInfractions.Racing = 0;
		SoldHistoryServedInfractions.Speeding = 0;
	}

	// Vanilla
	void Default()
	{
		DeleteAllCars();
		DeleteAllCustomizations();
		DeleteAllCareerRecords();

		if (BonusCarsHook && BonusCars.size()) CreateBonusCars_Hook();
		else CreateBonusCars();

		if (StockCarsHook) CreateStockCars_Failsafe();
		else CreateStockCars();

		DefaultSoldHistoryData();
	}

	// Unlimiter
	void Default_Unlimiter()
	{
		DeleteAllCars();
		DeleteAllCustomizations();
		DeleteAllCareerRecords();

		if (BonusCarsHook && BonusCars.size()) CreateBonusCars_Hook();
		else CreateBonusCars();

		CreateStockCars_Hook();

		DefaultSoldHistoryData();
	}

	void BuildRideForPlayer(unsigned int car, int player, /*RideInfo*/DWORD* ride)
	{
		FECarRecord* carrec = StockCarsHook ? UnlimiterCarStable->GetCarRecordByHandle(car) : GetCarRecordByHandle(car);
		if (!carrec) carrec = GetCarRecordByHandle(car);

		int Type = carrec->GetType();
		RideInfo_Init(ride, Type, 0, 0, 0); // CarRenderUsage::CarRenderUsage_Player
		FECustomizationRecord *cust = carrec->IsFromUnlimiterStable()
			? UnlimiterCarStable->GetCustomizationRecordByHandle(carrec->Customization)
			: GetCustomizationRecordByHandle(carrec->Customization);
		if (cust)
		{
			FECustomizationRecord_WriteRecordIntoRide((DWORD*)cust, ride);
		}
		else
		{
			RideInfo_SetRandomPaint(ride);
			RideInfo_SetStockParts(ride, 0);
		}
	}
};

FEPlayerCarDB* _FEPlayerCarDB;

void __fastcall FEPlayerCarDB_Default(FEPlayerCarDB* _this, void* EDX_Unused)
{
	if (!IsUnlimiterCarStableInitialized)
	{
		UnlimiterCarStable = (FEPlayerCarDB*)j_malloc(sizeof(FEPlayerCarDB));
		if (UnlimiterCarStable) IsUnlimiterCarStableInitialized = true;
		else
		{
			IsUnlimiterCarStableInitialized = false;
			StockCarsHook = false;
		}

		if (IsUnlimiterCarStableInitialized) UnlimiterCarStable->Default_Unlimiter();
	}

	_this->Default();
}

FECarRecord* __fastcall FEPlayerCarDB_GetCarRecordByHandle_Unlimiter(FEPlayerCarDB* _this, void* EDX_Unused, unsigned int handle)
{
	FECarRecord* carrec = StockCarsHook ? UnlimiterCarStable->GetCarRecordByHandle(handle) : _this->GetCarRecordByHandle(handle);
	if (!carrec) carrec = _this->GetCarRecordByHandle(handle);
	return carrec;
}

void __fastcall FEPlayerCarDB_BuildRideForPlayer_Unlimiter(FEPlayerCarDB* _this, void* EDX_Unused, unsigned int car, int player, DWORD *ride)
{
	_this->BuildRideForPlayer(car, player, ride);
}

FECarRecord* __fastcall FEPlayerCarDB_CreateCar(FEPlayerCarDB* _this, void* EDX_Unused, unsigned int fromCar, int FilterBits)
{
	return _this->CreateCar_Hook(fromCar, FilterBits);
}

// 0x590D9F
void __declspec(naked) FEPlayerCarDB_Default_BonusCarsCodeCave()
{
	_asm
	{
		pushad
		mov ecx, ebx
		mov _FEPlayerCarDB, ecx
	}

	_FEPlayerCarDB->CreateBonusCars_Hook();

	_asm
	{
		popad
		push 0x590EC1
		retn
	}
}