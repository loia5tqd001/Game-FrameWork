#include "pch.h"
#include "VisibleObject.h"
#include "Camera.h"

VisibleObject::VisibleObject(State initState, Vector3 pos, Vector2 vel, FLOAT nx) :
	GameObject(pos, vel),
	curState(initState), 
	nx(nx) 
{
	assert(std::abs(nx) == 1.0f);
	animations.emplace( State::Destroyed, Animation(SpriteType::Invisible) );
}

void VisibleObject::FlipHorizontally()
{
	assert(std::abs(nx) == 1.0f);
	nx = -nx;
}

void VisibleObject::LowDownBody(UINT oldHeight)
{ 
	assert(oldHeight > GetHeight());
	pos.y += oldHeight - GetHeight(); 
}

State VisibleObject::GetState() const
{
	assert(animations.count(curState) == 1);
	return curState;
}

UINT VisibleObject::GetWidth() const
{
	assert(animations.count(curState) == 1);
	return animations.at(curState).GetFrameSize().GetWidth();
}

UINT VisibleObject::GetHeight() const
{
	assert(animations.count(curState) == 1);
	return animations.at(curState).GetFrameSize().GetHeight();
}

void VisibleObject::Render() const
{
	assert(animations.count(curState) == 1);
	assert(std::abs(nx) == 1.0f);

	const Vector3 drawablePosition = Camera::Instance().GetPositionInViewPort( pos );
	animations.at(curState).Render( drawablePosition, { nx, 1.0f} ); // draw object's actual image
	
	RenderBoundingBox(); // draw object's bounding box for better debugging
}

void VisibleObject::SetState(State state)
{
	assert(animations.count(state) == 1); // make sure the state already has a corresponding animation 
	curState = state;
}
