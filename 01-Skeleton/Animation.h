#pragma once

#include "define.h"
#include <d3dx9.h>
#include <vector>


class Animation
{
private:
	static const LPD3DXSPRITE spriteHandler;

	const LPDIRECT3DTEXTURE9 pTexture   ;
	const std::vector<RECT>& frames     ;
	const float              holdTime   ;
	      float              holdingTime;
	      unsigned int       curFrame   ;

public:
	Animation(LPDIRECT3DTEXTURE9 texture, const std::vector<RECT>& frames, float holdTime);
	void Update(float dt);
	void Render(D3DXVECTOR3 pos, Direction dir) const;

};

