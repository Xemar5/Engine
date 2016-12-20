#pragma once
#include <vector>
#include <memory>
#include "Entity.h"




class Tileset;
template<typename t>
class Entity;
class Texture;


//class Layer
//{
//public:
//	double X = 0;
//	double Y = 0;
//	//*** If true, all entities of this layer will be updated every update tick
//	bool Update_Entities = true;
//	//*** If true, all entities of this layer will be updated every event
//	bool Events_Entities = true;
//	//*** Stores all entities of this layer
//	std::vector<std::shared_ptr<Entity>> Entities;
//	//*** Returns the entity with given index if it exists
//	Entity* operator[](unsigned ent);
//};


class State : protected EntityObject, protected std::enable_shared_from_this<State>
{
public:
	////***  Virtual Create function, should be overriden by derivering states
	//virtual void Create() = 0;
	////***  Virtual Update function, should be overriden by derivering states
	//virtual void Update();
	////***  Virtual Events function, should be overriden by derivering states
	//virtual void Events();

	//***  Virtual Create function, should be overriden by derivering states
	void Create() override = 0;
	//***  Virtual Update function, should be overriden by derivering states
	void Update() override;
	//***  Virtual Events function, should be overriden by derivering states
	void Events() override;


	//*** Stores all layers of this State
	//*** That's where all entities are stored
	//std::vector<std::shared_ptr<Layer>> Layers;

	//*** Returns the top-most built state
	static State* CurrentState() { return Built.back().get(); }
	//*** Returns the position of the top-most state in Built states vector
	static unsigned CurrentStateNo() { return Built.size() - 1; }
	//*** Returns the position of the given state in Built states vector
	static unsigned StateNo(State* stt) { for (unsigned i = 0; i < Built.size(); ++i) if (Built[i].get() == stt) return i; }
	//*** All Built States
	//*** Atleast one of them will get Update'd and Evente'd
	//*** (most of the time the the top State or all of them)
	static std::vector<std::shared_ptr<State>> Built;

	//*** Deleted states in this System loop
	//*** They will be removed at the begining of the next System loop
	static std::vector<unsigned> Deleted;


	//*** Creates an entity of supplied type to this state and creates it
	//*** Supplied entity has to deriver from Entity class
	//*** - layer - adds the entity to given layer
	//*** 			if the layer doesn't exist yet, this function will create all layers between
	template<typename T = EntityObject> Entity<T> Add_Entity(unsigned layer = unsigned(0));
	//*** Adds supplied entity to the state as new object independent from the parent
	template<typename T>				Entity<T> Add_Entity(std::shared_ptr<T> entity, unsigned layer = 0);
	//*** Changes the Layer of an entity
	static bool Change_Entity_Layer(Entity<> entity, unsigned new_layer);



	//*** Builds and creates a new state of given type
	//*** Deletes all previously built states and state layers
	template <typename T> static std::shared_ptr<T> New(std::vector<Entity<>> persistant_entities = {});
	//*** Builds and creates a new state layer of given type
	//*** - update_underneath - if true, System will update all state layers
	//***     aswell as the main state built before
	//*** 	else only this state layer will be updated
	template <typename T> static std::shared_ptr<T> New_Layer(bool update_underneath = false);
	//*** Exits the current state layer and destroys it
	//*** Works only if there is at least one state layer built, prints MSG otherwise
	template <bool = true> static void Exit_Layer();
	//*** Exits the game, destroy all states and state layers
	template <bool = true> static void Exit_Game();

	//*** If true, System will update all state layers aswell as the main state built before
	//*** Else only this state layer will be updated
	bool Update_Underneath = false;

	//	//*** Creates a Tileset with supplied mapping and adds it to this State's Tilesets container
	//	//*** - texture - the Texture class containing image file of all tiles
	//	//*** - pos - the position of this tileset in this State
	//	//*** - map - the mapping of all tiles
	//	std::shared_ptr<Tileset> Add_Tileset(std::shared_ptr<Texture> texture, unsigned layer, std::pair<int, int> pos, std::vector<std::vector<unsigned>> map);

	////*** Returns the container of all Tilesets from all layers in this State
	//std::vector<Tileset*> Get_Tilesets();
	//*** Returns the container of all Entities from all layers in this State
	std::vector<Entity<>> Get_Entities();
	//*** Returns an entity with given index if it exists
	Entity<> Ent(unsigned ent);
	//*** Removes this entity from the state, from players controlls and destroys it
	bool Remove_Entity(Entity<> ent);

