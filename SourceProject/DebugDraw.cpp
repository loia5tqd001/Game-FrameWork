#include "pch.h"
#include "DebugDraw.h"
#include "Game.h"
#include "Camera.h"
#include "Textures.h"

void DebugDraw::DrawSolidRect(const RectF& bbox, D3DCOLOR color)
{
	if (!Instance().isInDebugMode) return;

	static const auto& cam = Camera::Instance();
	const auto drawablePos = cam.GetPositionInViewPort( bbox.GetTopLeft() );

	static const auto bboxTexture = Textures::Get(TextureId::Bbox);
	Game::Instance().Draw(drawablePos, bboxTexture, bbox.GetOriginRect(), { 1.0f, 1.0f }, color);
}

void DebugDraw::DrawRectOutLine(const RectF& bbox, D3DCOLOR color)
{
	if (!Instance().isInDebugMode) return;

	const RectF left = { bbox.left, bbox.top, bbox.left + 1, bbox.bottom  };
	const RectF top  = { bbox.left, bbox.top, bbox.right   , bbox.top + 1 };

	if (bbox.left != 0.0f)	DrawSolidRect( left , color );
	if (bbox.top  != 0.0f)  DrawSolidRect( top  , color );
}

void DebugDraw::ToggleDebugMode()
{
	Instance().isInDebugMode = !Instance().isInDebugMode;
}

bool DebugDraw::IsInDebugMode()
{
	return Instance().isInDebugMode;
}

void DebugDraw::DrawString(const std::string& str, const Vector2& pos, D3DCOLOR color)
{
	if (!Instance().isInDebugMode) return;

	const auto drawablePos = Camera::Instance().GetPositionInViewPort( pos );
	Game::Instance().DrawString(str, drawablePos, color);
}

void DebugDraw::DrawString(const std::string& str, const Vector2& pos, D3DCOLOR color, UINT size, LPCSTR font)
{
	if (!Instance().isInDebugMode) return;

	const auto drawablePos = Camera::Instance().GetPositionInViewPort( pos );

	Game::Instance().AdjustFontString(size, font);
	Game::Instance().DrawString(str, drawablePos, color);
}
