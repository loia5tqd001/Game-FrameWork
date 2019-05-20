#pragma once
#include "States.h"
#include <vector>
#include <d3dx9.h>


class Animation
{
private:
	std::vector<States> allStates        ;
	unsigned int        curId      = 0u  ; 
	const float         holdTime         ;
	float		        holdedTime = 0.0f;

public:
	Animation(States begin, States end, float holdTime);
	void SetState(States state  );
	void Update  (float dt      );
	void Render  (POINTFLOAT pos);
};
