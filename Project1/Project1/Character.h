#pragma once


enum Character_Enums
{
	Nerk,
	Mosh,
	Dreg,
	Tar,
	Raiden
};

#include "Entity.h"
#include <string>

template <Character_Enums type>
class Character : public Entity
{
public:
	Character_Enums Number = type;
	void Create() override;
	void Update() override;
	void Events() override;
};
