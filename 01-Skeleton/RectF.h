#pragma once
#include <d3dx9.h>


struct RectF
{
	float left, top, right, bottom;

	RectF() : RectF(0.0f, 0.0f, 0.0f, 0.0f) {}
	RectF(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) {}

	float GetWidth () const { return right - left; }
	float GetHeight() const { return bottom - top; }

	operator RECT() const
	{
		return { (LONG)left, (LONG)top, (LONG)right, (LONG)bottom };
	}

	bool IsIntersect(const RectF& other) const
	{
		return left <= other.right && right >= other.left
			&& top <= other.bottom && bottom >= other.top;
	}

	RectF& OffSetRect(float dx, float dy)
	{
		left += dx, right  += dx;
		top  += dy, bottom += dy;
		return *this;
	}
	RectF GetOffSetRect(float dx, float dy) const
	{
		RectF result = *this;
		return result.OffSetRect(dx, dy);
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