#pragma once

#include "stdafx.h"
#include "stdio.h"

#define MaxPermTex 127
#define MaxTempTex 47

#pragma pack(push, 1)

typedef struct
{
	/* 0x0000 */ DWORD TexturesToLoadPerm[MaxPermTex]; // 87
	/* 0x015c */ DWORD TexturesToLoadTemp[MaxTempTex]; // 87
	/* 0x02b8 */ int NumTexturesToLoadPerm;
	/* 0x02bc */ int NumTexturesToLoadTemp;
	/* 0x02c0 */ DWORD MappedSkinHash;
	/* 0x02c4 */ DWORD MappedSkinbHash;
	/* 0x02c8 */ DWORD MappedGlobalSkinHash;
	/* 0x02cc */ DWORD MappedWheelHash;
	/* 0x02d0 */ DWORD MappedSpinnerHash;
	/* 0x02d4 */ DWORD MappedBadgingHash;
	/* 0x02d8 */ DWORD MappedSpoilerHash;
	/* 0x02dc */ DWORD MappedRoofScoopHash;
	/* 0x02e0 */ DWORD MappedUnkHash; // ??
	/* 0x02e4 */ DWORD MappedLightHash[11];
	/* 0x0310 */ DWORD MappedTireHash;
	/* 0x0314 */ DWORD MappedRimHash;
	/* 0x0318 */ DWORD MappedRimBlurHash;
	/* 0x031c */ DWORD MappedLicensePlateHash; // ??
	/* 0x0320 */ DWORD ReplaceSkinHash;
	/* 0x0324 */ DWORD ReplaceSkinbHash;
	/* 0x0328 */ DWORD ReplaceGlobalSkinHash;
	/* 0x032c */ DWORD ReplaceWheelHash;
	/* 0x0330 */ DWORD ReplaceSpinnerHash;
	/* 0x0334 */ DWORD ReplaceSpoilerHash;
	/* 0x0338 */ DWORD ReplaceRoofScoopHash; // ??
	/* 0x033c */ DWORD ReplaceUnknownHash; // ??
	/* 0x0340 */ DWORD ReplaceHeadlightHash[3];
	/* 0x034c */ DWORD ReplaceHeadlightGlassHash[3];
	/* 0x0358 */ DWORD ReplaceBrakelightHash[3];
	/* 0x0364 */ DWORD ReplaceBrakelightGlassHash[3];
	/* 0x0370 */ DWORD ReplaceReverselightHash[3];
	/* 0x037c */ DWORD ShadowHash;
} UsedCarTextureInfo;

#pragma pack(pop)

int UsedCarTextureReplace(DWORD* UsedCarTextureTable, int NumberOfTextures, int SourceTextureHash, int DestinationTextureHash)
{
	if (UsedCarTextureTable)
	{
		for (int i = 0; i < NumberOfTextures; i++)
		{
			if (UsedCarTextureTable[i] == SourceTextureHash) UsedCarTextureTable[i] = DestinationTextureHash;
		}
	}

	return DestinationTextureHash;
}