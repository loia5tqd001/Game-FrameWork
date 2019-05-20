#pragma once
#include "define.h"
#include "ISingleton.h"
#include "MyException.h"
#include <unordered_map>


class Frames : ISingleton
{
private:
	std::unordered_map<AnimationType, std::vector<RECT>> frameDictionary;

public:
	const std::vector<RECT>& AddFrames(AnimationType id, LPCSTR filePath);
	const std::vector<RECT>& GetFrames(AnimationType id) const;

private:
	Frames() : ISingleton(NULL) {}

public:
	static Frames& Instance()
	{
		static Frames instance;
		return instance;
	}
};