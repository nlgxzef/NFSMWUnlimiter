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
			case 3:
				PaintCategoryNameHash = bStringHash("CP_FILTER_TRAFFIC"); // CP_FILTER_RIM
				break;
			case 4:
				PaintCategoryNameHash = bStringHash("CP_FILTER_COP"); // CP_FILTER_RIM
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

				FEngSetColor_obj(*(DWORD**)(PaintSlot + 3), Blue | ((Green | ((Red | 0xFFFFFF00) << 8)) << 8));
			}
		}
	}
}

DWORD __fastcall CustomizePaint_CalcBrandHash(DWORD* _CustomizePaint, void* EDX_Unused, DWORD* ActivePaint)
{
	DWORD result;

	int MenuID = _CustomizePaint[82];
	int PaintScrollerIndex = _CustomizePaint[111];

	switch (MenuID)
	{
	case 0x301:
		switch (PaintScrollerIndex)
		{
		case 4:
			result = 0x9B21; // COP
			break;
		case 3:
			result = 0x19E0ECBE; // TRAFFIC
			break;
		case 2:
			result = 0x3797533; // PEARL
			break;
		case 1:
			result = 0x3437A52; // METAL
			break;
		case 0:
			result = 0x2DAAB07; // GLOSS
			break;
		default:
			result = CarPart_GetAppliedAttributeUParam(ActivePaint, 0xEBB03E66, 0); // BRAND_NAME
			break;
		}
		break;

	case 0x303:
		result = 0xDA27; // RIM
		break;

	default:
		result = 0x3E871F1; // VINYL
		break;
	}

	return result;
}

DWORD __fastcall CustomizePaint_CalcIndexFromBrandHash(DWORD* _CustomizePaint, void* EDX_Unused, DWORD BrandHash)
{
	DWORD result = 0;

	switch (BrandHash)
	{
	case 0x9B21:
		result = 4; // COP
		break;
	case 0x19E0ECBE:
		result = 3; // TRAFFIC
		break;
	case 0x3797533:
		result = 2; // PEARL
		break;
	case 0x3437A52:
		result = 1; // METAL
		break;
	case 0x2DAAB07:
	default:
		result = 0; // GLOSS
		break;
	}

	_CustomizePaint[111] = result;
	return result;
}

