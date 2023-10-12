#pragma once

#include "stdafx.h"
#include "stdio.h"

#include "bVector.h"

typedef struct bMatrix4
{
	bVector4 v0;
	bVector4 v1;
	bVector4 v2;
	bVector4 v3;

	inline bMatrix4& operator=(const bMatrix4& r) noexcept
	{
		v0 = r.v0;
		v1 = r.v1;
		v2 = r.v2;
		v3 = r.v3;

		return *this;
	}

	inline operator float* () noexcept { return reinterpret_cast<float*>(this); }
	inline bVector4& operator[](std::size_t index) noexcept { return (reinterpret_cast<bVector4*>(this))[index]; }

	bMatrix4(float* _mp)
	{
		v0 = _mp;
		v1 = _mp + 4;
		v2 = _mp + 8;
		v3 = _mp + 12;
	}
	bMatrix4(void* _vp) : bMatrix4((float*)_vp) {}
	bMatrix4(bVector4 _v0, bVector4 _v1, bVector4 _v2, bVector4 _v3)
	{
		v0 = _v0;
		v1 = _v1;
		v2 = _v2;
		v3 = _v3;
	}
	bMatrix4() : bMatrix4(bVector4(), bVector4(), bVector4(), bVector4()) {}
} bMatrix4;