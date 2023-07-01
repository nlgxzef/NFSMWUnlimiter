#include "stdio.h"
#include "InGameFunctions.h"
#include "includes\IniReader.h"

bool __cdecl QuickRaceUnlocker_IsCarUnlocked(int eUnlockFilters, unsigned int Handle, int a3)
{
    char UAT; // bl
    DWORD* FEPlayerCarDB; // edx MAPDST
    int CarID; // eax
    DWORD* carRecord; // esi
    DWORD* UserProfile; // edi
    BYTE CurrentBin; // dl
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
        switch (FECarRecord_GetType(carRecord))
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
            IsUnlocked = 1;
            break;
        default:
            break;
        }
    _ReturnIfUnlocked:
        v17 = -1;
        Attrib_Instance_dtInstance(Attrib);
        return IsUnlocked;
    }
    if ((carRecord[3] & 0xF0000) == 0 || (carRecord[3] & 8) == 0) // If N/A or not a bonus car
        goto _ReturnIfUnlocked;

    PresetHash = carRecord[0];

    // ToDo: Check unlock condition from _BonusCars.ini.
    // First, find preset in ini
    // If found, check the unlock condition type
    // If the required data for the condition is valid, go ahead.
    // If not, return the value from in-game function instead

    char BonusCarNameBuf[16];
    CIniReader BonusCars("UnlimiterData\\_BonusCars.ini");
    char* PresetName;
    int BinToBeat;

    int NumberOfBonusCars = BonusCars.ReadInteger("BonusCars", "NumberOfBonusCars", -1);

    // Check if any of our custom bonus cars are marked as CE only
    for (int i = 0; i <= NumberOfBonusCars; i++)
    {
        sprintf(BonusCarNameBuf, "BonusCar%d", i);
        if (BonusCars.ReadInteger(BonusCarNameBuf, "Category", 0xF0008) == 0xF0008) // Is a bonus car
        {
            PresetName = BonusCars.ReadString(BonusCarNameBuf, "PresetName", "");
            if (FEHashUpper(PresetName) == PresetHash) // If it's the preset we are checking
            {
                // If the car is marked as CE only, do CE check instead.
                if (BonusCars.ReadInteger(BonusCarNameBuf, "CEOnly", 0) != 0) goto _CEONLY;

                // Get and check if the condition is met
                int UnlockConditionType = BonusCars.ReadInteger(BonusCarNameBuf, "UnlockConditionType", -1);

                switch (UnlockConditionType)
                {
                case 0: // Initially unlocked
                    goto _Unlocked;
                    break;
                case 1: // Beat Blacklist member
                    BinToBeat = BonusCars.ReadInteger(BonusCarNameBuf, "Blacklist", -1);
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


    /* VANILLA CODE FOR REFERENCE
    // If there is no condition present in the file, return to defaults:
    if (PresetHash <= 0x13624E)
    {
        if (PresetHash != 0x13624E)
        {
            switch (PresetHash)
            {
            case 0x965F:
                if (CurrentBin <= 1)
                    goto _Unlocked;
                goto _Locked;
            case 0x9660:
                if (CurrentBin <= 2)
                    goto _Unlocked;
                goto _Locked;
            case 0x9661:
                if (CurrentBin <= 3)
                    goto _Unlocked;
                goto _Locked;
            case 0x9662:
                if (CurrentBin <= 4)
                    goto _Unlocked;
                goto _Locked;
            case 0x9663:
                if (CurrentBin <= 5)
                    goto _Unlocked;
                goto _Locked;
            case 0x9664:
                if (CurrentBin <= 6)
                    goto _Unlocked;
                goto _Locked;
            case 0x9665:
                if (CurrentBin <= 7)
                    goto _Unlocked;
                goto _Locked;
            case 0x9666:
                if (CurrentBin <= 8)
                    goto _Unlocked;
                goto _Locked;
            default:
                goto _Locked;
            }
        }
        if (CurrentBin <= 9)
            goto _Unlocked;
    _Locked:
        v17 = -1;
        Attrib_Instance_dtInstance(Attrib);
        return 0;
    }
    if (PresetHash <= 0x2D642B8)
    {
        if (PresetHash != 0x2D642B8)
        {
            switch (PresetHash)
            {
            case 0x13624F:                         // BL11
                if (CurrentBin <= 10)
                    goto _Unlocked;
                goto _Locked;
            case 0x136250:                         // BL12
                if (CurrentBin <= 11)
                    goto _Unlocked;
                goto _Locked;
            case 0x136251:                         // BL13
                if (CurrentBin <= 12)
                    goto _Unlocked;
                goto _Locked;
            case 0x136252:                         // BL14
                if (CurrentBin <= 13)
                    goto _Unlocked;
                goto _Locked;
            case 0x136253:                         // BL15
                if (CurrentBin <= 14)
                    goto _Unlocked;
                goto _Locked;
            default:
                goto _Locked;
            }
        }
        goto _CEONLY;
    }
    if (PresetHash > 0x54653C71)
    {
        if (PresetHash > 0xCB6AAF2F)
        {
            if (PresetHash != 0xE1075862 && PresetHash != 0xE115EAD0)// not CE_997S nor CE_SL65
                goto _Locked;
            goto _CEONLY;
        }
        if (PresetHash == 0xCB6AAF2F)             // BONUS_SL65
        {
            IsUnlockConditionNotMet = (UserProfile[43] & 0x8000) == 0;
            goto LABEL_75;
        }
        if (PresetHash != 0x54655133 && PresetHash != 0x582F21D9)// not CE_GT2 nor CE_CAMARO
        {
            IsNA = PresetHash == 0x634D1BD2;          // CE_CORVETTE
        LABEL_58:
            if (!IsNA)
                goto _Locked;
            goto _CEONLY;
        }
    }
    else if (PresetHash != 0x54653C71)          // not CE_C6R
    {
        if (PresetHash > 0x2CF370F0)
        {
            if (PresetHash == 0x2CF385B2)           // BONUS_GT2
            {
                IsUnlockConditionNotMet = (*((BYTE*)UserProfile + 174) & 1) == 0;
                goto LABEL_75;
            }
            if (PresetHash == 0x34498EB2)           // CASTROLGT
            {
                IsUnlockConditionNotMet = (UserProfile[43] & 0x40000) == 0;
                goto LABEL_75;
            }
            IsNA = PresetHash == 0x363A1FEA;          // CE_GTRSTREET
        }
        else
        {
            if (PresetHash == 0x2CF370F0 || PresetHash == 0x3A94520)// BONUS_C6R || E3_DEMO_BMW
            {
                IsUnlockConditionNotMet = (UserProfile[43] & 0x4000) == 0;
                goto LABEL_75;
            }
            if (PresetHash == 0x3D3401A)            // CE_SL500
                goto _CEONLY;
            IsNA = PresetHash == 0x3D8A6D1;           // CE_SUPRA
        }
        goto LABEL_58;
    }
_CEONLY:
    IsUnlockConditionNotMet = *(bool*)_IsCollectorsEdition == 0;
LABEL_75:
    if (IsUnlockConditionNotMet)
        goto _Locked;
_Unlocked:
    v17 = -1;
    Attrib_Instance_dtInstance(Attrib);
    return 1;
    */
}