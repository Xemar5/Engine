#pragma once

#include "State.h"
#include "Man.h"

class Main_Menu : public State
{
public:
	void Create() override;
	void Update() override;
	void Events() override;
};

