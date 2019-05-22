#include "Sprite.h"
#include "GameDev.h"

Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, RECT portion) : 
	pTexture(texture), 
	portion(portion) 
{}

void Sprite::Draw(const D3DXVECTOR3& pos, bool isFlipX, int alpha) const
{
	GameDev::Instance().Draw(pos, pTexture, portion, isFlipX, alpha);
}
