#pragma once
#include "stdio.h"
#include "InGameFunctions.h"

static injector::hook_back<void(*)(DWORD*, int, int)> hb_RenderFEFlares;

void RenderFEFlares(DWORD* view, int reflection, int renderFlareFlags)
{
	DWORD* TheFrontEndRenderingCar; // esi
	DWORD* i; // ebp
	DWORD* _CarRenderInfo; // ecx

	if (RenderFECarFlares != -1) // global var
	{
		if (*(int*)_DrawCars)
		{
			if (*(int*)_DrawLightFlares)
			{
				TheFrontEndRenderingCar = *(DWORD**)_FrontEndRenderingCarList;
				for (i = (DWORD*)_FrontEndRenderingCarList;
					TheFrontEndRenderingCar != i;
					TheFrontEndRenderingCar = (DWORD*)TheFrontEndRenderingCar[0])
				{
					if (TheFrontEndRenderingCar[349])
					{
						_CarRenderInfo = (DWORD*)TheFrontEndRenderingCar[198]; // 0x318
						if (_CarRenderInfo)
							CarRenderInfo_RenderFlaresOnCar(_CarRenderInfo, view, (float*)TheFrontEndRenderingCar + 200, (float*)TheFrontEndRenderingCar + 204, RenderFECarFlares, reflection, renderFlareFlags);
					}
				}
			}
		}
	}

	hb_RenderFEFlares.fun(view, reflection, renderFlareFlags);
}

DWORD GetWheelTextureHash(DWORD* _RideInfo, int index)
{
	DWORD* RimPart = RideInfo_GetPart(_RideInfo, index == 0 ? 66 : 67); // ? FRONT_WHEEL : REAR_WHEEL
	if (!RimPart) return 0;

	return bStringHash2("_WHEEL", CarPart_GetTextureNameHash(RimPart));
}

DWORD GetWheelTextureMaskHash(DWORD* _RideInfo, int index)
{
	DWORD* RimPart = RideInfo_GetPart(_RideInfo, index == 0 ? 66 : 67); // ? FRONT_WHEEL : REAR_WHEEL
	if (!RimPart) return 0;

	return bStringHash2("_WHEEL_INNER_MASK", CarPart_GetTextureNameHash(RimPart));
}

void CompositeRim(DWORD* _RideInfo)
{
	DWORD CompositeWheelHash; // ebx
	DWORD WheelTexHash; // edi
	DWORD TextureNameHash; // eax MAPDST
	DWORD WheelInnerMaskTexHash; // eax

	for (int i = 0; i < 2; i++)
	{
		CompositeWheelHash = _RideInfo[16+i]; // DUMMY_WHEELx, DUMMY_SPINNERx
		WheelTexHash = GetWheelTextureHash(_RideInfo, i);
		WheelInnerMaskTexHash = GetWheelTextureMaskHash(_RideInfo, i);
		CompositeWheel(_RideInfo, CompositeWheelHash, WheelTexHash, WheelInnerMaskTexHash, 78);
	}
}

