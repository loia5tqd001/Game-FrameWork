#pragma once
#include "Rect.h"


struct RectF
{
	float left, top, right, bottom;

	RectF(                                         ) : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) {}
	RectF(float l, float t, float r   , float b    ) : left(l   ), top(t   ), right(r   ), bottom(b   ) { assert(top <= bottom); }
	RectF(float x, float y, UINT width, UINT height) : RectF(x, y, x + width, y + height              ) {}

	operator Rect      () const { return { left, top, right, bottom }              ; } 
	Vector2  GetTopLeft() const { return { left, top }                             ; }
	Vector2  GetCenter () const { return { (left + right) / 2, (top + bottom) / 2} ; }
	float    GetWidth  () const { return right - left                              ; }
	float    GetHeight () const { return bottom - top                              ; }
	bool     IsNone    () const { return left == right                             ; }
	RectF    Clone     () const { return *this                                     ; }

	RectF GetOriginRect() const
	{
		assert(left <= right && top <= bottom);
		return { 0.0f, 0.0f, right - left, bottom - top };
	}
	RectF& Trim(float dl, float dt, float dr, float db)
	{
		left += dl, top += dt, right -= dr, bottom -= db;
		return *this;
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
