#include "ICollidable.h"
#include "Textures.h"
#include "GameDev.h"
#include <algorithm>

RECT IColliable::GetBoundingBox() const
{
	const LONG left = (LONG)GetPos().x;
	const LONG top  = (LONG)GetPos().y;
	const LONG right  = left + GetWidth();
	const LONG bottom = top + GetHeight();
	return { left, top, right, bottom };
}

void IColliable::RenderBoundingBox() const
{
	LPDIRECT3DTEXTURE9 bbox = Textures::Instance().GetTexture(TextureType::Bbox);
	GameDev::Instance().Draw(GetPos(), bbox, GetBoundingBox());
}

RECT CollisionDetector::GetBroadPhaseBox(const RECT & rect, float dx, float dy)
{
	RECT broadPhaseBox;
	broadPhaseBox.left   = min(rect.left  , rect.left   + (LONG)dx);
	broadPhaseBox.top    = min(rect.top   , rect.top    + (LONG)dy);
	broadPhaseBox.right  = max(rect.right , rect.right  + (LONG)dx);
	broadPhaseBox.bottom = max(rect.bottom, rect.bottom + (LONG)dy);
	return broadPhaseBox;
}

/// Resource: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/
/// Note: it's reported to have bugs in cases, but we'll fine so who cares
CollisionEvent CollisionDetector::SweptAABBEx(const IColliable & obj1, const IColliable & obj2, float dt)
{
	const auto v1 = obj1.GetVelocity();
	const auto v2 = obj2.GetVelocity();

	// if two objects moving relatively along together, obviously no collisions
	if (v1 == v2) return {};

	// relative motion this frame = relative velocity times dt(denta-time this frame)
	const float dx = (v1.x - v2.x) * dt; 
	const float dy = (v1.y - v2.y) * dt;

	const RECT rect1 = obj1.GetBoundingBox();
	const RECT rect2 = obj2.GetBoundingBox();
	// board phasing
	if (!IntersectRect(nullptr, &GetBroadPhaseBox(rect1, dx, dy) , &rect2)) return {}; 

	LONG dxEntry, dxExit;
	LONG dyEntry, dyExit;
	if (dx > 0.0f) {
		dxEntry = rect2.left  - rect1.right;
		dxExit  = rect2.right - rect1.left ;
	} else {
		dxEntry = rect2.right - rect1.left ;
		dxExit  = rect2.left  - rect1.right;
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
		txEntry = (float)dxEntry / dx;
		txExit  = (float)dxExit  / dx;
	}
	if (dy == 0.0f) {
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit  =  std::numeric_limits<float>::infinity();
	} else {
		tyEntry = dyEntry / dy;
		tyExit  = dyExit  / dy;
	}

	float entryTime = max(txEntry, tyEntry);
	float exitTime  = min(txExit , tyExit );
	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f) return {};

	float nx, ny;
	if (txEntry > tyEntry) {
		ny = 0.0f;
		nx = dxEntry < 0.0f ? 1.0f : -1.0f;
	} else {
		nx = 0.0f;
		ny = dyEntry < 0.0f ? 1.0f : -1.0f;
	}

	return { entryTime, nx, ny, obj2 };	
}

std::vector<CollisionEvent> CollisionDetector::CalcPotentialCollisions(const IColliable & obj, const std::vector<LPCCOLLIABLE>& coObjs, float dt)
{
	std::vector<CollisionEvent> potentialCollisions;

	for (UINT i = 0; i < coObjs.size(); i++)
	{
		CollisionEvent e = SweptAABBEx(obj, *coObjs.at(i), dt);
		if (e) potentialCollisions.emplace_back(std::move(e));
	}
	return potentialCollisions;
}

std::vector<CollisionEvent> CollisionDetector::FilterCollisions(std::vector<CollisionEvent> preFilter, float & min_tx, float & min_ty, float & nx, float & ny)
{
	// This function is being called tremendously, so there will be optimization, and yet to be hard to understand //

	assert(preFilter.size() > 0);

	std::vector<CollisionEvent> afterFilter;
	min_tx = min_ty = 1.0f;
	nx     = ny     = 0.0f;

	std::sort(preFilter.begin(), preFilter.end(), [](auto a, auto b) { return a.t < b.t; });
	bool usefulEventThisLoop; // declare here to avoid constantly initializing inside the loop
	for (UINT i = 0; i < preFilter.size(); i++)
	{
		CollisionEvent& event = preFilter[i];
		usefulEventThisLoop = false;

		// if afterFilter hasn't got min_tx yet, and this event is fit
		if (nx != 0.0f && event.nx != 0.0f) 
		{
			nx     = event.nx;
			min_tx = event.t ;
			usefulEventThisLoop = true;
		}

		// if afterFilter hasn't got min_ty yet, and this event is fit
		if (ny != 0.0f && event.ny != 0.0f)
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

	return afterFilter;

	/// DebugOut min_tx, min_ty,.. if weird things happen
}
