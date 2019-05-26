#pragma once
#include "GameObject.h"
#include "Animation.h"



class Mario : public GameObject
{
public:
	static constexpr float WALKING_SPEED      = 100.0f;
	static constexpr float JUMP_SPEED         = 200.0f;
	static constexpr float GRAVITY            = 500.0f;
	static constexpr float JUMP_DEFLECT_SPEED =   0.5f;

private:
	enum class Level { Small, Big };

private:
	Level level = Level::Big;

public:
	Mario(); 

	void OnKeyDown(BYTE keyCode);
	void ProcessInput();
	void HandleNoCollisions(float dt);
	void HandleCollisions(float dt, const std::vector<LPCGAMEOBJECT>& coObjects);

	void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects) override;
	void SetState(State state) override;

};

