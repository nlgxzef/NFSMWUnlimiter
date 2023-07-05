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
	// Get CarType Info
	void* FECarRecord = *(void**)_FECarRecord;
	int CarTypeID = FECarRecord_GetType(FECarRecord);
	sprintf(CarTypeName, GetCarTypeName(CarTypeID));

	// Read Part Options for the car
	sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
	CIniReader CarINI(CarININame);
	CIniReader GeneralINI("UnlimiterData\\_General.ini");

	if (IsMenuEmpty_CustomizeMain(CarINI, GeneralINI)) // Throw an error and add a dummy option if the menu is empty
	{
		CustomizeCategoryScreen_AddCustomOption(CustomizeMain, (char const*)CustomizeMain[4],
			bStringHash("BROWSER_NOT_APPLICABLE"),
			bStringHash("NOT_APPLICABLE"),
			0);

		DialogInterface_ShowOk((char const*)CustomizeMain[4], "", 1, bStringHash("CUSTOMIZE_NO_OPTIONS"));
	}
		

	if (CustomizeIsInBackRoom())
	{
		if (!HPCCompatibility)
		{
			if ((GetCarIntOption(CarINI, GeneralINI, "Main", "Parts", 1)) && !IsMenuEmpty_PartsBackroom(CarINI, GeneralINI))
			CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
				GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomParts", "MARKER_ICON_PARTS"),
				GetCarTextOptionHash(CarINI, GeneralINI, "Names", "Parts", "CO_PARTS"),
				0x801); // Body Backroom

			if ((GetCarIntOption(CarINI, GeneralINI, "Main", "Performance", 1)) && !IsMenuEmpty_Performance(CarINI, GeneralINI))
			CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
				GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomPerformance", "MARKER_ICON_PERFORMANCE"),
				GetCarTextOptionHash(CarINI, GeneralINI, "Names", "Performance", "CO_PERFORMANCE"),
				0x802); // Performance Backroom
		}
		if ((GetCarIntOption(CarINI, GeneralINI, "Main", "Visual", 1)) && !IsMenuEmpty_VisualBackroom(CarINI, GeneralINI))
		CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
			GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "BackroomVisual", "MARKER_ICON_VISUAL"),
			GetCarTextOptionHash(CarINI, GeneralINI, "Names", "Visual", "CO_VISUAL"),
			0x803); // Visuals Backroom
	}
	else
	{
		if (!HPCCompatibility)
		{
			if ((GetCarIntOption(CarINI, GeneralINI, "Main", "Parts", 1)) && !IsMenuEmpty_Parts(CarINI, GeneralINI))
			CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
				GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "Parts", "BROWSER_PARTS"),
				GetCarTextOptionHash(CarINI, GeneralINI, "Names", "Parts", "CO_PARTS"),
				0x801); // Body

			if ((GetCarIntOption(CarINI, GeneralINI, "Main", "Performance", 1)) && !IsMenuEmpty_Performance(CarINI, GeneralINI))
			CustomizeMain[106] = CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
				GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "Performance", "BROWSER_PERFORMANCE"),
				GetCarTextOptionHash(CarINI, GeneralINI, "Names", "Performance", "CO_PERFORMANCE"),
				0x802); // Performance
		}
		if ((GetCarIntOption(CarINI, GeneralINI, "Main", "Visual", 1)) && !IsMenuEmpty_Visual(CarINI, GeneralINI))
		CustomizeCategoryScreen_AddCustomOption(CustomizeMain, *(char**)g_pCustomizeSubPkg,
			GetCarTextOptionHash(CarINI, GeneralINI, "Icons", "Visual", "BROWSER_VISUAL"),
			GetCarTextOptionHash(CarINI, GeneralINI, "Names", "Visual", "CO_VISUAL"),
			0x803); // Visuals
	}
}