#pragma once

#include "stdio.h"
#include "CarPart.h"

#include "InGameTypes.h"
#include "InGameFunctions.h"
#include "GlobalVariables.h"
#include "Game.h"

//char TextureName[255];
//char* NormalMapSuffix = (char*)"_N";
//int InteriorTextureHash, InteriorNormalTextureHash;

int CarRenderInfo_GetLightState(DWORD* CarRenderInfo, int LightID)
{
	int result = 0; // OFF
	bool DamageLights = false;

	DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
	if (RideInfo)
	{
		DamageLights = CarConfigs[RideInfo[0]].Textures.DamageLights;
	}

	int OnLights = CarRenderInfo[1416];
	int BrokenLights = CarRenderInfo[1417];

	if (OnLights & LightID) result = 1; // ON
	if (BrokenLights & LightID) result = DamageLights ? 2 : 0; // DAMAGE0 or OFF

	return result;
}

void __fastcall CarRenderInfo_UpdateLightStateTextures(DWORD* CarRenderInfo, void* EDX_Unused)
{
	ReplacementTextureEntry* BodyReplacementTextureTable = (ReplacementTextureEntry*)(CarRenderInfo + 143);
	ReplacementTextureEntry* BodyReplacementTextureTableCarbon = (ReplacementTextureEntry*)(CarRenderInfo + 362);
	UsedCarTextureInfo* UsedTextureInfos = (UsedCarTextureInfo*)(CarRenderInfo + 1192);

	bool OwnCentre = false;
	bool OwnReverse = false;

	char TextureNameBuf[64];

	DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
	if (RideInfo)
	{
		OwnCentre = CarConfigs[RideInfo[0]].Textures.CentreBrake;
		OwnReverse = CarConfigs[RideInfo[0]].Textures.Reverse;
	}

	// Headlights
	int LeftHLState = (*(int*)_ForceHeadlightsOn) ? 1 : CarRenderInfo_GetLightState(CarRenderInfo, 1);
	int RightHLState = (*(int*)_ForceHeadlightsOn) ? 1 : CarRenderInfo_GetLightState(CarRenderInfo, 2);

	if (!CarConfigs[RideInfo[0]].Textures.HeadlightOff) // If headlight off texture is disabled
	{
		if (LeftHLState == 0) LeftHLState = 1;
		if (RightHLState == 0) RightHLState = 1;
	}

	DWORD ReplaceHLLeft = UsedTextureInfos->ReplaceHeadlightHash[LeftHLState];
	DWORD ReplaceHLRight = UsedTextureInfos->ReplaceHeadlightHash[RightHLState];
	DWORD ReplaceHLGlassLeft = UsedTextureInfos->ReplaceHeadlightGlassHash[LeftHLState];
	DWORD ReplaceHLGlassRight = UsedTextureInfos->ReplaceHeadlightGlassHash[RightHLState];

	// Normal table
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 27, ReplaceHLLeft, 73); // Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 37, ReplaceHLLeft, 73); // Mapped Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 28, ReplaceHLRight, 73); // Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 38, ReplaceHLRight, 73); // Mapped Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 32, ReplaceHLGlassLeft, 73); // Glass Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 42, ReplaceHLGlassLeft, 73); // Mapped Glass Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 33, ReplaceHLGlassRight, 73); // Glass Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 43, ReplaceHLGlassRight, 73); // Mapped Glass Right

	// CF table
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 27, ReplaceHLLeft, 73); // Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 37, ReplaceHLLeft, 73); // Mapped Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 28, ReplaceHLRight, 73); // Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 38, ReplaceHLRight, 73); // Mapped Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 32, ReplaceHLGlassLeft, 73); // Glass Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 42, ReplaceHLGlassLeft, 73); // Mapped Glass Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 33, ReplaceHLGlassRight, 73); // Glass Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 43, ReplaceHLGlassRight, 73); // Mapped Glass Right


	// Brakelights
	int LeftBLState = *(int*)_ForceBrakelightsOn ? 1 : CarRenderInfo_GetLightState(CarRenderInfo, 8);
	int RightBLState = *(int*)_ForceBrakelightsOn ? 1 : CarRenderInfo_GetLightState(CarRenderInfo, 16);
	int CentreBLState = CarRenderInfo_GetLightState(CarRenderInfo, 32);

	DWORD ReplaceBLLeft = UsedTextureInfos->ReplaceBrakelightHash[LeftBLState];
	DWORD ReplaceBLRight = UsedTextureInfos->ReplaceBrakelightHash[RightBLState];
	DWORD ReplaceBLCentre = UsedTextureInfos->ReplaceBrakelightHash[CentreBLState];
	DWORD ReplaceBLGlassLeft = UsedTextureInfos->ReplaceBrakelightGlassHash[LeftBLState];
	DWORD ReplaceBLGlassRight = UsedTextureInfos->ReplaceBrakelightGlassHash[RightBLState];
	DWORD ReplaceBLGlassCentre = UsedTextureInfos->ReplaceBrakelightGlassHash[CentreBLState];

	// Centre Brakelight (had to read the texture as we have no space for it in CRI)
	if (OwnCentre)
	{
		sprintf(TextureNameBuf, "%s_CENTRE_BRAKELIGHT", GetCarTypeName(RideInfo[0])); // Centre brakelight texture prefix
		DWORD CentreBLTex = bStringHash(TextureNameBuf);

		DWORD* Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::LEFT_BRAKELIGHT); // Brakelights
		if (Part)
		{
			CentreBLTex = CarPart_GetAppliedAttributeUParam(Part, bStringHash((char*)"TEXTURE_NAME_CENTRE"), CentreBLTex); // TEXTURE_NAME
		}

		switch (CentreBLState)
		{
		case 0: // Off
		default:
			ReplaceBLCentre = bStringHash2((char*)"_OFF", CentreBLTex);
			break;
		case 1: // On
			ReplaceBLCentre = bStringHash2((char*)"_ON", CentreBLTex);
			break;
		case 2: // Damaged
			ReplaceBLCentre = bStringHash2((char*)"_DAMAGE0", CentreBLTex);
			break;
		}
	}

	// Normal table
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 29, ReplaceBLLeft, 73); // Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 39, ReplaceBLLeft, 73); // Mapped Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 30, ReplaceBLRight, 73); // Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 40, ReplaceBLRight, 73); // Mapped Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 31, ReplaceBLCentre, 73); // Centre
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 41, ReplaceBLCentre, 73); // Mapped Centre
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 34, ReplaceBLGlassLeft, 73); // Glass Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 44, ReplaceBLGlassLeft, 73); // Mapped Glass Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 35, ReplaceBLGlassRight, 73); // Glass Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 45, ReplaceBLGlassRight, 73); // Mapped Glass Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 36, ReplaceBLGlassCentre, 73); // Glass Centre
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTable, 46, ReplaceBLGlassCentre, 73); // Mapped Glass Centre

	// CF table
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 29, ReplaceBLLeft, 73); // Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 39, ReplaceBLLeft, 73); // Mapped Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 30, ReplaceBLRight, 73); // Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 40, ReplaceBLRight, 73); // Mapped Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 31, ReplaceBLCentre, 73); // Centre
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 41, ReplaceBLCentre, 73); // Mapped Centre
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 34, ReplaceBLGlassLeft, 73); // Glass Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 44, ReplaceBLGlassLeft, 73); // Mapped Glass Left
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 35, ReplaceBLGlassRight, 73); // Glass Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 45, ReplaceBLGlassRight, 73); // Mapped Glass Right
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 36, ReplaceBLGlassCentre, 73); // Glass Centre
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 46, ReplaceBLGlassCentre, 73); // Mapped Glass Centre

	// Reverse lights
	if (OwnReverse)
	{
		int RevLState = *(int*)_ForceReverselightsOn ? 1 : CarRenderInfo_GetLightState(CarRenderInfo, 192);

		DWORD ReplaceRevL = UsedTextureInfos->ReplaceReverselightHash[RevLState];

		// Normal table
		ReplacementTextureTable_WriteEntry(BodyReplacementTextureTable, 47, bStringHash((char*)"REVERSE_LEFT"), ReplaceRevL, 73); // Left Reverse
		ReplacementTextureTable_WriteEntry(BodyReplacementTextureTable, 48, bStringHash((char*)"REVERSE_RIGHT"), ReplaceRevL, 73); // Right Reverse
		// CF table
		ReplacementTextureTable_WriteEntry(BodyReplacementTextureTableCarbon, 47, bStringHash((char*)"REVERSE_LEFT"), ReplaceRevL, 73); // Left Reverse
		ReplacementTextureTable_WriteEntry(BodyReplacementTextureTableCarbon, 48, bStringHash((char*)"REVERSE_RIGHT"), ReplaceRevL, 73); // Right Reverse
	}
}

void __fastcall CarRenderInfo_UpdateCarReplacementTextures(DWORD* CarRenderInfo, void* EDX_Unused)
{
	ReplacementTextureEntry* BodyReplacementTextureTable = (ReplacementTextureEntry*)(CarRenderInfo + 143);
	ReplacementTextureEntry* BodyReplacementTextureTableCarbon = (ReplacementTextureEntry*)(CarRenderInfo + 362);
	UsedCarTextureInfo* UsedTextureInfos = (UsedCarTextureInfo*)(CarRenderInfo + 1192);

	char srcTextureNameBuf[64];
	DWORD srcTextureHash = 0;
	DWORD TextureHash = 0;

	// Do Extra Customization texture replacements
	if (!DisableTextureReplacement)
	{
		DWORD* RideInfo = (DWORD*)CarRenderInfo[33];

		if (RideInfo)
		{
			// INTERIOR and INTERIOR_N replacement
			DWORD* Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::INTERIOR);
			sprintf(srcTextureNameBuf, "%s_INTERIOR", GetCarTypeName(RideInfo[0]));
			srcTextureHash = bStringHash(srcTextureNameBuf);

			if (Part)
			{
				TextureHash = CarPart_GetTextureNameHash(Part);
				if (TextureHash)
				{
					ReplacementTextureTable_WriteEntry(BodyReplacementTextureTable, 49, srcTextureHash, TextureHash, 73); // INTERIOR
					ReplacementTextureTable_WriteEntry(BodyReplacementTextureTable, 50, bStringHash2((char*)"_N", srcTextureHash), bStringHash2((char*)"_N", TextureHash), 73); // INTERIOR_N
				}
			}

			// LICENSEPLATE
			Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::LICENSE_PLATE);

			if (Part)
			{
				TextureHash = CarPart_GetTextureNameHash(Part);
				if (TextureHash)
				{
					ReplacementTextureTable_WriteEntry(BodyReplacementTextureTable, 51, 0x4C95C6F8, TextureHash, 73); // LICENSEPLATE
					ReplacementTextureTable_WriteEntry(BodyReplacementTextureTable, 52, bStringHash2((char*)"_N", 0x4C95C6F8), bStringHash2((char*)"_N", TextureHash), 73); // LICENSEPLATE_N
				}
			}

			// TIRE
			Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::HEADLIGHT);

			if (Part)
			{
				TextureHash = CarPart_GetTextureNameHash(Part);
				if (TextureHash)
				{
					ReplacementTextureTable_WriteEntry(BodyReplacementTextureTable, 53, 0xE4CEA024, TextureHash, 73); // TIRE_STYLE01
					ReplacementTextureTable_WriteEntry(BodyReplacementTextureTable, 54, bStringHash2((char*)"_N", 0xE4CEA024), bStringHash2((char*)"_N", TextureHash), 73); // TIRE_STYLE01_N
				}
			}

			// Attachments

			int CurrTexReplSlot = 55;

			for (int i = 0; i < 10; i++)
			{
				Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::ATTACHMENT0 + i);

				if (Part)
				{
					srcTextureHash = CarPart_GetAppliedAttributeUParam(Part, bStringHash((char*)"TEXTURE_NAME_OLD"), 0);
					TextureHash = CarPart_GetTextureNameHash(Part);

					if (srcTextureHash && TextureHash)
					{
						ReplacementTextureTable_WriteEntry(BodyReplacementTextureTable, CurrTexReplSlot++, srcTextureHash, TextureHash, 73); // Add replacement texture
						if (i < 5) ReplacementTextureTable_WriteEntry(BodyReplacementTextureTable, CurrTexReplSlot++, bStringHash2((char*)"_N", srcTextureHash), bStringHash2((char*)"_N", TextureHash), 73); // Normal map (ATTACHMENT0-4 only)
					}
				}
			}
		}
	}

	// Copy main table to CF table
	memcpy(BodyReplacementTextureTableCarbon, BodyReplacementTextureTable, 0x36C);

	// Do CF Stuff
	DWORD Carbonfibre = bStringHash((char*)"CARBONFIBRE");

	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 0, Carbonfibre, 73); // Skin1
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 1, UsedTextureInfos->ReplaceGlobalSkinHash, 73); // Skin1b
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 2, UsedTextureInfos->ReplaceGlobalSkinHash, 73); // Global_Skin1
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 3, Carbonfibre, 73); // Carskin_Carbonfibre
	ReplacementTextureTable_UpdateEntry(BodyReplacementTextureTableCarbon, 4, Carbonfibre, 73); // U2 Carskin 0x3C84D757
}

