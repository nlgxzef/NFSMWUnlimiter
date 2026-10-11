#pragma once

enum CarUsageType : int
{
	CAR_USAGE_TYPE_RACING = 0x0,
	CAR_USAGE_TYPE_COP = 0x1,
	CAR_USAGE_TYPE_TRAFFIC = 0x2,
	CAR_USAGE_TYPE_WHEELS = 0x3,
	CAR_USAGE_TYPE_UNIVERSAL = 0x4,
};

struct CarTypeInfo
{
	char CarTypeName[16];
	char BaseModelName[16];
	char GeometryFilename[32];
	char ManufacturerName[16];
	DWORD CarTypeNameHash;
	float HeadlightFOV;
	BYTE padHighPerformance;
	BYTE NumAvailableSkinNumbers;
	BYTE WhatGame;
	BYTE ConvertableFlag;
	BYTE WheelOuterRadius;
	BYTE WheelInnerRadiusMin;
	BYTE WheelInnerRadiusMax;
	BYTE pad0;
	bVector3 HeadlightPosition;
	bVector3 DriverRenderingOffset;
	bVector3 InCarSteeringWheelRenderingOffset;
	int Type;
	CarUsageType UsageType;
	DWORD CarMemTypeHash;
	BYTE MaxInstances[5];
	BYTE WantToKeepLoaded[5];
	BYTE pad4[2];
	float MinTimeBetweenUses[5];
	BYTE AvailableSkinNumbers[10];
	BYTE DefaultSkinNumber;
	BYTE Skinnable;
	int Padding;
	int DefaultBasePaint;

	bool IsCop()
	{
		return UsageType == CAR_USAGE_TYPE_COP;
	}

	bool IsTraffic()
	{
		return UsageType == CAR_USAGE_TYPE_TRAFFIC;
	}

	bool IsDamagableCop()
	{
		return IsCop() && CarMemTypeHash == CT_bStringHash("Cop") && CarTypeNameHash != CT_bStringHash("COPMIDSIZEINT");
	}

	bool IsHeli()
	{
		return IsCop() && CarMemTypeHash == CT_bStringHash("BigTraffic");
	}

	bool IsSkinnable()
	{
		return Skinnable != 0;
	}

	bool SetSkinnable(bool value)
	{
		Skinnable = value ? 1 : 0;
		return IsSkinnable();
	}
};

CarTypeInfo* CarTypeInfoArray;

CarTypeInfo* GetCarTypeInfo(int CarTypeID)
{
	return &CarTypeInfoArray[CarTypeID];
}