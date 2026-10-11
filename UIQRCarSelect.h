#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

void(__thiscall* UIQRCarSelect_RefreshHeader_Game)(DWORD*) = (void(__thiscall*)(DWORD*))0x7ADA50;

unsigned int __fastcall UIQRCarSelect_GetBonusUnlockText(DWORD* UIQRCarSelect, void* EDX_Unused, DWORD* FECarRecord)
{
    unsigned int PresetHash = FECarRecord[0];

	char* PresetName;
	DWORD CustomUnlockStringHash;

	int NumberOfBonusCars = BonusCars.size();

	// Check if any of our custom bonus cars are marked as CE only
	for (int i = 0; i < NumberOfBonusCars; i++)
	{
		if (BonusCars[i].Category == 0xF0008) // Is a bonus car
		{
			PresetName = BonusCars[i].PresetName;
			if (FEHashUpper(PresetName) == PresetHash) // If it's the preset we are checking
			{
				// Check if user has given a custom unlock condition string
				CustomUnlockStringHash = BonusCars[i].UnlockConditionStringHash;
				if (CustomUnlockStringHash != -1)
				{
					if (DoesStringExist(CustomUnlockStringHash))
						return CustomUnlockStringHash;
				}
				// or else...
				// Check if the car is CE only but the game is not CE
				if (BonusCars[i].CEOnly && (*(bool*)_IsCollectorsEdition == 0))
				{
					return CT_bStringHash("CARLOT_BONUSCAR_UNLOCK_MSG_05");
				}
				
				// Get and check the condition
				int UnlockConditionType = BonusCars[i].UnlockConditionType;

				switch (UnlockConditionType)
				{
				case 0: // Initially unlocked
					return CT_bStringHash("CARLOT_BONUSCAR_UNLOCK_MSG_06");
					break;
				case 1: // Beat Blacklist member
					return CT_bStringHash("CARLOT_UNLOCK_MSG_01");
					break;
				case 2: // Complete CS Event #68 (special flag)
					return CT_bStringHash("CARLOT_BONUSCAR_UNLOCK_MSG_01");
					break;
				case 3: // Enter "castrol" cheat code (special flag)
					return CT_bStringHash("CARLOT_BONUSCAR_UNLOCK_MSG_07");
					break;
				case 4: // Complete CS 100% (special flag)
					return CT_bStringHash("CARLOT_BONUSCAR_UNLOCK_MSG_02");
					break;
				case 5: // Complete Career mode at least once (special flag)
					return CT_bStringHash("CARLOT_BONUSCAR_UNLOCK_MSG_03");
					break;
				case 6: // Complete Game 100% (special flag, same as 5??)
					return CT_bStringHash("CARLOT_BONUSCAR_UNLOCK_MSG_04");
					break;
				case -1: // None (Use in game function for a hardcoded value instead)
				default:
					goto _InGameFunction;
					break;
				}
			}
		}
	}
	// If not found, check in game function
_InGameFunction:
	return UIQRCarSelect_GetBonusUnlockText_Game(UIQRCarSelect, FECarRecord);
}

int __fastcall UIQRCarSelect_GetBonusUnlockBinNumber(DWORD* UIQRCarSelect, void* EDX_Unused, DWORD* FECarRecord)
{
    unsigned int PresetHash = FECarRecord[0];
    char* PresetName;

    int NumberOfBonusCars = BonusCars.size();

    for (int i = 0; i < NumberOfBonusCars; i++)
    {
		if (BonusCars[i].Category == 0xF0008) // Is a bonus car
        {
			PresetName = BonusCars[i].PresetName;
            if (FEHashUpper(PresetName) == PresetHash) // If it's the preset we are checking
            {
                // Get and check if the condition is met
                int UnlockConditionType = BonusCars[i].UnlockConditionType;

				if (UnlockConditionType == 1)
					return BonusCars[i].Blacklist;
                else break;
            }
        }
    }

    return UIQRCarSelect_GetBonusUnlockBinNumber_Game(UIQRCarSelect, FECarRecord);
}

