#pragma once
#include "RectF.h"
#include "Font.h"

struct Colors
{
	static constexpr auto MyChineseBrown = D3DCOLOR_ARGB(123, 420, 69, 0);
	static constexpr auto MyPoisonGreen  = D3DCOLOR_ARGB(123, 69, 420, 0);
	static constexpr auto Gray           = D3DCOLOR_ARGB(200, 110, 110, 110);
	static constexpr auto White          = D3DCOLOR_XRGB(255, 255, 255);
};

class DebugDraw
{
private:
	bool isInDebugMode = true;
	Font fontDraw;

public:
	static void ToggleDebugMode();
	static bool IsInDebugMode();
	static bool IsInDeepDebug();

	static void DrawSolidRect(const RectF& bbox, D3DCOLOR color);
	static void DrawRectOutLine(const RectF& bbox, D3DCOLOR color);
	static void DrawString(const std::string& str, const Vector2& pos, D3DCOLOR color);
	static void DrawString(const std::string& str, const Vector2& pos, D3DCOLOR color, UINT size, LPCSTR font);

private:
	DebugDraw() : fontDraw(12, "Arial") {}
	static DebugDraw& Instance() 
	{ 
		static DebugDraw instance; 
		return instance; 
	}
};
