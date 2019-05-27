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

D3DXVECTOR3 Camera::GetDrawablePosition(const GameObject & obj) const
{
	const D3DXVECTOR3& objPos = obj.GetPosition();
	const float leftInScreen  = objPos.x - pos.x;
	const float topInScreen   = height - (objPos.y - pos.y + obj.GetHeight());
	return { leftInScreen, topInScreen, 0.0f };
}
