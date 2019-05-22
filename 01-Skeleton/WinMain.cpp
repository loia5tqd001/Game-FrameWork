#include "GameDev.h"
#include "MyException.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	GameDev::Instance().InitGame();
	GameDev::Instance().Run();

	//try
	//{	
	//	GameDev::Instance().InitGame();
	//	GameDev::Instance().Run();
	//}
	//catch (const std::exception& ex)
	//{
	//	MainWindow::ShowMessageBox(ex.what());
	//}
	//catch (...)
	//{
	//	MainWindow::ShowMessageBox("Unknown Exception");
	//}
}