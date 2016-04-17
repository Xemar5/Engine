#pragma once
#include "Entity.h"

class State;

class Character : public Entity
{
public:
	void Create() override;
	void Update() override;
	void Events() override;
	//*** Creates the character of given name in specific coordinates
	//*** if given name is not registered, no character will be created
	static Character* Add(State* stt, std::string name, int x, int y, unsigned layer);
};