void GetUsedCarTextureInfo(UsedCarTextureInfo* info, DWORD* RideInfo, int front_end_only)
{
	char* CarTypeName = GetCarTypeName(RideInfo[0]);
	int NumUsedCarTextures = 0;
	int NumTempUsedCarTextures = 0;

	bool IsInFE = *(int*)_TheGameFlowManager == 3;

	memset(info, 0, sizeof(UsedCarTextureInfo));

	char TextureNameBuf[64];

	sprintf(TextureNameBuf, "%s_SKIN1", CarTypeName); // SKIN1
	info->MappedSkinHash = bStringHash(TextureNameBuf);

	sprintf(TextureNameBuf, "%s_SKIN1B", CarTypeName); // SKIN1B
	info->MappedSkinbHash = bStringHash(TextureNameBuf);

	info->MappedGlobalSkinHash = bStringHash((char*)"GLOBAL_SKIN1"); // Global Skin1

	DWORD* Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::FRONT_WHEEL); // Front wheel
	DWORD TextureHash = 0;

	if (Part)
	{
		TextureHash = CarPart_GetTextureNameHash(Part);
		if (TextureHash) info->MappedWheelHash = bStringHash2((char*)"_WHEEL", TextureHash);
		else
		{
			sprintf(TextureNameBuf, "%s_TIRE", CarTypeName);
			info->MappedWheelHash = CarConfigs[RideInfo[0]].Textures.TireInnerMask ? bStringHash(TextureNameBuf) : 0;
		}
	}

	Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::REAR_WHEEL); // Rear wheel
	if (Part)
	{
		TextureHash = CarPart_GetTextureNameHash(Part);
		if (TextureHash) info->MappedSpinnerHash = bStringHash2((char*)"_WHEEL", TextureHash);
		else
		{
			sprintf(TextureNameBuf, "%s_TIRE", CarTypeName);
			info->MappedSpinnerHash = CarConfigs[RideInfo[0]].Textures.TireInnerMask ? bStringHash(TextureNameBuf) : 0;
		}
	}

	info->MappedSpoilerHash = bStringHash((char*)"SPOILER_SKIN1"); // Spoiler

	info->MappedRoofScoopHash = bStringHash((char*)"ROOF_SKIN"); // Roof scoop

	TextureHash = RideInfo[15]; // Replace skin hashes
	if (TextureHash)
	{
		info->ReplaceSkinHash = TextureHash; // mCompositeSkinHash
		info->ReplaceWheelHash = RideInfo[16]; // mCompositeWheelHash
		info->ReplaceSpinnerHash = RideInfo[17]; // mCompositeSpinnerHash

		/*Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::BASE_PAINT);
		if (Part) TextureHash = CarPart_GetTextureNameHash(Part);
		else TextureHash = 0;*/

		info->ReplaceSpoilerHash = TextureHash;
	}
	else // non-skinnable cars
	{
		TextureHash = info->MappedSkinHash;
		info->ReplaceSkinHash = TextureHash;
		info->ReplaceSpoilerHash = TextureHash;
		info->ReplaceWheelHash = 0;
		info->ReplaceSpinnerHash = 0;
	}

	info->ReplaceRoofScoopHash = TextureHash;

	info->ReplaceSkinbHash = 0;
	info->ReplaceGlobalSkinHash = info->ReplaceSkinHash;

	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, RideInfo[15] ? RideInfo[15] : info->ReplaceSkinHash); // Add replace skin hash
	//if (info->ReplaceSkinbHash) NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceSkinbHash);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, RideInfo[16] ? RideInfo[16] : info->ReplaceWheelHash); // Add replace wheel hash
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, RideInfo[17] ? RideInfo[17] : info->ReplaceSpinnerHash); // Add replace spinner hash

	NumTempUsedCarTextures = GetTempCarSkinTextures(info->TexturesToLoadTemp, NumTempUsedCarTextures, MaxTempTex, RideInfo);

	sprintf(TextureNameBuf, "%s_SKIN2", CarTypeName); // SKIN2
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf)); // Add Skin2

	sprintf(TextureNameBuf, "%s_SKIN3", CarTypeName); // SKIN3
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf)); // Add Skin3

	sprintf(TextureNameBuf, "%s_SKIN4", CarTypeName); // SKIN4
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf)); // Add Skin4

	// Light textures
	sprintf(TextureNameBuf, "%s_KIT00_HEADLIGHT", CarTypeName); // Headlight texture prefix
	DWORD HLTex = bStringHash(TextureNameBuf);

	sprintf(TextureNameBuf, "%s_KIT00_BRAKELIGHT", CarTypeName); // Brakelight texture prefix
	DWORD BLTex = bStringHash(TextureNameBuf);

	bool OwnCentre = CarConfigs[RideInfo[0]].Textures.CentreBrake;
	bool OwnReverse = CarConfigs[RideInfo[0]].Textures.Reverse;

	DWORD CentreBLTex = BLTex;
	DWORD RevLTex = BLTex;

	if (OwnCentre)
	{
		sprintf(TextureNameBuf, "%s_CENTRE_BRAKELIGHT", CarTypeName); // Centre brakelight texture prefix
		CentreBLTex = bStringHash(TextureNameBuf);
	}

	if (OwnReverse)
	{
		sprintf(TextureNameBuf, "%s_REVERSE", CarTypeName); // Reverse light texture prefix
		RevLTex = bStringHash(TextureNameBuf);
	}

	// Check texture name from attributes
	Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::LEFT_HEADLIGHT); // Headlights
	if (Part)
	{
		HLTex = CarPart_GetAppliedAttributeUParam(Part, 0x10C98090, HLTex); // TEXTURE_NAME
	}

	Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::LEFT_BRAKELIGHT); // Brakelights
	if (Part)
	{
		BLTex = CarPart_GetAppliedAttributeUParam(Part, 0x10C98090, BLTex); // TEXTURE_NAME
		CentreBLTex = OwnCentre ? CarPart_GetAppliedAttributeUParam(Part, bStringHash((char*)"TEXTURE_NAME_CENTRE"), CentreBLTex) : BLTex; // TEXTURE_NAME
		RevLTex = OwnReverse ? CarPart_GetAppliedAttributeUParam(Part, bStringHash((char*)"TEXTURE_NAME_REVERSE"), RevLTex) : BLTex; // TEXTURE_NAME
	}

	info->MappedLightHash[0] = bStringHash((char*)"HEADLIGHT_LEFT");
	info->MappedLightHash[1] = bStringHash((char*)"HEADLIGHT_RIGHT");
	info->MappedLightHash[5] = bStringHash((char*)"HEADLIGHT_GLASS_LEFT");
	info->MappedLightHash[6] = bStringHash((char*)"HEADLIGHT_GLASS_RIGHT");
	info->MappedLightHash[2] = bStringHash((char*)"BRAKELIGHT_LEFT");
	info->MappedLightHash[3] = bStringHash((char*)"BRAKELIGHT_RIGHT");
	info->MappedLightHash[4] = bStringHash((char*)"BRAKELIGHT_CENTRE");
	info->MappedLightHash[7] = bStringHash((char*)"BRAKELIGHT_GLASS_LEFT");
	info->MappedLightHash[8] = bStringHash((char*)"BRAKELIGHT_GLASS_RIGHT");
	info->MappedLightHash[9] = bStringHash((char*)"BRAKELIGHT_GLASS_CENTRE");
	//info->MappedLightHash[10] = bStringHash((char*)"REVERSE_LIGHT"); // New dynamic name for reverse lights

	bool Onf = !IsInFE && CarConfigs[RideInfo[0]].Textures.BrakelightOnfInGame;

	info->ReplaceHeadlightHash[0] = bStringHash2((char*)"_OFF", HLTex);
	info->ReplaceHeadlightHash[1] = bStringHash2((char*)"_ON", HLTex);
	info->ReplaceHeadlightHash[2] = bStringHash2((char*)"_DAMAGE0", HLTex);
	info->ReplaceHeadlightGlassHash[0] = bStringHash2((char*)"_GLASS_OFF", HLTex);
	info->ReplaceHeadlightGlassHash[1] = bStringHash2((char*)"_GLASS_ON", HLTex);
	info->ReplaceHeadlightGlassHash[2] = bStringHash2((char*)"_GLASS_DAMAGE0", HLTex);
	info->ReplaceBrakelightHash[0] = bStringHash2(Onf ? (char*)"_ONF" : (char*)"_OFF", BLTex);
	info->ReplaceBrakelightHash[1] = bStringHash2((char*)"_ON", BLTex);
	info->ReplaceBrakelightHash[2] = bStringHash2((char*)"_DAMAGE0", BLTex);
	info->ReplaceBrakelightGlassHash[0] = bStringHash2((char*)"_GLASS_OFF", BLTex);
	info->ReplaceBrakelightGlassHash[1] = bStringHash2((char*)"_GLASS_ON", BLTex);
	info->ReplaceBrakelightGlassHash[2] = bStringHash2((char*)"_GLASS_DAMAGE0", BLTex);
	info->ReplaceReverselightHash[0] = OwnReverse ? bStringHash2((char*)"_OFF", RevLTex) : 0;
	info->ReplaceReverselightHash[1] = OwnReverse ? bStringHash2((char*)"_ON", RevLTex) : 0;
	info->ReplaceReverselightHash[2] = OwnReverse ? bStringHash2((char*)"_DAMAGE0", RevLTex) : 0;

	// Add light textures to the table
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceHeadlightHash[0]);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceHeadlightHash[1]);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceHeadlightHash[2]);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceHeadlightGlassHash[0]);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceHeadlightGlassHash[1]);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceHeadlightGlassHash[2]);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceBrakelightHash[0]);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceBrakelightHash[1]);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceBrakelightHash[2]);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceBrakelightGlassHash[0]);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceBrakelightGlassHash[1]);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceBrakelightGlassHash[2]);

	if (OwnCentre) // Don't have space in struct, names will get read again in UpdateLightStateTextures
	{
		NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash2((char*)"_OFF", CentreBLTex));
		NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash2((char*)"_ON", CentreBLTex));
		NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash2((char*)"_DAMAGE0", CentreBLTex));
	}

	if (OwnReverse)
	{
		NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceReverselightHash[0]);
		NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceReverselightHash[1]);
		NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, info->ReplaceReverselightHash[2]);
	}

	// Add other car textures
	sprintf(TextureNameBuf, "%s_MISC", CarTypeName); // MISC
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	sprintf(TextureNameBuf, "%s_MISC_N", CarTypeName); // MISC_N
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	sprintf(TextureNameBuf, "%s_INTERIOR", CarTypeName); // INTERIOR
	TextureHash = bStringHash(TextureNameBuf);
	Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::INTERIOR); // Interior
	if (Part)
	{
		TextureHash = CarPart_GetAppliedAttributeUParam(Part, 0x10C98090, TextureHash); // TEXTURE_NAME
	}
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, TextureHash);
	//sprintf(TextureNameBuf, "%s_INTERIOR_N", CarTypeName); // INTERIOR_N
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash2((char*)"_N", TextureHash));

	sprintf(TextureNameBuf, "%s_BADGING", CarTypeName); // BADGING
	TextureHash = bStringHash(TextureNameBuf);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, TextureHash);
	info->MappedBadgingHash = TextureHash;

	sprintf(TextureNameBuf, "%s_BADGING_N", CarTypeName); // BADGING_N
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	sprintf(TextureNameBuf, "%s_DRIVER", CarTypeName); // DRIVER
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	sprintf(TextureNameBuf, "%s_ENGINE", CarTypeName); // ENGINE
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	sprintf(TextureNameBuf, "%s_BADGING_EU", CarTypeName); // BADGING_EU
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	sprintf(TextureNameBuf, "%s_LICENSE_PLATE", CarTypeName); // LICENSE_PLATE
	TextureHash = bStringHash(TextureNameBuf);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, TextureHash);
	info->MappedLicensePlateHash = TextureHash;

	sprintf(TextureNameBuf, "%s_SIDELIGHT", CarTypeName); // SIDELIGHT
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	sprintf(TextureNameBuf, "%s_DOOR_HANDLE", CarTypeName); // DOOR_HANDLE
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	sprintf(TextureNameBuf, "%s_LOGO", CarTypeName); // LOGO
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	//sprintf(TextureNameBuf, "AUDIO_SKIN", CarTypeName); // AUDIO_SKIN (U2 leftover??)
	//NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	char* ShadowSuffix = IsInFE ? (char*)"FE" : (char*)"IG";
	sprintf(TextureNameBuf, "%s_SHADOW%s", CarTypeName, ShadowSuffix); // SHADOWFE/IG
	TextureHash = bStringHash(TextureNameBuf);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, TextureHash);
	info->ShadowHash = TextureHash;

	sprintf(TextureNameBuf, "%s_NEON", CarTypeName); // NEON
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	sprintf(TextureNameBuf, "%s_TIRE", CarTypeName); // TIRE
	TextureHash = bStringHash(TextureNameBuf);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, TextureHash);
	info->MappedTireHash = TextureHash;

	sprintf(TextureNameBuf, "%s_TIRE_N", CarTypeName); // TIRE_N
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	sprintf(TextureNameBuf, "%s_RIM", CarTypeName); // RIM
	TextureHash = bStringHash(TextureNameBuf);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, TextureHash);
	info->MappedRimHash = TextureHash;

	sprintf(TextureNameBuf, "%s_RIM_BLUR", CarTypeName); // RIM_BLUR
	TextureHash = bStringHash(TextureNameBuf);
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, TextureHash);
	info->MappedRimBlurHash = TextureHash;

	sprintf(TextureNameBuf, "%s_TREAD", CarTypeName); // TREAD
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	sprintf(TextureNameBuf, "%s_TREAD_N", CarTypeName); // TREAD_N
	NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, bStringHash(TextureNameBuf));

	// Attachments
	DWORD srcTextureHash = 0;

	for (int i = 0; i < 10; i++)
	{
		Part = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::ATTACHMENT0 + i);

		if (Part)
		{
			srcTextureHash = CarPart_GetAppliedAttributeUParam(Part, bStringHash((char*)"TEXTURE_NAME_OLD"), 0);
			TextureHash = CarPart_GetTextureNameHash(Part);

			if (srcTextureHash && TextureHash)
			{
				UsedCarTextureReplace(info->TexturesToLoadPerm, NumUsedCarTextures, srcTextureHash, TextureHash); // Add replacement texture
				if (i < 5) UsedCarTextureReplace(info->TexturesToLoadPerm, NumUsedCarTextures, bStringHash2((char*)"_N", srcTextureHash), bStringHash2((char*)"_N", TextureHash)); // Normal map (ATTACHMENT0-4 only)
			}
		}
	}

	// Load decals
	DWORD Size;
	DWORD Shape;
	DWORD DecalNameHash;

	int DecalSlot1 = CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX0;
	int DecalSlot8 = CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX7;

	for (int i = CAR_SLOT_ID::__DECAL_MODEL_FIRST; i <= __DECAL_MODEL_LAST; i++)
	{
		Part = RideInfo_GetPart(RideInfo, i); // Decal dummy part
		if (Part)
		{
			Size = CarPart_GetAppliedAttributeUParam(Part, 0x001CAD5A, 0); // SIZE
			Shape = CarPart_GetAppliedAttributeUParam(Part, 0x03B16390, 0); // SHAPE

			if (Shape && Size)
			{
				for (int j = DecalSlot1; j <= DecalSlot8; j++)
				{
					Part = RideInfo_GetPart(RideInfo, j); // Decal texture part
					if (Part)
					{
						DecalNameHash = CarPart_GetAppliedAttributeUParam(Part, 0x0019CBC0, 0); // NAME

						if (DecalNameHash)
						{
							switch (Shape)
							{
							case 0x7A8B6BD0: // SQUARE
								DecalNameHash = bStringHash2((char*)"_SQUARE", DecalNameHash);
								break;
							case 0x001C0D0D: // RECT
								DecalNameHash = bStringHash2((char*)"_RECT", DecalNameHash);
								break;
							case 0x001EDC08: // WIDE
								DecalNameHash = bStringHash2((char*)"_WIDE", DecalNameHash);
								break;
							}

							NumUsedCarTextures += UsedCarTextureAddToTable(info->TexturesToLoadPerm, NumUsedCarTextures, MaxPermTex, DecalNameHash);
						}
					}
				}
			}
		}

		DecalSlot1 += 8;
		DecalSlot8 += 8;
	}

	info->NumTexturesToLoadPerm = NumUsedCarTextures;
	info->NumTexturesToLoadTemp = NumTempUsedCarTextures;
}

