#pragma once

#include "State.h"

class State1 : public State
{
public:
	void Create() override;
	void Update() override;
	void Events() override;
};

