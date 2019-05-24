#pragma once
#include "GameObject.h"
#include "Animation.h"



class Mario : public GameObject
{
private:
	enum class Level { Small, Big };

	static constexpr float WALKING_SPEED = 100.0f;
	static constexpr float JUMP_SPEED = 5.0f;
	static constexpr float DIE_DEFLECT_SPEED = 5.0f;
	static constexpr float GRAVITY = 0.0f;

private:
	Level level = Level::Big;
	bool IsActive () const override { return true; }

public:
	Mario(); 
	Mario(const Mario&) = delete;

	void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects) override;

	void SetState(State state) override;
	void SetLevel(Level l) { level = l; }

};

