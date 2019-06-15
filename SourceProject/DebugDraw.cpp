#include "pch.h"
#include "DebugDraw.h"
#include "Game.h"
#include "Textures.h"
#include "Camera.h"

void DebugDraw::DrawBoundingBox(const RectF& bbox, int alpha) const
{
	static const auto bboxTexture = Textures::Get(TextureType::Bbox);

	const Point position = { bbox.left, bbox.top, 0.0f };
	const Rect  portion  = bbox.GetOriginRect();
	Game::Instance().Draw( Camera::Instance().GetPositionInViewPort(position), bboxTexture, portion, { 1.0f, 1.0f }, alpha );
}

void DebugDraw::DrawOutLine(const RectF& bbox) const
{
	static constexpr auto lineColor = D3DCOLOR_XRGB(420, 69, 000);
	static std::vector<Vector2> points(5);

	const auto drawablePos = Camera::Instance().GetPositionInViewPort({ bbox.left, bbox.top, 0.0f });

	points[0] =                    { drawablePos.x   , drawablePos.y    };
	points[1] = points[0] + Vector2{ bbox.GetWidth() , 0.0f             };
	points[2] = points[0] + Vector2{ bbox.GetWidth() , bbox.GetHeight() };
	points[3] = points[0] + Vector2{ 0.0f            , bbox.GetHeight() };
	points[4] = points[0]                                                ;

	Game::Instance().DrawLines(points, lineColor);
}

void DebugDraw::SetDebugMode(bool isDebug)
{
	Instance().isInDebugMode = isDebug;
}

void DebugDraw::ToggleDebugMode()
{
	Instance().isInDebugMode = !Instance().isInDebugMode;
}

void DebugDraw::Draw(const RectF& bbox, DrawType drawType)
{
	if (!Instance().isInDebugMode) return;

	switch (drawType)
	{
		case DrawType::SolidFull:
			Instance().DrawBoundingBox(bbox, 200);
			break;

		case DrawType::SolidHalf:
			Instance().DrawBoundingBox(bbox, 100);
			break;

		case DrawType::Outline:
			Instance().DrawOutLine(bbox);
			break;
	}
}
