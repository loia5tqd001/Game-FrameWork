#pragma once
#include "enums.h"
#include "Animation.h"
#include <vector>
#include <d3dx9.h>
#include <assert.h>
#include <unordered_map>

// CAPITAL_ALIAS pointers: only point to objects, do not call new or delete
using LPGAMEOBJECT  = class GameObject*;
using LPCGAMEOBJECT = const GameObject*;

class GameObject
{
protected: 
	D3DXVECTOR3                          pos       ; // top-left
	UINT                                 width     ;
	UINT                                 height    ;
	D3DXVECTOR2                          vel       ;
	State                                curState  ;
	std::unordered_map<State, Animation> animations;
	D3DXVECTOR2                          scale     ; // direction and how much scale

	virtual bool IsCollidable() const { return true; } 
	GameObject(const GameObject&) = delete;

public: 

#if DEBUG
	bool is_debugging = false;
#endif

	const D3DXVECTOR3& GetPosition      () const { return pos                             ; }
	const UINT         GetWidth         () const { return UINT(width  * std::abs(scale.x)); }
	const UINT         GetHeight        () const { return UINT(height * std::abs(scale.y)); }
	const D3DXVECTOR2& GetVelocity      () const { return vel                             ; }
	const State        GetState         () const { return curState                        ; }
	const D3DXVECTOR2& GetScale         () const { return scale                           ; }
	const RectF        GetBoundingBox   () const;
	void               RenderBoundingBox() const;

	virtual void SetPosition(const D3DXVECTOR3& pos  ) { this->pos   = pos  ; }
	virtual void SetVelocity(const D3DXVECTOR2& vel  ) { this->vel   = vel  ; }
	virtual void SetState   (const State        state) { curState    = state; }
	virtual void SetScale   (const D3DXVECTOR2& scale) { this->scale = scale; }

	virtual void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects) {}
	virtual void Render() const;

	virtual ~GameObject()  = default; 
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

	template<typename T>
	void Clamp(T& toClamp, T low, T high)
	{
			 assert(low  < high);
		     if (toClamp < low ) toClamp = low ;
		else if (toClamp > high) toClamp = high;
	}
};




 