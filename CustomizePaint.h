#include "stdio.h"
#include "InGameFunctions.h"

#define dword_9BA080 *(DWORD*)0x9BA080

void __fastcall CustomizePaint_RefreshHeader(DWORD* CustomizePaint, void* EDX_Unused)
{
    DWORD* PaintCostCareerGroup; // eax
    DWORD* PaintCategoryNameObject; // eax
    DWORD* PaintHeatLevelCareerGroup; // eax
    DWORD CurrColorSelectorID; // eax
    int PaintCategoryNameHash; // ecx
    DWORD CurrColorSelectorIDMinus1; // eax
    DWORD* PaintCategoryArrows; // eax MAPDST
    int CurrVinylColorID; // ebx
    DWORD* CurrVinylColorSelectablePart; // edi
    DWORD* SelectedPaintCarPart; // edi MAPDST
    DWORD* SelectedPaintSelectablePart; // eax MAPDST
    DWORD* CustomizePaintDatum; // eax
    DWORD* CustomizePaintDatumOffset; // eax
    int SelectedItemNumber; // eax
    unsigned int PaintUnlockData; // ebx
    int LastItemNumber; // [esp-Ch] [ebp-18h]

    DWORD* CustomizationScreenHelper = (DWORD*)(CustomizePaint + 85);
    CustomizationScreenHelper_DrawTitle(CustomizationScreenHelper);

	int MenuCategoryID = CustomizePaint[82];
	int VinylColorCount = CustomizePaint[184];

	char const* CustomizePaintPackage = (const char*)CustomizePaint[4];

    if (bList_TraversebList(CustomizePaint + 140, 0) > 0)
    {
        (*(void(__thiscall**)(DWORD*))(CustomizePaint[136] + 8))(CustomizePaint + 136); // ArrayScroller::RefreshHeader
        CurrColorSelectorID = CustomizePaint[111];
        PaintCategoryNameHash = 0;
        
		switch (MenuCategoryID)
		{
		case 0x301: // Body Paint
			switch (CurrColorSelectorID)
			{
			case 0:
				PaintCategoryNameHash = 0xB6763CDE; // CP_FILTER_GLOSS
				break;
			case 1:
				PaintCategoryNameHash = 0x452B5481; // CP_FILTER_METALLIC
				break;
			case 2:
				PaintCategoryNameHash = 0xB715070A; // CP_FILTER_PEARL
				break;
			}
			SelectedPaintCarPart = *(DWORD**)((*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint) + 12);
			SelectedPaintSelectablePart = (DWORD*)(*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint); // GetSelectedPart
			CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, *((DWORD*)SelectedPaintSelectablePart + 4), SelectedPaintCarPart);
			break;
		case 0x303: // Rim Paint
			PaintCategoryNameHash = 0xB3100A3E; // CP_FILTER_RIM

			SelectedPaintCarPart = *(DWORD**)((*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint) + 12);
			SelectedPaintSelectablePart = (DWORD*)(*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint); // GetSelectedPart
			CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, *((DWORD*)SelectedPaintSelectablePart + 4), SelectedPaintCarPart);

			PaintCategoryArrows = FEngFindObject(CustomizePaintPackage, 0x2C526172);
			FEngSetInvisible(PaintCategoryArrows);
			break;
		default: // Vinyls
			switch (CurrColorSelectorID)
			{
			case 0:
				switch (VinylColorCount)
				{
				case 1:
					PaintCategoryNameHash = 0xD8EE1A80; // CO_VINYL_COLOR
					break;
				case 2:
					PaintCategoryNameHash = 0x5198BA16; // CP_FILTER_COLOR_1_2
					break;
				case 3:
					PaintCategoryNameHash = 0x5198BA17; // CP_FILTER_COLOR_1_3
					break;
				}
				break;
			case 1:
				switch (VinylColorCount)
				{
				case 2:
					PaintCategoryNameHash = 0x5198BE57; // CP_FILTER_COLOR_2_2
					break;
				case 3:
					PaintCategoryNameHash = 0x5198BE58; // CP_FILTER_COLOR_2_3
					break;
				}
				break;
			case 2:
				PaintCategoryNameHash = 0x5198C299; // CP_FILTER_COLOR_3_3
				break;
			}

			CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, *(DWORD*)(dword_9BA080 + 16), *(DWORD**)(dword_9BA080 + 12));

			if (VinylColorCount == 1)
			{
				PaintCategoryArrows = FEngFindObject(CustomizePaintPackage, 0x2C526172);
				FEngSetInvisible(PaintCategoryArrows);
			}
			CurrVinylColorID = 0;
			CurrVinylColorSelectablePart = CustomizePaint + 181;
			do
			{
				if (CurrVinylColorID < VinylColorCount && *CurrVinylColorSelectablePart) CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, *(DWORD*)(*CurrVinylColorSelectablePart + 16), *(DWORD**)(*CurrVinylColorSelectablePart + 12));
				++CurrVinylColorID;
				++CurrVinylColorSelectablePart;
			} while (CurrVinylColorID < 3);
			SelectedPaintCarPart = *(DWORD**)((*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint) + 12);
			SelectedPaintSelectablePart = (DWORD*)(*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint); // GetSelectedPart
			CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, *((DWORD*)SelectedPaintSelectablePart + 4), SelectedPaintCarPart);
			break;
		}

		FEngSetLanguageHash(CustomizePaintPackage, 0x78008599, PaintCategoryNameHash);
        
        SelectedPaintSelectablePart = (DWORD*)(*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint);
        CustomizationScreenHelper_SetCareerStuff(CustomizationScreenHelper, SelectedPaintSelectablePart, MenuCategoryID, 0);
        CustomizePaintDatum = (DWORD*)CustomizePaint[142];
		if (CustomizePaintDatum)
		{
			CustomizePaintDatumOffset = (DWORD*)(CustomizePaintDatum + 1);
			PaintUnlockData = CustomizePaintDatum[7];
		}
		else
		{
			CustomizePaintDatumOffset = 0;
			PaintUnlockData = 0;
		}
            
        SelectedItemNumber = bList_TraversebList(CustomizePaint + 140, CustomizePaintDatumOffset);
        LastItemNumber = bList_TraversebList(CustomizePaint + 140, 0);
        SelectedPaintSelectablePart = (DWORD*)(*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint);
        CustomizationScreenHelper_SetPartStatus(CustomizationScreenHelper, SelectedPaintSelectablePart, PaintUnlockData, SelectedItemNumber, LastItemNumber);
    }
    else
    {
        PaintCostCareerGroup = FEngFindObject(CustomizePaintPackage, 0x8D1559A4);
        FEngSetInvisible(PaintCostCareerGroup);
        PaintCategoryNameObject = FEngFindObject(CustomizePaintPackage, 0x78008599);
        FEngSetInvisible(PaintCategoryNameObject);
        PaintHeatLevelCareerGroup = FEngFindObject(CustomizePaintPackage, 0xF2492598);
        FEngSetInvisible(PaintHeatLevelCareerGroup);
    }

	// refresh paints
	for (int i = 0; i < 80; i++)
	{
		DWORD* PaintSlot = ArrayScroller_GetSlotAt(CustomizePaint + 136, i);
		int j = i + CustomizePaint[143]; // StartDatumID

		if (PaintSlot)
		{
			DWORD* PaintDatum = ArrayScroller_GetDatumAt(CustomizePaint + 136, j);
			if (PaintDatum)
			{
				SelectedPaintCarPart = *(DWORD**)(PaintDatum[6] + 12);
				BYTE Red = (BYTE)CarPart_GetAppliedAttributeIParam(SelectedPaintCarPart, bStringHash("RED"), 0);
				BYTE Green = (BYTE)CarPart_GetAppliedAttributeIParam(SelectedPaintCarPart, bStringHash("GREEN"), 0);
				BYTE Blue = (BYTE)CarPart_GetAppliedAttributeIParam(SelectedPaintCarPart, bStringHash("BLUE"), 0);

				FEngSetColor_obj(*(DWORD**)(PaintSlot + 3), Blue | (((unsigned __int8)Green | ((Red | 0xFFFFFF00) << 8)) << 8));
			}
		}
	}
}