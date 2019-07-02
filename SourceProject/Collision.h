#pragma once

struct CollisionEvent
{
	float t, nx, ny; // specific sweptAABB naming convention
	GameObject* pCoObj = nullptr; // pointer to object colliding with

	CollisionEvent() : t(1.0f), nx(0.0f), ny(0.0f), pCoObj(nullptr) {}
	CollisionEvent(float t, float nx, float ny, GameObject& coObj) : t(t), nx(nx), ny(ny), pCoObj(&coObj) {}

	operator bool() const { return pCoObj != nullptr; }
};

struct CollisionDetector
{
	static CollisionEvent SweptAABBEx(const GameObject& obj1, const GameObject& obj2, float dt);
	static std::vector<CollisionEvent> CalcPotentialCollisions(const GameObject& obj, const std::vector<GameObject*>& coObjs, float dt);
	static void FilterCollisionEvents(std::vector<CollisionEvent>& preFilter, float& min_tx, float& min_ty, float& nx, float&ny);
};