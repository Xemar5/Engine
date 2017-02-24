#pragma once
#include "Input.h"
#include "Mapping.h"



class Player
{
public:
	//*** Adds a new player
	//*** - device - if set to unsigned max (-1), player is not local
	//***			 otherwise users will be asked for defining this
	//***			 player's device mapping if not already defined
	static std::shared_ptr<Player> Add(unsigned device);

	//*** Returns an input mapped to supplied name if exists
	controlls::Input& GetInput(std::string input_name);

	//*** Returns the index of a device this player uses
	//*** Can be changed with SetDevice  function
	unsigned device() const { return _device; }

	//*** Changes the device this player uses
	//*** This function also updates mapping stored in this player
	//*** If the new device mapping is not defined, user will be asked to do it
	void SetDevice(unsigned device);

	//*** Vector containing all created players
	static std::vector<std::shared_ptr<Player>> players;
	//*** Player class of user of this machine
	static std::shared_ptr<Player> me;

	Player() = default;
protected:

	//*** The index of a device this player uses
	//*** Can be changed with SetDevice  function
	unsigned _device = -1;

	//*** All stored inputs andtheir names
	controlls::Mapping::MapInputs _mapping;

	friend class controlls::Mapping;
};

