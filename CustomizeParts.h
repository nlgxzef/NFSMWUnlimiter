#include "stdio.h"
#include "InGameFunctions.h"

void __fastcall CustomizeParts_dtor_Hook(DWORD* _CustomizeParts, void* EDX_Unused)
{
	RenderFECarFlares = -1;
	CustomizeParts_dtor(_CustomizeParts);
}

void __fastcall CustomizeParts_NotificationMessage(DWORD* _CustomizeParts, void* EDX_Unused, DWORD MessageHash, DWORD* FEObject, DWORD param1, DWORD param2)
{
	DWORD* PartInCart; // eax MAPDST
	unsigned int MenuID = _CustomizeParts[82];
	DWORD* SelectedPart; // eax MAPDST
	DWORD* ASelectablePart; // eax MAPDST
	int PackageSwitchArg; // eax

	// Get CarType Info
	void* FECarRecord = *(void**)_FECarRecord;
	int CarTypeID = FECarRecord_GetType(FECarRecord);

	if (MessageHash != 0x406415E3) // !PAD_ACCEPT
		CustomizationScreen_NotificationMessage(_CustomizeParts, MessageHash, FEObject, param1, param2);

	switch (MessageHash)
	{
	case 0x911AB364: // PAD_BACK
		if ((MenuID >= MenuID::Customize_Parts_Attachment0 && MenuID <= Customize_Parts_Attachment9) && !CarConfigs[CarTypeID].Main.ListAttachmentsUnderParts) // Attachments menu
		{
			cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizeSubTopPkg, _CustomizeParts[83] | (MenuID << 16), 0, 0); // CustomizeGenericTop.fng
		}
		else if (MenuID == MenuID::Customize_Visual_CustomGauges)
		{
			if (*(bool*)_CustomizeParts_TexturePackLoaded)
			{
				PackageSwitchArg = _CustomizeParts[83] | 0x3070000;
				*((BYTE*)_CustomizeParts + 456) = 1;
				cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizeSubPkg, PackageSwitchArg, 0, 0); // CustomizeCategory
			}
		}
		else if (MenuID <= MenuID::Customize_Vinyls_Min || MenuID > MenuID::Customize_Vinyls_Last)
		{
			cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizeSubPkg, _CustomizeParts[83] | (MenuID << 16), 0, 0); // CustomizeCategory
		}
		else
		{
			CarCustomizeManager_ClearTempColoredPart((DWORD*)_gCarCustomizeManager);
			cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizeSubTopPkg, _CustomizeParts[83] | (MenuID << 16), 0, 0); // CustomizeGenericTop
		}
		break;

	case 0xCF91AACD: // ??
		if (MenuID == MenuID::Customize_Visual_CustomGauges)
		{
			if (*(bool*)_CustomizeParts_TexturePackLoaded)
			{
				*((BYTE*)_CustomizeParts + 456) = 1;
			}
		}
		break;

	case 0x5A928018:
		PartInCart = (*(DWORD * (__thiscall**)(DWORD*))(*_CustomizeParts + 24))(_CustomizeParts);// FindInCartPart
		if (PartInCart)
		{
			if (!CarCustomizeManager_IsPartInCart((DWORD*)_gCarCustomizeManager, PartInCart))
			{
				PartInCart[8] &= 0xFu;
				(*(void(__thiscall**)(DWORD*))(*_CustomizeParts + 12))(_CustomizeParts);
			}
		}
		break;

	case 0x406415E3: // PAD_ACCEPT
		if (bList_TraversebList((DWORD*)(_CustomizeParts + 12), 0) != _CustomizeParts[59])
		{
			if (MenuID == MenuID::Customize_Visual_CustomGauges) // Custom Gauges
			{
				if (!*(bool*)_CustomizeParts_TexturePackLoaded) return;
				SelectedPart = (*(DWORD * (__thiscall**)(DWORD*))(*_CustomizeParts + 20))(_CustomizeParts);
				if (SelectedPart && (SelectedPart[8] & 0xF) == 2)
				{
					CustomizationScreen_PlayLocked(_CustomizeParts);
				}
				else
				{
					if (*(DWORD*)0x9BA080)
						CarCustomizeManager_ClearTempColoredPart((DWORD*)_gCarCustomizeManager);

					ASelectablePart = (DWORD*)j_malloc(44);
					if (ASelectablePart) SelectablePart_copy(ASelectablePart, SelectedPart);
					else ASelectablePart = 0;

					CarCustomizeManager_SetTempColoredPart((DWORD*)_gCarCustomizeManager, ASelectablePart);
					cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizeHudColorPkg, _CustomizeParts[82] | (_CustomizeParts[83] << 16), 0, 0);
				}

			}
			else
			{
				if (MenuID <= MenuID::Customize_Vinyls_Min || MenuID > MenuID::Customize_Vinyls_Last)
				{
					CustomizationScreen_NotificationMessage(_CustomizeParts, 0x406415E3, FEObject, param1, param2);
					return;
				}

				// Vinyls
				SelectedPart = (*(DWORD * (__thiscall**)(DWORD*))(*_CustomizeParts + 20))(_CustomizeParts);// GetSelectedPart

				if (SelectedPart && (SelectedPart[8] & 0xF) == 2)
				{
					CustomizationScreen_PlayLocked(_CustomizeParts);
				}
				else
				{
					if (CarPart_GetAppliedAttributeUParam((DWORD*)SelectedPart[3], 0x6212682B, 0)) // NUMREMAPCOLOURS
					{
						ASelectablePart = (DWORD*)j_malloc(44);
						if (ASelectablePart) SelectablePart_copy(ASelectablePart, SelectedPart);
						else ASelectablePart = 0;

						CarCustomizeManager_SetTempColoredPart((DWORD*)_gCarCustomizeManager, ASelectablePart);
						cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizePaintPkg, _CustomizeParts[82] | (_CustomizeParts[83] << 16), 0, 0);
					}
					else
						CustomizationScreen_NotificationMessage(_CustomizeParts, 0x406415E3, FEObject, param1, param2);
				}
			}
		}

		break;

	case 0x5073EF13: // PAD_LTRIGGER
		if (MenuID == MenuID::Customize_Parts_Headlights)
		{
			if (RenderFECarFlares == 1)
			{
				RenderFECarFlares = 0;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x70DFE5C2); // Text, COMMON_OFF
			}
			else if (RenderFECarFlares == 0)
			{
				RenderFECarFlares = 1;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x417B2604); // Text, COMMON_ON
			}
		}
		else if (MenuID == MenuID::Customize_Parts_Taillights)
		{
			switch (RenderFECarFlares)
			{
			default:
			case -1:
				RenderFECarFlares = 6;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x6AB80AFA); // Text, BUTTON_BRAKE_REVERSE
				break;
			case 2:
				RenderFECarFlares = -1;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x70DFE5C2); // Text, COMMON_OFF
				break;
			case 6:
				RenderFECarFlares = 2;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x417B2604); // Text, COMMON_ON
				break;
			}
		}
		break;

	case 0xD9FEEC59: // PAD_RTRIGGER
		if (MenuID == MenuID::Customize_Parts_Headlights)
		{
			if (RenderFECarFlares == 1)
			{
				RenderFECarFlares = 0;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x70DFE5C2); // Text, COMMON_OFF
			}
			else if (RenderFECarFlares == 0)
			{
				RenderFECarFlares = 1;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x417B2604); // Text, COMMON_ON
			}
		}
		else if (MenuID == MenuID::Customize_Parts_Taillights)
		{
			switch (RenderFECarFlares)
			{
			default:
			case -1:
				RenderFECarFlares = 2;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x417B2604); // Text, COMMON_ON
				break;
			case 2:
				RenderFECarFlares = 6;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x6AB80AFA); // Text, BUTTON_BRAKE_REVERSE
				break;
			case 6:
				RenderFECarFlares = -1;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x70DFE5C2); // Text, COMMON_OFF
				break;
			}
		}
		break;
	}
}

