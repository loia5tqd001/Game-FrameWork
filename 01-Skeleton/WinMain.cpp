#include "pch.h"
#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
#ifdef DEBUG

	Game::Instance().InitGame();
	Game::Instance().Run();

#else

	try
	{	
		Game::Instance().InitGame();
		Game::Instance().Run();
	}
	catch (const std::exception& ex)
	{
		Window::ShowMessageBox(ex.what());
	}
	catch (...)
	{
		Window::ShowMessageBox("Unknown Exception");
	}

#endif
}