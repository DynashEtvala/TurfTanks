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

	//ShowLogo();
	InitWindow(screenWidth, screenHeight, "Turf Tanks");
	HideCursor();

	GState curState;
	float delta_t;

	Texture2D* tBodyTex = new Texture2D(LoadTexture("sprites/tankBody.png"));
	Texture2D* tBarrelTex = new Texture2D(LoadTexture("sprites/tankBarrel.png"));
	Texture2D* tHubTex = new Texture2D(LoadTexture("sprites/tankHub.png"));

	Texture2D* bulletTex = new Texture2D(LoadTexture("sprites/bullet.png"));

	Texture2D* groundTex = new Texture2D(LoadTexture("sprites/ground.png"));

	Texture2D* buttonTex = new Texture2D(LoadTexture("sprites/button.png"));
	Texture2D* tokenTex = new Texture2D(LoadTexture("sprites/playerToken.png"));
	Texture2D* panelTex = new Texture2D(LoadTexture("sprites/panel.png"));

	MenuTankFactory::GetInstance().Initialize(tBodyTex, tBarrelTex, tHubTex);

	Tank test = { tBodyTex, tHubTex, tBarrelTex, {500, 500}, WHITE };

	Color playerColors[4] = { RED, BLUE, GREEN, YELLOW };

	int controlPlayer = 0;

	MainMenu mainMenu;
	
	Sprite menuBG = Sprite{ groundTex, Point{ 0, 0 }, Point{ groundTex->width * 28, groundTex->height * 16 }, Vector2{ 0, 0 }, 50.0f / 128.0f, WHITE, Point{ 1, 1}, 0, Vector2{ 0, 0}, 0 };

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose() && !exit)    // Detect window close button or ESC key
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
			for (int i = 0; i < 4; i++)
			{
				if (IsGamepadButtonReleased(i, GAMEPAD_XBOX_BUTTON_START))
				{
					GameState::setState(Menu);
					controlPlayer = i;
				}
			}
			menuBG.pos.x--;
			if (menuBG.pos.x < -50)
			{
				menuBG.pos.x += 50;
			}
			MenuTankFactory::GetInstance().Update(delta_t);
			break;
		case Menu:
			if (IsGamepadButtonReleased(controlPlayer, GAMEPAD_XBOX_BUTTON_A))
			{
				GameState::setState(mainMenu.GetCur()->state);
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
			menuBG.pos.x--;
			if (menuBG.pos.x < -50)
			{
				menuBG.pos.x += 50;
			}
			break;
		case Options:
			if (IsGamepadButtonReleased(controlPlayer, GAMEPAD_XBOX_BUTTON_B))
			{
				GameState::setState(Menu);
			}
			menuBG.pos.x--;
			if (menuBG.pos.x < -50)
			{
				menuBG.pos.x += 50;
			}
			break;
		case PlayerSelect:
			if (IsGamepadButtonReleased(controlPlayer, GAMEPAD_XBOX_BUTTON_B))
			{
				GameState::setState(Menu);
			}
			
			menuBG.pos.x--;
			if (menuBG.pos.x < -50)
			{
				menuBG.pos.x += 50;
			}
			break;
		case MapSelect:
			if (IsGamepadButtonReleased(controlPlayer, GAMEPAD_XBOX_BUTTON_B))
			{
				GameState::setState(PlayerSelect);
			}
			menuBG.pos.x--;
			if (menuBG.pos.x < -50)
			{
				menuBG.pos.x += 50;
			}
			break;
		case InGame:
			break;
		case GameOver:
			break;
		case Exit:
			exit = true;
			break;
		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		switch (curState)
		{
		default:
		case Splash:
			menuBG.Draw(delta_t);
			MenuTankFactory::GetInstance().Draw(delta_t);
			DrawText("PRESS START", screenWidth / 2 - MeasureText("PRESS START", 50) / 2, 700, 50, Color{ 0, 0, 0, (unsigned char)(((int)GetTime() % 2) * 255) });
			DrawText("Turf Tanks", screenWidth / 2 - MeasureText("Turf Tanks", 100) / 2, 100, 100, Color{ 20, 127, 20, 255 });
			break;
		case Menu:
			menuBG.Draw(delta_t);
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
			menuBG.Draw(delta_t);
			break;
		case PlayerSelect:
			menuBG.Draw(delta_t);
			DrawTexturePro(*panelTex, Rectangle{ 0, 0, (float)(panelTex->width), (float)(panelTex->height) }, Rectangle{ 450, 300, 150, 400 }, Vector2{ 0, 0 }, 0, GREEN);
			DrawTexturePro(*panelTex, Rectangle{ 0, 0, (float)(panelTex->width), (float)(panelTex->height) }, Rectangle{ 625, 300, 50, 400 }, Vector2{ 0, 0 }, 0, WHITE);
			DrawTexturePro(*panelTex, Rectangle{ 0, 0, (float)(panelTex->width), (float)(panelTex->height) }, Rectangle{ 700, 300, 150, 400 }, Vector2{ 0, 0 }, 0, PINK);
			break;
		case MapSelect:
			menuBG.Draw(delta_t);
			break;
		case InGame:
			break;
		case GameOver:
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