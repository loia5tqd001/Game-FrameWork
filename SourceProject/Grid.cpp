#include "pch.h"
#include "Goomba.h"
#include "Block.h"

Grid::Grid(const Json::Value& root)
{
	LoadResources(root);
}

auto Grid::LoadObjects(const Json::Value& grid)
{
	std::vector<GameObject*> staticObjects;
	std::vector<GameObject*> movingObjects;

	const Json::Value& jsonObjects = grid["objects"];
	objectHolder.reserve( jsonObjects.size() );

	for (const auto& jsonObj : jsonObjects)
	{
		const UINT  classId  = jsonObj[0].asUInt ();
		const bool  isStatic = jsonObj[1].asBool ();
		const float x        = jsonObj[2].asFloat();
		const float y        = jsonObj[3].asFloat();
		const UINT  width    = jsonObj[4].asInt  ();
		const UINT  height   = jsonObj[5].asInt  ();
		const float vx       = jsonObj[6].asFloat();
		const float vy       = jsonObj[7].asFloat();
		const float nx       = jsonObj[8].asFloat();

		static std::unique_ptr<GameObject> object;
		switch ((ClassId)classId)
		{
			case ClassId::Block:
				object = std::make_unique<Block>( Vector2{x, y}, width, height );
				break;

			case ClassId::Goomba:
				object = std::make_unique<Goomba>( Vector2{x, y}, Vector2{vx, 0.0f} );
				break;

			default:
				ThrowMyException("Can't find class id:", classId);
				break;
		}

		if (isStatic) staticObjects.emplace_back( object.get() );
		else          movingObjects.emplace_back( object.get() );

		objectHolder.emplace_back( std::move(object) );
	}

	return std::make_pair(staticObjects, movingObjects);
}

void Grid::LoadResources(const Json::Value& root)
{		
	const Json::Value& grid = root["grid"];
	cellSize = grid["cellsize"].asUInt();
	width    = grid["width"   ].asUInt();
	height   = grid["height"  ].asUInt();

	cells.resize(width * height);
	for (UINT x = 0; x < width; x++)
	for (UINT y = 0; y < height; y++)
	{
		cells[x * height + y].boundingBox = { float(x * cellSize), float(y * cellSize), cellSize, cellSize };
	}

	const auto [staticObjs, movingObjs] = LoadObjects(grid);

	for (const auto& obj : staticObjs)
	{
		const auto objBbox = obj->GetBBox();
		const auto cellsObjectBelong = CalcCollidableArea( objBbox );
		for (UINT x = cellsObjectBelong.xs; x <= cellsObjectBelong.xe; x++)
		for (UINT y = cellsObjectBelong.ys; y <= cellsObjectBelong.ye; y++)
		{
			auto& cell = cells[x * height + y];
			assert(objBbox.IsIntersect( cell.GetBBox() ));
			cell.staticObjects.emplace( obj );
		}
	}

	for (const auto& obj : movingObjs)
	{
		const auto objBbox = obj->GetBBox();
		const auto cellsObjectBelong = CalcCollidableArea( objBbox );
		for (UINT x = cellsObjectBelong.xs; x <= cellsObjectBelong.xe; x++)
		for (UINT y = cellsObjectBelong.ys; y <= cellsObjectBelong.ye; y++)
		{
			auto& cell = cells[x * height + y];
			assert(objBbox.IsIntersect( cell.GetBBox() ));
			cell.movingObjects.emplace( obj );
		}
	}
}

Area Grid::CalcCollidableArea(const RectF& bbox) const
{
	return 	{
		UINT(max(0         ,      bbox.left   / cellSize      )),
		UINT(min(width  - 1, ceil(bbox.right  / cellSize) - 1 )),
		UINT(max(0         ,      bbox.top    / cellSize      )),
		UINT(min(height - 1, ceil(bbox.bottom / cellSize) - 1 ))
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

void Grid::UpdateCells()
{
	// recalculate viewPortArea every frame
	viewPortArea = CalcCollidableArea( Camera::Instance().GetBBox() );

	std::unordered_set<GameObject*> shouldBeUpdatedObjects;
	bool hasDestroyedObject = false;

	for (UINT x = viewPortArea.xs; x <= viewPortArea.xe; x++)
		for (UINT y = viewPortArea.ys; y <= viewPortArea.ye; y++)
		{
			Cell& cell = cells[x * height + y];
			if (cell.movingObjects.size() == 0) continue;

			Utils::RemoveIf(cell.movingObjects, [&](auto& o)
			{
				static Camera& cam = Camera::Instance();
				const RectF oBbox = o->GetBBox();

				if (o->GetState() == State::Destroyed) hasDestroyedObject = true;

				// objects IsNone are either Destroyed or Die and won't be moving, so no need to care updating
				// NOTE: but if game has objects flying around after died we should rewrite this
				if (oBbox.IsNone()) return false; 

				// Objects offscreen should be updated when totally left their old cell
				if ( !oBbox.IsIntersect(cell.GetBBox()) )
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

	if (hasDestroyedObject) RemoveDestroyedObjects();
	RecalculateObjectsInViewPort();
}

void Grid::RemoveDestroyedObjects()
{
	for (UINT x = viewPortArea.xs; x <= viewPortArea.xe; x++)
	for (UINT y = viewPortArea.ys; y <= viewPortArea.ye; y++)
	{
		Cell& cell = cells[x * height + y];
		Utils::RemoveIf(cell.movingObjects, [](auto o) { return o->GetState() == State::Destroyed;} );
	}

	Utils::RemoveIf(objectHolder, [](auto& o) { return o->GetState() == State::Destroyed; });
}

void Grid::RecalculateObjectsInViewPort()
{
	std::unordered_set<GameObject*> result;

	for (UINT x = viewPortArea.xs; x <= viewPortArea.xe; x++)
	for (UINT y = viewPortArea.ys; y <= viewPortArea.ye; y++)
	{
		const Cell& cell = cells[x * height + y];
		result.insert(cell.staticObjects.begin(), cell.staticObjects.end());
		result.insert(cell.movingObjects.begin(), cell.movingObjects.end());
	}

	curObjectsInViewPort = { result.begin(), result.end() };
}

void Grid::RenderCells() const
{
	for (UINT x = viewPortArea.xs; x <= viewPortArea.xe; x++)
	for (UINT y = viewPortArea.ys; y <= viewPortArea.ye; y++)
	{
		const UINT  cellIndex = x * height + y   ;
		const Cell& cell      = cells[cellIndex] ;
		const RectF cellBbox  = cell.GetBBox()   ;

		DebugDraw::DrawRectOutLine( cellBbox, Colors::LightGray ); // cells outline

		DebugDraw::DrawSolidRect( { cellBbox.GetTopLeft(), 45, 37 }, Colors::LightGray ); // background for string

		const Vector2 cellDrawPosition = cellBbox.GetTopLeft() + Vector2{ 2.5f, 0.5f };

		static std::ostringstream os; os.str("");
		os << "index: " << cellIndex << "\n"
		   << "static: " << cell.staticObjects.size() << "\n"
		   << "moving: " << cell.movingObjects.size();

		DebugDraw::DrawString( os.str(), cellDrawPosition, Colors::White ); // actual string
	}
}
