#pragma once
#include "enums.h"

class GameObject
{
protected: 
	Vector3 pos; 
	Vector2 vel;
	D3DCOLOR bboxColor;

public: 
	Vector2 GetVelocity      () const;
	RectF   GetBoundingBox   () const;
	void    RenderBoundingBox() const; // draw bounding box for better debugging

	virtual State GetState   () const = 0;
	virtual UINT  GetWidth   () const = 0;
	virtual UINT  GetHeight  () const = 0;

	virtual void Update(float dt, const std::vector<GameObject*>& coObjects = {}) = 0;
	virtual void Render() const = 0;

	virtual ~GameObject() = default; 
	GameObject(const GameObject&) = delete; 
	GameObject(Vector3 pos, Vector2 vel = { 0.0f, 0.0f });


	//== Utils: ==

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
	bool is_debugging = false; // To select which objects targeted for debugging
#endif

};




 