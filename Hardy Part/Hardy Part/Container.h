#pragma once
#include <vector>
#include "Entity.h"

class Container
{
public:
	Container() = default;
	virtual ~Container() = 0;

	//*** The container of all entities this container holds
	std::vector<Entity<>> children;
	//*** The method function Reorder uses to place children in order
	std::function<bool(Entity<>, Entity<>)> reorderMethod = [](Entity<> e1, Entity<> e2) { return e1->Y > e2->Y; };
	//*** Reorders children using supplied function
	void Reorder();
	//*** Calculates the x pos form given coordinates
	virtual double Child_X(double x) { return x; };
	//*** Calculates the y pos form given coordinates
	virtual double Child_Y(double y) { return y; };
};
