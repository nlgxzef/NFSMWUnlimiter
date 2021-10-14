#pragma once

inline bool DoesFileExist(char const* path)
{
	struct stat buffer;
	return (stat(path, &buffer) == 0);
}

char num[4];

char* GetManuNameFromID()
{
	CIniReader Manu("UnlimiterData\\_CarManufacturers.ini");
	sprintf(num, "%d", ManuID);

	return Manu.ReadString("Manufacturers", num, "DEFAULT");
}

bool IsCop(BYTE CarTypeID)
{
	return *(BYTE*)((*(DWORD*)CarTypeInfoArray) + CarTypeID * SingleCarTypeInfoBlockSize + 0x94) == 1;
}
