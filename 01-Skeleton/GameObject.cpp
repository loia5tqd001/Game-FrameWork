#include "pch.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Textures.h"
#include "GameDev.h"
#include "Camera.h"


const Point GameObject::GetCenter() const
{
	return GetBoundingBox().GetCenter();
}

const UINT GameObject::GetWidth() const
{
	const  Rect& frameSize = animations.at(curState).GetFrameSize();
	const  UINT normalWidth = explicitWidth ? explicitWidth : frameSize.GetWidth();
	return UINT(normalWidth * std::abs(scale.x));
}

const UINT GameObject::GetHeight() const
{
	const  Rect& frameSize   = animations.at(curState).GetFrameSize();
	const  UINT normalHeight = explicitHeight ? explicitHeight : frameSize.GetHeight();
	return UINT(normalHeight * std::abs(scale.y));
}

const RectF GameObject::GetBoundingBox() const
{
	if (!IsCollidable()) return {};
	return { pos.x, pos.y, GetWidth(), GetHeight() };
}

const Point GameObject::GetDrawablePos() const
{
	static auto& cam = Camera::Instance();
	return cam.GetPositionInViewPort(GetPosition());
}

void GameObject::RenderBoundingBox() const
{
	const auto bboxTexture = Textures::Get(TextureType::Bbox);
	const auto portionDraw = animations.at(curState).GetFrameSize();
	GameDev::Instance().Draw(GetDrawablePos(), bboxTexture, portionDraw, scale);
}

void GameObject::SetState(State state)
{
	assert(animations.count(state) == 1); // make sure the state has already had a corresponding animation 
	curState = state;
}

void GameObject::Render() const
{
	if (IsCollidable()) RenderBoundingBox();
	animations.at(curState).Render(GetDrawablePos(), scale);
}


