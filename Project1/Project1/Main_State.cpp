#include "Main_State.h"
#include "System.h"
#include "Sprite.h"
#include "Timer.h"
#include "Animation.h"
#include "Player.h"
#include "Input_Handler.h"
#include "Keyboard_Handler.h"

Timer tmrr;
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
	Player::Set_Keys(p1,
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_w }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_s }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_a }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_d })
		);

	p1->Set_Entity(m2);
	tmrr.Start();
}
void Main_Menu::Update()
{
	auto pp = Player::Get(0);
	if (tmrr.Is_Started() && tmrr.Get() > 1000)
	{
		tmrr.Stop();
		Animation::Play(Layers[0]->Entities[1].get(), "idle");
	}

	State::Update();
}
void Main_Menu::Events()
{
	State::Events();
	//if (System::Events.type == SDL_MOUSEBUTTONDOWN) State::Exit_Game();
	//std::cout << "menu";
}

