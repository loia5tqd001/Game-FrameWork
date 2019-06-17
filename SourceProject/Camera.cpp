#include "pch.h"
#include "Camera.h"

void Camera::MoveTo(const Vector3 & newPos)
{
	pos = newPos;
}

void Camera::MoveBy(const Vector2 & dist)
{
	MoveTo(pos + dist);
}

void Camera::CenterTo(const Vector3 & center)
{
	MoveTo(center);
	MoveBy({ -float(width / 2), -float(height / 2) });
}

const Vector3 & Camera::GetPosition() const
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

Vector3 Camera::GetPositionInViewPort(const Vector3 & pos) const
{
	return pos - GetPosition();
}

