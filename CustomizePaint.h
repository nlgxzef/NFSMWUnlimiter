#include "stdio.h"
#include "InGameFunctions.h"

#define dword_9BA080 *(DWORD*)0x9BA080

DWORD __fastcall CustomizePaint_CalcNameHash(DWORD* _CustomizePaint, void* EDX_Unused)
{
	DWORD result = -1;

	int MenuID = _CustomizePaint[82];
	int PaintScrollerIndex = _CustomizePaint[111];
	int VinylColorCount = _CustomizePaint[184];

	// Get CarType Info
	void* FECarRecord = *(void**)_FECarRecord;
	int CarTypeID = FECarRecord_GetType(FECarRecord);

	DWORD* ActiveVinyl;

	switch (MenuID)
	{
	case 0x301:
		if (!PaintScrollerIndex)
		{
			result = CarConfigs[CarTypeID].Names.VisualPaintCustom;
			if (result == -1) result = PaintGroups[PaintScrollerIndex].StringHash;
		}
		else if (PaintScrollerIndex >= PaintGroups.size()) result = -1;
		else result = PaintGroups[PaintScrollerIndex].StringHash;
		break;

	case 0x303:
		result = 0xB3100A3E; // CP_FILTER_RIM
		break;

	default: // Vinyls
		ActiveVinyl = (DWORD*)CarCustomizeManager_GetActivePartFromSlot((DWORD*)_gCarCustomizeManager, 77); // VINYL_LAYER0

		switch (PaintScrollerIndex)
		{
		case 0:
			switch (VinylColorCount)
			{
			case 1:
				result = ActiveVinyl 
					? CarPart_GetAppliedAttributeUParam(ActiveVinyl, bStringHash((char*)"COLOR0LANGUAGEHASH"), 0xD8EE1A80) 
					: 0xD8EE1A80; // CO_VINYL_COLOR
				break;
			case 2:
				result = ActiveVinyl 
					? CarPart_GetAppliedAttributeUParam(ActiveVinyl, bStringHash((char*)"COLOR0LANGUAGEHASH"), 0x5198BA16) 
					: 0x5198BA16; // CP_FILTER_COLOR_1_2
				break;
			case 3:
				result = ActiveVinyl 
					? CarPart_GetAppliedAttributeUParam(ActiveVinyl, bStringHash((char*)"COLOR0LANGUAGEHASH"), 0x5198BA17) 
					: 0x5198BA17; // CP_FILTER_COLOR_1_3
				break;
			case 4:
				result = ActiveVinyl 
					? CarPart_GetAppliedAttributeUParam(ActiveVinyl, bStringHash((char*)"COLOR0LANGUAGEHASH"), 0x5198BA18) 
					: 0x5198BA18; // CP_FILTER_COLOR_1_4
				break;
			}
			break;
		case 1:
			switch (VinylColorCount)
			{
			case 2:
				result = ActiveVinyl
					? CarPart_GetAppliedAttributeUParam(ActiveVinyl, bStringHash((char*)"COLOR1LANGUAGEHASH"), 0x5198BE57)
					: 0x5198BE57; // CP_FILTER_COLOR_2_2
				break;
			case 3:
				result = ActiveVinyl
					? CarPart_GetAppliedAttributeUParam(ActiveVinyl, bStringHash((char*)"COLOR1LANGUAGEHASH"), 0x5198BE58)
					: 0x5198BE58; // CP_FILTER_COLOR_2_3
				break;
			case 4:
				result = ActiveVinyl
					? CarPart_GetAppliedAttributeUParam(ActiveVinyl, bStringHash((char*)"COLOR1LANGUAGEHASH"), 0x5198BE59)
					: 0x5198BE59; // CP_FILTER_COLOR_2_4
				break;
			}
			break;
		case 2:
			switch (VinylColorCount)
			{
			case 3:
				result = ActiveVinyl
					? CarPart_GetAppliedAttributeUParam(ActiveVinyl, bStringHash((char*)"COLOR2LANGUAGEHASH"), 0x5198C299)
					: 0x5198C299; // CP_FILTER_COLOR_3_3
				break;
			case 4:
				result = ActiveVinyl
					? CarPart_GetAppliedAttributeUParam(ActiveVinyl, bStringHash((char*)"COLOR2LANGUAGEHASH"), 0x5198C29A)
					: 0x5198C29A; // CP_FILTER_COLOR_3_4
				break;
			}
			break;
		case 3:
			result = ActiveVinyl
				? CarPart_GetAppliedAttributeUParam(ActiveVinyl, bStringHash((char*)"COLOR3LANGUAGEHASH"), 0x5198C6DB)
				: 0x5198C6DB; // CP_FILTER_COLOR_4_4
			break;
		}
	}

	return result;
}

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

		PaintCategoryNameHash = CustomizePaint_CalcNameHash(CustomizePaint, EDX_Unused);
        
		switch (MenuCategoryID)
		{
		case 0x301: // Body Paint
			SelectedPaintCarPart = *(DWORD**)((*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint) + 12);
			SelectedPaintSelectablePart = (DWORD*)(*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint); // GetSelectedPart
			CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, *((DWORD*)SelectedPaintSelectablePart + 4), SelectedPaintCarPart);
			break;
		case 0x303: // Rim Paint
			SelectedPaintCarPart = *(DWORD**)((*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint) + 12);
			SelectedPaintSelectablePart = (DWORD*)(*(int(__thiscall**)(DWORD*))(*CustomizePaint + 20))(CustomizePaint); // GetSelectedPart
			CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, *((DWORD*)SelectedPaintSelectablePart + 4), SelectedPaintCarPart);

			PaintCategoryArrows = FEngFindObject(CustomizePaintPackage, 0x2C526172);
			FEngSetInvisible(PaintCategoryArrows);
			break;
		default: // Vinyls
			CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, *(DWORD*)(dword_9BA080 + 16), *(DWORD**)(dword_9BA080 + 12));

			if (VinylColorCount == 1)
			{
				PaintCategoryArrows = FEngFindObject(CustomizePaintPackage, 0x2C526172);
				FEngSetInvisible(PaintCategoryArrows);
			}
			CurrVinylColorID = 0;
			CurrVinylColorSelectablePart = (DWORD*)SelectedPaintParts;
			do
			{
				if (CurrVinylColorID < VinylColorCount && *CurrVinylColorSelectablePart) CarCustomizeManager_PreviewPart((DWORD*)_gCarCustomizeManager, *(DWORD*)(*CurrVinylColorSelectablePart + 16), *(DWORD**)(*CurrVinylColorSelectablePart + 12));
				++CurrVinylColorID;
				++CurrVinylColorSelectablePart;
			} while (CurrVinylColorID < 4);
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
				BYTE Red = (BYTE)CarPart_GetAppliedAttributeIParam(SelectedPaintCarPart, bStringHash((char*)"RED"), 0);
				BYTE Green = (BYTE)CarPart_GetAppliedAttributeIParam(SelectedPaintCarPart, bStringHash((char*)"GREEN"), 0);
				BYTE Blue = (BYTE)CarPart_GetAppliedAttributeIParam(SelectedPaintCarPart, bStringHash((char*)"BLUE"), 0);

				FEngSetColor_obj(*(DWORD**)(PaintSlot + 3), Blue | ((Green | ((Red | 0xFFFFFF00) << 8)) << 8));
			}
		}
	}
}

