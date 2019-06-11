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
		assert(top < bottom);
	}
	RectF(float x, float y, UINT width, UINT height) : RectF(x, y, x + width, y + height)
	{}

	operator Rect() const
	{
		return { left + 0.5f, top + 0.5f, right + 0.5f, bottom + 0.5f };
	}

	float GetWidth () const { return right - left; }
	float GetHeight() const { return bottom - top; }

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

	RectF& MoveToOrigin()
	{
		return OffsetRect(left, top);
	}
	Rect GetMovedToOrigin() const
	{
		RectF result = *this;
		return result.MoveToOrigin();
	}
	RectF& OffsetRect(float dx, float dy)
	{
		left += dx, right  += dx;
		top  += dy, bottom += dy;
		return *this;
	}
	RectF GetOffsetRect(float dx, float dy) const
	{
		RectF result = *this;
		return result.OffsetRect(dx, dy);
	}
	RectF& BroadPhase(float dx, float dy)
	{
		left   = min(left  , left   + dx);
		top    = min(top   , top    + dy);
		right  = max(right , right  + dx);
		bottom = max(bottom, bottom + dy);
		return *this;
	}
	RectF GetBroadPhase(float dx, float dy) const
	{
		RectF result = *this;
		return result.BroadPhase(dx, dy);
	}
};
