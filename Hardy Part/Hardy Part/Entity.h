#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <functional>
#include <iostream>
#include "Body.h"

class Texture;
class Movement;
class Collider;

class Entity : public virtual Body
{
public:
	virtual void Create() {};
	virtual void Update() {};
	virtual void Events() {};

	//*** The texture of this entity
	//*** Takes care of visual part of the entity
	std::shared_ptr<Texture> texture = nullptr;
	//*** Controlls the movement of the entity
	//*** in nullptr, entity is considered static,
	//***    which means it can't be moved
	std::shared_ptr<Movement> movement = nullptr;
	//*** Change of colliders of this entity
	std::vector<std::shared_ptr<Collider>> colliders;
	//*** Returns the hitbox of this entity
	//*** Depends on texture
	std::pair<double, double> hitbox();



	virtual ~Entity() = default;
	Entity() = default;
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	operator std::shared_ptr<Entity>();
	operator std::shared_ptr<Body>();
};



