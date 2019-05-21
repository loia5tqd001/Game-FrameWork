#pragma once
#include "GameObject.h"
#include <optional>

struct CollisionEvent
{
	float	      t  ;
	float	      nx ; // specific 'swept aabb' naming convention
	float	      ny ; 
	LPCGAMEOBJECT obj; // object to collide with

	CollisionEvent& operator=(const CollisionEvent&) = default;
	CollisionEvent(const CollisionEvent&)     = default; 
	CollisionEvent(CollisionEvent&&) noexcept = default; // to force move semantics	

	CollisionEvent(float t, float nx, float ny, const GameObject& obj) :
		t(t), nx(nx), ny(ny), obj(&obj) {}

	operator bool() const { return obj != nullptr; }
};


struct CollisionDetector
{
	static RECT GetBroadPhaseBox(const RECT& rect, float dx, float dy);
	static std::optional<CollisionEvent> SweptAABBEx(const GameObject& obj1, const GameObject& obj2, float dt);
	static std::vector<CollisionEvent> CalcPotentialCollisions(const GameObject& obj, const std::vector<LPCGAMEOBJECT>& coObjs, float dt);
	static std::vector<CollisionEvent> FilterCollisions(std::vector<CollisionEvent> preFilter, float& min_tx, float& min_ty, float& nx, float&ny);
};