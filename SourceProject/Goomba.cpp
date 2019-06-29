#include "pch.h"
#include "Goomba.h"

Goomba::Goomba(const Vector2 & spawnPos, const Vector2 & vel) :
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
	pos.Neutralize(); // HACK: fix flickering, but will cause weird behaviors in cases. NOTE: Don't call this when vsync is off, will cause lag

	Utils::Clamp(pos.x, 0.0f, 624.0f, [this]() {vel.x = -vel.x; });

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

UINT Goomba::GetHeight() const
{
	return animations.at(curState).GetFrameSize().GetHeight();
}

void Goomba::LowDownBody(UINT oldHeight)
{ 
	assert(oldHeight > GetHeight());
	pos.y += oldHeight - GetHeight(); 
}

RectF Goomba::GetBBox() const
{
	if (curState == State::GoombaDie) return {};
	return VisibleObject::GetBBox();
}
