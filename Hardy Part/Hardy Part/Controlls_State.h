#pragma once

#include "State.h"

class Controlls_State : public State
{
public:
	void Create() override;
	void Update() override;
	void Events() override;
};