void __fastcall CustomizePaint_BuildSwatchList(DWORD* _CustomizePaint, void* EDX_Unused, unsigned int CarSlotID)
{
	int VinylColorLayer; // eax
	DWORD* ShowcasePaintPart; // ecx
	unsigned int BrandHash; // eax MAPDST
	bool IsIndexInvalid; // zf
	DWORD* ListItem; // eax
	DWORD* PaintSelectablePart; // eax
	DWORD* NextPaintSelectablePart; // eax
	int Unlockhash; // ebp
	DWORD* PaintDatum; // esi
	DWORD* pl_itm_nxt; // ecx MAPDST
	DWORD* pl_itm; // edx MAPDST
	DWORD* pl_itm_prv; // eax MAPDST
	DWORD* SelectablePartFromDatum; // edi
	DWORD* pItemIndex; // eax
	DWORD* ArraySlot; // ebp
	DWORD* PaintPart; // edi MAPDST
	int AttrNameHash; // eax MAPDST
	unsigned __int8 r; // al MAPDST
	unsigned __int8 b; // al
	DWORD InitialPosition; // eax
	int i; // [esp+Ch] [ebp-24h]
	DWORD* ActivePaint; // [esp+10h] [ebp-20h] MAPDST
	DWORD* PartList[2]; // [esp+1Ch] [ebp-14h] BYREF
	int v38; // [esp+2Ch] [ebp-4h]
	unsigned __int8 g; // [esp+34h] [ebp+4h]

	ArrayScroller_ClearData(_CustomizePaint + 136);
	if (CarSlotID < 79 || CarSlotID > 81)
		goto LABEL_11;
	if (CarSlotID == 79)
		VinylColorLayer = 0;
	else
		VinylColorLayer = CarSlotID == 80 ? 1 : 2;
	ShowcasePaintPart = *(DWORD**)(_Showcase_FromColor + 4 * VinylColorLayer);
	if (!ShowcasePaintPart)
		goto LABEL_11;
	if (_CustomizePaint[VinylColorLayer + 181])
		goto LABEL_11;
	ActivePaint = (DWORD*)ShowcasePaintPart[3];
	if (!ActivePaint)
		LABEL_11:
	ActivePaint = (DWORD*)CarCustomizeManager_GetActivePartFromSlot(
		(DWORD*)_gCarCustomizeManager,
		CarSlotID);
	BrandHash = CustomizePaint_CalcBrandHash(_CustomizePaint, EDX_Unused, ActivePaint);
	IsIndexInvalid = _CustomizePaint[111] == -1;
	if (IsIndexInvalid) CustomizePaint_CalcIndexFromBrandHash(_CustomizePaint, EDX_Unused, BrandHash);

	PartList[0] = (DWORD*)PartList;
	PartList[1] = (DWORD*)PartList;
	v38 = 0;
	CarCustomizeManager_GetCarPartList((DWORD*)_gCarCustomizeManager, CarSlotID, (DWORD*)PartList, 0);
	ListItem = PartList[0];
	for (i = 0; (DWORD**)PartList[0] != PartList; ListItem = PartList[0])
	{
		if (ListItem)
			PaintSelectablePart = ListItem - 1;
		else
			PaintSelectablePart = 0;
		if (CarPart_GetAppliedAttributeUParam((DWORD*)PaintSelectablePart[3], 0xEBB03E66, 0) == BrandHash)
		{
			if (PartList[0])
				NextPaintSelectablePart = PartList[0] - 1;
			else
				NextPaintSelectablePart = 0;
			Unlockhash = CarCustomizeManager_GetUnlockHash(
				(DWORD*)_gCarCustomizeManager,
				_CustomizePaint[82],
				*(BYTE*)(NextPaintSelectablePart[3] + 5) >> 5);
			PaintDatum = (DWORD*)j_malloc(0x20u);
			v38 = 1;
			if (PaintDatum)
			{
				pl_itm_nxt = (DWORD*)*PartList[0];
				pl_itm = PartList[0];
				pl_itm_prv = (DWORD*)PartList[0][1];
				*pl_itm_prv = *PartList[0];
				pl_itm_nxt[1] = (DWORD)pl_itm_prv;
				SelectablePartFromDatum = pl_itm - 1;
				ArrayDatum_ArrayDatum(PaintDatum, 0xC6AFDD7E, 0);
				*PaintDatum = _CustomizePaintDatum_vtable;
					PaintDatum[6] = (DWORD)SelectablePartFromDatum;
				PaintDatum[7] = Unlockhash;
			}
			else
			{
				PaintDatum = 0;
			}
			pItemIndex = &_CustomizePaint[_CustomizePaint[111]%3 + 112];
			IsIndexInvalid = *pItemIndex == -1;
			v38 = 0;
			if (IsIndexInvalid && ActivePaint == *(DWORD**)(PaintDatum[6] + 12))
				*pItemIndex = i;
			ArrayScroller_AddDatum((_CustomizePaint + 136), PaintDatum);
			ArraySlot = (DWORD*)ArrayScroller_GetSlotAt((_CustomizePaint + 136), i);
			if (ArraySlot)
			{
				PaintPart = *(DWORD**)(PaintDatum[6] + 12);
				AttrNameHash = bStringHash("RED");
				r = CarPart_GetAppliedAttributeIParam(PaintPart, AttrNameHash, 0);
				PaintPart = *(DWORD**)(PaintDatum[6] + 12);
				AttrNameHash = bStringHash("GREEN");
				g = CarPart_GetAppliedAttributeIParam(PaintPart, AttrNameHash, 0);
				PaintPart = *(DWORD**)(PaintDatum[6] + 12);
				AttrNameHash = bStringHash("BLUE");
				b = CarPart_GetAppliedAttributeIParam(PaintPart, AttrNameHash, 0);
				FEngSetColor_obj((DWORD*)ArraySlot[3], b | ((g | ((r | 0xFFFFFF00) << 8)) << 8));
			}
			++i;
		}
		else                                        // remove from list
		{
			pl_itm_nxt = (DWORD*)*PartList[0];
			pl_itm = PartList[0];
			pl_itm_prv = (DWORD*)PartList[0][1];
			*pl_itm_prv = *PartList[0];
			pl_itm_nxt[1] = (DWORD)pl_itm_prv;
			if (pl_itm != (DWORD*)4)
				(*(void(__thiscall**)(DWORD*, int)) * (pl_itm - 1))(pl_itm - 1, 1);
		}
	}
	if (*(int*)_Showcase_FromIndex)
	{
		_CustomizePaint[_CustomizePaint[111]%3 + 112] = *(int*)_Showcase_FromIndex - 1;
		ArrayScroller_SetInitialPosition((_CustomizePaint + 136), *(int*)_Showcase_FromIndex - 1);
		*(int*)_Showcase_FromIndex = 0;
	}
	else
	{
		InitialPosition = (DWORD)&_CustomizePaint[_CustomizePaint[111]%3 + 112];
		if (*(DWORD*)InitialPosition == -1)
			*(DWORD*)InitialPosition = 0;
		ArrayScroller_SetInitialPosition(
			(_CustomizePaint + 136),
			_CustomizePaint[_CustomizePaint[111]%3 + 112]);
	}
	(*(void(__thiscall**)(DWORD*))(*_CustomizePaint + 12))(_CustomizePaint);// RefreshHeader
	v38 = -1;
	bTList_SelectablePart_dtor((int**)PartList);
}