#pragma once

#include "stdafx.h"
#include "stdio.h"

#include "bMatrix.h"

typedef struct ePositionMarker
{
	/* 0x0000 */ DWORD NameHash;
	/* 0x0004 */ int iParam0;
	/* 0x0008 */ float fParam0;
	/* 0x000c */ float fParam1;
	/* 0x0010 */ bMatrix4 Matrix;

	inline operator void* () noexcept { return reinterpret_cast<void*>(this); }
} ePositionMarker;