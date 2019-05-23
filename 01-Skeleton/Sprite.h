#pragma once
#include <d3dx9.h>
#include <vector>


class Sprite
{
private:
	const LPDIRECT3DTEXTURE9 texture;
	const std::vector<RECT>  frames;

public:
	Sprite(LPDIRECT3DTEXTURE9 texture, std::vector<RECT> frames);
	void Draw(const D3DXVECTOR3& pos, UINT frameIndex, const D3DXVECTOR2& vtScale = { 1.0f, 1.0f }, int alpha = 255) const;
	UINT GetNumberOfFrames() const { return frames.size(); }
	RECT GetFrameSize(UINT frameIndex, const D3DXVECTOR2& vtScale = { 1.0f, 1.0f }) const;
};



