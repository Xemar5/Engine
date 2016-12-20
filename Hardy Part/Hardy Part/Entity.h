#pragma once
//#include <iostream>
//#include <string>
#include <vector>
#include <memory>
//#include <SDL.h>
//#include "Sprite.h"
//#include "Network.h"


class Texture;
class Movement;
class Collider;


class EntityObject : protected std::enable_shared_from_this<EntityObject>
{
public:
	virtual void Create() {};
	virtual void Update() {};
	virtual void Events() {};


	double scale = 1;
	std::shared_ptr<Texture> texture = nullptr;
	std::shared_ptr<Movement> movement = nullptr;
	std::vector<std::shared_ptr<Collider>> colliders;
	std::pair<double, double> hitbox();

	double X = 0;
	double Y = 0;
	double Z = 0;

	unsigned layer = 0;
	//EntityType type;
	//NetworkID networkID;

	virtual ~EntityObject() = default;
	EntityObject() = default;
	EntityObject(const EntityObject&) = delete;
	EntityObject& operator=(const EntityObject&) = delete;

	template <typename T>
	friend class Entity;
	friend class State;
};







template <typename T = EntityObject>
class Entity final
{
public:
	T* get() const;
	std::shared_ptr<T> get_shared() const;
	size_t count() const;

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
	std::shared_ptr<N> e = std::dynamic_pointer_cast<N, T>(_entity);
	if (e)
	{
		Entity<N> e_n;
		e_n._entity = e;
		return e_n;
	}
	else return nullptr;
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
	_entity = std::make_shared<T>();
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
template<typename T> template<typename N> Entity<T>::Entity(std::shared_ptr<N> ent)
{
	_entity = std::dynamic_pointer_cast<T>(ent);
}




