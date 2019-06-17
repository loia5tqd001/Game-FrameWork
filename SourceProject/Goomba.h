#pragma once
#include "VisibleObject.h"

class Goomba : public VisibleObject
{
public:
	Goomba(const Vector3& spawnPos, const Vector2& vel);

	void SetState(State state) override;
	UINT GetWidth() const override;

	void Update(float dt, const std::vector<GameObject*>& coObjects) override;
};
