#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

struct DetailsPane
{
	// Package name for the details pane
	char const* PackageName;

	// Main flag
	bool Visible;

	// Flags for each part
	int UpgradeLevel;
	bool CustomIcon; // Customizable widebody
	bool WheelAttrIcon; // Has wheel attributes
	bool PaintableIcon;
	bool CFIcon;
	bool NeonIcon;
	bool RemapIcon;
	bool DecalIcon;
	bool TrunkSlotIcon;
	int NumSlots; // Decal or trunk audio slots
	bool FilterIcon;
};

DetailsPane DetailsGroup;

#define EnabledColor 0xFFE6AA00
#define EnabledColorBackroom 0xFFE6AA00
#define DisabledColor 0xFF303030

#define NumIconsInDetailsPane 5

#define EmptyIconHash CT_bStringHash("DEFAULTALPHA")

DWORD DetailsPaneIcons[NumIconsInDetailsPane] =
{
	CT_bStringHash("ATTR_ICON_1"),
	CT_bStringHash("ATTR_ICON_2"),
	CT_bStringHash("ATTR_ICON_3"),
	CT_bStringHash("ATTR_ICON_4"),
	CT_bStringHash("ATTR_ICON_5")
};

DWORD NumRemapIcons[] =
{
	CT_bStringHash("VISUAL_PART_PAINT"),
	CT_bStringHash("PAINT_ICON_1"),
	CT_bStringHash("PAINT_ICON_2"),
	CT_bStringHash("PAINT_ICON_3"),
	CT_bStringHash("PAINT_ICON_4")
};

DWORD NumTrunkSlotIcons[] =
{
	CT_bStringHash("AUDIO_ICON_GENERIC"),
	CT_bStringHash("AUDIO_ICON_SLOT1"),
	CT_bStringHash("AUDIO_ICON_SLOT2"),
	CT_bStringHash("AUDIO_ICON_SLOT3"),
	CT_bStringHash("AUDIO_ICON_SLOT4"),
	CT_bStringHash("AUDIO_ICON_SLOT5"),
	CT_bStringHash("AUDIO_ICON_SLOT6"),
	CT_bStringHash("AUDIO_ICON_SLOT7"),
	CT_bStringHash("AUDIO_ICON_SLOT8"),
	CT_bStringHash("AUDIO_ICON_SLOT9"),
	CT_bStringHash("AUDIO_ICON_SLOT10"),
	CT_bStringHash("AUDIO_ICON_SLOT11"),
	CT_bStringHash("AUDIO_ICON_SLOT12")
};

//bool PartLink_HasLink(DWORD* CarPart); // shut up c3861

void UpdateDetailsPaneIcon(int IconID, DWORD TextureHash, bool enabled)
{
	if (IconID < NumIconsInDetailsPane)
	{
		DWORD* IconObj = (DWORD*)FEngFindObject(DetailsGroup.PackageName, DetailsPaneIcons[IconID]);

		if (IconObj && DetailsGroup.Visible)
		{
			FEngSetTextureHash_obj(IconObj, TextureHash);
			FEngSetColor_obj(IconObj, enabled ? (CustomizeIsInBackRoom() ? EnabledColorBackroom : EnabledColor) : DisabledColor);
		}
	}
}

void SetUpgradeGroupIcon(int UpgradeLevel)
{
	switch (DetailsGroup.UpgradeLevel)
	{
	case 0: // Stock
	default:
		UpdateDetailsPaneIcon(0, CT_bStringHash("PERFORMANCE_ICON_BASE_PACKAGE"), true);
		break;
	case 1:
		UpdateDetailsPaneIcon(0, CT_bStringHash("PERFORMANCE_ICON_PACKAGE_1"), true);
		break;
	case 2:
		UpdateDetailsPaneIcon(0, CT_bStringHash("PERFORMANCE_ICON_PACKAGE_1"), true);
		break;
	case 3:
		UpdateDetailsPaneIcon(0, CT_bStringHash("PERFORMANCE_ICON_PACKAGE_1"), true);
		break;
	case 4:
		UpdateDetailsPaneIcon(0, CT_bStringHash("PERFORMANCE_ICON_PACKAGE_1"), true);
		break;
	}
}

