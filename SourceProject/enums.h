#pragma once



enum class TextureId
{
	Bbox  = 0,
	Mario = 1,
	Misc  = 2,
	Enemy = 3,
	Map   = 4,
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

enum class TextId
{
	CharA = 'A', // 65
	CharB = 'B', 
	CharC = 'C',
	CharD = 'D',
	CharE = 'E',
	CharF = 'F',
	CharG = 'G',
	CharH = 'H',
	CharI = 'I',
			  
	CharJ = 'J',
	CharK = 'K',
	CharL = 'L',
	CharM = 'M',
	CharN = 'N',
	CharO = 'O',
	CharP = 'P',
	CharQ = 'Q',
	CharR = 'R',
			  
	CharS = 'S',
	CharT = 'T',
	CharU = 'U',
	CharV = 'V',
	CharW = 'W',
	CharX = 'X',
	CharY = 'Y',
	CharZ = 'Z',
	Char0 = '0', // 48
		  
	Char1 = '1',
	Char2 = '2',
	Char3 = '3',
	Char4 = '4',
	Char5 = '5',
	Char6 = '6',
	Char7 = '7',
	Char8 = '8',
	Char9 = '9',
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





