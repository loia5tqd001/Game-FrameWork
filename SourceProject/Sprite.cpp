#include "pch.h"

Sprite::Sprite(Sprite&& other) noexcept :
	texture( std::move(other.texture) ),
	frames( std::move(other.frames) )
{
}

Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, const std::vector<Rect>& frames) :
	texture(texture), 
	frames(frames) 
{
}

void Sprite::Draw(const Vector2& pos, UINT frameIndex, const Vector2& vtScale, int alpha) const
{
	assert(frameIndex <= frames.size());
	Game::Instance().Draw(pos, texture, frames[frameIndex], vtScale, D3DCOLOR_ARGB(alpha, 255, 255, 255));
}

Rect Sprite::GetFrameSize(UINT frameIndex, const Vector2 & vtScale) const
{
	assert(frameIndex <= frames.size());
	return frames[frameIndex] * vtScale.GetAbs();
}
