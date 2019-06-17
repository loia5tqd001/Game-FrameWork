#include "pch.h"
#include "GameObject.h"
#include "DebugDraw.h"

RectF GameObject::GetBoundingBox() const
{
	if (GetWidth() == 0) return {};
	return { pos.x, pos.y, GetWidth(), GetHeight() };
}

void GameObject::RenderBoundingBox() const
{
	DebugDraw::Draw( GetBoundingBox(), DrawType::SolidRect, bboxColor ); 
}

Vector2 GameObject::GetVelocity() const
{
	return vel;
}

GameObject::GameObject(Vector3 pos, Vector2 vel) : 
	pos(pos),
	vel(vel),
	bboxColor(Colors::MyChineseBrown)
{
}
