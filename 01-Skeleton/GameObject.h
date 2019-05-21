#pragma once

#include "define.h"
#include <vector>
#include <d3dx9.h>

// capital pointers: only point to objects, do not call new or delete
using LPCGAMEOBJECT = const class GameObject*;

class GameObject
{
protected: 
	D3DXVECTOR3 pos     ; // center of bounding box
	D3DXVECTOR2 vel     ;
	State       curState;

	inline virtual UINT GetWidth  () const = 0;
	inline virtual UINT GetHeight () const = 0;

public: 
	const D3DXVECTOR3& GetPosition   () const { return pos     ; }
	const D3DXVECTOR2& GetVelocity   () const { return vel     ; }
	State              GetState      () const { return curState; }
	RECT               GetBoundingBox() const;

	virtual void SetPosition(const D3DXVECTOR3& pos) { this->pos  = pos; }
	virtual void SetVelocity(const D3DXVECTOR2& vel) { this->vel  = vel; }
	virtual void SetState   (State            state) { curState = state; }

	virtual void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects) = 0;
	virtual void Render(                                                     ) = 0;

	GameObject(const D3DXVECTOR3& pos, const D3DXVECTOR2& vel, State state) : pos(pos), vel(vel), curState(state) {}
	GameObject(State initState, const D3DXVECTOR3& pos = {0.0f, 0.0f, 0.0f}, const D3DXVECTOR2& vel = {0.0f, 0.0f})
		: GameObject(pos, vel, initState) {}
	virtual ~GameObject() = default;

	// == for debuging == //
	void RenderBoundingBox() const; 
};




 