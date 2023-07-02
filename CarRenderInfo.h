#include "stdio.h"
#include "CarPart.h"
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
	float WheelWidth, WheelRadius, TireSkidWidthKitScale, TireSkidWidth, TireWidth, TireRadius, BodyKitFrontTireOffset, BodyKitRearTireOffset, TireSkidWidthFront, TireSkidWidthRear;
	WORD* TireSkidWidthKitScaleArea;

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
				TireSkidWidthFront = 0;
				TireSkidWidthRear = 0;

				DWORD* BodyKitCarPart = RideInfo_GetPart(TheRideInfo, 23); // BODY_KIT
				if (BodyKitCarPart)
				{
					KitNumber = CarPart_GetAppliedAttributeIParam(BodyKitCarPart, bStringHash("KITNUMBER"), 0);
					// Read offset attributes from body kit
					BodyKitFrontTireOffset = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, bStringHash("FRONT_TIRE_OFFSET"), 0.0f);
					BodyKitRearTireOffset = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, bStringHash("REAR_TIRE_OFFSET"), 0.0f);
					TireSkidWidthFront = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, bStringHash("FRONT_TIRE_WIDTH"), 0.0f);
					TireSkidWidthRear = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, bStringHash("REAR_TIRE_WIDTH"), 0.0f);
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
					TireSkidWidth = *(float*)(eCarAttributes + 110);

				// If they exist, use width value read from part attributes instead (DIRTY)
				if (IsRearWheel)
				{
					TireSkidWidth = TireSkidWidthRear != 0 ? TireSkidWidthRear : TireSkidWidth;
				}
				else
				{
					TireSkidWidth = TireSkidWidthFront != 0 ? TireSkidWidthFront : TireSkidWidth;
				}

				TireSkidWidthKitScaleArea = eCarAttributes + 40;
				if (IsRearWheel)
				{
					if (KitNumber >= Attrib_Private_GetLength(TireSkidWidthKitScaleArea))
						TireSkidWidthKitScaleAttrib = (float*)&eCarAttributes[44];//(float*)Attrib_DefaultDataArea();
					else
						TireSkidWidthKitScaleAttrib = (float*)&eCarAttributes[4 * KitNumber + 44];
					TireSkidWidthKitScale = TireSkidWidthKitScaleAttrib[1];
				}
				else if (KitNumber >= Attrib_Private_GetLength(TireSkidWidthKitScaleArea))
				{
					TireSkidWidthKitScale = *(float*)&eCarAttributes[44];//*(float*)Attrib_DefaultDataArea();
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

	// Fix and apply brake position markers
	int TireLOD = CarRenderInfo[1418];
	DWORD* FrontWheeleModel = (DWORD*)(CarRenderInfo[TireLOD + 1067] & 0xFFFFFFFC); // eModel
	DWORD* RearWheeleModel = (DWORD*)(CarRenderInfo[TireLOD + 1072] & 0xFFFFFFFC); // eModel
	DWORD* FrontBrakePositionMarker = 0, *RearBrakePositionMarker = 0;

	if (FrontWheeleModel) FrontBrakePositionMarker = (DWORD*)eModel_GetPositionMarker(FrontWheeleModel, bStringHash("FRONT_BRAKE"));
	if (RearWheeleModel) RearBrakePositionMarker = (DWORD*)eModel_GetPositionMarker(RearWheeleModel, bStringHash("REAR_BRAKE"));

	if (FrontBrakePositionMarker) CarRenderInfo[84] = FrontBrakePositionMarker[17]; // Y Position
	else CarRenderInfo[84] = 0;

	if (RearBrakePositionMarker) CarRenderInfo[85] = RearBrakePositionMarker[17]; // Y Position
	else // If there is no REAR_BRAKE markers attached to the rear rim, use FRONT_BRAKE marker instead
	{
		if (RearWheeleModel)
		{
			RearBrakePositionMarker = (DWORD*)eModel_GetPositionMarker(RearWheeleModel, bStringHash("FRONT_BRAKE"));
			if (RearBrakePositionMarker) CarRenderInfo[85] = RearBrakePositionMarker[17];
			else CarRenderInfo[85] = 0;
		}
		else CarRenderInfo[85] = 0;
	}
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
		if (!CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash("STOCK"), 0)) // If not stock
			return CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash("TEXTURE_NAME"), bStringHash("CARSHADOW_NEON")); // Custom texture or CARSHADOW_NEON
	}

	return 0;
}

