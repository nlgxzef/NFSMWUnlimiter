#pragma once

#include "stdafx.h"
#include "stdio.h"

#include "bVector.h"

#pragma pack(push, 1)

struct Attrib_Private
{
	WORD Capacity;
	WORD Length;
	WORD ElementSize;
	WORD Type;

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
};

struct Attrib_RefSpec
{
	/* 0x0000 */ unsigned int mClassKey;
	/* 0x0004 */ unsigned int mCollectionKey;
	/* 0x0008 */ DWORD* mCollectionPtr;

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
};

struct Attrib_HashMap {
	DWORD* /* Attrib_Node* */ mTable; // offset 0x0, size 0x4
	unsigned int mTableSize; // offset 0x4, size 0x4
	unsigned int mNumEntries; // offset 0x8, size 0x4
	unsigned short mWorstCollision; // offset 0xC, size 0x2
	unsigned short mKeyShift; // offset 0xE, size 0x2

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
};

struct Attrib_Class {
	// total size: 0xC
	unsigned int mKey; // offset 0x0, size 0x4
	unsigned int mRefCount; // offset 0x4, size 0x4
	DWORD* /*Attrib_ClassPrivate&*/ mPrivates; // offset 0x8, size 0x4

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
};

struct Attrib_Collection {
	/* 0x0000 */ Attrib_HashMap mTable; // offset 0x0, size 0x10
	/* 0x0010 */ Attrib_Collection* mParent; // offset 0x10, size 0x4
	/* 0x0014 */ Attrib_Class* mClass; // offset 0x14, size 0x4
	/* 0x0018 */ void* mLayout; // offset 0x18, size 0x4
	/* 0x001C */ unsigned int mRefCount; // offset 0x1C, size 0x4
	/* 0x0020 */ unsigned int mKey; // offset 0x20, size 0x4
	/* 0x0024 */ DWORD* /*Vault**/ mSource; // offset 0x24, size 0x4
	/* 0x0028 */ const char* mNamePtr; // offset 0x28, size 0x4

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
};

struct Attrib_Instance
{
	/* 0x0000 */ DWORD* /*IUnknown**/ mOwner;
	/* 0x0004 */ Attrib_Collection* mCollection;
	/* 0x0008 */ void* mLayoutPtr;
	/* 0x000C */ unsigned int mMsgPort;
	/* 0x0010 */ unsigned short mFlags;
	/* 0x0012 */ unsigned short mLocks;

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
};

struct CarBodyMotion
{
	/* 0x0000 */ float DegPerG;
	/* 0x0004 */ float MaxGs;
	/* 0x0008 */ float DegPerSec;

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
};

struct Attrib_Gen_ecar_LayoutStruct
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
}; /* size: 0x0120 */

struct Attrib_Gen_engine_LayoutStruct
{
	Attrib_Private _Array_TORQUE;
	float TORQUE[9];
	Attrib_Private _Array_SPEED_LIMITER;
	float SPEED_LIMITER[2];
	Attrib_Private _Array_ENGINE_BRAKING;
	float ENGINE_BRAKING[3];
	float FLYWHEEL_MASS;
	float MAX_RPM;
	float RED_LINE;
	float IDLE;
}; /* size: 0x60 */


#pragma pack(pop)

#define _Attrib_Database_sThis 0x90DCBC

Attrib_Instance*(__thiscall* Attrib_Instance_ctInstance)(Attrib_Instance* Attrib, Attrib_Collection* collection, DWORD msgPort, DWORD* owner) = (Attrib_Instance *(__thiscall*)(Attrib_Instance*, Attrib_Collection*, DWORD, DWORD*))0x452380;
Attrib_Instance*(__thiscall* Attrib_Instance_ctInstance_RS)(Attrib_Instance* Attrib, Attrib_RefSpec* refSpec, DWORD msgPort, DWORD* owner) = (Attrib_Instance *(__thiscall*)(Attrib_Instance*, Attrib_RefSpec*, DWORD, DWORD*))0x456CB0;
int(__thiscall* Attrib_Instance_dtInstance)(DWORD* Attrib) = (int(__thiscall*)(DWORD*))0x45A430;
DWORD (__thiscall* Attrib_Instance_GetCollection)(DWORD* Attrib) = (DWORD(__thiscall*)(DWORD*))0x452430;

Attrib_Class* (__thiscall* Attrib_Database_GetClass)(DWORD* Attrib_Database, DWORD ClassKey) = (Attrib_Class * (__thiscall*)(DWORD*, DWORD))0x455BC0;
DWORD (__thiscall* Attrib_Class_GetFirstCollection)(Attrib_Class* Attrib_Class) = (DWORD  (__thiscall*)(Attrib_Class*))0x456B00;
DWORD (__thiscall* Attrib_Class_GetNextCollection)(Attrib_Class* Attrib_Class, DWORD prev) = (DWORD  (__thiscall*)(Attrib_Class*, DWORD))0x456B20;
Attrib_Collection* (* Attrib_FindCollection)(DWORD ClassKey, DWORD CollectionKey) = (Attrib_Collection * (*)(DWORD, DWORD))0x455FD0;

void* (*Attrib_DefaultDataArea)(unsigned int bytes) = (void* (*)(unsigned int))0x6269B0;

DWORD(*Attrib_StringToKey)(char const* str) = (DWORD(*)(char const*))0x454640;
DWORD(*Attrib_StringToLowerCaseKey)(char const* str) = (DWORD(*)(char const*))0x4549B0;