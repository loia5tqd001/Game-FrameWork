#pragma once
#include "Vector2.h"

struct Rect : public RECT
{
	template<typename T>
	Rect(T l, T t, T r, T b) : RECT{ (LONG)l, (LONG)t, (LONG)r, (LONG)b }
	{}
	Rect() : RECT{ 0, 0, 0, 0 }
	{}

	Rect operator*(const Vector2& scale) const
	{
		return Rect{ left * scale.x, top * scale.y, right * scale.x, bottom * scale.y };
	}

	UINT GetWidth() const
	{
		assert(right >= left);
		return right - left;
	}
	UINT GetHeight() const
	{
		assert(bottom >= top);
		return bottom - top;
	}

	bool IsNone() const
	{
		return left == right;
	}

};