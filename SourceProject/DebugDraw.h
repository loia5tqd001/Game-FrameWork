#pragma once
#include "RectF.h"
#include "Font.h"

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
	static DebugDraw& Instance();

};
