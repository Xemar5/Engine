#include "Main_State.h"
#include "System.h"
#include "Sprite.h"
#include "Timer.h"
#include "Animation.h"
#include "Player.h"
#include "Input_Handler.h"
#include "Keyboard_Handler.h"
#include "Gamepad_Handler.h"
#include "Sword.h"
#include "Movement.h"
#include "Tileset.h"
#include "Texture.h"
#include <iostream>

#include "Character.h"

void Main_Menu::Create()
{

	
	auto* m1 = State::Add_Entity<Character<Nerk>>(0);
	auto* m2 = State::Add_Entity<Character<Mosh>>(0);
	auto* m3 = State::Add_Entity<Character<Dreg>>(0);
	auto* m4 = State::Add_Entity<Character<Tar>>(0);
	auto* m5 = State::Add_Entity<Character<Raiden>>(0);

	m1->X = 100;
	m1->Y = 100;
	m2->X = 200;
	m2->Y = 200;
	m3->X = 300;
	m3->Y = 300;
	m4->X = 400;
	m4->Y = 400;
	m5->X = 500;
	m5->Y = 500;

	auto p1 = Player::Set();
	Player::Set_Entity(p1, m1);
	Player::Set_Keys(p1,
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_w }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_s }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_a }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_d })
		);

	auto p2 = Player::Set();
	Player::Set_Entity(p2, m2);
	Player::Set_Keys(p2,
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,0 })
		);

	auto p3 = Player::Set();
	Player::Set_Entity(p3, m3);
	Player::Set_Keys(p3,
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,1 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,1 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,1 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,1 })
		);

	Sword* s1 = State::Add_Entity<Sword>(1);
	s1->Wealder = m1;

	Tile_Set = Tileset::Set(Texture::Load("imgs/tileset2.png", 120, 120, 24, 24, -1, -1), { 0,0 },
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	});
}
void Main_Menu::Update()
{
	for(auto layer : State::Layers)
		for (auto ent : layer->Entities)
		{
			if (ent->X > 800) ent->X = 0;
			if (ent->X < 0) ent->X = 800;
			if (ent->Y > 600) ent->Y = 0;
			if (ent->Y < 0) ent->Y = 600;
		}
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
	}
	State::Events();
}

