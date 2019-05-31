#include "pch.h"
#include "Map.h"
#include "Camera.h"
#include "Game.h"

void Map::LoadResources(LPCSTR jsonPath, std::shared_ptr<GameObject>& objects)
{
}

void Map::Render() const
{
	const RectF camRect = Camera::Instance().GetBBox();

	for (UINT i = 0; i < nRows; i++)
	{
		for (UINT j = 0; j < nCols; j++)
		{
			static D3DXVECTOR3 tilePos;
			tilePos.x = float(j * tileSize);
			tilePos.y = float(i * tileSize);
			tilePos  -= D3DXVECTOR3(camRect.left, camRect.top, 0.0f);
			Game::Instance().Draw(tilePos, texture, tiles[i * nCols + j]);
		}
	}
}
