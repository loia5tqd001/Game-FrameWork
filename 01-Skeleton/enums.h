#pragma once




enum class TextureType
{
	Bbox  = 0,
	Mario = 1,
	Misc  = 2,
	Enemy = 3,
	Count
};

enum class SpriteType
{
	Invisible         = 0,
	MarioBigIdle      = 1,
	MarioBigWalking   = 2,
	//MarioSmallIdle    = 3,
	//MarioSmallWalking = 4,
	//MarioDie          = 5,
	Count
};

enum class State
{
	MarioIdle,
	MarioWalking,
	MarioJump,
	MarioDie
};



