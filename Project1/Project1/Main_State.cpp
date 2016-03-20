#include "Main_State.h"
#include "System.h"
#include "Sprite.h"
#include "Timer.h"
#include "Animation.h"

	Timer tmrr;
void Main_Menu::Create()
{
	Man* m = State::Add_Entity<Man>(0);
	Man* m2 = State::Add_Entity<Man>(0);
	m2->X = 40;
	m2->Y = 45;
	m2->Get_Sprite()->Flip = SDL_FLIP_HORIZONTAL;
	tmrr.Start();
}
void Main_Menu::Update()
{
	
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

