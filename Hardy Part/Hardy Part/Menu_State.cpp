#include "Menu_State.h"
#include "Entity.h"
#include "Keyboard_Handler.h"
#include "Mouse_Handler.h"
#include "Main_State.h"

#include "Sprite.h"
#include "Texture.h"
#include "Animation.h"
#include "System.h"
#include "Timer.h"

void Menu_Menu::Create()
{
	auto* bg = State::Add_Entity<Entity>(0);
	Sprite::Create(bg, Texture::Load("imgs/Hardy Part.png", 80, 60, 80, 60, 0, 0));
	//Animation::Add(bg, "idle", "24-47x4", true);
	//Animation::Add(bg, "start", "0-23x4", false);
	//Animation::Play(bg, "start");
	//bg->X = Screen::Width / 2;
	//bg->Y = Screen::Height / 2;

	auto start_btn = State::Add_Entity(1);
	auto options_btn = State::Add_Entity(1);
	auto exit_btn = State::Add_Entity(1);

	Sprite::Create(start_btn, Texture::Load("imgs/main_menu_btn.png", 72, 74, 24, 24, 0, 0));
	Sprite::Create(options_btn, Texture::Load("imgs/main_menu_btn.png", 72, 74, 24, 24, 0, 0));
	Sprite::Create(exit_btn, Texture::Load("imgs/main_menu_btn.png", 72, 74, 24, 24, 0, 0));

	Animation::Add(start_btn, "start_idle", "0", true);
	Animation::Add(start_btn, "start_hoover", "1", true);
	Animation::Add(start_btn, "start_pushed", "2", true);
	Animation::Add(options_btn, "options_idle", "3", true);
	Animation::Add(options_btn, "options_hoover", "4", true);
	Animation::Add(options_btn, "options_pushed", "5", true);
	Animation::Add(exit_btn, "exit_idle", "6", true);
	Animation::Add(exit_btn, "exit_hoover", "7", true);
	Animation::Add(exit_btn, "exit_pushed", "8", true);

	Animation::Play(start_btn->Get_Sprite().get(), "start_idle");
	Animation::Play(options_btn->Get_Sprite().get(), "options_idle");
	Animation::Play(exit_btn->Get_Sprite().get(), "exit_idle");
}
void Menu_Menu::Update()
{
	(*this)[0][0]->X = Screen::Get_Screen_Size().first / 2 + sin(System::In_Game_Timer.Get() / 370.0) * 50;
	(*this)[0][0]->Y = Screen::Get_Screen_Size().second / 2 + cos(System::In_Game_Timer.Get() / 420.0) * 30 - 50;
	(*this)[0][0]->Get_Sprite()->Scale = pow(sin(System::In_Game_Timer.Get() / 450.0), 2)/2 + 2;
	(*this)[0][0]->Get_Sprite()->Rotation = sin(System::In_Game_Timer.Get() / 500.0) * 20;

	(*this)[1][0]->X = Screen::Get_Screen_Size().first / 2 - 30;
	(*this)[1][0]->Y = Screen::Get_Screen_Size().second / 2 + 100;
	(*this)[1][1]->X = Screen::Get_Screen_Size().first / 2;
	(*this)[1][1]->Y = Screen::Get_Screen_Size().second / 2 + 100;
	(*this)[1][2]->X = Screen::Get_Screen_Size().first / 2 + 30;
	(*this)[1][2]->Y = Screen::Get_Screen_Size().second / 2 + 100;

	State::Update();
}
void Menu_Menu::Events()
{
	if (Mouse_Handler::Contains_Mouse((*this)[1][0]))
	{
		std::cout << "b0\n";
		if(System::Events.type == SDL_MOUSEBUTTONDOWN && System::Events.button.button == SDL_BUTTON_LEFT)
			State::New<Main_Menu>();
	}
	if (Mouse_Handler::Contains_Mouse((*this)[1][1]))
	{
		std::cout << "b1\n";
		if (System::Events.type == SDL_MOUSEBUTTONDOWN && System::Events.button.button == SDL_BUTTON_LEFT)
			Screen::Change_Window_State();
	}
	if (Mouse_Handler::Contains_Mouse((*this)[1][2]))
	{
		std::cout << "b2\n";
		if (System::Events.type == SDL_MOUSEBUTTONDOWN && System::Events.button.button == SDL_BUTTON_LEFT)
			State::Exit_Game();
	}
	if (Keyboard_Handler::Key_Up({ SDLK_ESCAPE })) State::Exit_Game();
	if (Keyboard_Handler::Key_Up({ SDLK_RETURN })) State::New<Main_Menu>();
	State::Events();
}

