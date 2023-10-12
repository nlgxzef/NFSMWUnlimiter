#include "stdio.h"
#include "InGameFunctions.h"
#include "CarCustomizeManager.h"
#include "Helpers.h"

// 0x7A65C0
char CustomizeMain_SetScreenNames()
{
	char result; // al

	result = CustomizeIsInBackRoom();
	if (result)
	{
		*(DWORD*)g_pCustomizeSubPkg = 0x89FA88;					// "CustomizeCategory_BACKROOM.fng"
		*(DWORD*)g_pCustomizeSubTopPkg = 0x89FA4C;				// "CustomizeGenericTop_BACKROOM.fng"
		*(DWORD*)g_pCustomizePartsPkg = 0x89F9D8;				// "CustomizeParts_BACKROOM.fng"
		*(DWORD*)g_pCustomizePerfPkg = 0x89F8AC;				// "CustomizePerformance_BACKROOM.fng"
		*(DWORD*)g_pCustomizeDecalsPkg = 0x89F960;				// "Decals_BACKROOM.fng"
		*(DWORD*)g_pCustomizePaintPkg = 0x89F934;				// "Paint_BACKROOM.fng"
		*(DWORD*)g_pCustomizeRimsPkg = 0x89F914;				// "Rims_BACKROOM.fng"
		*(DWORD*)g_pCustomizeHudColorPkg = 0x89F980;			// "CustomHUDColor_BACKROOM.fng"
		*(DWORD*)g_pCustomizeHudPkg = 0x89F9B0;					// "CustomHUD_BACKROOM.fng"
		*(DWORD*)g_pCustomizeSpoilerPkg = 0x89F8EC;				// "Spoilers_BACKROOM.fng"
		*(DWORD*)g_pCustomizeShoppingCartPkg = CarCustomizeManager_IsCareerMode() ? 0x89FA08 /* "ShoppingCart_BACKROOM.fng" */ : 0x89FA24 /* "ShoppingCart_QR.fng" */;
	}
	else
	{
		*(DWORD*)g_pCustomizeSubPkg = 0x89FAA8;					// "CustomizeCategory.fng"
		*(DWORD*)g_pCustomizeSubTopPkg = 0x89FA70;				// "CustomizeGenericTop.fng"
		*(DWORD*)g_pCustomizePartsPkg = 0x89F9F4;				// "CustomizeParts.fng"
		*(DWORD*)g_pCustomizePerfPkg = 0x89F8D0;				// "CustomizePerformance.fng"
		*(DWORD*)g_pCustomizeDecalsPkg = 0x89F974;				// "Decals.fng"
		*(DWORD*)g_pCustomizePaintPkg = 0x89F948;				// "Paint.fng"
		*(DWORD*)g_pCustomizeRimsPkg = 0x89F928;				// "Rims.fng"
		*(DWORD*)g_pCustomizeHudColorPkg = 0x89F99C;			// "CustomHUDColor.fng"
		*(DWORD*)g_pCustomizeHudPkg = 0x89F9C8;					// "CustomHUD.fng"
		*(DWORD*)g_pCustomizeSpoilerPkg = 0x89F904;				// "Spoilers.fng"
		*(DWORD*)g_pCustomizeShoppingCartPkg = CarCustomizeManager_IsCareerMode() ? 0x89FA38 /* "ShoppingCart.fng" */ : 0x89FA24 /* "ShoppingCart_QR.fng" */ ;
	}
	return result;
}

// 0x7B1226
void __declspec(naked) MyCarsBackroomWidgetCodeCave()
{
	_asm
	{
		cmp byte ptr ds : [eax+0x12C],0x20 // In My cars
		jne originalcode
		call CustomizeIsInBackRoom
		test al, al
		jz loc_7B125F // Show backroom widget

		originalcode:
			mov al, byte ptr ds: [g_bTestCareerCustomization]
			push 0x7B122B
			retn

		loc_7B125F:
			push 0x7B125F
			retn
	}
}

