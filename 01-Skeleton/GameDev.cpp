#include "pch.h"
#include "GameDev.h"
#include "Textures.h"
#include "Sprites.h"
#include "Brick.h"
#include "Goomba.h"
#include "Camera.h"
#include "MyException.h"

// Learn more about jsoncpp: https://github.com/open-source-parsers/jsoncpp
void GameDev::LoadResources()
{
	static constexpr char* jsonPath = "textures\\db.json";

	std::ifstream jsonFile(jsonPath);
	if (!jsonFile.is_open())
	{
		DebugOut("Can't open json file: ", jsonPath, "\n");
		ThrowMyException("Can't open json file");
	}

	Json::Reader reader;
	Json::Value  root;
	if (!reader.parse(jsonFile, root))
	{
		LPCSTR msg = reader.getFormattedErrorMessages().c_str();
		DebugOut("Parse json file failed: ", msg, "\n");
		ThrowMyException(msg);
	}

	for (UINT i = 0; i < (UINT)TextureType::Count; i++)
	{
		Textures::Add(TextureType(i), root);
	}

	for (UINT i = 0; i < (UINT)SpriteType::Count; i++)
	{
		Sprites::Add(SpriteType(i), root);
	}

	map = std::make_unique<Map>(root, objects);
}

void GameDev::InitObjects()
{
	mario = std::make_unique<Mario>(D3DXVECTOR3(10.0f, 230.0f, 0.0f));

	goombas.reserve(3);
	goombas.emplace_back(std::make_unique<Goomba>(D3DXVECTOR3(200.0f, 16.0f, 0.0f)));
	goombas.emplace_back(std::make_unique<Goomba>(D3DXVECTOR3(260.0f, 16.0f, 0.0f)));
	goombas.emplace_back(std::make_unique<Goomba>(D3DXVECTOR3(320.0f, 16.0f, 0.0f)));

	bricks.reserve(35);
	for (UINT i = 0; i < 20; i++)
	{
		bricks.emplace_back(std::make_unique<Brick>(D3DXVECTOR3(16.0f * i, 0.0f, 0.0f)));
	}
	for (UINT i = 0; i < 5; i++)
	{
		bricks.emplace_back(std::make_unique<Brick>(D3DXVECTOR3(80.0f + i * 48.0f, 75.0f, 0.0f)));
		bricks.emplace_back(std::make_unique<Brick>(D3DXVECTOR3(80.0f + i * 48.0f, 59.0f, 0.0f)));
		bricks.emplace_back(std::make_unique<Brick>(D3DXVECTOR3(64.0f + i * 48.0f, 59.0f, 0.0f)));
	}
}

void GameDev::Update(float dt)
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
	Camera::Instance().CenterTo(mario->GetPosition());

	for (const auto& goomba : goombas)
	{
		goomba->Update(dt, {});
	}
	for (const auto& brick : bricks)
	{
		brick->Update(dt, {});
	}
}
void GameDev::ComposeFrame()
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