int GetTempCarSkinTextures(DWORD* textures_to_load, int num_textures, int max_textures, DWORD* ride)
{
	DWORD* VinylPart; // r3
	DWORD VinylLayerHash; // r29
	DWORD VinylLayerMaskHash; // r30
	DWORD WheelTextureHash; // r30
	DWORD WheelTextureMaskHash; // r3
	DWORD SpinnerTextureHash; // r30
	DWORD SpinnerTextureMaskHash; // r3

	// VINYL_LAYER0
	VinylPart = RideInfo_GetPart(ride, 77);
	if (VinylPart)
	{
		VinylLayerHash = GetVinylLayerHash(ride, 0);
		VinylLayerMaskHash = GetVinylLayerMaskHash(ride, 0);
		num_textures += UsedCarTextureAddToTable(textures_to_load, num_textures, max_textures, VinylLayerHash);
		num_textures += UsedCarTextureAddToTable(textures_to_load, num_textures, max_textures, VinylLayerMaskHash);
	}

	// FRONT_WHEEL
	WheelTextureHash = GetWheelTextureHash(ride, 0);
	WheelTextureMaskHash = GetWheelTextureMaskHash(ride, 0);
	if (WheelTextureHash && WheelTextureMaskHash)
	{
		num_textures += UsedCarTextureAddToTable(textures_to_load, num_textures, max_textures, WheelTextureHash);
		num_textures += UsedCarTextureAddToTable(textures_to_load, num_textures, max_textures, WheelTextureMaskHash);
	}

	// REAR_WHEEL
	WheelTextureHash = GetWheelTextureHash(ride, 1);
	WheelTextureMaskHash = GetWheelTextureMaskHash(ride, 1);
	if (WheelTextureHash && WheelTextureMaskHash)
	{
		num_textures += UsedCarTextureAddToTable(textures_to_load, num_textures, max_textures, WheelTextureHash);
		num_textures += UsedCarTextureAddToTable(textures_to_load, num_textures, max_textures, WheelTextureMaskHash);

		textures_to_load[180 - 87] = WheelTextureHash; // REAR WHEEL PAINT??
	}

	// SPINNER
	/*
	SpinnerTextureHash = GetSpinnerTextureHash(ride);
	SpinnerTextureMaskHash = GetSpinnerTextureMaskHash(ride);
	if (SpinnerTextureHash && SpinnerTextureMaskHash)
	{
		num_textures += UsedCarTextureAddToTable(textures_to_load, num_textures, max_textures, SpinnerTextureHash);
		num_textures += UsedCarTextureAddToTable(textures_to_load, num_textures, max_textures, SpinnerTextureMaskHash);
	}*/

	return num_textures;
}

int MenuID_Backup;

DWORD FindScreenInfo(char const* ScreenName, int MenuID)
{
	MenuID_Backup = MenuID; // Get menu ID to check for camera angle later.
	return FindScreenInfo_Game(ScreenName, MenuID);
}

DWORD FindScreenCameraInfo(DWORD ScreenInfo)
{
	DWORD result = FindScreenCameraInfo_Game(ScreenInfo);
	if (MenuID_Backup <= 0x100 || ScreenInfo == Attrib_StringToLowerCaseKey("customize_customizemain_257")) return result;

	// Get CarType Info
	void* FECarRecord = *(void**)_FECarRecord;
	int CarTypeID = FECarRecord_GetType(FECarRecord);
	sprintf(CarTypeName, GetCarTypeName(CarTypeID));

	// Read Camera Options for the car
	sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
	CIniReader CarINI(CarININame);
	CIniReader GeneralINI("UnlimiterData\\_General.ini");

	DWORD CustomAngle = 0;

	switch (MenuID_Backup)
	{
		// Parts sub menus
		case 0x101:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsBodyKits", "");
			break;
		case 0x102:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsSpoilers", "");
			break;
		case 0x103:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsRims", "");
			break;
		case 0x104:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsHoods", "");
			break;
		case 0x105:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsRoofScoops", "");
			break;
		case 0x106:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsInterior", "");
			break;
		case 0x107:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsRoof", "");
			break; 
		case 0x108:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsBrakes", "");
			break; 
		case 0x109:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsHeadlights", "");
			break;
		case 0x10A:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsTaillights", "");
			break;
		case 0x10B:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsMirrors", "");
			break;
		case 0x10C:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsAttachments", "");
			break;
		case 0x10D:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsAttachment1", "");
			break;
		case 0x10E:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsAttachment2", "");
			break;
		case 0x10F:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsAttachment3", "");
			break;
		case 0x110:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsAttachment4", "");
			break;
		case 0x111:
			CustomAngle = GetCarTextOptionVLTHash(CarINI, GeneralINI, "Cameras", "PartsAttachment5", "");
			break;

	}

	if (CustomAngle != 0 && CustomAngle != 0x82FC1624) result = CustomAngle;
	return result;
}