#include "StateContainer.h"
#include "State.h"
#include "Layer.h"
#include "Canvas.h"

std::shared_ptr<Layer> StateContainer::layer(unsigned i, std::shared_ptr<State> state)
{
	if (!state) state = State::CurrentState();
	auto it = state->_layerMap.find(i);
	if (it == state->_layerMap.end())
	{
		state->Container::Add(Body::Make<Layer>());
		state->_layerMap[i] = std::dynamic_pointer_cast<Layer>(state->children.back());
		
	}
	return state->_layerMap[i];
}


//template <typename T>
//std::shared_ptr<T> StateContainer::At(unsigned layer, unsigned ent, std::shared_ptr<State> state)
//{
//	if (!state) state = State::CurrentState();
//	auto l = State::layer(layer, state);
//	return l->children.size() > ent ? l->children[ent] : nullptr;
//}
