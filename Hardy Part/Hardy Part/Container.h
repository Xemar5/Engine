#pragma once
#include <vector>
#include "Entity.h"


class Container : public virtual Object
{
public:
	Container() = default;
	virtual ~Container() = 0;
	void Destroy() override;


	//*** The container of all entities this container holds
	std::vector<std::shared_ptr<Object>> children;
	//*** The method function Reorder uses to place children in order
	std::function<bool(std::shared_ptr<Object>, std::shared_ptr<Object>)> reorderMethod = [](std::shared_ptr<Object> e1, std::shared_ptr<Object> e2) { return e1->Y > e2->Y; };


	template<typename T = Entity, typename... Rest>
	std::shared_ptr<T> Get(unsigned childID, Rest... nextChildrenID);
	template<typename T = Entity>
	std::shared_ptr<T> Get(unsigned childID);

	//*** Adds given entity to this container's children vector
	virtual void AddChild(std::shared_ptr<Object> ent);
	//*** Removes given object from this container's child vector
	virtual void RemoveChild(std::shared_ptr<Object> obj);

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
	std::shared_ptr<Object> e = children.size() > childID ? children[childID] : nullptr;//Output_Handler::OutputReturn("MSG Container::Get<T> : index out of range\n", nullptr);
	if (auto c = std::dynamic_pointer_cast<Container>(e)) 
		return c->Get<T>(std::forward<Rest>(nextChildrenID)...);
	//Output_Handler::Output << "MSG Container::Get<T> : given entity is not a container or too many parameters\n";
	if (auto t = std::dynamic_pointer_cast<T>(e)) return t;
	//Output_Handler::Output << "MSG Container::Get<T> : given entity is not castable to given type\n";
	return nullptr;
}

template<typename T>
inline std::shared_ptr<T> Container::Get(unsigned childID)
{
	std::shared_ptr<Object> e = children.size() > childID ? children[childID] : nullptr;//Output_Handler::OutputReturn("MSG Container::Get : index out of range\n", nullptr);
	if (e)
	{
		if (std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(e)) return t;
		Output_Handler::Output << "MSG Container::Get : given entity is not castable to given type\n";
	}
	return nullptr;
}
