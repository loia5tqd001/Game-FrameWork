#pragma once
#include "GameObject.h"

class Map
{
private:
	UINT nRows, nCols, tileSize;
	std::vector<RECT> tileSets;

public:
	Map(const Map&) = delete;
	void LoadResources(LPCSTR jsonPath, std::shared_ptr<GameObject>& objects);
	void Render() const;

	UINT GetMapWidth () const { return nCols * tileSize; }
	UINT GetMapHeight() const { return nRows * tileSize; }
	UINT GetTileSize () const { return         tileSize; }
};