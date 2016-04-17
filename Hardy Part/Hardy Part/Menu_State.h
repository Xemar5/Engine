#pragma once

#include "State.h"

class Menu_Menu : public State
{
public:
	void Create() override;
	void Update() override;
	void Events() override;
};

