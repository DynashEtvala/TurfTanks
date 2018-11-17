#pragma once
#include "Sprite.h"
class Tank
{
protected:
	Sprite body;
	Sprite hub;
	Sprite barrel;
	Vector2 centerPos;
	Vector2 bodyDir;
	Vector2 barrelDir;
	Color tint;
public:
	Tank();
	Tank(Texture2D* _body, Texture2D* _hub, Texture2D* _barrel, Vector2 _start, Color _tint);
	~Tank();
	virtual void Update(float delta_t);
	virtual void Draw(float delta_t);
};

