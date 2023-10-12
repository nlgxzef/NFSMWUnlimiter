#pragma once

#include "stdafx.h"
#include "stdio.h"

#include "bVector.h"

#pragma pack(push, 1)

typedef struct Attrib_Private
{
	WORD Capacity;
	WORD Length;
	WORD ElementSize;
	WORD Type;

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
} Attrib_Private;

typedef struct Attrib_RefSpec
{
	/* 0x0000 */ unsigned int mClassKey;
	/* 0x0004 */ unsigned int mCollectionKey;
	/* 0x0008 */ DWORD* mCollectionPtr;

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
} Attrib_RefSpec;

typedef struct CarBodyMotion
{
	/* 0x0000 */ float DegPerG;
	/* 0x0004 */ float MaxGs;
	/* 0x0008 */ float DegPerSec;

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
} CarBodyMotion;

typedef struct Attrib_Gen_ecar_LayoutStruct
{
	/* 0x0000 */ Attrib_Private _Array_TireOffsets;
	/* 0x0008 */ BYTE _Pad_TireOffsets[8];
	/* 0x0010 */ bVector4 TireOffsets[4];
	/* 0x0050 */ Attrib_Private _Array_TireSkidWidthKitScale;
	/* 0x0058 */ bVector2 TireSkidWidthKitScale[7];
	/* 0x0090 */ Attrib_Private _Array_SkidFX;
	/* 0x0098 */ float SkidFX[2];
	/* 0x00A0 */ CarBodyMotion BodyRoll;
	/* 0x00AC */ CarBodyMotion BodySquat;
	/* 0x00B8 */ CarBodyMotion BodyDive;
	/* 0x00C4 */ Attrib_Private _Array_SlipFX;
	/* 0x00CC */ float SlipFX[2];
	/* 0x00D4 */ Attrib_Private _Array_TireSkidWidth;
	/* 0x00DC */ float TireSkidWidth[4];
	/* 0x00EC */ char const* CollectionName;
	/* 0x00F0 */ float CamberFront;
	/* 0x00F4 */ float ReflectionOffset;
	/* 0x00F8 */ float CamberRear;
	/* 0x00FC */ float RideHeight;
	/* 0x0100 */ Attrib_Private _Array_KitWheelOffsetRear;
	/* 0x0108 */ BYTE KitWheelOffsetRear[6];
	/* 0x010E */ Attrib_Private _Array_KitWheelOffsetFront;
	/* 0x0116 */ BYTE KitWheelOffsetFront[6];
	/* 0x011C */ char WheelSpokeCount;
	/* 0x011D */ BYTE Padding[3];

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
} Attrib_Gen_ecar_LayoutStruct; /* size: 0x0120 */

#pragma pack(pop)