// 0x7BFE2F
void __declspec(naked) MyCarsBackroomEscCodeCave()
{
	_asm
	{
		call CustomizeIsInBackRoom
		test al,al
		jnz loc_7BFFE2 // Switch rooms

		call CarCustomizeManager_IsCareerMode
		test al, al
		jz loc_7BFEC2 // Career Mode

		caveexit:
			push 0x7BFE4C
			retn

		loc_7BFEC2 :
			push 0x7BFEC2
			retn

		loc_7BFFE2 :
			push 0x7BFFE2
			retn
	}
}

// 0x7BFCC2
void __declspec(naked) MyCarsBackroomRoomChangeCodeCave()
{
	_asm
	{
		call cFEng_QueuePackageMessage
		call CarCustomizeManager_IsCareerMode
		test al, al
		jnz CareerMode

		MyCars:
			push 1
			jmp caveexit

		CareerMode:
			push 3
			jmp caveexit

		caveexit:
			push 0x7BFCC9
			retn
	}
}

// 0x7A60F0
void __declspec(naked) MyCarsBackroomRoomChangeCodeCave2()
{
	_asm
	{
		add esp,4
		call CarCustomizeManager_IsCareerMode
		test al,al
		jnz CareerMode

		MyCars :
			push 1
			jmp caveexit

		CareerMode :
			push 3
			jmp caveexit

		caveexit :
			push 0x7A60F5
			retn
	}
}

void __fastcall CustomizeMain_BuildOptionsList(DWORD* CustomizeMain, void* EDX_Unused)
{
	// Fix camera angle variable
	DWORD* TheGarageMainScreen = GarageMainScreen_GetInstance();
	if (TheGarageMainScreen) TheGarageMainScreen[34] = 0;
	
	// Get CarType Info
	void* FECarRecord = *(void**)_FECarRecord;
	int CarTypeID = FECarRecord_GetType(FECarRecord);
	sprintf(CarTypeName, GetCarTypeName(CarTypeID));

	if (IsMenuEmpty_CustomizeMain(CarTypeID)) // Throw an error and add a dummy option if the menu is empty
	{
		CustomizeCategoryScreen_AddCustomOption(CustomizeMain, (char const*)CustomizeMain[4],
			bStringHash((char*)"BROWSER_NOT_APPLICABLE"),
			bStringHash((char*)"NOT_APPLICABLE"),
			0);

		DialogInterface_ShowOk((char const*)CustomizeMain[4], "", 1, bStringHash((char*)"CUSTOMIZE_NO_OPTIONS"));
	}
		

	if (CustomizeIsInBackRoom())
	{
		if (!HPCCompatibility)
		{
			if (CarConfigs[CarTypeID].Category.Parts && !IsMenuEmpty_PartsBackroom(CarTypeID))
			CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
				CarConfigs[CarTypeID].Icons.BackroomParts,
				CarConfigs[CarTypeID].Names.Parts,
				MenuID::CustomizeCategory_Parts); // Body Backroom

			if (CarConfigs[CarTypeID].Category.Performance && !IsMenuEmpty_Performance(CarTypeID))
			CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
				CarConfigs[CarTypeID].Icons.BackroomPerformance,
				CarConfigs[CarTypeID].Names.Performance,
				MenuID::CustomizeCategory_Performance); // Performance Backroom
		}
		if (CarConfigs[CarTypeID].Category.Visual && !IsMenuEmpty_VisualBackroom(CarTypeID))
		CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
			CarConfigs[CarTypeID].Icons.BackroomVisual,
			CarConfigs[CarTypeID].Names.Visual,
			MenuID::CustomizeCategory_Visual); // Visuals Backroom
	}
	else
	{
		if (!HPCCompatibility)
		{
			if (CarConfigs[CarTypeID].Category.Parts && !IsMenuEmpty_Parts(CarTypeID))
			CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
				CarConfigs[CarTypeID].Icons.Parts,
				CarConfigs[CarTypeID].Names.Parts,
				MenuID::CustomizeCategory_Parts); // Body

			if (CarConfigs[CarTypeID].Category.Performance && !IsMenuEmpty_Performance(CarTypeID))
			CustomizeMain[106] = CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
				CarConfigs[CarTypeID].Icons.Performance,
				CarConfigs[CarTypeID].Names.Performance,
				MenuID::CustomizeCategory_Performance); // Performance
		}
		if (CarConfigs[CarTypeID].Category.Visual && !IsMenuEmpty_Visual(CarTypeID))
		CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
			CarConfigs[CarTypeID].Icons.Visual,
			CarConfigs[CarTypeID].Names.Visual,
			MenuID::CustomizeCategory_Visual); // Visuals
	}
}

