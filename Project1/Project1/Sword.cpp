#include "Sword.h"

#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Texture.h"

void Sword::Create()
{
	Sprite::Create(this, Texture::Load("imgs/xord.png", 24, 24, 0, 0, 0, 1));
	Animation::Add(this, "idle", "0", true);
	Animation::Add(this, "move", "0-4x4", false);
	Movement::Set(this, 2.3, 10);
}
void Sword::Update()
{
	if (Wealder)
	{
		int a, b;
		double x, y;
		SDL_GetMouseState(&a, &b);
		x = Wealder->X;
		y = Wealder->Y - 24;
		double ang = (atan2(b - y, a - x) * 180 / M_PI) + 90;
		Get_Sprite()->Rotation = ang;
		X = Wealder->X - cos(ang * M_PI / 180 + M_PI / 2) * 40;
		Y = Wealder->Y - 24 - sin(ang * M_PI / 180 + M_PI / 2) * 40;
		if (abs(ang - Old_Angle) > 5)
		{
			if (ang < Old_Angle) Get_Sprite()->Flip = SDL_FLIP_HORIZONTAL;
			if (ang > Old_Angle) Get_Sprite()->Flip = SDL_FLIP_NONE;
		}
		Old_Angle = ang;
	}
}
void Sword::Events()
{

}