void __fastcall UIQRCarSelect_RefreshCarList(DWORD* UIQRCarSelect, void* EDX_Unused)
{
	DWORD* ListHead = (DWORD*)UIQRCarSelect[11]; // FilteredCarsList[0]
	DWORD* ListItem = UIQRCarSelect + 11; // FilteredCarsList
	DWORD* ListNext, * ListPrev;
    DWORD* ASelectableCar;

    DWORD* FEDatabase = *(DWORD**)_FEDatabase;
	FEPlayerCarDB* stable;
    int unlock_filter;

    bool UseBonusCarsHooks = BonusCarsHook && BonusCars.size();

	if (ListHead != UIQRCarSelect + 11)
	{
		do
		{
			ListNext = (DWORD*)*ListHead;
			ListPrev = (DWORD*)ListHead[1];
			*ListPrev = *ListHead;
			ListNext[1] = (DWORD)ListPrev;
			j_free(ListHead);
			ListHead = (DWORD*)*ListItem;
		} while ((DWORD*)*ListItem != ListItem);
	}

	int filter = UIQRCarSelect[107]; // Filter

	if ((filter & FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_BONUS) != 0 && !UseBonusCarsHooks)
	{
		UIQRCarSelect_RefreshBonusCarList(UIQRCarSelect);
	}
	else
	{
        int iPlayerNum = UIQRCarSelect[106];
        int CarIndex = 0;
        if (iPlayerNum > 1)
        {
            stable = 0;
        }
        else
        {
			DWORD* UserProfile = (DWORD*)FEDatabase[4 + iPlayerNum];
            stable = (FEPlayerCarDB*)(UserProfile + 261); //&FEDatabase->CurrentUserProfiles[iPlayerNum]->PlayersCarStable;

            // Use the stable we created at boot for stock cars instead
            if (StockCarsHook && ((filter & FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_STOCK) != 0)) stable = UnlimiterCarStable;
        }

        int FEGameMode = FEDatabase[0x12C/4];//FEDatabase->FEGameMode;

        if ((FEGameMode & eFEGameModes::eFE_GAME_MODE_CAREER) != 0)
        {
            unlock_filter = 2;
        }
        else
        {
            if ((FEGameMode & eFEGameModes::eFE_GAME_MODE_QUICK_RACE) != 0)
            {
                unlock_filter = 1;
            }
            else
            {
                if ((FEGameMode & eFEGameModes::eFE_GAME_MODE_ONLINE) != 0)
                    goto UnlockFilter7;
                unlock_filter = 1;
                if ((FEGameMode & eFEGameModes::eFE_GAME_MODE_LAN) != 0)
                    UnlockFilter7:
                unlock_filter = 7;
            }
        }
        do
        {
            FECarRecord* record = stable->GetCarByIndex(CarIndex);
            if (record->Handle != -1)
            {
                if (record->MatchesFilter(filter))
                {
                    bool IsCarUnlocked = 1; // UnlockSystem_IsCarUnlocked(unlock_filter, record->Handle, iPlayerNum);
                    *(bool*)_UnlockAllThings = 1;
                    if (!GetMikeMannBuild() || IsValidMikeMannCar((DWORD*)record, filter))
                    {
                        ASelectableCar = (DWORD*)j_malloc(0x10);
                        if (ASelectableCar)
                        {
                            ASelectableCar[2] = record->Handle;
                            *((BYTE*)ASelectableCar + 12) = !IsCarUnlocked;
                        }
                        else
                        {
                            ASelectableCar = 0;
                        }
                        ListPrev = (DWORD*)ListItem[1];
                        *ListPrev = (DWORD)ASelectableCar;
                        ListItem[1] = (DWORD)ASelectableCar;
                        ASelectableCar[1] = (DWORD)ListPrev;
                        *ASelectableCar = (DWORD)ListItem;
                    }
                }
            }
            ++CarIndex;
        } while (CarIndex < NumFECarRecords);
        switch ((WORD)filter)// filter
        {
        //
        case FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_CAREER:
        case FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_PRESET:
            Sort:
            bTList_AllocationHeader_Sort(ListItem, SortCarsByUnlock);
            break;
        case FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_STOCK:
            if (!StockCarsHook) goto Sort;
			break;
        case FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_BONUS:
            if (!UseBonusCarsHooks) goto Sort;
            break;
        default:
            break;
        }
        UIQRCarSelect_SetupForPlayer(UIQRCarSelect, iPlayerNum);
	}
}

