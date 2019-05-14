#pragma once
#include <d3dx9.h>
#include "MyException.h"


class Sprite
{
private:
	LPD3DXSPRITE spriteHandler; 
	LPDIRECT3DTEXTURE9 pTexture;
	RECT portion;
	bool isFlipX;


public:
	Sprite(Sprite&&) noexcept {DebugOut("Moved\n");}//TODO: debug
	Sprite(const Sprite&)     {DebugOut("Copied\n"); }
	Sprite& operator=(const Sprite&) = default;

	Sprite(LPDIRECT3DTEXTURE9 texture, RECT portion, bool isFlipX);
	void Draw(POINTFLOAT pos);
};


