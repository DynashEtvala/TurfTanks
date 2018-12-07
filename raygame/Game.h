#pragma once
#include <vector>
#include "Sprite.h"
class Game
{
private:
	std::vector<Sprite> obsticles;
	Texture2D* wall;
	Texture2D* pit;
	Texture2D* spawn;
	Texture2D* body;
	Texture2D* hub;
	Texture2D* barrel;
public:
	Game();
	Game(Texture2D* _wall, Texture2D* _pit, Texture2D* _spawn, Texture2D* _body, Texture2D* _hub, Texture2D* _barrel);
	~Game();
	void initialize();
};

