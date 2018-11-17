#include "MenuTank.h"


MenuTank::MenuTank()
{}


MenuTank::MenuTank(Texture2D* _body, Texture2D* _barrel, Texture2D* _hub) : Tank(_body, _hub, _barrel, Vector2{-100, -100}, WHITE)
{}


MenuTank::~MenuTank()
{}


void MenuTank::Update(float delta_t)
{
	centerPos.x--;
	centerPos.y -= spd * delta_t;
}


void MenuTank::Draw(float delta_t)
{
	body.Draw(delta_t);
	barrel.Draw(delta_t);
	hub.Draw(delta_t);
}


void MenuTank::Initialize(Vector2 _pos, float _spd, Color _tint)
{
	centerPos = _pos;
	spd = _spd;
	body.tint = _tint;
	barrel.tint = _tint;
	hub.tint = _tint;
}