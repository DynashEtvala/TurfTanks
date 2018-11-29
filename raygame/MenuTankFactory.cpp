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
		free[i] = new MenuTank(_body, _barrel, _hub);
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
			used[usedCount]->Initialize(Vector2{ (float)(GetRandomValue(0, 1300) + 400), 850.0f }, (float)(GetRandomValue(25, 50)), colors[GetRandomValue(0, 5)]);
			usedCount++;
			for (int i = 0; i < freeCount - 1; i++)
			{
				free[i] = free[i + 1];
			}
			freeCount--;
		}/*
		else
		{
			MenuTank** tempF = used;
			used = new MenuTank*[total + 1];
			free = new MenuTank*[total + 1];
			for (int i = 0; i < total; i++)
			{
				free[i] = tempF[i];
			}
			free[total] = new MenuTank(body, barrel, hub);
			free[total]->Initialize(Vector2{ (float)(GetRandomValue(0, 1300) + 400), 850.0f }, (float)(GetRandomValue(25, 50)), colors[GetRandomValue(0, 5)]);
			total++;
			delete[] tempF;
		}*/
		spawnTimer -= 1;
	}
	for (int i = 0; i < usedCount; i++)
	{
		used[i]->Update(delta_t);
	}
	for (int i = 0; i < usedCount; i++)
	{
		if (used[i]->centerPos.y < -50)
		{
			free[freeCount] = used[i];
			freeCount++;
			for (int j = i; j < usedCount - 1; j++)
			{
				used[j] = used[j + 1];
			}
			usedCount--;
			i--;
		}
	}
}


void MenuTankFactory::Draw(float delta_t)
{
	for (int i = 0; i < usedCount; i++)
	{
		used[i]->Draw(delta_t);
	}
}