	//	//*** Returns the container of all Walls from all layers in this State
	//	std::vector<std::shared_ptr<Entity>> Get_Walls();

	//*** Operator [] overload returns the layer with given index
	//*** if such layer doesn't exist, returns nullptr
	//Layer& operator[](unsigned layer);
private:
	//*** The container of all Entities this state has
	//*** To add an entity use Add_Entity functions
	std::vector<Entity<>> __Entities;

	friend class System;
};



#include "Screen.h"
#include "Output_Handler.h"
#include "Entity.h"
#include "Player.h"

#include "Menu_State.h"
#include "Main_State.h"
#include "GameMenu_State.h"
#include "Controlls_State.h"


//*** Creates an entity of supplied type to this state and creates it
//*** Supplied entity has to deriver from Entity class
//*** - layer - adds the entity to given layer
//*** 			if the layer doesn't exist yet, this function will create all layers between
template <typename T>
Entity<T> State::Add_Entity(unsigned layer)
{
	if (!this)
	{
		Output_Handler::Error << "ERR State::Add_Entity : No this state\n";
		return nullptr;
	}
	Entity<T> e = std::make_shared<T>();
	__Entities.push_back(e);
	__Entities.back()->layer = layer;
	__Entities.back()->Create();
	Screen::Add(__Entities.back());
	return __Entities.back();
}

//*** Adds supplied entity to the state as new object independent from the parent
template <typename T>
Entity<T> State::Add_Entity(std::shared_ptr<T> entity, unsigned layer)
{
	if (!this)
	{
		Output_Handler::Error << "ERR State::Add_Entity : No this state\n";
		return nullptr;
	}
	if (!entity)
	{
		Output_Handler::Error << "ERR State::Add_Entity : No entity supplied\n";
		return nullptr;
	}
	__Entities.push_back(entity);
	if(layer != -1)	__Entities.back()->layer = layer;
	__Entities.back()->Create();

	Screen::Add(__Entities.back());
	return __Entities.back();
}


//*** Creates and initializes new State
//*** Template parameter must be supplied with an State derative
//*** Destroys all built State layers and creates new stack
template <typename T>
std::shared_ptr<T> State::New(std::vector<Entity<>> persistant_entities)
{
	Device::ClearAllDeviceInput();
	//Entity::__Registered.clear();

	for (unsigned i = 0; i < State::Built.size(); i++)
		State::Deleted.push_back(i);

	for (auto& p : Player::Get_Players())
	{
		bool has_persis_ent = false;
		for (auto& e : persistant_entities)
			if (p->__Entity == e)
			{
				has_persis_ent = true;
				break;
			}
		if (!has_persis_ent) p->__Entity = nullptr;
	}
	Screen::__Entities.clear();
	Screen::__Entities.push_back({});
	State::Built.push_back(std::make_shared<T>());
	////NetworkID::Reset();
	////Network::RPC_Saved.clear();

	for(auto ptr : persistant_entities)
		if(ptr) State::Built.back()->Add_Entity(ptr.get_shared(), ptr->layer);

	State::Built.back().get()->Create();
	return std::static_pointer_cast<T>(State::Built.back());
	//return nullptr;
}


//*** Creates new State layer
//*** Each layer is build on top of an existing one
//*** Layers underneath are not destroyed
//*** - update_underneath - if true, layers underneath will be updated every game tick
template <typename T>
std::shared_ptr<T> State::New_Layer(bool update_underneath)
{
	Device::ClearAllDeviceInput();
	Screen::__Entities.push_back({});
	State::Built.emplace_back(std::make_shared<T>());
	State::Built.back().get()->Update_Underneath = update_underneath;
	State::Built.back().get()->Create();
	return std::static_pointer_cast<T>(State::Built.back());
}

//*** Exits the top State layer and destroys it
template <bool T>
void State::Exit_Layer()
{
	Device::ClearAllDeviceInput();
	Screen::__Entities.pop_back();
	State::Deleted.push_back(State::Built.size() - 1);
}


//*** Exits the game 
template <bool T>
void State::Exit_Game()
{
	Device::ClearAllDeviceInput();
	Screen::__Entities.clear();
	for (unsigned i = 0; i < State::Built.size(); i++)
		State::Deleted.push_back(i);
}
