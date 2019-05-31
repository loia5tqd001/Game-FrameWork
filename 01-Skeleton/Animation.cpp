#include "pch.h"
#include "Animation.h"
#include "GameDev.h"
#include "Sprites.h"




Animation::Animation(SpriteType spriteId, float holdTime) :
	sprite(Sprites::Get(spriteId)),
	holdTime(holdTime)
{}

void Animation::Update(float dt)
{
	holdingTime += dt;
	while (holdingTime >= holdTime)
	{
		curFrame++;
		if (curFrame >= nFrames)
		{
			doneCycle = true;
			curFrame = 0;
		}
		holdingTime -= holdTime;
	}
}

void Animation::Render(const D3DXVECTOR3& pos, const D3DXVECTOR2& vtScale, int alpha) const
{
	sprite.Draw(pos, curFrame, vtScale, alpha);
}

bool Animation::IsDoneCycle()
{
	if (!doneCycle) return false;

	else doneCycle = false, curFrame = 0u, holdingTime = 0.0f;
	return true;
	
}

RECT Animation::GetFrameSize(const D3DXVECTOR2 & vtScale) const
{
	return sprite.GetFrameSize(curFrame, vtScale);
}


