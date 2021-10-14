#include "stdio.h"
#include "InGameFunctions.h"

int __fastcall CustomizeDecals_GetSlotIDFromCategory(DWORD* CustomizeDecals, void* EDX_Unused)
{
    int result; // eax

    switch (*(int*)CustomizeDecals_CurrentDecalLocation) // 0x501 - 0x506
    {
    case 0x501:
    default:
        switch (CustomizeDecals[82])
        {
        case 0x601:
        default:
            result = 83;                          // DECAL_FRONT_WINDOW_TEX0
            break;
        case 0x602:
            result = 84;
            break;
        case 0x603:
            result = 85;
            break;
        case 0x604:
            result = 86;
            break;
        case 0x605:
            result = 87;
            break;
        case 0x606:
            result = 88;
            break;
        case 0x607:
            result = 89;
            break;
        case 0x608:
            result = 90;
            break;
        }
        break;
    case 0x502:
        switch (CustomizeDecals[82])
        {
        case 0x601:
        default:
            result = 91;                          // DECAL_REAR_WINDOW_TEX0
            break;
        case 0x602:
            result = 92;
            break;
        case 0x603:
            result = 93;
            break;
        case 0x604:
            result = 94;
            break;
        case 0x605:
            result = 95;
            break;
        case 0x606:
            result = 96;
            break;
        case 0x607:
            result = 97;
            break;
        case 0x608:
            result = 98;
            break;
        }
        break;
    case 0x503:
        switch (CustomizeDecals[82])
        {
        case 0x601:
        default:
            result = 99;                          // DECAL_LEFT_DOOR_TEX0
            break;
        case 0x602:
            result = 100;
            break;
        case 0x603:
            result = 101;
            break;
        case 0x604:
            result = 102;
            break;
        case 0x605:
            result = 103;
            break;
        case 0x606:
            result = 104;
            break;
        }
        break;
    case 0x504:
        switch (CustomizeDecals[82])
        {
        case 0x601:
        default:
            result = 107;                         // DECAL_RIGHT_DOOR_TEX0
            break;
        case 0x602:
            result = 108;
            break;
        case 0x603:
            result = 109;
            break;
        case 0x604:
            result = 110;
            break;
        case 0x605:
            result = 111;
            break;
        case 0x606:
            result = 112;
            break;
        }
        break;
    case 0x505:
        switch (CustomizeDecals[82])
        {
        case 0x601:
        default:
            result = 115;                          // DECAL_LEFT_QUARTER_TEX0
            break;
        case 0x602:
            result = 116;
            break;
        case 0x603:
            result = 117;
            break;
        case 0x604:
            result = 118;
            break;
        case 0x605:
            result = 119;
            break;
        case 0x606:
            result = 120;
            break;
        case 0x607:
            result = 121;
            break;
        case 0x608:
            result = 122;
            break;
        }
        break;
    case 0x506:
        switch (CustomizeDecals[82])
        {
        case 0x601:
        default:
            result = 123;                          // DECAL_RIGHT_QUARTER_TEX0
            break;
        case 0x602:
            result = 124;
            break;
        case 0x603:
            result = 125;
            break;
        case 0x604:
            result = 126;
            break;
        case 0x605:
            result = 127;
            break;
        case 0x606:
            result = 128;
            break;
        case 0x607:
            result = 129;
            break;
        case 0x608:
            result = 130;
            break;
        }
        break;
    }
    return result;
}