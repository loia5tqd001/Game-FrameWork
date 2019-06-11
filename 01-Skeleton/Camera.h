#pragma once
#include "Window.h"
#include "GameObject.h"

class Camera : ISingleton
{
private:
	Point pos; 
	const UINT width  = Window::Instance().GetWidth (); 
	const UINT height = Window::Instance().GetHeight();

public:
	void  MoveTo(const Point& newPos);
	void  MoveBy(const Distance& dist);
	void  CenterTo(const Point& center);

	const Point& GetPosition() const;
	const RectF  GetBBox    () const;

	bool  IsIntersect(const RectF& box) const;
	Point GetPositionInViewPort (const Point& pos) const;

private:
	Camera() : ISingleton(NULL) {}

public:
	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
};
