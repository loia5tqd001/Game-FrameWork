#pragma once
#include "Brick.h"
#include "Camera.h"

class Grid
{
private:
	std::vector<std::vector<std::shared_ptr<GameObject>>> cells;
	UINT cellSize, width, height;

	Grid(const Grid&) = delete;
	Grid(const Json::Value& root)
	{
		LoadResources(root);
	}
	auto LoadObjects(const Json::Value& root)
	{
		std::unordered_map<int, std::shared_ptr<GameObject>> result;
		const Json::Value& objects = root["objects"];
		for (const auto& obj : objects)
		{
			const UINT objId   = obj[0].asUInt();
			const UINT classId = obj[1].asUInt();
			const UINT x       = obj[2].asUInt();
			const UINT y       = obj[3].asUInt();
			const UINT nx      = obj[4].asUInt();
			const D3DXVECTOR3 pos = { (float)x, (float)y, 0.0f };
			switch ((ObjectType)classId)
			{
				case ObjectType::Brick:
					result.emplace(objId, std::make_shared<Brick>(pos));

			}
		}
		return result;
	}
	void LoadResources(const Json::Value& root)
	{
		auto objectMap = LoadObjects(root);

		const Json::Value& grid = root["grid"];
		cellSize = grid["cellsize"].asUInt();
		width    = grid["width"   ].asUInt();
		height   = grid["height"  ].asUInt();
		cells.resize(width * height);
		const Json::Value& cellsData = grid["cells"];
		assert(width*height == cellsData.size());
		for (UINT i = 0; i < width * height; i++)
		{
			if (!cellsData[i].isNumeric())
			{
				for (auto& objId : cellsData[i])
				{
					auto& obj = objectMap.at(objId.asInt());
					cells[i].emplace_back(obj);
				}
			}
		}
	}
	void RemoveDestroyedObjects()
	{
		UINT xs, xe, ys, ye; GetViewPort(xs, xe, ys, ye);
		for (UINT y = ys; y <= ye; y++)
		for (UINT x = xs; x <= xe; x++)
		{
			auto& objs = cells[y * width + x];
			auto newEnd = std::remove_if(objs.begin(), objs.end(), 
				[](auto o){ return o->GetState() == State::Destroyed; });
			objs.erase(newEnd, objs.end());
		}
	}
	void GetViewPort(UINT& xs, UINT& xe, UINT& ys, UINT& ye) const
	{
		const auto camRect = Camera::Instance().GetBBox();
		                xs = UINT(camRect.left   / cellSize);//-2
		                xe = UINT(camRect.right  / cellSize);
		                ys = UINT(camRect.bottom / cellSize);//+2
		                ye = UINT(camRect.top    / cellSize);
	}

public:
	std::vector<LPGAMEOBJECT> GetObjectsInViewPort() const
	{
		std::vector<LPGAMEOBJECT> result;
		UINT xs, xe, ys, ye; GetViewPort(xs, xe, ys, ye);
		for (UINT y = ys; y <= ye; y++)
		for (UINT x = xs; x <= xe; x++)
		{
			const auto& objs = cells[y * width + x];
			std::transform(objs.begin(), objs.end(), std::back_inserter(result),
				[](auto& pO){ return pO.get(); });
		}
		std::sort(result.begin(), result.end());
		result.erase( std::unique( result.begin(),result.end() ), result.end() );
		return result;
	}
};

