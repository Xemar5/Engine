#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <functional>
#include <iostream>

#define Delegate [](auto e)

class Texture;
class Movement;
class Collider;
class Container;
class State;


class EntityObject;
template <typename T = EntityObject>
class Entity;



class EntityObject : public std::enable_shared_from_this<EntityObject>
{
public:
	virtual void Create() {};
	virtual void Update() {};
	virtual void Events() {};

	//*** The scale of this EntityObject
	//*** The bigger the scale the bigger the entity
	//double scale = 1;
	//*** The texture of this entity
	//*** Takes care of visual part of the entity
	std::shared_ptr<Texture> texture = nullptr;
	//*** The scale of this entity
	double scale = 1;
	//*** The scale of this entity
	double rotation = 0;
	//*** Controlls the movement of the entity
	//*** in nullptr, entity is considered static,
	//***    which means it can't be moved
	std::shared_ptr<Movement> movement = nullptr;
	//*** Change of colliders of this entity
	std::vector<std::shared_ptr<Collider>> colliders;
	//*** Returns the hitbox of this entity
	//*** Depends on texture
	std::pair<double, double> hitbox();
	//*** The Container object that this entity belongs to
	std::shared_ptr<Container> parent = nullptr;
	//*** Returns the scale of this entity and all it's parents
	double RealScale();
	//*** Returns the real position of this entity
	std::vector<double> RealPos();

	double X = 0;
	double Y = 0;
	double Z = 0;

	////*** the layer this entity is put on
	////*** read-only (use State::Change_Entity_Layer)
	//unsigned layer = 0;

	virtual ~EntityObject() = default;
	EntityObject() = default;
	EntityObject(const EntityObject&) = delete;
	EntityObject& operator=(const EntityObject&) = delete;



	template <typename T>
	friend class Entity;
	friend class State;
	friend class StateContainer;
};




template <typename T>
class Entity final
{
public:
	//*** Returns the pointer to holded entity
	T* get() const;
	//*** Returns a shared_ptr to holded entity
	std::shared_ptr<T> get_shared() const;
	//*** Returns the use count of stored shared_ptr
	size_t count() const;


	template <typename... Args>
	static Entity<T> Add(Args... args);
	//static Entity<T> Add() { return Add("", nullptr, nullptr); }
	//static Entity<T> Add(std::string name) { return Add(name, nullptr, nullptr); }
	//static Entity<T> Add(std::shared_ptr<Container> parent) { return Add("", parent, nullptr); }
	//static Entity<T> Add(std::function<void(Entity<T>)> construcingFoo) { return Add("", nullptr, construcingFoo); }
	//static Entity<T> Add(std::string name, std::shared_ptr<Container> parent) { return Add(name, parent, nullptr); }
	//static Entity<T> Add(std::string name, std::function<void(Entity<T>)> construcingFoo) { return Add(name, nullptr, construcingFoo); }
	//static Entity<T> Add(std::shared_ptr<Container> parent, std::function<void(Entity<T>)> construcingFoo) { return Add("", parent, construcingFoo); }
	//static Entity<T> Add(std::string name, std::shared_ptr<Container> parent, std::function<void(Entity<T>)> construcingFoo);




	template <typename N>
	Entity(std::shared_ptr<N> ent);
	Entity();
	Entity(const Entity& ent);
	Entity(EntityObject* ent);
	Entity(std::nullptr_t null);
	~Entity() = default;

	template<typename N> operator Entity<N>();
	template<typename N> operator std::shared_ptr<N>();
	operator std::shared_ptr<T>();
	operator bool();

	std::shared_ptr<T>& operator->();
	bool operator==(const Entity& ent);

	Entity& operator=(const Entity& ent);
	Entity& operator=(std::nullptr_t null);
	Entity& operator=(EntityObject* ent);
	template<typename N> Entity& operator=(std::shared_ptr<N> ent);

private:
	std::shared_ptr<T> _entity = nullptr;

	template<typename N>
	friend class Entity;
};




