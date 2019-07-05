#pragma once

class Block : public InvisibleObject
{
public:
	Block(const Vector2& pos, UINT width, UINT height) :
		InvisibleObject(pos, width, height)
	{
	}
};
