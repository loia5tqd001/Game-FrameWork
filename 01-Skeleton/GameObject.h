#pragma once


#include <vector>
#include "Animation.h"
#include "Textures.h"

enum Direction { LEFT, RIGHT };

class GameObject
{
protected: 
	D3DXVECTOR3 pos     ;
	UINT        width   ;
	UINT        height  ;
	D3DXVECTOR2 velocity;
	State      curState;

	std::vector<Animation> animations;

	GameObject(TextureType id, LPCSTR texturePath, D3DCOLOR transparentColor)
	{
		Textures::Instance().AddTexture(id, texturePath, transparentColor);
	}

public: 
	RECT GetBoundingBox() const
	{
		RECT boxCollider;
		boxCollider.left   = (UINT)pos.x - (width  / 2);
		boxCollider.top    = (UINT)pos.y - (height / 2);
		boxCollider.right  = (UINT)pos.x + (width  / 2);
		boxCollider.bottom = (UINT)pos.y + (height / 2);
	}
	D3DXVECTOR2 GetVelocity() const { return velocity; }
	void RenderBoundingBox() const; // for debug;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};

// capital pointers: only point to objects, do not call new or delete
using LPCGAMEOBJECT = const GameObject*;
//using LPGAMEOBJECT  =       GameObject*;