struct Performance
{
    float TopSpeed;
    float Handling;
    float Acceleration;

    void Default()
    {
        TopSpeed = 0.0f;
        Handling = 0.0f;
        Acceleration = 0.0f;
    }
};

void __fastcall UIQRCarSelect_UpdateSliders(DWORD* UIQRCarSelect, void* EDX_Unused)
{
    // todo: later
}

void __fastcall UIQRCarSelect_SetListNameAndTexture(DWORD* UIQRCarSelect, void* EDX_Unused)
{
    DWORD NameHash, TextureHash;

    switch ((WORD)UIQRCarSelect[107])
    {
    case FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_STOCK: // Stock
        NameHash = CT_bStringHash("CARLIST_STOCK");
        TextureHash = CT_bStringHash("CARBUCKET_STOCKCARS");
        break;
    case FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_CAREER: // Career
        NameHash = CT_bStringHash("CARLIST_CAREER");
        TextureHash = CT_bStringHash("CARBUCKET_CAREER");
        break;
    case FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_QUICK_RACE: // My Cars
        NameHash = CT_bStringHash("CARLIST_QUICKRACE");
        TextureHash = CT_bStringHash("CARBUCKET_CUSTOMIZECARS");
        break;
    case FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_BONUS: // Bonus
        NameHash = CT_bStringHash("CARLIST_BONUS");
        TextureHash = CT_bStringHash("CARBUCKET_BONUSCARS");
        break;
    case FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_PRESET: // Preset
        NameHash = CT_bStringHash("CARLIST_PRESET");
        TextureHash = CT_bStringHash("MAIN_ICON_CAREER");
        break;
    case FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_DEBUG: // Debug
        NameHash = CT_bStringHash("DEBUG_OPT");
        TextureHash = CT_bStringHash("MAIN_ICON_CAREER");
        break;
    default:
        NameHash = 0;
        TextureHash = 0;
        break;
    }

    char const* PackageFilename = (char const*)UIQRCarSelect[4];

    FEngSetLanguageHash(PackageFilename, 0xAA9834BC, NameHash);
    DWORD* Image = FEngFindImage(PackageFilename, 0xE3B271B8);
    FEngSetTextureHash_obj(Image, TextureHash);
}

