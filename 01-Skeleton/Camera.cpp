#include "pch.h"
#include "Camera.h"

void Camera::CenterTo(const D3DXVECTOR3 & newPos)
{
	MoveTo(newPos - D3DXVECTOR3((float)width / 2, (float)height / 2, 0.0f));
}

const RectF Camera::GetBBox() const
{
	const float left   = pos.x  ;
	const float right  = left   + (float)width;
	const float bottom = pos.y  ;
	const float top    = bottom + (float)height;
	return { left, top, right, bottom };
}

D3DXVECTOR3 Camera::GetDrawablePosition(const GameObject & obj) const
{
	const D3DXVECTOR3& objPos = obj.GetPosition();
	const float leftInScreen  = objPos.x - pos.x;
	const float topInScreen   = height - (objPos.y - pos.y + obj.GetHeight());
	return { leftInScreen, topInScreen, 0.0f };
}

// convert bottom left world coordinate rectangle to drawable top left coordinate position
D3DXVECTOR3 Camera::WorldRectToDrawablePosition(const RectF & rect) const
{
	assert(rect.bottom < rect.top);
	RectF cameraRect = GetBBox();
	return { rect.left - cameraRect.left, cameraRect.top - rect.top, 0.0f }; // demonstrate pictures on paper for more comprehension imagine
}


