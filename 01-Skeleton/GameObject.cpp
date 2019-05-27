#include "pch.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Textures.h"
#include "GameDev.h"
#include "Camera.h"



const RectF GameObject::GetBoundingBox() const
{
	if (!IsCollidable()) return {};
	return { pos.x, pos.y + height, pos.x + width, pos.y };
}

const D3DXVECTOR3 GameObject::GetDrawablePos() const
{
	return Camera::Instance().GetDrawablePosition(*this);
}

void GameObject::RenderBoundingBox() const
{
	LPDIRECT3DTEXTURE9 bboxTexture = Textures::Get(TextureType::Bbox);
	RectF              bbox        = GetBoundingBox();

	bbox.OffSetRect(-bbox.GetWidth(), -bbox.GetHeight());
	GameDev::Instance().Draw(GetDrawablePos() + D3DXVECTOR3{ 0.0f,float(height),0.0f }, bboxTexture, bbox, scale);
	//TODO: figureout wth's going on
}

void GameObject::SetState(const State state)
{
	assert(animations.count(state) == 1); // check if the state has had the corresponding animation yet
	curState = state;
}

void GameObject::Render() const
{
	if (IsCollidable()) RenderBoundingBox();
	animations.at(curState).Render(GetDrawablePos(), scale);
}


