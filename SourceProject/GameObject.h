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
	State   curState      ;
	Vector2 scale         ; // direction and how much scale
	std::unordered_map<State, Animation> animations;

	UINT explicitWidth  = 0; // for objects don't use sprite to determine width-height
	UINT explicitHeight = 0; // i.e spawner: is invisible but does have width n height to check collision

private:
	const Point    GetDrawablePos   () const;
	void           RenderBoundingBox() const;

public: 
	const Point&   GetPosition      () const { return pos     ; }
	const Vector2& GetVelocity      () const { return vel     ; }
	const State    GetState         () const { return curState; }
	const Vector2& GetScale         () const { return scale   ; }
	const Point    GetCenter        () const;
	const UINT     GetWidth         () const;
	const UINT     GetHeight        () const;
	const RectF    GetBoundingBox   () const;

	void LowDownBody(UINT oldHeight);
	void SetWidthHeight(UINT w, UINT h);

	virtual bool IsCollidable() const { return true; } 
	virtual void SetState(State state); 

	virtual void Update(float dt, const std::vector<LPCGAMEOBJECT>& coObjects = {}) {}
	virtual void Render() const;

	virtual ~GameObject() = default; 
	GameObject(const GameObject&) = delete; 
	GameObject(State initState, const Point& pos, const Vector2& vel = { 0.0f, 0.0f }, const Vector2& scale = { 1.0f, 1.0f });

	template<typename T>
	static void Clamp(T& toClamp, T low, T high)
	{
			 assert(low  < high);
		     if (toClamp < low ) toClamp = low ;
		else if (toClamp > high) toClamp = high;
	}

	template<typename T, typename Functor>
	static void Clamp(T& toClamp, T low, T high, Functor action)
	{
			 assert(low  < high);
		     if (toClamp < low ) toClamp = low , action();
		else if (toClamp > high) toClamp = high, action();
	}

#if DEBUG
	bool is_debugging = false;
#endif
};




 