DWORD __fastcall CustomizePaint_CalcBrandHash(DWORD* _CustomizePaint, void* EDX_Unused, DWORD* ActivePaint)
{
	DWORD result = 0x2DAAB07;

	int MenuID = _CustomizePaint[82];
	int PaintScrollerIndex = _CustomizePaint[111];

	switch (MenuID)
	{
	case 0x301:
		if (PaintScrollerIndex >= PaintGroups.size()) result = CarPart_GetAppliedAttributeUParam(ActivePaint, 0xEBB03E66, 0); // BRAND_NAME
		else result = PaintGroups[PaintScrollerIndex].BrandNameHash;
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

	for (int i = 0; i < PaintGroups.size(); i++)
	{
		if (PaintGroups[i].BrandNameHash == BrandHash)
		{
			result = i;
			break;
		}
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
	if (CarSlotID < 79 || CarSlotID > 82)
		goto LABEL_11;
	VinylColorLayer = CarSlotID - 79;
	ShowcasePaintPart = Showcase_FromColor[VinylColorLayer];
	if (!ShowcasePaintPart)
		goto LABEL_11;
	if (SelectedPaintParts[VinylColorLayer])
		goto LABEL_11;
	ActivePaint = (DWORD*)ShowcasePaintPart[3];
	if (!ActivePaint)
		LABEL_11:
	ActivePaint = (DWORD*)CarCustomizeManager_GetActivePartFromSlot((DWORD*)_gCarCustomizeManager, CarSlotID);
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
			pItemIndex = &SelectedPaints[_CustomizePaint[111]];
			IsIndexInvalid = *pItemIndex == -1;
			v38 = 0;
			if (IsIndexInvalid && ActivePaint == *(DWORD**)(PaintDatum[6] + 12))
				*pItemIndex = i;
			ArrayScroller_AddDatum((_CustomizePaint + 136), PaintDatum);
			ArraySlot = (DWORD*)ArrayScroller_GetSlotAt((_CustomizePaint + 136), i);
			if (ArraySlot)
			{
				PaintPart = *(DWORD**)(PaintDatum[6] + 12);
				AttrNameHash = bStringHash((char*)"RED");
				r = CarPart_GetAppliedAttributeIParam(PaintPart, AttrNameHash, 0);
				PaintPart = *(DWORD**)(PaintDatum[6] + 12);
				AttrNameHash = bStringHash((char*)"GREEN");
				g = CarPart_GetAppliedAttributeIParam(PaintPart, AttrNameHash, 0);
				PaintPart = *(DWORD**)(PaintDatum[6] + 12);
				AttrNameHash = bStringHash((char*)"BLUE");
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
		SelectedPaints[_CustomizePaint[111]] = *(int*)_Showcase_FromIndex - 1;
		ArrayScroller_SetInitialPosition((_CustomizePaint + 136), *(int*)_Showcase_FromIndex - 1);
		*(int*)_Showcase_FromIndex = 0;
	}
	else
	{
		InitialPosition = (DWORD)&SelectedPaints[_CustomizePaint[111]];
		if (*(DWORD*)InitialPosition == -1)
			*(DWORD*)InitialPosition = 0;
		ArrayScroller_SetInitialPosition(
			(_CustomizePaint + 136),
			SelectedPaints[_CustomizePaint[111]]);
	}
	(*(void(__thiscall**)(DWORD*))(*_CustomizePaint + 12))(_CustomizePaint);// RefreshHeader
	v38 = -1;
	bTList_SelectablePart_dtor((int**)PartList);
}

void __fastcall CustomizePaint_ScrollFilters(DWORD* _CustomizePaint, void* EDX_Unused, int direction)
{
	int Min = 0; // ebx
	int Max = 0; // ebx
	DWORD* CurrentPaintSelectablePart; // edi
	DWORD* NewSelectablePart; // edi
	DWORD* SelectedPart; // eax MAPDST
	int PaintScrollerIndex; // edi
	DWORD* CustomizePaintDatum; // eax
	DWORD* CustomizePaintDatumOffset; // eax
	DWORD PaintLocation; // eax
	unsigned int CarSlotID; // [esp-4h] [ebp-20h]

	// Get CarType Info
	void* FECarRecord = *(void**)_FECarRecord;
	int CarTypeID = FECarRecord_GetType(FECarRecord);

	if (_CustomizePaint[82] == 0x301) // Body Paint
	{
		Min = CarConfigs[CarTypeID].Visual.PaintCustom ? 0 : 1;
		Max = PaintGroups.size() - 1;
	}
	else
	{
		if (_CustomizePaint[82] == 0x303) return; // Rim Paint (has only one category)

		// Vinyl Paint
		Min = 0;
		Max = _CustomizePaint[184] - 1;
		if (_CustomizePaint[184] != 1)
		{
			CurrentPaintSelectablePart = SelectedPaintParts[_CustomizePaint[111]];
			if ((DWORD*)(*(int(__thiscall**)(DWORD*))(*_CustomizePaint + 20))(_CustomizePaint) != CurrentPaintSelectablePart)
			{
				if (CurrentPaintSelectablePart)
0					(*(void(__thiscall**)(DWORD*, int)) * CurrentPaintSelectablePart)(CurrentPaintSelectablePart, 1);
				NewSelectablePart = (DWORD*)j_malloc(0x2Cu);
				if (NewSelectablePart)
				{
					SelectedPart = (DWORD*)(*(int(__thiscall**)(DWORD*))(*_CustomizePaint + 20))(_CustomizePaint);
					SelectablePart_copy(NewSelectablePart, SelectedPart);
				}
				else
				{
					NewSelectablePart = 0;
				}
				SelectedPaintParts[_CustomizePaint[111]] = NewSelectablePart;
			}
		}
	}
	PaintScrollerIndex = _CustomizePaint[111];
	if (direction == -1)
	{
		if (--PaintScrollerIndex < Min) PaintScrollerIndex = Max;
	}
	else if (direction == 1)
	{
		if (++PaintScrollerIndex > Max) PaintScrollerIndex = Min;
	}
	if (PaintScrollerIndex != _CustomizePaint[111])
	{
		CustomizePaintDatum = (DWORD*)_CustomizePaint[142];
		if (CustomizePaintDatum)
			CustomizePaintDatumOffset = CustomizePaintDatum + 1;
		else
			CustomizePaintDatumOffset = 0;
		SelectedPaints[_CustomizePaint[111]] = bList_TraversebList(_CustomizePaint + 140, CustomizePaintDatumOffset) - 1;
		PaintLocation = _CustomizePaint[82] - 0x301;
		_CustomizePaint[111] = PaintScrollerIndex;
		if (!PaintLocation || PaintLocation == 2) // Body or Rim Paint
		{
			//CarSlotID = *(DWORD*)((*(int(__thiscall**)(DWORD*))(*_CustomizePaint + 20))(_CustomizePaint) + 16); // GetSelectedPart
			CustomizePaint_BuildSwatchList(_CustomizePaint, EDX_Unused, PaintLocation + 76);
		}
		else                                        // Vinyl paint
		{
			CustomizePaint_BuildSwatchList(_CustomizePaint, EDX_Unused, PaintScrollerIndex + 79);
		}
		(*(void(__thiscall**)(DWORD*))(*_CustomizePaint + 12))(_CustomizePaint);
	}
}

void __fastcall CustomizePaint_AddVinylAndColorsToCart(DWORD* _CustomizePaint, void* EDX_Unused)
{
	int CurrLayer = 0; // edi
	DWORD** VinylSelectablePartRef; // esi

	CarCustomizeManager_AddToCart((DWORD*)_gCarCustomizeManager, (DWORD*)dword_9BA080);

	VinylSelectablePartRef = SelectedPaintParts;
	do
	{
		if (CurrLayer < (int)_CustomizePaint[184] && *VinylSelectablePartRef)
			CarCustomizeManager_AddToCart((DWORD*)_gCarCustomizeManager, *VinylSelectablePartRef);
		if (*VinylSelectablePartRef)
			(**(void(__thiscall***)(DWORD*, int)) * VinylSelectablePartRef)(*VinylSelectablePartRef, 1);
		*VinylSelectablePartRef = 0;
		Showcase_FromColor[CurrLayer++] = 0;
		++VinylSelectablePartRef;
	} while (CurrLayer < 4);
}

void __fastcall CustomizePaint_NotificationMessage(DWORD* _CustomizePaint, void* EDX_Unused, DWORD MessageHash, DWORD* FEObject, DWORD param1, DWORD param2)
{
	DWORD* CurrentPaintSelectablePart; // ecx
	DWORD* NewSelectablePart; // edi
	DWORD* SelectedPart; // eax MAPDST
	int CurrVinylLayer; // edi
	DWORD* i; // ebx
	DWORD* ActivePart; // eax
	DWORD* PartInCart; // eax MAPDST
	int* ShowcaseFromColorRef; // edi
	DWORD* CustomizePaintDatum; // eax
	DWORD* CustomizePaintDatumOffset; // eax
	DWORD* SelectedPartRef; // esi MAPDST
	int num; // edi

	int MenuID = _CustomizePaint[82]; // eax MAPDST

	if (MessageHash != 0x9120409E && MessageHash != 0xB5971BF1) // !PAD_LEFT && !PAD_RIGHT
	{
		CustomizationScreen_NotificationMessage(_CustomizePaint, MessageHash, FEObject, param1, param2);
	}

	(*(void(__thiscall**)(DWORD*, DWORD, DWORD*, DWORD, DWORD))(_CustomizePaint[136] + 4))(_CustomizePaint + 136, MessageHash, FEObject, param1, param2);

	switch (MessageHash)
	{
	case 0x5A928018: // Unk (Remove from cart??)
		PartInCart = (DWORD*)(*(int(__thiscall**)(DWORD*))(*_CustomizePaint + 24))(_CustomizePaint);
		if (PartInCart && !CarCustomizeManager_IsPartInCart((DWORD*)_gCarCustomizeManager, PartInCart))
		{
			PartInCart[8] &= 0xFu;
		}
		(*(void(__thiscall**)(DWORD*))(*_CustomizePaint + 12))(_CustomizePaint);
		break;

	case 0x406415E3: // PAD_ACCEPT
		if (bList_TraversebList(_CustomizePaint + 140, 0) <= 0) return;
		if (MenuID == 0x301 || MenuID == 0x303) CustomizationScreen_NotificationMessage(_CustomizePaint, MessageHash, FEObject, param1, param2);
		else // Vinyl paint
		{
			CurrentPaintSelectablePart = (DWORD*)SelectedPaintParts[_CustomizePaint[111]];
			if (CurrentPaintSelectablePart)
				(*(void(__thiscall**)(DWORD*, int)) * CurrentPaintSelectablePart)(CurrentPaintSelectablePart, 1);
			NewSelectablePart = (DWORD*)j_malloc(0x2Cu);
			if (NewSelectablePart)
			{
				SelectedPart = (DWORD*)(*(int(__thiscall**)(DWORD*))(*_CustomizePaint + 20))(_CustomizePaint);
				SelectablePart_copy(NewSelectablePart, SelectedPart);
			}
			else
			{
				NewSelectablePart = 0;
			}
			SelectedPaintParts[_CustomizePaint[111]] = NewSelectablePart;
			if ((DWORD)CarCustomizeManager_GetActivePartFromSlot((DWORD*)_gCarCustomizeManager, 77) == *(DWORD*)(dword_9BA080 + 12))
			{
				CurrVinylLayer = 0;
				if ((int)_CustomizePaint[184] <= 0)
					return;
				for (i = (DWORD*)SelectedPaintParts; ; ++i)
				{
					ActivePart = CarCustomizeManager_GetActivePartFromSlot((DWORD*)_gCarCustomizeManager, CurrVinylLayer + 79);
					if (*i)
					{
						if (ActivePart != *(DWORD**)(*i + 12))
							break;
					}
					if (++CurrVinylLayer >= _CustomizePaint[184])
						return;
				}
			}
			CustomizePaint_AddVinylAndColorsToCart(_CustomizePaint, EDX_Unused);
			cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizePartsPkg, MenuID | (_CustomizePaint[83] << 16), 0, 0);
		}
		break;

	case 0x5073EF13: // PAD_LTRIGGER
		CustomizePaint_ScrollFilters(_CustomizePaint, EDX_Unused, -1);
		break;

	case 0xD9FEEC59: // PAD_RTRIGGER
		CustomizePaint_ScrollFilters(_CustomizePaint, EDX_Unused, 1);
		break;

	case 0x911C0A4B: // PAD_DOWN
	case 0x72619778: // PAD_UP
	case 0x9120409E: // PAD_LEFT
	case 0xB5971BF1: // PAD_RIGHT
		(*(void(__thiscall**)(DWORD*))(*_CustomizePaint + 12))(_CustomizePaint);
		break;

	case 0xC519BFBF: // PAD_BUTTON0
		*(int*)_Showcase_FromFilter = _CustomizePaint[111];
		CustomizePaintDatum = (DWORD*)_CustomizePaint[142];
		if (CustomizePaintDatum)
			CustomizePaintDatumOffset = CustomizePaintDatum + 1;
		else
			CustomizePaintDatumOffset = 0;
		*(int*)_Showcase_FromIndex = bList_TraversebList(_CustomizePaint + 140, CustomizePaintDatumOffset);
		for (int i = 0; i < MaximumPaintBrandCount; i++) Showcase_FromColor[i] = SelectedPaintParts[i];
		break;

	case 0xCF91AACD:
		SelectedPartRef = (DWORD*)SelectedPaintParts;

		for (int i = 0; i < 4; i++)
		{
			if (*SelectedPartRef) (**(void(__thiscall***)(DWORD, int)) * SelectedPartRef)(*SelectedPartRef, 1);
			*SelectedPartRef = 0;
			++SelectedPartRef;
		}
		break;

	case 0x911AB364: // PAD_BACK
		if (MenuID == 0x301 || MenuID == 0x303) // Body or rim paint
		{
			cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizeSubPkg, _CustomizePaint[83] | (MenuID << 16), 0, 0);
		}
		else // Vinyl
		{
			ShowcaseFromColorRef = (int*)Showcase_FromColor;
			SelectedPartRef = (DWORD*)SelectedPaintParts;

			for (int i = 0; i < 4; i++)
			{
				if (*SelectedPartRef) (**(void(__thiscall***)(DWORD, int)) * SelectedPartRef)(*SelectedPartRef, 1);
				*SelectedPartRef = 0;
				*ShowcaseFromColorRef++ = 0;
				++SelectedPartRef;
			}

			CarCustomizeManager_ResetPreview((DWORD*)_gCarCustomizeManager);
			cFEng_QueuePackageSwitch(*(DWORD**)cFEng_mInstance, *(char**)g_pCustomizePartsPkg, MenuID | (_CustomizePaint[83] << 16), 0, 0);
		}
		break;
	}
}

