#pragma once



enum class TextureType
{
	Bbox  = 0,
	Mario = 1,
	Misc  = 2,
	Enemy = 3,
	Map   = 4,
	Count
};

enum class SpriteType
{
	Invisible         = 0,
	MarioBigIdle      = 1,
	MarioBigWalking   = 2,
	MarioSmallIdle    = 3,
	MarioSmallWalking = 4,
	MarioDie          = 5,
	BrickIdle         = 6,
	GoombaMoving      = 7,
	GoombaDie         = 8,
	Count
};

enum class ObjectType
{
	Mario,
	Brick,
	Goomba,
	Count
};

enum class State
{
	Invisible,
	MarioIdle,
	MarioWalking,
	MarioJump,
	MarioDie,
	BrickIdle,
	GoombaMoving,
	GoombaDie,
	Destroyed,
	Count


};

enum class Scene
{
	Demo,
	Intro,
	GamePlay
};



