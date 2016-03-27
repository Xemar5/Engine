#include "Sword.h"

#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Texture.h"
#include "System.h"
#include "Hitbox.h"
#include <SDL.h>

void Sword::Create()
{
	Sprite::Create(this, Texture::Load("imgs/xord.png", 24, 24, 24, 24, 0, 1));
	Animation::Add(this, "idle", "0", true);
	Animation::Add(this, "move", "0-4x4", false);
	Movement::Set(this, 2.3, 10);
}
void Sword::Update()
{
	if (__Swinging)
	{
		if(__On_Left < 0) __Angle_Offset += Swing_Speed;
		else __Angle_Offset -= Swing_Speed;

		if (abs(__Angle_Offset) > Max_Swing)
		{
			__Swinging = false;
			__Angle_Offset = 0;
			__On_Left = -__On_Left;
		}
	}
	if (Wealder)
	{
		int a, b;
		double x, y;
		SDL_GetMouseState(&a, &b);
		x = Wealder->X;
		y = Wealder->Y - 8 * Screen::Get_Scale();
		double ang = (atan2(b - y, a - x) * 180 / M_PI) + 90 + (Max_Swing / 2 * __On_Left)+ __Angle_Offset;
		Get_Sprite()->Rotation = ang;
		X = Wealder->X - cos(ang * M_PI / 180 + M_PI / 2) * 40;
		Y = Wealder->Y - 8 * Screen::Get_Scale() - sin(ang * M_PI / 180 + M_PI / 2) * 40;
		if (abs(ang - __Old_Angle) > 5)
		{
			if (ang < __Old_Angle) Get_Sprite()->Flip = SDL_FLIP_HORIZONTAL;
			if (ang > __Old_Angle) Get_Sprite()->Flip = SDL_FLIP_NONE;
		}
		__Old_Angle = ang;
	}
}
void Sword::Events()
{
	if (System::Events.type == SDL_MOUSEBUTTONDOWN)
		__Swinging = true;
}