/*
void __declspec(naked) UsedCarTextureInfoCodeCave()
{
	_asm
	{
		mov eax, [esp + 0x84] // RideInfo
		test eax, eax
		jz caveexit
		mov ecx, [eax + 0xB8] // Interior CarPart
		test ecx, ecx
		jz caveexit
		call CarPart_GetTextureNameHash
		test eax, eax
		jz caveexit

		mov edi, eax
		push ebp
		lea eax, [esp + 0x40]
		push 0x8B4E8C // %s_INTERIOR
		push eax
		call sprintf
		lea eax, [esp + 0x48]
		push eax
		call bStringHash
		push edi // Dest
		push eax // Src
		push ebx
		push esi
		call UsedCarTextureReplace

		push eax
		push NormalMapSuffix
		call bStringHash2

		add esp, 0x28
		mov edi, eax
		push ebp
		lea eax, [esp + 0x40]
		push 0x8B4E7C // %s_INTERIOR_N
		push eax
		call sprintf
		lea eax, [esp + 0x48]
		push eax
		call bStringHash
		push edi // Dest
		push eax // Src
		push ebx
		push esi
		call UsedCarTextureReplace

		add esp, 0x20

		caveexit:
			push 0x75232F
			retn
	}
}

void __declspec(naked) TextureReplacementCodeCave()
{
	_asm pushad;

	int* CarRenderInfo;
	int* RideInfo;
	int partPtr, origTexHash, texHash;

	_asm mov dword ptr CarRenderInfo, esi;

	RideInfo = (int*)(*(CarRenderInfo + 0x21)); // RideInfo

	partPtr = *(RideInfo + 18 + 28); // INTERIOR
	if (partPtr)
	{
		texHash = CarPart_GetAppliedAttributeIParam((void*)partPtr, bStringHash((char*)"TEXTURE_NAME"), 0);
		InteriorTextureHash = texHash;
		if (texHash)
		{
			sprintf(TextureName, "%s_INTERIOR", GetCarTypeName(RideInfo[0]));
			origTexHash = bStringHash(TextureName); //CARNAME_INTERIOR
			// Texture Replacement Table = esi + 0x23C (8F)
			*(CarRenderInfo + 0xB3) = origTexHash;
			*(CarRenderInfo + 0xB4) = texHash;
			*(CarRenderInfo + 0xB5) = -1;
			// normal map
			InteriorNormalTextureHash = bStringHash2((char*)"_N", texHash);
			*(CarRenderInfo + 0xCE) = bStringHash2((char*)"_N", origTexHash);
			*(CarRenderInfo + 0xCF) = InteriorNormalTextureHash;
			*(CarRenderInfo + 0xD0) = -1;
		}
	}

	partPtr = *(RideInfo + 18 + 69); // LICENSE_PLATE
	if (partPtr)
	{
		texHash = CarPart_GetAppliedAttributeIParam((void*)partPtr, bStringHash((char*)"TEXTURE_NAME"), 0);
		if (texHash)
		{
			// Texture Replacement Table = esi + 0x23C (8F)
			*(CarRenderInfo + 0x9E) = 0x4C95C6F8; //LICENSEPLATE
			*(CarRenderInfo + 0x9F) = texHash;
			*(CarRenderInfo + 0xA0) = -1;
		}
	}

	partPtr = *(RideInfo + 18 + 64); // TIRE_TEXTURE
	if (partPtr)
	{
		texHash = CarPart_GetAppliedAttributeIParam((void*)partPtr, bStringHash((char*)"TEXTURE_NAME"), 0);
		if (texHash)
		{
			// Texture Replacement Table = esi + 0x23C (8F)
			*(CarRenderInfo + 0xCE) = 0xE4CEA024; // TIRE_STYLE01
			*(CarRenderInfo + 0xCF) = texHash;
			*(CarRenderInfo + 0xD0) = -1;
		}
	}

	_asm popad;
	_asm ret;
}*/

int SlotsToLookForKitWheelModifications[12]
{
	CAR_SLOT_ID::DAMAGE_BODY,
	CAR_SLOT_ID::BODY,
	CAR_SLOT_ID::ATTACHMENT0,
	CAR_SLOT_ID::ATTACHMENT1,
	CAR_SLOT_ID::ATTACHMENT2,
	CAR_SLOT_ID::ATTACHMENT3,
	CAR_SLOT_ID::ATTACHMENT4,
	CAR_SLOT_ID::ATTACHMENT5,
	CAR_SLOT_ID::ATTACHMENT6,
	CAR_SLOT_ID::ATTACHMENT7,
	CAR_SLOT_ID::ATTACHMENT8,
	CAR_SLOT_ID::ATTACHMENT9
};

int __fastcall CarRenderInfo_GetKitNumber(DWORD* CarRenderInfo, void* EDX_Unused)
{
	int KitNumber = 0;

	DWORD* TheRideInfo = (DWORD*)CarRenderInfo[33];

	if (TheRideInfo)
	{
		DWORD* Part = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BODY); // BODY
		if (Part)
		{
			KitNumber = CarPart_GetAppliedAttributeIParam(Part, bStringHash((char*)"KITNUMBER"), 0);
		}
	}

	return KitNumber;
}

bVector4 __fastcall CarRenderInfo_GetTireOffset(DWORD* CarRenderInfo, void* EDX_Unused, int WheelID)
{
	bVector4 TireOffsets;

	if (CarRenderInfo[34]) // CarTypeInfo
	{
		Attrib_Gen_ecar_LayoutStruct* eCarAttributes = (Attrib_Gen_ecar_LayoutStruct*)CarRenderInfo[1517];
		int KitNumber = CarRenderInfo_GetKitNumber(CarRenderInfo, 0);
		bool IsRearWheel = WheelID > 1;

		TireOffsets = (WheelID < Attrib_Private_GetLength(&eCarAttributes->_Array_TireOffsets))
			? eCarAttributes->TireOffsets[WheelID]
			: (bVector4)Attrib_DefaultDataArea(); // Get TireOffset

		int OffsetInMM = IsRearWheel ? *(int*)_TweakKitWheelOffsetRear : *(int*)_TweakKitWheelOffsetFront; // Get KitWheelOffsetFront/Rear
		if (!OffsetInMM)
		{
			if (KitNumber < Attrib_Private_GetLength(IsRearWheel
				? &eCarAttributes->_Array_KitWheelOffsetRear
				: &eCarAttributes->_Array_KitWheelOffsetFront))
				OffsetInMM = IsRearWheel
				? eCarAttributes->KitWheelOffsetRear[KitNumber]
				: eCarAttributes->KitWheelOffsetFront[KitNumber];
			else OffsetInMM = *(BYTE*)Attrib_DefaultDataArea();
		}

		float KitWheelOffset = (float)OffsetInMM * 0.001f; // mm -> meters

		DWORD* TheRideInfo = (DWORD*)CarRenderInfo[33];

		if (TheRideInfo) // Add Up CarPart Attribute offsets
		{
			for (int i = 0; i < 12; i++) // size of SlotsToLookForKitWheelModifications
			{
				DWORD* Part = RideInfo_GetPart(TheRideInfo, SlotsToLookForKitWheelModifications[i]);
				if (Part)
				{
					KitWheelOffset += CarPart_GetAppliedAttributeFParam(Part, 0,
						IsRearWheel ? bStringHash((char*)"REAR_TIRE_OFFSET") : bStringHash((char*)"FRONT_TIRE_OFFSET"),
						0.0f);
				}
			}
		}

		if (TireOffsets.y < 0.0f) KitWheelOffset *= -1; // Invert sign if needed
		TireOffsets.y += KitWheelOffset;
	}

	return TireOffsets;
}

