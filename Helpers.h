#pragma once

inline bool DoesFileExist(char const* path)
{
	struct stat buffer;
	return (stat(path, &buffer) == 0);
}

bool IsCop(BYTE CarTypeID)
{
	return *(BYTE*)((*(DWORD*)CarTypeInfoArray) + CarTypeID * SingleCarTypeInfoBlockSize + 0x94) == 1;
}

char* GetCarTextOption(CIniReader& CarINI, CIniReader& GeneralINI, char* Section, char* Option, char const* DefaultValue)
{
	return CarINI.ReadString(Section, Option, GeneralINI.ReadString(Section, Option, DefaultValue));
}

int GetCarIntOption(CIniReader& CarINI, CIniReader& GeneralINI, char* Section, char* Option, int DefaultValue)
{
	return CarINI.ReadInteger(Section, Option, GeneralINI.ReadInteger(Section, Option, DefaultValue));
}

int GetCarFloatOption(CIniReader& CarINI, CIniReader& GeneralINI, char* Section, char* Option, float DefaultValue)
{
	return CarINI.ReadFloat(Section, Option, GeneralINI.ReadFloat(Section, Option, DefaultValue));
}

int GetCarTextOptionHash(CIniReader& CarINI, CIniReader& GeneralINI, char* Section, char* Option, char const* DefaultValue)
{
	return bStringHash(GetCarTextOption(CarINI, GeneralINI, Section, Option, DefaultValue));
}

int GetCarTextOptionVLTHash(CIniReader& CarINI, CIniReader& GeneralINI, char* Section, char* Option, char const* DefaultValue)
{
	return Attrib_StringToLowerCaseKey(GetCarTextOption(CarINI, GeneralINI, Section, Option, DefaultValue));
}

bool IsMenuEmpty_Parts(CIniReader& CarINI, CIniReader& GeneralINI)
{
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "BodyKits", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Spoilers", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Rims", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Hoods", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "RoofScoops", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Interior", 0) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Roof", 0) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Brakes", 0) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Headlights", 0) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Taillights", 0) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Mirrors", 0) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Attachments", 0) >= 1) return 0;
	if (BETACompatibility && (GetCarIntOption(CarINI, GeneralINI, "Visual", "CustomGauges", 1) != 0)) return 0;

	return 1;
}

bool IsMenuEmpty_PartsBackroom(CIniReader& CarINI, CIniReader& GeneralINI)
{
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "BodyKits", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Spoilers", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Rims", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "Hoods", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Parts", "RoofScoops", 1) != 0) return 0;
	if (BETACompatibility && (GetCarIntOption(CarINI, GeneralINI, "Visual", "CustomGauges", 1) != 0)) return 0;

	return 1;
}

bool IsMenuEmpty_Performance(CIniReader& CarINI, CIniReader& GeneralINI)
{
	if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Engine", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Transmission", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Chassis", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Nitrous", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Tires", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Brakes", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Performance", "Induction", 1) != 0) return 0;

	return 1;
}

bool IsMenuEmpty_Decals(CIniReader& CarINI, CIniReader& GeneralINI)
{
	if (GetCarIntOption(CarINI, GeneralINI, "Visuals", "DecalsWindshield", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visuals", "DecalsRearWindow", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visuals", "DecalsLeftDoor", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visuals", "DecalsRightDoor", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visuals", "DecalsLeftQuarter", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visuals", "DecalsRightQuarter", 1) != 0) return 0;

	return 1;
}

bool IsMenuEmpty_Visual(CIniReader& CarINI, CIniReader& GeneralINI)
{
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Paint", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Vinyls", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "RimPaint", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "WindowTint", 1) != 0) return 0;
	if (!IsMenuEmpty_Decals(CarINI, GeneralINI)) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Numbers", 1) != 0) return 0;
	if (!BETACompatibility && (GetCarIntOption(CarINI, GeneralINI, "Visual", "CustomGauges", 1) != 0)) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Driver", 0) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "LicensePlate", 0) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Tires", 0) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Neon", 0) != 0) return 0;

	return 1;
}

bool IsMenuEmpty_VisualBackroom(CIniReader& CarINI, CIniReader& GeneralINI)
{
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Paint", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Vinyls", 1) != 0) return 0;
	if (GetCarIntOption(CarINI, GeneralINI, "Visual", "Decals", 1) != 0) return 0;
	if (!BETACompatibility && (GetCarIntOption(CarINI, GeneralINI, "Visual", "CustomGauges", 1) != 0)) return 0;

	return 1;
}

bool IsMenuEmpty_CustomizeMain(CIniReader& CarINI, CIniReader& GeneralINI)
{
	if (!HPCCompatibility)
	{
		if (GetCarIntOption(CarINI, GeneralINI, "Main", "Parts", 1) != 0) return 0;
		if (GetCarIntOption(CarINI, GeneralINI, "Main", "Performance", 1) != 0) return 0;
	}

	if (GetCarIntOption(CarINI, GeneralINI, "Main", "Visual", 1) != 0) return 0;

	return 1;
}

char* GetDefaultRimBrandName(int ID)
{
	if (ID > DefaultRimBrandCount) return "";
	else return DefaultRimBrandNames[ID];
}

char* GetDefaultRimBrandTexture(int ID)
{
	if (ID > DefaultRimBrandCount) return "";
	else return DefaultRimBrandTextures[ID];
}

char* GetDefaultRimBrandString(int ID)
{
	if (ID > DefaultRimBrandCount) return "";
	else return DefaultRimBrandStrings[ID];
}

int GetDefaultVinylGroupIndex(int ID)
{
	if (ID > DefaultVinylGroupCount) return 1;
	else return DefaultVinylGroupIndexes[ID];
}

char* GetDefaultVinylGroupTexture(int ID)
{
	if (ID > DefaultVinylGroupCount) return "";
	else return DefaultVinylGroupTextures[ID];
}

char* GetDefaultVinylGroupString(int ID)
{
	if (ID > DefaultVinylGroupCount) return "";
	else return DefaultVinylGroupStrings[ID];
}