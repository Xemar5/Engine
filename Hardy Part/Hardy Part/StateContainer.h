#pragma once
#include "Entity.h"
#include "Container.h"

class Layer;
class Canvas;

class StateContainer : public Container, public EntityObject
{
public:
	StateContainer() = default;
	virtual ~StateContainer() = default;

	static Entity<Layer> layer(unsigned i, Entity<State> state = nullptr);
	static Entity<> At(unsigned layer, unsigned ent, Entity<State> state = nullptr);
private:
	std::map<unsigned, Entity<Layer>> _layerMap;
};