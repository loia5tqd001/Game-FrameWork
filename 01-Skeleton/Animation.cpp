#include "Animation.h"
#include "Sprites.h"
#include "GameDev.h"

const LPD3DXSPRITE Animation::spriteHandler = GameDev::Instance().GetSpriteHandler();

Animation::Animation(LPDIRECT3DTEXTURE9 texture, const std::vector<RECT>& frames, float holdTime) :
	pTexture(texture),
	frames(frames),
	holdTime(holdTime),
	holdingTime(0.0f),
	curFrame(0u)
{}

void Animation::Update(float dt)
{
	holdingTime += dt;
	while (holdingTime >= holdTime)
	{
		if (++curFrame >= frames.size()) curFrame = 0;
		holdingTime -= holdTime;
	}
}

void Animation::Render(D3DXVECTOR3 pos, Direction dir) const
{
	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	if (dir == RightToLeft)
	{
		D3DXVECTOR2 vtScaleFlipX = D3DXVECTOR2(-1.0f, 1.0f);
		D3DXVECTOR2 centerScale = D3DXVECTOR2(pos.x, pos.y);
		D3DXMATRIX newMt;
		D3DXMatrixTransformation2D(&newMt, &centerScale, 0.0f, &vtScaleFlipX, NULL, 0.0f, NULL);
		D3DXMATRIX finalMt = newMt * oldMt;
		spriteHandler->SetTransform(&finalMt);
	}

	const RECT& rect = frames[curFrame];
	float xDraw = pos.x - float(rect.right - rect.left) / 2;
	float yDraw = pos.y - float(rect.bottom - rect.top) / 2;

	D3DXVECTOR3 drawPos(xDraw, yDraw, 0.0f);
	spriteHandler->Draw(pTexture, &rect, NULL, &drawPos, D3DCOLOR_XRGB(255, 255, 255));
	spriteHandler->SetTransform(&oldMt);
}


