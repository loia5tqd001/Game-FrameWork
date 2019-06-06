#pragma once
#include "Vector3.h"

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
		assert(right > left);
		return right - left;
	}
	UINT GetHeight() const
	{
		assert(bottom > top);
		return bottom - top;
	}

	bool IsNone() const
	{
		return right == 0; // left == 0, top == 0, bottom == 0 as well
	}

};