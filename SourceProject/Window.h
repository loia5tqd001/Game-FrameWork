#pragma once

class Window : ISingleton
{
private:
	static constexpr char* WINDOW_CLASS_NAME = "MainWindow" ;
	static constexpr char* WINDOW_TITLE      = "SE102 - UIT";
	static constexpr UINT  SCREEN_WIDTH      = 320;
	static constexpr UINT  SCREEN_HEIGHT     = 240;

	HINSTANCE hInstance = nullptr;
	HWND	  hWnd		= nullptr;
	std::bitset<256>    keyStates; // 256 is the maximum number of key codes possible

public:
	void InitWindow();
	bool ProcessMessage() const;
	void SetTitleToFps() const;
	bool IsKeyPressed(BYTE keyCode) const { return keyStates.test(keyCode); }

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static void ShowMessageBox(LPCSTR message, LPCSTR title = "", UINT type = MB_OK);

	const UINT GetWidth () const { return SCREEN_WIDTH ;}
	const UINT GetHeight() const { return SCREEN_HEIGHT;}
	const HWND GetHWnd  () const { return hWnd		   ;}

private:
	Window() : ISingleton(NULL) {}

public:
	static Window& Instance() 
	{ 
		static Window instance; 
		return instance; 
	}
};

