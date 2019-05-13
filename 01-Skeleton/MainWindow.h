#pragma once
#include <Windows.h>
#include "ISingleton.h"

class MainWindow : ISingleton
{
private:
	static constexpr char* WINDOW_CLASS_NAME = "MainWindow" ;
	static constexpr char* WINDOW_TITLE      = "SE102 - UIT";
	static constexpr int   SCREEN_WIDTH      = 320;
	static constexpr int   SCREEN_HEIGHT     = 240;

	HINSTANCE hInstance = nullptr;
	HWND	  hWnd		= nullptr;
	BOOL	  keyStates[256]; // 256 is the number of key codes possible

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void   OnKeyDown(BYTE keyCode);
	void   OnKeyUp  (BYTE keyCode);

public:
	void InitWindow();
	bool ProcessMessage() const;
	bool IsKeyPressed(BYTE keyCode) const { return keyStates[keyCode];  }
	static void ShowMessageBox(LPCSTR message, LPCSTR title = "", UINT type = MB_OK) { MessageBox(nullptr, message, title, type); }

	int	       GetWidth () const { return SCREEN_WIDTH ;}
	int	       GetHeight() const { return SCREEN_HEIGHT;}
	const HWND GetHWnd  () const { return hWnd		   ;}

private:
	MainWindow() : ISingleton(NULL) {}

public:
	static MainWindow& Instance() 
	{ 
		static MainWindow instance; 
		return instance; 
	}
};

