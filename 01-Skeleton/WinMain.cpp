#include "GameDevelopment.h"
#include "MyException.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
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
}