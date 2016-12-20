#pragma once

#include "State.h"

class GameMenu_State : public State
{
public:
	void Create() override;
	void Update() override;
	void Events() override;
};

