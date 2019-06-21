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

	operator Rect() const 
	{ 
		return { LONG(left - 0.5f), LONG(top - 0.5f), LONG(right + 0.5f), LONG(bottom + 0.5f) }; 
	} 

	float GetWidth () const { return right - left; }
	float GetHeight() const { return bottom - top; }
	bool  IsNone   () const { return left == right;}

	RectF& Trim(float dl, float dt, float dr, float db)
	{
		left += dl, top += dt, right -= dr, bottom -= db;
		return *this;
	}

	RectF GetOriginRect() const
	{
		assert(left <= right && top <= bottom);
		return { 0.0f, 0.0f, right - left, bottom - top };
	}

	Vector3 GetTopLeft() const
	{
		return Vector3{ left, top, 0.0f };
	}

	Vector3 GetCenter() const
	{
		const float x = (left + right) / 2;
		const float y = (top + bottom) / 2;
		return Vector3{ x, y, 0.0f };
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