void SetOtherIcons(DWORD* CarPart)
{
	// Disable everything first
	DetailsGroup.CustomIcon = 0;
	DetailsGroup.WheelAttrIcon = 0; // Has wheel attributes
	DetailsGroup.PaintableIcon = 0;
	DetailsGroup.CFIcon = 0;
	DetailsGroup.NeonIcon = 0;
	DetailsGroup.RemapIcon = 0;
	DetailsGroup.DecalIcon = 0;
	DetailsGroup.TrunkSlotIcon = 0;
	DetailsGroup.NumSlots = 0; // Color or trunk audio slots
	DetailsGroup.FilterIcon = 0;

	if (!CarPart) return;

	// Choose other icons based on the part type
	int CarSlotID = GetCarSlotIDFromPart(*((BYTE*)CarPart + 4));
	int CurrentIconID = 1;

	// Custom widebody
	bool IsCustom = 0;

	if (CarSlotID == CARSLOTID_BODY)
	{
		DetailsGroup.CustomIcon = 1;

		if (CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("CUSTOM"), 0)
			|| CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("CUSTOM_FRONT_BUMPER"), 0)
			|| CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("CUSTOM_REAR_BUMPER"), 0)
			|| CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("CUSTOM_SKIRT"), 0)
			|| CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("CUSTOM_FENDER"), 0)
			|| CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("CUSTOM_QUARTER"), 0))
			IsCustom = 1;
	}

	// Check for wheel attributes
	bool HasWheelAttr = 0;

	switch (CarSlotID)
	{
	case CARSLOTID_BODY:
	case CARSLOTID_ATTACHMENT0:
	case CARSLOTID_ATTACHMENT1:
	case CARSLOTID_ATTACHMENT2:
	case CARSLOTID_ATTACHMENT3:
	case CARSLOTID_ATTACHMENT4:
	case CARSLOTID_ATTACHMENT5:
	case CARSLOTID_ATTACHMENT6:
	case CARSLOTID_ATTACHMENT7:
	case CARSLOTID_ATTACHMENT8:
	case CARSLOTID_ATTACHMENT9:
		DetailsGroup.WheelAttrIcon = 1;

		if (CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("FRONT_TIRE_OFFSET"), 0)
			|| CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("REAR_TIRE_OFFSET"), 0))
			HasWheelAttr = 1;
		break;
	}

	// Check if paintable
	bool IsPaintable = 0;

	switch (CarSlotID)
	{
	case CARSLOTID_SPOILER:
	case CARSLOTID_ROOF:
	case CARSLOTID_LEFT_SIDE_MIRROR:
		DetailsGroup.PaintableIcon = 1;
		IsPaintable = (DetailsGroup.UpgradeLevel > 0)
			&& (CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("UNPAINTABLE"), 0) == 0)
			&& (CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("CARBONFIBRE"), 0) == 0);
		break;
	case CARSLOTID_FRONT_WHEEL:
	case CARSLOTID_REAR_WHEEL:
	case CARSLOTID_FRONT_BRAKE:
	case CARSLOTID_REAR_BRAKE:
		DetailsGroup.PaintableIcon = 1;
		IsPaintable = (DetailsGroup.UpgradeLevel > 0) || (CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("UNPAINTABLE"), 1) == 0);
		break;
	case CARSLOTID_HOOD:
	case CARSLOTID_ATTACHMENT0:
	case CARSLOTID_ATTACHMENT1:
	case CARSLOTID_ATTACHMENT2:
	case CARSLOTID_ATTACHMENT3:
	case CARSLOTID_ATTACHMENT4:
	case CARSLOTID_ATTACHMENT5:
	case CARSLOTID_ATTACHMENT6:
	case CARSLOTID_ATTACHMENT7:
	case CARSLOTID_ATTACHMENT8:
	case CARSLOTID_ATTACHMENT9:
		DetailsGroup.PaintableIcon = 1;
		IsPaintable = (CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("UNPAINTABLE"), 0) == 0)
			&& (CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("CARBONFIBRE"), 0) == 0);
		break;
	}

	// Check if carbon fibre
	bool CF = 0;
	switch (CarSlotID)
	{
	case CARSLOTID_BODY:
	case CARSLOTID_BASE:
	case CARSLOTID_SPOILER:
	case CARSLOTID_ROOF:
	case CARSLOTID_HOOD:
	case CARSLOTID_HEADLIGHT:
	case CARSLOTID_BRAKELIGHT:
	case CARSLOTID_ATTACHMENT0:
	case CARSLOTID_ATTACHMENT1:
	case CARSLOTID_ATTACHMENT2:
	case CARSLOTID_ATTACHMENT3:
	case CARSLOTID_ATTACHMENT4:
	case CARSLOTID_ATTACHMENT5:
	case CARSLOTID_ATTACHMENT6:
	case CARSLOTID_ATTACHMENT7:
	case CARSLOTID_ATTACHMENT8:
	case CARSLOTID_ATTACHMENT9:
		CF = CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("CARBONFIBRE"), 0);
		if (CF)
		{
			DetailsGroup.CFIcon = 1;
			DetailsGroup.PaintableIcon = 0; // If CF, it doesn't need to show the paintable icon.
		}
		break;
	}

	// Remap (vinyl paint)
	bool Remap = 0;
	if (CarSlotID == CARSLOTID_VINYL_LAYER0)
	{
		DetailsGroup.RemapIcon = 1;
		DetailsGroup.NumSlots = CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("REMAP"), 0)
			? CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("NUMREMAPCOLOURS"), 0)
			: 0;
	}

	// Decals
	bool HasDecals = 0;

	if (CarSlotID == CARSLOTID_HOOD)
	{
		DetailsGroup.DecalIcon = 1;

		if (DetailsGroup.UpgradeLevel == 0) HasDecals = 1;
		else if (CarPart_GetAppliedAttributeUParam(CarPart, CT_bStringHash("EXCLUDEDECAL"), 0) != CT_bStringHash("DECAL_HOOD")) HasDecals = 1;
	}

	// Filter
	bool IsFiltered = 0;
	switch (CarSlotID)
	{
	case CARSLOTID_BODY:
	case CARSLOTID_BASE:
	case CARSLOTID_SPOILER:
	case CARSLOTID_ROOF:
	case CARSLOTID_HOOD:
	case CARSLOTID_HEADLIGHT:
	case CARSLOTID_BRAKELIGHT:
	case CARSLOTID_ATTACHMENT0:
	case CARSLOTID_ATTACHMENT1:
	case CARSLOTID_ATTACHMENT2:
	case CARSLOTID_ATTACHMENT3:
	case CARSLOTID_ATTACHMENT4:
	case CARSLOTID_ATTACHMENT5:
	case CARSLOTID_ATTACHMENT6:
	case CARSLOTID_ATTACHMENT7:
	case CARSLOTID_ATTACHMENT8:
	case CARSLOTID_ATTACHMENT9:
		DetailsGroup.FilterIcon = 1;

		//if (PartLink_HasLink(CarPart)) IsFiltered = 1;
	}

	// Finally update the icons
	if (DetailsGroup.CustomIcon) UpdateDetailsPaneIcon(CurrentIconID++, CT_bStringHash("MAIN_ICON_CUSTOMIZE_CAR"), IsCustom);
	if (DetailsGroup.WheelAttrIcon) UpdateDetailsPaneIcon(CurrentIconID++, CT_bStringHash("PERFORMANCE_TIRES_BRAKES"), HasWheelAttr);
	if (DetailsGroup.PaintableIcon) UpdateDetailsPaneIcon(CurrentIconID++, CT_bStringHash("VISUAL_PART_PAINT"), IsPaintable);
	if (DetailsGroup.CFIcon) UpdateDetailsPaneIcon(CurrentIconID++, CT_bStringHash("VISUAL_PART_CARBON_FIBRE"), CF);
	if (DetailsGroup.RemapIcon) UpdateDetailsPaneIcon(CurrentIconID++, NumRemapIcons[DetailsGroup.NumSlots], DetailsGroup.NumSlots > 0);
	if (DetailsGroup.DecalIcon) UpdateDetailsPaneIcon(CurrentIconID++, CT_bStringHash("DECAL_ZONE_HOOD"), HasDecals);
	if (DetailsGroup.FilterIcon) UpdateDetailsPaneIcon(CurrentIconID++, CT_bStringHash("GENERIC_REMOVE"), IsFiltered);
}

