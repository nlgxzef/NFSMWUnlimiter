#pragma once

#include "stdafx.h"
#include "stdio.h"
#include "InGameFunctions.h"
#include "GlobalVariables.h"

int Clamp(int value, int min, int max)
{
	if (value < min) value = min;
	else if (value > max) value = max;

	return value;
}

bool IsCop(int CarTypeID)
{
	return CarTypeInfoArray[CarTypeID].IsCop();
}

bool IsHeli(int CarTypeID)
{
	return CarTypeInfoArray[CarTypeID].IsHeli();
}

bool IsTraffic(int CarTypeID)
{
	return CarTypeInfoArray[CarTypeID].IsTraffic();
}

bool IsSkinnable(int CarTypeID)
{
	return CarTypeInfoArray[CarTypeID].IsSkinnable();
}

void SetSkinnable(int CarTypeID)
{
	CarTypeInfoArray[CarTypeID].SetSkinnable(1);
}

bool ShouldRandomizeInTraffic(int CarTypeID)
{
	return IsTraffic(CarTypeID)
		&& CarConfigs[CarTypeID].RandomParts.RandomizeInTraffic;
}

int GetDefaultNumDecals(int DecalLocation)
{
	return (DecalLocation == CARSLOTID_DECAL_LEFT_DOOR || DecalLocation == CARSLOTID_DECAL_RIGHT_DOOR) ? 6 : 1;
}

bool IsMenuEmpty_Parts(int CarTypeID)
{
	if (CarConfigs[CarTypeID].Parts.BodyKits != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Spoilers != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Rims != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Hoods != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.RoofScoops != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Interior != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Roof != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Brakes != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Headlights != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Taillights != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Mirrors != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Attachments >= 1) return 0;
	if (BETACompatibility && (CarConfigs[CarTypeID].Visual.CustomGauges != 0)) return 0;

	return 1;
}

bool IsMenuEmpty_PartsBackroom(int CarTypeID)
{
	if (CarConfigs[CarTypeID].Parts.BodyKits != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Spoilers != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Rims != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.Hoods != 0) return 0;
	if (CarConfigs[CarTypeID].Parts.RoofScoops != 0) return 0;
	if (BETACompatibility && (CarConfigs[CarTypeID].Visual.CustomGauges != 0)) return 0;

	return 1;
}

bool IsMenuEmpty_Performance(int CarTypeID)
{
	if (CarConfigs[CarTypeID].Performance.Engine != 0) return 0;
	if (CarConfigs[CarTypeID].Performance.Transmission != 0) return 0;
	if (CarConfigs[CarTypeID].Performance.Chassis != 0) return 0;
	if (CarConfigs[CarTypeID].Performance.Nitrous != 0) return 0;
	if (CarConfigs[CarTypeID].Performance.Tires != 0) return 0;
	if (CarConfigs[CarTypeID].Performance.Brakes != 0) return 0;
	if (CarConfigs[CarTypeID].Performance.Induction != 0) return 0;

	return 1;
}

bool IsMenuEmpty_Visual(int CarTypeID)
{
	if (CarConfigs[CarTypeID].Visual.Paint != 0) return 0;
	if (CarConfigs[CarTypeID].Visual.Vinyls != 0) return 0;
	if (CarConfigs[CarTypeID].Visual.RimPaint != 0) return 0;
	if (CarConfigs[CarTypeID].Visual.WindowTint != 0) return 0;
	if (CarConfigs[CarTypeID].Visual.Decals) return 0;
	if (CarConfigs[CarTypeID].Visual.Numbers != 0) return 0;
	if (!BETACompatibility && (CarConfigs[CarTypeID].Visual.CustomGauges != 0)) return 0;
	if (CarConfigs[CarTypeID].Visual.Driver != 0) return 0;
	if (CarConfigs[CarTypeID].Visual.LicensePlate != 0) return 0;
	if (CarConfigs[CarTypeID].Visual.Tires != 0) return 0;
	if (CarConfigs[CarTypeID].Visual.Neon != 0) return 0;

	return 1;
}

