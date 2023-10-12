#pragma once
#include "stdio.h"
#include "InGameTypes.h"
#include "InGameFunctions.h"

void __fastcall CarRenderInfo_RenderFlaresOnCar(DWORD* CarRenderInfo, void* EDX_Unused, DWORD* view, bVector3* position, bMatrix4* body_matrix, int force_light_state, int reflection, int renderFlareFlags);

static injector::hook_back<void(*)(DWORD*, int, int)> hb_RenderFEFlares;

void RenderFEFlares(DWORD* view, int reflection, int renderFlareFlags)
{
	DWORD* TheFrontEndRenderingCar; // esi
	DWORD* i; // ebp
	DWORD* _CarRenderInfo; // ecx

	//if (RenderFECarFlares != -1) // global var
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
						{
							if (RenderFECarFlares != -1) CarRenderInfo_RenderFlaresOnCar(_CarRenderInfo, 0, view, (bVector3*)(TheFrontEndRenderingCar + 200), (bMatrix4*)(TheFrontEndRenderingCar + 204), RenderFECarFlares, reflection, renderFlareFlags);
							switch (RenderFECarFlares)
							{
								case 1: // Headlights
									_CarRenderInfo[1416] |= 3847; // OnLights
									break;
								case 2: // Taillights
									_CarRenderInfo[1416] |= 248; // OnLights
									break;
								default:
									_CarRenderInfo[1416] = 0; // OnLights
									break;
							}
						}
					}
				}
			}
		}
	}

	hb_RenderFEFlares.fun(view, reflection, renderFlareFlags);
}

DWORD GetWheelTextureHash(DWORD* _RideInfo, int index)
{
	DWORD* RimPart = RideInfo_GetPart(_RideInfo, index == 0 ? CAR_SLOT_ID::FRONT_WHEEL : CAR_SLOT_ID::REAR_WHEEL);
	if (!RimPart) return 0;

	DWORD TextureHash = CarPart_GetTextureNameHash(RimPart);
	if (TextureHash) return bStringHash2((char*)"_WHEEL", TextureHash);

	return CarConfigs[_RideInfo[0]].Textures.TireInnerMask
		? bStringHash2((char*)"_TIRE", CarPart_GetCarTypeNameHash(RimPart))
		: 0;
}

