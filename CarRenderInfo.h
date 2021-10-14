#include "stdio.h"
#include "InGameFunctions.h"

char TextureName[255];
char* NormalMapSuffix = "_N";
int InteriorTextureHash, InteriorNormalTextureHash;

int UsedCarTextureReplace(int* UsedCarTextureTable, int NumberOfTextures, int SourceTextureHash, int DestinationTextureHash)
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
			InteriorNormalTextureHash = bStringHash2("_N", texHash);
			*(CarRenderInfo + 0xCE) = bStringHash2("_N", origTexHash);
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
}