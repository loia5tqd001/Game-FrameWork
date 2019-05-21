#include "GameDev.h"
#include "MyException.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	//try
	//{	
		//GameDev::Instance().InitGame();
		GameDev& game = GameDev::Instance();
		game.InitGame();
		game.Run();
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