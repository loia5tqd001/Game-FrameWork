#include "pch.h"
#include "Brick.h"
#include "Goomba.h"

Grid::Grid(const Json::Value& root)
{
	LoadResources(root);
}

auto Grid::LoadObjects(const Json::Value& root)
{
	std::unordered_map<UINT, GameObject*> staticObjects;
	std::unordered_map<UINT, GameObject*> movingObjects;

	const Json::Value& jsonObjects = root["objects"];

	const UINT nObjects = jsonObjects[0].asUInt();
	assert(nObjects == jsonObjects.size() - 1);

	objectHolder.reserve(nObjects);

	for (UINT i = 1; i <= nObjects; i++)
	{
		const Json::Value& obj = jsonObjects[i];
		const UINT  objId    = obj[0].asUInt ();
		const UINT  classId  = obj[1].asUInt ();
		const bool  isStatic = obj[2].asBool ();
		const float x        = obj[3].asFloat();
		const float y        = obj[4].asFloat();
		const float vx       = obj[5].asFloat();
		const float vy       = obj[6].asFloat();
		const float nx       = obj[7].asFloat();

		static std::unique_ptr<GameObject> object;
		switch ((ObjectType)classId)
		{
			case ObjectType::Brick:
				object = std::make_unique<Brick>( Vector2(x, y) );
				break;

			case ObjectType::Goomba:
				object = std::make_unique<Goomba>( Vector2(x, y), Vector2(vx, 0.0f) );
				break;

			default:
				ThrowMyException("Read unknown type objects");
				break;
		}

		if (isStatic) staticObjects.emplace(objId, object.get());
		else          movingObjects.emplace(objId, object.get());

		objectHolder.emplace_back(std::move(object));
	}

	return std::make_pair(staticObjects, movingObjects);
}

void Grid::LoadResources(const Json::Value& root)
{		
	const auto mapObjects = LoadObjects(root);

	const Json::Value& grid = root["grid"];
	cellSize = grid["cellsize"].asUInt();
	width    = grid["width"   ].asUInt();
	height   = grid["height"  ].asUInt();

	const Json::Value& cellsData = grid["cells"];
	assert(cellsData.size() == width * height);

	cells.resize(width * height);
	for (UINT i = 0; i < width * height; i++)
	{
		const float x = float(i / height) * cellSize;
		const float y = float(i % height) * cellSize;
		cells[i].boundingBox = { x, y, cellSize, cellSize };

		const Json::Value& jsonCell = cellsData[i];
		const Json::Value& statics  = jsonCell [0];
		const Json::Value& movings  = jsonCell [1];

		for (UINT j = 0; j < statics.size(); j++)
		{
			UINT objId = statics[j].asUInt();
			auto obj   = mapObjects.first.at(objId);

			cells[i].staticObjects.emplace( obj );
			assert(obj->GetBBox().IsIntersect( cells[i].GetBBox() ));
		}
		for (UINT j = 0; j < movings.size(); j++)
		{
			UINT objId = movings[j].asUInt();
			auto obj   = mapObjects.second.at(objId);

			cells[i].movingObjects.emplace( obj );
			assert(obj->GetBBox().IsIntersect( cells[i].GetBBox() ));
		}
	}
}

Area Grid::CalcCollidableArea(const RectF& bbox) const
{
	return 	{
		UINT(max(0         , bbox.left   / cellSize)),
		UINT(min(width  - 1, bbox.right  / cellSize)),
		UINT(max(0         , bbox.top    / cellSize)),
		UINT(min(height - 1, bbox.bottom / cellSize))
	};
}

void Grid::SpawnObject(std::unique_ptr<GameObject> obj)
{
	Area area = CalcCollidableArea( obj->GetBBox() );

	for (UINT x = area.xs; x <= area.xe; x++)
	for (UINT y = area.ys; y <= area.ye; y++)
	{
		cells[x * height + y].movingObjects.emplace( obj.get() );
	}

	objectHolder.emplace_back( std::move(obj) );
}

std::vector<GameObject*> Grid::GetObjectsNear(GameObject* objectInInterest) const
{
	std::unordered_set<GameObject*> result;
	float dx, dy; objectInInterest->GetDxDy(GameTimer::Dt(), dx, dy);

	Area area = CalcCollidableArea( objectInInterest->GetBBox().GetBroadPhase(dx, dy) );

	for (UINT x = area.xs; x <= area.xe; x++)
	for (UINT y = area.ys; y <= area.ye; y++)
	{
		const Cell& cell = cells[x * height + y];
		result.insert(cell.staticObjects.begin(), cell.staticObjects.end());
		result.insert(cell.movingObjects.begin(), cell.movingObjects.end());
	}

	return { result.begin(), result.end() };
}

