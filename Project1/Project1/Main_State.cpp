#include "Main_State.h"
#include "System.h"
#include "Sprite.h"
#include "Timer.h"
#include "Animation.h"
#include "Player.h"
#include "Input_Handler.h"
#include "Keyboard_Handler.h"
#include "Gamepad_Handler.h"
#include "Sword.h"

void Main_Menu::Create()
{
	Man* m = State::Add_Entity<Man>(0);
	Man* m2 = State::Add_Entity<Man>(0);
	Man* m3 = State::Add_Entity<Man>(0);
	Man* m4 = State::Add_Entity<Man>(0);
	m2->X = 40;
	m2->Y = 45;
	m3->X = 410;
	m3->Y = 425;
	m4->X = 210;
	m4->Y = 225;
	m2->Get_Sprite()->Flip = SDL_FLIP_HORIZONTAL;

	auto p1 = Player::Set();
	Player::Set_Entity(p1, m2);
	Player::Set_Keys(p1,
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_w }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_s }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_a }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_d })
		);

	auto p2 = Player::Set();
	Player::Set_Entity(p2, m2);
	Player::Set_Keys(p2,
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,0 })
		);

	Sword* s1 = State::Add_Entity<Sword>(0);
	s1->Wealder = m2;
}
void Main_Menu::Update()
{
	State::Update();
}
void Main_Menu::Events()
{
	State::Events();
	//if (System::Events.type == SDL_MOUSEBUTTONDOWN) State::Exit_Game();
	//std::cout << "menu";
}

