#pragma once



enum class TextureId
{
	Mario = 0,
	Misc  = 1,
	Enemy = 2,
	Map   = 3,
	Count
};

enum class SpriteId
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

enum class SoundId
{
	Test,
	MarioJump,
	MarioMusic,
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





