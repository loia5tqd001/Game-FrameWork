#pragma once
#include "Vector3.h"
#include "Rect.h"


struct RectF
{
	float left, top, right, bottom;

	RectF() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) 
	{}
	RectF(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) 
	{
		assert(top <= bottom);
	}
	RectF(float x, float y, UINT width, UINT height) : RectF(x, y, x + width, y + height)
	{}

	float GetWidth () const { return right - left; }
	float GetHeight() const { return bottom - top; }
	bool  IsNone   () const { return left == right;}

	Point GetCenter() const
	{
		const float x = (left + right) / 2;
		const float y = (top + bottom) / 2;
		return Point{ x, y, 0.0f };
	}

	bool IsIntersect(const RectF& other) const
	{
		return left < other.right && right > other.left
			&& top < other.bottom && bottom > other.top;
	}

	RectF GetBroadPhase(float dx, float dy) const
	{
		return {
			min(left  , left   + dx),
			min(top   , top    + dy),
			max(right , right  + dx),
			max(bottom, bottom + dy)
		};
	}
};
