#include "stdio.h"
#include "InGameFunctions.h"

void __fastcall CustomizeSpoiler_BuildPartOptionListFromFilter(DWORD* _CustomizeSpoiler, void* EDX_Unused, DWORD* TheActiveCarPart)
{
    DWORD* TheIconScroller; // ebx MAPDST
    DWORD* v4; // eax
    int v5; // ecx
    DWORD* v6; // esi
    DWORD* v7; // eax
    int v8; // eax
    DWORD* TheSelectablePart; // esi
    char IsInBackroom; // al
    DWORD PartIcon; // ebp
    char PartName; // bl
    bool IsLocked; // al
    DWORD v16; // edx
    DWORD InitialOption; // eax MAPDST
    DWORD i; // [esp+Ch] [ebp-20h]
    unsigned int UnlockHash; // [esp+14h] [ebp-18h]
    DWORD PartList[2]; // [esp+18h] [ebp-14h] BYREF
    int v23; // [esp+28h] [ebp-4h]

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    TheIconScroller = _CustomizeSpoiler + 11;
    (*(void(__thiscall**)(DWORD*))(_CustomizeSpoiler[11] + 12))(_CustomizeSpoiler + 11);
    (*(void(__thiscall**)(DWORD*))(*TheIconScroller + 60))(TheIconScroller);
    PartList[0] = (DWORD)PartList;
    PartList[1] = (DWORD)PartList;
    v23 = 0;
    CarCustomizeManager_GetCarPartList((DWORD*)_gCarCustomizeManager, CAR_SLOT_ID::SPOILER, PartList, 0);
    v4 = (DWORD*)PartList[0];
    for (i = 1; (DWORD*)PartList[0] != PartList; v4 = (DWORD*)PartList[0])
    {
        v5 = *v4;
        v6 = v4;
        v7 = (DWORD*)v4[1];
        *v7 = v5;
        *(DWORD**)(v5 + 4) = v7;
        v8 = v6[2];
        TheSelectablePart = v6 - 1;
        if ((*(BYTE*)(v8 + 5) & 0x1F) == _CustomizeSpoiler[111] || (*(BYTE*)(v8 + 5) & 0x1F) == 4)
        {
            UnlockHash = CarCustomizeManager_GetUnlockHash_CarPart((DWORD*)_gCarCustomizeManager, (DWORD*)TheSelectablePart[3], _CustomizeSpoiler[82], TheSelectablePart[5]);
            IsInBackroom = CustomizeIsInBackRoom();
            PartIcon = IsInBackroom != 0 ? CarConfigs[CarTypeID].Icons.BackroomPartsSpoilers : CarConfigs[CarTypeID].Icons.PartsSpoilers;
            if (CarPart_GetAppliedAttributeIParam((DWORD*)TheSelectablePart[3], bStringHash((char*)"CARBONFIBRE"), 0))
                PartIcon = IsInBackroom != 0 ? CarConfigs[CarTypeID].Icons.BackroomPartsSpoilersCF : CarConfigs[CarTypeID].Icons.PartsSpoilersCF;
            PartName = *(BYTE*)(TheSelectablePart[3] + 5) >> 5;
            IsLocked = CarCustomizeManager_IsPartLocked((DWORD*)_gCarCustomizeManager, EDX_Unused, TheSelectablePart, 0);
            PartIcon = CarPart_GetAppliedAttributeIParam((DWORD*)TheSelectablePart[3], bStringHash((char*)"TEXTUREHASH"), PartIcon);
            CustomizationScreen_AddPartOption(_CustomizeSpoiler, TheSelectablePart, PartIcon, PartName, 0, UnlockHash, IsLocked);
            v16 = _CustomizeSpoiler[111];
            if (_CustomizeSpoiler[v16 + 112] == 1)
            {
                if (TheActiveCarPart && *((DWORD**)TheSelectablePart + 3) == TheActiveCarPart)
                    _CustomizeSpoiler[v16 + 112] = i;
                ++i;
            }
        }
        else
        {
            (**(void(__thiscall***)(DWORD*, int))TheSelectablePart)(TheSelectablePart, 1);
        }
    }
    if (*(int*)_Showcase_FromIndex)
    {
        _CustomizeSpoiler[_CustomizeSpoiler[111] + 112] = *(int*)_Showcase_FromIndex;
        InitialOption = *(int*)_Showcase_FromIndex;
        if (*((BYTE*)_CustomizeSpoiler + 297))
        {
            *((BYTE*)TheIconScroller + 240) = 0;
            *((BYTE*)TheIconScroller + 237) = 1;
            *((BYTE*)TheIconScroller + 238) = 0;
            TheIconScroller[57] = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD))(*TheIconScroller + 64))(TheIconScroller, InitialOption);
        *(int*)_Showcase_FromIndex = 0;
    }
    else
    {
        InitialOption = _CustomizeSpoiler[_CustomizeSpoiler[111] + 112];
        if (*((BYTE*)_CustomizeSpoiler + 297))
        {
            *((BYTE*)TheIconScroller + 240) = 0;
            *((BYTE*)TheIconScroller + 237) = 1;
            *((BYTE*)TheIconScroller + 238) = 0;
            TheIconScroller[57] = 0;
        }
        (*(void(__thiscall**)(DWORD*, DWORD))(*TheIconScroller + 64))(TheIconScroller, InitialOption);
    }
    v23 = -1;
    bTList_SelectablePart_dtor((int**)PartList);
}

void __fastcall CustomizeSpoiler_Setup(DWORD* _CustomizeSpoiler, void* EDX_Unused)
{
    const char* FEPackage; // eax
    DWORD* ArrowL; // eax
    DWORD* ArrowR; // eax
    DWORD* TheActivePart; // eax

    // Get CarType Info
    void* FECarRecord = *(void**)_FECarRecord;
    int CarTypeID = FECarRecord_GetType(FECarRecord);

    FEPackage = (const char*)_CustomizeSpoiler[4];
    _CustomizeSpoiler[87] = CarConfigs[CarTypeID].Names.PartsSpoilers;
    ArrowL = FEngFindImage(FEPackage, 0x91C4A50u);
    FEngSetButtonTexture(ArrowL, 0x5BC); // L1
    ArrowR = FEngFindImage(FEPackage, 0x2D145BE3u);
    FEngSetButtonTexture(ArrowR, 0x682); // R1
    TheActivePart = (DWORD*)CarCustomizeManager_GetActivePartFromSlot((DWORD*)_gCarCustomizeManager, CAR_SLOT_ID::SPOILER); // SPOILER
    if (*(int*)_Showcase_FromFilter == -1)
    {
        if (TheActivePart && (*((BYTE*)TheActivePart + 5) & 0x1F) != 4)
            _CustomizeSpoiler[111] = *((BYTE*)TheActivePart + 5) & 0x1F;
    }
    else
    {
        _CustomizeSpoiler[111] = *(int*)_Showcase_FromFilter;
        *(int*)_Showcase_FromFilter = -1;
    }
    CustomizeSpoiler_BuildPartOptionListFromFilter(_CustomizeSpoiler, EDX_Unused, TheActivePart);
    (*(void(__thiscall**)(DWORD*))(*_CustomizeSpoiler + 12))(_CustomizeSpoiler);
}