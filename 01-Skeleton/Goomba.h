#pragma once
#include "GameObject.h"

class Goomba : public GameObject
{
public:
	bool IsActive() const override { return curState != State::GoombaDie; }
	Goomba(const D3DXVECTOR3& spawnPos);
	void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects) override;
	void SetState(State state) override;
};
