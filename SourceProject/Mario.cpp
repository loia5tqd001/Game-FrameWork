#include "pch.h"
#include "Mario.h"
#include "Collision.h"
#include "Sounds.h"
#include "Window.h"
#include "Goomba.h"

Mario::Mario(const Vector3 & spawnPos) : 
	VisibleObject(State::MarioWalking, spawnPos)
{
	animations.emplace(State::MarioIdle   , Animation(SpriteId::MarioBigIdle   , 0.1f));
	animations.emplace(State::MarioJump   , Animation(SpriteId::MarioBigWalking, 0.1f));
	animations.emplace(State::MarioWalking, Animation(SpriteId::MarioBigWalking, 0.1f));
}

void Mario::OnKeyDown(BYTE keyCode)
{
	switch (keyCode)
	{
		case VK_SPACE:
			SetState(State::MarioJump);
			break;
	}
}

void Mario::ProcessInput()
{
	static const Window& wnd = Window::Instance();

	if (wnd.IsKeyPressed(VK_LEFT)) 
	{
		nx = -std::abs(nx);
		SetState(State::MarioWalking);
	}
	else if (wnd.IsKeyPressed(VK_RIGHT)) 
	{
		nx = std::abs(nx);
		SetState(State::MarioWalking);
	}
	else {
		SetState(State::MarioIdle);
	}
}

void Mario::HandleNoCollisions(float dt)
{
	pos.x += vel.x * dt;
	pos.y += vel.y * dt;
}

void Mario::HandleCollisions(float dt, const std::vector<GameObject*>& coObjects)
{
	auto coEvents = CollisionDetector::CalcPotentialCollisions(*this, coObjects, dt);
	if (coEvents.size() == 0) 
	{
		HandleNoCollisions(dt); return;
	}

	float min_tx, min_ty, nx, ny;
	CollisionDetector::FilterCollisionEvents(coEvents, min_tx, min_ty, nx, ny);
	
	pos.x += min_tx * vel.x * dt;
	pos.y += min_ty * vel.y * dt;

	if (nx != 0.0f) vel.x = 0.0f;
	if (ny != 0.0f) vel.y = 0.0f;

	// Collision logic with Goombas
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		const CollisionEvent& e = coEvents[i];

		if (auto goomba = dynamic_cast<Goomba*>(e.pCoObj))
		{
			if (e.ny < 0.0f && goomba->GetState() != State::GoombaDie)
			{
				goomba->SetState(State::GoombaDie);
				vel.y = -JUMP_DEFLECT_SPEED;
			}
		}
	}
}

void Mario::SetState(State state)
{
	VisibleObject::SetState(state);

	switch (state)
	{
		case State::MarioWalking:
			vel.x = nx * WALKING_SPEED;
			break;

		case State::MarioJump:
			Sounds::Invoke(Action::PlayOnce, SoundId::MarioJump);
			vel.y = -JUMP_SPEED;
			break;

		case State::MarioIdle:
			vel.x = 0.0f;
			break;

		case State::MarioDie:
			break;
	}
}

void Mario::Update(float dt, const std::vector<GameObject*>& coObjects)
{
	// early checking
	if (curState == State::MarioDie) return;

	// regular updates
	vel.y += GRAVITY * dt;

	// process input
	ProcessInput();

	// handle collisions
	HandleCollisions(dt, coObjects);

	// clamping
	//Clamp(pos.x, 0.0f, float(wnd.GetWidth() - GetWidth()));

	// update animations
	animations.at(curState).Update(dt);
}
