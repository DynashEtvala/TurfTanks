#pragma once
#include "MenuTank.h"
#include <vector>
class MenuTankFactory
{
private:
	MenuTankFactory();
	MenuTankFactory(MenuTankFactory const&);
	void operator=(MenuTankFactory const&);
	MenuTank** free;
	MenuTank** used;
	size_t freeCount;
	size_t usedCount;
	size_t total;
	float spawnTimer = 0;
	Color colors[6] = { Color{255, 0, 0, 255}, Color{ 255, 255, 0, 255 }, Color{ 0, 255, 0, 255 }, Color{ 0, 255, 255, 255 }, Color{ 0, 0, 255, 255 }, Color{ 255, 0, 255, 255 } };
	Texture2D* body;
	Texture2D* barrel;
	Texture2D* hub;
public:
	static MenuTankFactory& GetInstance();
	void Initialize(Texture2D* _body, Texture2D* _barrel, Texture2D* _hub);
	void Update(float delta_t);
	void Draw(float delta_t);
	~MenuTankFactory();
};

