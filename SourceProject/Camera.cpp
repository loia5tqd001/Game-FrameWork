#include "pch.h"

void Camera::MoveTo(const Vector2 & newPos)
{
	pos.x = floor(newPos.x);
	pos.y = floor(newPos.y);
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

const RectF Camera::GetBBox() const
{
	return { pos, width, height };
}

Vector2 Camera::GetPositionInViewPort(const Vector2 & objPos) const
{
	return objPos - pos;
}

Camera& Camera::Instance()
{
	static Camera instance;
	return instance;
}

