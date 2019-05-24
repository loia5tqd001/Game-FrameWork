#include "Mario.h"
#include "Collision.h"
#include "MainWindow.h"
#include "GameDev.h"


Mario::Mario() :
	GameObject(State::MarioWalking, D3DXVECTOR3(10.0f, 10.0f, 0.0f), 15, 27)
{
	animations.emplace(State::MarioIdle   , Animation(SpriteType::MarioBigIdle   , 0.1f));
	animations.emplace(State::MarioWalking, Animation(SpriteType::MarioBigWalking, 0.1f));
}

void Mario::Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects)
{
	static const MainWindow& wnd = MainWindow::Instance();

	vel.y += GRAVITY * dt;

	std::vector<CollisionEvent> coEvents;
	if (curState != State::MarioDie) {
		coEvents = CollisionDetector::CalcPotentialCollisions(*this, coObjects, dt);
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		if (wnd.IsKeyPressed(VK_LEFT))
		{
			pos.x -= WALKING_SPEED * dt;
			SetState(State::MarioWalking);
			scale.x = - std::abs(scale.x);
		}
		else if (wnd.IsKeyPressed(VK_RIGHT))
		{
			pos.x += WALKING_SPEED * dt;
			SetState(State::MarioWalking);
			scale.x = std::abs(scale.x);
		}
		else
		{
			SetState(State::MarioIdle);
		}

		if (pos.x > MainWindow::Instance().GetWidth() - GetWidth())
		{
			pos.x = float(MainWindow::Instance().GetWidth() - GetWidth());
		}
		else if (pos.x < 0.0f)
		{
			pos.x = 0.0f;
		}
	}
	else
	{
		float min_tx, nx;
		float min_ty, ny;

		auto coEventsResult = CollisionDetector::FilterCollisions(std::move(coEvents), min_tx, min_ty, nx, ny); 

		// + nx * 0.420f: need to push out a bit to avoid overlapping next frame
		pos.x += min_tx * vel.x * dt + nx * 0.420f;		
		pos.y += min_ty * vel.y * dt + ny * 0.420f;

		if (nx != 0.0f) vel.x = 0.0f;
		if (ny != 0.0f) vel.y = 0.0f;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			CollisionEvent& e = coEventsResult[i];


		}
	}
	animations.at(curState).Update(dt);
}

void Mario::SetState(State state)
{
	GameObject::SetState(state);

	switch (state)
	{
		case State::MarioWalking:
			break;

		case State::MarioJump:
			break;

		case State::MarioIdle:
			break;

		case State::MarioDie:
			break;
	}
}

