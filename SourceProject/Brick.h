#pragma once
#include "VisibleObject.h"

class Brick : public VisibleObject
{
public:
	Brick(const Vector3& pos) :
		VisibleObject(State::BrickIdle, pos)
	{
		animations.emplace(State::BrickIdle, Animation(SpriteType::BrickIdle));
	}
};
