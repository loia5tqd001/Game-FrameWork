#include "pch.h"
#include "Camera.h"

void Camera::MoveTo(const Point & newPos)
{
	pos = newPos;
}

void Camera::MoveBy(const Distance & dist)
{
	MoveTo(pos + dist);
}

void Camera::CenterTo(const Point & center)
{
	MoveTo(center);
	MoveBy({ -float(width / 2), -float(height / 2) });
}

const Point & Camera::GetPosition() const
{
	return pos;
}

const RectF Camera::GetBBox() const
{
	return { pos.x, pos.y, width, height };
}

bool Camera::IsIntersect(const RectF & box) const
{
	return GetBBox().IsIntersect(box);
}

Point Camera::GetPositionInViewPort(const Point & pos) const
{
	return pos - GetPosition();
}

