#pragma once

enum GState { Splash = 0, Menu, PlayerSelect, MapSelect, InGame, GameOver, Options, Exit };

class GameState
{
private:
	GameState();
	GameState(GameState const&);  // prevents external use
	void operator=(GameState const&); // prevents external use
	GState state;

public:
	static GState getState();
	static GState setState(GState newState);
	static GameState& GetInstance();
	~GameState();
};
