#pragma once
#include "ISingleton.h"
#include <Windows.h>
#include <bitset>
#include "MyException.h"
class MainWindow : ISingleton
{
private:
	static constexpr char* WINDOW_CLASS_NAME = "MainWindow" ;
	static constexpr char* WINDOW_TITLE      = "SE102 - UIT";
	static constexpr int   SCREEN_WIDTH      = 320;
	static constexpr int   SCREEN_HEIGHT     = 240;

	HINSTANCE hInstance = nullptr;
	HWND	  hWnd		= nullptr;
	std::bitset<256> curKeyStates; // 256 is the number of key codes possible
	std::bitset<256> preKeyStates;

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void   OnKeyDown(BYTE keyCode);
	void   OnKeyUp  (BYTE keyCode);

public:
	void InitWindow();
	bool ProcessMessage() const;
	bool IsKeyPressed(BYTE keyCode) const { return curKeyStates[keyCode]; }
	bool IsKeyHitOnce(BYTE keyCode) const { 
		DebugOut(curKeyStates[keyCode] && !preKeyStates[keyCode]); 
		return curKeyStates[keyCode] && !preKeyStates[keyCode];
	}
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

