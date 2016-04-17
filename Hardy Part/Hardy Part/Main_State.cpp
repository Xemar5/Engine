#include "Main_State.h"
#include "System.h"
#include "Sprite.h"
#include "Timer.h"
#include "Animation.h"
#include "Player.h"
#include "Input_Handler.h"
#include "Keyboard_Handler.h"
#include "Mouse_Handler.h"
#include "Gamepad_Handler.h"
#include "Sword.h"
#include "Movement.h"
#include "Tileset.h"
#include "Texture.h"
#include <iostream>
#include <ctime>
#include "Menu_State.h"

#include "Character.h"
#include "Wall.h"


void Main_Menu::Create()
{
	State::Add_Tileset
	(
		Texture::Load("imgs/orange-tile.png", 240, 24, 24, 24, 0, 0),
		{ Screen::Width/2,Screen::Height / 2 },
		{
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,2,2,5,0,0,0,0,0,0,5,5,3,3 },
			{ 0,0,2,2,4,6,2,0,0,0,0,0,5,4,9,9,6 },
			{ 0,0,4,7,6,0,2,0,2,2,4,0,2,6,0,0,0 },
			{ 0,0,3,0,0,0,5,4,2,6,2,0,4,0,0,0,0 },
			{ 0,0,3,0,0,0,6,8,6,0,2,0,3,4,4,0,0 },
			{ 0,0,2,0,0,2,4,5,0,2,4,0,4,8,5,0,0 },
			{ 0,0,2,2,3,2,7,5,0,5,6,0,5,3,4,0,0 },
			{ 0,0,6,6,8,9,0,3,0,4,0,0,6,3,6,0,0 },
			{ 0,0,0,4,2,5,0,2,0,2,3,4,0,3,4,0,0 },
			{ 0,0,0,3,6,5,3,4,0,6,9,5,0,6,2,0,0 },
			{ 4,2,3,3,0,6,9,6,0,0,0,2,2,4,2,0,0 },
			{ 6,7,7,9,0,0,0,0,0,0,0,7,8,8,6,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
		}
	);

	std::cout << Get_Tilesets()[0]->Get_Pos().first;
	
	auto* m1 = Character::Add(this, "Nerk", 100, 100, 0);
	auto* m2 = Character::Add(this, "Mosh", 200, 200, 0);
	auto* m3 = Character::Add(this, "Dreg", 300, 300, 0);
	auto* m4 = Character::Add(this, "Tar", 400, 400, 0);
	auto* m5 = Character::Add(this, "Benio", 500, 500, 0);


	for (int i = 0; i < 0; ++i)
		Character::Add(this, "Nerk", 100, 100, 0);



	auto p1 = Player::Set(0);
	Player::Set_Entity(p1, m1);
	Player::Set_Keys(p1,
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_w }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_s }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_a }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_d }),

		Input_Handler::Set(&Mouse_Handler::Button_Held, { SDL_BUTTON_LEFT }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDL_BUTTON_RIGHT })
		);

	auto p2 = Player::Set(1);
	Player::Set_Entity(p2, m2);
	Player::Set_Keys(p2,
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,0 }),

		Input_Handler::Set(&Mouse_Handler::Button_Held, { SDL_BUTTON_LEFT }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDL_BUTTON_RIGHT })
		);

	auto p3 = Player::Set(2);
	Player::Set_Entity(p3, m3);
	Player::Set_Keys(p3,
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,1 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,1 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,1 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,1 }),

		Input_Handler::Set(&Mouse_Handler::Button_Held, { SDL_BUTTON_LEFT }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDL_BUTTON_RIGHT })
		);

	auto p4 = Player::Set(3);
	Player::Set_Entity(p4, m4);
	Player::Set_Keys(p4,
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,2 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,2 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,2 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,2 }),

		Input_Handler::Set(&Mouse_Handler::Button_Held, { SDL_BUTTON_LEFT }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDL_BUTTON_RIGHT })
		);

	Sword* s1 = State::Add_Entity<Sword>(1);
	s1->Wealder = m1;

	srand((unsigned)time(0));
	if (Get_Tilesets().size())
		for (unsigned i = 0; i < Get_Tilesets().size(); i++)
		for (auto wp : Get_Tilesets()[i]->Get_Wall_Placeholders())
		{
			auto* w = State::Add_Entity<Wall<Wall_Enum::Cobble>>(i);
			w->X = wp.first * (int)Screen::Get_Scale() + Get_Tilesets()[i]->Get_Pos().first * (int)Screen::Get_Scale();
			w->Y = wp.second * (int)Screen::Get_Scale() + Get_Tilesets()[i]->Get_Pos().second * (int)Screen::Get_Scale() + 24 * (int)Screen::Get_Scale();
			int r = 2;
			switch (r)
			{
			case 0: Animation::Play(w, "type0"); break;
			case 1: Animation::Play(w, "type1"); break;
			case 2: Animation::Play(w, "type2"); break;
			default:break;
			}
		}
}
void Main_Menu::Update()
{
	for (auto ent : Layers[0]->Entities)
	{
		auto tile = Get_Tilesets()[0]->Which_Tile((int)ent->X, (int)ent->Y);
		if (tile == 0 || tile >= 6)
		{
			ent->X = Screen::Width/2 - 350;
			ent->Y = Screen::Height/2 + 220;
		}
	}

	SDL_Point p;
	SDL_GetMouseState(&p.x, &p.y);
	Uint32 px, py;
	px = (Uint32)((double)p.x / (double)Screen::Width * 255);
	py = (Uint32)((double)p.y / (double)Screen::Height * 255);
	SDL_SetRenderDrawColor(Screen::Renderer, px, 255 - (px+py)/2, py, 255);
	//for(auto layer : State::Layers)
	//	for (auto ent : layer->Entities)
	//	{
	//		if (ent->X > 800) ent->X = 0;
	//		if (ent->X < 0) ent->X = 800;
	//		if (ent->Y > 600) ent->Y = 0;
	//		if (ent->Y < 0) ent->Y = 600;
	//	}
	State::Update();
}
void Main_Menu::Events()
{
	if (System::Events.type == SDL_KEYDOWN)
	{
		auto pl = Player::Get(0);
		auto sw = dynamic_cast<Sword*>(State::Layers[1]->Entities[0].get());
		if (System::Events.key.keysym.sym == SDLK_1)
		{
			Player::Set_Entity(pl, State::Layers[0]->Entities[0].get());
			sw->Wealder = State::Layers[0]->Entities[0].get();
		}
		if (System::Events.key.keysym.sym == SDLK_2)
		{
			Player::Set_Entity(pl, State::Layers[0]->Entities[1].get());
			sw->Wealder = State::Layers[0]->Entities[1].get();
		}
		if (System::Events.key.keysym.sym == SDLK_3)
		{
			Player::Set_Entity(pl, State::Layers[0]->Entities[2].get());
			sw->Wealder = State::Layers[0]->Entities[2].get();
		}
		if (System::Events.key.keysym.sym == SDLK_4)
		{
			Player::Set_Entity(pl, State::Layers[0]->Entities[3].get());
			sw->Wealder = State::Layers[0]->Entities[3].get();
		}
		if (System::Events.key.keysym.sym == SDLK_5)
		{
			Player::Set_Entity(pl, State::Layers[0]->Entities[4].get());
			sw->Wealder = State::Layers[0]->Entities[4].get();
		}
		//if (System::Events.key.keysym.sym == SDLK_5)
		//{
		//	Player::Set_Entity(pl, State::Layers[0]->Entities[4].get());
		//	sw->Wealder = State::Layers[0]->Entities[4].get();
		//}
	}


	if (Keyboard_Handler::Key_Up({ SDLK_SPACE }))
	{
		for (auto pl : Player::Get_Players())
		{
			Player::Set_Entity(pl.get(), nullptr);
		}
		State::New<Menu_Menu>();
	}

	State::Events();
}

