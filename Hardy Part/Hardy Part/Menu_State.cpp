#include "Menu_State.h"
#include "Entity.h"
#include "Device.h"
#include "Main_State.h"
#include "GameMenu_State.h"


#include "Sprite.h"
#include "Texture.h"
#include "Animation.h"
#include "System.h"
#include "Timer.h"
#include "Textfield.h"


void Menu_Menu::Create()
{
	auto bg = State::Add_Entity<Entity>(0);
	Sprite::Create(bg.get(), Texture::Load("imgs/Hardy Part.png", 80, 60, 80, 60, 0, 0));
	//Animation::Add(bg, "idle", "24-47x4", true);
	//Animation::Add(bg, "start", "0-23x4", false);
	//Animation::Play(bg, "start");
	//bg->X = Screen::Width / 2;
	//bg->Y = Screen::Height / 2;

	//auto start_btn = State::Add_Entity(1);
	//auto options_btn = State::Add_Entity(1);
	//auto exit_btn = State::Add_Entity(1);

	auto start_btn = State::Add_Entity<Textfield>(1);
	auto options_btn = State::Add_Entity<Textfield>(1);
	auto exit_btn = State::Add_Entity<Textfield>(1);
	
	dynamic_cast<Textfield*>(start_btn.get())->Set("Start", "imgs/slkscr.ttf", 32);
	dynamic_cast<Textfield*>(options_btn.get())->Set("Options", "imgs/slkscr.ttf", 32);
	dynamic_cast<Textfield*>(exit_btn.get())->Set("exit", "imgs/slkscr.ttf", 32);
	
	start_btn->Get_Sprite()->Get_Texture()->Set_Starting_Point(1, 0);
	options_btn->Get_Sprite()->Get_Texture()->Set_Starting_Point(1, 0);
	exit_btn->Get_Sprite()->Get_Texture()->Set_Starting_Point(1, 0);

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
	Ent(0)->X = Screen::Get_Screen_Size().first / 2 + sin(System::In_Game_Timer.Get() / 370.0) * 50;
	Ent(0)->Y = Screen::Get_Screen_Size().second / 2 + cos(System::In_Game_Timer.Get() / 420.0) * 30 - 50;
	Ent(0)->Get_Sprite()->Scale = pow(sin(System::In_Game_Timer.Get() / 450.0), 2)/2 + 2;
	Ent(0)->Get_Sprite()->Rotation = sin(System::In_Game_Timer.Get() / 500.0) * 20;

	Ent(1)->X = Screen::Get_Screen_Size().first / 2 - 30;
	Ent(1)->Y = Screen::Get_Screen_Size().second / 2 + 100;
	Ent(2)->X = Screen::Get_Screen_Size().first / 2 - 30;
	Ent(2)->Y = Screen::Get_Screen_Size().second / 2 + 120;
	Ent(3)->X = Screen::Get_Screen_Size().first / 2 - 30;
	Ent(3)->Y = Screen::Get_Screen_Size().second / 2 + 140;
}
void Menu_Menu::Events()
{
	if (Mouse::Get[Input::Set(IT_MOUSE_BUTTON, SDL_BUTTON_LEFT)].Down())
	{
		if (Mouse::Contains_Mouse(Ent(1))) State::New<Main_Menu>();
		if (Mouse::Contains_Mouse(Ent(2))) State::New<Controlls_State>();
		if (Mouse::Contains_Mouse(Ent(3))) State::Exit_Game();
		//{
		//	Screen::Change_Window_State();
		//	SDL_WarpMouseInWindow(
		//		Screen::Window,
		//		(Screen::Get_Screen_Size().first / 2) * (int)Screen::Get_Scale(),
		//		(Screen::Get_Screen_Size().second / 2 + 100) * (int)Screen::Get_Scale());
		//}
	}
	if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_ESCAPE)].Up()) State::Exit_Game();
	if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_RETURN)].Up()) State::New<GameMenu_State>();
}

