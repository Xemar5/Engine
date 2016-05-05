#pragma once

#include "State.h"

class GameMenu_State : public State
{
private:
	unsigned __first_unused_index = 0;

public:
	void Create() override;
	void Update() override;
	void Events() override;

};