void __fastcall UIQRCarSelect_RefreshHeader(DWORD* UIQRCarSelect, void* EDX_Unused)
{
    UIQRCarSelect_UpdateSliders(UIQRCarSelect, EDX_Unused);
    UIQRCarSelect_SetListNameAndTexture(UIQRCarSelect, EDX_Unused);

    DWORD* FEDatabase = *(DWORD**)_FEDatabase;
    int FEGameMode = FEDatabase[0x12C / 4]; //FEDatabase->FEGameMode;
    char buf[128];
    DWORD Attrib[5];

    char const* PackageFilename = (char const*)UIQRCarSelect[4];

    if ((FEGameMode & 0x8000) != 0 || (FEGameMode & 1) == 0) // eFE_GAME_MODE_CAR_LOT or not eFE_GAME_MODE_CAREER (disabled for fun)
    {
        FEngSetInvisible(FEngFindObject(PackageFilename, CT_bStringHash("MARKER_APPEAR")));
        FEngSetInvisible(FEngFindObject(PackageFilename, 0xE998FE99));
    }

    FEngSetScript(PackageFilename, 0xD0F7C7CC, CT_bStringHash("HIDE"), 1);

    DWORD* pSelectedCar = (DWORD*)UIQRCarSelect[13];
    int filter = (WORD)UIQRCarSelect[107]; // Filter
    FEPlayerCarDB* stable = 0;

    int iPlayerNum = UIQRCarSelect[106];
    DWORD* UserProfile = (DWORD*)FEDatabase[4 + iPlayerNum];

    if (!pSelectedCar || *(BYTE*)(pSelectedCar + 12)) // pSelectedCar->bLocked
    {
        FEngSetInvisible(FEngFindObject(PackageFilename, CT_bStringHash("ACCEPT_GROUP")));
    }

    if (pSelectedCar)
    {
        if ((FEGameMode & 8) == 0 && (FEGameMode & 0x40) == 0)
        {
            FEngSetVisible(FEngFindObject(PackageFilename, CT_bStringHash("SHOWCASE_REP")));
            FEngSetVisible(FEngFindObject(PackageFilename, 0x18A4384F));
        }

        FEngSetVisible(FEngFindObject(PackageFilename, CT_bStringHash("ACCEPT_GROUP")));
        cFEng_QueuePackageMessage(*(int**)cFEng_mInstance, 0x7C4583DC, PackageFilename, 0);

        int SelCarPos = bList_TraversebList(UIQRCarSelect + 11, pSelectedCar);
        FEPrintf(PackageFilename, CT_bStringHash("NUMBER"), "%d", SelCarPos);
        int NumCars = bList_TraversebList(UIQRCarSelect + 11, 0);
        FEPrintf(PackageFilename, CT_bStringHash("NUMBER_OF"), "%d", NumCars);


        if (iPlayerNum > 1) stable = 0;
        else
        {
            stable = (FEPlayerCarDB*)(UserProfile + 261); //&FEDatabase->CurrentUserProfiles[iPlayerNum]->PlayersCarStable;
        }

        // Use the stable we created at boot for stock cars instead
        if (StockCarsHook && ((filter & FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_STOCK) != 0)) stable = UnlimiterCarStable;

        FECarRecord* CarRecordByHandle = stable->GetCarRecordByHandle(((BYTE*)pSelectedCar)[8]);

        if (CarRecordByHandle && ((BYTE*)pSelectedCar)[12]) // pSelectedCar->bLocked
        {
            FEngSetScript(PackageFilename, 0xD0F7C7CC, CT_bStringHash("SHOW"), 1);
            if (CarRecordByHandle->MatchesFilter(0xF0008))
            {
                DWORD BonusUnlockText = UIQRCarSelect_GetBonusUnlockText(UIQRCarSelect, EDX_Unused, (DWORD*)CarRecordByHandle);
                if (BonusUnlockText == CT_bStringHash("CARLOT_UNLOCK_MSG_01"))
                {
                    int BonusUnlockBinNumber = UIQRCarSelect_GetBonusUnlockBinNumber(UIQRCarSelect, EDX_Unused, (DWORD*)CarRecordByHandle);
                    FEngSNPrintf(buf, 128, "blacklist_rival_%02d_aka", BonusUnlockBinNumber);
                    char* rivalname = GetLocalizedString(FEHashUpper(buf));
                    char* unlockmsg = GetLocalizedString(CT_bStringHash("CARLOT_UNLOCK_MSG_01"));
                    FEPrintf(PackageFilename, 0x2D25B2C4, unlockmsg, rivalname, BonusUnlockBinNumber);
                }
                else
                {
                    FEngSetLanguageHash(PackageFilename, 0x2D25B2C4, BonusUnlockText);
                }
            }
            else
            {
                Attrib_Gen_frontend_frontend(Attrib, CarRecordByHandle->FEKey, 0, 0);
                int UnlockedAt = *(unsigned __int8*)(Attrib[2] + 89) + 1; // UnlockedAt??
                //v76 = 0;
                FEngSNPrintf(buf, 128, "blacklist_rival_%02d_aka", UnlockedAt);
                char* rivalname = GetLocalizedString(FEHashUpper(buf));
                char* unlockmsg = GetLocalizedString(CT_bStringHash("CARLOT_UNLOCK_MSG_01"));
                FEPrintf(PackageFilename, 0x2D25B2C4, unlockmsg, rivalname, UnlockedAt);
                //v76 = -1;
                Attrib_Instance_dtInstance(Attrib);
            }
        }

        FEngSetInvisible(FEngFindObject(PackageFilename, 0xD6D32016));
        FEngSetInvisible(FEngFindObject(PackageFilename, 0x79D6E45C));

        if (CarRecordByHandle)
        {
        
            FEngSetTextureHash_obj((DWORD*)UIQRCarSelect[15], CarRecordByHandle->GetManuLogoHash());
            FEngSetTextureHash_obj((DWORD*)UIQRCarSelect[16], CarRecordByHandle->GetLogoHash());

    #ifdef _DEBUG
            DWORD* CarNameObj = FEngFindObject(PackageFilename, CT_bStringHash("CAR_NAME"));
            FEngSetVisible(CarNameObj);
            FEngSetColor_obj(CarNameObj, 0xFFFFFFFF);
            FEPrintf(PackageFilename, CT_bStringHash("CAR_NAME"), GetLocalizedString(CarRecordByHandle->GetNameHash()));
#endif
        }

        if (CarRecordByHandle && ((FEGameMode & 0x8000) != 0)) // eFEGameModes::eFE_GAME_MODE_CAR_LOT
        {
            DWORD* CareerSettings = (DWORD*)UserProfile[0xA8 / 4]; // UserProfile->TheCareerSettings

            FEPrintf(PackageFilename, 0x1930B057, "%$d", CareerSettings[3]); // CurrentCash

            FEPrintf(PackageFilename, 0x20C83C31, "%$d", CarRecordByHandle->GetCost());
            FEngSetLanguageHash(PackageFilename, 0xDC18C4D4, 0xA9950B93);
            FEngSetLanguageHash(PackageFilename, 0xB94139F4, 0x7010BBF2);
        }
        if ((FEGameMode & 1) == 0 || (FEGameMode & 0x8000) != 0) // eFEGameModes::eFE_GAME_MODE_CAREER || eFEGameModes::eFE_GAME_MODE_CAR_LOT
            FEngSetInvisible((DWORD*)UIQRCarSelect[53]); // HeatMeter
        else
            FEngSetVisible((DWORD*)UIQRCarSelect[53]); // HeatMeter
        if (CarRecordByHandle && CarRecordByHandle->CareerHandle == 0xFF)
        {
            FEngSetInvisible((DWORD*)UIQRCarSelect[53]); // HeatMeter;
        }
        else if (CarRecordByHandle)
        {
            FEngSetInvisible(FEngFindObject(PackageFilename, CT_bStringHash("MARKER_APPEAR")));
            FEngSetInvisible(FEngFindObject(PackageFilename, 0xE998FE99));

            FECareerRecord* CareerRecordByHandle = stable->GetCareerRecordByHandle(CarRecordByHandle->CareerHandle);
            if (FEMarkerManager_GetNumMarkers((DWORD*)TheFEMarkerManager, 20, 0) > 0 // FEMarkerManager::ePossibleMarker::MARKER_ADD_IMPOUND_BOX
                || *(bool*)CheatCanAddImpoundBox && !CareerRecordByHandle->TheImpoundData.ImpoundedState)
            {
                int NumMarkers = FEMarkerManager_GetNumMarkers((DWORD*)TheFEMarkerManager, 20, 0); // FEMarkerManager::ePossibleMarker::MARKER_ADD_IMPOUND_BOX
                FEngSetVisible(FEngFindObject(PackageFilename, CT_bStringHash("MARKER_APPEAR")));
                FEPrintf(PackageFilename, 0x5B875870, "%2d", NumMarkers);
                FEPrintf(PackageFilename, CT_bStringHash("MARKER_BLOOM"), "%2d", NumMarkers);
            }
            else
            {
                FEngSetInvisible(FEngFindObject(PackageFilename, CT_bStringHash("MARKER_APPEAR")));
            }

            char ImpoundedState = CareerRecordByHandle->TheImpoundData.ImpoundedState;
            if (ImpoundedState == 4) // FEImpoundData::eImpoundReasons::IMPOUND_RELEASED
            {
                FEngSetLanguageHash(PackageFilename, CT_bStringHash("BOUNTY_HEADER"), CT_bStringHash("CS_RELEASE_HEADER"));
                FEngSetLanguageHash(PackageFilename, CT_bStringHash("UNSERVED_HEADER"), CT_bStringHash("PLAYER_FUND_HEADER"));

                DWORD* CareerSettings = (DWORD*)UserProfile[0xA8 / 4]; // UserProfile->TheCareerSettings

                FEPrintf(PackageFilename, CT_bStringHash("BOUNTY_DATA"), "%$0.0f", CarRecordByHandle->GetReleaseFromImpoundCost());
                FEPrintf(PackageFilename, CT_bStringHash("UNSERVED_DATA"), "%$d", CareerSettings[3]); // CurrentCash
                FEngSetInvisible(FEngFindObject(PackageFilename, CT_bStringHash("SHOWCASE_REP")));
            }
            else
            {
                if (ImpoundedState)
                {
                    FEngSetLanguageHash(PackageFilename, CT_bStringHash("BOUNTY_HEADER"), CT_bStringHash("CS_RELEASE_HEADER"));
                    FEngSetLanguageHash(PackageFilename, CT_bStringHash("UNSERVED_HEADER"), CT_bStringHash("PLAYER_FUND_HEADER"));
                    FEngSetLanguageHash(PackageFilename, CT_bStringHash("BOUNTY_DATA"), CT_bStringHash("CS_PENDING"));

                    DWORD* CareerSettings = (DWORD*)UserProfile[0xA8 / 4]; // UserProfile->TheCareerSettings
                    FEPrintf(PackageFilename, CT_bStringHash("UNSERVED_DATA"), "%$d", CareerSettings[3]); // CurrentCash
                    FEngSetInvisible(FEngFindObject(PackageFilename, CT_bStringHash("SHOWCASE_REP")));

                    if (FEMarkerManager_GetNumMarkers((DWORD*)TheFEMarkerManager, 21, 0) > 0 || *(bool*)CheatReleaseFromImpoundMarker)
                    {
                        int NumMarkers = FEMarkerManager_GetNumMarkers((DWORD*)TheFEMarkerManager, 21, 0);
                        FEngSetVisible(FEngFindObject(PackageFilename, 0xE998FE99));
                        FEPrintf(PackageFilename, 0xCC59B910, "%2d", NumMarkers);
                        FEPrintf(PackageFilename, CT_bStringHash("MARKER_BLOOM2"), "%2d", NumMarkers);
                        FEngSetInvisible(FEngFindObject(PackageFilename, CT_bStringHash("MARKER_APPEAR")));
                    }
                }
                else
                {
                    FEngSetLanguageHash(PackageFilename, CT_bStringHash("BOUNTY_HEADER"), 0x17574B0E);
                    FEngSetLanguageHash(PackageFilename, CT_bStringHash("UNSERVED_HEADER"), 0x915F4D26);

                    if ((FEGameMode & 8) == 0 && (FEGameMode & 0x40) == 0) // !eFEGameModes::eFE_GAME_MODE_ONLINE && eFEGameModes::eFE_GAME_MODE_LAN
                        FEngSetVisible(FEngFindObject(PackageFilename, CT_bStringHash("SHOWCASE_REP")));

                    CareerRecordByHandle = stable->GetCareerRecordByHandle(CarRecordByHandle->CareerHandle);
                    if (CareerRecordByHandle)
                    {
                        FEPrintf(PackageFilename, CT_bStringHash("BOUNTY_DATA"), "%$d", CareerRecordByHandle->Bounty);
                        int FineValue = CareerRecordByHandle->UnservedInfractions.GetFineValue();
                        FEPrintf(PackageFilename, CT_bStringHash("UNSERVED_DATA"), "%$d", FineValue);
                    }
                }
            }

            CustomizeMeter_SetCurrent((DWORD*)UIQRCarSelect[53], CareerRecordByHandle->GetVehicleHeat());
            CustomizeMeter_SetPreview((DWORD*)UIQRCarSelect[53], CareerRecordByHandle->GetVehicleHeat());
            CustomizeMeter_Draw((DWORD*)UIQRCarSelect[53]);
        }
    }
    else
    {
        FEngSetLanguageHash(PackageFilename, 0x2D25B2C4, CT_bStringHash("CS_NO_CARS_IN_LIST"));
        cFEng_QueuePackageMessage(*(int**)cFEng_mInstance, 0xD9420CD5, PackageFilename, 0);
        if ((filter & FEPlayerCarDBFilterBits::FE_CAR_FILTER_LIST_QUICK_RACE) != 0)
            FEngSetLanguageHash(PackageFilename, 0x36C1E04D, CT_bStringHash("CS_NO_CARS_IN_LIST_ADD_IN_MY_CAR_SCREEN"));
        else
            FEngSetLanguageHash(PackageFilename, 0x36C1E04D, CT_bStringHash("CS_NO_CARS_IN_LIST"));

        FEngSetInvisible(FEngFindObject(PackageFilename, CT_bStringHash("SHOWCASE_REP")));
        FEngSetInvisible(FEngFindObject(PackageFilename, 0x18A4384F));

        CarViewer_CancelCarLoad();

        GarageMainScreen_DisableCarRendering(GarageMainScreen_GetInstance());

        cFEng_QueuePackageMessage(*(int**)cFEng_mInstance, 0x913FA282, PackageFilename, 0);
        *((BYTE*)UIQRCarSelect + 420) = 0; // bLoadingBarActive
        *((DWORD*)UIQRCarSelect + 14) = 0; // tLastEventTimer.PackedTime
    }

}

