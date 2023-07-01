#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

bool __fastcall CarCustomizeManager_IsCastrolCar(DWORD* CarCustomizeManager, int edx_unused)
{
    bool result; // al

    int CarType; // eax
    CarType = FECarRecord_GetType(*(void**)_FECarRecord);

    // Get config files
    sprintf(CarTypeName, GetCarTypeName(CarType));
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    int EngineType = GetCarIntOption(CarINI, GeneralINI, "Main", "EngineType", -1);

    if ((EngineType == -1 && CarType == 52) || EngineType == 1) // FORDGT
        result = EasterEggs_IsEasterEggUnlocked((DWORD*)gEasterEggs, 4);
    else
        result = 0;
    return result;
}

bool __fastcall CarCustomizeManager_IsRotaryCar(DWORD* CarCustomizeManager, int edx_unused)
{
    int CarType; // eax
    CarType = FECarRecord_GetType(*(void**)_FECarRecord);

    // Get config files
    sprintf(CarTypeName, GetCarTypeName(CarType));
    sprintf(CarININame, "UnlimiterData\\%s.ini", CarTypeName);
    CIniReader CarINI(CarININame);
    CIniReader GeneralINI("UnlimiterData\\_General.ini");

    int EngineType = GetCarIntOption(CarINI, GeneralINI, "Main", "EngineType", -1);

    if (EngineType == -1) return CarType == 5 || CarType == 56; // RX7, RX8
    else return EngineType == 2;
}

int __fastcall CarCustomizeManager_GetPartPrice(DWORD* _CarCustomizeManager, void* EDX_Unused, DWORD* TheSelectablePart)
{
    int PerfPartType; // ebx MAPDST
    int MaxLevel; // eax MAPDST
    int MaxPackages; // eax
    int PerfPartLevel; // edx
    int UnlockFilter; // eax MAPDST
    int CarSlotID; // [esp-Ch] [ebp-18h]
    int UpgradeLevel; // [esp-8h] [ebp-14h] MAPDST

    int Cost = 0;
    if (TheSelectablePart && !CustomizeIsInBackRoom())
    {
        if (*((BYTE*)TheSelectablePart + 28))   // Performance Parts
        {
            PerfPartType = TheSelectablePart[6];
            MaxLevel = Physics_Upgrades_GetMaxLevel(_CarCustomizeManager + 2, PerfPartType);
            PerfPartLevel = TheSelectablePart[5];
            MaxPackages = CarCustomizeManager_GetMaxPackages(_CarCustomizeManager, PerfPartType);
            UpgradeLevel = PerfPartLevel - MaxLevel + MaxPackages;
            UnlockFilter = CarCustomizeManager_GetUnlockFilter();
            return UnlockSystem_GetPerfPackageCost(UnlockFilter, PerfPartType, UpgradeLevel, 0);
        }

        // Check for a cost attribute
        DWORD* TheCarPart = (DWORD*)TheSelectablePart[3];
        if (TheCarPart)
        {
            Cost = CarPart_GetAppliedAttributeUParam(TheCarPart, bStringHash("COST"), -1);
        }

        if (Cost == -1) // If no attribute is set, go for the default stuff instead
        {
            switch (*((DWORD*)TheSelectablePart + 4))// Body and Visual Parts
            {
            case 79:                                  // VINYL_COLOUR0_0
            case 80:                                  // VINYL_COLOUR0_1
            case 81:                                  // VINYL_COLOUR0_2
            case 82:                                  // VINYL_COLOUR0_3
            case 133:                                 // HUD_BACKING_COLOUR
            case 134:                                 // HUD_NEEDLE_COLOUR
            case 135:                                 // HUD_CHARACTER_COLOUR
                break;
            default:
                UpgradeLevel = *((DWORD*)TheSelectablePart + 3);
                CarSlotID = *((DWORD*)TheSelectablePart + 4);
                UnlockFilter = CarCustomizeManager_GetUnlockFilter();
                Cost = UnlockSystem_GetCarPartCost(UnlockFilter, CarSlotID, TheCarPart, 0);
                break;
            }
        }
    }
    return Cost;
}

void __declspec(naked) IsNewCodeCaveParts()
{
    _asm
    {
        ja IsNotNew
        push 0x7A50FF
        retn

        IsNotNew:
            xor al,al
            pop edi
            pop esi
            retn 4
    }
}

void __declspec(naked) IsNewCodeCaveRims()
{
    _asm
    {
        xor al, al
        pop edi
        pop esi
        retn 4
    }
}

void __declspec(naked) IsNewCodeCaveVisual()
{
    _asm
    {
        ja IsNotNew
        push 0x7A51DF
        retn

        IsNotNew :
            xor al, al
            pop edi
            pop esi
            retn 4
    }
}

void __declspec(naked) IsLockedCodeCaveParts()
{
    _asm
    {
        ja IsNotLocked
        push 0x7BAD3A
        retn

        IsNotLocked :
            xor al, al
            pop edi
            pop esi
            pop ebx
            retn 8
    }
}

void __declspec(naked) IsLockedCodeCaveVisual()
{
    _asm
    {
        ja IsNotLocked
        push 0x7BAEE6
        retn

        IsNotLocked :
            xor al, al
            pop edi
            pop esi
            pop ebx
            retn 8
    }
}

bool __fastcall CarCustomizeManager_AreAllRimsStock(DWORD* _CarCustomizeManager, void* EDX_Unused)
{
    DWORD* StockFrontWheel = CarCustomizeManager_GetStockCarPart((DWORD*)_gCarCustomizeManager, 66); // FRONT_WHEEL
    DWORD* StockRearWheel = CarCustomizeManager_GetStockCarPart((DWORD*)_gCarCustomizeManager, 67); // FRONT_WHEEL

    DWORD* InstalledFrontWheel = CarCustomizeManager_GetInstalledCarPart((DWORD*)_gCarCustomizeManager, 66);
    DWORD* InstalledRearWheel = CarCustomizeManager_GetInstalledCarPart((DWORD*)_gCarCustomizeManager, 67);

    bool IsFrontStock = StockFrontWheel == InstalledFrontWheel;
    bool IsRearStock = !InstalledRearWheel || StockRearWheel == InstalledRearWheel;

    return IsFrontStock && IsRearStock;
}