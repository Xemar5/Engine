#pragma once
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <functional>

class Texture;
class Movement;
class Collider;
class State;

namespace ent
{
	class EntityObject;
	template <typename T = EntityObject>
	class Entity;

#define Delegate(T, FOO) [](::ent::Entity<T> e) { FOO }

	//*** Contains all entities
	extern std::vector<Entity<>> All;
	//*** Contains all entities in an ordered manner
	//*** The map key is the layer the entity is stored in
	//*** The vector of entities is ordered by the Y value
	extern std::map<std::shared_ptr<State>, std::map<int, std::vector<Entity<>>>> Ordered;
	//*** Contains all entities with unique names
	extern std::map<std::string, Entity<>> Registered;

	template <typename T = EntityObject> Entity<T> Add() { return Add<T>("", nullptr, nullptr); }
	template <typename T = EntityObject> Entity<T> Add(std::string name) { return Add<T>(name, nullptr, nullptr); }
	template <typename T = EntityObject> Entity<T> Add(std::shared_ptr<State> state) { return Add<T>("", state, nullptr); }
	template <typename T = EntityObject> Entity<T> Add(std::function<void(Entity<T>)> construcingFoo) { return Add<T>("", nullptr, construcingFoo); }
	template <typename T = EntityObject> Entity<T> Add(std::string name, std::shared_ptr<State> state) { return Add<T>(name, state, nullptr); }
	template <typename T = EntityObject> Entity<T> Add(std::string name, std::function<void(Entity<T>)> construcingFoo) { return Add<T>(name, nullptr, construcingFoo); }
	template <typename T = EntityObject> Entity<T> Add(std::shared_ptr<State> state, std::function<void(Entity<T>)> construcingFoo) { return Add<T>("", state, construcingFoo); }
	template <typename T = EntityObject> Entity<T> Add(std::string name, std::shared_ptr<State> state, std::function<void(Entity<T>)> construcingFoo);








	class EntityObject : protected std::enable_shared_from_this<EntityObject>
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
		//*** Controlls the movement of the entity
		//*** in nullptr, entity is considered static,
		//***    which means it can't be moved
		std::shared_ptr<Movement> movement = nullptr;
		//*** Set of colliders of this entity
		std::vector<std::shared_ptr<Collider>> colliders;
		//*** Returns the hitbox of this entity
		//*** Depends on texture
		std::pair<double, double> hitbox();

		double X = 0;
		double Y = 0;
		double Z = 0;

		//*** the layer this entity is put on
		//*** read-only (use State::Change_Entity_Layer)
		unsigned layer = 0;

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
		//*** Returns the pointer to holded entity
		T* get() const;
		//*** Returns a shared_ptr to holded entity
		std::shared_ptr<T> get_shared() const;
		//*** Returns the use count of stored shared_ptr
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





	template<typename T>
	Entity<T> Add(std::string name, std::shared_ptr<State> state, std::function<void(Entity<T>)> construcingFoo)
	{
		Entity<T> e = std::make_shared<T>();
		All.push_back(e);
		if (construcingFoo) construcingFoo(e);
		if (!state) state = State::CurrentState();

		Ordered[state][e->layer].push_back(e);
		if (name.size())
		{
			if (Registered.at(name)) Output_Handler::Output << "MSG ent::Entity<T> Add : Entity with given name already registered; overriting\n";
			Registered[name] = e;
		}
		return e;
	}

}


