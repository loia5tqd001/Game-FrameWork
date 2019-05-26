#pragma once

#include "enums.h"
#include "Sprite.h"



class Animation
{
private:
	const Sprite& sprite            ;
	const float   holdTime          ;
	      float   holdingTime = 0.0f;
	const UINT    nFrames           ;
	      UINT    curFrame    = 0u  ;

public:
	Animation(const Sprite& sprite, float holdTime);
	Animation(SpriteType  spriteId, float holdTime);
	void Update(float dt);
	void Render(const D3DXVECTOR3& pos, Direction dir = Direction::Right, int alpha = 255) const;

};

