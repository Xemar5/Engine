#pragma once

#include "Entity.h"

class Layer : public Container
{
public:
	Layer() { parent = State::CurrentState(); }
};