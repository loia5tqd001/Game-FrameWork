#include "GameObject.h"
#include "Sprite.h"
#include "Textures.h"
#include "GameDev.h"



RECT GameObject::GetBoundingBox() const
{
	RECT boundingBox;
	boundingBox.left   = (UINT)pos.x - (GetWidth () / 2);
	boundingBox.top    = (UINT)pos.y - (GetHeight() / 2);
	boundingBox.right  = (UINT)pos.x + (GetWidth () / 2);
	boundingBox.bottom = (UINT)pos.y + (GetHeight() / 2);
	return boundingBox;
}

void GameObject::RenderBoundingBox() const
{
	LPDIRECT3DTEXTURE9 bbox = Textures::Instance().GetTexture(TextureType::Bbox);
	GameDev::Instance().Draw(pos, bbox, GetBoundingBox());
}


