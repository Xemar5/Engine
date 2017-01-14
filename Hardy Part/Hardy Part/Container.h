#pragma once
#include <vector>
#include "Entity.h"


class Container : public virtual Body
{
public:
	Container() = default;
	virtual ~Container() = 0;


	//*** The container of all entities this container holds
	std::vector<std::shared_ptr<Body>> children;
	//*** The method function Reorder uses to place children in order
	std::function<bool(std::shared_ptr<Body>, std::shared_ptr<Body>)> reorderMethod = [](std::shared_ptr<Body> e1, std::shared_ptr<Body> e2) { return e1->Y > e2->Y; };


	template<typename T = Entity, typename... Rest>
	std::shared_ptr<T> Get(unsigned childID, Rest... nextChildrenID);
	template<typename T = Entity>
	std::shared_ptr<T> Get(unsigned childID);

	//*** Adds given entity to this container's children vector
	void Add(std::shared_ptr<Body> ent);


	//*** Reorders children using supplied function
	void Reorder();
	//*** Calculates the x pos form given coordinates
	virtual double Child_X(double x) { return x; };
	//*** Calculates the y pos form given coordinates
	virtual double Child_Y(double y) { return y; };
};


#include "Output_Handler.h"


template<typename T, typename ...Rest>
inline std::shared_ptr<T> Container::Get(unsigned childID, Rest ...nextChildrenID)
{
	std::shared_ptr<Body> e = children.size() > childID ? children[childID] : Output_Handler::OutputReturn("MSG Container::Get<T> : index out of range\n", nullptr);
	if (auto c = std::dynamic_pointer_cast<Container>(e)) 
		return c->Get<T>(std::forward<Rest>(nextChildrenID)...);
	Output_Handler::Output << "MSG Container::Get<T> : given entity is not a container or too many parameters\n";
	if (auto t = std::dynamic_pointer_cast<T>(e)) return t;
	Output_Handler::Output << "MSG Container::Get<T> : given entity is not castable to given type\n";
	return nullptr;
}

template<typename T>
inline std::shared_ptr<T> Container::Get(unsigned childID)
{
	std::shared_ptr<Body> e = children.size() > childID ? children[childID] : Output_Handler::OutputReturn("MSG Container::Get : index out of range\n", nullptr);
	if(e) if(std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(e)) return t;
	Output_Handler::Output << "MSG Container::Get : given entity is not castable to given type\n";
	return nullptr;
}
