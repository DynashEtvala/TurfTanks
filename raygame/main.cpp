/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "GameState.h"
#include "Sprite.h"
#include "MenuTankFactory.h"
#include "MainMenu.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1300;
	int screenHeight = 800;

	bool exit = false;

	ShowLogo();
	InitWindow(screenWidth, screenHeight, "Turf Tanks");
	HideCursor();

	GState curState = GameState::setState(InGame);
	float delta_t;

	//Set up textures
	Texture2D* tBodyTex = new Texture2D(LoadTexture("sprites/tankBody.png"));
	Texture2D* tBarrelTex = new Texture2D(LoadTexture("sprites/tankBarrel.png"));
	Texture2D* tHubTex = new Texture2D(LoadTexture("sprites/tankHub.png"));

	Texture2D* bulletTex = new Texture2D(LoadTexture("sprites/bullet.png"));

	Texture2D* groundTex = new Texture2D(LoadTexture("sprites/ground.png"));

	Texture2D* buttonTex = new Texture2D(LoadTexture("sprites/button.png"));
	Texture2D* tokenTex = new Texture2D(LoadTexture("sprites/playerToken.png"));
	Texture2D* panelTex = new Texture2D(LoadTexture("sprites/panel.png"));


	//MenuTankFactory::GetInstance().Initialize(tBodyTex, tBarrelTex, tHubTex);

	//Player info initialization
	Color playerColors[4] = { RED, BLUE, GREEN, YELLOW };

	int playerTokenLocation[4] = { 1, 1, 1, 1 };

	int controlPlayer = 0;

	//menu setup
	MainMenu mainMenu;
	
	Sprite background = Sprite{ groundTex, Point{ 0, 0 }, Point{ groundTex->width * 28, groundTex->height * 16 }, Vector2{ 0, 0 }, 50.0f / 128.0f, WHITE, Point{ 1, 1}, 0, Vector2{ 0, 0}, 0 };

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose() && !exit)    // Detect window close button or ESC key or exit condition is true
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------
		curState = GameState::getState();
		delta_t = GetFrameTime();

		switch (curState)
		{
		default:
		case Splash:
			//check for player pressing start
			for (int i = 0; i < 4; i++)
			{
				if (IsGamepadButtonReleased(i, GAMEPAD_XBOX_BUTTON_START))
				{
					GameState::setState(Menu);
					controlPlayer = i;
				}
			}
			//move background
			background.pos.x--;
			if (background.pos.x < -50)
			{
				background.pos.x += 50;
			}
			MenuTankFactory::GetInstance().Update(delta_t);
			break;
		case Menu:
			//menu navigation
			if (IsGamepadButtonReleased(controlPlayer, GAMEPAD_XBOX_BUTTON_A))
			{
				GameState::setState(mainMenu.GetCur()->state);
				if (GameState::getState() == PlayerSelect)
				{
					for (int i = 0; i < 4; i++)
					{
						playerTokenLocation[i] = 1;
					}
				}
			}
			else if (IsGamepadButtonReleased(controlPlayer, GAMEPAD_XBOX_BUTTON_B))
			{
				GameState::setState(Splash);
			}
			else if (IsGamepadButtonReleased(controlPlayer, GAMEPAD_XBOX_BUTTON_DOWN))
			{
				mainMenu.MoveBelow();
			}
			else if (IsGamepadButtonReleased(controlPlayer, GAMEPAD_XBOX_BUTTON_UP))
			{
				mainMenu.MoveAbove();
			}
			//move background
			background.pos.x--;
			if (background.pos.x < -50)
			{
				background.pos.x += 50;
			}
			break;
		case Options:
			//menu navigation
			if (IsGamepadButtonReleased(controlPlayer, GAMEPAD_XBOX_BUTTON_B))
			{
				GameState::setState(Menu);
			}
			//move background
			background.pos.x--;
			if (background.pos.x < -50)
			{
				background.pos.x += 50;
			}
			break;
		case PlayerSelect:
			//menu navigation
			if (IsGamepadButtonReleased(controlPlayer, GAMEPAD_XBOX_BUTTON_B))
			{
				GameState::setState(Menu);
			}
			
			//player team select
			for (int i = 0; i < 4; i++)
			{
				if (IsGamepadButtonPressed(i, GAMEPAD_XBOX_BUTTON_LEFT))
				{
					playerTokenLocation[i] = 0;
				}
				else if (IsGamepadButtonPressed(i, GAMEPAD_XBOX_BUTTON_RIGHT))
				{
					playerTokenLocation[i] = 2;
				}
			}
			//confirm teams
			if (IsGamepadButtonPressed(controlPlayer, GAMEPAD_XBOX_BUTTON_START))
			{
				//check if both teams have players
				int team1Count = 0, team2Count = 0;
				for (int i = 0; i < 4; i++)
				{
					if (IsGamepadAvailable(i))
					{
						if (playerTokenLocation[i] == 0)
						{
							team1Count++;
						}
						else if (playerTokenLocation[i] == 2)
						{
							team2Count++;
						}
					}
				}
				if (team1Count > 0 && team2Count > 0)
				{
					GameState::setState(MapSelect);
				}
			}
			//move background
			background.pos.x--;
			if (background.pos.x < -50)
			{
				background.pos.x += 50;
			}
			break;
		case MapSelect:
			//menu navigation
			if (IsGamepadButtonReleased(controlPlayer, GAMEPAD_XBOX_BUTTON_B))
			{
				GameState::setState(PlayerSelect);
			}
			//move background
			background.pos.x--;
			if (background.pos.x < -50)
			{
				background.pos.x += 50;
			}
			break;
		case InGame:
			break;
		case GameOver:
			break;
		case Exit:
			// exit the game
			exit = true;
			break;
		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		switch (curState)
		{
		default:
		case Splash:
			background.Draw(delta_t);
			//MenuTankFactory::GetInstance().Draw(delta_t);
			DrawText("PRESS START", screenWidth / 2 - MeasureText("PRESS START", 50) / 2, 700, 50, Color{ 0, 0, 0, (unsigned char)(((int)GetTime() % 2) * 255) });
			DrawText("Turf Tanks", screenWidth / 2 - MeasureText("Turf Tanks", 100) / 2, 100, 100, Color{ 20, 127, 20, 255 });
			break;
		case Menu:
			background.Draw(delta_t);
			DrawText("Turf Tanks", screenWidth / 2 - MeasureText("Turf Tanks", 100) / 2, 100, 100, Color{ 20, 127, 20, 255 });
			//current menu button
			DrawTexturePro(*buttonTex, Rectangle{ 0, 0, (float)(buttonTex->width), (float)(buttonTex->height) }, Rectangle{ (float)(screenWidth / 2 - MeasureText(mainMenu.GetCur()->text.c_str(), 40) / 2 - 10), 490, (float)(MeasureText(mainMenu.GetCur()->text.c_str(), 40) + 20), 60 }, Vector2{ 0, 0 }, 0, Color{ 20, 127, 20, 128 });
			DrawText(mainMenu.GetCur()->text.c_str(), screenWidth / 2 - MeasureText(mainMenu.GetCur()->text.c_str(), 40) / 2, 500, 40, BLACK);
			//above menu button
			DrawTexturePro(*buttonTex, Rectangle{ 0, 0, (float)(buttonTex->width), (float)(buttonTex->height) }, Rectangle{ (float)(screenWidth / 2 - MeasureText(mainMenu.GetCur()->above->text.c_str(), 20) / 2 - 5), 450, (float)(MeasureText(mainMenu.GetCur()->above->text.c_str(), 20) + 10), 30 }, Vector2{ 0, 0}, 0, Color{ 20, 127, 20, 128 });
			DrawText(mainMenu.GetCur()->above->text.c_str(), screenWidth / 2 - MeasureText(mainMenu.GetCur()->above->text.c_str(), 20) / 2, 455, 20, BLACK);
			//below menu button
			DrawTexturePro(*buttonTex, Rectangle{ 0, 0, (float)(buttonTex->width), (float)(buttonTex->height) }, Rectangle{ (float)(screenWidth / 2 - MeasureText(mainMenu.GetCur()->below->text.c_str(), 20) / 2 - 5), 560, (float)(MeasureText(mainMenu.GetCur()->below->text.c_str(), 20) + 10), 30 }, Vector2{ 0, 0 }, 0, Color{ 20, 127, 20, 128 });
			DrawText(mainMenu.GetCur()->below->text.c_str(), screenWidth / 2 - MeasureText(mainMenu.GetCur()->below->text.c_str(), 20) / 2, 565, 20, BLACK);
			break;
		case Options:
			background.Draw(delta_t);
			break;
		case PlayerSelect:
			background.Draw(delta_t);
			DrawTexturePro(*panelTex, Rectangle{ 0, 0, (float)(panelTex->width), (float)(panelTex->height) }, Rectangle{ 425, 300, 150, 400 }, Vector2{ 0, 0 }, 0, Color{ 0, 228, 48, 176 });
			DrawTexturePro(*panelTex, Rectangle{ 0, 0, (float)(panelTex->width), (float)(panelTex->height) }, Rectangle{ 600, 300, 100, 400 }, Vector2{ 0, 0 }, 0, Color{ 255, 255, 255, 176 });
			DrawTexturePro(*panelTex, Rectangle{ 0, 0, (float)(panelTex->width), (float)(panelTex->height) }, Rectangle{ 725, 300, 150, 400 }, Vector2{ 0, 0 }, 0, Color{ 255, 109, 194, 176 });
			if (IsGamepadAvailable(GAMEPAD_PLAYER1))
			{
				DrawTexturePro(*tokenTex, Rectangle{ 0, 0, (float)(tokenTex->width), (float)(tokenTex->height) }, Rectangle{ 500 + (float)(playerTokenLocation[GAMEPAD_PLAYER1]) * 150, 350, 75, 75 }, Vector2{ 36, 36 }, 0, RED);
			}
			if (IsGamepadAvailable(GAMEPAD_PLAYER2))
			{
				DrawTexturePro(*tokenTex, Rectangle{ 0, 0, (float)(tokenTex->width), (float)(tokenTex->height) }, Rectangle{ 500 + (float)(playerTokenLocation[GAMEPAD_PLAYER2]) * 150, 450, 75, 75 }, Vector2{ 36, 36 }, 0, BLUE);
			}
			if (IsGamepadAvailable(GAMEPAD_PLAYER3))
			{
				DrawTexturePro(*tokenTex, Rectangle{ 0, 0, (float)(tokenTex->width), (float)(tokenTex->height) }, Rectangle{ 500 + (float)(playerTokenLocation[GAMEPAD_PLAYER4]) * 150, 550, 75, 75 }, Vector2{ 36, 36 }, 0, GREEN);
			}
			if (IsGamepadAvailable(GAMEPAD_PLAYER4))
			{
				DrawTexturePro(*tokenTex, Rectangle{ 0, 0, (float)(tokenTex->width), (float)(tokenTex->height) }, Rectangle{ 500 + (float)(playerTokenLocation[GAMEPAD_PLAYER4]) * 150, 650, 75, 75 }, Vector2{ 36, 36 }, 0, YELLOW);
			}
			break;
		case MapSelect:
			background.Draw(delta_t);
			break;
		case InGame:
			break;
		case GameOver:
			break;
		case Exit:
			break;
		}

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//-------------------------------------------------------------------------------------- 
	delete tBarrelTex;
	delete tBodyTex;
	delete tHubTex;
	delete bulletTex;
	delete groundTex;
	delete buttonTex;
	delete panelTex;
	delete tokenTex;
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}