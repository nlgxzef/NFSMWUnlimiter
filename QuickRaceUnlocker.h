#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

bool __cdecl QuickRaceUnlocker_IsCarUnlocked(int eUnlockFilters, unsigned int Handle, int a3)
{
    char UAT; // bl
    DWORD* FEPlayerCarDB; // edx MAPDST
    int CarTypeID; // eax
    DWORD* carRecord; // esi
    DWORD* UserProfile; // edi
    BYTE CurrentBin; // dl
    bool InitiallyUnlocked;
    char IsUnlocked; // bl
    bool IsStockCareerOrMyCars; // al
    unsigned int PresetHash; // esi
    bool IsNA; // zf
    bool IsUnlockConditionNotMet; // zf
    DWORD Attrib[5]; // [esp+Ch] [ebp-20h] BYREF
    int v17; // [esp+28h] [ebp-4h]

    UAT = *(bool*)_UnlockAllThings;
    DWORD* FEDatabase = *(DWORD**)_FEDatabase;

    if (a3 < 0 || a3 >= 2)
        FEPlayerCarDB = 0;
    else
        FEPlayerCarDB = (DWORD*)(*((DWORD*)FEDatabase + a3 + 4) + 1044);
    carRecord = FEPlayerCarDB_GetCarRecordByHandle(FEPlayerCarDB, Handle);

    Attrib_Gen_frontend_frontend(Attrib, carRecord[1], 0, 0);// FEKey

    UserProfile = (DWORD*)*((DWORD*)FEDatabase + 4);
    CurrentBin = *((BYTE*)UserProfile + 176);   // UserProfile->CareerSettings->CurrentBin

    IsUnlocked = (*(BYTE*)(Attrib[2] + 89) >= CurrentBin) | UAT;
    IsStockCareerOrMyCars = (carRecord[3] & 7) != 0;// FilterBits
    IsNA = (carRecord[3] & 0xF0000) == 0;
    v17 = 0;

    if (!IsNA && IsStockCareerOrMyCars)
    {
        CarTypeID = FECarRecord_GetType(carRecord);

        switch (CarConfigs[CarTypeID].Main.InitiallyUnlocked)
        {
        case 0:
            InitiallyUnlocked = 0;
            break;
        case 1:
            InitiallyUnlocked = 1;
            break;
        case -1:
        default:
            switch (CarTypeID)
            {
            case 5:                                   // RX8
            case 6:                                   // IMPREZAWRX
            case 8:                                   // MUSTANGGT
            case 23:                                  // SL500
            case 24:                                  // 997S
            case 47:                                  // IS300
            case 62:                                  // GTI
            case 67:                                  // GALLARDO
            case 68:                                  // COBALTSS
            case 74:                                  // PUNTO
                InitiallyUnlocked = 1;
                break;
            default:
                InitiallyUnlocked = 0;
                break;
            }
            break;
        }
        
    _ReturnIfUnlocked:
        v17 = -1;
        Attrib_Instance_dtInstance(Attrib);
        return IsUnlocked || InitiallyUnlocked;
    }
    if ((carRecord[3] & 0xF0000) == 0 || (carRecord[3] & 8) == 0) // If N/A or not a bonus car
        goto _ReturnIfUnlocked;

    PresetHash = carRecord[0];

    // ToDo: Check unlock condition from _BonusCars.ini.
    // First, find preset in ini
    // If found, check the unlock condition type
    // If the required data for the condition is valid, go ahead.
    // If not, return the value from in-game function instead

    char* PresetName;
    int BinToBeat;

    int NumberOfBonusCars = BonusCars.size();

    // Check if any of our custom bonus cars are marked as CE only
    for (int i = 0; i < NumberOfBonusCars; i++)
    {
        if (BonusCars[i].Category == 0xF0008) // Is a bonus car
        {
            PresetName = BonusCars[i].PresetName;
            if (FEHashUpper(PresetName) == PresetHash) // If it's the preset we are checking
            {
                // If the car is marked as CE only, do CE check instead.
                if (BonusCars[i].CEOnly) goto _CEONLY;

                // Get and check if the condition is met
                int UnlockConditionType = BonusCars[i].UnlockConditionType;

                switch (UnlockConditionType)
                {
                case 0: // Initially unlocked
                    goto _Unlocked;
                    break;
                case 1: // Beat Blacklist member
                    BinToBeat = BonusCars[i].Blacklist;
                    if (CurrentBin < BinToBeat) goto _Unlocked;
                    else goto _Locked;
                    break;
                case 2: // Complete CS Event #68 (special flag)
                    if (UserProfile[43] & 0x8000) goto _Unlocked;
                    else goto _Locked;
                    break;
                case 3: // Enter "castrol" cheat code (special flag)
                    if (UserProfile[43] & 0x40000) goto _Unlocked;
                    else goto _Locked;
                    break;
                case 4: // Complete CS 100% (special flag)
                    if (*((BYTE*)UserProfile + 174) & 1) goto _Unlocked;
                    else goto _Locked;
                    break;
                case 5: // Complete Career mode at least once  (special flag)
                case 6: // Complete Game 100% (same as 5??)
                    if (UserProfile[43] & 0x4000) goto _Unlocked;
                    else goto _Locked;
                    break;
                case -1: // None (Use in game function for a hardcoded value instead)
                default:
                    goto _InGameFunction;
                    break;

                }
            }
        }
    }
    // If the preset cannot be found in the ini
    goto _InGameFunction;

_CEONLY:
    IsUnlockConditionNotMet = *(bool*)_IsCollectorsEdition == 0;
    if (IsUnlockConditionNotMet)
        goto _Locked;

_Unlocked:
    v17 = -1;
    Attrib_Instance_dtInstance(Attrib);
    return 1;

_Locked:
    v17 = -1;
    Attrib_Instance_dtInstance(Attrib);
    return 0;

    // If the bonus car preset isn't in the custom list, also try the in-game function
_InGameFunction:
    v17 = -1;
    Attrib_Instance_dtInstance(Attrib);
    return QuickRaceUnlocker_IsCarUnlocked_Game(eUnlockFilters, Handle, a3);
}