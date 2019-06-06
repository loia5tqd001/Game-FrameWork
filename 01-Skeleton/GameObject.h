#pragma once
#include "enums.h"
#include "Animation.h"

// CAPITAL_ALIAS pointers: only point to objects, do not call new or delete
using LPGAMEOBJECT  = class GameObject*;
using LPCGAMEOBJECT = const GameObject*;

class GameObject
{
protected: 
	Point   pos           ; 
	Vector2 vel           ;
	UINT    explicitWidth ; // moving objects should define this, or GetWidth() will be defined by the width of sprites 
	UINT    explicitHeight; 
	State   curState      ;
	Vector2 scale         ; // direction and how much scale
	std::unordered_map<State, Animation> animations;

public: 
	virtual bool IsCollidable() const { return true; } 
	GameObject(const GameObject&) = delete;

#if DEBUG
	bool is_debugging = false;
#endif

	const Point&   GetPosition      () const { return pos     ; }
	const Vector2& GetVelocity      () const { return vel     ; }
	const State    GetState         () const { return curState; }
	const Vector2& GetScale         () const { return scale   ; }
	const Point    GetCenter        () const;
	const UINT     GetWidth         () const;
	const UINT     GetHeight        () const;
	const RectF    GetBoundingBox   () const;
	const Point    GetDrawablePos   () const;
	void           RenderBoundingBox() const;

	void LowDownBody(UINT oldHeight)
	{
		pos.y += oldHeight - GetHeight();
	}

	virtual void SetState(State state); 

	virtual void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects = {}) {}
	virtual void Render() const;
	virtual ~GameObject() = default; 

	GameObject(State initState, 
		const Point& pos, 
		const Vector2& vel = { 0.0f, 0.0f },
		const UINT width = 0u,
		const UINT height = 0u,
		const Vector2& scale = { 1.0f, 1.0f })
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




 