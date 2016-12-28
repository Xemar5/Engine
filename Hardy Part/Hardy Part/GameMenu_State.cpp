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
	((Entity<>)layer(0))->scale = 3;
	for (auto pl : Player::Get_Players())
		if (auto ent = Player::Get_Entity(pl))
			ent->scale = 1.5;

	int xoffs = 40;
	int yoffs = 40;

	struct Tab : public EntityObject
	{
		Tab(int x, int y) : x(x), y(y) {}

		void Create() override
		{
			Texture::Load(this->shared_from_this(), "imgs/Character_Selection.png", 80, 48, 0, 0);
			this->X = Screen::Window_Size().first / 6 + x + xoffs;
			this->Y = Screen::Window_Size().second / 6 + y + yoffs;
		}
	private:
		int x;
		int y;
		int xoffs = 40;
		int yoffs = 40;
	};

	Entity<Tab>::Add(-75, -43);
	Entity<Tab>::Add(75, -43);
	Entity<Tab>::Add(-75, 43);
	Entity<Tab>::Add(75, 43);

	//auto cs1 = Entity<EntityObject>::Add([xoffs, yoffs](auto e)
	//{
	//	Texture::Load(e, "imgs/Character_Selection.png", 80, 48, 0, 0);
	//	e->X = Screen::Window_Size().first / 6 - 75 + xoffs;
	//	e->Y = Screen::Window_Size().second / 6 - 43 + yoffs;
	//	e->scale = 1;
	//});

	//auto cs2 = Entity<EntityObject>::Add([xoffs, yoffs](auto e)
	//{
	//	Texture::Load(e, "imgs/Character_Selection.png", 80, 48, 0, 0);
	//	e->X = Screen::Window_Size().first / 6 + 75 + xoffs;
	//	e->Y = Screen::Window_Size().second / 6 - 43 + yoffs;
	//	e->scale = 1;
	//});

	//auto cs3 = Entity<EntityObject>::Add([xoffs, yoffs](auto e)
	//{
	//	Texture::Load(e, "imgs/Character_Selection.png", 80, 48, 0, 0);
	//	e->X = Screen::Window_Size().first / 6 - 75 + xoffs;
	//	e->Y = Screen::Window_Size().second / 6 + 43 + yoffs;
	//	e->scale = 1;
	//});

	//auto cs4 = Entity<EntityObject>::Add([xoffs, yoffs](auto e)
	//{
	//	Texture::Load(e, "imgs/Character_Selection.png", 80, 48, 0, 0);
	//	e->X = Screen::Window_Size().first / 6 + 75 + xoffs;
	//	e->Y = Screen::Window_Size().second / 6 + 43 + yoffs;
	//	e->scale = 1;
	//});
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
				//State::Remove_Entity(Player::Get_Entity(p));
				Player::Remove(p);
			}
	}

	if(Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_SPACE)].Up() && Player::Get_Players().size())
	{
		Change<Main_Menu>();
	}
	if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_ESCAPE)].Up())
	{
		for (auto pl : Player::Get_Players())
			Player::Remove(pl);
		Change<Menu_Menu>();
	}
}

