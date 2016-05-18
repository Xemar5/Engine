#include "Sword.h"

#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Texture.h"
#include "System.h"
#include "Hitbox.h"
#include <SDL.h>
#include "Player.h"
#include "Input_Handler.h"
#include "Mouse_Handler.h"

void Sword::Create()
{
	auto sp = Sprite::Create(this, Texture::Load("imgs/xord.png", 24, 24, 24, 24, 0, 1));
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
		double a = Wealder->Input_Preset["raright"]->Check() - Wealder->Input_Preset["raleft"]->Check();
		double b = Wealder->Input_Preset["radown"]->Check() - Wealder->Input_Preset["raup"]->Check();
		double ang = __Old_Angle;
		if (a || b)
			ang = (atan2(b, a) * 180 / M_PI) + 90 + (Max_Swing / 2 * __On_Left) + __Angle_Offset;
		double x, y;
		x = Player::Get_Entity(Wealder)->X;
		y = Player::Get_Entity(Wealder)->Y - 8;
		Get_Sprite()->Rotation = ang;
		X = Player::Get_Entity(Wealder)->X - cos(ang * M_PI / 180 + M_PI / 2) * 20;
		Y = Player::Get_Entity(Wealder)->Y - 8 - sin(ang * M_PI / 180 + M_PI / 2) * 20;
		if (abs(ang - __Old_Angle) > 3  && abs(ang - __Old_Angle) < 180)
		{
			if (ang < __Old_Angle) Get_Sprite()->Flip = SDL_FLIP_HORIZONTAL;
			if (ang > __Old_Angle) Get_Sprite()->Flip = SDL_FLIP_NONE;
		}
		__Old_Angle = ang;
	}
}
void Sword::Events()
{
	if (Mouse_Handler::Button_Down({SDL_BUTTON_LEFT}))
		__Swinging = true;
}