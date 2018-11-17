#include "Tank.h"


Tank::Tank()
{}


Tank::Tank(Texture2D* _body, Texture2D* _hub, Texture2D* _barrel, Vector2 _start, Color _tint)
{
	active = true;
	body = Sprite{ _body, Point{ 0, 0 }, Point{ _body->width, _body->height }, _start, 0.525f, _tint };
	barrel = Sprite{ _barrel, Point{ 0, 0 }, Point{ _barrel->width, _barrel->height }, _start, 0.525f, _tint, Point{ 1, 1 }, 0, Vector2{ (float)(_barrel->width) / 2 * 0.525f, (float)(_barrel->height) * 0.525f }, 0 };
	hub = Sprite{ _hub, Point{ 0, 0 }, Point{ _hub->width, _hub->height }, _start, 0.525f, _tint };
}


Tank::~Tank()
{}


void Tank::Update(float delta_t)
{

}


void Tank::Draw(float delta_t)
{
	body.Draw(delta_t);
	barrel.Draw(delta_t);
	hub.Draw(delta_t);
}