void __fastcall CustomizeParts_RefreshHeader(DWORD* _CustomizeParts, void* EDX_Unused)
{
	DWORD* SelectedPart;
	unsigned int MenuID = _CustomizeParts[82];

	if (MenuID == MenuID::Customize_Parts_Headlights || MenuID == MenuID::Customize_Parts_Taillights)
	{
		FEngSetVisible(FEngFindObject((const char*)_CustomizeParts[4], 0x53639A10)); // Switcher
		FEngSetVisible(FEngFindObject((const char*)_CustomizeParts[4], 0x2C3CC2D3)); // bg

		switch (RenderFECarFlares)
		{
		case 1:
		case 2:
			FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x417B2604); // Text, COMMON_ON
			break;
		case 6:
			FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x6AB80AFA); // Text, BUTTON_BRAKE_REVERSE
			break;
		case -1:
		case 0:
		default:
			FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x70DFE5C2); // Text, COMMON_OFF
			break;
		}
	}
	else
	{
		FEngSetInvisible(FEngFindObject((const char*)_CustomizeParts[4], 0x53639A10)); // Switcher
		FEngSetInvisible(FEngFindObject((const char*)_CustomizeParts[4], 0x2C3CC2D3)); // bg
	}

	CustomizationScreen_RefreshHeader(_CustomizeParts);

	if (bList_TraversebList((DWORD*)(_CustomizeParts + 12), 0) == _CustomizeParts[59])
	{
		FEngSetInvisible(FEngFindObject((const char*)_CustomizeParts[4], 0x8D1559A4)); // Career Part Price Group
		FEngSetInvisible(FEngFindObject((const char*)_CustomizeParts[4], 0x5E7B09C9)); // Part Name??
		FEngSetInvisible(FEngFindObject((const char*)_CustomizeParts[4], 0xF2492598)); // Heat Level Group
	}
	else
	{
		SelectedPart = (DWORD*)(*(int(__thiscall**)(DWORD*))(*_CustomizeParts + 20))(_CustomizeParts);
		if (SelectedPart)
		{
			if (CarPart_GetAppliedAttributeUParam((DWORD*)SelectedPart[3], 0x6212682B, 0)) // NUMREMAPCOLOURS
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0xB94139F4, 0x8098A54C); // COMMON_CONTINUE
			else FEngSetLanguageHash((const char*)_CustomizeParts[4], 0xB94139F4, 0x649F4A65); // CP_ADD_TO_CART
		

			if (_CustomizeParts[82] == MenuID::Customize_Visual_CustomGauges) // Custom Gauges
			{
				CustomizeParts_SetHUDTextures(_CustomizeParts);
				CustomizeParts_SetHUDColors(_CustomizeParts);
			}
			else if ((float)(*(int*)_RealTimer - _CustomizeParts[110]) * (*(float*)0x890984) <= (*(float*)0x894B58))
				*((BYTE*)_CustomizeParts + 436) = 1;
			else
			{
				CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, SelectedPart[4], (DWORD*)SelectedPart[3]);
			}

			DWORD LanguageHash = CarPart_GetAppliedAttributeUParam((DWORD*)(SelectedPart[3]), bStringHash((char*)"LANGUAGEHASH"), 0);
			if (LanguageHash)
				FEngSetLanguageHash((char const*)_CustomizeParts[4], 0x5E7B09C9, LanguageHash);
			else FEPrintf((char const*)_CustomizeParts[4], 0x5E7B09C9, "%s", CarPart_GetName((DWORD*)(SelectedPart[3])));
		}
	}
}

