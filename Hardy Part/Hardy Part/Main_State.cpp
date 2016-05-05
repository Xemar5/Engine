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
	auto ttt = Tileset::Add
		(
			this, Tileset::Set(Texture::Load("imgs/orange-tile.png", 240, 24, 24, 24, 0, 0),
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
			}),
			Screen::Get_Screen_Size().first / 2, Screen::Get_Screen_Size().second / 2, 0, 1
			);

	std::cout << ttt->X << std::endl;
	std::cout << ttt->Get_Texture()->Get_SDL_Starting_Point().x << std::endl;

	int midx = Screen::Get_Screen_Size().first / 2 - 195;
	int midy = Screen::Get_Screen_Size().second / 2 + 110;

	auto* m1 = Character::Add(this, "Nerk", midx, midy, 1);
	auto* m2 = Character::Add(this, "Mosh", midx + 20, midy, 1);
	auto* m3 = Character::Add(this, "Dreg", midx + 40, midy, 1);
	auto* m4 = Character::Add(this, "Tar", midx + 60, midy, 1);
	auto* m5 = Character::Add(this, "Benio", midx + 80, midy, 1);

	for (int i = 0; i < 0; ++i)
		Character::Add(this, "Nerk", 100, 100, 1);



	auto p1 = Player::Set(0);
	Player::Set_Entity(p1, m1);
	Player::Set_Keys(p1,
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_w }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_s }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_a }),
		Input_Handler::Set(&Keyboard_Handler::Key_Held, { SDLK_d }),

		Input_Handler::Set_Dynamic(&Mouse_Handler::Get_Relative_Mouse_X_State, { &Player::Get_Entity(p1)->Get_Movement()->Xpos, &Player::Get_Entity(p1)->Get_Movement()->Ypos }),
		Input_Handler::Set_Dynamic(&Mouse_Handler::Get_Relative_Mouse_Y_State, { &Player::Get_Entity(p1)->Get_Movement()->Xpos, &Player::Get_Entity(p1)->Get_Movement()->Ypos })
		);

	auto p2 = Player::Set(1);
	Player::Set_Entity(p2, m2);
	Player::Set_Keys(p2,
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,0 }),

		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 2,0 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 4,0 })
		);

	auto p3 = Player::Set(2);
	Player::Set_Entity(p3, m3);
	Player::Set_Keys(p3,
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,1 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,1 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,1 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,1 }),

		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 2,1 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 4,1 })
		);

	auto p4 = Player::Set(3);
	Player::Set_Entity(p4, m4);
	Player::Set_Keys(p4,
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 1,2 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 1,2 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Negative, { 0,2 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State_Positive, { 0,2 }),

		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 2,2 }),
		Input_Handler::Set(&Gamepad_Handler::Get_Axis_State, { 4,2 })
		);

	Sword* s1 = State::Add_Entity<Sword>(2);
	s1->Wealder = p1;

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

	for (auto ent : Get_Entities())
	{
		if (!Get_Tilesets().size()) break;

		auto tile = Get_Tilesets()[0]->Which_Tile((int)ent->X, (int)ent->Y);

		if (tile == 0 || tile >= 6)
		{		
			ent->X = Screen::Get_Screen_Size().first / 2 - 190;
			ent->Y = Screen::Get_Screen_Size().second / 2 + 110;
		}
	}

	Uint32 px = Mouse_Handler::Get_Mouse_Pos().first;
	Uint32 py = Mouse_Handler::Get_Mouse_Pos().second;
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
	State::Update();
}
void Main_Menu::Events()
{
	if (System::Events.type == SDL_KEYDOWN)
	{
		auto pl = Player::Get(0);
		auto sw = dynamic_cast<Sword*>(State::Layers[1]->Entities[0].get());
		if (System::Events.key.keysym.sym == SDLK_1)
			Player::Set_Entity(pl, State::Layers[1]->Entities[0].get(), true);
		if (System::Events.key.keysym.sym == SDLK_2)
			Player::Set_Entity(pl, State::Layers[1]->Entities[1].get(), true);
		if (System::Events.key.keysym.sym == SDLK_3)
			Player::Set_Entity(pl, State::Layers[1]->Entities[2].get(), true);
		if (System::Events.key.keysym.sym == SDLK_4)
			Player::Set_Entity(pl, State::Layers[1]->Entities[3].get(), true);
		if (System::Events.key.keysym.sym == SDLK_5)
			Player::Set_Entity(pl, State::Layers[1]->Entities[4].get(), true);
		//if (System::Events.key.keysym.sym == SDLK_5)
		//{
		//	Player::Set_Entity(pl, State::Layers[0]->Entities[4].get());
		//	sw->Wealder = State::Layers[0]->Entities[4].get();
		//}
	}


	if (Keyboard_Handler::Key_Up({ SDLK_ESCAPE }))
	{
		for (auto pl : Player::Get_Players())
		{
			Player::Set_Entity(pl.get(), nullptr);
		}
		State::New<Menu_Menu>();
	}

	State::Events();
}

