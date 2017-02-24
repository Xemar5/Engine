#pragma once
#include <vector>
#include <memory>
#include "Entity.h"
#include "Container.h"
#include "LayerContainer.h"
#include "Network\Network.h"
#include "Camera.h"

class Tileset;
class Texture;
namespace network {
	class Peer;
}

class State : public LayerContainer
{
public:

	//*** Virtual Create function, should be overriden by derivering states
	virtual void Create() = 0;
	//*** Virtual Update function, should be overriden by derivering states
	virtual void Update();
	//*** Virtual Events function, should be overriden by derivering states
	virtual void Events();
	//*** Fires when state is beind deleted
	//*** Use to delete allocated data
	virtual void Cleanup() {}

	//*** If true, System will update all state layers aswell as the main state built before
	//*** Else only this state layer will be updated
	bool Update_Underneath = false;

	enum class Phase
	{
		SystemReserved,
		StateCreate,
		StateUpdate,
		StateEvents,
		ObjectCreate,
		ObjectUpdate,
		ObjectEvents
	};

	//*** Returns the phase of this state
	static Phase state_phase() { return _state_phase; }



	//*** Returns the top-most built state
	static std::shared_ptr<State> CurrentState();
	//*** All Built States
	//*** Atleast one of them will get Update'd and Evente'd
	//*** (most of the time the the top State or all of them)
	static std::vector<std::shared_ptr<State>> Built;

	//*** Deleted states in this System loop
	//*** They will be removed at the begining of the next System loop
	static std::vector<unsigned> Deleted;
	//*** Newly created states in this System loop
	//*** Their Create function will fire at the begining of the next System loop
	static std::vector<unsigned> Created;




	//*** Builds and creates a new state of given type
	//*** Deletes all previously built states and state layers
	template <typename T, typename... Args> static std::shared_ptr<T> Change(Args&&... args);
	//*** Builds and creates a new state layer of given type
	//*** - update_underneath - if true, System will update all state layers
	//***     aswell as the main state built before
	//*** 	else only this state layer will be updated
	template <typename T, bool update_underneath = false, typename... Args> static std::shared_ptr<T> Add(Args&&... args);
	//*** Exits the current state layer and destroys it
	//*** Works only if there is at least one state layer built, prints MSG otherwise
	template <bool = true> static void Remove();
	//*** Exits the game, destroy all states and state layers
	template <bool = true> static void Exit_Game();


	//*** Received messages
	//*** Resolved at the end of this state update loop
	std::vector<std::pair<network::message::Type, std::shared_ptr<std::istream>>> received_function_calls;


	virtual ~State() = 0 {};
private:
	void __Update(std::shared_ptr<Object> e);
	void __Events(std::shared_ptr<Object> e);

	//*** Checks if given state is being deleted
	static bool __isDeleted(std::shared_ptr<State> stt);

	//*** Current phase of this state
	static Phase _state_phase;

	//*** Pointer to the current state
	static std::shared_ptr<State> _CurrentState;



	friend void network::impl::tcp::Init();
	friend class System;
	friend class Screen;
	friend class Layer;
};









#include "Screen.h"
#include "Output_Handler.h"
#include "Entity.h"
#include "Player.h"
#include "Sprite.h"
#include "Layer.h"
#include "Generic.h"
#include "Shape.h"



//*** Creates and initializes new State
//*** Template parameter must be supplied with an State derative
//*** Destroys all built State layers and creates new stack
template <typename T, typename... Args>
std::shared_ptr<T> State::Change(Args&&... args)
{
	//if (__isDeleted(CurrentState())) return nullptr;

	_state_phase = Phase::SystemReserved;

	for (unsigned i = 0; i < Built.size(); i++)
		Deleted.push_back(i);
	network::message::messages[0].clear();
	network::message::messages[2].clear();
	
	Built.push_back(std::make_shared<T>(std::forward<Args>(args)...));
	Created.push_back(Built.size() - 1);

	//_state_phase = Phase::StateCreate;
	//_CurrentState = Built.back();
	//Built.back()->Create();
	//_CurrentState = nullptr;
	//_state_phase = Phase::SystemReserved;

	return std::static_pointer_cast<T>(Built.back());
}


//*** Creates new State layer
//*** Each layer is build on top of an existing one
//*** Layers underneath are not destroyed
//*** - update_underneath - if true, layers underneath will be updated every game tick
template <typename T, bool update_underneath, typename... Args>
std::shared_ptr<T> State::Add(Args&&... args)
{
	//if (__isDeleted(CurrentState())) return nullptr;

	_state_phase = Phase::SystemReserved;

	Built.push_back(std::make_shared<T>(std::forward<Args>(args)...));
	Built.back()->Update_Underneath = update_underneath;
	Created.push_back(Built.size() - 1);
	
	//_state_phase = Phase::StateCreate;
	//_CurrentState = Built.back();
	//Built.back()->Create();
	//_CurrentState = nullptr;
	//_state_phase = Phase::SystemReserved;
	
	return std::static_pointer_cast<T>(Built.back());
}

//*** Exits the top State layer and destroys it
template <bool T>
void State::Remove()
{
	if (!__isDeleted(CurrentState()))
	{
		Deleted.push_back(Built.size() - 1);
	}
}


//*** Exits the game 
template <bool T>
void State::Exit_Game()
{
	if (!__isDeleted(CurrentState()))
	{
		for (unsigned i = 0; i < Built.size(); i++)
			Deleted.push_back(i);
	}
}

