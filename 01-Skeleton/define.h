#pragma once

enum class Direction
{
	Right, Left
};

enum class TextureType
{
	Mario,
	Misc,
	Enemy,
	Bbox
};

enum class SpriteType
{
	Bbox,
	MarioDie,
	MarioBigIdle,
	MarioBigWalking,
	MarioSmallIdle,
	MarioSmallWalking,
};

enum class State
{
	MarioIdle,
	MarioWalking,
	MarioJump,
	MarioDie
};



