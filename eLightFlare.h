#pragma once

#include "stdafx.h"
#include "stdio.h"

#include "Color.h"

struct eLightFlare : bTNode<eLightFlare>
{
	/* 0x0008 */ DWORD NameHash;
	/* 0x000c */ Color ColourTint;
	/* 0x0010 */ float PositionX;
	/* 0x0014 */ float PositionY;
	/* 0x0018 */ float PositionZ;
	/* 0x001c */ float ReflectPosZ;
	/* 0x0020 */ float DirectionX;
	/* 0x0024 */ float DirectionY;
	/* 0x0028 */ float DirectionZ;
	/* 0x002c */ char Type;
	/* 0x002d */ char Flags;
	/* 0x002e */ short ScenerySectionNumber;

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
}; /* size: 0x0030 */
