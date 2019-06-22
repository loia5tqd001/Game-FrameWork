#pragma once
#include "Vector2.h"

struct Vector3 : public D3DXVECTOR3
{
	template<typename T>
	Vector3(T x, T y, float z) : D3DXVECTOR3((float)x, (float)y, z)
	{}
	Vector3() : D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	{}

	//to fix blury texture issue: https://docs.microsoft.com/vi-vn/windows/desktop/direct3d9/directly-mapping-texels-to-pixels
	Vector3& ToRasterizablePos() 
	{
		x = floor(x), y = floor(y), z = floor(z);
		return *this;
	}

	Vector3 operator+(const Vector2& offset) const
	{
		assert(z == 0.0f);
		return Vector3{ x + offset.x, y + offset.y, 0.0f };
	}
	Vector3& operator+=(const Vector2& offset)
	{
		return *this = *this + offset;
	}
	Vector3 operator-(const Vector3& other) const
	{
		return Vector3{ x - other.x, y - other.y, z - other.z };
	}
	Vector3 operator+(const Vector3& other) const
	{
		return Vector3{ x + other.x, y + other.y, z + other.z };
	}
};
