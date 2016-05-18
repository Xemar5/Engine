#include <fstream>
#include "GameMenu_State.h"
#include "Sprite.h"
#include "Texture.h"
#include "Entity.h"
#include "Input_Handler.h"
#include "Player.h"
#include "Character.h"

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

Player* Add_New_Player(unsigned const ui, int controller_id)
{
	if (ui & (1 << (controller_id + 1))) return false;

	std::ifstream file;
	file.open("keybinds.txt");
	if (file)
	{
		auto p = Player::Set();
		std::string name = "keyboard";
		if (controller_id >= 0) name = SDL_JoystickNameForIndex(controller_id);
		p->Input_Preset = Input_Handler::Load(file, name, controller_id);
		file.close();
		//ui = ui | (1 << (controller_id + 1));
		return p;
	}
	return nullptr;
}

#include "System.h"
class Main_Menu;
void GameMenu_State::Events()
{
	if ((System::Events.type == SDL_KEYDOWN && System::Events.key.keysym.sym == SDLK_RETURN) ||
		(System::Events.type == SDL_JOYBUTTONDOWN && System::Events.jbutton.button == SDL_CONTROLLER_BUTTON_A))
	{
		int ind = -1;
		for (unsigned i = 0; i < Gamepad_Handler::Gamepad_Count(); i++)
		{
			if (System::Events.cdevice.which == Gamepad_Handler::Get_Gamepads()[i]->Get_SDL_Index())
			{
				ind = Gamepad_Handler::Get_Gamepads()[i]->Get_Index();
				break;
			}
		}
		if (auto* p = Add_New_Player(Player::Get_First_Unused_Index(), ind))
		{
			auto* m1 = Character::Add(this, "Nerk", 100, 100, 3);
			Player::Set_Entity(p, m1);
		}
	}
	if (Keyboard_Handler::Key_Up({ SDLK_SPACE }) && Player::Get_Players().size())
//		if (System::Events.type == SDL_KEYDOWN && System::Events.key.keysym.sym == SDLK_SPACE)
	{
		std::vector<Entity*> v(Player::Get_Players().size());
		for (unsigned i = 0; i < Player::Get_Players().size(); ++i)
			v[i] = Player::Get_Entity(Player::Get_Players()[i].get());
		State::New<Main_Menu>(v);
	}
	if (Keyboard_Handler::Key_Up({ SDLK_ESCAPE }))
	{
		for (auto pl : Player::Get_Players())
			Player::Remove(pl.get());
		State::New<Menu_Menu>();
	}
	State::Events();
}

