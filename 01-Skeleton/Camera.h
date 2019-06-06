#pragma once
#include "MainWindow.h"
#include "GameObject.h"

class Camera : ISingleton
{
private:
	Point pos; 
	const UINT width  = MainWindow::Instance().GetWidth (); 
	const UINT height = MainWindow::Instance().GetHeight();

public:
	void  MoveTo(const Point& newPos);
	void  MoveBy(const Distance& dist);
	void  CenterTo(const Point& center);

	const Point& GetPosition() const;
	const RectF  GetBBox    () const;

	bool  IsIntersect(const RectF& box) const;

	Point GetPositionInViewPort (const GameObject& obj) const;
	//Point WorldRectToDrawablePosition(const RectF& rect) const;

private:
	Camera() : ISingleton(NULL) {}

public:
	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
};
