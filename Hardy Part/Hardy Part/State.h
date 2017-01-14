#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Container.h"
#include "StateContainer.h"
#include "Network\Network.h"

class Tileset;
class Texture;

class State : public StateContainer
{
public:

	//***  Virtual Create function, should be overriden by derivering states
	virtual void Create() = 0;
	//***  Virtual Update function, should be overriden by derivering states
	virtual void Update();
	//***  Virtual Events function, should be overriden by derivering states
	virtual void Events();

	//*** If true, System will update all state layers aswell as the main state built before
	//*** Else only this state layer will be updated
	bool Update_Underneath = false;

	enum class StatePhase
	{
		SystemReserved,
		Create,
		Update,
		Events
	};

	//*** Returns the phase of this state
	static StatePhase state_phase() { return _state_phase; }



	//*** Returns the top-most built state
	static std::shared_ptr<State> CurrentState();
	//*** All Built States
	//*** Atleast one of them will get Update'd and Evente'd
	//*** (most of the time the the top State or all of them)
	static std::vector<std::shared_ptr<State>> Built;

	//*** Deleted states in this System loop
	//*** They will be removed at the begining of the next System loop
	static std::vector<unsigned> Deleted;




	//*** Builds and creates a new state of given type
	//*** Deletes all previously built states and state layers
	template <typename T> static std::shared_ptr<T> Change();
	//*** Builds and creates a new state layer of given type
	//*** - update_underneath - if true, System will update all state layers
	//***     aswell as the main state built before
	//*** 	else only this state layer will be updated
	template <typename T> static std::shared_ptr<T> Add(bool update_underneath = false);
	//*** Exits the current state layer and destroys it
	//*** Works only if there is at least one state layer built, prints MSG otherwise
	template <bool = true> static void Remove();
	//*** Exits the game, destroy all states and state layers
	template <bool = true> static void Exit_Game();

	virtual ~State() = 0 {};
private:
	void __Update(std::shared_ptr<Body> e);
	void __Events(std::shared_ptr<Body> e);

	//*** Checks if given state is being deleted
	static bool __isDeleted(std::shared_ptr<State> stt);

	//*** Current phase of this state
	static StatePhase _state_phase;

	friend void network::impl::tcp::Init();
	friend class System;
	friend class Screen;
};









#include "Screen.h"
#include "Output_Handler.h"
#include "Entity.h"
#include "Player.h"
#include "Sprite.h"
#include "Layer.h"
#include "Generic.h"




//*** Creates and initializes new State
//*** Template parameter must be supplied with an State derative
//*** Destroys all built State layers and creates new stack
template <typename T>
std::shared_ptr<T> State::Change()
{
	if (__isDeleted(CurrentState())) return nullptr;

	_state_phase = StatePhase::SystemReserved;

	Device::ClearAllDeviceInput();

	for (unsigned i = 0; i < Built.size(); i++)
		Deleted.push_back(i);
	network::message::messages[0].clear();
	network::message::messages[2].clear();

	Built.push_back(std::make_shared<T>());

	_state_phase = StatePhase::Create;
	Built.back()->Create();
	_state_phase = StatePhase::SystemReserved;

	return std::static_pointer_cast<T>(Built.back());
}


//*** Creates new State layer
//*** Each layer is build on top of an existing one
//*** Layers underneath are not destroyed
//*** - update_underneath - if true, layers underneath will be updated every game tick
template <typename T>
std::shared_ptr<T> State::Add(bool update_underneath)
{
	if (__isDeleted(CurrentState())) return nullptr;

	_state_phase = StatePhase::SystemReserved;

	Device::ClearAllDeviceInput();
	Built.emplace_back(std::make_shared<T>());
	Built.back()->Update_Underneath = update_underneath;
	//Built.back()->State::Create();
	
	_state_phase = StatePhase::Create;
	Built.back()->Create();
	_state_phase = StatePhase::SystemReserved;
	
	return std::static_pointer_cast<T>(Built.back());
}

//*** Exits the top State layer and destroys it
template <bool T>
void State::Remove()
{
	if (!__isDeleted(CurrentState()))
	{
		Device::ClearAllDeviceInput();
		Deleted.push_back(Built.size() - 1);
	}
}


//*** Exits the game 
template <bool T>
void State::Exit_Game()
{
	if (!__isDeleted(CurrentState()))
	{
		Device::ClearAllDeviceInput();
		for (unsigned i = 0; i < Built.size(); i++)
			Deleted.push_back(i);
	}
}

