#include "StateContainer.h"
#include "State.h"
#include "Layer.h"
#include "Canvas.h"

Entity<Layer> StateContainer::layer(unsigned i, Entity<State> state)
{
	if (!state) state = State::CurrentState();
	auto it = state->_layerMap.find(i);
	if (it == state->_layerMap.end())
	{
		state->children.push_back(Entity<Layer>::Add(state->shared_from_this()));
		state->_layerMap[i] = state->children.back();
	}
	return state->_layerMap[i];
}


Entity<> StateContainer::At(unsigned layer, unsigned ent, Entity<State> state)
{
	if (!state) state = State::CurrentState();
	auto l = State::layer(layer, state);
	return l->children.size() > ent ? l->children[ent] : nullptr;
}
