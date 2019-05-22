#include "Animation.h"
#include "GameDev.h"
#include "Textures.h"
#include "Frames.h"


Animation::Animation(TextureType textureType, AnimationType animationType, float holdTime) :
	pTexture(Textures::Instance().GetTexture(textureType)),
	frames(Frames::Instance().GetFrames(animationType)),
	holdTime(holdTime)
{}

Animation::Animation(LPDIRECT3DTEXTURE9 texture, const std::vector<RECT>& frames, float holdTime) :
	pTexture(texture),
	frames(frames),
	holdTime(holdTime)
{}

void Animation::Update(float dt)
{
	holdingTime += dt;
	while (holdingTime >= holdTime)
	{
		if (++curFrame >= frames.size()) 
		{
			curFrame = 0;
		}
		holdingTime -= holdTime;
	}
}

void Animation::Render(const D3DXVECTOR3& pos, Direction dir, int alpha) const
{
	GameDev::Instance().Draw(pos, pTexture, frames[curFrame], dir == Direction::Left, alpha);
}


