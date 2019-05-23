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
	static constexpr float GRAVITY = 2.0f;

private:
	Animation 	
		aniDie          { TextureType::Mario, SpriteType::Mario_Die         , 0.001f },
		aniBigIdle      { TextureType::Mario, SpriteType::Mario_BigIdle     , 0.001f },
		aniBigWalking   { TextureType::Mario, SpriteType::Mario_BigWalking  , 0.001f },
		aniSmallIdle    { TextureType::Mario, SpriteType::Mario_SmallIdle   , 0.001f },
		aniSmallWalking { TextureType::Mario, SpriteType::Mario_SmallWalking, 0.001f };

	Level level = Level::Big;
	Direction dir = Direction::Right;

	inline UINT GetWidth () const override { return level == Level::Small ? 13 : 15; }
	inline UINT GetHeight() const override { return level == Level::Small ? 15 : 27; }

public:
	Mario() : GameObject(State::MarioWalking) {}
	Mario(const Mario&) = delete;

	void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects) override;
	void Render(                                                     ) override;

	void SetState(State state) override;
	void SetLevel(Level l) { level = l; }

};

