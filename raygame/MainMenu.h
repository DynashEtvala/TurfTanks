#pragma once
#include "GameState.h"
#include <string>

struct Button
{
	GState state;
	Button* above;
	Button* below;
	std::string text;
};

class MainMenu
{
private:
	Button* curButton;
public:
	Button * GetCur();
	Button* GetAbove();
	Button* GetBelow();
	void MoveAbove();
	void MoveBelow();
	MainMenu();
	~MainMenu();
};

