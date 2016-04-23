#pragma once
#include <initializer_list>
#include <vector>
#include <memory>
#include <SDL.h>


class Entity;
class Input_Handler;
typedef std::shared_ptr<Input_Handler> Input_Function;

class Player
{
public:
	//*** Initializes a new player and sets it's index to the given one
	//*** If the index is already taken, returns the existing player
	static Player* Set(int index = -1);
	//*** Returns the keybingings of the given player
	static std::vector<Input_Function> Get_Keys(Player* player);
	//*** Sets the input handlers to a given player
	static bool Set_Keys
		(
			Player* player,
			Input_Function up,
			Input_Function down,
			Input_Function left,
			Input_Function right,
			Input_Function aim_v,
			Input_Function aim_h
	);
	//*** Returns an existing player with a given index if it exists
	static Player* Get(int index);
	//*** Returns an existing player with a given index if it exists
	static int Get_First_Unused_Index();
	//*** Sets the given entity for this player to controll
	//*** - change_mouse_coordinates - if true, the relative x and y coordinates of mouse input will be set
	//***							   to the x and y pos of supplied entity
	static bool Set_Entity(Player* player, Entity* ent, bool change_mouse_coordinates = false);
	//*** Returns the entity given player controlls
	static Entity* Get_Entity(Player* player);
	//*** Returns the container of all created Players
	static std::vector<std::shared_ptr<Player>> Get_Players();
private:
	//*** The index of this Player
	int __Index = -1;
	//*** The entity this Player controlls
	Entity* __Entity = nullptr;

	//*** The up input function
	Input_Function __Up = nullptr;
	//*** The down input function
	Input_Function __Down = nullptr;
	//*** The left input function
	Input_Function __Left = nullptr;
	//*** The right input function
	Input_Function __Right = nullptr;
	//*** The aim vertical input function
	Input_Function __Aim_V = nullptr;
	//*** The aim horizontal input function
	Input_Function __Aim_H = nullptr;

	//*** The container of all the Player objectss
	static std::vector<std::shared_ptr<Player>> __Players;

	static void __Update();
	static void __Events();

	friend class Input_Handler;
};

