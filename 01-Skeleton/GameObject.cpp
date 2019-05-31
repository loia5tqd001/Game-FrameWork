#include "pch.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Textures.h"
#include "GameDev.h"
#include "Camera.h"


const UINT GameObject::GetWidth() const
{
	const  RECT& visualBox  = animations.at(curState).GetFrameSize();
	const  UINT normalWidth = explicitWidth ? explicitWidth : visualBox.right - visualBox.left;
	return UINT(normalWidth * std::abs(scale.x));
}

const UINT GameObject::GetHeight() const
{
	const  RECT& visualBox   = animations.at(curState).GetFrameSize();
	const  UINT normalHeight = explicitHeight ? explicitHeight : visualBox.bottom - visualBox.top;
	return UINT(normalHeight * std::abs(scale.y));
}

const RectF GameObject::GetBoundingBox() const
{
	if (!IsCollidable()) return {};
	return { pos.x, pos.y + GetHeight(), pos.x + GetWidth(), pos.y };
}

const D3DXVECTOR3 GameObject::GetDrawablePos() const
{
	return Camera::Instance().WorldRectToDrawablePosition(GetBoundingBox());
}

void GameObject::RenderBoundingBox() const
{
	LPDIRECT3DTEXTURE9 bboxTexture = Textures::Get(TextureType::Bbox);
	const RECT         portionDraw = animations.at(curState).GetFrameSize();
	GameDev::Instance().Draw(GetDrawablePos(), bboxTexture, portionDraw, scale);
}

void GameObject::SetState(const State state)
{
	assert(animations.count(state) == 1); // make sure the state has already had a corresponding animation 
	curState = state;
}

void GameObject::Render() const
{
	if (IsCollidable()) RenderBoundingBox();
	animations.at(curState).Render(GetDrawablePos(), scale);
}


