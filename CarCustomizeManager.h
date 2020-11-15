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

    int EngineType = CarINI.ReadInteger("Main", "EngineType", GeneralINI.ReadInteger("Main", "EngineType", -1));

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

    int EngineType = CarINI.ReadInteger("Main", "EngineType", GeneralINI.ReadInteger("Main", "EngineType", -1));

    if (EngineType == -1) return CarType == 5 || CarType == 56; // RX7, RX8
    else return EngineType == 2;
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