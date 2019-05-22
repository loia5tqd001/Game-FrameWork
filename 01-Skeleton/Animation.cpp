#include "Animation.h"
#include "GameDev.h"
#include "Textures.h"
#include "Frames.h"


Animation::Animation(TextureType textureType, AnimationType animationType, float holdTime) :
	//spriteHandler(GameDev::Instance().GetSpriteHandler()),
	pTexture(Textures::Instance().GetTexture(textureType)),
	frames(Frames::Instance().GetFrames(animationType)),
	holdTime(holdTime)
{}

Animation::Animation(LPDIRECT3DTEXTURE9 texture, const std::vector<RECT>& frames, float holdTime) :
	//spriteHandler(GameDev::Instance().GetSpriteHandler()),
	pTexture(texture),
	frames(frames),
	holdTime(holdTime)
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
	LPD3DXSPRITE spriteHandler = GameDev::Instance().GetSpriteHandler();
	D3DXMATRIX oldMt;
	spriteHandler->GetTransform(&oldMt);

	if (dir == Direction::Left)
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


