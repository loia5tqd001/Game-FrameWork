#pragma once
#include "GameObject.h"



class Mario : public GameObject
{
public:
	static constexpr float WALKING_SPEED      =  100.0f;
	static constexpr float JUMP_SPEED         =  400.0f;
	static constexpr float GRAVITY            = 1000.0f;
	static constexpr float JUMP_DEFLECT_SPEED =   50.0f;

private:
	enum class Level { Small, Big };

private:
	Level level = Level::Big;

public:
	Mario(const Point & spawnPos);

	void OnKeyDown(BYTE keyCode);
	void ProcessInput();
	void HandleNoCollisions(float dt);
	void HandleCollisions(float dt, const std::vector<LPCGAMEOBJECT>& coObjects);

	void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects) override;
	void SetState(State state) override;

};

