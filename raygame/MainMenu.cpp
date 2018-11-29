#include "MainMenu.h"


Button * MainMenu::GetCur()
{
	return curButton;
}


Button* MainMenu::GetAbove()
{
	return curButton->above;
}


Button* MainMenu::GetBelow()
{
	return curButton->below;
}


void MainMenu::MoveAbove()
{
	curButton = curButton->above;
}


void MainMenu::MoveBelow()
{
	curButton = curButton->below;
}


MainMenu::MainMenu()
{
	curButton = new Button();
	curButton->state = PlayerSelect;
	curButton->text = "Play";
	curButton->above = new Button();
	curButton->above->state = Options;
	curButton->above->text = "Options";
	curButton->above->below = curButton;
	curButton->below = new Button();
	curButton->below->state = Exit;
	curButton->below->text = "Exit";
	curButton->below->above = curButton;
	curButton->below->below = curButton->above;
	curButton->above->above = curButton->below;
}


MainMenu::~MainMenu()
{
	delete curButton->above;
	delete curButton->below;
	delete curButton;
}