float __fastcall CarRenderInfo_GetTireWidth(DWORD* CarRenderInfo, void* EDX_Unused, int WheelID)
{
	float TireSkidWidth = *(float*)_WheelStandardWidth;

	if (CarRenderInfo[34]) // CarTypeInfo
	{
		Attrib_Gen_ecar_LayoutStruct* eCarAttributes = (Attrib_Gen_ecar_LayoutStruct*)CarRenderInfo[1517];
		int KitNumber = CarRenderInfo_GetKitNumber(CarRenderInfo, 0);
		bool IsRearWheel = WheelID > 1;

		TireSkidWidth = (WheelID < Attrib_Private_GetLength(&eCarAttributes->_Array_TireSkidWidth))
			? eCarAttributes->TireSkidWidth[WheelID]
			: *(float*)Attrib_DefaultDataArea(); // Get TireSkidWidth

		DWORD* TheRideInfo = (DWORD*)CarRenderInfo[33];

		if (TheRideInfo) // Get CarPart Attribute Tire Width
		{
			DWORD* Part = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BODY); // BODY
			if (Part)
			{
				TireSkidWidth = CarPart_GetAppliedAttributeFParam(Part, 0,
					IsRearWheel ? bStringHash((char*)"REAR_TIRE_WIDTH") : bStringHash((char*)"FRONT_TIRE_WIDTH"),
					TireSkidWidth);
			}
		}

		bVector2 TireSkidWidthScaleVector = (KitNumber < Attrib_Private_GetLength(&eCarAttributes->_Array_TireSkidWidthKitScale))
			? eCarAttributes->TireSkidWidthKitScale[KitNumber]
			: eCarAttributes->TireSkidWidthKitScale[0];
		float TireSkidWidthKitScale = IsRearWheel ? TireSkidWidthScaleVector.y : TireSkidWidthScaleVector.x; // Get TireSkidWidthScale

		TireSkidWidth *= TireSkidWidthKitScale; // Write wheel width
	}

	return TireSkidWidth;
}

float __fastcall CarRenderInfo_GetTireRadius(DWORD* CarRenderInfo, void* EDX_Unused, int WheelID)
{
	float TireRadius = *(float*)_WheelStandardRadius;

	if (CarRenderInfo[34]) // CarTypeInfo
	{
		Attrib_Gen_ecar_LayoutStruct* eCarAttributes = (Attrib_Gen_ecar_LayoutStruct*)CarRenderInfo[1517];
		int KitNumber = CarRenderInfo_GetKitNumber(CarRenderInfo, 0);
		bool IsRearWheel = WheelID > 1;

		bVector4 TireOffsets = (WheelID < Attrib_Private_GetLength(&eCarAttributes->_Array_TireOffsets))
			? eCarAttributes->TireOffsets[WheelID]
			: (bVector4)Attrib_DefaultDataArea(); // Get TireOffset

		TireRadius = TireOffsets.w;

		DWORD* TheRideInfo = (DWORD*)CarRenderInfo[33];

		if (TheRideInfo) // Get CarPart Attribute Tire Width
		{
			DWORD* Part = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BODY); // BODY
			if (Part)
			{
				TireRadius = CarPart_GetAppliedAttributeFParam(Part, 0,
					IsRearWheel ? bStringHash((char*)"REAR_TIRE_RADIUS") : bStringHash((char*)"FRONT_TIRE_RADIUS"),
					TireRadius);
			}
		}
	}

	return TireRadius;
}

float __fastcall CarRenderInfo_GetTireRadiusScale(DWORD* CarRenderInfo, void* EDX_Unused, int WheelID)
{
	float TireRadius = *(float*)_WheelStandardRadius;
	float TireRadiusFromAttr = *(float*)_WheelStandardRadius;
	float TireRadiusScale = 1.0f;

	if (CarRenderInfo[34]) // CarTypeInfo
	{
		Attrib_Gen_ecar_LayoutStruct* eCarAttributes = (Attrib_Gen_ecar_LayoutStruct*)CarRenderInfo[1517];
		int KitNumber = CarRenderInfo_GetKitNumber(CarRenderInfo, 0);
		bool IsRearWheel = WheelID > 1;

		bVector4 TireOffsets = (WheelID < Attrib_Private_GetLength(&eCarAttributes->_Array_TireOffsets))
			? eCarAttributes->TireOffsets[WheelID]
			: (bVector4)Attrib_DefaultDataArea(); // Get TireOffset

		TireRadius = TireOffsets.w;

		DWORD* TheRideInfo = (DWORD*)CarRenderInfo[33];

		if (TheRideInfo) // Get CarPart Attribute Tire Width
		{
			DWORD* Part = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BODY); // BODY
			if (Part)
			{
				TireRadiusFromAttr = CarPart_GetAppliedAttributeFParam(Part, 0,
					IsRearWheel ? bStringHash((char*)"REAR_TIRE_RADIUS") : bStringHash((char*)"FRONT_TIRE_RADIUS"),
					TireRadius);
			}
		}

		TireRadiusScale = TireRadiusFromAttr / TireRadius;
	}

	return TireRadiusScale;
}

void __fastcall CarRenderInfo_UpdateWheelYRenderOffset(DWORD* CarRenderInfo, void* EDX_Unused)
{
	// ROADMAP
	// Get wheel offset from vlt. If KITNUMBER > 5, use value from KIT0. + Add up the values from attributes
	// Get wheel width from vlt (TireSkidWidth) or use the one from KIT instead.

	float* WheelYRenderOffset = (float*)(CarRenderInfo + 68);
	float* WheelWidth = (float*)(CarRenderInfo + 72);
	float* WheelRadius = (float*)(CarRenderInfo + 74);
	float* WheelWidthScale = (float*)(CarRenderInfo + 76);
	float* WheelRadiusScale = (float*)(CarRenderInfo + 80);
	float* WheelBrakeMarkerY = (float*)(CarRenderInfo + 84);

	if (CarRenderInfo[34])
	{
		for (int WheelID = 0; WheelID < 4; WheelID++)
		{
			bool IsRearWheel = WheelID > 1;

			bVector4 TireOffsets = CarRenderInfo_GetTireOffset(CarRenderInfo, 0, WheelID); // Get tire offsets
			WheelYRenderOffset[WheelID] = -TireOffsets.y; // Write wheel offset

			float TireSkidWidth = CarRenderInfo_GetTireWidth(CarRenderInfo, 0, WheelID); // Get tire width
			float TireRadius = CarRenderInfo_GetTireRadius(CarRenderInfo, 0, WheelID); // Get tire radius

			//WheelRadius[IsRearWheel] = TireRadius; // Write wheel radius

			// Write width and radius scales
			WheelWidthScale[WheelID] = (WheelWidth[IsRearWheel] <= 0.0f || TireSkidWidth <= 0.0f)
				? 1.0f
				: TireSkidWidth / WheelWidth[IsRearWheel];
			WheelRadiusScale[WheelID] = (WheelRadius[IsRearWheel] <= 0.0f || TireRadius <= 0.0f)
				? 1.0f
				: TireRadius / WheelRadius[IsRearWheel];
		}
	}
	else
	{
		WheelYRenderOffset[0] = 0;
		WheelYRenderOffset[1] = 0;
		WheelYRenderOffset[2] = 0;
		WheelYRenderOffset[3] = 0;
	}
	
	// Fix and apply brake position markers
	int TireLOD = CarRenderInfo[1418];
	DWORD* FrontWheeleModel = (DWORD*)(CarRenderInfo[TireLOD + 1067] & 0xFFFFFFFC); // eModel
	DWORD* RearWheeleModel = (DWORD*)(CarRenderInfo[TireLOD + 1072] & 0xFFFFFFFC); // eModel
	ePositionMarker* FrontBrakePositionMarker = 0, * RearBrakePositionMarker = 0;

	if (FrontWheeleModel) FrontBrakePositionMarker = eModel_GetPositionMarker(FrontWheeleModel, bStringHash((char*)"FRONT_BRAKE"));
	if (RearWheeleModel) RearBrakePositionMarker = eModel_GetPositionMarker(RearWheeleModel, bStringHash((char*)"REAR_BRAKE"));

	if (FrontBrakePositionMarker) WheelBrakeMarkerY[0] = FrontBrakePositionMarker->Matrix.v3.y; // Y Position
	else WheelBrakeMarkerY[0] = 0;

	if (RearBrakePositionMarker) WheelBrakeMarkerY[1] = RearBrakePositionMarker->Matrix.v3.y; // Y Position
	else // If there is no REAR_BRAKE markers attached to the rear rim, use FRONT_BRAKE marker instead
	{
		if (RearWheeleModel)
		{
			RearBrakePositionMarker = eModel_GetPositionMarker(RearWheeleModel, bStringHash((char*)"FRONT_BRAKE"));
			if (RearBrakePositionMarker) WheelBrakeMarkerY[1] = RearBrakePositionMarker->Matrix.v3.y;
			else WheelBrakeMarkerY[1] = 0;
		}
		else WheelBrakeMarkerY[1] = 0;
	}
}

Color __fastcall CarRenderInfo_GetColor(DWORD* CarRenderInfo, void* EDX_Unused, int CarSlotID, int ColorID, Color original, int AlphaType)
{
	Color color = 0;

	DWORD* TheRideInfo = (DWORD*)CarRenderInfo[33];

	if (TheRideInfo)
	{
		DWORD* Part = RideInfo_GetPart(TheRideInfo, CarSlotID); // BODY
		if (Part)
		{
			color.r = CarPart_GetAppliedAttributeIParam(Part, ColorHashes[ColorID][0], original.r) % 256;
			color.g = CarPart_GetAppliedAttributeIParam(Part, ColorHashes[ColorID][1], original.g) % 256;
			color.b = CarPart_GetAppliedAttributeIParam(Part, ColorHashes[ColorID][2], original.b) % 256;
			if (AlphaType) color.a = CarPart_GetAppliedAttributeIParam(Part, ColorHashes[ColorID][3], original.a) % (64 * AlphaType % 5);
		}
	}

	return color;
}

// Neon Stuff

#define CRI_Loc_NeonDirection 47 // CarRenderInfo + 0xBC (Padding)
#define CRI_Loc_NeonBrightness 51 // CarRenderInfo + 0xCC (Padding)

float NeonBrightnessBackup = 0;
float NeonDirectionBackup = 0;
float NeonBrightnessMax = 1.0f;
float NeonBrightnessMin = 0.01f;

float CarDistMax = 2.0f;
float CarDistMult = 0.5f;
float CarDistBright = 0.0f;
float CarShadBright = 110.0f;
float FrontShadowSize = 1.2f;
float RearShadowSize = 1.2f;
float LeftShadowSize = 1.05f;
float RightShadowSize = 1.05f;

float ShadowSunMultiplier = 0.5f;

void AddRenderInfo(DWORD* _CarRenderInfo)
{
	float* _CRIf = (float*)_CarRenderInfo;

	if (*(int*)_TheGameFlowManager == 3 && NeonBrightnessBackup)
	{
		_CRIf[CRI_Loc_NeonBrightness] = NeonBrightnessBackup; // NeonBrightness
		_CRIf[CRI_Loc_NeonDirection] = NeonDirectionBackup; // NeonDirection
	}
	else
	{
		_CRIf[CRI_Loc_NeonBrightness] = (bRandom(101) % 100 + 30) / 100.0f; // NeonBrightness
		_CRIf[CRI_Loc_NeonDirection] = 1.0f; // NeonDirection
	}
}

DWORD GetNeonTextureHash(DWORD* _RideInfo)
{
	DWORD* NeonPart = RideInfo_GetPart(_RideInfo, 65); // BRAKELIGHT
	if (NeonPart)
	{
		if (!CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash((char*)"STOCK"), 0)) // If not stock
			return CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash((char*)"TEXTURE_NAME"), bStringHash((char*)"CARSHADOW_NEON")); // Custom texture or CARSHADOW_NEON
	}

	return 0;
}

DWORD GetShadowCutTextureHash(DWORD* _RideInfo)
{
	DWORD DefaultShadowCutTextureHash = bStringHash((char*)"CARSHADOW_NEON_CUT");
	
	DWORD NeonTextureHash = GetNeonTextureHash(_RideInfo);
	if (NeonTextureHash)
	{
		DWORD ShadowCutTextureHash = bStringHash2((char*)"_CUT", NeonTextureHash);
		if (GetTextureInfo(ShadowCutTextureHash, 0, 0)) return ShadowCutTextureHash;
		else if (GetTextureInfo(DefaultShadowCutTextureHash, 0, 0)) return DefaultShadowCutTextureHash;
	}

	return 0;
}

