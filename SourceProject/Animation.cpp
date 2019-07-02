#include "pch.h"

Animation::Animation(SpriteId spriteId, float holdTime) :
	sprite(Sprites::Get(spriteId)),
	holdTime(holdTime)
{
	if (holdTime == 0.0f)
	{
		assert(nFrames == 1);
		doneCycle = true;
	}
}

void Animation::Update(float dt)
{
	if (nFrames == 1) return;

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

void Animation::Render(const Vector2& pos, const Vector2& vtScale, int alpha) const
{
	sprite.Draw(pos, curFrame, vtScale, alpha);
}

bool Animation::IsDoneCycle()
{
	if (!doneCycle) return false;

	else doneCycle = false, curFrame = 0u, holdingTime = 0.0f;
	return true;
	
}

Rect Animation::GetFrameSize(const Vector2 & vtScale) const
{
	return sprite.GetFrameSize(curFrame, vtScale);
}


