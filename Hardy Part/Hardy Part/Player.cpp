#include "Player.h"
#include "Input.h"
#include "Movement.h"
#include "Entity.h"
#include "Sprite.h"
#include "Animation.h"
#include "Output_Handler.h"

std::vector<std::shared_ptr<Player>> Player::__Players;
std::vector<std::string> Player::__Used_Presets;
unsigned Player::Max_Players = 4;

std::shared_ptr<Player> Player::Set(int index)
{
	auto pl = Player::Get(index);
	if (pl)
	{
		Output_Handler::Output << "MSG Player::Change : Payer with a given index already exists; returning existing player\n";
		return pl;
	}

	if (index < 0) index = Player::Get_First_Unused_Index();
	if (index >= (int)Player::Max_Players)
	{
		Output_Handler::Output << "MSG Player::Change : Exceding the max number of players (" << Player::Max_Players << ")\n";
		return nullptr;
	}
	Player::__Players.push_back(std::make_shared<Player>());
	Player::__Players.back()->__Index = index;
	return Player::__Players.back();
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

std::shared_ptr<Player> Player::Get(int index)
{
	if (index < 0) return nullptr;

	for (int i = 0; (unsigned)i < Player::__Players.size(); i++)
		if (Player::__Players[i]->__Index == index)
			return Player::__Players[i];

	return nullptr;
}

bool Player::Remove(std::shared_ptr<Player> player)
{
	if (!player)
	{
		Output_Handler::Error << "ERR Player::Remove : no Player supplied\n";
		return false;
	}
	for (unsigned i = 0; i < Player::Get_Players().size(); ++i)
		if (Player::Get_Players()[i] == player)
		{
			__Players[i]->__Entity = nullptr;
			__Players.erase(__Players.begin() + i);
			return true;
		}
	return false;
}

bool Player::RemoveAll()
{
	while (__Players.size())
		if(!Remove(__Players[__Players.size() - 1])) return false;
	return true;
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

bool Player::Set_Controller(std::shared_ptr<Player> player, Sint32 controller)
{
	if (!player)
	{
		Output_Handler::Error << "ERR Player::Set_Controller : No player supplied\n";
		return false;
	}
	//if (controller < -2 || contro)
	//{
	//	Output_Handler::Error << "Player::Set_Controller : No controller supplied\n";
	//	return false;
	//}
	player->Controller = controller;
	//player->__ControllerName = controlls::Device::Get(controller).Name();
	return true;
}

bool Player::Set_Entity(std::shared_ptr<Player> player, std::shared_ptr<Entity> ent)
{
	if (!player)
	{
		Output_Handler::Error << "ERR Player::Set_Entity : No Player Supplied\n";
		return false;
	}
	player->__Entity = ent;
	return true;
}

std::shared_ptr<Entity> Player::Get_Entity(std::shared_ptr<Player> player)
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

std::vector<std::shared_ptr<Entity>> Player::Get_Controlled_Entities()
{
	std::vector<std::shared_ptr<Entity>> v(Player::Get_Players().size());
	for (unsigned i = 0; i < Player::Get_Players().size(); ++i)
		v[i] = Player::Get_Entity(Player::Get_Players()[i]);
	return v;
}

void Player::__Update()
{
	//for (unsigned i = 0; i < Player::__Players.size(); i++)
	//{
	for(auto p : Player::__Players)
	{
		if (p->Controller == -2) continue;
		if (auto ent = Get_Entity(p))
		{

			//auto& ip = controlls::Device::Get(p->Controller);

			auto sgn = [](double d) {return d ? d / abs(d) : 0; };
			double vx = 0, vy = 0;
			//vy += sgn(ip["ladown"].Held()) - sgn(ip["laup"].Held());
			//vx += sgn(ip["laright"].Held()) - sgn(ip["laleft"].Held());


			if (vx < 0) p->__Entity->texture->Flip = SDL_FLIP_HORIZONTAL;
			if (vx > 0) p->__Entity->texture->Flip = SDL_FLIP_NONE;
			Movement::Add_Force(p->__Entity, vx, vy);


			double(*foo)(std::vector<Sint32>) = nullptr;

			Sint32 x = (Sint32)ent->X;
			Sint32 y = (Sint32)ent->Y;

			//for (auto& foo : ip)
			//{
			//	if (!foo.second) continue;
			//	if (foo.second->Input_Function == Mouse_Handler::Get_Relative_Mouse_X_State ||
			//		foo.second->Input_Function == Mouse_Handler::Get_Relative_Mouse_Y_State)
			//	{
			//		foo.second->Input_Args[0] = x;
			//		foo.second->Input_Args[1] = y;
			//	}
			//}
		}
	}
}

void Player::__Events()
{
}
