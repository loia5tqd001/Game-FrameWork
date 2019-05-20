#pragma once
#include <d3dx9.h>

// to draw static sprite
class Sprite
{
private:
	static const LPD3DXSPRITE spriteHandler;
	const LPDIRECT3DTEXTURE9 pTexture;
	const RECT portion;

public:
	Sprite(LPDIRECT3DTEXTURE9 texture, RECT portion) : pTexture(texture), portion(portion) {}
	void Draw(D3DXVECTOR3 pos, bool isFlipX) const;
};



