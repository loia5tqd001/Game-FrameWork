#include "Collision.h"
#include <algorithm>
#include <limits.h>

RECT CollisionDetector::GetBroadPhaseBox(const RECT & rect, float dx, float dy)
{
	RECT broadPhaseRect;
	broadPhaseRect.left   = min(rect.left  , rect.left   + dx);
	broadPhaseRect.top    = min(rect.top   , rect.top    + dy);
	broadPhaseRect.right  = max(rect.right , rect.right  + dx);
	broadPhaseRect.bottom = max(rect.bottom, rect.bottom + dy);
	return broadPhaseRect;
}

/// Resource: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/
/// Note: it's reported to have bugs in cases, but we'll fine so who cares
CollisionEvent CollisionDetector::SweptAABBEx(const GameObject & obj1, const GameObject & obj2, float dt)
{
	const auto v1 = obj1.GetVelocity();
	const auto v2 = obj2.GetVelocity();

	// relative motion distance this frame = relative velocity times dt(denta-time this frame)
	const float dx = (v1.x - v2.x) * dt; 
	const float dy = (v1.y - v2.y) * dt;

	// if two objects are moving relatively along together, obviously no collisions
	if (dx == 0.0f && dy == 0.0f) return CollisionEvent(); 

	const RECT rect1 = obj1.GetBoundingBox();
	const RECT rect2 = obj2.GetBoundingBox();

	// board phasing
	if (IntersectRect(nullptr, &GetBroadPhaseBox(rect1, dx, dy) , &rect2)) return CollisionEvent(); 

	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;
	if (dx > 0.0f)
	{
		xInvEntry = rect2.left - rect1.right;
		xInvExit = rect2.right - rect1.left;
	}
	else
	{
		xInvEntry = rect2.right - rect1.left;
		xInvExit = rect2.left - rect1.right;
	}
	if (dy > 0.0f)
	{
		yInvEntry = rect2.top - rect1.bottom;
		yInvExit = rect2.bottom - rect1.top;
	}
	else
	{
		yInvEntry = rect2.bottom - rect1.top;
		yInvExit = rect2.top - rect1.bottom;
	}


	float xEntry, yEntry;
	float xExit, yExit;
	if (dx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / dx;
		xExit = xInvExit / dx;
	}

	if (dy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / dy;
		yExit = yInvExit / dy;
	}

	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);
	float normalx;
	float normaly;

	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
	{
		return CollisionEvent();
	}

	if (xEntry > yEntry)
	{
		if (xInvEntry < 0.0f)
		{
			normalx = 1.0f;
			normaly = 0.0f;
		}
		else
		{
			normalx = -1.0f;
			normaly = 0.0f;
		}
	}
	else
	{
		if (yInvEntry < 0.0f)
		{
			normalx = 0.0f;
			normaly = 1.0f;
		}
		else
		{
			normalx = 0.0f;
			normaly = -1.0f;
		}
	}

	return { entryTime, normalx, normaly, &obj2 };
	
}

std::vector<CollisionEvent> CollisionDetector::CalcPotentialCollisions(const GameObject & obj, const std::vector<LPGAMEOBJECT>& coObjs, float dt)
{
	std::vector<CollisionEvent> potentialCollisions;

	for (int i = 0; i < coObjs.size(); i++)
	{
		CollisionEvent e = SweptAABBEx(obj, *coObjs.at(i), dt);
		if (e) potentialCollisions.emplace_back(std::move(e));
	}
	return potentialCollisions;
}

std::vector<CollisionEvent> CollisionDetector::FilterCollisions(std::vector<CollisionEvent>&& preFilter, float & min_tx, float & min_ty, float & nx, float & ny)
{
	// This function is being called tremendously, so there will be optimization, and yet be hard to understand //

	assert(preFilter.size() > 0);

	std::vector<CollisionEvent> afterFilter;
	min_tx = min_ty = 1.0f;
	nx     = ny     = 0.0f;

	std::sort(preFilter.begin(), preFilter.end(), [](auto a, auto b) { return a->t < b->t; });
	bool usefulEventThisLoop; // declare here to avoid constantly initializing inside the loop
	for (int i = 0; i < preFilter.size(); i++)
	{
		CollisionEvent& event = preFilter[i];
		usefulEventThisLoop = false;

		// if afterFilter hasn't got min_tx yet, and this event is fit
		if (nx != 0.0f && event.nx != 0.0f) 
		{
			nx = event.nx;
			min_tx = event.t;
			usefulEventThisLoop = true;
		}

		// if afterFilter hasn't got min_ty yet, and this event is fit
		if (ny != 0.0f && event.ny != 0.0f)
		{
			ny = event.ny;
			min_ty = event.t;
			usefulEventThisLoop = true;
		}

		if (usefulEventThisLoop)
		{
			afterFilter.emplace_back(std::move(event)); // move semantics (rvalue casting)
		}

		// if min time collisions in two axis are both collected, move on
		if (nx != 0.0f && ny != 0.0f) break; 
	}

	return afterFilter;

	/// DebugOut min_tx, min_ty,.. if weird things happen
}
