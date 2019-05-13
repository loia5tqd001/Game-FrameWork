#include "MainWindow.h"
#include "MyException.h"
#include "GameDevelopment.h"


LRESULT MainWindow::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			MainWindow::Instance().OnKeyDown((BYTE)wParam);
			break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
			MainWindow::Instance().OnKeyUp((BYTE)wParam);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void MainWindow::InitWindow()
{
	hInstance = GetModuleHandle(NULL);

	WNDCLASSEX		 wc;
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hInstance	 = hInstance;
	wc.lpfnWndProc   = WinProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hbrBackground = NULL;
	wc.hIcon		 = NULL;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hIconSm		 = NULL;
	wc.lpszMenuName	 = NULL;
	wc.style		 = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);

	hWnd = CreateWindow(WINDOW_CLASS_NAME,
						WINDOW_TITLE,
						WS_OVERLAPPEDWINDOW, // Full screen: WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						SCREEN_WIDTH,
						SCREEN_HEIGHT,
						NULL,
						NULL,
						hInstance,
						NULL);

	if (hWnd == nullptr) ThrowMyException("Can't create window!");

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
}

void MainWindow::OnKeyDown(BYTE keyCode)
{
	keyStates[keyCode] = true;
	GameDev::Instance().OnKeyDown(keyCode);
}

void MainWindow::OnKeyUp(BYTE keyCode)
{
	keyStates[keyCode] = false;
	GameDev::Instance().OnKeyUp(keyCode);
}

bool MainWindow::ProcessMessage() const
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) return false;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}
