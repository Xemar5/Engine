#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

template <typename T>
class Pointer;

class Collider
{
public:
	//*** Creates and adds a new collider to the given entity
	//*** Stores the location of the collider in _Static_Colliders or _Colliders vector
	static std::shared_ptr<Collider> Add(std::shared_ptr<Entity> ent);
	
	//*** Checks for all encountered collisions and resloves them
	//*** Fired from main timeline - use only when necessary
	static void Update();

	//*** Returns true if given colliders overlap
	static bool Overlap(std::shared_ptr<Collider> c1, std::shared_ptr<Collider> c2);

	double W = 30;
	double H = 30;

	~Collider();
protected:
	//*** Contains all colliders of Entities with Movement class specified
	static std::vector<std::shared_ptr<Collider>> _Colliders;
	//*** Contains all colliders of non-moving Entities
	static std::vector<std::shared_ptr<Collider>> _StaticColliders;

	//*** The entity this collider is attached to
	std::shared_ptr<Entity> _Parent = nullptr;

};