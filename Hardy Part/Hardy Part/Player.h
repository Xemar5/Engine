#pragma once
#include <initializer_list>
#include <vector>
#include <memory>
#include <SDL.h>


class Entity;
typedef double(*Input_Function)(std::vector<Sint32>);

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
	//*** Sets the controller of a player based on the given device index
	static bool Set_Controller(Player* player, Sint32 controller);
	//*** The index of this Player
	Sint32 Controller = -2;
	//*** Sets the given entity for this player to controll
	//*** - change_mouse_coordinates - if true, the relative x and y coordinates of mouse input will be set
	//***							   to the x and y pos of supplied entity
	static bool Set_Entity(Player* player, std::shared_ptr<Entity> ent);
	//*** Returns the entity given player controlls
	static std::shared_ptr<Entity> Get_Entity(Player* player);
	//*** Returns the container of all created Players
	static std::vector<std::shared_ptr<Player>> Get_Players();
	//*** Returns a vector of all entities that are being controlled by each player
	static std::vector<std::shared_ptr<Entity>> Get_Controlled_Entities();
	//*** The maximum number of players
	static unsigned Max_Players;
private:
	int __Index = -1;
	//*** The entity this Player controlls
	std::shared_ptr<Entity> __Entity = nullptr;

	//*** Vecotr of all used input presets from a file
	//*** An used input preset can't be used again
	static std::vector<std::string> __Used_Presets;


	//*** The container of all the Player objectss
	static std::vector<std::shared_ptr<Player>> __Players;

	static void __Update();
	static void __Events();

	friend class System;
};

