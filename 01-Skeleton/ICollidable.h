#pragma once
#include <d3dx9.h>

using LPCCOLLIABLE = const class IColliable*;

struct CollisionEvent
{
	float	     t      = 1.0f   ;
	float	     nx     = 0.0f   ; // specific 'swept aabb' naming convention
	float	     ny     = 0.0f   ;
	LPCCOLLIABLE pCoObj = nullptr; // pointer to object collide with

	CollisionEvent() = default;
	CollisionEvent(float t, float nx, float ny, const IColliable& coObj) : t(t), nx(nx), ny(ny), pCoObj(&coObj) {}
	operator bool() const { return pCoObj != nullptr; }
};

class IColliable
{
protected:
	D3DXVECTOR2 vel   ;
	UINT        width ;
	UINT        height;

public:	
	const D3DXVECTOR2& GetVelocity() const { return vel; }
	void SetVelocity(const D3DXVECTOR2& vel) { this->vel = vel; }
	
	virtual const D3DXVECTOR3& GetPos   () const = 0;
	virtual const UINT         GetWidth () const { return width ;}
	virtual const UINT         GetHeight() const { return height;}

	RECT GetBoundingBox() const;
	void RenderBoundingBox() const; // for debuging
};

struct CollisionDetector
{
	static RECT GetBroadPhaseBox(const RECT& rect, float dx, float dy);
	static CollisionEvent SweptAABBEx(const IColliable& obj1, const IColliable& obj2, float dt);
	static std::vector<CollisionEvent> CalcPotentialCollisions(const IColliable& obj, const std::vector<LPCCOLLIABLE>& coObjs, float dt);
	static std::vector<CollisionEvent> FilterCollisions(std::vector<CollisionEvent> preFilter, float& min_tx, float& min_ty, float& nx, float&ny);
};

