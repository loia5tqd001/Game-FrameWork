#include "Frames.h"
#include "MyException.h"
#include <fstream>

const std::vector<RECT>& Frames::AddFrames(AnimationType id, LPCSTR filePath)
{
	assert(frameDictionary.count(id) == 0);

	std::ifstream frameFile(filePath, std::ifstream::in);
	if (!frameFile.is_open()) ThrowMyException("Add frames from file failed");

	std::vector<RECT> frames;
	unsigned int     nFrames;
	frameFile >> nFrames;
	frames.reserve(nFrames);

	RECT buffer;
	for (int i = 0; i < nFrames; i++)
	{
		frameFile >> buffer.left >> buffer.top >> buffer.right >> buffer.bottom;
		frames.emplace_back(std::move(buffer));
	}

	frameDictionary.emplace(id, std::move(frames));
	return GetFrames(id);
}

const std::vector<RECT>& Frames::GetFrames(AnimationType id) const
{
	assert(frameDictionary.count(id) == 1);
	return frameDictionary.at(id);
}