#pragma once
#include "enums.h"
#include "RectF.h"
#include "Animation.h"

// CAPITAL_ALIAS pointers: only point to objects, do not call new or delete
using LPGAMEOBJECT  = class GameObject*;
using LPCGAMEOBJECT = const GameObject*;

class GameObject
{
protected: 
	D3DXVECTOR3                          pos           ; // bottom-left
	D3DXVECTOR2                          vel           ;
	UINT                                 explicitWidth ; // moving objects should define this,
	UINT                                 explicitHeight; // or GetWidth will be defined by the width of sprites 
	State                                curState      ;
	std::unordered_map<State, Animation> animations    ;
	D3DXVECTOR2                          scale         ; // direction and how much scale

public: 
	virtual bool IsCollidable() const { return true; } 
	GameObject(const GameObject&) = delete;

#if DEBUG
	bool is_debugging = false;
#endif

	const D3DXVECTOR3& GetPosition      () const { return pos     ; }
	const D3DXVECTOR2& GetVelocity      () const { return vel     ; }
	const State        GetState         () const { return curState; }
	const D3DXVECTOR2& GetScale         () const { return scale   ; }
	const UINT         GetWidth         () const;
	const UINT         GetHeight        () const;
	const RectF        GetBoundingBox   () const;
	const D3DXVECTOR3  GetDrawablePos   () const;
	void               RenderBoundingBox() const;

	virtual void SetState(const State state); 
	virtual void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects = {}) {}
	virtual void Render() const;

	virtual ~GameObject()  = default; 
	GameObject(State initState, 
		const D3DXVECTOR3& pos, 
		const D3DXVECTOR2& vel = { 0.0f, 0.0f },
		const UINT width = 0u,
		const UINT height = 0u,
		const D3DXVECTOR2& scale = { 1.0f, 1.0f })
		:
		curState(initState),
		pos(pos),
		vel(vel),
		explicitWidth(width),
		explicitHeight(height),
		scale(scale) {}

	template<typename T>
	static void Clamp(T& toClamp, T low, T high)
	{
			 assert(low  < high);
		     if (toClamp < low ) toClamp = low ;
		else if (toClamp > high) toClamp = high;
	}
};




 