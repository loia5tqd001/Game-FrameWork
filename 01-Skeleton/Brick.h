#pragma once
#include "GameObject.h"

class Brick : public GameObject
{
public:
	Brick(const Point& pos) :
		GameObject(State::BrickIdle, pos)
	{
		animations.emplace(State::BrickIdle, Animation(SpriteType::BrickIdle));
	}
};
