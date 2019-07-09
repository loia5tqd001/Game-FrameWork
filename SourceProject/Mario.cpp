#include "pch.h"
#include "Mario.h"
#include "Goomba.h"

static auto& setting = Settings::Instance();

Mario::Mario(const Vector2 & spawnPos) : 
	VisibleObject(State::MarioWalking, spawnPos)
{
	animations.emplace(State::MarioIdle   , Animation(SpriteId::MarioBigIdle   , 0.1f));
	animations.emplace(State::MarioJump   , Animation(SpriteId::MarioBigWalking, 0.1f));
	animations.emplace(State::MarioWalking, Animation(SpriteId::MarioBigWalking, 0.1f));

	bboxColor = Colors::MyPoisonGreen;
}

RectF Mario::GetBBox() const
{
	return VisibleObject::GetBBox().Trim(2, 0, 2, 0);
}

void Mario::OnKeyDown(BYTE keyCode)
{
	switch (keyCode)
	{
		case VK_TAB:
			OnFlashing(false);
			break;
	}

	if (keyCode == setting.Get(KeyControls::Jump)) {
		if (_isJumping == false) {
			SetState(State::MarioJump);
			_isJumping = true;
		}
	}
}

void Mario::ProcessInput()
{
	static const Window& wnd = Window::Instance();

	if (wnd.IsKeyPressed( setting.Get(KeyControls::Left) )) 
	{
		nx = -std::abs(nx);
		SetState(State::MarioWalking);
	}
	else if (wnd.IsKeyPressed( setting.Get(KeyControls::Right) )) 
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
	_isJumping = true; //mario is falling, cant't jump
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
	if (ny != 0.0f) { vel.y = 0.0f; _isJumping = false; }

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
				OnFlashing(true);
			}
		}
	}
}

void Mario::OnFlashing(std::optional<bool> setFlashing) // NOTE: Don't use this when vsync is off
{
	static bool  isFlashing = false;
	static float timePassed;
	static UINT  nFrameUnrendered;

	if (setFlashing.has_value()) {
		isFlashing = setFlashing.value();
		timePassed = 0.0f;
		nFrameUnrendered = 0;
	}

	if (isFlashing == false) { // currently not in flashing
		shouldDrawImage = true;
	} 
	else if ((timePassed += GameTimer::Dt()) <= 1.0f) { // if in flashing, accumulate timePassed, check if still in flashing
	
		// my flashing rule: render each 1 frame per 10:
		if (++nFrameUnrendered >= 10) { 
			shouldDrawImage = true;
			nFrameUnrendered = 0;
		}
		else {
			shouldDrawImage = false;
		}
	}
	else { // after calculating timePassed, realise time to done flashing
		shouldDrawImage = true;
		timePassed = 0.0f;
		isFlashing = false;
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
			Sounds::PlayAt(SoundId::MarioJump);
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

	// update animations
	animations.at(curState).Update(dt);

	// recalculate if image should be rendered
	OnFlashing();
}

void Mario::Render() const
{
	VisibleObject::Render();

	const Vector2 drawablePos = Camera::Instance().GetPositionInViewPort( pos ) - Vector2{ 14.0f, 10.0f };
	Texts::DrawString("mario", drawablePos );
}
