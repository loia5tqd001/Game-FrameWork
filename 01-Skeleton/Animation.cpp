#include "Animation.h"
#include "Sprites.h"
#include <cassert>


Animation::Animation(States begin, States end, float holdTime)
	: holdTime(holdTime)
{
	assert(begin > States(0) && end < States::Count);
	assert(holdTime > 0.0f);

	allStates.reserve(int(end) - int(begin) - 1); // number of states will be using

	// useful states are from after 'begin' to near 'end'
	for (int i = (int)begin + 1; i < (int)end; i++)
	{
		allStates.emplace_back((States)i);
	}
}

void Animation::Advance()
{
	if (++curStateIndex >= allStates.size())
	{
		curStateIndex = 0;
	}
}

void Animation::Update(float dt)
{
	holdedTime += dt;
	while (holdedTime >= holdTime)
	{
		Advance();
		holdedTime -= holdTime;
	}
}

void Animation::Render(POINTFLOAT pos)
{
	States curState = allStates[curStateIndex];
	Sprites::Instance().GetSprite(curState).Draw(pos);
}


