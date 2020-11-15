#include "stdio.h"
#include "InGameFunctions.h"

int __fastcall FEShoppingCartItem_GetCarPartCatHash(DWORD* _this, int EDX_Unused, int CarSlotID)
{
    int result;

    switch (CarSlotID)
    {
    case 0:
        result = bStringHash("CO_ROOF");
        break;
    case 23:
        result = bStringHash("CO_BODY_KITS");
        break;
    case 24:
        result = bStringHash("CO_BRAKES");
        break;
    case 28:
        result = bStringHash("CO_INTERIOR");
        break;
    case 29:
        result = bStringHash("CO_TAILLIGHTS");
        break;
    case 31:
        result = bStringHash("CO_HEADLIGHTS");
        break;
    case 33:
        result = bStringHash("CO_SIDE_MIRROR");
        break;
    case 43:
        result = bStringHash("CO_DRIVER");
        break;
    case 44:
        result = bStringHash("CO_SPOILERS");
        break;
    case 52:
        result = bStringHash("CO_ATTACHMENT_1");
        break;
    case 53:
        result = bStringHash("CO_ATTACHMENT_2");
        break;
    case 54:
        result = bStringHash("CO_ATTACHMENT_3");
        break;
    case 55:
        result = bStringHash("CO_ATTACHMENT_4");
        break;
    case 56:
        result = bStringHash("CO_ATTACHMENT_5");
        break;
    case 57:
        result = bStringHash("CO_ATTACHMENT_6");
        break;
    case 58:
        result = bStringHash("CO_ATTACHMENT_7");
        break;
    case 59:
        result = bStringHash("CO_ATTACHMENT_8");
        break;
    case 60:
        result = bStringHash("CO_ATTACHMENT_9");
        break;
    case 61:
        result = bStringHash("CO_ATTACHMENT_10");
        break;
    case 62:
        result = bStringHash("CO_ROOF_SCOOPS");
        break;
    case 63:
        result = bStringHash("CO_HOODS");
        break;
    case 66:
        result = bStringHash("CO_RIMS");
        break;
    case 69:
        result = bStringHash("CO_LICENSE_PLATE");
        break;
    case 76:
        result = bStringHash("CO_PAINT");
        break;
    case 77:
        result = bStringHash("CO_VINYLS");
        break;
    case 78:
        result = bStringHash("CO_RIM_PAINT");
        break;
    case 83:
        result = bStringHash("CO_DECAL_WINDSHIELD");
        break;
    case 91:
        result = bStringHash("CO_DECAL_REAR_WINDOW");
        break;
    case 99:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
        result = bStringHash("CO_DECAL_LEFT_DOOR");
        break;
    case 107:
    case 108:
    case 109:
    case 110:
    case 111:
    case 112:
        result = bStringHash("CO_DECAL_RIGHT_DOOR");
        break;
    case 113:
        result = bStringHash("CO_NUMBERS");
        break;
    case 115:
        result = bStringHash("CO_DECAL_LEFT_QUARTER");
        break;
    case 123:
        result = bStringHash("CO_DECAL_RIGHT_QUARTER");
        break;
    case 131:
        result = bStringHash("CO_WINDOW_TINT");
        break;
    case 132:
        result = bStringHash("CO_CUSTOM_HUD");
        break;
    default:
        result = 0;
        break;
    }
    return result;
}