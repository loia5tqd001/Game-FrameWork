#pragma once
#include "Window.h"
#include "GameObject.h"

class Camera : ISingleton
{
private:
	Vector2 pos; 
	const UINT width  = Window::Instance().GetWidth (); 
	const UINT height = Window::Instance().GetHeight();

public:
	void  MoveTo(const Vector2& newPos);
	void  MoveBy(const Vector2& dist);
	void  CenterTo(const Vector2& center);

	void  ClampWithin(const RectF& theBox);

	const Vector2& GetPosition() const;
	const RectF    GetBBox    () const;

	bool    IsIntersect(const RectF& box) const;
	Vector2 GetPositionInViewPort (const Vector2& pos) const;

private:
	Camera() : ISingleton(NULL) {}

public:
	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
};
