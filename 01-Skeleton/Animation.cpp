#include "Animation.h"
#include "Sprites.h"
#include <cassert>
#include <algorithm>


Animation::Animation(States begin, States end, float holdTime)
	: holdTime(holdTime)
{
	assert(begin > States(0) && end < States::Count);
	assert(holdTime > 0.0f);

	// reserve number of states will be pushed to std::vector
	allStates.reserve(int(end) - int(begin) - 1); 

	// useful states are on range of after 'begin' to near 'end'
	for (int i = (int)begin + 1; i < (int)end; i++)
	{
		allStates.emplace_back((States)i);
	}
}

void Animation::SetState(States state)
{
	auto it = std::find(allStates.begin(), allStates.end(), state);
	assert(it != allStates.end());
	curId = it - allStates.begin();
}

void Animation::Update(float dt)
{
	// declare inner function: advance to the next state
	static auto Advance = [this]() { if (++curId >= allStates.size()) curId = 0; }; 

	holdedTime += dt;
	while (holdedTime >= holdTime)
	{
		Advance();
		holdedTime -= holdTime;
	}
}

void Animation::Render(POINTFLOAT pos)
{
	States curState = allStates[curId];
	Sprites::Instance().GetSprite(curState).Draw(pos);
}


