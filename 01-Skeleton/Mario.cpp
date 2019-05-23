#include "Mario.h"
#include "Collision.h"



void Mario::Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects)
{
	vel.y += GRAVITY * dt;

	std::vector<CollisionEvent> coEvents;
	if (curState != State::MarioDie) {
		coEvents = CollisionDetector::CalcPotentialCollisions(*this, coObjects, dt);
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		pos.x += vel.x * dt;
		pos.y += vel.y * dt;
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

			//if (dynamic_cast<CGoomba *>(e->obj))
			//{
			//	CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

			//	// jump on top >> kill Goomba and deflect a bit 
			//	if (e->ny < 0)
			//	{
			//		if (goomba->GetState() != GOOMBA_STATE_DIE)
			//		{
			//			goomba->SetState(GOOMBA_STATE_DIE);
			//			vy = -MARIO_JUMP_DEFLECT_SPEED;
			//		}
			//	}
			//	else if (e->nx != 0)
			//	{
			//		/*if (untouchable==0)
			//		{
			//			if (goomba->GetState()!=GOOMBA_STATE_DIE)
			//			{
			//				if (level > MARIO_LEVEL_SMALL)
			//				{
			//					level = MARIO_LEVEL_SMALL;
			//					StartUntouchable();
			//				}
			//				else
			//					SetState(MARIO_STATE_DIE);
			//			}
			//		}*/
			//	}
			//}
		}
	}
	curAnimation->Update(dt);
}

void Mario::Render()
{
	RenderBoundingBox();

	switch (curState)
	{
		case State::MarioDie:
			aniDie.Render(pos, dir);
			break;

		case State::MarioIdle:
			if (level == Level::Big) aniBigIdle.Render(pos, dir);
			else                   aniSmallIdle.Render(pos, dir);
			break;

		case State::MarioWalking:
			if (level == Level::Big) aniBigWalking.Render(pos, dir); 
			else                   aniSmallWalking.Render(pos, dir);
			break;
	}
}

void Mario::SetState(State state)
{
	GameObject::SetState(state);

	switch (state)
	{
		case State::MarioWalking:
			curAnimation = (level == Level::Big) ? &aniBigWalking : &aniSmallWalking;
			if (dir == Direction::Right) vel.x = WALKING_SPEED;
			else                       vel.x = - WALKING_SPEED;
			break;

		case State::MarioJump:
			vel.y = - JUMP_SPEED;
			break;

		case State::MarioIdle:
			vel.x = 0.0f;
			break;

		case State::MarioDie:
			vel.y = - DIE_DEFLECT_SPEED;
			break;
	}
}

