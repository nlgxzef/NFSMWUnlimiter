#pragma once

#include "stdafx.h"
#include "stdio.h"

typedef struct Color
{
	union
	{
		DWORD rgba;
		struct
		{
			BYTE r;
			BYTE g;
			BYTE b;
			BYTE a;
		};
	};

	//inline bool operator!() noexcept { return rgba == 0; }
	inline operator DWORD () noexcept { return rgba; }
	inline operator bool() { return rgba != 0; }
	inline Color& operator=(const Color& c) noexcept
	{
		rgba = c.rgba;
		return *this;
	}

	Color(BYTE _r, BYTE _g, BYTE _b, BYTE _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
	
	Color(DWORD _rgba)
	{
		rgba = _rgba;
	}
	Color() : Color(0) {}
} Color;