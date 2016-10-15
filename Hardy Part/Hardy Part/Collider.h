#pragma once
#include <vector>
#include <memory>
class Entity;

class Collider
{
public:
	//*** Creates and adds a new collider to the given entity
	//*** Stores the location of the collider in _Static_Colliders or _Colliders vector
	static Collider* Add(Entity* ent);
	
	//*** Checks for all encountered collisions and resloves them
	//*** Fired from main timeline - use only when necessary
	static void Update();

	//*** Returns true if given colliders overlap
	static bool Overlap(Collider* c1, Collider* c2);

	double W = 30;
	double H = 30;

	~Collider();
protected:
	//*** Contains all colliders of Entities with Movement class specified
	static std::vector<std::shared_ptr<Collider>> _Colliders;
	//*** Contains all colliders of non-moving Entities
	static std::vector<std::shared_ptr<Collider>> _StaticColliders;

	//*** The entity this collider is attached to
	Entity* _Parent = nullptr;

};