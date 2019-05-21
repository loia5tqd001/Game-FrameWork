#include "GameObject.h"



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
	// TODO: after create window successfully
	////D3DXVECTOR3 p(x, y, 0);
	//RECT rect;

	//LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance().GetTexture(TextureType::Bbox);

	//

	//Game::GetInstance()->Draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 32);
}


