#pragma once
#include <chrono>

class GameTimer 
{
private:
	std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	float deltaTime = 0.0f;

private:
	GameTimer() = default;

	static GameTimer& Instance()
	{
		static GameTimer instance;
		return instance;
	}

public:
	static void BeginFrame()
	{
		Instance().last = Instance().now;
		Instance().now = std::chrono::steady_clock::now();

		std::chrono::duration<float> duration = Instance().now - Instance().last;
		Instance().deltaTime = duration.count();
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

	static float DeltaTime() { return Instance().deltaTime; }
	static void  DebugFps () { Debug::Out("Fps is", GetFps()); }
};