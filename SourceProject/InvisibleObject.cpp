#include "pch.h"

InvisibleObject::InvisibleObject(Vector2 pos, UINT w, UINT h, Vector2 vel) :
	GameObject(pos, vel), 
	width(w), 
	height(h) 
{
}

State InvisibleObject::GetState() const
{
	return State::Invisible;
}

RectF InvisibleObject::GetBBox() const
{
	return { pos, width, height };
}

void InvisibleObject::Render() const
{
	RenderBoundingBox();
}
