#pragma once

enum Direction
{
	LeftToRight,
	RightToLeft,
};

enum TextureType
{
	Mario,
	Boomba
};

enum AnimationType
{

};

enum State
{
	Mario_Begin,
	Mario_Running,
	Mario_Walking,
	Mario_End,

	Boomba_Begin,
	Boomba_Running,
	Boomba_Thiking,
	Boomba_End,

	Count
};