bool IsMenuEmpty_VisualBackroom(int CarTypeID)
{
	if (CarConfigs[CarTypeID].Visual.Paint != 0) return 0;
	if (CarConfigs[CarTypeID].Visual.Vinyls != 0) return 0;
	if (CarConfigs[CarTypeID].Visual.Decals) return 0;
	if (!BETACompatibility && (CarConfigs[CarTypeID].Visual.CustomGauges != 0)) return 0;

	return 1;
}

bool IsMenuEmpty_CustomizeMain(int CarTypeID)
{
	if (!HPCCompatibility)
	{
		if (CarConfigs[CarTypeID].Category.Parts != 0) return 0;
		if (CarConfigs[CarTypeID].Category.Performance != 0) return 0;
	}

	if (CarConfigs[CarTypeID].Category.Visual != 0) return 0;

	return 1;
}

// mINI stuff

int mINI_ReadInteger(mINI::INIStructure& ini, std::string Section, std::string Key, int DefaultValue = 0)
{
	int result = DefaultValue;

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			if (ini[Section][Key].starts_with("0x") || ini[Section][Key].starts_with("-0x")) result = std::stol(ini[Section][Key], 0, 16);
			else result = std::stol(ini[Section][Key]);
		}
		catch (const std::exception& ex)
		{
			result = DefaultValue;
		}
	}

	return result;
}

float mINI_ReadFloat(mINI::INIStructure& ini, std::string Section, std::string Key, float DefaultValue = 0.0f)
{
	float result = DefaultValue;

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = std::stof(ini[Section][Key]);
		}
		catch (const std::exception& ex)
		{
			result = DefaultValue;
		}
	}

	return result;
}

char* mINI_ReadString(mINI::INIStructure& ini, std::string Section, std::string Key, const char* DefaultValue = "")
{
	char* result = (char*)DefaultValue;

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = (char*)ini[Section][Key].c_str();
		}
		catch (const std::exception& ex)
		{
			result = (char*)DefaultValue;
		}
	}

	return result;
}

DWORD mINI_ReadHash(mINI::INIStructure& ini, std::string Section, std::string Key, DWORD DefaultValue = -1)
{
	DWORD result = DefaultValue;

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = bStringHash((char*)ini[Section][Key].c_str());
		}
		catch (const std::exception& ex)
		{
			result = DefaultValue;
		}
	}

	return result;
}

DWORD mINI_ReadHashS(mINI::INIStructure& ini, std::string Section, std::string Key, const char* DefaultValue = "")
{
	DWORD result = bStringHash((char*)DefaultValue);

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = bStringHash((char*)ini[Section][Key].c_str());
		}
		catch (const std::exception& ex)
		{
			result = bStringHash((char*)DefaultValue);
		}
	}

	return result;
}

DWORD mINI_ReadVLTHash(mINI::INIStructure& ini, std::string Section, std::string Key, DWORD DefaultValue = 0x82FC1624)
{
	DWORD result = DefaultValue;

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = Attrib_StringToLowerCaseKey(ini[Section][Key].c_str());
		}
		catch (const std::exception& ex)
		{
			result = DefaultValue;
		}
	}

	return result;
}

DWORD mINI_ReadVLTHashS(mINI::INIStructure& ini, std::string Section, std::string Key, const char* DefaultValue = "")
{
	DWORD result = Attrib_StringToLowerCaseKey(DefaultValue);

	if (ini.has(Section) && ini[Section].has(Key))
	{
		try
		{
			result = Attrib_StringToLowerCaseKey(ini[Section][Key].c_str());
		}
		catch (const std::exception& ex)
		{
			result = Attrib_StringToLowerCaseKey(DefaultValue);
		}
	}

	return result;
}

int GetMatchingDefaultRimBrand(DWORD BrandNameHash)
{
	for (int i = 0; i <= DefaultRimBrandCount; i++)
	{
		if (bStringHash(DefaultRimBrandNames[i]) == BrandNameHash) return i;
	}
	return 1; // 0 is custom
}