void __fastcall CustomizePaint_SetupVinylColor(DWORD* _CustomizePaint, void* EDX_Unused)
{
	int CarSlotID; // eax MAPDST
	signed int NumRemapColors; // eax
	DWORD* ArrowL; // eax
	DWORD* ArrowR; // eax
	DWORD* ShowcaseFromColorRef; // ecx
	DWORD* SelectedPartRef; // ebp
	DWORD* PartInCart; // eax
	DWORD* InstalledPart; // esi
	DWORD* CustomizationRecord; // esi
	int CarTypeID; // eax
	DWORD* TheSelectablePart; // eax
	char UpgradeLevel; // cl
	bool v15; // zf
	int num; // [esp+14h] [ebp-30h]
	DWORD ASelectablePart[11]; // [esp+18h] [ebp-2Ch] BYREF

	CarSlotID = 79;

	DWORD* FEDatabase = *(DWORD**)_FEDatabase;
	void* FECarRecord = *(void**)_FECarRecord;

	if (*(int*)_Showcase_FromFilter != -1)
	{
		CarSlotID = 79 + *(int*)_Showcase_FromFilter;

		*(int*)_Showcase_FromFilter = -1;
	}

	CustomizePaint_BuildSwatchList(_CustomizePaint, EDX_Unused, CarSlotID);
	NumRemapColors = CarPart_GetAppliedAttributeUParam(*(DWORD**)(dword_9BA080 + 12), 0x6212682B, 0); // NUMREMAPCOLOURS
	_CustomizePaint[184] = NumRemapColors;
	if (NumRemapColors > 1)
	{
		cFEng_QueuePackageMessage(*(DWORD**)cFEng_mInstance, 0x1A7240F3, (const char*)_CustomizePaint[4], 0);
	}
	else
	{
		ArrowL = FEngFindObject((const char*)_CustomizePaint[4], 0x2C3CC2D3);
		FEngSetInvisible(ArrowL);
		ArrowR = FEngFindObject((const char*)_CustomizePaint[4], 0x53639A10);
		FEngSetInvisible(ArrowR);
	}
	ShowcaseFromColorRef = (DWORD*)Showcase_FromColor;
	CarSlotID = 79;
	SelectedPartRef = (DWORD*)SelectedPaintParts;
	num = 4;
	do
	{
		if (*ShowcaseFromColorRef)
		{
			*SelectedPartRef = *ShowcaseFromColorRef;
			*ShowcaseFromColorRef = 0;
		}
		else
		{
			ASelectablePart[0] = (DWORD)SelectablePart_vtable;
			ASelectablePart[3] = 0;
			ASelectablePart[4] = CarSlotID;
			ASelectablePart[5] = 0;
			ASelectablePart[6] = 7;
			*((BYTE*)ASelectablePart + 28) = 0;
			ASelectablePart[8] = 1;
			ASelectablePart[9] = 0;
			*((BYTE*)ASelectablePart + 40) = 0;
			PartInCart = (DWORD*)CarCustomizeManager_IsPartTypeInCart((DWORD*)_gCarCustomizeManager, ASelectablePart);

			if (PartInCart)
			{
				InstalledPart = *(DWORD**)(PartInCart[3] + 12);
			}
			else
			{
				CustomizationRecord = FEPlayerCarDB_GetCustomizationRecordByHandle((DWORD*)(*((DWORD*)FEDatabase + 4) + 0x414), *((BYTE*)FECarRecord + 16));
				CarTypeID = FECarRecord_GetType(FECarRecord);
				InstalledPart = FECustomizationRecord_GetInstalledPart(CustomizationRecord, CarTypeID, CarSlotID);
			}
			if (InstalledPart)
			{
				TheSelectablePart = (DWORD*)j_malloc(0x2Cu);
				if (TheSelectablePart)
				{
					UpgradeLevel = *((BYTE*)InstalledPart + 5) >> 5;
					*TheSelectablePart = SelectablePart_vtable;
					TheSelectablePart[3] = (DWORD)InstalledPart;
					TheSelectablePart[4] = CarSlotID;
					TheSelectablePart[5] = UpgradeLevel;
					TheSelectablePart[6] = 7;
					*((BYTE*)TheSelectablePart + 28) = 0;
					TheSelectablePart[8] = 1;
					TheSelectablePart[9] = 0;
					*((BYTE*)TheSelectablePart + 40) = 0;
					*SelectedPartRef = (DWORD)TheSelectablePart;
				}
				else
				{
					*SelectedPartRef = 0;
				}
			}
			else
			{
				*SelectedPartRef = 0;
			}
		}
		++ShowcaseFromColorRef;
		++CarSlotID;
		++SelectedPartRef;
		v15 = num == 1;
		--num;
	}

	while (!v15);
}


