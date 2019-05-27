#include "pch.h"
#include "Mario.h"
#include "Collision.h"
#include "MainWindow.h"
#include "GameDev.h"
#include "Goomba.h"
#include "Brick.h"

static const MainWindow& wnd = MainWindow::Instance();

Mario::Mario(const D3DXVECTOR3 & spawnPos) : 
	GameObject(State::MarioWalking, spawnPos, { 0.0f, 0.0f }, 16, 27)
{
	animations.emplace(State::MarioIdle   , Animation(SpriteType::MarioBigIdle   , 0.1f));
	animations.emplace(State::MarioJump   , Animation(SpriteType::MarioBigWalking, 0.1f));
	animations.emplace(State::MarioWalking, Animation(SpriteType::MarioBigWalking, 0.1f));
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
	if (wnd.IsKeyPressed(VK_LEFT)) 
	{
		scale.x = -std::abs(scale.x);
		SetState(State::MarioWalking);
	}
	else if (wnd.IsKeyPressed(VK_RIGHT)) 
	{
		scale.x = std::abs(scale.x);
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

void Mario::HandleCollisions(float dt, const std::vector<LPCGAMEOBJECT>& coObjects)
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

		if (auto goomba = dynamic_cast<const Goomba*>(e.pCoObj))
		{
			if (e.ny > 0.0f && goomba->GetState() != State::GoombaDie)
			{
				Goomba* g = const_cast<Goomba*>(goomba);
				g->SetState(State::GoombaDie);
				vel.y = JUMP_DEFLECT_SPEED;
			}
		}
	}
}

void Mario::Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects)
{
	// early checking
	if (curState == State::MarioDie) return;

	// regular updates
	vel.y -= GRAVITY * dt;

	// process input
	ProcessInput();

	// handle collisions
	HandleCollisions(dt, coObjects);

	// clamping
	Clamp(pos.x, 0.0f, float(wnd.GetWidth() - GetWidth()));

	// update animations
	animations.at(curState).Update(dt);
}

void Mario::SetState(State state)
{
	GameObject::SetState(state);

	switch (state)
	{
		case State::MarioWalking:
			vel.x = scale.x * WALKING_SPEED;
			break;

		case State::MarioJump:
			vel.y = JUMP_SPEED;
			break;

		case State::MarioIdle:
			vel.x = 0.0f;
			break;

		case State::MarioDie:
			break;
	}
}
