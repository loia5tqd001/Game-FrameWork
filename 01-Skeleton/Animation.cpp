#include "pch.h"
#include "Animation.h"
#include "GameDev.h"
#include "Sprites.h"


Animation::Animation(SpriteType spriteId, float holdTime) :
	sprite(Sprites::Get(spriteId)),
	holdTime(holdTime)
{
	if (holdTime == std::numeric_limits<float>::infinity())
	{
		assert(nFrames == 1);
	}
}

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

void Animation::Render(const Point& pos, const Vector2& vtScale, int alpha) const
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


