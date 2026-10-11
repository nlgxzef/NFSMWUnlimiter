#pragma once

#include "stdio.h"
#include "InGameFunctions.h"

struct PresetCar
{
	PresetCar* next; // offset 0x0, size 0x4
	PresetCar* prev; // offset 0x4, size 0x4
    char CarTypeName[32]; // offset 0x8, size 0x20
    char PresetName[32]; // offset 0x28, size 0x20
    unsigned long long FEKey; // offset 0x48, size 0x8
    unsigned long long VehicleKey; // offset 0x50, size 0x8
    unsigned int FilterBits; // offset 0x58, size 0x4
    int PhysicsLevel; // offset 0x5C, size 0x4
    DWORD PartNameHashes[NumCarSlots]; // offset 0x60, size 0x22C
};

int (*GetNumPresetCars)() = (int (*)())0x739E10;
PresetCar* (*GetPresetCarAt)(int index) = (PresetCar * (*)(int))0x748120;