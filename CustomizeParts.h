#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

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

	if (MessageHash != 0x406415E3) // !PAD_ACCEPT
		CustomizationScreen_NotificationMessage(_CustomizeParts, MessageHash, FEObject, param1, param2);

	switch (MessageHash)
	{
	case 0x911AB364: // PAD_BACK
		if (MenuID >= 0x10D && MenuID <= 0x116) // Attachments menu
		{
			cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizeSubTopPkg, _CustomizeParts[83] | (MenuID << 16), 0, 0); // CustomizeGenericTop.fng
		}
		else if (MenuID == 0x307)
		{
			if (*(bool*)_CustomizeParts_TexturePackLoaded)
			{
				PackageSwitchArg = _CustomizeParts[83] | 0x3070000;
				*((BYTE*)_CustomizeParts + 456) = 1;
				cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizeSubPkg, PackageSwitchArg, 0, 0); // CustomizeCategory
			}
		}
		else if (MenuID <= 0x401 || MenuID > 0x4FF)
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
		if (MenuID == 0x307)
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
			if (MenuID == 0x307) // Custom Gauges
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
				if (MenuID <= 0x401 || MenuID > 0x4FF)
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
		if (MenuID == 0x109)
		{
			if (RenderFECarFlares == 1)
			{
				RenderFECarFlares = -1;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x70DFE5C2); // Text, COMMON_OFF
			}
			else if (RenderFECarFlares == -1)
			{
				RenderFECarFlares = 1;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x417B2604); // Text, COMMON_ON
			}
		}
		else if (MenuID == 0x10A)
		{
			switch (RenderFECarFlares)
			{
			default:
			case -1:
				RenderFECarFlares = 2;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x6AB80AFA); // Text, BUTTON_BRAKE_REVERSE
				break;
			case 0:
				RenderFECarFlares = -1;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x70DFE5C2); // Text, COMMON_OFF
				break;
			case 2:
				RenderFECarFlares = 0;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x417B2604); // Text, COMMON_ON
				break;
			}
		}
		break;

	case 0xD9FEEC59: // PAD_RTRIGGER
		if (MenuID == 0x109)
		{
			if (RenderFECarFlares == 1)
			{
				RenderFECarFlares = -1;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x70DFE5C2); // Text, COMMON_OFF
			}
			else if (RenderFECarFlares == -1)
			{
				RenderFECarFlares = 1;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x417B2604); // Text, COMMON_ON
			}
		}
		else if (MenuID == 0x10A)
		{
			switch (RenderFECarFlares)
			{
			default:
			case -1:
				RenderFECarFlares = 0;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x417B2604); // Text, COMMON_ON
				break;
			case 0:
				RenderFECarFlares = 2;
				FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x6AB80AFA); // Text, BUTTON_BRAKE_REVERSE
				break;
			case 2:
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

	//if (MenuID == 0x109) RenderFECarFlares = 1; // Headlights
	//else if (MenuID == 0x10A) RenderFECarFlares = 2; // Taillights
	//else RenderFECarFlares = -1;
	if (MenuID == 0x109 || MenuID == 0x10A)
	{
		FEngSetVisible(FEngFindObject((const char*)_CustomizeParts[4], 0x53639A10)); // Switcher
		FEngSetVisible(FEngFindObject((const char*)_CustomizeParts[4], 0x2C3CC2D3)); // bg

		switch (RenderFECarFlares)
		{
		case 0:
			FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x417B2604); // Text, COMMON_ON
			break;
		case 1:
			FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x417B2604); // Text, COMMON_ON
			break;
		case 2:
			FEngSetLanguageHash((const char*)_CustomizeParts[4], 0x889BACB6, 0x6AB80AFA); // Text, BUTTON_BRAKE_REVERSE
			break;
		case -1:
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
		

			if (_CustomizeParts[82] == 0x307) // Custom Gauges
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

			DWORD LanguageHash = CarPart_GetAppliedAttributeUParam((DWORD*)(SelectedPart[3]), bStringHash("LANGUAGEHASH"), 0);
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
	DWORD* ACarPart;
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

	// Read Part Options for the car
	sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
	CIniReader CarINI(CarININame);
	CIniReader GeneralINI("UnlimiterData\\_General.ini");

	// Vinyls
	if (MenuID >= 0x402 && MenuID <= 0x4FF)
	{
		CarSlotID = 77;

		CIniReader VinylGroupsINI("UnlimiterData\\_VinylGroups.ini");
		sprintf(VinylBrandID, "Group%d", MenuID - 0x402);
		sprintf(VinylBrandIcon, VinylGroupsINI.ReadString(VinylBrandID, "Texture", GetDefaultVinylGroupTexture(MenuID - 0x402)));
		sprintf(VinylBrandString, VinylGroupsINI.ReadString(VinylBrandID, "String", GetDefaultVinylGroupString(MenuID - 0x402)));
		PartCategory = VinylGroupsINI.ReadInteger(VinylBrandID, "Index", GetDefaultVinylGroupIndex(MenuID - 0x402));

		PartIconNormal = bStringHash(VinylBrandIcon);
		_CustomizeParts[87] = bStringHash(VinylBrandString);
		
		if (dword_9BA080) TheActiveCarPart = (DWORD*)dword_9BA080[3];
		else TheActiveCarPart = CarCustomizeManager_GetActivePartFromSlot((DWORD*)_gCarCustomizeManager, CarSlotID);

	}
	else
	{
		switch (MenuID) // Other parts
		{
		case 0x101:
			CarSlotID = 23; // BODY
			PartIconNormal = CustomizeIsInBackRoom() != 0
				? GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPartsBodyKits", "MARKER_ICON_PARTS_BODYKITS")
				: GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsBodyKits", "VISUAL_PART_BODY");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsBodyKits", "CO_BODY_KITS");
			break;

		case 0x104:
			CarSlotID = 63; // HOOD
			PartIconNormal = CustomizeIsInBackRoom() != 0
				? GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPartsHoods", "MARKER_ICON_PARTS_HOODS")
				: GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsHoods", "VISUAL_PART_HOOD");
			PartIconCF = CustomizeIsInBackRoom() != 0
				? GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPartsHoodsCF", "MARKER_ICON_PARTS_CF_HOODS")
				: GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsHoodsCF", "VISUAL_PART_HOOD_CARBON");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsHoods", "CO_HOODS");
			break;

		case 0x105:
			CarSlotID = 62; // ROOF
			PartIconNormal = CustomizeIsInBackRoom() != 0
				? GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPartsRoofScoops", "MARKER_ICON_PARTS_ROOFSCOOPS")
				: GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsRoofScoops", "VISUAL_PART_ROOF_SCOOP");
			PartIconCF = CustomizeIsInBackRoom() != 0
				? GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPartsRoofScoopsCF", "MARKER_ICON_PARTS_CF_ROOFSCOOPS")
				: GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsRoofScoopsCF", "VISUAL_PART_ROOF_SCOOP_CARBON");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsRoofScoops", "CO_ROOF_SCOOPS");
			break;

		case 0x106:
			CarSlotID = 28; // INTERIOR
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsInterior", "VISUAL_PART_INTERIOR");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsInterior", "CO_INTERIOR");
			break;

		case 0x107: // Roof
			CarSlotID = 0; // BASE
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsRoof", "VISUAL_PART_ROOF");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsRoof", "CO_ROOF");
			break;

		case 0x108: // Brake
			CarSlotID = 24; // FRONT_BRAKE
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsBrakes", "VISUAL_PART_BRAKE");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsBrakes", "CO_BRAKES");
			break;

		case 0x109: // Headlight
			CarSlotID = 31; // LEFT_HEADLIGHT
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsHeadlights", "VISUAL_PART_HEAD_LIGHTS");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsHeadlights", "CO_HEADLIGHTS");
			break;

		case 0x10A: // Brakelight
			CarSlotID = 29; // LEFT_BRAKELIGHT
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsTaillights", "VISUAL_PART_TAIL_LIGHTS");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsTaillights", "CO_TAILLIGHTS");
			break;

		case 0x10B: // Mirror
			CarSlotID = 33; // LEFT_SIDE_MIRROR
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsMirrors", "VISUAL_PART_SIDE_MIRROR");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsMirrors", "CO_SIDE_MIRROR");
			break;

		case 0x10D: // Attachment 1
			CarSlotID = 52; // ATTACHMENT0
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsAttachment0", "VISUAL_PART_ATTACHMENT");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachment0", "CO_ATTACHMENT_1");
			break;

		case 0x10E: // Attachment 2
			CarSlotID = 53; // ATTACHMENT1
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsAttachment1", "VISUAL_PART_ATTACHMENT");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachment1", "CO_ATTACHMENT_2");
			break;

		case 0x10F: // Attachment 3
			CarSlotID = 54; // ATTACHMENT2
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsAttachment2", "VISUAL_PART_ATTACHMENT");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachment2", "CO_ATTACHMENT_3");
			break;

		case 0x110: // Attachment 4
			CarSlotID = 55; // ATTACHMENT3
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsAttachment3", "VISUAL_PART_ATTACHMENT");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachment3", "CO_ATTACHMENT_4");
			break;

		case 0x111: // Attachment 5
			CarSlotID = 56; // ATTACHMENT4
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsAttachment4", "VISUAL_PART_ATTACHMENT");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachment4", "CO_ATTACHMENT_5");
			break;

		case 0x112: // Attachment 6
			CarSlotID = 57; // ATTACHMENT5
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsAttachment5", "VISUAL_PART_ATTACHMENT");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachment5", "CO_ATTACHMENT_6");
			break;

		case 0x113: // Attachment 7
			CarSlotID = 58; // ATTACHMENT6
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsAttachment6", "VISUAL_PART_ATTACHMENT");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachment6", "CO_ATTACHMENT_7");
			break;

		case 0x114: // Attachment 8
			CarSlotID = 59; // ATTACHMENT7
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsAttachment7", "VISUAL_PART_ATTACHMENT");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachment7", "CO_ATTACHMENT_8");
			break;

		case 0x115: // Attachment 9
			CarSlotID = 60; // ATTACHMENT8
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsAttachment8", "VISUAL_PART_ATTACHMENT");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachment8", "CO_ATTACHMENT_9");
			break;

		case 0x116: // Attachment 10
			CarSlotID = 61; // ATTACHMENT9
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "PartsAttachment9", "VISUAL_PART_ATTACHMENT");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "PartsAttachment9", "CO_ATTACHMENT_10");
			break;

		case 0x304: // Window Tint
			CarSlotID = 131; // WINDOW_TINT
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualWindowTint", "VISUAL_PART_WINDOW_TINTING");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualWindowTint", "CO_WINDOW_TINT");
			break;

		case 0x307: // Custom Gauges

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

			CarSlotID = 132; // CUSTOM_HUD
			PartIconNormal = CustomizeIsInBackRoom() != 0
				? GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomVisualCustomGauges", "MARKER_ICON_VISUAL_HUD")
				: GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualCustomGauges", "VISUAL_PART_HUDS");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualCustomGauges", "CO_CUSTOM_HUD");
			break;

		case 0x308: // Drivers
			CarSlotID = 43; // DRIVER
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualDriver", "VISUAL_PART_DRIVER");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualDriver", "CO_DRIVER");
			break;

		case 0x309: // License Plates
			CarSlotID = 69; // LICENSE_PLATE
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualLicensePlate", "VISUAL_PART_LICENSE_PLATE");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualLicensePlate", "CO_LICENSE_PLATE");
			break;

		case 0x314: // Tires
			CarSlotID = 64; // HEADLIGHT
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualTires", "VISUAL_PART_TIRE");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualTires", "CO_TIRES");
			break;

		case 0x315: // Neon
			CarSlotID = 65; // BRAKELIGHT
			PartIconNormal = GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "VisualNeon", "VISUAL_PART_NEON");
			_CustomizeParts[87] = GetCarTextOptionHash(CarINI, GeneralINI, "Names", "VisualNeon", "CO_NEON");
			break;

		case 0x316: // Empty Slot
			CarSlotID = 68; // SPINNER
			PartIconNormal = bStringHash("VISUAL_PART_SPINNER");
			_CustomizeParts[87] = bStringHash("CO_SPINNER");
			break;

		case 0x317: // Empty Slot
			CarSlotID = 137; // WHEEL_MANUFACTURER
			PartIconNormal = bStringHash("VISUAL_PART_WHEEL_MANUFACTURER");
			_CustomizeParts[87] = bStringHash("CO_WHEEL_MANUFACTURER");
			break;

		case 0x318: // Empty Slot
			CarSlotID = 138; // MISC
			PartIconNormal = bStringHash("VISUAL_PART_MISC");
			_CustomizeParts[87] = bStringHash("CO_MISC");
			break;
		}

		if (MenuID == 0x307 && dword_9BA080) TheActiveCarPart = (DWORD*)dword_9BA080[3];
		else TheActiveCarPart = CarCustomizeManager_GetActivePartFromSlot((DWORD*)_gCarCustomizeManager, CarSlotID);
	}