Area Grid::GetVicinityAreaOfViewPort() const
{
	Area area = CalcCollidableArea( Camera::Instance().GetBBox() );
	area.xs = max(0    , (int)area.xs - 2); // expand considering region by (2,1) cells
	area.xe = min(width  - 1, area.xe + 2);
	area.ys = max(0    , (int)area.ys - 1); 
	area.ye = min(height - 1, area.ye + 1); 
	return area;
}

void Grid::RemoveDestroyedObjects()
{
	Area area = GetVicinityAreaOfViewPort();

	for (UINT x = area.xs; x <= area.xe; x++)
	for (UINT y = area.ys; y <= area.ye; y++)
	{
		Cell& cell = cells[x * height + y];
		Utils::RemoveIf(cell.movingObjects, [](auto o) { return o->GetState() == State::Destroyed;} );
	}

	Utils::RemoveIf(objectHolder, [](auto& o) { return o->GetState() == State::Destroyed; });
}

void Grid::RecalculateObjectsInViewPort()
{
	std::unordered_set<GameObject*> result;

	Area area = GetVicinityAreaOfViewPort();

	for (UINT x = area.xs; x <= area.xe; x++)
	for (UINT y = area.ys; y <= area.ye; y++)
	{
		const Cell& cell = cells[x * height + y];
		result.insert(cell.staticObjects.begin(), cell.staticObjects.end());
		result.insert(cell.movingObjects.begin(), cell.movingObjects.end());
	}

	curObjectsInViewPort = { result.begin(), result.end() };
}

void Grid::UpdateCells()
{
	std::unordered_set<GameObject*> shouldBeUpdatedObjects;

	for (UINT x = 0; x < width; x++)
	for (UINT y = 0; y < height; y++)
	{
		Cell& cell = cells[x * height + y];

		Utils::RemoveIf(cell.movingObjects, [&](auto& o)
		{
			static Camera& cam = Camera::Instance();
			const RectF oBbox = o->GetBBox();

			// objects IsNone are either Destroyed or Die and won't be moving, so no need to care updating
			// NOTE: but if game has objects flying around after died we should rewrite this
			if (oBbox.IsNone()) return false; 

			// Always reupdate objects on screen even on the case they move to new cell when haven't totally left old cell
			// Objects offscreen should be updated when totally leave their old cell
			if (oBbox.IsIntersect( cam.GetBBox() ) || !oBbox.IsIntersect( cell.GetBBox() ))
			{
				shouldBeUpdatedObjects.emplace(o);	
				return true;
			}
			
			return false;
		});
	}

	for (auto& obj : shouldBeUpdatedObjects)
	{
		Area area = CalcCollidableArea( obj->GetBBox() );

		for (UINT x = area.xs; x <= area.xe; x++)
		for (UINT y = area.ys; y <= area.ye; y++)
		{
			cells[x * height + y].movingObjects.emplace( obj );
		}
	}
	
	RemoveDestroyedObjects();
	RecalculateObjectsInViewPort();
}

void Grid::RenderCells() const
{
	Area area = CalcCollidableArea( Camera::Instance().GetBBox() );

	for (UINT x = area.xs; x <= area.xe; x++)
	for (UINT y = area.ys; y <= area.ye; y++)
	{
		const UINT  cellIndex = x * height + y   ;
		const Cell& cell      = cells[cellIndex] ;
		const RectF cellBbox  = cell.GetBBox()   ;

		DebugDraw::DrawRectOutLine( cellBbox, Colors::DimGray ); // cells outline

		DebugDraw::DrawSolidRect( cellBbox.Clone().Trim(0, 0, 115, 123), Colors::DimGray ); // background for string

		const Vector2 cellDrawPosition = cellBbox.GetTopLeft() + Vector2{ 2.5f, 0.5f };

		static std::ostringstream os; os.str("");
		os << "index: " << cellIndex << "\n"
		   << "static: " << cell.staticObjects.size() << "\n"
		   << "moving: " << cell.movingObjects.size();

		DebugDraw::DrawString( os.str(), cellDrawPosition, Colors::White ); // actual string
	}
}
