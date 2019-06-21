#include "pch.h"
#include "GameObject.h"


void GameObject::RenderBoundingBox() const
{
	DebugDraw::DrawSolidRect( GetBBox(), bboxColor ); 
}

void GameObject::GetDxDy(float dt, float& dx, float& dy) const
{
	dx = vel.x * dt;
	dy = vel.y * dt;
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