void SetShadowSize(DWORD* _RideInfo, bool IsNeon)
{
	//DWORD* BodyKitCarPart = RideInfo_GetPart(_RideInfo, CAR_SLOT_ID::BODY); // BODY_KIT

	if (IsNeon)
	{
		ShadowSunMultiplier = 0.0f;
		FrontShadowSize = 1.2f;
		RearShadowSize = 1.2f;
		LeftShadowSize = 1.2f;
		RightShadowSize = 1.2f;
	}
	else
	{
		ShadowSunMultiplier = 0.5f;
		FrontShadowSize = 1.05f;
		RearShadowSize = 1.05f;
		LeftShadowSize = 1.05f;
		RightShadowSize = 1.05f;
	}
}

int __stdcall SetNeonColor(DWORD* _CarRenderInfo, int OriginalColor)
{
	float* _CRIf = (float*)_CarRenderInfo;

	DWORD* NeonTextureInfo = GetTextureInfo(GetNeonTextureHash((DWORD*)_CarRenderInfo[33]), 0, 0);
	if ((DWORD)NeonTextureInfo != _CarRenderInfo[52])
	{
		return OriginalColor;
	}

	DWORD* NeonPart = RideInfo_GetPart((DWORD*)_CarRenderInfo[33], 65); // BRAKELIGHT

	int r = 0, g = 0, b = 0, a = 0, r2 = 0, g2 = 0, b2 = 0, a2 = 0, rDif = 0, gDif = 0, bDif = 0, aDif = 0;
	float br = 1.0f;
	if (NeonPart)
	{
		if (!CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash((char*)"STOCK"), 0)) // If not stock
		{
			r = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash((char*)"RED"), 0) % 256;
			g = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash((char*)"GREEN"), 0) % 256;
			b = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash((char*)"BLUE"), 0) % 256;
			a = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash((char*)"ALPHA"), 0) % 256;
			r2 = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash((char*)"RED2"), r) % 256;
			g2 = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash((char*)"GREEN2"), g) % 256;
			b2 = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash((char*)"BLUE2"), b) % 256;
			a2 = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash((char*)"ALPHA2"), a) % 256;

			// Multiply alphas for shadow
			a *= 4;
			if (a > 255) a = 255;
			a2 *= 4;
			if (a2 > 255) a2 = 255;

			rDif = r2 - r;
			gDif = g2 - g;
			bDif = b2 - b;
			aDif = a2 - a;

			if ((rDif != 0) || (gDif != 0) || (bDif != 0) || (aDif != 0)) // Do pulse
			{
				if (!IsPaused())
				{
					_CRIf[CRI_Loc_NeonBrightness] += _CRIf[CRI_Loc_NeonDirection] * 1.7f * (*(float*)_RealTimeElapsedFrame);

					if (_CRIf[CRI_Loc_NeonBrightness] > NeonBrightnessMax)
					{
						_CRIf[CRI_Loc_NeonBrightness] = NeonBrightnessMax;
						_CRIf[CRI_Loc_NeonDirection] = -1.0f;
					}

					if (_CRIf[CRI_Loc_NeonBrightness] < NeonBrightnessMin)
					{
						_CRIf[CRI_Loc_NeonBrightness] = NeonBrightnessMin;
						_CRIf[CRI_Loc_NeonDirection] = 1.0f;
					}

					NeonBrightnessBackup = _CRIf[CRI_Loc_NeonBrightness];
					NeonDirectionBackup = _CRIf[CRI_Loc_NeonDirection];
				}

				br = _CRIf[CRI_Loc_NeonBrightness];
			}
		}
	}

	int c = (r + (int)(rDif * br))
		+ (g + (int)(gDif * br) << 8)
		+ (b + (int)(bDif * br) << 16)
		+ (a + (int)(aDif * br) << 24);

	int res = /*OriginalColor |*/ c;

	//SetMaterialColor(r * br, g * br, b * br, a);

	return res;
}

DWORD _NeonColorBackup;

void __declspec(naked) ShadowColorCave()
{
	_asm
	{
		shl eax, 0x18

		pushad
		push eax // original color
		push ebx // render info
		call SetNeonColor
		mov _NeonColorBackup, eax
		popad

		mov eax, _NeonColorBackup
		mov ecx, dword ptr ds: [ebx + 0xD0]
		test ecx, ecx
		push 0x7444A1
		retn
	}
}

double __fastcall CarRenderInfo_DrawAmbientShadow_Hook(DWORD* _CarRenderInfo, void* EDX_Unused, int eView, float* bV3, float flt, float* bM41, float* bM42, float* bM43)
{
	double ret = CarRenderInfo_DrawAmbientShadow_Game(_CarRenderInfo, eView, bV3, flt, bM41, bM42, bM43);

	DWORD NeonTextureHash = GetNeonTextureHash((DWORD*)_CarRenderInfo[33]); // CarRenderInfo->pRideInfo);
	if (NeonTextureHash)
	{
		SetShadowSize((DWORD*)_CarRenderInfo[33], 1);
		DWORD* NeonTextureInfo = GetTextureInfo(NeonTextureHash, 0, 0);
		DWORD* ShadowTextureInfo = (DWORD*)_CarRenderInfo[52]; // CarRenderInfo->mpShadowTexture
		_CarRenderInfo[52] = (DWORD)NeonTextureInfo;
		CarRenderInfo_DrawAmbientShadow_Game(_CarRenderInfo, eView, bV3, flt, bM41, bM42, bM43);
		_CarRenderInfo[52] = (DWORD)ShadowTextureInfo;
		SetShadowSize((DWORD*)_CarRenderInfo[33], 0);
	}

	return ret;
}

DWORD __stdcall GetShadowStyle(DWORD* _CarRenderInfo)
{
	AddRenderInfo(_CarRenderInfo);
	DWORD cutHash = GetShadowCutTextureHash((DWORD*)_CarRenderInfo[33]);
	return cutHash ? cutHash : bStringHash((char*)"CARSHADOW");
}

DWORD _ShadowStyleBackup;

// 0x75FC83
void __declspec(naked) CarShadowCave()
{
	__asm
	{
		pushad
		push esi
		call GetShadowStyle
		mov _ShadowStyleBackup, eax
		popad

		mov eax, _ShadowStyleBackup
		push 0x75FC88
		retn
	}
}

// Light Flare Color Stuff

//static injector::hook_back<void(*)(DWORD*, DWORD*, float*, float, int, int, float, DWORD, float)> hb_eRenderLightFlare;
static injector::hook_back<void(*)(DWORD*, eLightFlare*, bMatrix4*, float, int, int, float, Color, float)> hb_eRenderLightFlare;
DWORD* _CarRenderInfo_Backup = 0;

// Hook to apply custom flare colors
void eRenderLightFlare_Hook(DWORD* view, eLightFlare* light_flare, bMatrix4* local_world, float intensity_scale, int a5, int a6, float a7, Color ColourOverRide, float sizescale)
{
	DWORD* CarRenderInfo = _CarRenderInfo_Backup;

	if (light_flare)
	{
		switch (light_flare->NameHash) // eLightFlare->NameHash
		{
		case 0xD09091C6: // RIGHT_HEADLIGHT
			if (CarRenderInfo)
			{
				DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
				if (RideInfo)
				{
					DWORD* RHeadlightPart = RideInfo_GetPart(RideInfo, 40); // RIGHT_HEADLIGHT
					if (RHeadlightPart)
					{
						int r = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash((char*)"RED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash((char*)"GREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash((char*)"BLUE"), 0) % 256;

						// If no color attribute is present, use the values from LEFT_HEADLIGHT instead
						if (r == 0 && g == 0 && b == 0)
						{
							DWORD* HeadlightPart = RideInfo_GetPart(RideInfo, 31); // LEFT_HEADLIGHT
							if (HeadlightPart)
							{
								r = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"RED"), 0) % 256;
								g = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"GREEN"), 0) % 256;
								b = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"BLUE"), 0) % 256;
							}
						}

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare->ColourTint = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare->ColourTint;
					}
				}
			}
			break;

		case 0x7A5BCF69: // CENTRE_HEADLIGHT
			if (CarRenderInfo)
			{
				DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
				if (RideInfo)
				{
					DWORD* HeadlightPart = RideInfo_GetPart(RideInfo, 31); // LEFT_HEADLIGHT
					if (HeadlightPart)
					{
						int r = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"DISPRED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"DISPGREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"DISPBLUE"), 0) % 256;

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare->ColourTint = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare->ColourTint;
					}
				}
			}
			break;

		case 0x9DB90133: // LEFT_HEADLIGHT
			if (CarRenderInfo)
			{
				DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
				if (RideInfo)
				{
					DWORD* HeadlightPart = RideInfo_GetPart(RideInfo, 31); // LEFT_HEADLIGHT
					if (HeadlightPart)
					{
						int r = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"RED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"GREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"BLUE"), 0) % 256;

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare->ColourTint = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare->ColourTint;
					}
				}
			}
			break;

		case 0xBF700A79: // RIGHT_BRAKELIGHT
			if (CarRenderInfo)
			{
				DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
				if (RideInfo)
				{
					DWORD* RBrakelightPart = RideInfo_GetPart(RideInfo, 38); // RIGHT_BRAKELIGHT
					if (RBrakelightPart)
					{
						int r = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash((char*)"RED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash((char*)"GREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash((char*)"BLUE"), 0) % 256;

						// If no color attribute is present, use the values from LEFT_BRAKELIGHT instead
						if (r == 0 && g == 0 && b == 0)
						{
							DWORD* BrakelightPart = RideInfo_GetPart(RideInfo, 29); // LEFT_BRAKELIGHT
							if (BrakelightPart)
							{
								r = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"RED"), 0) % 256;
								g = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"GREEN"), 0) % 256;
								b = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"BLUE"), 0) % 256;
							}
						}

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare->ColourTint = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare->ColourTint;
					}
				}
			}
			break;

		case 0xA2A2FC7C: // CENTRE_BRAKELIGHT
			if (CarRenderInfo)
			{
				DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
				if (RideInfo)
				{
					DWORD* BrakelightPart = RideInfo_GetPart(RideInfo, 29); // LEFT_BRAKELIGHT
					if (BrakelightPart)
					{
						int r = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"DISPRED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"DISPGREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"DISPBLUE"), 0) % 256;

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare->ColourTint = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare->ColourTint;
					}
				}
			}
			break;

		case 0x31A66786: // LEFT_BRAKELIGHT
			if (CarRenderInfo)
			{
				DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
				if (RideInfo)
				{
					DWORD* BrakelightPart = RideInfo_GetPart(RideInfo, 29); // LEFT_BRAKELIGHT
					if (BrakelightPart)
					{
						int r = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"RED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"GREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"BLUE"), 0) % 256;

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare->ColourTint = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare->ColourTint;
					}
				}
			}
			break;

		case 0x7ADF7EF8: // RIGHT_REVERSE
			if (CarRenderInfo)
			{
				DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
				if (RideInfo)
				{
					DWORD* RBrakelightPart = RideInfo_GetPart(RideInfo, 38); // RIGHT_BRAKELIGHT
					if (RBrakelightPart)
					{
						int r = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash((char*)"RED2"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash((char*)"GREEN2"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash((char*)"BLUE2"), 0) % 256;

						// If no color attribute is present, use the values from LEFT_BRAKELIGHT instead
						if (r == 0 && g == 0 && b == 0)
						{
							DWORD* BrakelightPart = RideInfo_GetPart(RideInfo, 29); // LEFT_BRAKELIGHT
							if (BrakelightPart)
							{
								r = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"RED2"), 0) % 256;
								g = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"GREEN2"), 0) % 256;
								b = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"BLUE2"), 0) % 256;
							}
						}

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare->ColourTint = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare->ColourTint;
					}
				}
			}
			break;

		case 0x7A5B2F25: // LEFT_REVERSE
			if (CarRenderInfo)
			{
				DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
				if (RideInfo)
				{
					DWORD* BrakelightPart = RideInfo_GetPart(RideInfo, 29); // LEFT_BRAKELIGHT
					if (BrakelightPart)
					{
						int r = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"RED2"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"GREEN2"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash((char*)"BLUE2"), 0) % 256;

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare->ColourTint = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare->ColourTint;
					}
				}
			}
			break;
		}
	}

	// Call the original function
	hb_eRenderLightFlare.fun(view, light_flare, local_world, intensity_scale, a5, a6, a7, ColourOverRide, sizescale);
}

