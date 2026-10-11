#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

enum FEPlayerCarDBFilterBits {
    FE_CAR_FILTER_REGION_MASK = -65536,
    FE_CAR_FILTER_REGION_ALL = 983040,
    FE_CAR_FILTER_REGION_MAX = 524288,
    FE_CAR_FILTER_REGION_MIN = 65536,
    FE_CAR_FILTER_REGION_DEBUG = 524288,
    FE_CAR_FILTER_REGION_JAPAN = 262144,
    FE_CAR_FILTER_REGION_EUROPE = 131072,
    FE_CAR_FILTER_REGION_AMERICA = 65536,
    FE_CAR_FILTER_LIST_MASK = 65535,
    FE_CAR_FILTER_LIST_MAX = 8,
    FE_CAR_FILTER_LIST_MIN = 1,
    FE_CAR_FILTER_PINKSLIP = 64,
    FE_CAR_FILTER_LIST_DEBUG = 32,
    FE_CAR_FILTER_LIST_PRESET = 16,
    FE_CAR_FILTER_LIST_BONUS = 8,
    FE_CAR_FILTER_LIST_QUICK_RACE = 4,
    FE_CAR_FILTER_LIST_CAREER = 2,
    FE_CAR_FILTER_LIST_STOCK = 1,
};

struct FECarRecord // sizeof=0x14
{
    DWORD Handle;
    DWORD FEKey;
    DWORD VehicleKey;
    DWORD FilterBits;
    BYTE Customization;
    BYTE CareerHandle;
    WORD Padd;

	bool MatchesFilter(int CarIndex)
	{
		return (CarIndex & this->FilterBits & 0xFFFF0000) != 0 && ((unsigned __int16)CarIndex & this->FilterBits) != 0;
	}

    bool IsFromUnlimiterStable()
    {
        return Padd == UnlimiterStableKey;
    }

    DWORD GetManuLogoHash()
    {
		return FECarRecord_GetManuLogoHash((DWORD*)this);
    }

    DWORD GetLogoHash()
	{
		return FECarRecord_GetLogoHash((DWORD*)this);
	}

    DWORD GetNameHash()
    {
        return FECarRecord_GetNameHash((DWORD*)this);
    }

    int GetCost()
	{   
		return FECarRecord_GetCost((DWORD*)this);
	}

    float GetReleaseFromImpoundCost()
    {
		return FECarRecord_GetReleaseFromImpoundCost((DWORD*)this);
    }

    int GetType()
    {
		return FECarRecord_GetType((DWORD*)this);
    }

    FECarRecord* Default()
    {
		return (FECarRecord*)FECarRecord_Default((DWORD*)this);
    }

    void __as(const FECarRecord *other_record)
    {
        FEKey = other_record->FEKey;
        VehicleKey = other_record->VehicleKey;
        FilterBits = other_record->FilterBits;
    }
};

char const* __fastcall FECarRecord_GetManufacturerName(FECarRecord* _this, void* EDX_Unused)
{
	if (!_this) return (char const*)_nullString;
	
	DWORD Attrib[5], AttribParent[5];

	Attrib_Gen_frontend_frontend(Attrib, _this->FEKey, 0, 0);
	DWORD Parent = Attrib_Instance_GetParent(Attrib);
	Attrib_Gen_frontend_frontend(AttribParent, Parent, 0, 0);
	char const* ManufacturerName = *(const char**)(AttribParent[2] + 24);
	Attrib_Instance_dtInstance(AttribParent);
	Attrib_Instance_dtInstance(Attrib);
	return ManufacturerName;
}