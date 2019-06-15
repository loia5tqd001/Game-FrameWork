#pragma once

class DebugDraw : ISingleton
{
private:
	bool isInDebugMode = true;

private:
	void DrawBoundingBox(const RectF& bbox, int alpha) const;
	void DrawOutLine(const RectF& bbox) const;

public:
	static void SetDebugMode(bool isDebug);
	static void ToggleDebugMode();

	enum class DrawType { SolidFull, SolidHalf, Outline };
	static void Draw(const RectF& bbox, DrawType drawType);

private:
	DebugDraw() : ISingleton(NULL) {}

public:
	static DebugDraw& Instance() 
	{ 
		static DebugDraw instance; 
		return instance; 
	}
};
