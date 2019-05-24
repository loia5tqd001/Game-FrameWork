#include "GameObject.h"
#include "Sprite.h"
#include "Textures.h"
#include "GameDev.h"



const RECT GameObject::GetBoundingBox() const
{
	if (!IsCollidable()) return {};
	const LONG left   = (LONG)pos.x;
	const LONG top    = (LONG)pos.y;
	const LONG right  = left + width;
	const LONG bottom = top + height;
	return { left, top, right, bottom };
}

void GameObject::RenderBoundingBox() const
{
	LPDIRECT3DTEXTURE9 bboxTexture = Textures::GetTexture(TextureType::Bbox);
	RECT               bbox        = GetBoundingBox();
	assert(OffsetRect(&bbox, -bbox.left, -bbox.top));
	GameDev::Instance().Draw(pos, bboxTexture, bbox, scale);
	// OffSetRect function: https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-offsetrect
}

void GameObject::Render() const
{
	if (IsCollidable()) RenderBoundingBox();
	animations.at(curState).Render(pos, scale);
}


