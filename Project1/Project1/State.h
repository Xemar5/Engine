#pragma once
#include <vector>
#include <memory>

class Tileset;
class Entity;

class Layer
{
public:
	//*** If true, all entities of this layer will be updated every update tick
	bool Update_Entities = true;
	//*** If true, all entities of this layer will be updated every event
	bool Events_Entities = true;
	//*** Stores all entities of this layer
	std::vector<std::shared_ptr<Entity>> Entities;
};


class State
{
public:
	//***  Virtual Create function, should be overriden by derivering states
	virtual void Create() = 0;
	//***  Virtual Update function, should be overriden by derivering states
	virtual void Update();
	//***  Virtual Events function, should be overriden by derivering states
	virtual void Events();


	//*** Stores all layers of this State
	//*** That's where all entities are stored
	std::vector<std::shared_ptr<Layer>> Layers;

	//*** All Built States
	//*** Atleast one of them will get Update'd and Evente'd
	//*** (most of the time the the top State or all of them)
	static std::vector<std::shared_ptr<State>> Built;

	//*** Deleted states in this System loop
	//*** They will be removed at the begining of the next System loop
	static std::vector<unsigned> Deleted;


	//*** Adds an entity of supplied type to this state and creates it
	//*** Supplied entity has to deriver from Entity class
	//*** - layer - adds the entity to given layer
	//*** 	if the layer doesn't exist yet, this function will create all layers between
	template<typename T> T * Add_Entity(unsigned layer = unsigned(0));


	//*** Builds and creates a new state of given type
	//*** Deletes all previously built states and state layers
	template <typename T> static T* New();
	//*** Builds and creates a new state layer of given type
	//*** - update_underneath - if true, System will update all state layers
	//***     aswell as the main state built before
	//*** 	else only this state layer will be updated
	template <typename T> static T* New_Layer(bool update_underneath = false);
	//*** Exits the current state layer and destroys it
	//*** Works only if there is at least one state layer built, prints MSG otherwise
	template <bool = true> static void Exit_Layer();
	//*** Exits the game, destroy all states and state layers
	template <bool = true> static void Exit_Game();

	//*** If true, System will update all state layers aswell as the main state built before
	//*** Else only this state layer will be updated
	bool Update_Underneath = false;

	//*** The Tileset of this State
	std::shared_ptr<Tileset> Tile_Set = nullptr;
};

template <typename T>
T* State::Add_Entity(unsigned layer)
{
	while (Layers.size() <= layer) Layers.emplace_back(std::make_shared<Layer>());
	Layers[layer]->Entities.emplace_back(std::make_shared<T>());
	Layers[layer]->Entities.back()->Create();
	Layers[layer]->Entities.back()->__Layer = layer;
	return dynamic_cast<T*>(Layers[layer]->Entities.back().get());
}


template <typename T>
T* State::New()
{
	for (unsigned i = 0; i < State::Built.size(); i++)
		State::Deleted.push_back(i);
	State::Built.emplace_back(std::make_shared<T>());
	State::Built.back().get()->Create();
	return dynamic_cast<T*>(State::Built.back().get());
}
template <typename T>
T* State::New_Layer(bool update_underneath)
{
	State::Built.emplace_back(std::make_shared<T>());
	State::Built.back().get()->Update_Underneath = update_underneath;
	State::Built.back().get()->Create();
	return dynamic_cast<T*>(State::Built.back().get());
}
template <bool T>
void State::Exit_Layer()
{
	State::Deleted.push_back(State::Built.size() - 1);
}
template <bool T>
void State::Exit_Game()
{
	for (unsigned i = 0; i < State::Built.size(); i++)
		State::Deleted.push_back(i);
}
