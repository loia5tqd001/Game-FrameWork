#include "pch.h"
#include "Camera.h"

void Camera::MoveTo(const Vector2 & newPos)
{
	pos = newPos;
}

void Camera::MoveBy(const Vector2 & dist)
{
	MoveTo(pos + dist);
}

void Camera::CenterTo(const Vector2 & center)
{
	MoveTo(center);
	MoveBy({ -float(width / 2), -float(height / 2) });
}

void Camera::ClampWithin(const RectF& theBox)
{
	Utils::Clamp(pos.x, theBox.left, theBox.right - width);
	Utils::Clamp(pos.y, theBox.top, theBox.bottom - height);
}

const Vector2 & Camera::GetPosition() const
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

Vector2 Camera::GetPositionInViewPort(const Vector2 & pos) const
{
	return pos - GetPosition();
}

