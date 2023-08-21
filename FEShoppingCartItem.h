#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

int __fastcall FEShoppingCartItem_GetCarPartCatHash(DWORD* _this, int EDX_Unused, int CarSlotID)
{
    int result;

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    switch (CarSlotID)
    {
    case 0:
        result = CarConfigs[CarTypeID].Names.PartsRoof;
        break;
    case 23:
        result = CarConfigs[CarTypeID].Names.PartsBodyKits;
        break;
    case 24:
        result = CarConfigs[CarTypeID].Names.PartsBrakes;
        break;
    case 28:
        result = CarConfigs[CarTypeID].Names.PartsInterior;
        break;
    case 29:
        result = CarConfigs[CarTypeID].Names.PartsTaillights;
        break;
    case 31:
        result = CarConfigs[CarTypeID].Names.PartsHeadlights;
        break;
    case 33:
        result = CarConfigs[CarTypeID].Names.PartsMirrors;
        break;
    case 43:
        result = CarConfigs[CarTypeID].Names.VisualDriver;
        break;
    case 44:
        result = CarConfigs[CarTypeID].Names.PartsSpoilers;
        break;
    case 52:
        result = CarConfigs[CarTypeID].Names.PartsAttachment0;
        break;
    case 53:
        result = CarConfigs[CarTypeID].Names.PartsAttachment1;
        break;
    case 54:
        result = CarConfigs[CarTypeID].Names.PartsAttachment2;
        break;
    case 55:
        result = CarConfigs[CarTypeID].Names.PartsAttachment3;
        break;
    case 56:
        result = CarConfigs[CarTypeID].Names.PartsAttachment4;
        break;
    case 57:
        result = CarConfigs[CarTypeID].Names.PartsAttachment5;
        break;
    case 58:
        result = CarConfigs[CarTypeID].Names.PartsAttachment6;
        break;
    case 59:
        result = CarConfigs[CarTypeID].Names.PartsAttachment7;
        break;
    case 60:
        result = CarConfigs[CarTypeID].Names.PartsAttachment8;
        break;
    case 61:
        result = CarConfigs[CarTypeID].Names.PartsAttachment9;
        break;
    case 62:
        result = CarConfigs[CarTypeID].Names.PartsRoofScoops;
        break;
    case 63:
        result = CarConfigs[CarTypeID].Names.PartsHoods;
        break;
    case 64: // HEADLIGHT
        result = CarConfigs[CarTypeID].Names.VisualTires;
        break;
    case 65: // BRAKELIGHT
        result = CarConfigs[CarTypeID].Names.VisualNeon;
        break;
    case 66:
        result = CarConfigs[CarTypeID].Names.PartsRims;
        break;
    case 67:
        result = CarConfigs[CarTypeID].Names.PartsRims;
        break;
    case 69:
        result = CarConfigs[CarTypeID].Names.VisualLicensePlate;
        break;
    case 76:
        result = CarConfigs[CarTypeID].Names.VisualPaint;
        break;
    case 77:
        result = CarConfigs[CarTypeID].Names.VisualVinyls;
        break;
    case 78:
        result = CarConfigs[CarTypeID].Names.VisualRimPaint;
        break;
    case 83:
    case 84:
    case 85:
    case 86:
    case 87:
    case 88:
    case 89:
    case 90:
        result = CarConfigs[CarTypeID].Names.VisualDecalsWindshield;
        break;
    case 91:
    case 92:
    case 93:
    case 94:
    case 95:
    case 96:
    case 97:
    case 98:
        result = CarConfigs[CarTypeID].Names.VisualDecalsRearWindow;
        break;
    case 99:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
        result = CarConfigs[CarTypeID].Names.VisualDecalsLeftDoor;
        break;
    case 107:
    case 108:
    case 109:
    case 110:
    case 111:
    case 112:
        result = CarConfigs[CarTypeID].Names.VisualDecalsRightDoor;
        break;
    case 113: // DECAL_RIGHT_DOOR_TEX6
        result = CarConfigs[CarTypeID].Names.VisualNumbers;
        break;
    case 115:
    case 116:
    case 117:
    case 118:
    case 119:
    case 120:
    case 121:
    case 122:
        result = CarConfigs[CarTypeID].Names.VisualDecalsLeftQuarter;
        break;
    case 123:
    case 124:
    case 125:
    case 126:
    case 127:
    case 128:
    case 129:
    case 130:
        result = CarConfigs[CarTypeID].Names.VisualDecalsRightQuarter;
        break;
    case 131:
        result = CarConfigs[CarTypeID].Names.VisualWindowTint;
        break;
    case 132:
        result = CarConfigs[CarTypeID].Names.VisualCustomGauges;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

unsigned int FEShoppingCartItem_GetPerfPkgCatHash(int PerfPkgType)
{
    unsigned int result; // eax

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    result = 0;
    switch (PerfPkgType)
    {
    case 0:
        result = CarConfigs[CarTypeID].Names.PerformanceTires;
        break;
    case 1:
        result = CarConfigs[CarTypeID].Names.PerformanceBrakes;
        break;
    case 2:
        result = CarConfigs[CarTypeID].Names.PerformanceChassis;
        break;
    case 3:
        result = CarConfigs[CarTypeID].Names.PerformanceTransmission;
        break;
    case 4:
        result = CarConfigs[CarTypeID].Names.PerformanceEngine;
        break;
    case 5:
        result = CarCustomizeManager_IsTurbo((DWORD*)_gCarCustomizeManager)
            ? CarConfigs[CarTypeID].Names.PerformanceTurbo
            : CarConfigs[CarTypeID].Names.PerformanceSupercharger;
        break;
    case 6:
        result = CarConfigs[CarTypeID].Names.PerformanceNitrous;
        break;
    default:
        return result;
    }
    return result;
}

unsigned int FEShoppingCartItem_GetPerfPkgLevelHash(int PerfPkgType, int PerfPkgLevel)
{
    unsigned int result; // eax

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    switch (PerfPkgType)
    {
    case 0: // Tires
        switch (PerfPkgLevel)
        {
        case 0:
        default:
            result = CarConfigs[CarTypeID].Names.PerformanceTiresStock;
            break;
        case 1:
            result = CarConfigs[CarTypeID].Names.PerformanceTiresStreet;
            break;
        case 2:
            result = CarConfigs[CarTypeID].Names.PerformanceTiresSuperStreet;
            break;
        case 3:
            result = CarConfigs[CarTypeID].Names.PerformanceTiresRace;
            break;
        case 4:
            result = CarConfigs[CarTypeID].Names.PerformanceTiresPro;
            break;
        case 5:
            result = CarConfigs[CarTypeID].Names.PerformanceTiresSuperPro;
            break;
        case 6:
            result = CarConfigs[CarTypeID].Names.PerformanceTiresUltimate;
            break;
        case 7:
            result = CarConfigs[CarTypeID].Names.PerformanceTiresJunkman;
            break;
        }
        break;
    case 1: // Brakes
        switch (PerfPkgLevel)
        {
        case 0:
        default:
            result = CarConfigs[CarTypeID].Names.PerformanceBrakesStock;
            break;
        case 1:
            result = CarConfigs[CarTypeID].Names.PerformanceBrakesStreet;
            break;
        case 2:
            result = CarConfigs[CarTypeID].Names.PerformanceBrakesSuperStreet;
            break;
        case 3:
            result = CarConfigs[CarTypeID].Names.PerformanceBrakesRace;
            break;
        case 4:
            result = CarConfigs[CarTypeID].Names.PerformanceBrakesPro;
            break;
        case 5:
            result = CarConfigs[CarTypeID].Names.PerformanceBrakesSuperPro;
            break;
        case 6:
            result = CarConfigs[CarTypeID].Names.PerformanceBrakesUltimate;
            break;
        case 7:
            result = CarConfigs[CarTypeID].Names.PerformanceBrakesJunkman;
            break;
        }
        break;
    case 2: // Suspension
        switch (PerfPkgLevel)
        {
        case 0:
        default:
            result = CarConfigs[CarTypeID].Names.PerformanceChassisStock;
            break;
        case 1:
            result = CarConfigs[CarTypeID].Names.PerformanceChassisStreet;
            break;
        case 2:
            result = CarConfigs[CarTypeID].Names.PerformanceChassisSuperStreet;
            break;
        case 3:
            result = CarConfigs[CarTypeID].Names.PerformanceChassisRace;
            break;
        case 4:
            result = CarConfigs[CarTypeID].Names.PerformanceChassisPro;
            break;
        case 5:
            result = CarConfigs[CarTypeID].Names.PerformanceChassisSuperPro;
            break;
        case 6:
            result = CarConfigs[CarTypeID].Names.PerformanceChassisUltimate;
            break;
        case 7:
            result = CarConfigs[CarTypeID].Names.PerformanceChassisJunkman;
            break;
        }
        break;
    case 3: // Transmission
        switch (PerfPkgLevel)
        {
        case 0:
        default:
            result = CarConfigs[CarTypeID].Names.PerformanceTransmissionStock;
            break;
        case 1:
            result = CarConfigs[CarTypeID].Names.PerformanceTransmissionStreet;
            break;
        case 2:
            result = CarConfigs[CarTypeID].Names.PerformanceTransmissionSuperStreet;
            break;
        case 3:
            result = CarConfigs[CarTypeID].Names.PerformanceTransmissionRace;
            break;
        case 4:
            result = CarConfigs[CarTypeID].Names.PerformanceTransmissionPro;
            break;
        case 5:
            result = CarConfigs[CarTypeID].Names.PerformanceTransmissionSuperPro;
            break;
        case 6:
            result = CarConfigs[CarTypeID].Names.PerformanceTransmissionUltimate;
            break;
        case 7:
            result = CarConfigs[CarTypeID].Names.PerformanceTransmissionJunkman;
            break;
        }
        break;
    case 4: // Engine
        switch (PerfPkgLevel)
        {
        case 0:
        default:
            result = CarConfigs[CarTypeID].Names.PerformanceEngineStock;
            break;
        case 1:
            result = CarConfigs[CarTypeID].Names.PerformanceEngineStreet;
            break;
        case 2:
            result = CarConfigs[CarTypeID].Names.PerformanceEngineSuperStreet;
            break;
        case 3:
            result = CarConfigs[CarTypeID].Names.PerformanceEngineRace;
            break;
        case 4:
            result = CarConfigs[CarTypeID].Names.PerformanceEnginePro;
            break;
        case 5:
            result = CarConfigs[CarTypeID].Names.PerformanceEngineSuperPro;
            break;
        case 6:
            result = CarConfigs[CarTypeID].Names.PerformanceEngineUltimate;
            break;
        case 7:
            result = CarConfigs[CarTypeID].Names.PerformanceEngineJunkman;
            break;
        }
        break;
    case 5: // Turbo/Supercharger
        if (CarCustomizeManager_IsTurbo((DWORD*)_gCarCustomizeManager))
        {
            switch (PerfPkgLevel)
            {
            case 0:
            default:
                result = CarConfigs[CarTypeID].Names.PerformanceTurboStock;
                break;
            case 1:
                result = CarConfigs[CarTypeID].Names.PerformanceTurboStreet;
                break;
            case 2:
                result = CarConfigs[CarTypeID].Names.PerformanceTurboSuperStreet;
                break;
            case 3:
                result = CarConfigs[CarTypeID].Names.PerformanceTurboRace;
                break;
            case 4:
                result = CarConfigs[CarTypeID].Names.PerformanceTurboPro;
                break;
            case 5:
                result = CarConfigs[CarTypeID].Names.PerformanceTurboSuperPro;
                break;
            case 6:
                result = CarConfigs[CarTypeID].Names.PerformanceTurboUltimate;
                break;
            case 7:
                result = CarConfigs[CarTypeID].Names.PerformanceTurboJunkman;
                break;
            }
        }
        else
        {
            switch (PerfPkgLevel)
            {
            case 0:
            default:
                result = CarConfigs[CarTypeID].Names.PerformanceSuperchargerStock;
                break;
            case 1:
                result = CarConfigs[CarTypeID].Names.PerformanceSuperchargerStreet;
                break;
            case 2:
                result = CarConfigs[CarTypeID].Names.PerformanceSuperchargerSuperStreet;
                break;
            case 3:
                result = CarConfigs[CarTypeID].Names.PerformanceSuperchargerRace;
                break;
            case 4:
                result = CarConfigs[CarTypeID].Names.PerformanceSuperchargerPro;
                break;
            case 5:
                result = CarConfigs[CarTypeID].Names.PerformanceSuperchargerSuperPro;
                break;
            case 6:
                result = CarConfigs[CarTypeID].Names.PerformanceSuperchargerUltimate;
                break;
            case 7:
                result = CarConfigs[CarTypeID].Names.PerformanceSuperchargerJunkman;
                break;
            }
        }
        break;
    case 6: // Nitrous
        switch (PerfPkgLevel)
        {
        case 0:
        default:
            result = CarConfigs[CarTypeID].Names.PerformanceNitrousStock;
            break;
        case 1:
            result = CarConfigs[CarTypeID].Names.PerformanceNitrousStreet;
            break;
        case 2:
            result = CarConfigs[CarTypeID].Names.PerformanceNitrousSuperStreet;
            break;
        case 3:
            result = CarConfigs[CarTypeID].Names.PerformanceNitrousRace;
            break;
        case 4:
            result = CarConfigs[CarTypeID].Names.PerformanceNitrousPro;
            break;
        case 5:
            result = CarConfigs[CarTypeID].Names.PerformanceNitrousSuperPro;
            break;
        case 6:
            result = CarConfigs[CarTypeID].Names.PerformanceNitrousUltimate;
            break;
        case 7:
            result = CarConfigs[CarTypeID].Names.PerformanceNitrousJunkman;
            break;
        }
        break;
    }

    return result;
}

void __fastcall FEShoppingCartItem_DrawPartName(DWORD* FEShoppingCartItem)
{
    int SelectablePart; // esi
    int PerfPkgType; // ebx
    int PerfPkgLevel; // esi
    int PerfPkgRealLevel; // esi
    const char* PartMaterialName; // eax MAPDST
    DWORD PaintTypeNameHash; // ebp
    DWORD PaintBrandNameHash; // eax
    DWORD SpeechColourNameHash; // eax MAPDST
    int RightDoorNumberLeft; // ebx
    int RightDoorNumberRight; // eax
    DWORD* RightDoorNumberLeftPart; // ebp
    DWORD* RightDoorNumberRightPart; // ebx
    DWORD SlotNameHash; // ebx
    const char* Decals; // eax MAPDST
    int PartNameBufLen; // eax
    DWORD* CartItemName; // ebx MAPDST
    DWORD CarSlotID; // esi MAPDST
    DWORD PartCategoryNameHash; // eax MAPDST
    const char* PartCategoryName; // eax MAPDST
    DWORD* ThePartInCart; // ebx MAPDST
    int CurrLanguage; // eax MAPDST
    DWORD PartNameHash; // eax MAPDST
    const char* PaintTypeName; // [esp-8h] [ebp-5Ch] MAPDST
    const char* LeftNumberName; // [esp-8h] [ebp-5Ch] MAPDST
    const char* SlotName; // [esp-8h] [ebp-5Ch] MAPDST
    const char* Junkman; // [esp-4h] [ebp-58h] MAPDST
    const char* PartName; // [esp-4h] [ebp-58h] MAPDST
    const char* SpeechColourName; // [esp-4h] [ebp-58h] MAPDST
    const char* RightNumberName; // [esp-4h] [ebp-58h] MAPDST
    DWORD StockHash; // [esp-4h] [ebp-58h]
    const char* RemoveDecal; // [esp-4h] [ebp-58h] MAPDST
    int InnerRadius; // [esp-4h] [ebp-58h] MAPDST
    char PartNameBuf[64]; // [esp+14h] [ebp-40h] BYREF

    SelectablePart = *(DWORD*)(*((DWORD*)FEShoppingCartItem + 21) + 12);
    if (!*(BYTE*)(SelectablePart + 28))
    {
        switch (*(DWORD*)(SelectablePart + 16))
        {
        case 44:
        case 62:
        case 63:
            ThePartInCart = *(DWORD**)(SelectablePart + 12);
            if (!CarPart_HasAppliedAttribute(ThePartInCart, bStringHash((char*)"CARBONFIBRE")))
                goto LABEL_68;
            ThePartInCart = *(DWORD**)(SelectablePart + 12);
            if (!CarPart_GetAppliedAttributeIParam(ThePartInCart, bStringHash((char*)"CARBONFIBRE"), 0))
                goto LABEL_68;
            CurrLanguage = GetCurrentLanguage();
            ThePartInCart = *(DWORD**)(SelectablePart + 12);
            CartItemName = *((DWORD**)FEShoppingCartItem + 11);
            CarSlotID = *(DWORD*)(SelectablePart + 16);
            if (CurrLanguage == 1)
            {
                PartNameHash = CarPart_GetAppliedAttributeUParam(ThePartInCart, bStringHash((char*)"LANGUAGEHASH"), 0);
                PartName = GetLocalizedString(PartNameHash);
                PartMaterialName = GetLocalizedString(0x5415B874);// CARBON
                goto LABEL_62;
            }
            PartNameHash = CarPart_GetAppliedAttributeUParam(ThePartInCart, bStringHash((char*)"LANGUAGEHASH"), 0);
            PartName = GetLocalizedString(PartNameHash);
            PartMaterialName = GetLocalizedString(0x5415B874);// CARBON
            goto LABEL_64;
        case 66: // FRONT_WHEEL
        case 67: // REAR_WHEEL
            ThePartInCart = *(DWORD**)(SelectablePart + 12);
            if (ThePartInCart == CarCustomizeManager_GetStockCarPart((DWORD*)_gCarCustomizeManager, 66))
                goto LABEL_66;
            PartNameHash = CarPart_GetAppliedAttributeUParam(ThePartInCart, bStringHash((char*)"LANGUAGEHASH"), 0);
            if (PartNameHash) PartName = GetLocalizedString(PartNameHash);
            else PartName = CarPart_GetName(*(DWORD**)(SelectablePart + 12));

            CarSlotID = *(DWORD*)(SelectablePart + 16);
            SlotNameHash = CarSlotID == 67 ? bStringHash((char*)"CUSTOMIZE_REAR_WHEEL") : bStringHash((char*)"CUSTOMIZE_FRONT_WHEEL");
            SlotName = GetLocalizedString(SlotNameHash);

            bSNPrintf(PartNameBuf, 64, "%s", PartName);
            PartNameBufLen = strlen(PartNameBuf);
            if (PartNameBufLen > 0)
            {
                if (PartNameBufLen > 6 && !PartNameHash) // Cut last 6 chars if it doesn't use LANGUAGEHASH attribute
                {
                    PartNameBufLen -= 6;
                    PartNameBuf[PartNameBufLen] = '\0';
                }

                CurrLanguage = GetCurrentLanguage();
                ThePartInCart = *(DWORD**)(SelectablePart + 12);
                CartItemName = *((DWORD**)FEShoppingCartItem + 11);
                
                if (CurrLanguage == 1)
                {
                    InnerRadius = (char)CarPart_GetAppliedAttributeIParam(ThePartInCart, 0xEB0101E2, 0);// INNER_RADIUS
                    PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                    PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                    FEPrintf_obj(CartItemName, "%s - %s : %s %$d\"", PartCategoryName, SlotName, PartNameBuf, InnerRadius);
                }
                else
                {
                    InnerRadius = (char)CarPart_GetAppliedAttributeIParam(ThePartInCart, 0xEB0101E2, 0);// INNER_RADIUS
                    PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                    PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                    FEPrintf_obj(CartItemName, "%s - %s: %s %$d\"", PartCategoryName, SlotName, PartNameBuf, InnerRadius);
                }
            }
            return;
        case 76:                                  // BASE_PAINT
            PaintTypeNameHash = 0x452B5481;         // CP_FILTER_METALLIC
            PaintBrandNameHash = CarPart_GetAppliedAttributeUParam(*(DWORD**)(SelectablePart + 12), 0xEBB03E66, 0);// BRAND_NAME
            if (PaintBrandNameHash > 0x3437A52)
            {
                if (PaintBrandNameHash == 0x3797533)
                    PaintTypeNameHash = 0xB715070A;
            }
            else
            {
                switch (PaintBrandNameHash)
                {
                case 0x3437A52:
                    PaintTypeNameHash = 0x452B5481;
                    break;
                case 0xDA27:
                    PaintTypeNameHash = 0xB3100A3E;
                    break;
                case 0x2DAAB07:
                    PaintTypeNameHash = 0xB6763CDE;
                    break;
                }
            }
            CurrLanguage = GetCurrentLanguage();
            ThePartInCart = *(DWORD**)(SelectablePart + 12);
            CarSlotID = *(DWORD*)(SelectablePart + 16);
            CartItemName = *((DWORD**)FEShoppingCartItem + 11);
            if (CurrLanguage == 1)
            {
                SpeechColourNameHash = CarPart_GetAppliedAttributeUParam(ThePartInCart, bStringHash((char*)"SPEECHCOLOUR"), 0);
                SpeechColourName = GetLocalizedString(SpeechColourNameHash);
                PaintTypeName = GetLocalizedString(PaintTypeNameHash);
                PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                FEPrintf_obj(CartItemName, "%s : %s %s", PartCategoryName, PaintTypeName, SpeechColourName);
            }
            else
            {
                SpeechColourNameHash = CarPart_GetAppliedAttributeUParam(ThePartInCart, bStringHash((char*)"SPEECHCOLOUR"), 0);
                SpeechColourName = GetLocalizedString(SpeechColourNameHash);
                PaintTypeName = GetLocalizedString(PaintTypeNameHash);
                PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                FEPrintf_obj(CartItemName, "%s: %s %s", PartCategoryName, PaintTypeName, SpeechColourName);
            }
            return;
        case 77:                                  // VINYL_LAYER0
            ThePartInCart = *(DWORD**)(SelectablePart + 12);
            if (ThePartInCart)
                goto LABEL_69;
        LABEL_66:
            CurrLanguage = GetCurrentLanguage();
            CartItemName = *((DWORD**)FEShoppingCartItem + 11);
            CarSlotID = *(DWORD*)(SelectablePart + 16);
            StockHash = 0x60A662F5;                 // CO_RETURN_TO_STOCK
            if (CurrLanguage != 1)
                goto LABEL_67;
            goto LABEL_33;
        case 78:                                  // PAINT_RIM
            CurrLanguage = GetCurrentLanguage();
            ThePartInCart = *(DWORD**)(SelectablePart + 12);
            CartItemName = *((DWORD**)FEShoppingCartItem + 11);
            CarSlotID = *(DWORD*)(SelectablePart + 16);
            if (CurrLanguage == 1)
            {
                SpeechColourNameHash = CarPart_GetAppliedAttributeUParam(ThePartInCart, bStringHash((char*)"SPEECHCOLOUR"), 0);
                PartName = GetLocalizedString(SpeechColourNameHash);
                PartMaterialName = GetLocalizedString(0xB3100A3E);// CP_FILTER_RIM
            LABEL_62:
                PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                FEPrintf_obj(CartItemName, "%s : %s %s", PartCategoryName, PartMaterialName, PartName);
            }
            else
            {
                SpeechColourNameHash = CarPart_GetAppliedAttributeUParam(ThePartInCart, bStringHash((char*)"SPEECHCOLOUR"), 0);
                PartName = GetLocalizedString(SpeechColourNameHash);
                PartMaterialName = GetLocalizedString(0xB3100A3E);
            LABEL_64:
                PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                FEPrintf_obj(CartItemName, "%s: %s %s", PartCategoryName, PartMaterialName, PartName);
            }
            return;
        case 83:                                  // DECALS (83-130)
        case 84:
        case 85:
        case 86:
        case 87:
        case 88:
        case 89:
        case 90:
        case 91:
        case 92:
        case 93:
        case 94:
        case 95:
        case 96:
        case 97:
        case 98:
        case 99:
        case 100:
        case 101:
        case 102:
        case 103:
        case 104:
        case 107:
        case 108:
        case 109:
        case 110:
        case 111:
        case 112:
        case 115:
        case 116:
        case 117:
        case 118:
        case 119:
        case 120:
        case 121:
        case 122:
        case 123:
        case 124:
        case 125:
        case 126:
        case 127:
        case 128:
        case 129:
        case 130:
            ThePartInCart = *(DWORD**)(SelectablePart + 12);
            if (ThePartInCart)
            {
                CarPart_GetAppliedAttributeUParam(ThePartInCart, 0xEBB03E66, 0);// BRAND_NAME
                ThePartInCart = *(DWORD**)(SelectablePart + 12);
                CarPart_GetAppliedAttributeUParam(ThePartInCart, bStringHash((char*)"NAME"), 0);
                switch (*(DWORD*)(SelectablePart + 16))
                {
                case 83:
                case 91:
                case 99:
                case 107:
                case 115:
                case 123:
                    SlotNameHash = bStringHash((char*)"CO_DECAL_SLOT_1");
                    goto LABEL_45;
                case 84:
                case 92:
                case 100:
                case 108:
                case 116:
                case 124:
                    SlotNameHash = bStringHash((char*)"CO_DECAL_SLOT_2");
                    goto LABEL_45;
                case 85:
                case 93:
                case 101:
                case 109:
                case 117:
                case 125:
                    SlotNameHash = bStringHash((char*)"CO_DECAL_SLOT_3");
                    goto LABEL_45;
                case 86:
                case 94:
                case 102:
                case 110:
                case 118:
                case 126:
                    SlotNameHash = bStringHash((char*)"CO_DECAL_SLOT_4");
                    goto LABEL_45;
                case 87:
                case 95:
                case 103:
                case 111:
                case 119:
                case 127:
                    SlotNameHash = bStringHash((char*)"CO_DECAL_SLOT_5");
                    goto LABEL_45;
                case 88:
                case 96:
                case 104:
                case 112:
                case 120:
                case 128:
                    SlotNameHash = bStringHash((char*)"CO_DECAL_SLOT_6");
                    goto LABEL_45;
                case 89:
                case 97:
                case 121:
                case 129:
                    SlotNameHash = bStringHash((char*)"CO_DECAL_SLOT_7");
                    goto LABEL_45;
                case 90:
                case 98:
                case 122:
                case 130:
                    SlotNameHash = bStringHash((char*)"CO_DECAL_SLOT_8");
                    //goto LABEL_45;
                LABEL_45:
                    CurrLanguage = GetCurrentLanguage();
                    ThePartInCart = *(DWORD**)(SelectablePart + 12);
                    CartItemName = *((DWORD**)FEShoppingCartItem + 11);
                    CarSlotID = *(DWORD*)(SelectablePart + 16);
                    if (CurrLanguage == 1)
                    {
                        PartName = CarPart_GetName(ThePartInCart);
                        SlotName = GetLocalizedString(SlotNameHash);
                        PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                        PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                        Decals = GetLocalizedString(0x955980BC);// CO_DECALS
                        FEPrintf_obj(CartItemName, "%s : %s %s %s", Decals, PartCategoryName, SlotName, PartName);
                    }
                    else
                    {
                        PartName = CarPart_GetName(ThePartInCart);
                        SlotName = GetLocalizedString(SlotNameHash);
                        PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                        PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                        Decals = GetLocalizedString(0x955980BC);
                        FEPrintf_obj(CartItemName, "%s: %s %s %s", Decals, PartCategoryName, SlotName, PartName);
                    }
                    break;
                default:
                    CurrLanguage = GetCurrentLanguage();
                    ThePartInCart = *(DWORD**)(SelectablePart + 12);
                    CartItemName = *((DWORD**)FEShoppingCartItem + 11);
                    CarSlotID = *(DWORD*)(SelectablePart + 16);
                    if (CurrLanguage == 1)
                    {
                        PartName = CarPart_GetName(ThePartInCart);
                        PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                        PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                        Decals = GetLocalizedString(0x955980BC);
                        FEPrintf_obj(CartItemName, "%s : %s %s", Decals, PartCategoryName, PartName);
                    }
                    else
                    {
                        PartName = CarPart_GetName(ThePartInCart);
                        PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                        PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                        Decals = GetLocalizedString(0x955980BC);
                        FEPrintf_obj(CartItemName, "%s: %s %s", Decals, PartCategoryName, PartName);
                    }
                    break;
                }
            }
            else
            {
                CurrLanguage = GetCurrentLanguage();
                CartItemName = *((DWORD**)FEShoppingCartItem + 11);
                CarSlotID = *(DWORD*)(SelectablePart + 16);
                if (CurrLanguage == 1)
                {
                    RemoveDecal = GetLocalizedString(0x7177DC17);
                    PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                    PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                    Decals = GetLocalizedString(0x955980BC);
                    FEPrintf_obj(CartItemName, "%s : %s - %s", Decals, PartCategoryName, RemoveDecal);
                }
                else
                {
                    RemoveDecal = GetLocalizedString(0x7177DC17);
                    PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                    PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                    Decals = GetLocalizedString(0x955980BC);
                    FEPrintf_obj(CartItemName, "%s: %s - %s", Decals, PartCategoryName, RemoveDecal);
                }
            }
            return;
        case 113:
            RightDoorNumberLeft = CarCustomizeManager_IsPartTypeInCart_ID((DWORD*)_gCarCustomizeManager, 113);
            RightDoorNumberRight = CarCustomizeManager_IsPartTypeInCart_ID((DWORD*)_gCarCustomizeManager, 114);
            if (!RightDoorNumberLeft || !RightDoorNumberRight)
                return;
            RightDoorNumberLeftPart = *(DWORD**)(*(DWORD*)(RightDoorNumberLeft + 12) + 12);
            RightDoorNumberRightPart = *(DWORD**)(*(DWORD*)(RightDoorNumberRight + 12) + 12);
            if (RightDoorNumberLeftPart && RightDoorNumberRightPart)
            {
                CurrLanguage = GetCurrentLanguage();
                CarSlotID = *(DWORD*)(SelectablePart + 16);
                CartItemName = *((DWORD**)FEShoppingCartItem + 11);
                if (CurrLanguage == 1)
                {
                    RightNumberName = CarPart_GetName(RightDoorNumberRightPart);
                    LeftNumberName = CarPart_GetName(RightDoorNumberLeftPart);
                    PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                    PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                    FEPrintf_obj(CartItemName, "%s : %s%s", PartCategoryName, LeftNumberName, RightNumberName);
                }
                else
                {
                    RightNumberName = CarPart_GetName(RightDoorNumberRightPart);
                    LeftNumberName = CarPart_GetName(RightDoorNumberLeftPart);
                    PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                    PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                    FEPrintf_obj(CartItemName, "%s: %s%s", PartCategoryName, LeftNumberName, RightNumberName);
                }
                return;
            }
            CurrLanguage = GetCurrentLanguage();
            CartItemName = *((DWORD**)FEShoppingCartItem + 11);
            CarSlotID = *(DWORD*)(SelectablePart + 16);
            StockHash = 0xBE434A38;                 // CN_REMOVE_NUMBERS
            if (CurrLanguage == 1)
            {
            LABEL_33:
                PartName = GetLocalizedString(StockHash);
                goto LABEL_76;
            }
        LABEL_67:
            PartName = GetLocalizedString(StockHash);
            goto LABEL_78;
        default:
        LABEL_68:
            ThePartInCart = *(DWORD**)(SelectablePart + 12);
        LABEL_69:
            if (!CarPart_HasAppliedAttribute(ThePartInCart, bStringHash((char*)"LANGUAGEHASH")))
            {
                CurrLanguage = GetCurrentLanguage();
                ThePartInCart = *(DWORD**)(SelectablePart + 12);
                CartItemName = *((DWORD**)FEShoppingCartItem + 11);
                CarSlotID = *(DWORD*)(SelectablePart + 16);
                if (CurrLanguage == 1)
                {
                    PartName = CarPart_GetName(ThePartInCart);
                LABEL_76:
                    PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                    PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                    FEPrintf_obj(CartItemName, "%s : %s", PartCategoryName, PartName);
                }
                else
                {
                    PartName = CarPart_GetName(ThePartInCart);
                LABEL_78:
                    PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                    PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                    FEPrintf_obj(CartItemName, "%s: %s", PartCategoryName, PartName);
                }
                return;
            }
            CurrLanguage = GetCurrentLanguage();
            ThePartInCart = *(DWORD**)(SelectablePart + 12);
            CartItemName = *((DWORD**)FEShoppingCartItem + 11);
            CarSlotID = *(DWORD*)(SelectablePart + 16);
            if (CurrLanguage == 1)
            {
                PartNameHash = CarPart_GetAppliedAttributeUParam(ThePartInCart, bStringHash((char*)"LANGUAGEHASH"), 0);
                PartName = GetLocalizedString(PartNameHash);
                PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
                PartCategoryName = GetLocalizedString(PartCategoryNameHash);
                FEPrintf_obj(CartItemName, "%s : %s", PartCategoryName, PartName);
                return;
            }
            PartNameHash = CarPart_GetAppliedAttributeUParam(ThePartInCart, bStringHash((char*)"LANGUAGEHASH"), 0);
            PartName = GetLocalizedString(PartNameHash);
            PartCategoryNameHash = FEShoppingCartItem_GetCarPartCatHash(FEShoppingCartItem, 0, CarSlotID);
            break;
        }

        PartCategoryName = GetLocalizedString(PartCategoryNameHash);
        FEPrintf_obj(CartItemName, "%s: %s", PartCategoryName, PartName);
        return;
    }
    PerfPkgType = *(DWORD*)(SelectablePart + 24);
    PerfPkgLevel = *(DWORD*)(SelectablePart + 20);
    
    switch (PerfPkgLevel)
    {
    case 0:
        PerfPkgRealLevel = 0; // stock
        break;
    case 7:
        PerfPkgRealLevel = 7; // junkman
        break;
    default:
        PerfPkgRealLevel = PerfPkgLevel
            - Physics_Upgrades_GetMaxLevel((DWORD*)(_FECarRecord + 4), PerfPkgType)
            + 6;
        break;
    }

    CurrLanguage = GetCurrentLanguage();
    CartItemName = *((DWORD**)FEShoppingCartItem + 11);
    if (CurrLanguage == 1)
    {
        PartNameHash = FEShoppingCartItem_GetPerfPkgLevelHash(PerfPkgType, PerfPkgRealLevel);
        PartName = GetLocalizedString(PartNameHash);
        PartCategoryNameHash = FEShoppingCartItem_GetPerfPkgCatHash(PerfPkgType);

        PartCategoryName = GetLocalizedString(PartCategoryNameHash);
        FEPrintf_obj(CartItemName, "%s : %s", PartCategoryName, PartName);
        return;
    }
    PartNameHash = FEShoppingCartItem_GetPerfPkgLevelHash(PerfPkgType, PerfPkgRealLevel);
    PartName = GetLocalizedString(PartNameHash);
    PartCategoryNameHash = FEShoppingCartItem_GetPerfPkgCatHash(PerfPkgType);

    PartCategoryName = GetLocalizedString(PartCategoryNameHash);
    FEPrintf_obj(CartItemName, "%s: %s", PartCategoryName, PartName);
    return;
}