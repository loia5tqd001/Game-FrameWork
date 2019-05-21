#pragma once

#include "define.h"
#include <d3dx9.h>
#include <vector>


class Animation
{
private:
	const LPD3DXSPRITE spriteHandler = GameDev::Instance().GetSpriteHandler();

	const LPDIRECT3DTEXTURE9 pTexture          ;
	const std::vector<RECT>& frames            ;
	const float              holdTime          ;
	      float              holdingTime = 0.0f;
	      unsigned int       curFrame    = 0u  ;

public:
	Animation(LPDIRECT3DTEXTURE9 texture, const std::vector<RECT>& frames, float holdTime);
	Animation(TextureType textureType, AnimationType animationType, float holdTime);
	void Update(float dt);
	void Render(D3DXVECTOR3 pos, Direction dir) const;

};

