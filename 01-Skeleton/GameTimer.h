#pragma once
#include <chrono>
#include "ISingleton.h"
#include "MyException.h"


class GameTimer : ISingleton
{
private:
	std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	float deltaTime = 0.0f;

private:
	GameTimer() : ISingleton(NULL) {}
	static GameTimer& Instance()
	{
		static GameTimer instance;
		return instance;
	}

	static int GetFps();

public:
	static void BeginFrame();	
	static float DeltaTime() /*secs*/{ return Instance().deltaTime; }
	static void DebugFps  () { DebugOut("Fps is ", GetFps(), "\n"); }
};