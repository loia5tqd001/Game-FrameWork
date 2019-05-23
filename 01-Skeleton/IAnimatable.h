#pragma once
#include "enums.h"
#include <unordered_map>
#include "Animation.h"

class IAnimatable
{
protected:
	std::unordered_map<State, Animation> animations;
	State curState;
	Direction dir;

public:
	void SetState(State state) { curState = state; }
	void Render(const D3DXVECTOR3& pos, int alpha) const { animations.at(curState).Render(pos, dir, alpha); }}
};