DWORD hcLC = 0x40CCCCCC;
DWORD hcLF = 0x40CCCCCC;
DWORD hcRC = 0x40CCCCCC;
DWORD hcRF = 0x40CCCCCC;

// 0x738241
void __declspec(naked) RenderTextureHeadlightsColorCave()
{
	_asm
	{
		mov ecx, [hcRC] // right close
		mov dword ptr ds : [esp + 0x9C] , ecx
		fstp dword ptr ds : [esp + 0x20]
		mov ecx, [hcRF] // right far
		mov dword ptr ds : [esp + 0xA0] , ecx
		fld dword ptr ds : [0x9034FC]
		mov ecx, [hcLF] // left far
		mov dword ptr ds : [esp + 0xA4] , ecx
		fadd dword ptr ds : [0x9034E4]
		mov ecx, [hcLC] // left close
		mov dword ptr ds : [esp + 0xA8] , ecx

		push 0x73826D
		retn
	}
}

void __fastcall CarRenderInfo_RenderTextureHeadlights_Hook(DWORD* CarRenderInfo, void* EDX_Unused, DWORD* view, float* l_w, unsigned int Accurate)
{
	if (CarRenderInfo)
	{
		DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
		if (RideInfo)
		{
			
			DWORD* RHeadlightPart = RideInfo_GetPart(RideInfo, 40); // RIGHT_HEADLIGHT
			if (RHeadlightPart)
			{
				int r = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash((char*)"RED"), 0) % 256;
				int g = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash((char*)"GREEN"), 0) % 256;
				int b = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash((char*)"BLUE"), 0) % 256;

				// If no color attribute is present, use the values from LEFT_HEADLIGHT instead
				if (r == 0 && g == 0 && b == 0)
				{
					DWORD* HeadlightPart = RideInfo_GetPart(RideInfo, 31); // LEFT_HEADLIGHT
					if (HeadlightPart)
					{
						r = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"RED"), 0) % 256;
						g = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"GREEN"), 0) % 256;
						b = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"BLUE"), 0) % 256;
					}
				}

				if (r == 0 && g == 0 && b == 0) hcRC = 0x40CCCCCC;
				else hcRC = r + (g << 8) + (b << 16) + (0x40 << 24);
			}
			else hcRC = 0x40CCCCCC;

			DWORD* HeadlightPart = RideInfo_GetPart(RideInfo, 31); // LEFT_HEADLIGHT
			if (HeadlightPart)
			{
				int r = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"RED"), 0) % 256;
				int g = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"GREEN"), 0) % 256;
				int b = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"BLUE"), 0) % 256;

				if (r == 0 && g == 0 && b == 0) hcLC = 0x40CCCCCC;
				else hcLC = r + (g << 8) + (b << 16) + (0x40 << 24);
				
			}
			else hcLC = 0x40CCCCCC;

			hcRF = hcRC;
			hcLF = hcLC;
		}
	}

	CarRenderInfo_RenderTextureHeadlights(CarRenderInfo, view, l_w, Accurate);

	hcLC = 0x40CCCCCC;
	hcLF = 0x40CCCCCC;
	hcRF = 0x40CCCCCC;
	hcRC = 0x40CCCCCC;
}

// 0x743235
void __declspec(naked) RenderLightFlareCodeCave()
{
	_asm
	{
		mov edi, dword ptr ds: [esp + 0x60] // CarRenderInfo
		mov _CarRenderInfo_Backup, edi 
		call eRenderLightFlare_Hook

		push 0x74323A
		retn
	}
}

float signalflicker(float time, float rate)
{
	return (fmod(time, rate) > (rate / 2.0f)) ? 1.0f : 0.0f;
}

int signalsequence(float time, float rate, int num)
{
	return floor(fmod(time, rate) / (rate / (num + 1)));
}

void __fastcall CarRenderInfo_CreateCarLightFlares(DWORD* CarRenderInfo, void* EDX_Unused)
{
	DWORD* Solid;
	ePositionMarker* Marker;
	eLightFlare* Flare;
	int FlareType = 0;

	if (CarRenderInfo[34]) // CarTypeInfo
	{
		for (int CarSlotID = 75; CarSlotID >= 0; CarSlotID--)
		{
			Marker = 0;
			Solid = (DWORD*)(CarRenderInfo[737 + CarRenderInfo[1418] + CarSlotID * 5] & 0xFFFFFFFC);

			if (Solid)
			{
				while (1)
				{
					Marker = eSolid_GetPositionMarker(Solid, Marker);
					if (!Marker) break;

					Flare = (eLightFlare*)FastMem_Alloc((DWORD*)_gFastMem, 0x30, 0);
					if (!Flare) break;

					switch (Marker->NameHash)
					{
					case 0x7A5BCF69: // CENTRE_HEADLIGHT
						FlareType = 0; // ELF_CAR_HEADLIGHT
						Flare->ColourTint = CarRenderInfo_GetColor(CarRenderInfo, 0, 31, 2, 0, 0);
						if (!Flare->ColourTint) goto _LeftHeadlight;
						break;
					case 0xD09091C6: // RIGHT_HEADLIGHT
						FlareType = 0; // ELF_CAR_HEADLIGHT
						Flare->ColourTint = CarRenderInfo_GetColor(CarRenderInfo, 0, 40, 0, 0, 0);
						if (!Flare->ColourTint) goto _LeftHeadlight;
						break;
					case 0x9DB90133: // LEFT_HEADLIGHT
						FlareType = 0; // ELF_CAR_HEADLIGHT
					_LeftHeadlight:
						Flare->ColourTint = CarRenderInfo_GetColor(CarRenderInfo, 0, 31, 0, 0, 0);
						break;


					case 0xA2A2FC7C: // CENTRE_BRAKELIGHT
						FlareType = 1; // ELF_CAR_BRAKELIGHT
						Flare->ColourTint = CarRenderInfo_GetColor(CarRenderInfo, 0, 29, 2, 0, 0);
						if (!Flare->ColourTint) goto _LeftBrakelight;
						break;
					case 0xBF700A79: // RIGHT_BRAKELIGHT
						FlareType = 1; // ELF_CAR_BRAKELIGHT
						Flare->ColourTint = CarRenderInfo_GetColor(CarRenderInfo, 0, 38, 0, 0, 0);
						if (!Flare->ColourTint) goto _LeftBrakelight;
						break;
					case 0x31A66786: // LEFT_BRAKELIGHT
						FlareType = 1; // ELF_CAR_BRAKELIGHT
					_LeftBrakelight:
						Flare->ColourTint = CarRenderInfo_GetColor(CarRenderInfo, 0, 29, 0, 0, 0);
						break;


					case 0x7ADF7EF8: // RIGHT_REVERSE
						FlareType = 3; // ELF_CAR_REVERSELIGHT
						Flare->ColourTint = CarRenderInfo_GetColor(CarRenderInfo, 0, 38, 1, 0, 0);
						if (!Flare->ColourTint) goto _LeftReverse;
						break;
					case 0x7A5B2F25: // LEFT_REVERSE
						FlareType = 3; // ELF_CAR_REVERSELIGHT
					_LeftReverse:
						Flare->ColourTint = CarRenderInfo_GetColor(CarRenderInfo, 0, 29, 1, 0, 0);
						break;


					case 0x1E4150B4: // COPLIGHTRED
						FlareType = 5; // ELF_CAR_COPLIGHTRED
						break;

					case 0xE662C161: // COPLIGHTBLUE
						FlareType = 6; // ELF_CAR_COPLIGHTBLUE
						break;

					case 0xB4348DBA: // COPLIGHTWHITE
						FlareType = 7; // ELF_CAR_COPLIGHTWHITE
						break;

					case 0x41489594: // COPLIGHTBRIGHTRED
						FlareType = 10; // ELF_CAR_COPLIGHTBRIGHTRED
						break;

					case 0x6A52A241: // COPLIGHTBRIGHTBLUE
						FlareType = 11; // ELF_CAR_COPLIGHTBRIGHTBLUE
						break;

					case 0x28CD78F5: // COPLIGHTORANGE
						FlareType = 12; // ELF_CAR_COPLIGHTORANGE
						break;


					case 0x2E68A46F: // FRONT_LEFT_SIGNAL
					case 0x513456E2: // FRONT_RIGHT_SIGNAL
					case 0x6045CE90: // REAR_LEFT_SIGNAL
					case 0xBEB6C523: // REAR_RIGHT_SIGNAL
						FlareType = 17; // ELF_BLINKING_AMBER
						break;
					}

					Flare->NameHash = Marker->NameHash;
					Flare->Type = FlareType;
					switch (FlareType)
					{
					case 5: // ELF_CAR_COPLIGHTRED
					case 6: // ELF_CAR_COPLIGHTBLUE
					case 7: // ELF_CAR_COPLIGHTWHITE
					case 10: // ELF_CAR_COPLIGHTBRIGHTRED
					case 11: // ELF_CAR_COPLIGHTBRIGHTBLUE
					case 12: // ELF_CAR_COPLIGHTORANGE
						Flare->Flags = 2; // n-Directional
						break;
					default:
						Flare->Flags = 4; // Uni-Directional
						break;
					}
					Flare->PositionX = Marker->Matrix.v3.x;
					Flare->PositionY = Marker->Matrix.v3.y;
					Flare->PositionZ = Marker->Matrix.v3.z;
					Flare->ReflectPosZ = 0;
					Flare->DirectionX = Marker->Matrix.v2.x;
					Flare->DirectionY = Marker->Matrix.v2.y;
					Flare->DirectionZ = Marker->Matrix.v2.z;

					//bTNode<eLightFlare>_AddAfter((bTNode<eLightFlare>*)CarRenderInfo[65], CarRenderInfo[66]);

					eLightFlare* Last = (eLightFlare*)CarRenderInfo[66];
					Flare->Next = Last->Next;
					Flare->Prev = Last;
					Last->Next = Flare;
					CarRenderInfo[66] = (DWORD)Flare;
					
					//Flare->Next = (eLightFlare*)(DWORD*)(CarRenderInfo + 65);
				}
			}
		}
	}
}

