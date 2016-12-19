#include "Entity.h"
#include "Texture.h"
#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Screen.h"
#include "State.h"
#include "Output_Handler.h"
#include "Collider.h"

std::map<std::string, Entity*> Entity::__Registered;

std::pair<double, double> Entity::Get_Hitbox() const
{
	if (!this) { Output_Handler::Error << "ERR Entity::Get_Hitbox : No this Entity\n"; return std::pair<double, double>(); }
	if (!this->Display()) { Output_Handler::Error << "ERR Entity::Get_Hitbox : This entity has no sprite supplied\n"; return std::pair<double, double>(); }
	return std::make_pair(
		(double)this->Display()->Frame_Rect().w * this->Display()->Scale,
		(double)this->Display()->Frame_Rect().h * this->Display()->Scale
		);
}

template<typename T>
T* Entity::Display() const
{
	if (!this) { Output_Handler::Error << "ERR Entity::Display : No this Entity\n"; return nullptr; }
	return dynamic_cast<T*>(__Texture.get());
}

double Entity::Get_Scale() const
{
	if (!this) { Output_Handler::Error << "ERR Entity::Display : No this Entity\n"; return 1.0; }
	if (!Display()) { Output_Handler::Error << "ERR Entity::Display : This entity has no sprite supplied\n"; return 1.0; }
	return Display()->Scale;
}

Texture * Entity::Get_Texture() const
{
	if (!this) { Output_Handler::Error << "ERR Entity::Get_Texture : No this Entity\n"; return nullptr; }
	return __Texture.get();
}
Movement * Entity::Get_Movement() const
{
	if (!this) { Output_Handler::Error << "ERR Entity::Get_Movement : No this Entity\n"; return nullptr; }
	return __Movement.get();
}
Collider * Entity::Get_Collider(unsigned index) const
{
	if (!this) { Output_Handler::Error << "ERR Entity::Get_Collider : No this Entity\n"; return nullptr; }
	if (index >= __Colliders.size()) { Output_Handler::Error << "ERR Entity::Get_Collider : Given index is greater than the number of Colliders this Entity has\n"; return nullptr; }
	return __Colliders[index].get();
}



bool Entity::Register(Entity * ent, std::string name, bool forceRegister)
{
	auto name_exists = __Registered.find(name);
	if (name_exists != __Registered.end())
	{
		if (!forceRegister) Output_Handler::Output << "MSG Entity::Register : Name already registered; re-registering\n";
		else { Output_Handler::Error << "ERR Entity::Register : Name already registered\n"; return false; }
	}
	auto ent_registered = __Registered.end();
	for (auto key = __Registered.begin(); key != __Registered.end(); ++key)
	{
		if (key->second == ent) { ent_registered = key; break; }
	}
	if (ent_registered != __Registered.end())
		__Registered.erase(ent_registered->first);
	__Registered[name] = ent;
	return true;
}

Entity * Entity::Get(std::string name)
{
	auto ent = __Registered.find(name);
	if (ent == __Registered.end()) Output_Handler::Error << "ERR Entity::Get : No entity registered with given name; returning nullptr\n";
	return ent == __Registered.end() ? nullptr : ent->second;
}

std::vector<std::shared_ptr<Entity>> Entity::All()
{
	return State::Built.size() ? State::Built.back()->Get_Entities() : std::vector<std::shared_ptr<Entity>>();
}



