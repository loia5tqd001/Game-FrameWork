#include "GameObject.h"
#include "Sprite.h"
#include "Textures.h"
#include "GameDev.h"



const RectF GameObject::GetBoundingBox() const
{
	if (!IsCollidable()) return {};
	return { pos.x, pos.y, pos.x + width, pos.y + height };
}

void GameObject::RenderBoundingBox() const
{
	LPDIRECT3DTEXTURE9 bboxTexture = Textures::Get(TextureType::Bbox);
	RectF              bbox        = GetBoundingBox();

	bbox.OffSetRect(-bbox.GetWidth(), -bbox.GetHeight());
	GameDev::Instance().Draw(pos, bboxTexture, bbox, scale);
}

void GameObject::SetState(const State state)
{
	assert(animations.count(state) == 1); // check if the state's had the corresponding animation yet
	curState = state;
}

void GameObject::Render() const
{
	if (IsCollidable()) RenderBoundingBox();
	animations.at(curState).Render(pos, scale);
}


