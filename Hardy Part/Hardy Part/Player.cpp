#include "Player.h"
#include "Input_Handler.h"
#include "Mouse_Handler.h"
#include "Movement.h"
#include "Entity.h"
#include "Sprite.h"
#include "Animation.h"
#include "Output_Handler.h"

std::vector<std::shared_ptr<Player>> Player::__Players;

Player* Player::Set(int index)
{
	auto* pl = Player::Get(index);
	if (pl)
	{
		Output_Handler::Output << "MSG Player::Set : Payer with a given index already exists; returning existing player\n";
		return pl;
	}

	Player::__Players.push_back(std::make_shared<Player>());
	if (index < 0) index = Player::Get_First_Unused_Index();
	Player::__Players.back()->__Index = index;
	return Player::__Players.back().get();
}


//bool Player::Set_Keys(Player * player,
//	Input_Function up,
//	Input_Function down,
//	Input_Function left,
//	Input_Function right,
//	Input_Function aim_v,
//	Input_Function aim_h)
//	{
//	if (!player)
//	{
//		Output_Handler::Error << "ERR Player::Set_Keys : No Player supplied\n";
//		return false;
//	}
//	if (!up)
//	{
//		Output_Handler::Error << "ERR Player::Set_Keys : No up input supplied\n";
//		return false;
//	}
//	if (!down)
//	{
//		Output_Handler::Error << "ERR Player::Set_Keys : No down input supplied\n";
//		return false;
//	}
//	if (!left)
//	{
//		Output_Handler::Error << "ERR Player::Set_Keys : No left input supplied\n";
//		return false;
//	}
//	if (!right)
//	{
//		Output_Handler::Error << "ERR Player::Set_Keys : No right input supplied\n";
//		return false;
//	}
//	if (!aim_v)
//	{
//		Output_Handler::Error << "ERR Player::Set_Keys : No Aim Vertical input supplied\n";
//		return false;
//	}
//	if (!aim_h)
//	{
//		Output_Handler::Error << "ERR Player::Set_Keys : No Aim Horizontal input supplied\n";
//		return false;
//	}
//
//	player->__Up = up;
//	player->__Down = down;
//	player->__Left = left;
//	player->__Right = right;
//	player->__Aim_V = aim_v;
//	player->__Aim_H = aim_h;
//
//	return true;
//}

Player * Player::Get(int index)
{
	if (index < 0) return nullptr;

	for (int i = 0; (unsigned)i < Player::__Players.size(); i++)
		if (Player::__Players[i]->__Index == index)
			return Player::__Players[i].get();

	return nullptr;
}

bool Player::Remove(Player * player)
{
	if (!player)
	{
		Output_Handler::Error << "ERR Player::Remove : no Player supplied\n";
		return false;
	}
	for (unsigned i = 0; i < Player::Get_Players().size(); ++i)
		if (Player::Get_Players()[i].get() == player)
		{
			__Players.erase(__Players.begin() + i);
			return true;
		}
	return false;
}

int Player::Get_First_Unused_Index()
{
	int index = 0;
	for (int i = 0; (unsigned)i < Player::__Players.size();)
		if (Player::__Players[i]->__Index == index)
		{
			++index;
			i = 0;
		}
		else ++i;
	return index;
}

bool Player::Set_Entity(Player* player, Entity * ent)
{
	if (!player)
	{
		Output_Handler::Error << "ERR Player::Set_Entity : No Player Supplied\n";
		return false;
	}
	player->__Entity = ent;
	return true;
}

Entity * Player::Get_Entity(Player* player)
{
	if (!player)
	{
		Output_Handler::Error << "ERR Player::Get_Entity : No Player supplied\n";
		return nullptr;
	}
	if (!player->__Entity)
	{
		Output_Handler::Error << "ERR Player::Get_Entity : Given player controlls no Entity\n";
		return nullptr;
	}
	return player->__Entity;
}

std::vector<std::shared_ptr<Player>> Player::Get_Players()
{
	return __Players;
}

std::vector<Entity*> Player::Get_Controlled_Entities()
{
	std::vector<Entity*> v(Player::Get_Players().size());
	for (unsigned i = 0; i < Player::Get_Players().size(); ++i)
		v[i] = Player::Get_Entity(Player::Get_Players()[i].get());
	return v;
}

void Player::__Update()
{
	//for (unsigned i = 0; i < Player::__Players.size(); i++)
	//{
	for(auto p : Player::__Players)
	{
		if (Entity* ent = Get_Entity(p.get()))
		{

			auto& ip = p->Input_Preset;


			double vx = 0, vy = 0;
			vy += ip["ladown"]->Check();
			vy -= ip["laup"]->Check();
			vx += ip["laright"]->Check();
			vx -= ip["laleft"]->Check();


			if (vx < 0) p->__Entity->Get_Sprite()->Flip = SDL_FLIP_HORIZONTAL;
			if (vx > 0) p->__Entity->Get_Sprite()->Flip = SDL_FLIP_NONE;
			Movement::Add_Force(p->__Entity, vx, vy);


			double(*foo)(std::vector<Sint32>) = nullptr;

			Sint32 x = (Sint32)ent->X;
			Sint32 y = (Sint32)ent->Y;

			for (auto& foo : ip)
			{
				if (!foo.second) continue;
				if (foo.second->Input_Function == Mouse_Handler::Get_Relative_Mouse_X_State ||
					foo.second->Input_Function == Mouse_Handler::Get_Relative_Mouse_Y_State)
				{
					foo.second->Input_Args[0] = x;
					foo.second->Input_Args[1] = y;
				}
			}
		}
	}
}

void Player::__Events()
{
}
