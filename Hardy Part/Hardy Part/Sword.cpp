#include "Sword.h"

#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Texture.h"
#include "System.h"
#include <SDL.h>
#include "Player.h"
#include "Device.h"

void Sword::Create()
{
	auto sp = Sprite::Load(this, "imgs/xord.png", 24, 24, 0, 1, 24, 24);
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
		double a = 0, b = 0;
		auto r = Device::Get(Wealder->Controller)["raright"];
		auto l = Device::Get(Wealder->Controller)["raleft"];
		auto d = Device::Get(Wealder->Controller)["radown"];
		auto u = Device::Get(Wealder->Controller)["raup"];

		a = r.Held() - l.Held();
		b = d.Held() - u.Held();
		if (r.Type() == IT_MOUSE_AXIS)
			a -= Player::Get_Entity(Wealder)->X;
		if (d.Type() == IT_MOUSE_AXIS)
			b -= Player::Get_Entity(Wealder)->Y;

		double ang = __Old_Angle;
		if (a || b)
			ang = (atan2(b, a) * 180 / M_PI) + 90 + (Max_Swing / 2 * __On_Left) + __Angle_Offset;
		double x, y;
		x = Player::Get_Entity(Wealder)->X;
		y = Player::Get_Entity(Wealder)->Y - 8;
		Display()->Rotation = ang;
		X = Player::Get_Entity(Wealder)->X - cos(ang * M_PI / 180 + M_PI / 2) * 20;
		Y = Player::Get_Entity(Wealder)->Y - 8 - sin(ang * M_PI / 180 + M_PI / 2) * 20;
		if (abs(ang - __Old_Angle) > 3  && abs(ang - __Old_Angle) < 180)
		{
			if (ang < __Old_Angle) Display()->Flip = SDL_FLIP_HORIZONTAL;
			if (ang > __Old_Angle) Display()->Flip = SDL_FLIP_NONE;
		}
		__Old_Angle = ang;
	}
}
void Sword::Events()
{
	if (Wealder && Device::Get(Wealder->Controller)["r1"].Down())
		__Swinging = true;
}