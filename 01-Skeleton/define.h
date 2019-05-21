#pragma once

enum class Direction
{
	Right,
	Left
};

enum class TextureType
{
	Mario,
	Misc,
	Enemy,
	Bbox
};

enum class AnimationType
{
	Mario_Die,
	Mario_BigIdle,
	Mario_BigWalking,
	Mario_SmallIdle,
	Mario_SmallWalking,
};

enum class State
{
	Mario_Idle,
	Mario_Walking,
	Mario_Jump,
	Mario_Die
};



