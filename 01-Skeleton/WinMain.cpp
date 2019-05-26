#include "pch.h"
#include "GameDev.h"
#include "MyException.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
#ifdef DEBUG

	GameDev::Instance().InitGame();
	GameDev::Instance().Run();

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