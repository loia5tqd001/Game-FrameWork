#include "pch.h"
#include "Camera.h"

void Camera::MoveTo(const Point & newPos)
{
	pos = newPos;
}

void Camera::MoveBy(const Distance & dist)
{
	pos += dist;
}

void Camera::CenterTo(const Point & center)
{
	MoveTo(center);
	MoveBy({ -float(width), -float(height) });
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

Point Camera::GetPositionInViewPort(const GameObject & obj) const
{
	return obj.GetPosition() - GetPosition();
}

//// convert bottom left world coordinate rectangle to drawable top left coordinate position
//Point Camera::WorldRectToDrawablePosition(const RectF & rect) const
//{
//	assert(rect.bottom < rect.top);
//	RectF cameraRect = GetBBox();
//	return { rect.left - cameraRect.left, cameraRect.top - rect.top, 0.0f }; // demonstrate pictures on paper for more comprehension imagine
//}


