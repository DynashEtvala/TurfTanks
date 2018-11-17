#pragma once
#include "raylib.h"
#include "Helpers.h"

class Sprite
{
public:
	Texture2D* tex;
	Point frame;
	Point frameCount;
	Point frameSize;
	Vector2 pos;
	Vector2 orig;
	Color tint;
	float scale;
	float rot;
	float spf;
	float ftime = 0;
	Sprite();
	Sprite(Texture2D* _tex, Point _frame, Point _frameSize, Vector2 _pos, float _scale, Color tint);
	Sprite(Texture2D* _tex, Point _frame, Point _frameSize, Vector2 _pos, float _scale, Color tint, Point _frameCount, float _spf);
	Sprite(Texture2D* _tex, Point _frame, Point _frameSize, Vector2 _pos, float _scale, Color tint, Point _frameCount, float _spf, Vector2 _orig, float _rot);
	~Sprite();
	virtual void Update(float delta_t);
	virtual void Draw(float delta_t);
};

