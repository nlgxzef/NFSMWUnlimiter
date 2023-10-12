#include "stdio.h"
#include "InGameFunctions.h"

int __fastcall CustomizeDecals_GetSlotIDFromCategory(DWORD* CustomizeDecals, void* EDX_Unused)
{
    int result; // eax

    switch (*(int*)CustomizeDecals_CurrentDecalLocation)
    {
    case MenuID::Customize_Decals_Windshield:
    default:
        switch (CustomizeDecals[82])
        {
        case MenuID::Customize_Decals_Slot1:
        default:
            result = CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX0;
            break;
        case MenuID::Customize_Decals_Slot2:
            result = CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX1;
            break;
        case MenuID::Customize_Decals_Slot3:
            result = CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX2;
            break;
        case MenuID::Customize_Decals_Slot4:
            result = CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX3;
            break;
        case MenuID::Customize_Decals_Slot5:
            result = CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX4;
            break;
        case MenuID::Customize_Decals_Slot6:
            result = CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX5;
            break;
        case MenuID::Customize_Decals_Slot7:
            result = CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX6;
            break;
        case MenuID::Customize_Decals_Slot8:
            result = CAR_SLOT_ID::DECAL_FRONT_WINDOW_TEX7;
            break;
        }
        break;
    case MenuID::Customize_Decals_RearWindow:
        switch (CustomizeDecals[82])
        {
        case MenuID::Customize_Decals_Slot1:
        default:
            result = CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX0;
            break;
        case MenuID::Customize_Decals_Slot2:
            result = CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX1;
            break;
        case MenuID::Customize_Decals_Slot3:
            result = CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX2;
            break;
        case MenuID::Customize_Decals_Slot4:
            result = CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX3;
            break;
        case MenuID::Customize_Decals_Slot5:
            result = CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX4;
            break;
        case MenuID::Customize_Decals_Slot6:
            result = CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX5;
            break;
        case MenuID::Customize_Decals_Slot7:
            result = CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX6;
            break;
        case MenuID::Customize_Decals_Slot8:
            result = CAR_SLOT_ID::DECAL_REAR_WINDOW_TEX7;
            break;
        }
        break;
    case MenuID::Customize_Decals_LeftDoor:
        switch (CustomizeDecals[82])
        {
        case MenuID::Customize_Decals_Slot1:
        default:
            result = CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX0;
            break;
        case MenuID::Customize_Decals_Slot2:
            result = CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX1;
            break;
        case MenuID::Customize_Decals_Slot3:
            result = CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX2;
            break;
        case MenuID::Customize_Decals_Slot4:
            result = CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX3;
            break;
        case MenuID::Customize_Decals_Slot5:
            result = CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX4;
            break;
        case MenuID::Customize_Decals_Slot6:
            result = CAR_SLOT_ID::DECAL_LEFT_DOOR_TEX5;
            break;
        }
        break;
    case MenuID::Customize_Decals_RightDoor:
        switch (CustomizeDecals[82])
        {
        case MenuID::Customize_Decals_Slot1:
        default:
            result = CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX0;
            break;
        case MenuID::Customize_Decals_Slot2:
            result = CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX1;
            break;
        case MenuID::Customize_Decals_Slot3:
            result = CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX2;
            break;
        case MenuID::Customize_Decals_Slot4:
            result = CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX3;
            break;
        case MenuID::Customize_Decals_Slot5:
            result = CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX4;
            break;
        case MenuID::Customize_Decals_Slot6:
            result = CAR_SLOT_ID::DECAL_RIGHT_DOOR_TEX5;
            break;
        }
        break;
    case MenuID::Customize_Decals_LeftQuarter:
        switch (CustomizeDecals[82])
        {
        case MenuID::Customize_Decals_Slot1:
        default:
            result = CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX0;
            break;
        case MenuID::Customize_Decals_Slot2:
            result = CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX1;
            break;
        case MenuID::Customize_Decals_Slot3:
            result = CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX2;
            break;
        case MenuID::Customize_Decals_Slot4:
            result = CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX3;
            break;
        case MenuID::Customize_Decals_Slot5:
            result = CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX4;
            break;
        case MenuID::Customize_Decals_Slot6:
            result = CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX5;
            break;
        case MenuID::Customize_Decals_Slot7:
            result = CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX6;
            break;
        case MenuID::Customize_Decals_Slot8:
            result = CAR_SLOT_ID::DECAL_LEFT_QUARTER_TEX7;
            break;
        }
        break;
    case MenuID::Customize_Decals_RightQuarter:
        switch (CustomizeDecals[82])
        {
        case MenuID::Customize_Decals_Slot1:
        default:
            result = CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX0;
            break;
        case MenuID::Customize_Decals_Slot2:
            result = CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX1;
            break;
        case MenuID::Customize_Decals_Slot3:
            result = CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX2;
            break;
        case MenuID::Customize_Decals_Slot4:
            result = CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX3;
            break;
        case MenuID::Customize_Decals_Slot5:
            result = CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX4;
            break;
        case MenuID::Customize_Decals_Slot6:
            result = CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX5;
            break;
        case MenuID::Customize_Decals_Slot7:
            result = CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX6;
            break;
        case MenuID::Customize_Decals_Slot8:
            result = CAR_SLOT_ID::DECAL_RIGHT_QUARTER_TEX7;
            break;
        }
        break;
    }
    return result;
}

// 0x7B8556
void __declspec(naked) GetUnlockHashCodeCave_CustomizeDecals_BuildDecalList()
{
    _asm
    {
        mov edx, dword ptr ds: [esp+0x20] // CarPart
        call CarCustomizeManager_GetUnlockHash_CarPart

        push 0x7B855B
        retn
    }
}