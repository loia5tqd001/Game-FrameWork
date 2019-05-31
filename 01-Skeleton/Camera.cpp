#include "pch.h"
#include "Camera.h"

const RectF Camera::GetBBox() const
{
	const float left   = pos.x  ;
	const float right  = left   + (float)width;
	const float bottom = pos.y  ;
	const float top    = bottom + (float)height;
	return { left, top, right, bottom };
}

// convert bottom left world coordinate rectangle to drawable top left coordinate position
D3DXVECTOR3 Camera::WorldRectToDrawablePosition(const RectF & rect) const
{
	assert(rect.bottom < rect.top);
	RectF cameraRect = GetBBox();
	return { rect.left - cameraRect.left, cameraRect.top - rect.top, 0.0f }; // demonstrate pictures on paper for more comprehension imagine
}

void Camera::CenterTo(const D3DXVECTOR3 & newPos)
{
	MoveTo(newPos - D3DXVECTOR3((float)width / 2, (float)height / 2, 0.0f));
}
