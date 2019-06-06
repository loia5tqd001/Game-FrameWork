#pragma once
#include "GameObject.h"

class Goomba : public GameObject
{
public:
	Goomba(const Point& spawnPos);
	void SetState(State state) override;
	bool IsCollidable() const  override { return curState != State::GoombaDie; }
	void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects) override;
};