char* GetDefaultRimBrandName(int ID)
{
	if (ID > DefaultRimBrandCount) return (char*)"";
	else return DefaultRimBrandNames[ID];
}

char* GetDefaultRimBrandTexture(int ID)
{
	if (ID > DefaultRimBrandCount) return (char*)"";
	else return DefaultRimBrandTextures[ID];
}

char* GetDefaultRimBrandString(int ID)
{
	if (ID > DefaultRimBrandCount) return (char*)"";
	else return DefaultRimBrandStrings[ID];
}

int GetMatchingDefaultVinylGroupIndex(int id)
{
	for (int i = 0; i <= DefaultVinylGroupCount; i++)
	{
		if (DefaultVinylGroupIndexes[i] == id) return i;
	}
	return 1; // 0 is custom
}

int GetDefaultVinylGroupIndex(int ID)
{
	if (ID > DefaultVinylGroupCount) return 1;
	else return DefaultVinylGroupIndexes[ID];
}

char* GetDefaultVinylGroupTexture(int ID)
{
	if (ID > DefaultVinylGroupCount) return (char*)"";
	else return DefaultVinylGroupTextures[ID];
}

char* GetDefaultVinylGroupString(int ID)
{
	if (ID > DefaultVinylGroupCount) return (char*)"";
	else return DefaultVinylGroupStrings[ID];
}

bool GetDefaultVinylGroupAltCamera(int ID)
{
	if (ID > DefaultVinylGroupCount) return 1;
	else return DefaultVinylGroupAltCameras[ID];
}

int GetMatchingDefaultPaintBrand(DWORD BrandNameHash)
{
	for (int i = 0; i <= DefaultPaintBrandCount; i++)
	{
		if (bStringHash(DefaultPaintBrandNames[i]) == BrandNameHash) return i;
	}
	return 1; // 0 is custom
}

char* GetDefaultPaintBrandName(int ID)
{
	if (ID > DefaultPaintBrandCount) return (char*)"";
	else return DefaultPaintBrandNames[ID];
}

char* GetDefaultPaintBrandString(int ID)
{
	if (ID > DefaultPaintBrandCount) return (char*)"";
	else return DefaultPaintBrandStrings[ID];
}

int GetDefaultPaintBrandAvailableForBody(int ID)
{
	if (ID > DefaultPaintBrandCount) return 1;
	else return DefaultPaintBrandAvailableForBody[ID];
}

int GetDefaultPaintBrandAvailableForRims(int ID)
{
	if (ID > DefaultPaintBrandCount) return 0;
	else return DefaultPaintBrandAvailableForRims[ID];
}

int GetDefaultPaintBrandAvailableForVinyl(int ID)
{
	if (ID > DefaultPaintBrandCount) return 1;
	else return DefaultPaintBrandAvailableForVinyl[ID];
}

void SetRimBrandName(RimBrand& Brand, const char* Name)
{
	Brand.BrandNameHash = bStringHash((char*)Name);

	strncpy(Brand.BrandName, Name ? Name : "", sizeof(Brand.BrandName) - 1);
	Brand.BrandName[sizeof(Brand.BrandName) - 1] = 0;
}

char* GetDefaultCopDestroyedStringPVehicle(int ID)
{
	if (ID > DefaultCopDestroyedStringCount) return (char*)"";
	else return DefaultCopDestroyedStringPVehicles[ID];
}

char* GetDefaultCopDestroyedString(int ID)
{
	if (ID > DefaultCopDestroyedStringCount) return (char*)"";
	else return DefaultCopDestroyedStrings[ID];
}

void AnimateValue(float& value, float target, float stepSize)
{
	int Direction;

	if (value == target) return;
	else if (value > target) Direction = -1;
	else Direction = 1;

	switch (Direction)
	{
	case -1: // decrease
		value -= stepSize;
		if (value < target) value = target;
		break;
	case 1: // increase
		value += stepSize;
		if (value > target) value = target;
		break;
	}
}

inline float Signum(float value)
{
	return (value < 0.0f) ? -1.0f 
		: (value == 0.0f) ? 0.0f : 1.0f;
}