#include "LayerContainer.h"
#include "State.h"
#include "Layer.h"
#include "Canvas.h"



LayerContainer::LayerContainer()
{
	_parent_container = std::make_shared<Layer>(true);
	_parent_container->reorderMethod = [](std::shared_ptr<Object> b1, std::shared_ptr<Object> b2) { return false; };
}

void LayerContainer::AddChild(unsigned layer, std::shared_ptr<Object> obj)
{
	if (obj->parent)
	{
		for (auto it = obj->parent->children.begin(); it != obj->parent->children.end(); ++it)
			if (*it == obj)
			{
				obj->parent->children.erase(it);
				obj->parent = nullptr;
				break;
			}
	}

	std::shared_ptr<Layer> l = _GetOrCreateLayer(layer);
	l->AddChild(obj);
}

void LayerContainer::AddChild(std::shared_ptr<State> state, unsigned layer, std::shared_ptr<Object> obj)
{
	State::CurrentState()->AddChild(layer, obj);
}

std::shared_ptr<Layer> LayerContainer::_GetOrCreateLayer(unsigned id)
{
	auto it = _layer_vector.begin();
	while (it != _layer_vector.end())
	{
		if (it->first == id) break;
		else if (it->first > id)
		{
			it = _layer_vector.insert(it, { id, std::make_shared<Layer>(false) });
			break;
		}
		else ++it;
	}
	if (it == _layer_vector.end())
	{
		_layer_vector.push_back({ id, std::make_shared<Layer>(false) });
		it = _layer_vector.begin() + (_layer_vector.size() - 1);
	}
	return std::dynamic_pointer_cast<Layer>(it->second);
}

std::shared_ptr<Layer> LayerContainer::GetLayer(unsigned index)
{
	return _GetOrCreateLayer(index);
}