void __fastcall CustomizePaint_Setup(DWORD * _CustomizePaint, void* EDX_Unused)
{
	DWORD* L1Btn; // eax
	DWORD* R1Btn; // eax
	DWORD* NewArraySlot; // ebp
	DWORD* PaintSlot; // eax
	const char* FEPackageName = (const char*)_CustomizePaint[4];
	DWORD ColorObjHash; // eax
	DWORD* ColorObj; // eax
	DWORD MenuID = _CustomizePaint[82];
	DWORD* ArrowL; // eax
	DWORD* ArrowR; // eax

	// Get CarType Info
	void* FECarRecord = *(void**)_FECarRecord;
	int CarTypeID = FECarRecord_GetType(FECarRecord);

	L1Btn = FEngFindImage(FEPackageName, 0x91C4A50u);
	FEngSetButtonTexture(L1Btn, 0x5BC);
	R1Btn = FEngFindImage(FEPackageName, 0x2D145BE3u);
	FEngSetButtonTexture(R1Btn, 0x682);

	for (int i = 1; i <= 80; ++i)
	{
		NewArraySlot = (DWORD*)j_malloc(0x14u);
		PaintSlot = 0;
		if (NewArraySlot)
		{
			ColorObjHash = FEngHashString("COLOR_%d", i);
			ColorObj = FEngFindImage(FEPackageName, ColorObjHash);
			PaintSlot = ArraySlot_ArraySlot(NewArraySlot, ColorObj);
		}
		ArrayScroller_AddSlot(_CustomizePaint + 136, PaintSlot);
	}

	/*
	_CustomizePaint[112] = -1;
	_CustomizePaint[113] = -1;
	_CustomizePaint[114] = -1;*/

	for (int i = 0; i < MaximumPaintBrandCount; i++)
	{
		SelectedPaints[i] = -1;
		SelectedPaintParts[i] = 0;
	}

	if (*(int*)_Showcase_FromFilter != -1)
		_CustomizePaint[111] = *(int*)_Showcase_FromFilter;

	if (MenuID > 0x303) // Vinyls
	{
		if (MenuID >= 0x402 && MenuID <= 0x4FF)
		{
			_CustomizePaint[87] = CarConfigs[CarTypeID].Names.VisualVinylsColor;         // CO_VINYL_COLOR
			CustomizePaint_SetupVinylColor(_CustomizePaint, EDX_Unused);
		}
	}
	else if (MenuID == 0x303) // Rim Paint
	{
		_CustomizePaint[87] = CarConfigs[CarTypeID].Names.VisualRimPaint;           // CO_RIM_PAINT
		ArrowL = FEngFindObject(FEPackageName, 0x2C3CC2D3);
		FEngSetInvisible(ArrowL);
		ArrowR = FEngFindObject(FEPackageName, 0x53639A10);
		FEngSetInvisible(ArrowR);
		CustomizePaint_BuildSwatchList(_CustomizePaint, EDX_Unused, 78);
	}
	else if (MenuID == 0x301) // Body Paint
	{
		cFEng_QueuePackageMessage(*(DWORD**)cFEng_mInstance, 0x1A7240F3, FEPackageName, 0);
		_CustomizePaint[87] = CarConfigs[CarTypeID].Names.VisualPaint;            // CO_PAINT
		CustomizePaint_BuildSwatchList(_CustomizePaint, EDX_Unused, 76);
	}
	*(int*)_Showcase_FromFilter = -1;
	*((BYTE*)_CustomizePaint + 283) = 1;
	(*(int(__thiscall**)(DWORD*))(*_CustomizePaint + 12))(_CustomizePaint);
}