void __fastcall CustomizeMain_SwitchRooms(DWORD* _CustomizeMain, void* EDX_Unused)
{
	bool InBackroom; // bl
	DWORD* TheIconScroller; // esi
	int CurrIndex; // ebp
	DWORD* TheFEManager; // eax
	int GarageType; // [esp-4h] [ebp-18h]

	InBackroom = CustomizeIsInBackRoom() == 0;
	CustomizeSetInBackRoom(InBackroom);
	CustomizeMain_SetTitle(_CustomizeMain, InBackroom);
	TheIconScroller = _CustomizeMain + 11;
	
	CurrIndex = _CustomizeMain[14] ? (*(int(__thiscall**)(DWORD*, DWORD))(*TheIconScroller + 36))(_CustomizeMain + 11, _CustomizeMain[14]) : 0; // IconScroller::GetOptionIndex
	
	cFEng_QueuePackageMessage(*(int**)cFEng_mInstance, InBackroom ? 0xA1CAFF8D : 0x5C01C5, (const char*)_CustomizeMain[4], 0);

	if (InBackroom) GarageType = 4;
	else
	{
		cFEng_QueuePackageMessage(*(int**)cFEng_mInstance, 0x5C01C5, (const char*)_CustomizeMain[4], 0);
		GarageType = CarCustomizeManager_IsCareerMode_CheckTCC() ? 3 : 1;
	}

	TheFEManager = FEManager_Get();
	FEManager_SetGarageType(TheFEManager, GarageType);
	CustomizeMain_SetScreenNames();
	(*(void(__thiscall**)(DWORD*))(*TheIconScroller + 12))(_CustomizeMain + 11); // IconScroller::RemoveAll
	(*(void(__thiscall**)(DWORD*))(*TheIconScroller + 60))(_CustomizeMain + 11); // IconScroller::AddInitialBookEnds
	CustomizeMain_BuildOptionsList(_CustomizeMain, EDX_Unused);
	if (*((BYTE*)_CustomizeMain + 297))
	{
		*((BYTE*)_CustomizeMain + 284) = 0;
		*((BYTE*)_CustomizeMain + 281) = 1;
		*((BYTE*)_CustomizeMain + 282) = 0;
		_CustomizeMain[68] = 0;
	}
	(*(void(__thiscall**)(DWORD*, int))(*TheIconScroller + 64))(_CustomizeMain + 11, CurrIndex); // IconScroller::SetInitialPos
	(*(void(__thiscall**)(DWORD*))(*_CustomizeMain + 12))(_CustomizeMain); // CustomizeMain::RefreshHeader
}

