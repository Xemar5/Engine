#include <fstream>
#include "GameMenu_State.h"
#include "Sprite.h"
#include "Texture.h"
#include "Entity.h"
#include "Device.h"
#include "Player.h"
#include "Character.h"

void GameMenu_State::Create()
{
	for (auto pl : Player::Get_Players())
		if (auto ent = Player::Get_Entity(pl.get()))
			ent->Get_Sprite()->Scale = 1.5;

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

Player* Add_New_Player(Sint32 controller)
{
	for (auto& pl : Player::Get_Players())
		if (pl->Controller == controller) return nullptr;
	if (auto p = Player::Set())
	{
		Player::Set_Controller(p, controller);
		return p;
	}
	return nullptr;
}

#include "System.h"
class Main_Menu;
void GameMenu_State::Events()
{
	Player* p = nullptr;
	if (Device::Get(Device::Which())["x"].Down())
	{
		if (auto* p = Add_New_Player(Device::Which()))
		{
			auto* m1 = Character::Add(this, "Nerk", 100, 100, 3, 1.5);
			Player::Set_Entity(p, m1);
		}
	}
	if (Device::Get(Device::Which())["b"].Down())
	{
		for (auto& p : Player::Get_Players())

			if (p->Controller == Device::Which())
			{
				Player::Remove(p.get());
				State::Remove_Entity(Player::Get_Entity(p.get()));
			}
	}

	if(Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_SPACE)].Up() && Player::Get_Players().size())
	{
		std::vector<Entity*> v(Player::Get_Players().size());
		for (unsigned i = 0; i < Player::Get_Players().size(); ++i)
			v[i] = Player::Get_Entity(Player::Get_Players()[i].get());
		State::New<Main_Menu>(v);
	}
	if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_ESCAPE)].Up())
	{
		for (auto pl : Player::Get_Players())
			Player::Remove(pl.get());
		State::New<Menu_Menu>();
	}
	State::Events();
}

