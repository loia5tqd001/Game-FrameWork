#pragma once
#include "GameObject.h"
#include "Animation.h"

class VisibleObject : public GameObject
{
protected:
	FLOAT nx      ; 
	State curState;
	std::unordered_map<State, Animation> animations;

public:
	VisibleObject(State initState, Vector3 pos, Vector2 vel = { 0.0f, 0.0f }, FLOAT nx = 1.0f);

	void FlipHorizontally();
	void LowDownBody(UINT oldHeight); // recalculate position when lowing down body (height changed)

	State GetState () const override;
	UINT  GetWidth () const override;
	UINT  GetHeight() const override;

	void Update(float dt, const std::vector<GameObject*>& coObjects = {}) override {}
	void Render() const override;

	virtual void SetState(State state);
};
