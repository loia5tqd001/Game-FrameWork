#pragma once
#include <chrono>

class GameTimer 
{
private:
	std::chrono::steady_clock::time_point last = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	float deltaTime = 0.0f;
	unsigned int fps = 0u;

private:
	GameTimer() = default;
	static GameTimer& Instance()
	{
		static GameTimer instance;
		return instance;
	}
	void CalculateFps()
	{
		static float timePassed = 0.0f;
		static unsigned int nFramesPassed = 0u;

		nFramesPassed++;
		timePassed += deltaTime;

		if (timePassed >= 1.0f)
		{
			fps = nFramesPassed;
			nFramesPassed = 0;
			timePassed -= 1.0f;
		}
	}
	void Mark()
	{
		last = now; 
		now = std::chrono::steady_clock::now();
		std::chrono::duration<float> duration = now - last;
		deltaTime = duration.count();
		CalculateFps();
	}

public:
	inline static void  BeginFrame() {        Instance().Mark()   ; }
	inline static auto  GetFps    () { return Instance().fps      ; }
	inline static float Dt        () { return Instance().deltaTime; }
};