#pragma once
#include "GameDev.h"

class Sprite
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE spriteHandler = GameDev::Instance().GetSpriteHandler();

public:
	void Draw(POINTFLOAT pos, LPDIRECT3DTEXTURE9 pTexture, RECT portion); // move to sprite class
	void Draw(POINTFLOAT pos, bool isFlipX);
};

void Sprite::Draw(POINTFLOAT pos, LPDIRECT3DTEXTURE9 pTexture, RECT portion)
{
	// 'pos' is the position of sprite, which anchors to the center of that sprite.
	// we want to draw from the position at the top left of that sprite (not the center),
	// so we calculate draw position by translate haft the size of the sprite to the top left direction from that sprite position
	float xDraw = pos.x - float(portion.right - portion.left) / 2;
	float yDraw = pos.y - float(portion.bottom - portion.top) / 2;
	D3DXVECTOR3 drawPos(xDraw, yDraw, 0.0f);
	spriteHandler->Draw(pTexture, &portion, NULL, &drawPos, D3DCOLOR_XRGB(255, 255, 255));
	//Draw function: https://docs.microsoft.com/en-us/windows/desktop/direct3d9/id3dxsprite--draw
}

