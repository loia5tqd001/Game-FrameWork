#include "pch.h"
#include "InvisibleObject.h"

InvisibleObject::InvisibleObject(Vector3 pos, UINT w, UINT h, Vector2 vel) :
	GameObject(pos, vel), 
	width(w), 
	height(h) 
{
}

State InvisibleObject::GetState() const
{
	return State::Invisible;
}

UINT InvisibleObject::GetWidth() const
{
	return width;
}

UINT InvisibleObject::GetHeight() const
{
	return height;
}

void InvisibleObject::Render() const
{
	RenderBoundingBox();
}
