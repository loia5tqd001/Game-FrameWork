#include "GameObject.h"
#include "Sprite.h"
#include "Textures.h"
#include "GameDev.h"



const RECT GameObject::GetBoundingBox() const
{
	if (!IsActive()) return {};
	RECT boundingBox;
	boundingBox.left   = (UINT)pos.x - (GetWidth () / 2);
	boundingBox.top    = (UINT)pos.y - (GetHeight() / 2);
	boundingBox.right  = (UINT)pos.x + (GetWidth () / 2);
	boundingBox.bottom = (UINT)pos.y + (GetHeight() / 2);
	return boundingBox;
}

void GameObject::RenderBoundingBox() const
{
	LPDIRECT3DTEXTURE9 bboxTexture = Textures::Instance().GetTexture(TextureType::Bbox);
	const LONG left   = (LONG)pos.x;
	const LONG top    = (LONG)pos.y;
	const LONG right  = left + width;
	const LONG bottom = top + height;
	GameDev::Instance().Draw(pos, bboxTexture, { left, top, right, bottom }, scale);
}

void GameObject::Render() const
{
	RenderBoundingBox();
	animations.at(curState).Render(pos, scale);
}