DWORD GetShadowCutTextureHash(DWORD* _RideInfo)
{
	DWORD DefaultShadowCutTextureHash = bStringHash("CARSHADOW_NEON_CUT");
	
	DWORD NeonTextureHash = GetNeonTextureHash(_RideInfo);
	if (NeonTextureHash)
	{
		DWORD ShadowCutTextureHash = bStringHash2("_CUT", NeonTextureHash);
		if (GetTextureInfo(ShadowCutTextureHash, 0, 0)) return ShadowCutTextureHash;
		else if (GetTextureInfo(DefaultShadowCutTextureHash, 0, 0)) return DefaultShadowCutTextureHash;
	}

	return 0;
}

void SetShadowSize(DWORD* _RideInfo, bool IsNeon)
{
	//DWORD* BodyKitCarPart = RideInfo_GetPart(_RideInfo, 23); // BODY_KIT

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
		if (!CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash("STOCK"), 0)) // If not stock
		{
			r = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash("RED"), 0) % 256;
			g = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash("GREEN"), 0) % 256;
			b = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash("BLUE"), 0) % 256;
			a = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash("ALPHA"), 0) % 256;
			r2 = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash("RED2"), r) % 256;
			g2 = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash("GREEN2"), g) % 256;
			b2 = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash("BLUE2"), b) % 256;
			a2 = CarPart_GetAppliedAttributeIParam(NeonPart, bStringHash("ALPHA2"), a) % 256;

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
	return cutHash ? cutHash : bStringHash("CARSHADOW");
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

static injector::hook_back<void(*)(DWORD*, DWORD*, float*, float, int, int, float, DWORD, float)> hb_eRenderLightFlare;
DWORD* _CarRenderInfo_Backup = 0;