void __fastcall CarRenderInfo_RenderFlaresOnCar(DWORD* CarRenderInfo, void* EDX_Unused, DWORD* view, bVector3* position, bMatrix4* body_matrix, int force_light_state, int reflection, int renderFlareFlags)
{
	float time = *(float*)(CarRenderInfo + 67) + Sim_GetTime(); // this->CarTimebaseStart
	bMatrix4* LocalWorld = eFrameMallocMatrix(1);

	if (LocalWorld)
	{
		bCopy(LocalWorld, body_matrix);
		LocalWorld->v3.x = position->x;
		LocalWorld->v3.y = position->y;
		LocalWorld->v3.z = position->z;
		LocalWorld->v3.w = 1.0f;

		if (reflection) CarRenderInfo_RenderTextureHeadlights_Hook(CarRenderInfo, 0, view, (float*)LocalWorld, 0);

		DWORD* RideInfo = (DWORD*)CarRenderInfo[33]; // this->pRideInfo
		if (IsCop(RideInfo[0]) && (CarRenderInfo[1416] & 0x1000) != 0)// UsageType = Cop && mOnLights = Cop Lights
			++view[21];

		// Check for US parking lights
		bool USParkingLights = 0;
		DWORD* HeadlightPart = RideInfo_GetPart(RideInfo, CAR_SLOT_ID::LEFT_HEADLIGHT);
		if (HeadlightPart) USParkingLights = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash((char*)"US_PARKING_LIGHTS"), 0) != 0;

		int PixelSize = eView_GetPixelSize(view, position, *(float*)(CarRenderInfo + 1514)); // this->mRadius

		if (eGetCurrentViewMode() == 3) PixelSize = (int)(PixelSize * *(float*)flt_8B2EE8);

		if (PixelSize >= view[9] && eView_GetVisibleState(view, (bVector3*)(CarRenderInfo + 36), (bVector3*)(CarRenderInfo + 40), LocalWorld)) // this->AABBMin, this->AABBMax
		{
			// define default intensity values
			float IntsLeftHeadlight = 0.0f;
			float IntsRightHeadlight = 0.0f;
			float IntsCentreHeadlight = 0.0f;

			if (*(DWORD*)_UTL_Collections_Singleton_INIS_mInstance)
			{
				IntsLeftHeadlight = 0.0f;
				IntsRightHeadlight = 0.0f;
				IntsCentreHeadlight = 0.0f;
			}

			float IntsLeftBrakelight = 0.5f;
			float IntsRightBrakelight = 0.5f;
			float IntsCentreBrakelight = 0.0f;
			float IntsLeftReverse = 0.0f;
			float IntsRightReverse = 0.0f;
			float IntsCopRed = 0.0f;
			float IntsCopBlue = 0.0f;
			float IntsCopWhite = 0.0f;
			float IntsFrontLeftSignal = 0.0f;
			float IntsFrontRightSignal = 0.0f;
			float IntsRearLeftSignal = 0.0f;
			float IntsRearRightSignal = 0.0f;

			bool FlickerHeadlights = 0;

			if (*(bool*)_ForceHeadlightsOn) force_light_state |= 1;
			if (*(bool*)_ForceBrakelightsOn) force_light_state |= 2;
			if (*(bool*)_ForceReverselightsOn) force_light_state |= 4;

			if (force_light_state & 1) // FORCE_HEADLIGHTS_ON
			{
				IntsLeftHeadlight = 1.0f;
				IntsRightHeadlight = 1.0f;
				IntsCentreHeadlight = 1.0f;
			}
			else if (force_light_state & 8) // FORCE_HEADLIGHTS_OFF
			{
				IntsLeftHeadlight = 0.0f;
				IntsRightHeadlight = 0.0f;
				IntsCentreHeadlight = 0.0f;
			}

			if (force_light_state & 2) // FORCE_BRAKELIGHTS_ON
			{
				IntsLeftBrakelight = 1.5f;
				IntsRightBrakelight = 1.5f;
				IntsCentreBrakelight = 1.0f;
			}
			else if (force_light_state & 16) // FORCE_BRAKELIGHTS_OFF
			{
				IntsLeftBrakelight = 0.5f;
				IntsRightBrakelight = 0.5f;
				IntsCentreBrakelight = 0.0f;
			}

			if (force_light_state & 4) // FORCE_REVERSELIGHTS_ON
			{
				IntsLeftReverse = 1.0f;
				IntsRightReverse = 1.0f;
			}
			else if (force_light_state & 32) // FORCE_REVERSELIGHTS_OFF
			{
				IntsLeftReverse = 0.0f;
				IntsRightReverse = 0.0f;
			}

			// evaluate on and broken lights
			DWORD OnLights = CarRenderInfo[1416];
			if (ForceSignalsOn) OnLights += 0xF00;
			DWORD BrokenLights = CarRenderInfo[1417];

			// LIGHT_LHEAD
			if (OnLights & 1) IntsLeftHeadlight = 1.0f;
			if (BrokenLights & 1) IntsLeftHeadlight = 0.0f;

			// LIGHT_RHEAD
			if (OnLights & 2) IntsRightHeadlight = 1.0f;
			if (BrokenLights & 2) IntsRightHeadlight = 0.0f;

			// LIGHT_CHEAD
			if (OnLights & 4) IntsCentreHeadlight = 1.0f;
			if (BrokenLights & 4) IntsCentreHeadlight = 0.0f;

			// LIGHT_LBRAKE
			if (OnLights & 8) IntsLeftBrakelight += 16.0f;
			if (BrokenLights & 8) IntsLeftBrakelight = 0.0f;

			// LIGHT_RBRAKE
			if (OnLights & 16) IntsRightBrakelight += 16.0f;
			if (BrokenLights & 16) IntsRightBrakelight = 0.0f;

			// LIGHT_CBRAKE
			if (OnLights & 32) IntsCentreBrakelight = 16.5f;
			if (BrokenLights & 32) IntsCentreBrakelight = 0.0f;

			// LIGHT_LREVERSE
			if (OnLights & 64) IntsLeftReverse += 17.0f;
			if (BrokenLights & 64) IntsLeftReverse = 0.0f;

			// LIGHT_RREVERSE
			if (OnLights & 128) IntsRightReverse += 17.0f;
			if (BrokenLights & 128) IntsRightReverse = 0.0f;

			// LIGHT_LRSIGNAL
			if (OnLights & 256) IntsRearLeftSignal = 1.0f;
			if (BrokenLights & 256) IntsRearLeftSignal = 0.0f;

			// LIGHT_RRSIGNAL
			if (OnLights & 512) IntsRearRightSignal = 1.0f;
			if (BrokenLights & 512) IntsRearRightSignal = 0.0f;

			// LIGHT_LFSIGNAL
			if (OnLights & 1024) IntsFrontLeftSignal = 1.0f;
			if (BrokenLights & 1024) IntsFrontLeftSignal = 0.0f;

			// LIGHT_RFSIGNAL
			if (OnLights & 2048) IntsFrontRightSignal = 1.0f;
			if (BrokenLights & 2048) IntsFrontRightSignal = 0.0f;

			// LIGHT_COPRED
			if (OnLights & 4096) IntsCopRed = *(float*)_cpr;
			if (BrokenLights & 4096) IntsCopRed = 0.0f;

			// LIGHT_COPBLUE
			if (OnLights & 8192) IntsCopBlue = *(float*)_cpb;
			if (BrokenLights & 8192) IntsCopBlue = 0.0f;

			// LIGHT_COPWHITE
			if (OnLights & 16384)
			{
				IntsCopWhite = *(float*)_cpw;
				FlickerHeadlights = 1;
			}
			if (BrokenLights & 16384) IntsCopWhite = 0.0f;


			int flarecount = 0;
			float copflicker = coplightflicker(time, 0);
			float signalintensity = signalflicker(time, 0.7f);

			float IntensityScale = 0.0f;
			float Scale = 1.0f;

			// Render
			for (eLightFlare* Flare = (eLightFlare*)CarRenderInfo[65]; //this->LightFlareList
				(DWORD*)Flare != CarRenderInfo + 65;
				Flare = Flare->Next)
			{
				IntensityScale = 0.0f;
				Scale = 1.0f;
				if (IsTraffic(RideInfo[0]) && Flare->Type == 1) Flare->Type == 2; // ELF_CAR_TRAFFIC_BRAKELIGHT

				if ((!(renderFlareFlags & 2) || Flare->Type == 1)
					&& (!(renderFlareFlags & 1) || Flare->Type - 5 <= 7))
				{
					switch (Flare->NameHash)
					{
					case 0x9DB90133: // LEFT_HEADLIGHT
						IntensityScale = FlickerHeadlights ? copflicker * IntsLeftHeadlight : IntsLeftHeadlight;
						break;

					case 0xD09091C6: // RIGHT_HEADLIGHT
						IntensityScale = FlickerHeadlights ? (1.0f - copflicker) * IntsRightHeadlight : IntsRightHeadlight;
						break;

					case 0x7A5BCF69: // CENTRE_HEADLIGHT
						IntensityScale = IntsCentreHeadlight;
						break;

					case 0x31A66786: // LEFT_BRAKELIGHT
						IntensityScale = IntsLeftBrakelight;
						break;

					case 0xBF700A79: // RIGHT_BRAKELIGHT
						IntensityScale = IntsRightBrakelight;
						break;

					case 0xA2A2FC7C: // CENTRE_BRAKELIGHT
						IntensityScale = IntsCentreBrakelight;
						break;

					case 0x7A5B2F25: // LEFT_REVERSE
						IntensityScale = IntsLeftReverse;
						break;

					case 0x7ADF7EF8: // RIGHT_REVERSE
						IntensityScale = IntsRightReverse;
						break;

					case 0x2E68A46F: // FRONT_LEFT_SIGNAL
						IntensityScale = USParkingLights ? IntsLeftHeadlight : signalintensity * IntsFrontLeftSignal;
						break;

					case 0x6045CE90: // REAR_LEFT_SIGNAL
						IntensityScale = signalintensity * IntsRearLeftSignal;
						break;

					case 0x513456E2: // FRONT_RIGHT_SIGNAL
						IntensityScale = USParkingLights ? IntsRightHeadlight : signalintensity * IntsFrontRightSignal;
						break;

					case 0xBEB6C523: // REAR_RIGHT_SIGNAL
						IntensityScale = signalintensity * IntsRearRightSignal;
						break;

					case 0x1E4150B4: // COPLIGHTRED
					case 0x41489594: // COPLIGHTBRIGHTRED
						IntensityScale = coplightflicker2(time, 0, flarecount) * IntsCopRed;
						break;

					case 0xE662C161: // COPLIGHTBLUE
					case 0x6A52A241: // COPLIGHTBRIGHTBLUE
						IntensityScale = coplightflicker2(time, 1, flarecount) * IntsCopBlue;
						break;

					case 0xB4348DBA: // COPLIGHTWHITE
						IntensityScale = bSin(coplightflicker2(time, 2, flarecount) * IntsCopWhite * *(float*)_copWhitemul);
						break;

					case 0x28CD78F5: // COPLIGHTORANGE
						IntensityScale = 1.0f;
						break;
					}

					if (IntensityScale > 0.0f)
					{
						if (IntensityScale > 1.0f) IntensityScale = 1.0f;

						if (reflection)
						{
							hb_eRenderLightFlare.fun(view, Flare, LocalWorld, IntensityScale, 1, 2, *(float*)(CarRenderInfo + 1118), Flare->ColourTint, 1.0f); // this->mWorldHeightUnderCar
						}
						else
						{
							hb_eRenderLightFlare.fun(view, Flare, LocalWorld, IntensityScale, 0, renderFlareFlags & 1, 0.0f, Flare->ColourTint, Scale);
						}

						flarecount++;
					}
				}
			}

			// NIS Light stuff
			if (view[1] == 1 && !reflection)
			{
				float NISLightIntensity = 1.0f;
				bVector3 NISLightPos;
				NISLightPos.x = *(float*)_gTWEAKER_NISLightPosX + position->x;
				NISLightPos.y = *(float*)_gTWEAKER_NISLightPosY + position->y;
				NISLightPos.z = *(float*)_gTWEAKER_NISLightPosZ + position->z;

				if (*(bool*)_gTWEAKER_NISLightEnabled)
				{
					position = &NISLightPos;
					NISLightIntensity = *(float*)_gTWEAKER_NISLightIntensity;
				}
				if (IntsCopRed > 0.0f || IntsCopBlue > 0.0f)
				{
					if (IntsCopRed <= 0.0f)
					{
						if (IntsCopBlue > 0.0f)
						{
							IntensityScale = NISLightIntensity * IntsCopBlue;
							AddQuickDynamicLight((DWORD*)_ShaperLightsCharacters, *(int*)_Lightslot, 0.2f, 0.2f, 0.8f, IntensityScale, position);
						}
					}
					else
					{
						IntensityScale = NISLightIntensity * IntsCopRed;
						AddQuickDynamicLight((DWORD*)_ShaperLightsCharacters, *(int*)_Lightslot, 0.8f, 0.2f, 0.0f, IntensityScale, position);
					}
				}
				else
				{
					RestoreShaperRig((DWORD*)_ShaperLightsCharacters, *(int*)_Lightslot, (DWORD*)_ShaperLightsCharactersBackup);
				}
			}
		}
	}
}


// Camber stuff
float __stdcall GetCamber(DWORD* _CarRenderInfo, float original, bool isRear)
{
	float Camber = original;

	// Get value from custom attribute
	DWORD* TheRideInfo = (DWORD*)_CarRenderInfo[33]; // CarRenderInfo->pRideInfo
	if (TheRideInfo)
	{
		DWORD* BodyKitCarPart = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BODY); // BODY_KIT
		if (BodyKitCarPart)
		{
			// Read camber attributes from body kit
			Camber = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, isRear ? bStringHash((char*)"REAR_CAMBER") : bStringHash((char*)"FRONT_CAMBER"), original);
		}
	}

	return Camber;
}

// 0x0074EFCF
void __declspec(naked) CamberFrontCave()
{
	__asm
	{
		pushad

		push 0; // is rear
		mov edi, dword ptr ds: [edi + 0xF0]
		push edi // original
		push esi // render info
		call GetCamber

		popad
		push 0x74EFD5
		retn
	}
}

// 0x0074EFE8
void __declspec(naked) CamberRearCave()
{
	__asm
	{
		pushad

		push 1 // is rear
		mov edi, dword ptr ds : [edi + 0xF8]
		push edi // original
		push esi // render info
		call GetCamber

		popad
		push 0x74EFEE
		retn
	}
}

