#pragma once
#include "GameObject.h"
#include "Animation.h"



#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400

#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3

#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7

#define MARIO_ANI_DIE				8

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000


class Mario : public GameObject
{
private:
	enum class Level { Small, Big };

	static constexpr float WALKING_SPEED = 1.0f;
	static constexpr float JUMP_SPEED = 5.0f;
	static constexpr float DIE_DEFLECT_SPEED = 5.0f;
	static constexpr float GRAVITY = 0.9f;

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

