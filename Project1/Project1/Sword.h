#pragma once
#include "Entity.h"

class Sword : public Entity
{
public:
	Entity* Wealder = nullptr;
	double Old_Angle = 0.0;
	void Create() override;
	void Update() override;
	void Events() override;
};
