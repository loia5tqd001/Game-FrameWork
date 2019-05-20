#pragma once
#include "Sprite.h"
#include <vector>

class AnimationFrame
{
private:
	const Sprite& sprite;
	const float holdTime;

public:
	AnimationFrame(const AnimationFrame&) = delete;
	AnimationFrame(const Sprite& sprite, float holdTime):
		sprite(sprite),
		holdTime(holdTime)
	{}
	float GetTime() const { return holdTime; }
};


class Animation
{
private:
	std::vector<AnimationFrame> allStates;
	unsigned int				curFrame = 0u;
	float						holdedTime = 0.0f;

public:
	Animation(States begin, States end, float holdTime);
	void SetState(States state);
	void Update(float dt);
	void Render(POINTFLOAT pos);
};


