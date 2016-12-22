#pragma once
#include "Entity.h"

class State;

class Character : public ent::EntityObject
{
public:
	void Create() override;
	void Update() override;
	void Events() override;
	//*** Creates the character of given name in specific coordinates
	//*** if given name is not registered, no character will be created
	static ent::Entity<> Add(unsigned state, std::string name, int x = 0, int y = 0, unsigned layer = 0, double scale = 1);
	static void RPC_Add(unsigned state, std::string name, int x, int y, unsigned layer, double scale);
};

