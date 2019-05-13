#pragma once
#include <Windows.h>
#include <chrono>
#include <string>
#include "ISingleton.h"


class FrameTimer : ISingleton
{
private:
	std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	float deltaTime = 0.0f;

private:
	FrameTimer() : ISingleton(NULL) {}
	static FrameTimer& Instance()
	{
		static FrameTimer instance;
		return instance;
	}

	static int GetFps()
	{
		static float timePassed = 0.0f;
		static int fps = 0;
		static int nFrame = 0;

		nFrame++;
		timePassed += DeltaTime();

		if (timePassed >= 1.0f)
		{
			fps = nFrame;
			nFrame = 0;
			timePassed -= 1.0f;
		}

		return fps;
	}

public:
	static void BeginFrame()
	{
		Instance().last = Instance().now;
		Instance().now = std::chrono::steady_clock::now();

		std::chrono::duration<float> duration = Instance().now - Instance().last;
		Instance().deltaTime = duration.count();
	}

	static float DeltaTime() // unit: second
	{
		return Instance().deltaTime;
	}

	static void DebugFps()
	{
		std::string str = "Fps is: " + std::to_string(GetFps()) + "\n";
		OutputDebugString(str.c_str());
	}
};