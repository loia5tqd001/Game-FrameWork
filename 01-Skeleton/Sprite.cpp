#include "Sprite.h"
#include "GameDev.h"

Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, std::vector<RectF> frames) : 
	texture(texture), 
	frames(frames) 
{}

void Sprite::Draw(const D3DXVECTOR3& pos, UINT frameIndex, const D3DXVECTOR2& vtScale, int alpha) const
{
	assert(frameIndex <= frames.size());
	GameDev::Instance().Draw(pos, texture, frames[frameIndex], vtScale, alpha);
}

RectF Sprite::GetFrameSize(UINT frameIndex, const D3DXVECTOR2 & vtScale) const
{
	assert(frameIndex <= frames.size());
	const float xScale = std::abs(vtScale.x);
	const float yScale = std::abs(vtScale.y);
	RectF  visibleBox = frames[frameIndex];
	visibleBox.left   *= xScale;
	visibleBox.top    *= yScale;
	visibleBox.right  *= xScale;
	visibleBox.bottom *= yScale;
	return visibleBox;
}
