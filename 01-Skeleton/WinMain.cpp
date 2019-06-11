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
		GameDev::Instance().InitGame();
		GameDev::Instance().Run();
	}
	catch (const std::exception& ex)
	{
		MainWindow::ShowMessageBox(ex.what());
	}
	catch (...)
	{
		MainWindow::ShowMessageBox("Unknown Exception");
	}

#endif
}