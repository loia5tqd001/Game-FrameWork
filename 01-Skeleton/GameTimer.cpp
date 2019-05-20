#include "GameTimer.h"

int GameTimer::GetFps()
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

void GameTimer::BeginFrame()
{
	Instance().last = Instance().now;
	Instance().now = std::chrono::steady_clock::now();

	std::chrono::duration<float> duration = Instance().now - Instance().last;
	Instance().deltaTime = duration.count();
}