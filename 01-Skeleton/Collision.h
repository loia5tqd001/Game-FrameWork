#pragma once
#include "GameObject.h"

struct CollisionEvent
{
	const float	      t  ;
	const float	      nx ; // specific 'swept aabb' naming convention
	const float	      ny ; 
	const GameObject& obj; // object to collide with

	// to force move semantics
	CollisionEvent(const CollisionEvent&)     = delete;
	CollisionEvent(CollisionEvent&&) noexcept = default; 

	CollisionEvent() noexcept : 
		t(1.0f), nx(0.0f), ny(0.0f), obj(nullptr) {}

	CollisionEvent(float t, float nx, float ny, const GameOjbect& obj) :
		t(t), nx(nx), ny(ny), obj(obj) {}

	operator bool() const { return obj == nullptr; }
};


struct CollisionDetector
{
	static RECT GetBroadPhaseBox(const RECT& rect, float dx, float dy);
	static CollisionEvent SweptAABBEx(const GameObject& obj1, const GameObject& obj2, float dt);
	static std::vector<CollisionEvent> CalcPotentialCollisions(const GameObject& obj, const std::vector<LPGAMEOBJECT>& coObjs, float dt);
	static std::vector<CollisionEvent> FilterCollisions(std::vector<CollisionEvent>&& preFilter, float& min_tx, float& min_ty, float& nx, float&ny);
};