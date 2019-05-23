#pragma once
#include "define.h"
#include "ISingleton.h"
#include "MyException.h"
#include <unordered_map>


class Frames : ISingleton
{
private:
	std::unordered_map<SpriteType, std::vector<RECT>> frameDictionary;

public:
	void AddFrames(SpriteType id, LPCSTR filePath); 
	const std::vector<RECT>& GetFrames(SpriteType id) const;

private:
	Frames() : ISingleton(NULL) {}

public:
	static Frames& Instance()
	{
		static Frames instance;
		return instance;
	}
};