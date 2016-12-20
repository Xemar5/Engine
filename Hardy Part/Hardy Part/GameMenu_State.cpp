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
		if (auto ent = Player::Get_Entity(pl))
			ent->texture->Scale = 1.5;

	int xoffs = 40;
	int yoffs = 40;

	auto cs1 = State::Add_Entity(1);
	Texture::Load(cs1.get(), "imgs/Character_Selection.png", 80, 48, 0, 0);
	cs1->X = Screen::Get_Screen_Size().first / 2 - 75 + xoffs;
	cs1->Y = Screen::Get_Screen_Size().second / 2 - 43 + yoffs;
	cs1->texture->Scale = 1.5;

	auto cs2 = State::Add_Entity(1);
	Texture::Load(cs2.get(), "imgs/Character_Selection.png", 80, 48, 0, 0);
	cs2->X = Screen::Get_Screen_Size().first / 2 + 75 + xoffs;
	cs2->Y = Screen::Get_Screen_Size().second / 2 - 43 + yoffs;
	cs2->texture->Scale = 1.5;

	auto cs3 = State::Add_Entity(1);
	Texture::Load(cs3.get(), "imgs/Character_Selection.png", 80, 48, 0, 0);
	cs3->X = Screen::Get_Screen_Size().first / 2 - 75 + xoffs;
	cs3->Y = Screen::Get_Screen_Size().second / 2 + 43 + yoffs;
	cs3->texture->Scale = 1.5;

	auto cs4 = State::Add_Entity(1);
	Texture::Load(cs4.get(), "imgs/Character_Selection.png", 80, 48, 0, 0);
	cs4->X = Screen::Get_Screen_Size().first / 2 + 75 + xoffs;
	cs4->Y = Screen::Get_Screen_Size().second / 2 + 43 + yoffs;
	cs4->texture->Scale = 1.5;
}

void GameMenu_State::Update()
{
}

std::shared_ptr<Player> Add_New_Player(Sint32 controller)
{
	for (auto& pl : Player::Get_Players())
		if (pl->Controller == controller)
			return nullptr;
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
		if (auto p = Add_New_Player(Device::Which()))
		{
			auto m1 = Character::Add(0, "Nerk", 100, 100, 3, 1.5);
			Player::Set_Entity(p, m1);
		}
	}
	if (Device::Get(Device::Which())["b"].Down())
	{
		for (auto& p : Player::Get_Players())

			if (p->Controller == Device::Which())
			{
				State::Remove_Entity(Player::Get_Entity(p));
				Player::Remove(p);
			}
	}

	if(Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_SPACE)].Up() && Player::Get_Players().size())
	{
		State::New<Main_Menu>(Player::Get_Controlled_Entities());
	}
	if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_ESCAPE)].Up())
	{
		for (auto pl : Player::Get_Players())
			Player::Remove(pl);
		State::New<Menu_Menu>();
	}
}

