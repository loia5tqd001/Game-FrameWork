#include "pch.h"

void GameObject::RenderBoundingBox() const
{
	DebugDraw::DrawSolidRect( GetBBox(), bboxColor ); 
}

void GameObject::GetDxDy(float dt, float& dx, float& dy) const
{
	dx = vel.x * dt;
	dy = vel.y * dt;
}

void GameObject::ClampWithin(const RectF& theBox)
{
	const auto objBBox = GetBBox();
	Utils::Clamp(pos.x, theBox.left, theBox.right - objBBox.GetWidth());
	Utils::Clamp(pos.y, theBox.top, theBox.bottom - objBBox.GetHeight());
}

Vector2 GameObject::GetVelocity() const
{
	return vel;
}

GameObject::GameObject(Vector2 pos, Vector2 vel) : 
	pos(pos),
	vel(vel),
	bboxColor(Colors::DimGray)
{
}
