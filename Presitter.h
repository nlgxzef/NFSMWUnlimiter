#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

#define NumFECarRecords 200
#define NumFECustomizationRecords 75
#define NumCarSlots 139
#define CarNameLength 32
#define PresetNameLength 32
#define PresetFileLength 0x290

static injector::hook_back<HRESULT(WINAPI*)(HWND, int, HANDLE, DWORD, LPSTR)> hb_SHGetFolderPathA;

void Presitter_Save(char const* ProfileName)
{
	// Presittter: Dump preset data from customization records next to the game profile
	char SaveProfilePath[MAX_PATH];
	char PresetPath[MAX_PATH];
	char CarTypeName[CarNameLength];
	char PresetName[PresetNameLength];
	int zero = 0;

	hb_SHGetFolderPathA.fun(0, 0x8005, 0, 0, SaveProfilePath); // Get save profile folder
	strcat(SaveProfilePath, "\\NFS Most Wanted");
	strcat(SaveProfilePath, "\\");
	strcat(SaveProfilePath, ProfileName);
	strcat(SaveProfilePath, "\\Presets");
	CreateDirectoryA(SaveProfilePath, 0);

	sprintf(PresetPath, "%s\\SkipSave", SaveProfilePath);
	FILE* SkipFile = fopen(PresetPath, "rb");
	if (!SkipFile)
	{
		DWORD* FEDatabase = *(DWORD**)_FEDatabase;

		for (int i = 0; i < NumFECarRecords; i++)
		{
			// Get car record
			DWORD* CarRecord = (DWORD*)(FEDatabase[4] + 1044 + 20 * i); // In game implementation returns 0 on bonus cars

			if (CarRecord)
			{
				// Get Customization Record
				BYTE CustRecHandle = ((BYTE*)CarRecord)[16];

				if (CustRecHandle != -1)
				{
					// Get customization record
					DWORD* CustomizationRecord = FEPlayerCarDB_GetCustomizationRecordByHandle((DWORD*)(FEDatabase[4] + 1044), CustRecHandle);

					if (CustomizationRecord)
					{
						// Create file handle
						sprintf(PresetPath, "%s\\%02d.bin", SaveProfilePath, CustRecHandle);
						FILE* PresetFile = fopen(PresetPath, "wb");

						if (PresetFile)
						{
							// TODO: Maybe add a message to show the presitter is working on the preset data
							// (Saving %s, please don't turn off the system.)

							memset(CarTypeName, 0, sizeof(CarTypeName));
							memset(PresetName, 0, sizeof(PresetName));

							fwrite(&zero, sizeof(DWORD), 1, PresetFile); // padding 00 00 00 00
							fwrite(&zero, sizeof(DWORD), 1, PresetFile); // padding 00 00 00 00

							sprintf(CarTypeName, GetCarTypeName(FECarRecord_GetType(CarRecord))); // CarTypeName
							fwrite(CarTypeName, sizeof(CarTypeName), 1, PresetFile);

							sprintf(PresetName, "CUSTOMIZATION_RECORD_%02d", CustRecHandle); // Preset Name
							fwrite(PresetName, sizeof(PresetName), 1, PresetFile);

							fwrite(&CarRecord[1], sizeof(DWORD), 1, PresetFile); // frontend hash
							fwrite(&zero, sizeof(DWORD), 1, PresetFile); // padding 00 00 00 00

							fwrite(&CarRecord[2], sizeof(DWORD), 1, PresetFile); // pvehicle hash
							fwrite(&zero, sizeof(DWORD), 1, PresetFile); // padding 00 00 00 00
							fwrite(&zero, sizeof(DWORD), 1, PresetFile); // padding 00 00 00 00
							fwrite(&zero, sizeof(DWORD), 1, PresetFile); // padding 00 00 00 00

							// Write Parts
							for (int p = 0; p < NumCarSlots; p++)
							{
								DWORD* TheCarPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, FECarRecord_GetType(CarRecord), p);
								if (TheCarPart) fwrite(&TheCarPart[0], sizeof(DWORD), 1, PresetFile);
								else fwrite(&zero, sizeof(DWORD), 1, PresetFile); // padding 00 00 00 00
							}

							fwrite(&zero, sizeof(DWORD), 1, PresetFile); // padding 00 00 00 00

							// Close the file
							fclose(PresetFile);
						}
					}
				}
			}
		}
#ifdef _DEBUG
		bReleasePrintf("Presitter: Saved customization records as preset data.\n");
#endif
	}
	else fclose(SkipFile);
}

