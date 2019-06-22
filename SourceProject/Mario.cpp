#include "pch.h"
#include "Mario.h"
#include "Collision.h"
#include "Window.h"
#include "Camera.h"

#include "Sounds.h"
#include "Texts.h"

#include "Goomba.h"

Mario::Mario(const Vector3 & spawnPos) : 
	VisibleObject(State::MarioWalking, spawnPos)
{
	animations.emplace(State::MarioIdle   , Animation(SpriteId::MarioBigIdle   , 0.1f));
	animations.emplace(State::MarioJump   , Animation(SpriteId::MarioBigWalking, 0.1f));
	animations.emplace(State::MarioWalking, Animation(SpriteId::MarioBigWalking, 0.1f));

	bboxColor = Colors::MyPoisonGreen;
}

RectF Mario::GetBBox() const
{
	return VisibleObject::GetBBox().Trim(1, 0, 1, 0);
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
	if (coEvents.size() == 0) { HandleNoCollisions(dt); return; }

	float min_tx, min_ty, nx, ny;
	CollisionDetector::FilterCollisionEvents(coEvents, min_tx, min_ty, nx, ny);

	// NOTE: HACK: not perfect handler but we're fine
	if (coEvents.size() == 0) return; // the case object's going toward the corner

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
	Utils::Clamp(pos.x, 0.0f, 624.0f);
	Utils::Clamp(pos.y, 0.0f, pos.y);

	// update animations
	animations.at(curState).Update(dt);

	// === test collision
	//static Window& wnd = Window::Instance();
	//vel.x = vel.y = 0.0f;
	//if (wnd.IsKeyPressed(VK_LEFT))
	//	vel.x -= WALKING_SPEED;
	//if (wnd.IsKeyPressed(VK_RIGHT))
	//	vel.x += WALKING_SPEED;
	//if (wnd.IsKeyPressed(VK_UP))
	//	vel.y -= WALKING_SPEED;
	//if (wnd.IsKeyPressed(VK_DOWN))
	//	vel.y += WALKING_SPEED;
	//HandleCollisions(dt, coObjects);
}

void Mario::Render() const
{
	VisibleObject::Render();

	const Vector3 drawablePos = Camera::Instance().GetPositionInViewPort( pos ) - Vector3{ 14.0f, 10.0f, 0.0f};
	Texts::DrawString("mario", drawablePos );
}
