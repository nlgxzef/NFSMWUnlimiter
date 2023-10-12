#pragma once

#include "stdio.h"
#include "CarPart.h"
#include "InGameFunctions.h"

#include "bMatrix.h"

void __fastcall TireState_DoSkids_Hook(DWORD* _TireState, DWORD* _CarRenderConn, float intensity, float* delta_pos, float* tireWorldMatrix, float* carMatrix, float skidWidth)
{
	Attrib_Gen_ecar_LayoutStruct* eCarAttributes = (Attrib_Gen_ecar_LayoutStruct*)_CarRenderConn[7]; // Attrib_Gen_ecar mAttributes
	DWORD* CarRenderInfo = (DWORD*)_CarRenderConn[17]; // CarRenderConn->mRenderInfo
	float TireSkidWidth = skidWidth;

	int WheelID;

	for (WheelID = 0; WheelID < 4; WheelID++)
	{
		if ((DWORD*)_CarRenderConn[29 + WheelID] == _TireState) break;
	}
	
	if (CarRenderInfo && WheelID < 4)
	{
		TireSkidWidth = CarRenderInfo_GetTireWidth(CarRenderInfo, 0, WheelID)/* * CarRenderInfo_GetTireRadiusScale(CarRenderInfo, 0, WheelID)*/; // Get tire width and multiply with radius scale
	}

	bMatrix4 skidMatrix = tireWorldMatrix;
	float camberAdjust = 0.03;
	float skidOffset = TireSkidWidth / 2 - camberAdjust;
	skidMatrix.v3.y += skidMatrix.v3.y < 0 ? skidOffset : -skidOffset;

	TireState_DoSkids_Game(_TireState, intensity, delta_pos, skidMatrix, carMatrix, TireSkidWidth);
}