// Hook to apply custom flare colors
void eRenderLightFlare_Hook(DWORD* view, DWORD* light_flare, float* local_world, float intensity_scale, int a5, int a6, float a7, DWORD ColourOverRide, float sizescale)
{
	DWORD* CarRenderInfo = _CarRenderInfo_Backup;

	if (light_flare)
	{
		switch (light_flare[2]) // eLightFlare->NameHash
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
						int r = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash("RED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash("GREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash("BLUE"), 0) % 256;

						// If no color attribute is present, use the values from LEFT_HEADLIGHT instead
						if (r == 0 && g == 0 && b == 0)
						{
							DWORD* HeadlightPart = RideInfo_GetPart(RideInfo, 31); // LEFT_HEADLIGHT
							if (HeadlightPart)
							{
								r = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("RED"), 0) % 256;
								g = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("GREEN"), 0) % 256;
								b = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("BLUE"), 0) % 256;
							}
						}

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare[3] = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare[3] ? light_flare[3] : 0;
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
						int r = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("DISPRED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("DISPGREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("DISPBLUE"), 0) % 256;

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare[3] = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare[3] ? light_flare[3] : 0;
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
						int r = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("RED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("GREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("BLUE"), 0) % 256;

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare[3] = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare[3] ? light_flare[3] : 0;
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
						int r = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash("RED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash("GREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash("BLUE"), 0) % 256;

						// If no color attribute is present, use the values from LEFT_BRAKELIGHT instead
						if (r == 0 && g == 0 && b == 0)
						{
							DWORD* BrakelightPart = RideInfo_GetPart(RideInfo, 29); // LEFT_BRAKELIGHT
							if (BrakelightPart)
							{
								r = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("RED"), 0) % 256;
								g = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("GREEN"), 0) % 256;
								b = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("BLUE"), 0) % 256;
							}
						}

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare[3] = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare[3] ? light_flare[3] : 0;
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
						int r = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("DISPRED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("DISPGREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("DISPBLUE"), 0) % 256;

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare[3] = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare[3] ? light_flare[3] : 0;
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
						int r = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("RED"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("GREEN"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("BLUE"), 0) % 256;

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare[3] = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare[3] ? light_flare[3] : 0;
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
						int r = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash("RED2"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash("GREEN2"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(RBrakelightPart, bStringHash("BLUE2"), 0) % 256;

						// If no color attribute is present, use the values from LEFT_BRAKELIGHT instead
						if (r == 0 && g == 0 && b == 0)
						{
							DWORD* BrakelightPart = RideInfo_GetPart(RideInfo, 29); // LEFT_BRAKELIGHT
							if (BrakelightPart)
							{
								r = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("RED2"), 0) % 256;
								g = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("GREEN2"), 0) % 256;
								b = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("BLUE2"), 0) % 256;
							}
						}

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare[3] = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare[3] ? light_flare[3] : 0;
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
						int r = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("RED2"), 0) % 256;
						int g = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("GREEN2"), 0) % 256;
						int b = CarPart_GetAppliedAttributeIParam(BrakelightPart, bStringHash("BLUE2"), 0) % 256;

						// eLightFlare->ColourTint (normally unused in MW)
						light_flare[3] = r + (g << 8) + (b << 16);
						ColourOverRide = light_flare[3] ? light_flare[3] : 0;
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
				int r = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash("RED"), 0) % 256;
				int g = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash("GREEN"), 0) % 256;
				int b = CarPart_GetAppliedAttributeIParam(RHeadlightPart, bStringHash("BLUE"), 0) % 256;

				// If no color attribute is present, use the values from LEFT_HEADLIGHT instead
				if (r == 0 && g == 0 && b == 0)
				{
					DWORD* HeadlightPart = RideInfo_GetPart(RideInfo, 31); // LEFT_HEADLIGHT
					if (HeadlightPart)
					{
						r = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("RED"), 0) % 256;
						g = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("GREEN"), 0) % 256;
						b = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("BLUE"), 0) % 256;
					}
				}

				if (r == 0 && g == 0 && b == 0) hcRC = 0x40CCCCCC;
				else hcRC = r + (g << 8) + (b << 16) + (0x40 << 24);
			}
			else hcRC = 0x40CCCCCC;

			DWORD* HeadlightPart = RideInfo_GetPart(RideInfo, 31); // LEFT_HEADLIGHT
			if (HeadlightPart)
			{
				int r = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("RED"), 0) % 256;
				int g = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("GREEN"), 0) % 256;
				int b = CarPart_GetAppliedAttributeIParam(HeadlightPart, bStringHash("BLUE"), 0) % 256;

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

// Camber stuff
float __stdcall GetCamber(DWORD* _CarRenderInfo, float original, bool isRear)
{
	float Camber = original;

	// Get value from custom attribute
	DWORD* TheRideInfo = (DWORD*)_CarRenderInfo[33]; // CarRenderInfo->pRideInfo
	if (TheRideInfo)
	{
		DWORD* BodyKitCarPart = RideInfo_GetPart(TheRideInfo, 23); // BODY_KIT
		if (BodyKitCarPart)
		{
			// Read camber attributes from body kit
			Camber = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, isRear ? bStringHash("REAR_CAMBER") : bStringHash("FRONT_CAMBER"), original);
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
		DWORD* BodyKitCarPart = RideInfo_GetPart(TheRideInfo, 23); // BODY_KIT
		if (BodyKitCarPart)
		{
			// Read height attribute from body kit
			RideHeight = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, bStringHash("RIDE_HEIGHT"), original);
		}
	}

	return RideHeight;
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