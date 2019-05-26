#pragma once


enum class Direction
{
	Right, Left
};

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
	MarioBigIdle      = 0,
	MarioBigWalking   = 1,
	MarioSmallIdle    = 2,
	MarioSmallWalking = 3,
	MarioDie          = 4,
	Count
};

enum class State
{
	MarioIdle,
	MarioWalking,
	MarioJump,
	MarioDie
};



