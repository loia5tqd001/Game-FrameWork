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
	void    RenderBoundingBox() const; // draw bounding box for better debugging

	virtual State GetState() const = 0;
	virtual RectF GetBBox () const = 0;

	virtual void Update(float dt, const std::vector<GameObject*>& coObjects = {}) = 0;
	virtual void Render() const = 0;

	virtual ~GameObject() = default; 
	GameObject(const GameObject&) = delete; 
	GameObject(Vector3 pos, Vector2 vel = { 0.0f, 0.0f });
	
#if DEBUG
	bool is_debugging = false; // To select which objects targeted for debugging
#endif

};




 