#pragma once
#include "MainWindow.h"
#include "GameObject.h"

class Camera : ISingleton
{
private:
	D3DXVECTOR3 pos   = { 0.0f, 0.0f, 0.0f }; // bottom-left
	const UINT width  = MainWindow::Instance().GetWidth (); // what if full screen
	const UINT height = MainWindow::Instance().GetHeight();

public:
	void  MoveTo(const D3DXVECTOR3& newPos)  { pos = newPos                     ; }
	void  MoveBy(float dx, float dy)         { pos += { dx, dy, 0.0f }          ; }
	const D3DXVECTOR3& GetPosition()  const  { return pos                       ; }
	const UINT         GetWidth   ()  const  { return width                     ; }
	const UINT         GetHeight  ()  const  { return height                    ; }
	const RectF        GetBBox    ()  const  ;
	bool  IsContain(const RectF& box) const  { return GetBBox().IsIntersect(box); }
	D3DXVECTOR3 GetDrawablePosition  (const  GameObject& obj) const;

private:
	Camera() : ISingleton(NULL) {}

public:
	static Camera& Instance()
	{
		static Camera instance;
		return instance;
	}
};
