#pragma once

#include "enums.h"
#include "Sprite.h"



class Animation
{
private:
	const Sprite& sprite                                  ;
	const float   holdTime                                ;
	      float   holdingTime = 0.0f                      ;
	const UINT    nFrames     = sprite.GetNumberOfFrames();
	      UINT    curFrame    = 0u                        ;
		  bool    doneCycle   = false                     ;

public:
	Animation(SpriteType  spriteId, float holdTime);
	void Update(float dt);
	void Render(const D3DXVECTOR3& pos, Direction dir = Direction::Right, int alpha = 255) const;
	bool IsDoneCycle(); // for some animation aimed to animate one curve each call

};

