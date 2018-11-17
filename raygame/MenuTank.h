#pragma once
#include "Tank.h"
class MenuTank :
	public Tank
{
private:
	float spd;
public:
	MenuTank();
	MenuTank(Texture2D* _body, Texture2D* _barrel, Texture2D* _hub);
	~MenuTank();
	virtual void Update(float delta_t);
	virtual void Draw(float delta_t);
	void Initialize(Vector2 _pos, float _spd, Color _tint);
};

