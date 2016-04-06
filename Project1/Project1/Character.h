#pragma once


enum class Character_Enum
{
	Nerk,
	Mosh,
	Dreg,
	Tar,
	Raiden
};

#include "Entity.h"

template <Character_Enum type>
class Character : public Entity
{
public:
	Character_Enum Type = type;
	void Create() override;
	void Update() override;
	void Events() override;
};