template<typename T>					  Entity<T>::operator bool()
{
	return _entity ? true : false;
}
template<typename T>					  Entity<T>::operator std::shared_ptr<T>()
{
	return _entity;
}
template<typename T> template<typename N> Entity<T>::operator std::shared_ptr<N>()
{
	return std::dynamic_pointer_cast<N>(_entity);
}
template<typename T> template<typename N> Entity<T>::operator Entity<N>()
{
	return Entity<N>(std::dynamic_pointer_cast<N>(_entity));
}

template<typename T> template<typename N> Entity<T> & Entity<T>::operator=(std::shared_ptr<N> ent)
{
	_entity = std::dynamic_pointer_cast<T>(ent);
	return *this;
}
template<typename T>					  Entity<T> & Entity<T>::operator=(std::nullptr_t null)
{
	//std::cout << "nullptr asigned Entity\n";
	_entity = null;
	return *this;
}
template<typename T>					  Entity<T> & Entity<T>::operator=(EntityObject * ent)
{
	_entity = ent->shared_from_this();
	return *this;
}
template<typename T>					  Entity<T> & Entity<T>::operator=(const Entity<T> & ent)
{
	//std::cout << "asigned Entity\n";
	_entity = ent._entity;
	return *this;
}

template<typename T> std::shared_ptr<T> & Entity<T>::operator->()
{
	return _entity;
}
template<typename T> bool Entity<T>::operator==(const Entity<T> & ent)
{
	return _entity == ent._entity;
}

template<typename T>				T * Entity<T>::get() const
{
	return _entity.get();
}
template<typename T> std::shared_ptr<T> Entity<T>::get_shared() const
{
	return _entity;
}
template<typename T>			 size_t Entity<T>::count() const
{
	return _entity ? _entity.use_count() : 0;
}

template<typename T>					  Entity<T>::Entity()
{
	//std::cout << "default constructed Entity\n";
	_entity = nullptr;
}
template<typename T>					  Entity<T>::Entity(const Entity<T> & ent)
{
	//std::cout << "copy constructed Entity\n";
	_entity = ent._entity;
}
template<typename T>					  Entity<T>::Entity(EntityObject * ent)
{
	_entity = ent->shared_from_this();
}
template<typename T>					  Entity<T>::Entity(std::nullptr_t null)
{
	//std::cout << "nullptr constructed Entity\n";
	_entity = null;
}

#include "Container.h"
class StateContainer;
class State;

template<typename T>
template<typename ...Args> inline Entity<T> Entity<T>::Add(Args ...args)
{
	Entity<T> e = std::make_shared<T>(args...);
	e->Create();
	if (!e->parent) e->parent = State::CurrentState()->layer(0);
	e->parent->children.push_back(e);
	return e;
}
template<typename T> template<typename N> Entity<T>::Entity(std::shared_ptr<N> ent)
{
	_entity = std::dynamic_pointer_cast<T>(ent);
}
//
//template<typename T>
//Entity<T> Entity<T>::Add(std::string name, std::shared_ptr<Container> parent, std::function<void(Entity<T>)> construcingFoo)
//{
//	Entity<T> e = std::make_shared<T>();
//
//	//auto l = std::dynamic_pointer_cast<StateContainer>(e._entity);
//	//if (l)
//	//{
//	//	State::CurrentState()->children.push_back(e);
//	//	e->parent = State::CurrentState();
//	//}
//	//else if(std::dynamic_pointer_cast<State>(parent))
//	//	Output_Handler::OutputReturn("MSG Entity<T>::Add : only layers can be added to States\n", nullptr);
//	//else
//	{
//		if (construcingFoo) construcingFoo(e);
//		if (!parent) parent = State::CurrentState()->layer(0);
//		parent->children.push_back(e);
//		e->parent = parent;
//
//		//if (name.size())
//		//{
//		//	if (Registered.at(name)) Output_Handler::Output << "MSG Entity<T> Add : Entity with given name already registered; overriting\n";
//		//	Registered[name] = e;
//		//}
//	}
//	return e;
//}
//

