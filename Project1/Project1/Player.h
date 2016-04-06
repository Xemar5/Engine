#pragma once
#include <initializer_list>
#include <vector>
#include <memory>
#include <SDL.h>


class Entity;
class Input_Handler;

class Player
{
public:
	//*** Initializes a new player and sets it's index to the given one
	//*** If the index is already taken, returns the existing player
	static Player* Set(int index = -1);
	//*** Sets the input handlers to a given player
	static bool Set_Keys
		(
			Player* player,
			std::shared_ptr<Input_Handler> up,
			std::shared_ptr<Input_Handler> down,
			std::shared_ptr<Input_Handler> left,
			std::shared_ptr<Input_Handler> right
		);
	//*** Returns an existing player with a given index if it exists
	static Player* Get(int index);
	//*** Returns an existing player with a given index if it exists
	static int Get_First_Unused_Index();
	//*** Sets the given entity for this player to controll
	static bool Set_Entity(Player* player, Entity* ent);
	//*** Returns the entity given player controlls
	static Entity* Get_Entity(Player* player);

private:
	//*** The index of this Player
	int __Index = -1;
	//*** The entity this Player controlls
	Entity* __Entity = nullptr;

	//*** The up key function
	//*** Use with Gamepad_Handler or Keyboard_Handler
	std::shared_ptr<Input_Handler> __Up = nullptr;
	//*** The down key function
	//*** Use with Gamepad_Handler or Keyboard_Handler
	std::shared_ptr<Input_Handler>__Down = nullptr;
	//*** The left key function
	//*** Use with Gamepad_Handler or Keyboard_Handler
	std::shared_ptr<Input_Handler>__Left = nullptr;
	//*** The right key function
	//*** Use with Gamepad_Handler or Keyboard_Handler
	std::shared_ptr<Input_Handler>__Right = nullptr;

	//*** The container of all the Player objectss
	static std::vector<std::shared_ptr<Player>> __Players;

	static void __Update();
	static void __Events();

	friend class Input_Handler;
};


#undef PLAYER_KEYBIND