void __fastcall CustomizeParts_Setup(DWORD* _CustomizeParts, void* EDX_Unused)
{
	DWORD MenuID = _CustomizeParts[82];
	DWORD PartIconNormal = 0, PartIconCF = 0, PartIconCustom = 0;
	int CarSlotID = 0;
	int PartCategory = 0;
	DWORD SelectablePartsList[3];
	DWORD* TheActiveCarPart;
	DWORD* TheSelectablePart;
	DWORD UnlockHash;
	DWORD PartName;
	bool IsLocked;

	int v9; // ecx
	DWORD* v10; // esi
	DWORD* v11; // eax
	int v12; // eax

	DWORD* dword_9BA080 = *(DWORD**)0x9BA080;

	// Get CarType Info
	void* FECarRecord = *(void**)_FECarRecord;
	int CarTypeID = FECarRecord_GetType(FECarRecord);
	sprintf(CarTypeName, GetCarTypeName(CarTypeID));

	// Vinyls
	if (MenuID >= MenuID::Customize_Vinyls_First && MenuID <= MenuID::Customize_Vinyls_Last)
	{
		CarSlotID = CAR_SLOT_ID::VINYL_LAYER0;
		int i = MenuID - MenuID::Customize_Vinyls_First;

		if (i == 0)
		{
			PartIconNormal = CarConfigs[CarTypeID].Icons.VisualVinylsCustom;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.VisualVinylsCustom;

			if (PartIconNormal == -1) PartIconNormal = VinylGroups[i].TextureHash;
			if (_CustomizeParts[87] == -1) _CustomizeParts[87] = VinylGroups[i].StringHash;
		}
		else
		{
			PartIconNormal = VinylGroups[i].TextureHash;
			_CustomizeParts[87] = VinylGroups[i].StringHash;
		}

		PartCategory = VinylGroups[i].Index;
		
		if (dword_9BA080) TheActiveCarPart = (DWORD*)dword_9BA080[3];
		else TheActiveCarPart = CarCustomizeManager_GetActivePartFromSlot((DWORD*)_gCarCustomizeManager, CarSlotID);

	}
	else
	{
		switch (MenuID) // Other parts
		{
		case MenuID::Customize_Parts_Bodykits:
			CarSlotID = CAR_SLOT_ID::BODY;
			PartIconNormal = CustomizeIsInBackRoom() != 0
				? CarConfigs[CarTypeID].Icons.BackroomPartsBodyKits
				: CarConfigs[CarTypeID].Icons.PartsBodyKits;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsBodyKits;
			break;

		case MenuID::Customize_Parts_Hoods:
			CarSlotID = CAR_SLOT_ID::HOOD;
			PartIconNormal = CustomizeIsInBackRoom() != 0
				? CarConfigs[CarTypeID].Icons.BackroomPartsHoods
				: CarConfigs[CarTypeID].Icons.PartsHoods;
			PartIconCF = CustomizeIsInBackRoom() != 0
				? CarConfigs[CarTypeID].Icons.BackroomPartsHoodsCF
				: CarConfigs[CarTypeID].Icons.PartsHoodsCF;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsHoods;
			break;

		case MenuID::Customize_Parts_RoofScoops:
			CarSlotID = CAR_SLOT_ID::ROOF;
			PartIconNormal = CustomizeIsInBackRoom() != 0
				? CarConfigs[CarTypeID].Icons.BackroomPartsRoofScoops
				: CarConfigs[CarTypeID].Icons.PartsRoofScoops;
			PartIconCF = CustomizeIsInBackRoom() != 0
				? CarConfigs[CarTypeID].Icons.BackroomPartsRoofScoopsCF
				: CarConfigs[CarTypeID].Icons.PartsRoofScoopsCF;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsRoofScoops;
			break;

		case MenuID::Customize_Parts_Interior:
			CarSlotID = CAR_SLOT_ID::INTERIOR;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsInterior;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsInterior;
			break;

		case MenuID::Customize_Parts_Roof: // Roof
			CarSlotID = CAR_SLOT_ID::BASE;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsRoof;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsRoof;
			break;

		case MenuID::Customize_Parts_Brakes: // Brake
			CarSlotID = CAR_SLOT_ID::FRONT_BRAKE;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsBrakes;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsBrakes;
			break;

		case MenuID::Customize_Parts_Headlights: // Headlight
			CarSlotID = CAR_SLOT_ID::LEFT_HEADLIGHT;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsHeadlights;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsHeadlights;
			RenderFECarFlares = ForceLightsOnInFE ? 1 : 0;
			break;

		case MenuID::Customize_Parts_Taillights: // Brakelight
			CarSlotID = CAR_SLOT_ID::LEFT_BRAKELIGHT;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsTaillights;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsTaillights;
			RenderFECarFlares = ForceLightsOnInFE ? 2 : -1;
			break;

		case MenuID::Customize_Parts_Mirrors: // Mirror
			CarSlotID = CAR_SLOT_ID::LEFT_SIDE_MIRROR;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsMirrors;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsMirrors;
			break;

		case MenuID::Customize_Parts_Attachment0: // Attachment 1
			CarSlotID = CAR_SLOT_ID::ATTACHMENT0;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsAttachment0;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsAttachment0;
			break;

		case MenuID::Customize_Parts_Attachment1: // Attachment 2
			CarSlotID = CAR_SLOT_ID::ATTACHMENT1;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsAttachment1;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsAttachment1;
			break;

		case MenuID::Customize_Parts_Attachment2: // Attachment 3
			CarSlotID = CAR_SLOT_ID::ATTACHMENT2;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsAttachment2;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsAttachment2;
			break;

		case MenuID::Customize_Parts_Attachment3: // Attachment 4
			CarSlotID = CAR_SLOT_ID::ATTACHMENT3;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsAttachment3;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsAttachment3;
			break;

		case MenuID::Customize_Parts_Attachment4: // Attachment 5
			CarSlotID = CAR_SLOT_ID::ATTACHMENT4;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsAttachment4;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsAttachment4;
			break;

		case MenuID::Customize_Parts_Attachment5: // Attachment 6
			CarSlotID = CAR_SLOT_ID::ATTACHMENT5;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsAttachment5;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsAttachment5;
			break;

		case MenuID::Customize_Parts_Attachment6: // Attachment 7
			CarSlotID = CAR_SLOT_ID::ATTACHMENT6;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsAttachment6;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsAttachment6;
			break;

		case MenuID::Customize_Parts_Attachment7: // Attachment 8
			CarSlotID = CAR_SLOT_ID::ATTACHMENT7;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsAttachment7;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsAttachment7;
			break;

		case MenuID::Customize_Parts_Attachment8: // Attachment 9
			CarSlotID = CAR_SLOT_ID::ATTACHMENT8;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsAttachment8;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsAttachment8;
			break;

		case MenuID::Customize_Parts_Attachment9: // Attachment 10
			CarSlotID = CAR_SLOT_ID::ATTACHMENT9;
			PartIconNormal = CarConfigs[CarTypeID].Icons.PartsAttachment9;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.PartsAttachment9;
			break;

		case MenuID::Customize_Visual_WindowTint: // Window Tint
			CarSlotID = CAR_SLOT_ID::WINDOW_TINT;
			PartIconNormal = CarConfigs[CarTypeID].Icons.VisualWindowTint;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.VisualWindowTint;
			break;

		case MenuID::Customize_Visual_CustomGauges: // Custom Gauges

			if (*(bool*)_CustomizeParts_TexturePackLoaded) // 0x9B9EB0
			{
				CustomizeParts_ShowHudObjects(_CustomizeParts);
				cFEng_QueuePackageMessage(*(int**)cFEng_mInstance, 0x8CB81F09, (const char*)_CustomizeParts[4], 0);
			}
			else
			{
				cFEng_QueuePackageMessage(*(int**)cFEng_mInstance, 0x13FD3296, (const char*)_CustomizeParts[4], 0);
				CustomizeParts_LoadHudTextures(_CustomizeParts);
			}

			CarSlotID = CAR_SLOT_ID::CUSTOM_HUD;
			PartIconNormal = CustomizeIsInBackRoom() != 0
				? CarConfigs[CarTypeID].Icons.BackroomVisualCustomGauges
				: CarConfigs[CarTypeID].Icons.VisualCustomGauges;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.VisualCustomGauges;
			break;

		case MenuID::Customize_Visual_Driver: // Drivers
			CarSlotID = CAR_SLOT_ID::DRIVER;
			PartIconNormal = CarConfigs[CarTypeID].Icons.VisualDriver;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.VisualDriver;
			break;

		case MenuID::Customize_Visual_LicensePlate: // License Plates
			CarSlotID = CAR_SLOT_ID::LICENSE_PLATE;
			PartIconNormal = CarConfigs[CarTypeID].Icons.VisualLicensePlate;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.VisualLicensePlate;
			break;

		case MenuID::Customize_Visual_Tires: // Tires
			CarSlotID = CAR_SLOT_ID::HEADLIGHT;
			PartIconNormal = CarConfigs[CarTypeID].Icons.VisualTires;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.VisualTires;
			break;

		case MenuID::Customize_Visual_Neon: // Neon
			CarSlotID = CAR_SLOT_ID::BRAKELIGHT;
			PartIconNormal = CarConfigs[CarTypeID].Icons.VisualNeon;
			_CustomizeParts[87] = CarConfigs[CarTypeID].Names.VisualNeon;
			break;

		case 0x316: // Empty Slot
			CarSlotID = CAR_SLOT_ID::SPINNER;
			PartIconNormal = bStringHash((char*)"VISUAL_PART_SPINNER");
			_CustomizeParts[87] = bStringHash((char*)"CO_SPINNER");
			break;

		case 0x317: // Empty Slot (no model)
			CarSlotID = CAR_SLOT_ID::CV;
			PartIconNormal = bStringHash((char*)"VISUAL_PART_CV");
			_CustomizeParts[87] = bStringHash((char*)"CO_CV");
			break;

		case 0x318: // Empty Slot (no model)
			CarSlotID = CAR_SLOT_ID::WHEEL_MANUFACTURER;
			PartIconNormal = bStringHash((char*)"VISUAL_PART_WHEEL_MANUFACTURER");
			_CustomizeParts[87] = bStringHash((char*)"CO_WHEEL_MANUFACTURER");
			break;

		case 0x319: // Empty Slot (no model)
			CarSlotID = CAR_SLOT_ID::MISC;
			PartIconNormal = bStringHash((char*)"VISUAL_PART_MISC");
			_CustomizeParts[87] = bStringHash((char*)"CO_MISC");
			break;
		}

		if (MenuID == MenuID::Customize_Visual_CustomGauges && dword_9BA080) TheActiveCarPart = (DWORD*)dword_9BA080[3];
		else TheActiveCarPart = CarCustomizeManager_GetActivePartFromSlot((DWORD*)_gCarCustomizeManager, CarSlotID);
	}

AddToList:
	// Initialize the list
	SelectablePartsList[0] = (DWORD)SelectablePartsList; // Next
	SelectablePartsList[1] = (DWORD)SelectablePartsList; // Prev
	//v31 = 0;

	if (CarSlotID != CAR_SLOT_ID::VINYL_LAYER0) PartCategory = 0; // VINYL_LAYER0

	CarCustomizeManager_GetCarPartList((DWORD*)_gCarCustomizeManager, CarSlotID, SelectablePartsList, PartCategory); // Read parts into the list

	DWORD* v8 = (DWORD*)SelectablePartsList[0]; // Next
	int v28 = 0;
	int a8 = 1;
	DWORD NewPartIcon = PartIconNormal;

	if ((DWORD*)SelectablePartsList[0] != SelectablePartsList)
	{
		while (1)
		{
			// List maths??
			v9 = *v8; // Next -> Next
			v10 = v8;
			v11 = (DWORD*)v8[1]; // Next -> Prev
			*v11 = v9;
			*(DWORD*)(v9 + 4) = (DWORD)v11;
			v12 = v10[4];

			TheSelectablePart = (DWORD*)(v10 - 1);
			UnlockHash = CarCustomizeManager_GetUnlockHash_CarPart((DWORD*)_gCarCustomizeManager, (DWORD*)TheSelectablePart[3], _CustomizeParts[82], v12);

			if (CarSlotID != CAR_SLOT_ID::VINYL_LAYER0) break; // VINYL_LAYER0

			if ((*((BYTE*)TheSelectablePart[3] + 5) & 0x1F) == PartCategory) goto LABEL_46;

			(**(void(__thiscall***)(DWORD*, int))TheSelectablePart)(TheSelectablePart, 1); // Refresh the part??

		LABEL_50:
			v8 = (DWORD*)SelectablePartsList[0];
			if ((DWORD*)SelectablePartsList[0] == SelectablePartsList)
				goto LABEL_51;
		}

	LABEL_46:
		// Choose Part Icon
		PartIconCustom = CarPart_GetAppliedAttributeIParam((DWORD*)TheSelectablePart[3], bStringHash((char*)"TEXTUREHASH"), 0);
		if (PartIconCustom) NewPartIcon = PartIconCustom;
		else if (CarPart_GetAppliedAttributeIParam((DWORD*)TheSelectablePart[3], bStringHash((char*)"CARBONFIBRE"), 0) && PartIconCF) NewPartIcon = PartIconCF;
		else NewPartIcon = PartIconNormal;
	
		PartName = *(BYTE*)(TheSelectablePart[3] + 5) >> 5;
		IsLocked = CarCustomizeManager_IsPartLocked((DWORD*)_gCarCustomizeManager, EDX_Unused, TheSelectablePart, 0);
		CustomizationScreen_AddPartOption(_CustomizeParts, TheSelectablePart, NewPartIcon, PartName, 0, UnlockHash, IsLocked);

		if (TheActiveCarPart && TheSelectablePart[3] == (DWORD)TheActiveCarPart) v28 = a8;
		a8++;
		goto LABEL_50;
	}

LABEL_51:
	int v21 = *(int*)_Showcase_FromIndex;
	if (v21)
	{
		if (*((BYTE*)_CustomizeParts + 297))
		{
			*((BYTE*)_CustomizeParts + 284) = 0;
			*((BYTE*)_CustomizeParts + 281) = 1;
			*((BYTE*)_CustomizeParts + 282) = 0;
			_CustomizeParts[68] = 0;
		}
		(*(void(__thiscall**)(DWORD*, int))(_CustomizeParts[11] + 64))(_CustomizeParts + 11, v21);
		*(int*)_Showcase_FromIndex = 0;
	}
	else
	{
		if (*((BYTE*)_CustomizeParts + 297))
		{
			*((BYTE*)_CustomizeParts + 284) = 0;
			*((BYTE*)_CustomizeParts + 281) = 1;
			*((BYTE*)_CustomizeParts + 282) = 0;
			_CustomizeParts[68] = 0;
		}
		(*(void(__thiscall**)(DWORD*, int))(_CustomizeParts[11] + 64))(_CustomizeParts + 11, v28);
	}
	(*(void(__thiscall**)(DWORD*))(*_CustomizeParts + 12))(_CustomizeParts);
	//v31 = -1;
	bTList_SelectablePart_dtor(SelectablePartsList);
}