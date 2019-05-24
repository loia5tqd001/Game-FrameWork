#include "Mario.h"
#include "Collision.h"
#include "MainWindow.h"
#include "GameDev.h"
#include "Goomba.h"
#include "Brick.h"

static const MainWindow& wnd = MainWindow::Instance();

Mario::Mario() :
	GameObject(State::MarioWalking, D3DXVECTOR3(10.0f, 10.0f, 0.0f), 15, 27)
{
	animations.emplace(State::MarioIdle   , Animation(SpriteType::MarioBigIdle   , 0.1f));
	animations.emplace(State::MarioWalking, Animation(SpriteType::MarioBigWalking, 0.1f));
}

void Mario::HandleInput(float dt)
{

	if (wnd.IsKeyPressed(VK_LEFT)) 
	{
		vel.x = -WALKING_SPEED;
		SetState(State::MarioWalking);
		scale.x = -std::abs(scale.x);
	}
	else if (wnd.IsKeyPressed(VK_RIGHT)) 
	{
		vel.x =  WALKING_SPEED;
		SetState(State::MarioWalking);
		scale.x = std::abs(scale.x);
	}
	else {
		SetState(State::MarioIdle);
		vel.x = 0.0f;
	}
}

void Mario::HandleNoCollisions(float dt)
{
	pos.x += vel.x * dt;
	pos.y += vel.y * dt;
}

void Mario::HandleCollisions(float dt, std::vector<CollisionEvent> coEvents)
{
	assert(coEvents.size() > 0);

	float min_tx, nx;
	float min_ty, ny;

	auto afterFilter = CollisionDetector::FilterCollisions(std::move(coEvents), min_tx, min_ty, nx, ny);

	// "+ nx*0.420f": need to push out a bit to avoid overlapping next frame
	pos.x += min_tx*vel.x*dt + nx*0.420f;
	pos.y += min_ty*vel.y*dt + ny*0.420f;

	if (nx != 0.0f) vel.x = 0.0f;
	if (ny != 0.0f) vel.y = 0.0f;



	// Collision logic with Goombas
	//for (UINT i = 0; i < afterFilter.size(); i++)
	//{
	//	const CollisionEvent& e = afterFilter[i];

	//	if (auto goomba = dynamic_cast<const Goomba*>(e.pCoObj))
	//	{
	//		// jump on top >> kill Goomba and deflect a bit 
	//		if (e.ny < 0.0f && goomba->GetState() != State::GoombaDie)
	//		{
	//			Goomba* g = (Goomba*)goomba;
	//			g->SetState(State::GoombaDie);
	//			vel.y = -JUMP_DEFLECT_SPEED;
	//		}
	//	}
	//}
}

void Mario::Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects)
{
	vel.y += GRAVITY * dt;

	HandleInput(dt);

	std::vector<CollisionEvent> coEvents;
	if (curState != State::MarioDie) {
		coEvents = CollisionDetector::CalcPotentialCollisions(*this, coObjects, dt);
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0) {
		HandleNoCollisions(dt);
	}
	else {
		HandleCollisions(dt, std::move(coEvents));
	}

	Clamp(pos.x, 0.0f, float(wnd.GetWidth() - GetWidth()));
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

