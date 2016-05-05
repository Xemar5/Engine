#include "GameMenu_State.h"
#include "Sprite.h"
#include "Texture.h"
#include "Entity.h"
#include "Input_Handler.h"
#include "Player.h"

void GameMenu_State::Create()
{
	int xoffs = 40;
	int yoffs = 40;

	auto cs1 = State::Add_Entity(1);
	Sprite::Create(cs1, Texture::Load("imgs/Character_Selection.png", 80, 48, 0, 0, 0, 0));
	cs1->X = Screen::Get_Screen_Size().first / 2 - 75 + xoffs;
	cs1->Y = Screen::Get_Screen_Size().second / 2 - 43 + yoffs;
	cs1->Get_Sprite()->Scale = 1.5;

	auto cs2 = State::Add_Entity(1);
	Sprite::Create(cs2, Texture::Load("imgs/Character_Selection.png", 80, 48, 0, 0, 0, 0));
	cs2->X = Screen::Get_Screen_Size().first / 2 + 75 + xoffs;
	cs2->Y = Screen::Get_Screen_Size().second / 2 - 43 + yoffs;
	cs2->Get_Sprite()->Scale = 1.5;

	auto cs3 = State::Add_Entity(1);
	Sprite::Create(cs3, Texture::Load("imgs/Character_Selection.png", 80, 48, 0, 0, 0, 0));
	cs3->X = Screen::Get_Screen_Size().first / 2 - 75 + xoffs;
	cs3->Y = Screen::Get_Screen_Size().second / 2 + 43 + yoffs;
	cs3->Get_Sprite()->Scale = 1.5;

	auto cs4 = State::Add_Entity(1);
	Sprite::Create(cs4, Texture::Load("imgs/Character_Selection.png", 80, 48, 0, 0, 0, 0));
	cs4->X = Screen::Get_Screen_Size().first / 2 + 75 + xoffs;
	cs4->Y = Screen::Get_Screen_Size().second / 2 + 43 + yoffs;
	cs4->Get_Sprite()->Scale = 1.5;
}

void GameMenu_State::Update()
{
	State::Update();
}

void GameMenu_State::Events()
{
	if (Keyboard_Handler::Key_Down({ SDLK_RETURN }))
	{
		//auto p1 = Player::Set(0);
		////Player::Set_Entity(p1, m1);
		//Player::Set_Keys(p1,
		//	Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_w }),
		//	Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_s }),
		//	Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_a }),
		//	Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_d }),

		//	Input_Handler::Set_Dynamic(&Mouse_Handler::Get_Relative_Mouse_X_State, { &Player::Get_Entity(p1)->Get_Movement()->Xpos, &Player::Get_Entity(p1)->Get_Movement()->Ypos }),
		//	Input_Handler::Set_Dynamic(&Mouse_Handler::Get_Relative_Mouse_Y_State, { &Player::Get_Entity(p1)->Get_Movement()->Xpos, &Player::Get_Entity(p1)->Get_Movement()->Ypos })
		//	);
	}
	State::Events();
}
