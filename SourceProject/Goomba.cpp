#include "pch.h"
#include "Goomba.h"

Goomba::Goomba(const Vector3 & spawnPos, const Vector2 & vel) :
	VisibleObject(State::GoombaMoving, spawnPos, vel)
{
	animations.emplace(State::GoombaMoving, Animation(SpriteId::GoombaMoving, 0.1f));
	animations.emplace(State::GoombaDie   , Animation(SpriteId::GoombaDie   , 0.1f));
}

void Goomba::Update(float dt, const std::vector<GameObject*>& coObjects)
{
	if (curState == State::GoombaDie || curState == State::Destroyed) return;

	pos.x += vel.x * dt;
	pos.y += vel.y * dt;

	Clamp(pos.x, 0.0f, 624.0f, [this]() {vel.x = -vel.x; });

	animations.at(curState).Update(dt);
}

void Goomba::SetState(State state)
{
	const auto oldHeight = GetHeight();

	VisibleObject::SetState(state);

	switch (state)
	{
		case State::GoombaDie:
			LowDownBody(oldHeight);
			vel.x = 0.0f;
			break;
	}
}

UINT Goomba::GetWidth() const
{
	if (curState == State::GoombaDie) return 0;
	return VisibleObject::GetWidth();
}
