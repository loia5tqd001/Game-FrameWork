#pragma once


struct RectF
{
	float left, top, right, bottom;

	RectF() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) {}
	RectF(float l, float t, float r, float b) : left(l), top(t), right(r), bottom(b) 
	{
		assert(top > bottom);
	}

	float GetWidth () const { return right - left; }
	float GetHeight() const { return top - bottom; }

	bool IsIntersect(const RectF& other) const
	{
		return left < other.right && right > other.left
			&& bottom < other.top && top > other.bottom;
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
		right  = max(right , right  + dx);
		bottom = min(bottom, bottom + dy);
		top    = max(top   , top    + dy);
		return *this;
	}
	RectF GetBroadPhase(float dx, float dy) const
	{
		RectF result = *this;
		return result.BroadPhase(dx, dy);
	}
};
