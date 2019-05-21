#include "Sprite.h"
#include "GameDev.h"

Sprite::Sprite(LPDIRECT3DTEXTURE9 texture, RECT portion) : pTexture(texture), portion(portion), spriteHandler(GameDev::Instance().GetSpriteHandler()) {}

void Sprite::Draw(D3DXVECTOR3 pos, bool isFlipX) const
{
	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	if (isFlipX)
	{
		D3DXVECTOR2 vtScaleFlipX = D3DXVECTOR2(-1.0f, 1.0f);
		D3DXVECTOR2 centerScale = D3DXVECTOR2(pos.x, pos.y);
		D3DXMATRIX newMt;
		D3DXMatrixTransformation2D(&newMt, &centerScale, 0.0f, &vtScaleFlipX, NULL, 0.0f, NULL);
		D3DXMATRIX finalMt = newMt * oldMt;
		spriteHandler->SetTransform(&finalMt);
	}

	// 'pos' is the position of the entity owns the sprite, which anchors to the center of that enity.
	// by default we will draw from the position at the top left of the sprite, not the center.
	// so we calculate starting drawing position by offsetting to the top left direction from 'pos'

	float xDraw = pos.x - float(portion.right - portion.left) / 2;
	float yDraw = pos.y - float(portion.bottom - portion.top) / 2;
	D3DXVECTOR3 drawPos(xDraw, yDraw, 0.0f);
	spriteHandler->Draw(pTexture, &portion, NULL, &drawPos, D3DCOLOR_XRGB(255, 255, 255));

	//Draw function: https://docs.microsoft.com/en-us/windows/desktop/direct3d9/id3dxsprite--draw

	spriteHandler->SetTransform(&oldMt);
}
