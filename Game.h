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

	return bStringHash2((char*)"_WHEEL", CarPart_GetTextureNameHash(RimPart));
}

DWORD GetWheelTextureMaskHash(DWORD* _RideInfo, int index)
{
	DWORD* RimPart = RideInfo_GetPart(_RideInfo, index == 0 ? 66 : 67); // ? FRONT_WHEEL : REAR_WHEEL
	if (!RimPart) return 0;

	return bStringHash2((char*)"_WHEEL_INNER_MASK", CarPart_GetTextureNameHash(RimPart));
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

DWORD FindScreenCameraInfo(DWORD ScreenInfo)
{
	DWORD result = FindScreenCameraInfo_Game(ScreenInfo);

	DWORD* TheGarageMainScreen = GarageMainScreen_GetInstance();
	if (!TheGarageMainScreen) return result;

	int MenuID = TheGarageMainScreen[34];
	if (MenuID <= 0x101 && MenuID >= 0x9FF) return result;

	if (ScreenInfo != TheGarageMainScreen[29]) return result;

	// Get CarType Info
	void* FECarRecord = *(void**)_FECarRecord;
	if ((MenuID <= 0x101 && MenuID >= 0x8FF) || !FECarRecord) return result;

	int CarTypeID = FECarRecord_GetType(FECarRecord);

	DWORD CustomAngle = 0;
	if (MenuID >= 0x701 && MenuID <= 0x7FF) // Rims
	{
		switch (RimsToCustomize)
		{
		case -1:
			CustomAngle = CarConfigs[CarTypeID].Cameras.PartsRimsBrandRear;
			break;
		case 0:
			CustomAngle = CarConfigs[CarTypeID].Cameras.PartsRimsBrandAll;
			break;
		case 1:
			CustomAngle = CarConfigs[CarTypeID].Cameras.PartsRimsBrand;
			break;
		}
	}
	else if (MenuID >= 0x401 && MenuID <= 0x4FF) // Vinyls
	{
		CustomAngle = CarConfigs[CarTypeID].Cameras.VisualVinylsGroup;
	}
	else if (MenuID >= 0x601 && MenuID <= 0x608) // Decal slots
	{
		switch (*(int*)CustomizeDecals_CurrentDecalLocation) // 0x501 - 0x506
		{
		case 0x501:
		default:
			switch (MenuID)
			{
			case 0x601:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield1;                          // DECAL_FRONT_WINDOW_TEX0
				break;
			case 0x602:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield2;
				break;
			case 0x603:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield3;
				break;
			case 0x604:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield4;
				break;
			case 0x605:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield5;
				break;
			case 0x606:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield6;
				break;
			case 0x607:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield7;
				break;
			case 0x608:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield8;
				break;
			}
			break;
		case 0x502:
			switch (MenuID)
			{
			case 0x601:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow1;                          // DECAL_REAR_WINDOW_TEX0
				break;
			case 0x602:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow2;
				break;
			case 0x603:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow3;
				break;
			case 0x604:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow4;
				break;
			case 0x605:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow5;
				break;
			case 0x606:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow6;
				break;
			case 0x607:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow7;
				break;
			case 0x608:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow8;
				break;
			}
			break;
		case 0x503:
			switch (MenuID)
			{
			case 0x601:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor1;                          // DECAL_LEFT_DOOR_TEX0
				break;
			case 0x602:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor2;
				break;
			case 0x603:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor3;
				break;
			case 0x604:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor4;
				break;
			case 0x605:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor5;
				break;
			case 0x606:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor6;
				break;
			}
			break;
		case 0x504:
			switch (MenuID)
			{
			case 0x601:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor1;                         // DECAL_RIGHT_DOOR_TEX0
				break;
			case 0x602:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor2;
				break;
			case 0x603:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor3;
				break;
			case 0x604:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor4;
				break;
			case 0x605:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor5;
				break;
			case 0x606:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor6;
				break;
			}
			break;
		case 0x505:
			switch (MenuID)
			{
			case 0x601:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter1;                          // DECAL_LEFT_QUARTER_TEX0
				break;
			case 0x602:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter2;
				break;
			case 0x603:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter3;
				break;
			case 0x604:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter4;
				break;
			case 0x605:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter5;
				break;
			case 0x606:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter6;
				break;
			case 0x607:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter7;
				break;
			case 0x608:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter8;
				break;
			}
			break;
		case 0x506:
			switch (MenuID)
			{
			case 0x601:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter1;                          // DECAL_RIGHT_QUARTER_TEX0
				break;
			case 0x602:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter2;
				break;
			case 0x603:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter3;
				break;
			case 0x604:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter4;
				break;
			case 0x605:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter5;
				break;
			case 0x606:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter6;
				break;
			case 0x607:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter7;
				break;
			case 0x608:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter8;
				break;
			}
			break;
		}
	}
	else
	{
		switch (MenuID)
		{
			default:
				CustomAngle = FindScreenCameraInfo_Game(ScreenInfo);
			break;
			// Parts sub menus
			case 0x101:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsBodyKits;
				break;
			case 0x102:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsSpoilers;
				break;
			case 0x103:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsRims;
				break;
			case 0x104:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsHoods;
				break;
			case 0x105:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsRoofScoops;
				break;
			case 0x106:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsInterior;
				break;
			case 0x107:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsRoof;
				break; 
			case 0x108:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsBrakes;
				break; 
			case 0x109:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsHeadlights;
				break;
			case 0x10A:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsTaillights;
				break;
			case 0x10B:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsMirrors;
				break;
			case 0x10C:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachments;
				break;
			case 0x10D:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment0;
				break;
			case 0x10E:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment1;
				break;
			case 0x10F:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment2;
				break;
			case 0x110:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment3;
				break;
			case 0x111:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment4;
				break;
			case 0x112:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment5;
				break;
			case 0x113:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment6;
				break;
			case 0x114:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment7;
				break;
			case 0x115:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment8;
				break;
			case 0x116:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment9;
				break;
			case 0x301:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualPaint;
				break;
			case 0x302:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualVinyls;
				break;
			case 0x303:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualRimPaint;
				break;
			case 0x304:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualWindowTint;
				break;
			case 0x305:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecals;
				break;
			case 0x306:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualNumbers;
				break;
			case 0x307:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualCustomGauges;
				break;
			case 0x308:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDriver;
				break;
			case 0x309:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualLicensePlate;
				break;
			case 0x314:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualTires;
				break;
			case 0x315:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualNeon;
				break;
			case 0x501:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield;
				break;
			case 0x502:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow;
				break;
			case 0x503:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor;
				break;
			case 0x504:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor;
				break;
			case 0x505:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter;
				break;
			case 0x506:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter;
				break;
		}
	}

	if (MenuID == 0x314)
	{
		AnimateValue(*(float*)_CarSelectTireSteerAngle, -20.0f, 3.0f);
	}
	else
	{
		AnimateValue(*(float*)_CarSelectTireSteerAngle, CarSelectTireSteerAngle_Backup, 3.0f);
	}

	if (CustomAngle != 0 && CustomAngle != 0x82FC1624) result = CustomAngle;
	return result;
}

bool CarInfo_IsSkinned_Traffic(int CarTypeID)
{
	if (ShouldRandomizeInTraffic(CarTypeID))
	{
		return 1;
	}

	return CarInfo_IsSkinned_Game(CarTypeID);
}