AddToList:
	// Initialize the list
	SelectablePartsList[0] = (DWORD)SelectablePartsList; // Next
	SelectablePartsList[1] = (DWORD)SelectablePartsList; // Prev
	//v31 = 0;

	if (CarSlotID != 77) PartCategory = 0; // VINYL_LAYER0

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
			UnlockHash = CarCustomizeManager_GetUnlockHash((DWORD*)_gCarCustomizeManager, _CustomizeParts[82], v12);

			if (CarSlotID != 77) break; // VINYL_LAYER0

			ACarPart = (DWORD*)TheSelectablePart[3];
			if ((*((BYTE*)ACarPart + 5) & 0x1F) == PartCategory) goto LABEL_46;

			(**(void(__thiscall***)(DWORD*, int))TheSelectablePart)(TheSelectablePart, 1); // Refresh the part??

		LABEL_50:
			v8 = (DWORD*)SelectablePartsList[0];
			if ((DWORD*)SelectablePartsList[0] == SelectablePartsList)
				goto LABEL_51;
		}

		ACarPart = (DWORD*)TheSelectablePart[3];

	LABEL_46:
		// Choose Part Icon
		PartIconCustom = CarPart_GetAppliedAttributeIParam(ACarPart, bStringHash("TEXTUREHASH"), 0);
		if (PartIconCustom) NewPartIcon = PartIconCustom;
		else if (CarPart_GetAppliedAttributeIParam(ACarPart, bStringHash("CARBONFIBRE"), 0) && PartIconCF) NewPartIcon = PartIconCF;
		else NewPartIcon = PartIconNormal;
	
		PartName = *(BYTE*)(TheSelectablePart[3] + 5) >> 5;
		IsLocked = CarCustomizeManager_IsPartLocked((DWORD*)_gCarCustomizeManager, TheSelectablePart, 0);
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