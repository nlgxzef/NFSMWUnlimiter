#pragma once

enum eCustomTuningType
{
    NUM_CUSTOM_TUNINGS = 3,
    CTT_SETTING_3 = 2,
    CTT_SETTING_2 = 1,
    CTT_SETTING_1 = 0,
};

enum Physics_Upgrades_Type
{
    PUT_MAX = 7,
    PUT_NOS = 6,
    PUT_INDUCTION = 5,
    PUT_ENGINE = 4,
    PUT_TRANSMISSION = 3,
    PUT_CHASSIS = 2,
    PUT_BRAKES = 1,
    PUT_TIRES = 0,
};

struct Physics_Upgrades_Package
{
	int Part[Physics_Upgrades_Type::PUT_MAX];
	int Junkman;
};

struct Physics_Upgrades_Tunings
{
	float Value[Physics_Upgrades_Type::PUT_MAX];
};
