#pragma once

#include "Entity.h"

class Layer : public EntityObject, public Container
{
public:
	Layer() { EntityObject::parent = State::CurrentState(); }
	Layer(Entity<Container> parent) { EntityObject::parent = parent; }
};