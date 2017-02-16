#pragma once

#include "Entity.h"

class Layer : public Container
{
public:
	Layer(bool is_state_parent)
	{
		if(!is_state_parent)
			parent = State::CurrentState()->_parent_container;
	}
};