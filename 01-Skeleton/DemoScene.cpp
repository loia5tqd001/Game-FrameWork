#include "pch.h"
#include "DemoScene.h"
#include "Textures.h"
#include "Sprites.h"
#include "Brick.h"
#include "Goomba.h"
#include "Camera.h"

// Learn more about jsoncpp: https://github.com/open-source-parsers/jsoncpp
void DemoScene::LoadResources()
{
	static constexpr char* jsonPath = "textures\\db.json";

	std::ifstream jsonFile(jsonPath);
	if (!jsonFile.is_open())
		ThrowMyException("Can't open json file", jsonPath);

	Json::Reader reader;
	Json::Value  root;
	if (!reader.parse(jsonFile, root))
	{
		LPCSTR msg = reader.getFormattedErrorMessages().c_str();
		ThrowMyException("Parse json file failed:", msg);
	}

	for (UINT i = 0; i < (UINT)TextureType::Count; i++)
		Textures::Add(TextureType(i), root);

	for (UINT i = 0; i < (UINT)SpriteType::Count; i++)
		Sprites::Add(SpriteType(i), root);

	map = std::make_unique<Map>(root);

	LoadObjects();
}

void DemoScene::Update(float dt)
{
	static auto getCollidableObjects = [this]()
	{
		std::vector<LPCGAMEOBJECT> coObjects;
		coObjects.reserve(goombas.size() + bricks.size());

		for (const auto& goomba : goombas)
		{
			coObjects.emplace_back(goomba.get());
		}
		for (const auto& brick : bricks)
		{
			coObjects.emplace_back(brick.get());
		}
		return coObjects;
	};

	mario->Update(dt, getCollidableObjects());
	Camera::Instance().CenterTo(mario->GetCenter());

	for (const auto& goomba : goombas)
	{
		goomba->Update(dt);
	}
	for (const auto& brick : bricks)
	{
		brick->Update(dt);
	}
}
void DemoScene::Draw()
{
	map->Render();
	mario->Render();
	for (const auto& goomba : goombas)
	{
		goomba->Render();
	}
	for (const auto& brick : bricks)
	{
		brick->Render();
	}
}

void DemoScene::LoadObjects()
{
	mario = std::make_unique<Mario>(Point(10.0f, 10.0f, 0.0f));

	goombas.reserve(3);
	goombas.emplace_back(std::make_unique<Goomba>(Point(200.0f, 209.0f, 0.0f)));
	goombas.emplace_back(std::make_unique<Goomba>(Point(260.0f, 209.0f, 0.0f)));
	goombas.emplace_back(std::make_unique<Goomba>(Point(320.0f, 209.0f, 0.0f)));

	bricks.reserve(35);
	for (UINT i = 0; i < 20; i++)
	{
		bricks.emplace_back(std::make_unique<Brick>(Point(16.0f * i, 224.0f, 0.0f)));
	}
	for (UINT i = 0; i < 5; i++)
	{
		bricks.emplace_back(std::make_unique<Brick>(Point(80.0f + i * 48.0f, 149.0f, 0.0f)));
		bricks.emplace_back(std::make_unique<Brick>(Point(80.0f + i * 48.0f, 165.0f, 0.0f)));
		bricks.emplace_back(std::make_unique<Brick>(Point(64.0f + i * 48.0f, 165.0f, 0.0f)));
	}
}


