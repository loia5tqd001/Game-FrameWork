#include "pch.h"
#include "DebugDraw.h"
#include "Game.h"
#include "Camera.h"
#include "Textures.h"

void DebugDraw::DrawSolidRect(const RectF& bbox, D3DCOLOR color)
{
	if (!Instance().isInDebugMode) return;

	static const auto& cam = Camera::Instance();
	const auto drawablePos = cam.GetPositionInViewPort({ bbox.left - 0.5f, bbox.top - 0.5f, 0.0f });

	const Rect portion = (Rect)bbox;
	std::vector<Vector2> points(2 * portion.GetHeight());

	for (UINT i = 0; i < portion.GetHeight(); i++)
	{
		points[i * 2]     = { drawablePos.x                     , drawablePos.y + i};
		points[i * 2 + 1] = { drawablePos.x + portion.GetWidth(), drawablePos.y + i};
	}                                    

	Game::Instance().DrawLines(points, color);
}

void DebugDraw::DrawRectOutLine(const RectF& bbox, D3DCOLOR color)
{
	if (!Instance().isInDebugMode) return;

	static std::vector<Vector2> points(5);
	const auto drawablePos = Camera::Instance().GetPositionInViewPort({ bbox.left, bbox.top, 0.0f });

	points[0] =                    { drawablePos.x   , drawablePos.y    };
	points[1] = points[0] + Vector2{ bbox.GetWidth() , 0.0f             };
	points[2] = points[0] + Vector2{ bbox.GetWidth() , bbox.GetHeight() };
	points[3] = points[0] + Vector2{ 0.0f            , bbox.GetHeight() };
	points[4] = points[0]                                                ;

	Game::Instance().DrawLines(points, color);
}

void DebugDraw::ToggleDebugMode()
{
	Instance().isInDebugMode = !Instance().isInDebugMode;
}

bool DebugDraw::IsInDebugMode()
{
	return Instance().isInDebugMode;
}

void DebugDraw::DrawString(const std::string& str, const Vector3& pos, D3DCOLOR color)
{
	if (!Instance().isInDebugMode) return;

	const auto drawablePos = Camera::Instance().GetPositionInViewPort( pos );
	Game::Instance().DrawString(str, drawablePos, color);
}

void DebugDraw::DrawString(const std::string& str, const Vector3& pos, D3DCOLOR color, UINT size, LPCSTR font)
{
	if (!Instance().isInDebugMode) return;

	const auto drawablePos = Camera::Instance().GetPositionInViewPort( pos );

	Game::Instance().AdjustFontString(size, font);
	Game::Instance().DrawString(str, drawablePos, color);
}
