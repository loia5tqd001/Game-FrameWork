#pragma once

enum class DrawType { SolidRect, RectOutline };

struct Colors
{
	static constexpr auto MyChineseBrown = D3DCOLOR_ARGB(123, 420, 69, 0);
	static constexpr auto MyPoisonGreen  = D3DCOLOR_ARGB(123, 69, 420, 0);
};

class DebugDraw : ISingleton
{
private:
	bool isInDebugMode = true;

private:
	void DrawBoundingBox(const RectF& bbox, D3DCOLOR color) const;
	void DrawOutLine(const RectF& bbox, D3DCOLOR color) const;

public:
	static void ToggleDebugMode();

	static void Draw(const RectF& bbox, DrawType drawType, D3DCOLOR color);

private:
	DebugDraw() : ISingleton(NULL) {}

public:
	static DebugDraw& Instance() 
	{ 
		static DebugDraw instance; 
		return instance; 
	}
};
