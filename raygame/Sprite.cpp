#include "Sprite.h"



Sprite::Sprite()
{
	tex = nullptr;
	frame = Point{ 0, 0 };
	frameSize = Point{ 0, 0 };
	pos = Vector2{ 0, 0 };
	scale = 0;
	tint = BLANK;
	frameCount = Point{ 0, 0 };
	spf = 0;
	orig = Vector2{ 0, 0 };
	rot = 0;
}


Sprite::Sprite(Texture2D* _tex, Point _frame, Point _frameSize, Vector2 _pos, float _scale, Color _tint)
{
	tex = _tex;
	frame = _frame;
	frameSize = _frameSize;
	pos = _pos;
	scale = _scale;
	tint = _tint;
	frameCount = Point{ 1, 1 };
	spf = 0;
	orig = Vector2{ _frameSize.x * 0.5f, _frameSize.y * 0.5f };
	rot = 0;
}


Sprite::Sprite(Texture2D* _tex, Point _frame, Point _frameSize, Vector2 _pos, float _scale, Color _tint, Point _frameCount, float _spf)
{
	tex = _tex;
	frame = _frame;
	frameSize = _frameSize;
	pos = _pos;
	scale = _scale;
	tint = _tint;
	frameCount = _frameCount;
	spf = _spf;
	orig = Vector2{ _frameSize.x * 0.5f, _frameSize.y * 0.5f };
	rot = 0;
}


Sprite::Sprite(Texture2D* _tex, Point _frame, Point _frameSize, Vector2 _pos, float _scale, Color _tint, Point _frameCount, float _spf, Vector2 _orig, float _rot)
{
	tex = _tex;
	frame = _frame;
	frameSize = _frameSize;
	pos = _pos;
	scale = _scale;
	tint = _tint;
	frameCount = _frameCount;
	spf = _spf;
	orig = _orig;
	rot = _rot;
}


Sprite::~Sprite()
{}


void Sprite::Update(float delta_t)
{
	if (spf > 0)
	{
		ftime += delta_t;
		if (ftime >= spf)
		{
			ftime -= spf;
			frame.x++;
			if (frame.x >= frameCount.x)
			{
				frame.x = 0;
				frame.y++;
				if (frame.y >= frameCount.y)
				{
					frame.y = 0;
				}
			}
		}
	}
}


void Sprite::Draw(float delta_t)
{
	DrawTexturePro(*tex, Rectangle{ (float)(frame.x) * frameSize.x, (float)(frame.y) * frameSize.y, (float)(frameSize.x), (float)(frameSize.y) }, Rectangle{ pos.x, pos.y, frameSize.x * scale, frameSize.y * scale }, orig, rot, tint);
}




