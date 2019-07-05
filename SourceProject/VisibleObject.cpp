#include "pch.h"

VisibleObject::VisibleObject(State initState, Vector2 pos, Vector2 vel, FLOAT nx) :
	GameObject(pos, vel),
	curState(initState), 
	nx(nx) 
{
	assert(std::abs(nx) == 1.0f);
	animations.emplace( State::Destroyed, Animation(SpriteId::Invisible) );
}

void VisibleObject::FlipHorizontally()
{
	assert(std::abs(nx) == 1.0f);
	nx = -nx;
}

State VisibleObject::GetState() const
{
	assert(animations.count(curState) == 1);
	return curState;
}

RectF VisibleObject::GetBBox() const
{
	assert(animations.count(curState) == 1);
	const auto animationFrame = animations.at(curState).GetFrameSize();
	return { pos, animationFrame.GetWidth(), animationFrame.GetHeight() };
}

void VisibleObject::Render() const
{
	assert(animations.count(curState) == 1);
	assert(std::abs(nx) == 1.0f);

	if (shouldDrawImage && !DebugDraw::IsInDeepDebug()) 
	{
		const auto drawablePosition = Camera::Instance().GetPositionInViewPort( pos );
		animations.at(curState).Render( drawablePosition, { nx, 1.0f} ); // draw object's actual image
	}
	
	RenderBoundingBox(); // draw object's bounding box for better debugging
}

void VisibleObject::SetState(State state)
{
	assert(animations.count(state) == 1); // make sure the state already has a corresponding animation 
	curState = state;
}
