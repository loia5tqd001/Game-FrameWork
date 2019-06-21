#include "pch.h"
#include "GameObject.h"
#include "DebugDraw.h"


void GameObject::RenderBoundingBox() const
{
	DebugDraw::Draw( GetBBox(), DrawType::SolidRect, bboxColor ); 
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
