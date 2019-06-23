#include "pch.h"
#include "Sprite.h"
#include "Game.h"


Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, const std::vector<Rect>& frames) : 
	texture(texture), 
	frames(frames) 
{
}

void Sprite::Draw(const Vector2& pos, UINT frameIndex, const Vector2& vtScale, int alpha) const
{
	assert(frameIndex <= frames.size());
	Game::Instance().Draw(pos, texture, frames[frameIndex], vtScale, alpha);
}

Rect Sprite::GetFrameSize(UINT frameIndex, const Vector2 & vtScale) const
{
	assert(frameIndex <= frames.size());
	return frames[frameIndex] * vtScale.GetAbs();
}