DWORD GetWheelTextureMaskHash(DWORD* _RideInfo, int index)
{
	DWORD* RimPart = RideInfo_GetPart(_RideInfo, index == 0 ? CAR_SLOT_ID::FRONT_WHEEL : CAR_SLOT_ID::REAR_WHEEL);
	if (!RimPart) return 0;

	DWORD TextureHash = CarPart_GetTextureNameHash(RimPart);
	if (TextureHash) return bStringHash2((char*)"_WHEEL_INNER_MASK", TextureHash);
	return CarConfigs[_RideInfo[0]].Textures.TireInnerMask
		? bStringHash2((char*)"_TIRE_INNER_MASK", CarPart_GetCarTypeNameHash(RimPart))
		: 0;
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
		CompositeWheel(_RideInfo, CompositeWheelHash, WheelTexHash, WheelInnerMaskTexHash, CAR_SLOT_ID::PAINT_RIM);
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
	VinylPart = RideInfo_GetPart(ride, CAR_SLOT_ID::VINYL_LAYER0);
	if (VinylPart)
	{
		VinylLayerHash = GetVinylLayerHash_Game(ride, 0);
		VinylLayerMaskHash = GetVinylLayerMaskHash_Game(ride, 0);
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

		//textures_to_load[180 - 87] = WheelTextureHash; // REAR WHEEL PAINT??
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

DWORD FindScreenInfo(char const* ScreenName, int MenuID)
{
	if (MenuID >= MenuID::Customize_Rims_Min && MenuID <= MenuID::Customize_Rims_Last) // Rims (front)
	{
		return FindScreenInfo_Game("Rims.fng", -1);
	}
	else if (MenuID >= MenuID::Customize_Vinyls_First && MenuID <= MenuID::Customize_Vinyls_Last) // Vinyls
	{
		if (MenuID - MenuID::Customize_Vinyls_First >= VinylGroups.size()) MenuID = MenuID::Customize_Vinyls_AltCam;
		else MenuID = VinylGroups[MenuID - MenuID::Customize_Vinyls_First].UseAltCamera ? MenuID::Customize_Vinyls_AltCam : MenuID::Customize_Vinyls_DefaultCam;
	}

	return FindScreenInfo_Game(ScreenName, MenuID);
}

DWORD FindScreenCameraInfo(DWORD ScreenInfo)
{
	DWORD result = FindScreenCameraInfo_Game(ScreenInfo);

	DWORD* TheGarageMainScreen = GarageMainScreen_GetInstance();
	if (!TheGarageMainScreen) return result;

	int MenuID = TheGarageMainScreen[34];

	// Get CarType Info
	void* FECarRecord = *(void**)_FECarRecord;
	if ((MenuID <= MenuID::Customize_First && MenuID >= MenuID::Customize_Last) || !FECarRecord) return result;

	int CarTypeID = FECarRecord_GetType(FECarRecord);

	DWORD CustomAngle = 0;
	if (MenuID >= MenuID::Customize_Rims_Min && MenuID <= MenuID::Customize_Rims_Last) // Rims
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
	else if (MenuID >= MenuID::Customize_Vinyls_Min && MenuID <= MenuID::Customize_Vinyls_Last) // Vinyls
	{
		CustomAngle = CarConfigs[CarTypeID].Cameras.VisualVinylsGroup;
	}
	else if (MenuID >= MenuID::Customize_Decals_Slot1 && MenuID <= MenuID::Customize_Decals_Slot8) // Decal slots
	{
		switch (*(int*)CustomizeDecals_CurrentDecalLocation) // 0x501 - 0x506
		{
		case MenuID::Customize_Decals_Windshield:
		default:
			switch (MenuID)
			{
			case MenuID::Customize_Decals_Slot1:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield1;                          // DECAL_FRONT_WINDOW_TEX0
				break;
			case MenuID::Customize_Decals_Slot2:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield2;
				break;
			case MenuID::Customize_Decals_Slot3:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield3;
				break;
			case MenuID::Customize_Decals_Slot4:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield4;
				break;
			case MenuID::Customize_Decals_Slot5:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield5;
				break;
			case MenuID::Customize_Decals_Slot6:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield6;
				break;
			case MenuID::Customize_Decals_Slot7:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield7;
				break;
			case MenuID::Customize_Decals_Slot8:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield8;
				break;
			}
			break;
		case MenuID::Customize_Decals_RearWindow:
			switch (MenuID)
			{
			case MenuID::Customize_Decals_Slot1:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow1;                          // DECAL_REAR_WINDOW_TEX0
				break;
			case MenuID::Customize_Decals_Slot2:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow2;
				break;
			case MenuID::Customize_Decals_Slot3:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow3;
				break;
			case MenuID::Customize_Decals_Slot4:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow4;
				break;
			case MenuID::Customize_Decals_Slot5:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow5;
				break;
			case MenuID::Customize_Decals_Slot6:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow6;
				break;
			case MenuID::Customize_Decals_Slot7:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow7;
				break;
			case MenuID::Customize_Decals_Slot8:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow8;
				break;
			}
			break;
		case MenuID::Customize_Decals_LeftDoor:
			switch (MenuID)
			{
			case MenuID::Customize_Decals_Slot1:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor1;                          // DECAL_LEFT_DOOR_TEX0
				break;
			case MenuID::Customize_Decals_Slot2:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor2;
				break;
			case MenuID::Customize_Decals_Slot3:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor3;
				break;
			case MenuID::Customize_Decals_Slot4:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor4;
				break;
			case MenuID::Customize_Decals_Slot5:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor5;
				break;
			case MenuID::Customize_Decals_Slot6:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor6;
				break;
			}
			break;
		case MenuID::Customize_Decals_RightDoor:
			switch (MenuID)
			{
			case MenuID::Customize_Decals_Slot1:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor1;                         // DECAL_RIGHT_DOOR_TEX0
				break;
			case MenuID::Customize_Decals_Slot2:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor2;
				break;
			case MenuID::Customize_Decals_Slot3:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor3;
				break;
			case MenuID::Customize_Decals_Slot4:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor4;
				break;
			case MenuID::Customize_Decals_Slot5:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor5;
				break;
			case MenuID::Customize_Decals_Slot6:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor6;
				break;
			}
			break;
		case MenuID::Customize_Decals_LeftQuarter:
			switch (MenuID)
			{
			case MenuID::Customize_Decals_Slot1:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter1;                          // DECAL_LEFT_QUARTER_TEX0
				break;
			case MenuID::Customize_Decals_Slot2:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter2;
				break;
			case MenuID::Customize_Decals_Slot3:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter3;
				break;
			case MenuID::Customize_Decals_Slot4:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter4;
				break;
			case MenuID::Customize_Decals_Slot5:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter5;
				break;
			case MenuID::Customize_Decals_Slot6:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter6;
				break;
			case MenuID::Customize_Decals_Slot7:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter7;
				break;
			case MenuID::Customize_Decals_Slot8:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter8;
				break;
			}
			break;
		case MenuID::Customize_Decals_RightQuarter:
			switch (MenuID)
			{
			case MenuID::Customize_Decals_Slot1:
			default:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter1;                          // DECAL_RIGHT_QUARTER_TEX0
				break;
			case MenuID::Customize_Decals_Slot2:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter2;
				break;
			case MenuID::Customize_Decals_Slot3:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter3;
				break;
			case MenuID::Customize_Decals_Slot4:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter4;
				break;
			case MenuID::Customize_Decals_Slot5:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter5;
				break;
			case MenuID::Customize_Decals_Slot6:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter6;
				break;
			case MenuID::Customize_Decals_Slot7:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter7;
				break;
			case MenuID::Customize_Decals_Slot8:
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
			case MenuID::Customize_Parts_Bodykits:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsBodyKits;
				break;
			case MenuID::Customize_Parts_Spoilers:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsSpoilers;
				break;
			case MenuID::Customize_Parts_Rims:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsRims;
				break;
			case MenuID::Customize_Parts_Hoods:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsHoods;
				break;
			case MenuID::Customize_Parts_RoofScoops:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsRoofScoops;
				break;
			case MenuID::Customize_Parts_Interior:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsInterior;
				break;
			case MenuID::Customize_Parts_Roof:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsRoof;
				break; 
			case MenuID::Customize_Parts_Brakes:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsBrakes;
				break; 
			case MenuID::Customize_Parts_Headlights:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsHeadlights;
				break;
			case MenuID::Customize_Parts_Taillights:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsTaillights;
				break;
			case MenuID::Customize_Parts_Mirrors:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsMirrors;
				break;
			case MenuID::Customize_Parts_Attachments:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachments;
				break;
			case MenuID::Customize_Parts_Attachment0:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment0;
				break;
			case MenuID::Customize_Parts_Attachment1:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment1;
				break;
			case MenuID::Customize_Parts_Attachment2:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment2;
				break;
			case MenuID::Customize_Parts_Attachment3:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment3;
				break;
			case MenuID::Customize_Parts_Attachment4:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment4;
				break;
			case MenuID::Customize_Parts_Attachment5:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment5;
				break;
			case MenuID::Customize_Parts_Attachment6:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment6;
				break;
			case MenuID::Customize_Parts_Attachment7:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment7;
				break;
			case MenuID::Customize_Parts_Attachment8:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment8;
				break;
			case MenuID::Customize_Parts_Attachment9:
				CustomAngle = CarConfigs[CarTypeID].Cameras.PartsAttachment9;
				break;
			case MenuID::Customize_Visual_Paint:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualPaint;
				break;
			case MenuID::Customize_Visual_Vinyls:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualVinyls;
				break;
			case MenuID::Customize_Visual_RimPaint:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualRimPaint;
				break;
			case MenuID::Customize_Visual_WindowTint:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualWindowTint;
				break;
			case MenuID::Customize_Visual_Decals:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecals;
				break;
			case MenuID::Customize_Visual_Numbers:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualNumbers;
				break;
			case MenuID::Customize_Visual_CustomGauges:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualCustomGauges;
				break;
			case MenuID::Customize_Visual_Driver:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDriver;
				break;
			case MenuID::Customize_Visual_LicensePlate:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualLicensePlate;
				break;
			case MenuID::Customize_Visual_Tires:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualTires;
				break;
			case MenuID::Customize_Visual_Neon:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualNeon;
				break;
			case MenuID::Customize_Decals_Windshield:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsWindshield;
				break;
			case MenuID::Customize_Decals_RearWindow:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRearWindow;
				break;
			case MenuID::Customize_Decals_LeftDoor:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftDoor;
				break;
			case MenuID::Customize_Decals_RightDoor:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightDoor;
				break;
			case MenuID::Customize_Decals_LeftQuarter:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsLeftQuarter;
				break;
			case MenuID::Customize_Decals_RightQuarter:
				CustomAngle = CarConfigs[CarTypeID].Cameras.VisualDecalsRightQuarter;
				break;
		}
	}

	if (MenuID == MenuID::Customize_Visual_Tires)
	{
		AnimateValue(*(float*)_CarSelectTireSteerAngle, -20.0f, 50.0f * (*(float*)_RealTimeElapsedFrame));
	}
	else
	{
		AnimateValue(*(float*)_CarSelectTireSteerAngle, CarSelectTireSteerAngle_Backup, 50.0f * (*(float*)_RealTimeElapsedFrame));
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

void elCloneLightContext(DWORD* light_context, bMatrix4* local_world, bMatrix4* world_view, bVector4* camera_world_position, DWORD* view, DWORD* old_context)
{
	D3DXVECTOR3 scale, translation;
	D3DXQUATERNION rotation;

	D3DXMatrixDecompose(&scale, &rotation, &translation, (D3DXMATRIX*)local_world);

	D3DXMATRIX matrix;
	D3DXMatrixRotationQuaternion(&matrix, &rotation);
	matrix._41 = translation.x;
	matrix._42 = translation.y;
	matrix._43 = translation.z;

	elCloneLightContext_Game(light_context, (bMatrix4*)&matrix, world_view, camera_world_position, view, old_context);
}