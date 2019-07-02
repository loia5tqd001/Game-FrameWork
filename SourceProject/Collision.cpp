#include "pch.h"

/// Resource: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/
CollisionEvent CollisionDetector::SweptAABBEx(const GameObject & obj1, const GameObject & obj2, float dt)
{
	const auto v1 = obj1.GetVelocity();
	const auto v2 = obj2.GetVelocity();	
	if (v1 == v2) return {}; // if two objects'r moving along together, obviously no collisions

	const RectF rect1 = obj1.GetBBox();
	const RectF rect2 = obj2.GetBBox();

	// relative motion this frame = relative velocity times dt(denta-time this frame)
	const float dx = (v1.x - v2.x) * dt; 
	const float dy = (v1.y - v2.y) * dt;
	if (!rect1.GetBroadPhase(dx, dy).IsIntersect(rect2)) return {}; 

	float dxEntry, dxExit;
	float dyEntry, dyExit;
	if (dx > 0.0f) {
		dxEntry = rect2.left   - rect1.right ;
		dxExit  = rect2.right  - rect1.left  ;
	} else {				   
		dxEntry = rect2.right  - rect1.left  ;
		dxExit  = rect2.left   - rect1.right ;
	}
	if (dy > 0.0f) {
		dyEntry = rect2.top    - rect1.bottom;
		dyExit  = rect2.bottom - rect1.top   ;
	} else {
		dyEntry = rect2.bottom - rect1.top   ;
		dyExit  = rect2.top    - rect1.bottom;
	}

	float txEntry, txExit;
	float tyEntry, tyExit;
	if (dx == 0.0f) {
		txEntry = -std::numeric_limits<float>::infinity();
		txExit  =  std::numeric_limits<float>::infinity();
	} else {
		txEntry = dxEntry / dx;
		txExit  = dxExit  / dx;
	}
	if (dy == 0.0f) {
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit  =  std::numeric_limits<float>::infinity();
	} else {
		tyEntry = dyEntry / dy;
		tyExit  = dyExit  / dy;
	}

	const float entryTime = max(txEntry, tyEntry);
	const float exitTime  = min(txExit , tyExit );

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f) return {};

	float nx = 0.0f, ny = 0.0f;
	if ( !(txEntry == 0.0f && tyEntry == 0.0f) ) // both tEntry = 0 means object's going toward the corner
	{
		if (txEntry > tyEntry) {
			ny = 0.0f;
			nx = dx < 0.0f ? 1.0f : -1.0f; 
		} else {
			nx = 0.0f;
			ny = dy < 0.0f ? 1.0f : -1.0f;
		}
	}

	return { entryTime, nx, ny, const_cast<GameObject&>(obj2) };	
}

std::vector<CollisionEvent> CollisionDetector::CalcPotentialCollisions(const GameObject & obj, const std::vector<GameObject*>& coObjs, float dt)
{
	std::vector<CollisionEvent> potentialCollisions;

	for (UINT i = 0; i < coObjs.size(); i++)
	{
		CollisionEvent e = SweptAABBEx(obj, *coObjs.at(i), dt);
		if (e) potentialCollisions.emplace_back(std::move(e));
	}
	return potentialCollisions;
}

void CollisionDetector::FilterCollisionEvents(std::vector<CollisionEvent>& coEvents, float & min_tx, float & min_ty, float & nx, float & ny)
{
	assert(coEvents.size() > 0);

	std::vector<CollisionEvent> afterFilter;
	min_tx = min_ty = 1.0f;
	nx     = ny     = 0.0f;

	std::sort(coEvents.begin(), coEvents.end(), [](auto a, auto b) { return a.t < b.t; });
	bool usefulEventThisLoop; // declare here to avoid constantly initializing inside the loop
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		CollisionEvent& event = coEvents[i];
		usefulEventThisLoop = false;

		// if afterFilter hasn't got min_tx yet, and this event is fit
		if (nx == 0.0f && event.nx != 0.0f) 
		{
			nx     = event.nx;
			min_tx = event.t ;
			usefulEventThisLoop = true;
		}

		// if afterFilter hasn't got min_ty yet, and this event is fit
		if (ny == 0.0f && event.ny != 0.0f)
		{
			ny     = event.ny;
			min_ty = event.t ;
			usefulEventThisLoop = true;
		}

		if (usefulEventThisLoop)
		{
			afterFilter.emplace_back(std::move(event));
		}

		// if min time collisions in two axis are both collected, move on
		if (nx != 0.0f && ny != 0.0f) break; 
	}

	coEvents = std::move(afterFilter);
}
