#include "Menu_State.h"
#include "Device.h"
#include "Main_State.h"
#include "GameMenu_State.h"


#include "Sprite.h"
#include "Texture.h"
#include "Animation.h"
#include "System.h"
#include "Timer.h"
#include "Textfield.h"
#include "Character.h"


void Menu_Menu::Create()
{
	auto bg = ent::Add<>();
	Texture::Load(bg, "imgs/Hardy Part.png", 80, 60, 0, 0);
	//Player::Set_Entity(p, m1);
	//Animation::Add(bg, "idle", "24-47x4", true);
	//Animation::Add(bg, "start", "0-23x4", false);
	//Animation::Play(bg, "start");
	//bg->X = Screen::Width / 2;
	//bg->Y = Screen::Height / 2;

	//auto start_btn = State::Add_Entity(1);
	//auto options_btn = State::Add_Entity(1);
	//auto exit_btn = State::Add_Entity(1);
	auto f = [](auto e) { e->layer = 1; };
	
	auto start_btn = ent::Add<Textfield>(f);
	auto options_btn = ent::Add<Textfield>(f);
	auto exit_btn = ent::Add<Textfield>(f);

	Textfield::SetText(start_btn, "start", "imgs/slkscr.ttf", 32);
	Textfield::SetText(options_btn, "options", "imgs/slkscr.ttf", 32);
	Textfield::SetText(exit_btn, "exit", "imgs/slkscr.ttf", 32);
	//dynamic_cast<Textfield*>(start_btn.get())->SetText("start", "imgs/slkscr.ttf", 32);
	//dynamic_cast<Textfield*>(options_btn.get())->SetText("options", "imgs/slkscr.ttf", 32);
	//dynamic_cast<Textfield*>(exit_btn.get())->SetText("exit", "imgs/slkscr.ttf", 32);
	
	start_btn->texture->Set_Starting_Pos(0, 0);
	options_btn->texture->Set_Starting_Pos(0, 0);
	exit_btn->texture->Set_Starting_Pos(0, 0);
	//Sprite::Create(start_btn, Texture::Load("imgs/main_menu_btn.png", 72, 74, 24, 24, 0, 0));
	//Sprite::Create(options_btn, Texture::Load("imgs/main_menu_btn.png", 72, 74, 24, 24, 0, 0));
	//Sprite::Create(exit_btn, Texture::Load("imgs/main_menu_btn.png", 72, 74, 24, 24, 0, 0));

	//Animation::Add(start_btn, "start_idle", "0", true);
	//Animation::Add(start_btn, "start_hoover", "1", true);
	//Animation::Add(start_btn, "start_pushed", "2", true);
	//Animation::Add(options_btn, "options_idle", "3", true);
	//Animation::Add(options_btn, "options_hoover", "4", true);
	//Animation::Add(options_btn, "options_pushed", "5", true);
	//Animation::Add(exit_btn, "exit_idle", "6", true);
	//Animation::Add(exit_btn, "exit_hoover", "7", true);
	//Animation::Add(exit_btn, "exit_pushed", "8", true);

	//Animation::Play(start_btn->Get_Sprite().get(), "start_idle");
	//Animation::Play(options_btn->Get_Sprite().get(), "options_idle");
	//Animation::Play(exit_btn->Get_Sprite().get(), "exit_idle");
}
void Menu_Menu::Update()
{
	ent::All[0]->X = Screen::Get_Screen_Size().first / 2 + sin(System::In_Game_Timer.Get() / 370.0) * 50;
	ent::All[0]->Y = Screen::Get_Screen_Size().second / 2 + cos(System::In_Game_Timer.Get() / 420.0) * 30 - 50;
	ent::All[0]->texture->Scale = pow(sin(System::In_Game_Timer.Get() / 450.0), 2)/2 + 2;
	ent::All[0]->texture->Rotation = sin(System::In_Game_Timer.Get() / 500.0) * 20;

	ent::All[1]->X = Screen::Get_Screen_Size().first / 2;
	ent::All[1]->Y = Screen::Get_Screen_Size().second / 2 + 100;
	ent::All[2]->X = Screen::Get_Screen_Size().first / 2;
	ent::All[2]->Y = Screen::Get_Screen_Size().second / 2 + 120;
	ent::All[3]->X = Screen::Get_Screen_Size().first / 2;
	ent::All[3]->Y = Screen::Get_Screen_Size().second / 2 + 140;
}
void Menu_Menu::Events()
{
	if (Mouse::Get[Input::Set(IT_MOUSE_BUTTON, SDL_BUTTON_LEFT)].Up())
	{
		if (Mouse::Contains_Mouse(ent::All[1])) State::New<GameMenu_State>();
		if (Mouse::Contains_Mouse(ent::All[2])) State::New<Controlls_State>();
		if (Mouse::Contains_Mouse(ent::All[3])) State::Exit_Game();
		//{
		//	Screen::Change_Window_State();
		//	SDL_WarpMouseInWindow(
		//		Screen::Window,
		//		(Screen::Get_Screen_Size().first / 2) * (int)Screen::Get_Scale(),
		//		(Screen::Get_Screen_Size().second / 2 + 100) * (int)Screen::Get_Scale());
		//}
	}
	else if (Device::Get(Device::Which())["start"].Up()) State::Exit_Game();
	else if (Device::Get(Device::Which())["b"].Up()) State::Exit_Game();
	else if (Device::Get(Device::Which())["a"].Up()) State::New<GameMenu_State>();
	else if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_ESCAPE)].Up()) State::Exit_Game();
	else if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_RETURN)].Up()) State::New<GameMenu_State>();
}

