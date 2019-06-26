#pragma once
#include "RectF.h"

struct Colors
{
	static constexpr auto MyChineseBrown = D3DCOLOR_ARGB(123, 420, 69, 0);
	static constexpr auto MyPoisonGreen  = D3DCOLOR_ARGB(123, 69, 420, 0);
	static constexpr auto GridDebug      = D3DCOLOR_XRGB(255, 255, 255);
};

class DebugDraw
{
private:
	bool isInDebugMode = true;

public:
	static void ToggleDebugMode();
	static bool IsInDebugMode();

	static void DrawSolidRect(const RectF& bbox, D3DCOLOR color);
	static void DrawRectOutLine(const RectF& bbox, D3DCOLOR color);
	static void DrawString(const std::string& str, const Vector2& pos, D3DCOLOR color);
	static void DrawString(const std::string& str, const Vector2& pos, D3DCOLOR color, UINT size, LPCSTR font);

private:
	DebugDraw() = default;
	static DebugDraw& Instance() 
	{ 
		static DebugDraw instance; 
		return instance; 
	}
};
