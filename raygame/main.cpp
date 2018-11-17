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

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1300;
	int screenHeight = 800;
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

	MenuTankFactory::GetInstance().Initialize(tBodyTex, tBarrelTex, tHubTex);

	Tank test = { tBodyTex, tHubTex, tBarrelTex, {500, 500}, WHITE };

	int controlPlayer = 0;
	
	Sprite menuBG = Sprite{ groundTex, Point{ 0, 0 }, Point{ groundTex->width * 28, groundTex->height * 16 }, Vector2{ 0, 0 }, 50.0f / 128.0f, WHITE, Point{ 1, 1}, 0, Vector2{ 0, 0}, 0 };

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
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
					GameState::setState(MainMenu);
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
		case MainMenu:
			menuBG.pos.x--;
			if (menuBG.pos.x < -50)
			{
				menuBG.pos.x += 50;
			}
			break;
		case Options:
			menuBG.pos.x--;
			if (menuBG.pos.x < -50)
			{
				menuBG.pos.x += 50;
			}
			break;
		case PlayerSelect:
			menuBG.pos.x--;
			if (menuBG.pos.x < -50)
			{
				menuBG.pos.x += 50;
			}
			break;
		case MapSelect:
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
		case MainMenu:
			menuBG.Draw(delta_t);
			DrawText("Turf Tanks", screenWidth / 2 - MeasureText("Turf Tanks", 100) / 2, 100, 100, Color{ 20, 127, 20, 255 });
			break;
		case Options:
			break;
		case PlayerSelect:
			break;
		case MapSelect:
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
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}