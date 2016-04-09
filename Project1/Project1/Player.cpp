#include "Player.h"
#include "Input_Handler.h"
#include "Movement.h"
#include "Entity.h"
#include "Sprite.h"
#include "Animation.h"
#include <iostream>

std::vector<std::shared_ptr<Player>> Player::__Players;

Player* Player::Set(int index)
{
	auto* pl = Player::Get(index);
	if (pl)
	{
		std::cout << "MSG Player::Set : Payer with a given index already exists; returning existing player\n";
		return pl;
	}

	Player::__Players.push_back(std::make_shared<Player>());
	if (index < 0) index = Player::Get_First_Unused_Index();
	Player::__Players.back()->__Index = index;
	return Player::__Players.back().get();
}

bool Player::Set_Keys(Player * player,
	std::shared_ptr<Input_Handler> up,
	std::shared_ptr<Input_Handler> down,
	std::shared_ptr<Input_Handler> left,
	std::shared_ptr<Input_Handler> right,
	std::shared_ptr<Input_Handler> aim_v,
	std::shared_ptr<Input_Handler> aim_h)
	{
	if (!player)
	{
		std::cerr << "ERR Player::Set_Keys : No Player supplied\n";
		return false;
	}
	if (!up)
	{
		std::cerr << "ERR Player::Set_Keys : No up input supplied\n";
		return false;
	}
	if (!down)
	{
		std::cerr << "ERR Player::Set_Keys : No down input supplied\n";
		return false;
	}
	if (!left)
	{
		std::cerr << "ERR Player::Set_Keys : No left input supplied\n";
		return false;
	}
	if (!right)
	{
		std::cerr << "ERR Player::Set_Keys : No right input supplied\n";
		return false;
	}
	if (!aim_v)
	{
		std::cerr << "ERR Player::Set_Keys : No Aim Vertical input supplied\n";
		return false;
	}
	if (!aim_h)
	{
		std::cerr << "ERR Player::Set_Keys : No Aim Horizontal input supplied\n";
		return false;
	}

	player->__Up = up;
	player->__Down = down;
	player->__Left = left;
	player->__Right = right;
	player->__Aim_V = aim_v;
	player->__Aim_H = aim_h;

	return true;
}

Player * Player::Get(int index)
{
	if (index < 0) return nullptr;

	for (int i = 0; (unsigned)i < Player::__Players.size(); i++)
		if (Player::__Players[i]->__Index == index)
			return Player::__Players[i].get();

	return nullptr;
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
		std::cerr << "ERR Player::Set_Entity : No Player Supplied\n";
		return false;
	}
	if (!ent)
	{
		std::cerr << "ERR Player::Set_Entity : No Entity supplied\n";
		return false;
	}
	player->__Entity = ent;
	return true;
}

Entity * Player::Get_Entity(Player* player)
{
	if (!player)
	{
		std::cerr << "ERR Player::Get_Entity : No Player supplied\n";
		return nullptr;
	}
	if (!player->__Entity)
	{
		std::cerr << "ERR Player::Get_Entity : Given player controlls no Entity\n";
		return nullptr;
	}
	return player->__Entity;
}

void Player::__Update()
{
	for (unsigned i = 0; i < Player::__Players.size(); i++)
	{
		double vx = 0, vy = 0;
		vy += Player::__Players[i]->__Down->Check();
		vy -= Player::__Players[i]->__Up->Check();
		vx += Player::__Players[i]->__Right->Check();
		vx -= Player::__Players[i]->__Left->Check();
		if (vx < 0) Player::__Players[i]->__Entity->Get_Sprite()->Flip = SDL_FLIP_HORIZONTAL;
		if (vx > 0) Player::__Players[i]->__Entity->Get_Sprite()->Flip = SDL_FLIP_NONE;
		Movement::Add_Force(Player::__Players[i]->__Entity, vx, vy);
	}
}

void Player::__Events()
{
}
