#include "Main_State.h"
#include "System.h"
#include "Sprite.h"
#include "Timer.h"
#include "Animation.h"
#include "Player.h"
#include "Device.h"
#include "Sword.h"
#include "Movement.h"
#include "Tileset.h"
#include "Texture.h"
#include <iostream>
#include <ctime>
class GameMenu_State;

#include "Character.h"
#include "Wall.h"


void Main_Menu::Create()
{
	for (auto pl : Player::Get_Players())
		if (auto ent = Player::Get_Entity(pl.get()))
			ent->Get_Sprite()->Scale = 1;

	auto ttt = State::Add_Entity<Tileset>
		(
			Tileset::Set(Texture::Load("imgs/orange-tile.png", 240, 24, 24, 24, 0, 0),
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
			})
			);
	ttt->X = Screen::Get_Screen_Size().first / 2;
	ttt->Y = Screen::Get_Screen_Size().second / 2;
	//Output_Handler::Output << ttt->X << std::endl;
	//Output_Handler::Output << ttt->Get_Texture()->Get_SDL_Starting_Point().x << std::endl;

	int midx = Screen::Get_Screen_Size().first / 2 - 195;
	int midy = Screen::Get_Screen_Size().second / 2 + 110;



	//auto* m1 = Character::Add(this, "Nerk", midx, midy, 1);
	//auto* m2 = Character::Add(this, "Mosh", midx + 20, midy, 1);
	//auto* m3 = Character::Add(this, "Dreg", midx + 40, midy, 1);
	//auto* m4 = Character::Add(this, "Tar", midx + 60, midy, 1);
	//auto* m5 = Character::Add(this, "Benio", midx + 80, midy, 1);

	//for (int i = 0; i < 0; ++i)
	//	Character::Add(this, "Nerk", 100, 100, 1);



	//auto p1 = Player::Set(0);
	//Player::Set_Entity(p1, m1);
	//Player::Set_Keys(p1,
	//	Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_w }),
	//	Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_s }),
	//	Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_a }),
	//	Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_d }),

	//	Input_Handler::Set(&Mouse_Handler::Get_Relative_Mouse_X_State, { 0,0 }),
	//	Input_Handler::Set(&Mouse_Handler::Get_Relative_Mouse_Y_State, { 0,0 })
	//	);

	//auto p2 = Player::Set(1);
	//Player::Set_Entity(p2, m2);
	//Player::Set_Keys(p2,
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,0 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,0 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,0 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,0 }),

	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 2,0 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 4,0 })
	//	);

	//auto p3 = Player::Set(2);
	//Player::Set_Entity(p3, m3);
	//Player::Set_Keys(p3,
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,1 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,1 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,1 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,1 }),

	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 2,1 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 4,1 })
	//	);

	//auto p4 = Player::Set(3);
	//Player::Set_Entity(p4, m4);
	//Player::Set_Keys(p4,
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,2 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,2 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,2 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,2 }),

	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 2,2 }),
	//	Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 4,2 })
	//	);
	if (Player::Get_Players().size())
	{
		auto s1 = State::Add_Entity<Sword>(1);
		dynamic_cast<Sword*>(s1.get())->Wealder = Player::Get_Players().front().get();
	}
	//srand((unsigned)time(0));
	//if (this->Layers[0]->Entities.size())
	//	for (unsigned i = 0; i < Get_Tilesets().size(); i++)
	//		for (auto wp : Get_Tilesets()[i]->Get_Wall_Placeholders())
	//		{
	//			auto* w = State::Add_Entity<Wall<Wall_Enum::Cobble>>(i);
	//			w->X = wp.first;
	//			w->Y = wp.second + Get_Tilesets()[i]->Get_Texture()->Get_Frame_Size().second;
	//			int r = rand()%3;
	//			switch (r)
	//			{
	//			case 0: Animation::Play(w, "type0"); break;
	//			case 1: Animation::Play(w, "type1"); break;
	//			case 2: Animation::Play(w, "type2"); break;
	//			default:break;
	//			}
	//		}
}
void Main_Menu::Update()
{
	for (auto tileset : Get_Entities())
	{
		if (!tileset->As<Tileset>()) continue;
		for (auto ent : Get_Entities())
		{
			if (tileset == ent) continue;
			if (!Get_Entities().size()) break;
			auto tile = tileset->As<Tileset>()->Which_Tile((int)ent->X, (int)ent->Y);

			if (tile == 0 || tile >= 6)
			{
				ent->X = Screen::Get_Screen_Size().first / 2 - 190;
				ent->Y = Screen::Get_Screen_Size().second / 2 + 110;
			}
		}
	}
	Uint32 px = (Uint32)Mouse::Get[Input::Set(IT_MOUSE_AXIS, MA_X)].Held();
	Uint32 py = (Uint32)Mouse::Get[Input::Set(IT_MOUSE_AXIS, MA_Y)].Held();
	px = (Uint32)((double)px / (double)Screen::Get_Screen_Size().first * 255);
	py = (Uint32)((double)py / (double)Screen::Get_Screen_Size().second * 255);
	SDL_SetRenderDrawColor(Screen::Renderer, px, 255 - (px+py)/2, py, 255);




	//for(auto layer : State::Layers)
	//	for (auto ent : layer->Entities)
	//	{
	//		if (ent->X > 800) ent->X = 0;
	//		if (ent->X < 0) ent->X = 800;
	//		if (ent->Y > 600) ent->Y = 0;
	//		if (ent->Y < 0) ent->Y = 600;
	//	}
}
void Main_Menu::Events()
{
	//if (System::Events.type == SDL_KEYDOWN)
	//{
	//	if (State::Layers.size() > 1 && State::Layers[1]->Entities.size())
	//	{
	//		auto pl = Player::Get(0);
	//		auto sw = dynamic_cast<Sword*>(State::Layers[1]->Entities[0].get());
	//		if (System::Events.key.keysym.sym == SDLK_1)
	//			Player::Set_Entity(pl, State::Layers[1]->Entities[0].get());
	//		if (System::Events.key.keysym.sym == SDLK_2)
	//			Player::Set_Entity(pl, State::Layers[1]->Entities[1].get());
	//		if (System::Events.key.keysym.sym == SDLK_3)
	//			Player::Set_Entity(pl, State::Layers[1]->Entities[2].get());
	//		if (System::Events.key.keysym.sym == SDLK_4)
	//			Player::Set_Entity(pl, State::Layers[1]->Entities[3].get());
	//		if (System::Events.key.keysym.sym == SDLK_5)
	//			Player::Set_Entity(pl, State::Layers[1]->Entities[4].get());
	//	}
	//	//if (System::Events.key.keysym.sym == SDLK_5)
	//	//{
	//	//	Player::Set_Entity(pl, State::Layers[0]->Entities[4].get());
	//	//	sw->Wealder = State::Layers[0]->Entities[4].get();
	//	//}
	//}


	if (Keyboard::Get[Input::Set(IT_KEYBOARD_KEY, SDLK_ESCAPE)].Up())
	{
		
		//for (auto pl : Player::Get_Players())
		//{
		//	//Player::Remove(pl.get());
		//	//Player::Set_Entity(pl.get(), nullptr);
		//}
		State::New<GameMenu_State>(Player::Get_Controlled_Entities());
	}
}

