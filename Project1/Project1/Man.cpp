#include <initializer_list>

#include "Man.h"
#include "Keyboard_Handler.h"
#include "Gamepad_Handler.h"

#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Texture.h"
#include "System.h"

void Man::Create()
{
	X = 20;
	Y = 20;
	Sprite::Create(this, Texture::Load("imgs/Sprite-0001b-sheet.png", 160, 32, -5, 0, 0, 1));
	Animation::Add(this, "idle", "0x10 1x7 2x8 3x7 4x13 3x7 2x8 1x7", true);
	Animation::Play(this, "idle");
	//Load_Sprite("imgs/Paku_G.bmp", 256, 128, -8, -4, 0, 1);
	//Add_Animation("idle2", "0x43 1x5 2x26 1x5", true);
	Movement::Set(this, 10);
}
void Man::Update()
{
	//double vx1 = 0;
	//double vy1 = 0;
	//double vx2 = 0;
	//double vy2 = 0;
	//double(*foo)(std::initializer_list<Sint32>) = &Gamepad_Handler::Get_Axis_State_Positive;

	//if (Gamepad_Handler::Get(0))
	//{
	//	vy1 += Gamepad_Handler::Get_Axis_State_Positive({ 1, 0 });
	//	vy1 -= Gamepad_Handler::Get_Axis_State_Negative({ 1, 0 });
	//	vx1 += Gamepad_Handler::Get_Axis_State_Positive({ 0, 0 });
	//	vx1 -= Gamepad_Handler::Get_Axis_State_Negative({ 0, 0 });
	//	if (Gamepad_Handler::Button_Down({ SDL_CONTROLLER_BUTTON_X, 0 }))
	//	{
	//		X = 20;
	//		Y = 20;
	//	}
	//}

	//vy1 -= Keyboard_Handler::Key_Held({ SDLK_w });
	//vy1 += Keyboard_Handler::Key_Held({ SDLK_s });
	//vx1 -= Keyboard_Handler::Key_Held({ SDLK_a });
	//vx1 += Keyboard_Handler::Key_Held({ SDLK_d });

	//if (vx1 > 0) Get_Sprite()->Flip = SDL_FLIP_NONE;
	//if (vx1 < 0) Get_Sprite()->Flip = SDL_FLIP_HORIZONTAL;

	//Movement::Move(this, vx1, vy1, 0.02);
}
void Man::Events()
{

}