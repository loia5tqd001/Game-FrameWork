#include "Animation.h"
#include "GameDev.h"
#include "Sprites.h"




Animation::Animation(SpriteType spriteId, float holdTime) :
	sprite(Sprites::Instance().GetSprite(spriteId)),
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

void Animation::Render(const D3DXVECTOR3& pos, Direction dir, int alpha) const
{
	sprite.Draw(pos, curFrame, dir == Direction::Left, alpha);
}

bool Animation::IsDoneCycle()
{
	if (!doneCycle) return false;

	else doneCycle = false, curFrame = 0u, holdingTime = 0.0f;
	return true;
	
}


