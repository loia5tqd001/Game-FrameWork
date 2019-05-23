#pragma once

#include "enums.h"
#include "Animation.h"
#include <vector>
#include <d3dx9.h>
#include <unordered_map>

// CAPITAL_ALIAS pointers: only point to objects, do not call new or delete
using LPCGAMEOBJECT = const class GameObject*;

class GameObject
{
protected: 
	D3DXVECTOR3                          pos       ; // top-left
	CONST UINT                           width     ;
	CONST UINT                           height    ;
	D3DXVECTOR2                          vel       ;
	State                                curState  ;
	std::unordered_map<State, Animation> animations;
	D3DXVECTOR2                          scale     ; // direction and how much scale

	virtual ~GameObject()  = default; 
	virtual bool IsActive() const = 0;

public: 
	const D3DXVECTOR3& GetPosition      () const { return pos                   ; }
	const UINT         GetWidth         () const { return UINT(width  * scale.x); }
	const UINT         GetHeight        () const { return UINT(height * scale.y); }
	const D3DXVECTOR2& GetVelocity      () const { return vel                   ; }
	const State        GetState         () const { return curState              ; }
	const D3DXVECTOR2& GetScale         () const { return scale                 ; }
	const RECT         GetBoundingBox   () const;
	void               RenderBoundingBox() const;

	virtual void SetPosition(const D3DXVECTOR3& pos  ) { this->pos   = pos  ; }
	virtual void SetVelocity(const D3DXVECTOR2& vel  ) { this->vel   = vel  ; }
	virtual void SetState   (State              state) { curState    = state; }
	virtual void SetScale   (const D3DXVECTOR2& scale) { this->scale = scale; }

	virtual void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects) = 0;
	virtual void Render() const;

	GameObject(State initState, 
		const D3DXVECTOR3& pos, 
		const UINT width,
		const UINT height,
		const D3DXVECTOR2& vel = { 0.0f, 0.0f },
		const D3DXVECTOR2& scale = { 1.0f, 1.0f })
		:
		curState(initState),
		pos(pos),
		width(width),
		height(height),
		vel(vel),
		scale(scale) {}
};




 