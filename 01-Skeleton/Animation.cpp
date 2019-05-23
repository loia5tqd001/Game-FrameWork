#include "Animation.h"
#include "GameDev.h"
#include "Textures.h"
#include "Frames.h"


Animation::Animation(const Sprite& sprite, float holdTime) :
	sprite(sprite),
	holdTime(holdTime),
	nFrames(sprite.GetNumberOfFrames())
{}

void Animation::Update(float dt)
{
	holdingTime += dt;
	while (holdingTime >= holdTime)
	{
		if (++curFrame >= nFrames) curFrame = 0;
		holdingTime -= holdTime;
	}
}

void Animation::Render(const D3DXVECTOR3& pos, Direction dir, int alpha) const
{
	sprite.Draw(pos, curFrame, dir == Direction::Left, alpha);
}


