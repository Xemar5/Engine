#include "Main_State.h"
#include "System.h"
#include "Sprite_Handler.h"

void Main_Menu::Create()
{
	Man* m = State::Add_Entity<Man>(0);
	std::cout << m->Get_Sprite_Handler()->Get_Frame_Size().first;
}
void Main_Menu::Update()
{
	State::Update();
}
void Main_Menu::Events()
{
	State::Events();
	if (System::Events.type == SDL_MOUSEBUTTONDOWN) State::Exit_Game();
	std::cout << "menu";
}

