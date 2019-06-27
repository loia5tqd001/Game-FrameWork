#include "pch.h"
#include "DebugDraw.h"
#include "Game.h"
#include "Camera.h"
#include "Window.h"
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

	if (bbox.left != 0.0f)
	{
		const RectF left = { bbox.left, bbox.top, bbox.left + 1, bbox.bottom  };
		DrawSolidRect( left , color );
	}

	if (bbox.top != 0.0f)
	{
		const RectF top  = { bbox.left, bbox.top, bbox.right   , bbox.top + 1 };
		DrawSolidRect( top  , color );
	}
}

void DebugDraw::ToggleDebugMode()
{
	Instance().isInDebugMode = !Instance().isInDebugMode;
}

bool DebugDraw::IsInDebugMode()
{
	return Instance().isInDebugMode;
}

bool DebugDraw::IsInDeepDebug()
{
	return IsInDebugMode() && Window::Instance().IsKeyPressed(VK_SHIFT);
}

void DebugDraw::DrawString(const std::string& str, const Vector2& pos, D3DCOLOR color)
{
	if (!Instance().isInDebugMode) return;

	const auto drawablePos = Camera::Instance().GetPositionInViewPort( pos );
	Instance().fontDraw.DrawString(str, drawablePos, color);
}

void DebugDraw::DrawString(const std::string& str, const Vector2& pos, D3DCOLOR color, UINT size, LPCSTR font)
{
	if (!Instance().isInDebugMode) return;

	const auto drawablePos = Camera::Instance().GetPositionInViewPort( pos );

	Instance().fontDraw.AdjustFont(size, font);
	Instance().fontDraw.DrawString(str, drawablePos, color);
}
