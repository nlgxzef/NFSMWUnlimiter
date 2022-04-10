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

void __fastcall CarRenderInfo_UpdateWheelYRenderOffset(DWORD* CarRenderInfo, void* EDX_Unused)
{
	float* TireOffsets, *TireSkidWidthKitScaleAttrib;
	BYTE OffsetInMM;
	float WheelWidth, WheelRadius, TireSkidWidthKitScale, TireSkidWidth, TireWidth, TireRadius, BodyKitFrontTireOffset, BodyKitRearTireOffset;
	WORD* TireSkidWidthKitScaleArea;
	DWORD AttrVal;

	if (CarRenderInfo[34]) // CarRenderInfo->pCarTypeInfo
	{
		int CurrWheelID = 0;
		int CurrWheelData = 0;
		int CurrWheelDataX2 = 0;

		// WheelYRenderOffset[4], WheelWidths[2], WheelRadius[2], WheelWidthScales[4], WheelRadiusScales[4], WheelBrakeMarkerY[2], WheelSpeeds[4]
		float* WheelFloats = (float*)(CarRenderInfo + 68);
		int v41 = -52 - (DWORD)CarRenderInfo;

		DWORD* TheRideInfo = (DWORD*)CarRenderInfo[33]; // CarRenderInfo->pRideInfo
		if (TheRideInfo)
		{
			do
			{
				WORD* eCarAttributes = (WORD*)CarRenderInfo[1517]; // Attrib_Gen_ecar mAttributes
				bool IsRearWheel = CurrWheelID > 1;

				if (CurrWheelID >= Attrib_Private_GetLength(eCarAttributes))
					TireOffsets = (float*)Attrib_DefaultDataArea();
				else TireOffsets = (float*)&eCarAttributes[CurrWheelData + 8];

				int KitNumber = 0;
				WheelFloats[0] = -TireOffsets[1]; // Y

				BodyKitFrontTireOffset = 0;
				BodyKitRearTireOffset = 0;

				DWORD* BodyKitCarPart = RideInfo_GetPart(TheRideInfo, 23); // BODY_KIT
				if (BodyKitCarPart)
				{
					KitNumber = CarPart_GetAppliedAttributeIParam(BodyKitCarPart, bStringHash("KITNUMBER"), 0);
					// Read offset attributes from body kit
					AttrVal = CarPart_GetAppliedAttributeUParam(BodyKitCarPart, bStringHash("FRONT_TIRE_OFFSET"), 0);
					BodyKitFrontTireOffset = *(float*)&AttrVal;
					AttrVal = CarPart_GetAppliedAttributeUParam(BodyKitCarPart, bStringHash("REAR_TIRE_OFFSET"), 0);
					BodyKitRearTireOffset = *(float*)&AttrVal;

				}

				// todo (in v4): Read offset attributes from spacer parts

				if (IsRearWheel)
				{
					OffsetInMM = *(int*)_TweakKitWheelOffsetRear;
					if (!OffsetInMM)
					{
						if (KitNumber < Attrib_Private_GetLength(eCarAttributes + 128))
							OffsetInMM = *(BYTE*)((BYTE*)eCarAttributes + KitNumber + 264);
						else OffsetInMM = *(BYTE*)Attrib_DefaultDataArea();
					}
				}
				else
				{
					OffsetInMM = *(int*)_TweakKitWheelOffsetFront;
					if (!OffsetInMM)
					{
						if (KitNumber < Attrib_Private_GetLength(eCarAttributes + 135))
							OffsetInMM = *(BYTE*)((BYTE*)eCarAttributes + KitNumber + 278);
						else OffsetInMM = *(BYTE*)Attrib_DefaultDataArea();
					}
				}

				float WheelOffset = (float)OffsetInMM * 0.001f; // mm -> meters
				if (WheelFloats[0] <= 0.0f)
					WheelOffset *= -1;
				WheelFloats[0] += WheelOffset;

				// Add offsets read from part attributes
				if (IsRearWheel)
				{
					if (CurrWheelID == 2) WheelFloats[0] += BodyKitRearTireOffset; // Right wheel
					else WheelFloats[0] -= BodyKitRearTireOffset; // Left wheel
				}
				else
				{
					if (CurrWheelID == 1) WheelFloats[0] += BodyKitFrontTireOffset; // Right wheel
					else WheelFloats[0] -= BodyKitFrontTireOffset; // Left wheel
				}

				WheelWidth = *(float*)&CarRenderInfo[IsRearWheel + 72];
				WheelRadius = *(float*)&CarRenderInfo[IsRearWheel + 74];

				if (CurrWheelID >= Attrib_Private_GetLength(eCarAttributes + 106))
					TireSkidWidth = *(float*)Attrib_DefaultDataArea();
				else
					TireSkidWidth = *(float*)((int)WheelFloats + v41 + (DWORD)eCarAttributes);
				TireSkidWidthKitScaleArea = eCarAttributes + 40;
				if (CurrWheelData >= 16)
				{
					if (KitNumber >= Attrib_Private_GetLength(TireSkidWidthKitScaleArea))
						TireSkidWidthKitScaleAttrib = (float*)Attrib_DefaultDataArea();
					else
						TireSkidWidthKitScaleAttrib = (float*)&eCarAttributes[4 * KitNumber + 44];
					TireSkidWidthKitScale = TireSkidWidthKitScaleAttrib[1];
				}
				else if (KitNumber >= Attrib_Private_GetLength(TireSkidWidthKitScaleArea))
				{
					TireSkidWidthKitScale = *(float*)Attrib_DefaultDataArea();
				}
				else
				{
					TireSkidWidthKitScale = *(float*)&eCarAttributes[4 * KitNumber + 44];
				}

				CurrWheelDataX2 = CurrWheelData * 2;
				TireWidth = TireSkidWidthKitScale * TireSkidWidth;
				TireRadius = *(float*)(CurrWheelData * 2 + CarRenderInfo[1517] + 28);
				if (WheelWidth <= 0.0f || TireWidth <= 0.0f)
					WheelFloats[8] = 1.0f; // WheelWidthScales
				else
					WheelFloats[8] = TireWidth / WheelWidth; // WheelWidthScales
				if (WheelRadius <= 0.0f || TireRadius <= 0.0f)
					WheelFloats[12] = 1.0f; // WheelRadiusScales
				else
					WheelFloats[12] = TireRadius / WheelRadius; // WheelRadiusScales

				// Go to the next wheel
				++WheelFloats;
				++CurrWheelID;
				CurrWheelData += 8;
			} while ((CurrWheelDataX2 + 16) < 64);
		}
	}
	else
	{
		CarRenderInfo[68] = 0; // WheelYRenderOffset[0]
		CarRenderInfo[69] = 0; // WheelYRenderOffset[1]
		CarRenderInfo[70] = 0; // WheelYRenderOffset[2]
		CarRenderInfo[71] = 0; // WheelYRenderOffset[3]
	}
}