void __fastcall CustomizeMain_NotificationMessage(DWORD* _CustomizeMain, void* EDX_Unused, DWORD Message, DWORD* FEObject, DWORD param1, DWORD param2)
{
	int NumMarkers; // eax
	int JoyPort; // al

	DWORD* GarageMainScreen = FEngFindScreen("GarageMain.fng");
	DWORD* FEDatabase = *(DWORD**)_FEDatabase;
	bool TestCareerCustomization = *(bool*)g_bTestCareerCustomization;
	bool IsInCareerMode = CarCustomizeManager_IsCareerMode_CheckTCC();
	BYTE* MemoryCard_s_pThis = *(BYTE**)_MemoryCard_s_pThis;

	if (!CustomizeIsInBackRoom() || Message != 0x911AB364) CustomizeCategoryScreen_NotificationMessage(_CustomizeMain, Message, FEObject, param1, param2);

	switch (Message)
	{
	case 0x911AB364: // PAD_BACK
		if (CustomizeIsInBackRoom())
		{
			CustomizeMain_SwitchRooms(_CustomizeMain, EDX_Unused);
		}
		else
		{
			cFEng_QueuePackageMessage(*(int**)cFEng_mInstance, 0x6D5D86A1, (const char*)_CustomizeMain[4], 0);
			if (IsInCareerMode) // Is Career Mode
			{
				if (GarageMainScreen) *(DWORD*)(GarageMainScreen + 34) = -1;
				JoyPort = FEngMapJoyParamToJoyport(param1);
				cFrontendDatabase_SetPlayersJoystickPort(FEDatabase, 0, JoyPort);
				if (!cFrontendDatabase_IsCarStableDirty(FEDatabase))
					*((BYTE*)MemoryCard_s_pThis + 43) = 1;
				*(int*)_CarViewer_haveLoadedOnce = 0;
				RaceStarter_StartCareerFreeRoam();
			}
			CarCustomizeManager_RelinquishControl((DWORD*)_gCarCustomizeManager);
		}
		break;

	case 0x1265ECE9:
		GarageMainScreen_UpdateCurrentCameraView(GarageMainScreen, 0);
		cFEng_QueuePackageMessage(*(int**)cFEng_mInstance, CustomizeIsInBackRoom() ? 0xA1CAFF8D : 0x5C01C5, (const char*)_CustomizeMain[4], 0);
		break;

	case 0x34DC1BEC: // OK to MISSING_PARTS_MARKER dialog
		NumMarkers = IsInCareerMode ? FEMarkerManager_GetNumCustomizeMarkers((DWORD*)TheFEMarkerManager) : (MyCarsBackroom || TestCareerCustomization) ? 1 : 0;
		if (NumMarkers > _CustomizeMain[107]) CustomizeMain_SwitchRooms(_CustomizeMain, EDX_Unused);
		_CustomizeMain[107] = 0;
		break;

	case 0xC519BFC4: // PAD_BUTTON5
		if (IsInCareerMode || MyCarsBackroom)
		{
			NumMarkers = IsInCareerMode ? FEMarkerManager_GetNumCustomizeMarkers((DWORD*)TheFEMarkerManager) : (MyCarsBackroom || TestCareerCustomization) ? 1 : 0;

			if (!CustomizeIsInBackRoom() && NumMarkers)
			{
				_CustomizeMain[107] = 0;
				if (FEMarkerManager_IsMarkerAvailable((DWORD*)TheFEMarkerManager, 4, 0) && !CarCustomizeManager_CanInstallJunkman((DWORD*)_gCarCustomizeManager, 5))
				{
					++_CustomizeMain[107];
				}
				if (FEMarkerManager_IsMarkerAvailable((DWORD*)TheFEMarkerManager, 3, 0) && !CarCustomizeManager_CanInstallJunkman((DWORD*)_gCarCustomizeManager, 6))
				{
					++_CustomizeMain[107];
				}
				if (_CustomizeMain[107] > 0)
				{
					DialogInterface_ShowOneButton((const char*)_CustomizeMain[4], "", 2, 0x417B2601, 0x34DC1BEC, 0x3B3E83); // COMMON_OK, 0x34DC1BEC (OK message??), MISSING_PARTS_MARKER
					return;
				}
				CustomizeMain_SwitchRooms(_CustomizeMain, EDX_Unused);
			}
		}
		break;
	}
}

void __fastcall CustomizeMain_RefreshHeader(DWORD* _CustomizeMain, void* EDX_Unused)
{
	CustomizeCategoryScreen_RefreshHeader(_CustomizeMain);

	bool TestCareerCustomization = *(bool*)g_bTestCareerCustomization;
	bool IsInCareerMode = CarCustomizeManager_IsCareerMode_CheckTCC();

	DWORD* BackroomGroup = (DWORD*)FEngFindObject((const char*)_CustomizeMain[4], 0xDC6EE739); // BACKROOM_GROUP
	int NumMarkers = IsInCareerMode ? FEMarkerManager_GetNumCustomizeMarkers((DWORD*)TheFEMarkerManager) : (MyCarsBackroom || TestCareerCustomization) ? 1 : 0;

	if (!CustomizeIsInBackRoom() && NumMarkers) FEngSetVisible(BackroomGroup);
	else FEngSetInvisible(BackroomGroup);
	
	DWORD* v4 = (DWORD*)_CustomizeMain[14];
	if (v4) CarCustomizeManager_IsCategoryNew((DWORD*)_gCarCustomizeManager, EDX_Unused, (WORD)v4[20]);
}