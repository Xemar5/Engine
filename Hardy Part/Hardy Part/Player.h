#pragma once
#include <initializer_list>
#include <vector>
#include <memory>
#include <SDL.h>
#include "Input_Handler.h"


class Entity;
typedef std::shared_ptr<Input_Handler> Input_Function;

class Player
{
public:
	//*** Initializes a new player and sets it's index to the given one
	//*** If the index is already taken, returns the existing player
	static Player* Set(int index = -1);
	////*** Sets the inp*ut handlers to a given player
	//*** Returns an existing player with a given index if it exists
	static Player* Get(int index);
	//*** Removes the player from the game
	static bool Remove(Player* player);
	//*** Returns an existing player with a given index if it exists
	static int Get_First_Unused_Index();
	//*** Sets the given entity for this player to controll
	//*** - change_mouse_coordinates - if true, the relative x and y coordinates of mouse input will be set
	//***							   to the x and y pos of supplied entity
	static bool Set_Entity(Player* player, Entity* ent);
	//*** Returns the entity given player controlls
	static Entity* Get_Entity(Player* player);
	//*** Returns the container of all created Players
	static std::vector<std::shared_ptr<Player>> Get_Players();
	//*** Returns a vector of all entities that are being controlled by each player
	static std::vector<Entity*> Get_Controlled_Entities();
	//*** A map storing all important actions
	Input_Preset Input_Preset = Input_Handler::Empty_Preset;
private:
	//*** The index of this Player
	int __Index = -1;
	//*** The entity this Player controlls
	Entity* __Entity = nullptr;


	//*** The container of all the Player objectss
	static std::vector<std::shared_ptr<Player>> __Players;

	static void __Update();
	static void __Events();

	friend class Input_Handler;
};