void UpdateDetailsPane(DWORD* CarPart)
{
	// Empty out the icons first
	for (int i = 0; i < NumIconsInDetailsPane; i++)
	{
		UpdateDetailsPaneIcon(i, EmptyIconHash, false);
	}

	// First icon is always the upgrade level icon
	if (CarPart) DetailsGroup.UpgradeLevel = (*((BYTE*)CarPart + 5) >> 5);
	else DetailsGroup.UpgradeLevel = 0;

	SetUpgradeGroupIcon(DetailsGroup.UpgradeLevel);

	// Set other icons
	SetOtherIcons(CarPart);
}

void SetDetailsPaneVisibility(char const* PackageName, bool visible)
{
	DWORD* DetailsGroupObj = (DWORD*)FEngFindObject(DetailsGroup.PackageName, CT_bStringHash("DETAILS_GROUP"));
	if (DetailsGroupObj)
	{
		if (visible) FEngSetVisible(DetailsGroupObj);
		else FEngSetInvisible(DetailsGroupObj);

		DetailsGroup.Visible = visible;
	}
	else
	{
#ifdef _DEBUG
		bReleasePrintf("DetailsPane_SetVisibility: DETAILS_GROUP obj not found in package %s\n", PackageName);
#endif
		DetailsGroup.Visible = 0;
	}
}

void RefreshDetailsPane(char const* PackageName, DWORD* PartsList, DWORD* CurrentSelectablePart)
{
	DetailsGroup.PackageName = PackageName;
	SetDetailsPaneVisibility(PackageName, 1);

	if (DetailsGroup.Visible)
	{
		// populate details pane
		DWORD* parts_head = PartsList;
		DWORD* parts_tail = (DWORD*)PartsList[1];

		int PartsCount = bList_TraversebList(parts_head, parts_tail);

		if (PartsCount)
		{
			int UpgradeLevel = 0;
			DWORD* CurrSelPart = (DWORD*)CurrentSelectablePart;

			if (CurrSelPart) UpdateDetailsPane((DWORD*)CurrSelPart[3]);
		}
		else
		{
			SetDetailsPaneVisibility(PackageName, 0);
		}
	}
}
