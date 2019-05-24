#pragma once
#include "GameObject.h"
#include "Animation.h"



class Mario : public GameObject
{
private:
	enum class Level { Small, Big };

	static constexpr float WALKING_SPEED = 100.0f;
	static constexpr float JUMP_SPEED = 5.0f;
	static constexpr float GRAVITY = 500.0f;
	static constexpr float JUMP_DEFLECT_SPEED = 0.5f;

private:
	Level level = Level::Big;

public:
	Mario(); 

	void HandleInput(float dt);
	void HandleNoCollisions(float dt);
	void HandleCollisions(float dt, std::vector<struct CollisionEvent> coEvents);
	void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects) override;
	void SetState(State state) override;
	void SetLevel(Level l) { level = l; }



};

