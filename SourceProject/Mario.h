#pragma once
#include "VisibleObject.h"


class Mario : public VisibleObject
{
public:
	static constexpr float WALKING_SPEED      =  100.0f;
	static constexpr float JUMP_SPEED         =  400.0f;
	static constexpr float GRAVITY            = 1000.0f;
	static constexpr float JUMP_DEFLECT_SPEED =   50.0f;

private:
	void ProcessInput();
	void HandleNoCollisions(float dt);
	void HandleCollisions(float dt, const std::vector<GameObject*>& coObjects);

public:
	Mario(const Vector3 & spawnPos);

	RectF GetBBox() const override;

	void OnKeyDown(BYTE keyCode);
	void SetState(State state) override;

	void Update(float dt, const std::vector<GameObject*>& coObjects) override;
	void Render() const override;
};

