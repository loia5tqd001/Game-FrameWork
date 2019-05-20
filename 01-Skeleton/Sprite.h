#pragma once
#include "MyException.h"
#include "define.h"
#include <d3dx9.h>


class Sprite
{
private:
	LPD3DXSPRITE spriteHandler; 
	LPDIRECT3DTEXTURE9 pTexture;
	RECT portion;
	bool isFlipX;

public:
	Sprite(Sprite&&) noexcept = default;
	Sprite(const Sprite&) = delete;

	Sprite(LPDIRECT3DTEXTURE9 texture, RECT portion, bool isFlipX);
	void Draw(D3DXVECTOR3 pos);
};


