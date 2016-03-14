#pragma once

#include "Entity.h"
#include "Gamepad_Handler.h"

class Man : public Entity
{
public:
	void Create() override;
	void Update() override;
	void Events() override;
};
