#include "Sprite.h"
#include "GameDev.h"

Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, std::vector<RECT> frames) : 
	texture(texture), 
	frames(frames) 
{}

void Sprite::Draw(const D3DXVECTOR3& pos, UINT frameIndex, bool isFlipX, int alpha) const
{
	assert(frameIndex <= frames.size());
	GameDev::Instance().Draw(pos, texture, frames[frameIndex], isFlipX, alpha);
}