void __fastcall UIQRCarSelect_ScrollLists(DWORD* UIQRCarSelect, void *EDX_Unused, int direction)
{
    DWORD* FEDatabase = *(DWORD**)_FEDatabase;
    int FEGameMode = FEDatabase[0x12C / 4]; //FEDatabase->FEGameMode;

	DWORD region = UIQRCarSelect[107] & 0xFFFF0000; // reg
	DWORD list = (WORD)UIQRCarSelect[107]; // Filter

    switch (direction)
    {
    case -1:
        if (list == 1) list = 64;
		else list /= 2;
        break;
    case 1:
        if (list == 64) list = 1;
        else list *=2;
        break;
    }

    UIQRCarSelect[107] = region | list;
    UIQRCarSelect_RefreshCarList(UIQRCarSelect, EDX_Unused);
    UIQRCarSelect_RefreshHeader(UIQRCarSelect, EDX_Unused);
}

void __fastcall UIQRCarSelect_ScrollRegions(DWORD* UIQRCarSelect, void* EDX_Unused, int direction)
{
    DWORD* FEDatabase = *(DWORD**)_FEDatabase;
    int FEGameMode = FEDatabase[0x12C / 4]; //FEDatabase->FEGameMode;

    DWORD region = UIQRCarSelect[107] & 0xFFFF0000; // reg
    DWORD list = (WORD)UIQRCarSelect[107]; // Filter

    switch (direction)
    {
    case -1:
        if (region == 65536) region = 983040;
        else if (region == 983040) region = 524288;
        else region /= 2;
        break;
    case 1:
        if (region == 983040) region = 65536;
        else if (region == 524288) region = 983040;
        else region *= 2;
        break;
    }

    UIQRCarSelect[107] = region | list;
    UIQRCarSelect_RefreshCarList(UIQRCarSelect, EDX_Unused);
    UIQRCarSelect_RefreshHeader(UIQRCarSelect, EDX_Unused);
}

// Get stable with player number??
FEPlayerCarDB* __fastcall sub_4061B0_Hook(DWORD* FEDB, void* EDX_Unused, int iPlayerNum)  
{  
    if (StockCarsHook && iPlayerNum < 2)  
        return UnlimiterCarStable;  
    else  
        return reinterpret_cast<FEPlayerCarDB*(__thiscall*)(DWORD*, int)>(0x4061B0)(FEDB, iPlayerNum);  
}

// Get car record with player number??
FECarRecord* __fastcall sub_7A1990_Hook(DWORD* FEDB, void *EDX_unused, unsigned int iPlayerNum, unsigned int handle)
{
    if (iPlayerNum > 1)
        return (FECarRecord*)FEPlayerCarDB_GetCarRecordByHandle(0, handle);
    else
    {
		DWORD* UserProfile = (DWORD*)FEDB[iPlayerNum + 4];
		FEPlayerCarDB* stable = (FEPlayerCarDB*)(UserProfile + 261);
        FECarRecord* carrec = StockCarsHook ? UnlimiterCarStable->GetCarRecordByHandle(handle) : stable->GetCarRecordByHandle(handle);
        if (!carrec)
        {
            carrec = stable->GetCarRecordByHandle(handle);
        }

        return carrec;
    }
}