// Ride Height Stuff
float __stdcall GetRideHeight(DWORD* _CarRenderInfo, float original)
{
	float RideHeight = original;

	// Get value from custom attribute
	DWORD* TheRideInfo = (DWORD*)_CarRenderInfo[33]; // CarRenderInfo->pRideInfo
	if (TheRideInfo)
	{
		DWORD* BodyKitCarPart = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BODY); // BODY_KIT
		if (BodyKitCarPart)
		{
			// Read height attribute from body kit
			RideHeight = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, bStringHash((char*)"RIDE_HEIGHT"), original);
		}
	}

	return RideHeight;
}

// Extra Pitch
float __stdcall CarRenderInfo_GetExtraPitch(DWORD* _CarRenderInfo, float original)
{
	float ExtraPitch = original;

	// Get value from custom attribute
	DWORD* TheRideInfo = (DWORD*)_CarRenderInfo[33]; // CarRenderInfo->pRideInfo
	if (TheRideInfo)
	{
		DWORD* BodyKitCarPart = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BODY); // BODY_KIT
		if (BodyKitCarPart)
		{
			// Read height attribute from body kit
			ExtraPitch = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, bStringHash((char*)"EXTRA_PITCH"), original);
		}
	}

	return ExtraPitch;
}

// Reflection Offset
float CarRenderInfo_GetReflectionOffset(DWORD* _CarRenderInfo, float original)
{
	float ReflectionOffset = original;

	// Get value from custom attribute
	DWORD* TheRideInfo = (DWORD*)_CarRenderInfo[33]; // CarRenderInfo->pRideInfo
	if (TheRideInfo)
	{
		DWORD* BodyKitCarPart = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BODY); // BODY_KIT
		if (BodyKitCarPart)
		{
			// Read height attribute from body kit
			ReflectionOffset = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, bStringHash((char*)"REFLECTION_OFFSET"), original);
		}
	}

	return ReflectionOffset;
}

// Extra Rear Tire Offset
float ExtraRearTireOffset;

float* __fastcall Attrib_Gen_ecar_ExtraRearTireOffset_Hook(DWORD* _CarRenderInfo, void* EDX_Unused)
{
	ExtraRearTireOffset = 0.0f;
	
	if (_CarRenderInfo)
	{
		DWORD* Attrib_Instance = _CarRenderInfo + 1515;

		if (Attrib_Instance)
		{
			float* ExtraRearTireOffsetPtr = Attrib_Gen_ecar_ExtraRearTireOffset(Attrib_Instance);

			DWORD* TheRideInfo = (DWORD*)_CarRenderInfo[33]; // CarRenderInfo->pRideInfo
			if (TheRideInfo)
			{
				DWORD* BodyKitCarPart = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::BODY); // BODY_KIT
				if (BodyKitCarPart)
				{
					// Read attribute from body kit
					ExtraRearTireOffset = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, bStringHash((char*)"EXTRA_REAR_TIRE_OFFSET"), *ExtraRearTireOffsetPtr);
				}
			}
		}
	}

	return &ExtraRearTireOffset;
}

// 0x74F2FF
void __declspec(naked) ExtraRearTireOffsetCave_CarRenderInfo_Render()
{
	_asm
	{
		mov ecx, esi // CarRenderInfo instead of Attrib
		mov dword ptr ds: [esp+0x18], edi
		call Attrib_Gen_ecar_ExtraRearTireOffset_Hook
		push 0x74F30E
		retn
	}
}

// Rear wheel light material replacement
// 0x74F40B
DWORD edi_wheel_backup;
void __declspec(naked) RearWheelLightMaterialCodeCave()
{
	_asm
	{
		mov edi_wheel_backup, edi
		mov edi, dword ptr ds:[esp+0x10]
		cmp edi, ebx // wheel model != 0
		jz loc_74F45A
		cmp ecx, ebx // light material != 0
		jz loc_74F45A
		mov eax, dword ptr ds:[esp+0xB0]
		mov ecx, [edi]
		push eax
		push 0x22719FA9 // MAGSILVER
		and ecx, 0xFFFFFFFC
		call eModel_ReplaceLightMaterial_Game
		mov ecx, dword ptr ds : [esp + 0xB0]
		push ecx
		mov ecx, [edi]
		push 0xFD102A92 // MAGCHROME
		and ecx, 0xFFFFFFFC
		call eModel_ReplaceLightMaterial_Game
		mov edx, dword ptr ds : [esp + 0xB0]
		mov ecx, [edi]
		push edx
		push 0x12049251 // MAGGUNMETAL
		and ecx, 0xFFFFFFFC
		call eModel_ReplaceLightMaterial_Game


	loc_74F45A:
		mov edi, edi_wheel_backup
		push 0x74F45A
		retn
	}
}

void CarRenderInfo_AdjustBrakeScale(DWORD* CarRenderInfo, D3DXMATRIX* local_world, int WheelID)
{
	bool IsRearWheel = WheelID > 1;
	DWORD* TheRideInfo = (DWORD*)CarRenderInfo[33];

	float* WheelRadiusScale = (float*)(CarRenderInfo + 80);

	if (TheRideInfo)
	{
		if (!CarConfigs[TheRideInfo[0]].Main.ScaleBrakesWithRims) return;

		// Get wheels and brakes
		DWORD* WheelPart = RideInfo_GetPart(TheRideInfo, IsRearWheel ? CAR_SLOT_ID::REAR_WHEEL : CAR_SLOT_ID::FRONT_WHEEL);
		DWORD* BrakePart = RideInfo_GetPart(TheRideInfo, IsRearWheel ? CAR_SLOT_ID::REAR_BRAKE : CAR_SLOT_ID::FRONT_BRAKE);

		if (IsRearWheel && !WheelPart) WheelPart = RideInfo_GetPart(TheRideInfo, CAR_SLOT_ID::FRONT_WHEEL); // Get front wheel if rear wheel is not installed

		if (WheelPart && BrakePart)
		{
			int OuterRadius = CarPart_GetAppliedAttributeIParam(WheelPart, bStringHash((char*)"OUTER_RADIUS"), 23);
			int InnerRadius = CarPart_GetAppliedAttributeIParam(WheelPart, bStringHash((char*)"INNER_RADIUS"), 20);

			bool ScaleRim = CarPart_GetAppliedAttributeIParam(WheelPart, bStringHash((char*)"SCALE"), 1);
			bool ScaleBrake = CarPart_GetAppliedAttributeIParam(BrakePart, bStringHash((char*)"SCALE"), 1);

			if ((ScaleRim && ScaleBrake) && (OuterRadius != 23 || InnerRadius != 20)) // If the rim is not stock
			{
				if (InnerRadius > 16)
				{
					D3DXVECTOR3 scale, translation;
					D3DXQUATERNION rotation;
					D3DXMatrixDecompose(&scale, &rotation, &translation, local_world);

					// Set initial scale
					scale.x *= 0.85f;
					scale.z *= 0.85f;

					// Scale to the car's wheel
					scale.x *= WheelRadiusScale[WheelID];
					scale.z *= WheelRadiusScale[WheelID];

					// Adjust scale for rim size
					scale.x += scale.x * (InnerRadius - 17) * 0.07f;
					scale.z += scale.z * (InnerRadius - 17) * 0.07f;

					// Clip size for really big rims
					float maxScale = 1.15f * WheelRadiusScale[WheelID];
					if (abs(scale.x) > maxScale)
					{
						scale.x = Signum(scale.x) * maxScale;
						//scale.y = Signum(scale.y) * maxScale;
						scale.z = Signum(scale.z) * maxScale;
					}

					D3DXMATRIX result;
					D3DXMatrixScaling(&result, scale.x, scale.y, scale.z);

					D3DXMATRIX rotationMatrix;
					D3DXMatrixRotationQuaternion(&rotationMatrix, &rotation);

					D3DXMatrixMultiply(&result, &result, &rotationMatrix);

					result._41 = translation.x;
					result._42 = translation.y;
					result._43 = translation.z;

					*local_world = result;
				}
			}
		}
	}
}

void __fastcall eViewPlatInterface_Render_FrontLeftBrake(DWORD* view, DWORD* CarRenderInfo, DWORD* model, bMatrix4* local_world, DWORD* light_context, unsigned int flags, unsigned int unk)
{
	CarRenderInfo_AdjustBrakeScale(CarRenderInfo, (D3DXMATRIX*)local_world, 0);
	eViewPlatInterface_Render(view, model, local_world, light_context, flags, unk);
}

// 0x74FFD1
void __declspec(naked) ScaleBrakesCave_FrontLeft_eViewPlatInterface_Render()
{
	_asm
	{
		mov edx, esi // CarRenderInfo
		call eViewPlatInterface_Render_FrontLeftBrake
		push 0x74FFD6
		retn
	}
}

void __fastcall eViewPlatInterface_Render_FrontRightBrake(DWORD* view, DWORD* CarRenderInfo, DWORD* model, bMatrix4* local_world, DWORD* light_context, unsigned int flags, unsigned int unk)
{
	CarRenderInfo_AdjustBrakeScale(CarRenderInfo, (D3DXMATRIX*)local_world, 1);
	eViewPlatInterface_Render(view, model, local_world, light_context, flags, unk);
}


// 0x750181
void __declspec(naked) ScaleBrakesCave_FrontRight_eViewPlatInterface_Render()
{
	_asm
	{
		mov edx, esi // CarRenderInfo
		call eViewPlatInterface_Render_FrontRightBrake
		push 0x750186
		retn
	}
}

void __fastcall eViewPlatInterface_Render_RearRightBrake(DWORD* view, DWORD* CarRenderInfo, DWORD* model, bMatrix4* local_world, DWORD* light_context, unsigned int flags, unsigned int unk)
{
	CarRenderInfo_AdjustBrakeScale(CarRenderInfo, (D3DXMATRIX*)local_world, 2);
	eViewPlatInterface_Render(view, model, local_world, light_context, flags, unk);
}

// 0x75033B
void __declspec(naked) ScaleBrakesCave_RearRight_eViewPlatInterface_Render()
{
	_asm
	{
		mov edx, esi // CarRenderInfo
		call eViewPlatInterface_Render_RearRightBrake
		push 0x750340
		retn
	}
}

void __fastcall eViewPlatInterface_Render_RearLeftBrake(DWORD* view, DWORD* CarRenderInfo, DWORD* model, bMatrix4* local_world, DWORD* light_context, unsigned int flags, unsigned int unk)
{
	CarRenderInfo_AdjustBrakeScale(CarRenderInfo, (D3DXMATRIX*)local_world, 3);
	eViewPlatInterface_Render(view, model, local_world, light_context, flags, unk);
}

// 0x7504AC
void __declspec(naked) ScaleBrakesCave_RearLeft_eViewPlatInterface_Render()
{
	_asm
	{
		mov edx, dword ptr ds : [esp + 0x14] // CarRenderInfo
		call eViewPlatInterface_Render_RearLeftBrake
		push 0x7504B1
		retn
	}
}

// 0x75051A
void __declspec(naked) ScaleBrakesCave_RearLeftFE_eViewPlatInterface_Render()
{
	_asm
	{
		mov edx, dword ptr ds : [esp + 0x14] // CarRenderInfo
		call eViewPlatInterface_Render_RearLeftBrake
		push 0x75051F
		retn
	}
}

int __fastcall CarRenderInfo_SetPlayerDamage_Hook(DWORD* CarRenderInfo, void* EDX_Unused, DWORD* DamageInfo)
{
	int result = CarRenderInfo_SetPlayerDamage_Game(CarRenderInfo, DamageInfo);

	bool DamageLights = false;

	DWORD* RideInfo = (DWORD*)CarRenderInfo[33];
	if (RideInfo)
	{
		DamageLights = CarConfigs[RideInfo[0]].Textures.DamageLights;
	}

	if (DamageLights)
	{
		if ((DamageInfo[0] & 7) >= 2) DamageInfo[5] |= 7; // Front damage: Break headlights
		if (((DamageInfo[0] >> 3) & 0x7) >= 2) DamageInfo[5] |= 248; // Rear damage: Break brakelights and reverses
		if (((DamageInfo[0] >> 12) & 0x7) >= 2) DamageInfo[5] |= 1; // Front left damage: Break left headlight
		if (((DamageInfo[0] >> 15) & 0x7) >= 2) DamageInfo[5] |= 2; // Front right damage: Break right headlight
		if (((DamageInfo[0] >> 18) & 0x7) >= 2) DamageInfo[5] |= 72; // Rear left damage: Break left brakelight and reverse
		if (((DamageInfo[0] >> 21) & 0x7) >= 2) DamageInfo[5] |= 144; // Rear right damage: Break right brakelight and reverse
	}

	return result;
}