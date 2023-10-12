#pragma once

#include "stdafx.h"
#include "stdio.h"

// bVector2
typedef struct bVector2
{

	float x;
	float y;


	inline bVector2& operator=(const bVector2& r) noexcept
	{
		x = r.x;
		y = r.y;

		return *this;
	}

	inline operator float* () noexcept { return reinterpret_cast<float*>(this); }

	bVector2(float* _fp)
	{
		x = _fp[0];
		y = _fp[1];
	}
	bVector2(void* _vp) : bVector2((float*)_vp) {}
	bVector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	bVector2() : bVector2(0.0f, 0.0f) {}
} bVector2;

// bVector3
typedef struct bVector3
{
	float x;
	float y;
	float z;
	BYTE pad[4];

	inline bVector3& operator=(const bVector3& r) noexcept
	{
		x = r.x;
		y = r.y;
		z = r.z;

		return *this;
	}

	inline operator float* () noexcept { return reinterpret_cast<float*>(this); }

	bVector3(float* _fp)
	{
		x = _fp[0];
		y = _fp[1];
		z = _fp[2];
	}
	bVector3(void* _vp) : bVector3((float*)_vp) {}
	bVector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	bVector3() : bVector3(0.0f, 0.0f, 0.0f) {}
} bVector3;

// bVector4
typedef struct bVector4
{
	float x;
	float y;
	float z;
	float w;

	inline bVector4& operator=(const bVector4& r) noexcept
	{
		x = r.x;
		y = r.y;
		z = r.z;
		w = r.w;

		return *this;
	}

	inline operator float* () noexcept { return reinterpret_cast<float*>(this); }
	
	bVector4(float* _fp)
	{
		x = _fp[0];
		y = _fp[1];
		z = _fp[2];
		w = _fp[3];
	}
	bVector4(void* _vp) : bVector4((float*)_vp) {}
	bVector4(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	bVector4() : bVector4(0.0f, 0.0f, 0.0f, 0.0f) {}
} bVector4;

typedef bVector4 bQuaternion;