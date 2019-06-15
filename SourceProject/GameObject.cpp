#include "pch.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Textures.h"
#include "Game.h"
#include "Camera.h"
#include "DebugDraw.h"

GameObject::GameObject(State initState, const Point& pos, const Vector2& vel, const Vector2& scale) :
	curState(initState),
	pos(pos),
	vel(vel),
	scale(scale)
{
}

void GameObject::LowDownBody(UINT oldHeight)
{
	pos.y += oldHeight - GetHeight();
}

const Point GameObject::GetCenter() const
{
	return GetBoundingBox().GetCenter();
}

const UINT GameObject::GetWidth() const
{
	const  Rect& frameSize  = animations.at(curState).GetFrameSize();
	const  UINT normalWidth = explicitWidth ? explicitWidth : frameSize.GetWidth();
	return UINT(normalWidth * std::abs(scale.x));
}

const UINT GameObject::GetHeight() const
{
	const  Rect& frameSize   = animations.at(curState).GetFrameSize();
	const  UINT normalHeight = explicitHeight ? explicitHeight : frameSize.GetHeight();
	return UINT(normalHeight * std::abs(scale.y));
}

void GameObject::SetWidthHeight(UINT w, UINT h)
{
	assert(curState == State::Invisible); // only invisible objects should have explicitWidth and explicitHeight
	explicitWidth  = w;
	explicitHeight = h;
}

const RectF GameObject::GetBoundingBox() const
{
	if (!IsCollidable()) return {};
	return { pos.x, pos.y, GetWidth(), GetHeight() };
}

const RectF GameObject::GetVisibleBox() const
{
	const  Rect& frameSize  = animations.at(curState).GetFrameSize();
	const  UINT  frameWidth = UINT( frameSize.GetWidth()  * std::abs(scale.x) );
	const  UINT frameHeight = UINT( frameSize.GetHeight() * std::abs(scale.y) );
	return { pos.x, pos.y, frameWidth, frameHeight };
}

const Point GameObject::GetDrawablePos() const
{
	static auto& cam = Camera::Instance();
	return cam.GetPositionInViewPort(GetPosition()); 
}

void GameObject::SetState(State state)
{
	assert(animations.count(state) == 1); // make sure the state has already had a corresponding animation 
	curState = state;
}

void GameObject::Render() const
{
	if (IsCollidable()) DebugDraw::Draw( GetBoundingBox(), DebugDraw::DrawType::SolidHalf );
	else                DebugDraw::Draw( GetVisibleBox (), DebugDraw::DrawType::SolidFull );

	animations.at(curState).Render(GetDrawablePos(), scale);
}


