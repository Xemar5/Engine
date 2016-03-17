#include "Main_State.h"
#include "System.h"

void Main_Menu::Create()
{
	Gamepad_Handler::Set(0);
	Man* m = State::Add_Entity<Man>(0);
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

