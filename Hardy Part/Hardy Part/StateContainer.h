#pragma once
#include "Entity.h"
#include "Container.h"

class Layer;
class Canvas;
class State;

class StateContainer : public Container
{
public:
	StateContainer() = default;
	virtual ~StateContainer() = default;

	static std::shared_ptr<Layer> layer(unsigned i, std::shared_ptr<State> state = nullptr);
private:
	std::map<unsigned, std::shared_ptr<Layer>> _layerMap;
};