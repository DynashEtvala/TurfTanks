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
	total = 1;
	freeCount = total;
	usedCount = 0;
	free = new MenuTank*[total];
	used = new MenuTank*[total];
	for (int i = 0; i < freeCount; i++)
	{
		free[i] = new MenuTank{ _body, _barrel, _hub };
	}
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
		if (usedCount < total)
		{
			used[usedCount] = free[0];
			for (int i = 0; i < freeCount - 1; i++)
			{
				free[i] = free[i + 1];
			}
		}
		else
		{
			MenuTank** tempF = new MenuTank*[total * 2];

		}
		spawnTimer -= 1;
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

