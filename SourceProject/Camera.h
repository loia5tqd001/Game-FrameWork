#pragma once

class Camera
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
	const RectF GetBBox() const;

	Vector2 GetPositionInViewPort(const Vector2& objPos) const;

private:
	Camera() = default;
	Camera(const Camera&) = delete;

public:
	static Camera& Instance();
};