void Presitter_Load(char const* ProfileName)
{
	// Presitter: Load preset data over customization records
	char SaveProfilePath[MAX_PATH];
	char PresetPath[MAX_PATH];
	char CarTypeName[CarNameLength];
	char PresetName[PresetNameLength];
	BYTE PresetBuf[PresetFileLength];
	int WrongCarCount = 0;

	hb_SHGetFolderPathA.fun(0, 0x8005, 0, 0, SaveProfilePath); // Get save profile folder
	strcat(SaveProfilePath, "\\NFS Most Wanted");
	strcat(SaveProfilePath, "\\");
	strcat(SaveProfilePath, ProfileName);
	strcat(SaveProfilePath, "\\Presets");
	CreateDirectoryA(SaveProfilePath, 0);

	sprintf(PresetPath, "%s\\SkipLoad", SaveProfilePath);
	FILE* SkipFile = fopen(PresetPath, "rb");
	if (!SkipFile)
	{
		DWORD* FEDatabase = *(DWORD**)_FEDatabase;

		for (int i = 0; i < NumFECarRecords; i++)
		{
			// Get car record
			DWORD* CarRecord = (DWORD*)(FEDatabase[4] + 1044 + 20 * i); // In game implementation returns 0 on bonus cars

			if (CarRecord)
			{
				// Get Customization Record
				BYTE CustRecHandle = ((BYTE*)CarRecord)[16];

				if (CustRecHandle != -1)
				{
					// Get customization record
					DWORD* CustomizationRecord = FEPlayerCarDB_GetCustomizationRecordByHandle((DWORD*)(FEDatabase[4] + 1044), CustRecHandle);

					if (CustomizationRecord)
					{
						// Create file handle
						sprintf(PresetPath, "%s\\%02d.bin", SaveProfilePath, CustRecHandle);
						FILE* PresetFile = fopen(PresetPath, "rb");

						if (PresetFile)
						{
							memset(PresetBuf, 0, sizeof(PresetBuf)); // clear the buffer

							// Check file size
							fseek(PresetFile, 0, SEEK_END); // Go to the end
							int FileSize = ftell(PresetFile); // Get current offset
							if (FileSize == PresetFileLength)
							{
								fseek(PresetFile, 0, SEEK_SET); // Return to the beginning
								fread(PresetBuf, sizeof(PresetBuf), 1, PresetFile); // read file to buffer

								char* CarNameFromFEREC = GetCarTypeName(FECarRecord_GetType(CarRecord));
								char* CarNameFromPRESET = (char*)(PresetBuf + 8);
								if (!strcmp(CarNameFromFEREC, CarNameFromPRESET)) // Check if it's the same car
								{
									FECustomizationRecord_BecomePresitter((WORD*)CustomizationRecord, 0, PresetBuf); // Apply parts from preset over Customization record
								}
								else WrongCarCount++;
							}
							else WrongCarCount++;

							fclose(PresetFile); // Close the file
						}
					}
				}
			}
		}

#ifdef _DEBUG
		if (WrongCarCount) bReleasePrintf("Presitter: Loaded preset data over the customization records with %d errors.\n", WrongCarCount);
		else bReleasePrintf("Presitter: Loaded preset data over the customization records.\n");
#endif
	}
	else fclose(SkipFile);
}