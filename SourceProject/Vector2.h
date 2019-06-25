#pragma once


struct Vector2 : public D3DXVECTOR2
{
	template<typename T>
	Vector2(T x, T y) : D3DXVECTOR2((float)x, (float)y) 
	{}
	Vector2() : D3DXVECTOR2(0.0f, 0.0f) 
	{}

	D3DXVECTOR3 ToRasterizablePos() const
	{
		//to fix blury texture issue: https://docs.microsoft.com/vi-vn/windows/desktop/direct3d9/directly-mapping-texels-to-pixels
		return { floor(x), floor(y), 0.0f };
	}
	Vector2& Neutralize()
	{
		x = floor(x + 0.5f), y = floor(y + 0.5f);
		return *this;
	}
	Vector2 GetAbs() const
	{
		return Vector2{ std::abs(x), std::abs(y) };
	}
	Vector2 operator+(const Vector2& other) const
	{
		return { x + other.x, y + other.y };
	}
	Vector2 operator-(const Vector2& other) const
	{
		return { x - other.x, y - other.y };
	}
	Vector2& operator+=(const Vector2& other)
	{
		return *this = *this + other;
	}
};

