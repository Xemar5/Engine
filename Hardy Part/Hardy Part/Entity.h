#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SDL.h>
#include "Sprite.h"
#include "Network.h"

class Sprite;
class Action;
class Hitbox;
class Stats;
class Texture;
class Movement;
class Collider;


enum EntityType
{
	ET_Default,
	ET_Generic,
	ET_Character
};

//All your Entities should NOT override this class, deriver Entity class instead.

class Entity
{
public:
	//***  Virtual Create function, should be overriden by derivering entites
	virtual void Create() {};
	//***  Virtual Update function, should be overriden by derivering entites
	virtual void Update() {};
	//***  Virtual Events function, should be overriden by derivering entites
	virtual void Events() {};

	//*** Returns this as an entity derative if possible
	template <typename T> T* As() { return dynamic_cast<T*>(this); };
	//*** Returns the Hitbox pointer if it exists
	std::pair<double, double> Get_Hitbox() const;

	//*** Returns the Texture pointer if it exists
	template<typename T = Texture>
	T* Display() const;
	//*** Returns the scale of this entity
	virtual double Get_Scale() const;

	//*** Returns the Texture pointer if it exists
	Texture* Get_Texture() const;
	//*** Returns the Movement pointer if it exists
	Movement* Get_Movement() const;
	//*** Returns the Collider pointer if it exists
	Collider* Get_Collider(unsigned index) const;

	//*** X coordinate of this entity position
	double X = 0;
	//*** Y coordinate of this entity position
	double Y = 0;
	//*** Z coordinate of this entity position
	//*** determines which entity should be drawn at which point
	double Z = 0;

	//*** Returns the layer this character is set on
	unsigned Get_Layer() const { return __Layer; };
	//*** The type of this entity
	//*** Default if not specified
	EntityType Get_Type() const { return __Type; }

	//*** The ID of this entity in the network
	NetworkID networkID;


	//*** Registers an entity with given name
	//*** Can be retrived with Get("name")
	//*** Can't register if name already taken
	//*** Registering the same entity again with different name will change it
	static bool Register(Entity* ent, std::string name, bool forceRegister = false);

	//*** Returns the map of all registered entities
	static std::map<std::string, Entity*> Registered() { return __Registered; };
	//*** Returns an entity by its name if registered
	static Entity* Get(std::string name);
	//*** Returns all existing entities
	static std::vector<std::shared_ptr<Entity>> All();



	virtual ~Entity() 
	{
		for (auto e = __Registered.begin(); e != __Registered.end(); ++e)
			if (e->second == this) { __Registered.erase(e->first); break; }

		auto ttr = __Texture.get();
		__Texture = nullptr;
 		if(ttr) ttr->Destroy();

		__Movement = nullptr;

		for (auto& c : __Colliders)
			c = nullptr;
		__Colliders.clear();
	}

protected:
	//*** A class containing all compounds needed for a sprite to be rendered
	//*** If nullptr, entity wont be displayed, but still can has usage (Actions)
	std::shared_ptr<Texture> __Texture = nullptr;

	//*** A class resolving movement input
	//*** If nullptr, entity can't move
	std::shared_ptr<Movement> __Movement = nullptr;

	//*** A vector of class responsible for handling collisions
	//*** If size of 0, entity ignore all collisions
	//*** If this Entity has no Movement specified, this entity doesn't move after collision
	//***	and ignore all collisions from other non-moving entities
	std::vector<std::shared_ptr<Collider>> __Colliders;

	//*** The layer of the state this entity is set on
	unsigned __Layer = -1;
	//*** The type of this entity
	//*** ET_Default if not specified
	EntityType __Type = ET_Default;

	//*** A map containing all registered Entities
	static std::map<std::string, Entity*> __Registered;

	friend class Sprite;
	friend class Texture;
	friend class Generic;
	friend class Hitbox;
	friend class Movement;
	friend class State;
	friend class Collider;
};


