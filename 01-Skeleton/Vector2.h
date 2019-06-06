#pragma once


struct Vector2 : public D3DXVECTOR2
{
	template<typename T>
	Vector2(T x, T y) : D3DXVECTOR2((float)x, (float)y)
	{}

	Vector2 GetAbs() const
	{
		return Vector2{ std::abs(x), std::abs(y) };
	}
};

using Distance = Vector2;

