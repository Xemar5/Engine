#pragma once
#include "Entity.h"
#include "Container.h"

class Layer;
class Canvas;
class State;

class LayerContainer
{
public:
	LayerContainer();
	virtual ~LayerContainer() = default;

	//*** Adds child to the layer in this state
	static void AddChild(unsigned layer, std::shared_ptr<Object> obj);
	//*** Adds child to the layer in specific state
	static void AddChild(std::shared_ptr<State> state, unsigned layer, std::shared_ptr<Object> obj);

	template<typename T = Entity, typename... Rest>
	std::shared_ptr<T> GetChild(unsigned layerID, unsigned childID, Rest... nextChildrenID);
	template<typename T = Entity>
	std::shared_ptr<T> GetChild(unsigned layerID, unsigned childID);
	//*** Returns a layer with given id if it exists
	//*** Otherwise creates new layer and returns it
	std::shared_ptr<Layer> GetLayer(unsigned childID);
protected:
	//*** Returns a layer with given id
	//*** Otherwise creates a new layer and returns it
	std::shared_ptr<Layer> _GetOrCreateLayer(unsigned id);
	//*** Stores all layers
	//*** Bodies cannot be directly added to the State, they are added to layers
	std::vector<std::pair<unsigned, std::shared_ptr<Container>>> _layer_vector;
	//*** Parent of all Layers this state has
	std::shared_ptr<Container> _parent_container;

	friend class Layer;
	friend class System;
};

template<typename T, typename ...Rest>
inline std::shared_ptr<T> LayerContainer::GetChild(unsigned layerID, unsigned childID, Rest ...nextChildrenID)
{
	return _GetOrCreateLayer(layerID)->Get(childID, nextChildrenID...);
}

template<typename T>
inline std::shared_ptr<T> LayerContainer::GetChild(unsigned layerID, unsigned childID)
{
	return _GetOrCreateLayer(layerID)->Get(childID);
}

