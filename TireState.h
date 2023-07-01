#pragma once

#include "stdio.h"
#include "CarPart.h"
#include "InGameFunctions.h"

void __fastcall TireState_DoSkids_Hook(DWORD* _TireState, DWORD* _CarRenderConn, float intensity, float* delta_pos, float* tireWorldMatrix, int Unk, float SkidWidth)
{
	float* TireOffsets;
	int KitNumber = 0;
	float TireOffsetY = 0.0f;
	float BodyTireWidth = SkidWidth;
	float _SkidWidth = SkidWidth;
	float BodyTireOffset = 0.0f;
	int WheelID = 0;
	BYTE OffsetInMM;
	bool IsRear;

	if (_CarRenderConn)
	{
		WORD* eCarAttributes = (WORD*)_CarRenderConn[7]; // Attrib_Gen_ecar mAttributes
		DWORD* TheRideInfo = (DWORD*)_CarRenderConn[16]; // CarRenderConn->mRideInfo

		if (eCarAttributes && TheRideInfo)
		{
			for (int i = 0; i < 4; i++) // Fix Y offset for the current wheel
			{
				IsRear = i >> 1;

				// Get TireOffset Y from VLT
				if (i >= Attrib_Private_GetLength(eCarAttributes))
					TireOffsets = (float*)Attrib_DefaultDataArea();
				else TireOffsets = (float*)&eCarAttributes[i*8 + 8];

				TireOffsetY = TireOffsets[1]; // Y

				// Get Kit Number and attributes
				DWORD* BodyKitCarPart = RideInfo_GetPart(TheRideInfo, 23); // BODY_KIT
				if (BodyKitCarPart)
				{
					KitNumber = CarPart_GetAppliedAttributeIParam(BodyKitCarPart, bStringHash("KITNUMBER"), 0);
					// Read offset attributes from body kit
					BodyTireOffset = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, IsRear ? bStringHash("REAR_TIRE_OFFSET") : bStringHash("FRONT_TIRE_OFFSET"), 0.0f);
					BodyTireWidth = CarPart_GetAppliedAttributeFParam(BodyKitCarPart, 0, IsRear ? bStringHash("REAR_TIRE_WIDTH") : bStringHash("FRONT_TIRE_WIDTH"), SkidWidth);
				}

				// Get KitWheelOffsetFront/Rear
				if (IsRear)
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

				float KitWheelOffset = (float)OffsetInMM * 0.001f; // Convert mm -> meters

				// Calculate new offset
				if (TireOffsetY <= 0.0f) // Multiply offsets with -1 if negative
				{
					KitWheelOffset *= -1;
					BodyTireOffset *= -1;
				}

				TireOffsetY += KitWheelOffset; // Add offset from VLT
				TireOffsetY += BodyTireOffset; // Add offset from body kit attribute


				// Write new offsets into CarRenderConn
				*(float*)(_CarRenderConn + 37 + i * 4) = TireOffsetY;


				// Modify skid width if the function pushed correct tire state
				DWORD* CRCTireState = (DWORD*)_CarRenderConn[29 + i]; // CarRenderConn->mTireState[i]
				if (CRCTireState == _TireState) _SkidWidth = BodyTireWidth;
			}
		}
	}

	// Finally do the skids
	TireState_DoSkids_Game(_TireState, intensity, delta_pos, tireWorldMatrix, Unk, _SkidWidth);
}

