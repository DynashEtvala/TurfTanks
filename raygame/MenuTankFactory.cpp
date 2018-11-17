#include "MenuTankFactory.h"



MenuTankFactory::MenuTankFactory()
{}


void MenuTankFactory::operator=(MenuTankFactory const&)
{}


MenuTankFactory::~MenuTankFactory()
{}


void MenuTankFactory::Initialize(Texture2D* _body, Texture2D* _barrel, Texture2D* _hub)
{
	body = _body;
	barrel = _barrel;
	hub = _hub;
	tanks.push_back(MenuTank{ body, barrel, hub });
	tanks.back().Initialize(Vector2{ (float)(GetRandomValue(200, 1600)), (float)(GetScreenHeight()) + 60 }, (float)(GetRandomValue(50, 100)), colors[GetRandomValue(0, 5)]);
}


MenuTankFactory& MenuTankFactory::GetInstance()
{
	static MenuTankFactory instance;
	return instance;
}


void MenuTankFactory::Update(float delta_t)
{
	if (spawnTimer < 1)
	{
		spawnTimer += delta_t;
	}
	else
	{
		for (auto iter = tanks.begin(); iter != tanks.end(); iter++)
		{
			if (!iter->active)
			{
				iter->Initialize(Vector2{ (float)(GetRandomValue(200, 1600)), (float)(GetScreenHeight()) + 60 }, (float)(GetRandomValue(50, 100)), colors[GetRandomValue(0, 5)]);
				break;
			}
			if ((iter + 1) == tanks.end())
			{
				tanks.push_back(MenuTank{body, barrel, hub});
				tanks.back().Initialize(Vector2{ (float)(GetRandomValue(200, 1600)), (float)(GetScreenHeight()) + 60 }, (float)(GetRandomValue(50, 100)), colors[GetRandomValue(0, 5)]);
				break;
			}
		}
		spawnTimer -= 1;
	}
	for (auto iter = tanks.begin(); iter != tanks.end(); iter++)
	{
		if (iter->active)
		{
			iter->Update(delta_t);
		}
	}
}


void MenuTankFactory::Draw(float delta_t)
{
	for (auto iter = tanks.begin(); iter != tanks.end(); iter++)
	{
		if (iter->active)
		{
			iter->Draw(delta_t);
		}
	}
}

