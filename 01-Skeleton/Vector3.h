#pragma once
#include "Vector2.h"

struct Vector3 : public D3DXVECTOR3
{
	template<typename T>
	Vector3(T x, T y, float z) : D3DXVECTOR3((float)x, (float)y, z)
	{}
	Vector3() : D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	{}

	Vector3 operator+(const Distance& offset) const
	{
		assert(z == 0.0f);
		return Vector3{ x + offset.x, y + offset.y, 0.0f };
	}
	Vector3& operator+=(const Distance& offset)
	{
		return *this = *this + offset;
	}
	Vector3 operator-(const Vector3& other) const
	{
		return Vector3{ x - other.x, y - other.y, z - other.z };
	}
};

using Point = Vector3;
