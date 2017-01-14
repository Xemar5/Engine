#include "Entity.h"
#include "Texture.h"
#include "Output_Handler.h"

//#include "Sprite.h"
//#include "Animation.h"
//#include "Movement.h"
//#include "Screen.h"
//#include "State.h"
//#include "Collider.h"
//
//std::map<std::string, Pointer*> Pointer::__Registered;
//
//std::pair<double, double> Pointer::Get_Hitbox() const
//{
//	if (!this) { Output_Handler::Error << "ERR Pointer::Get_Hitbox : No this Pointer\n"; return std::pair<double, double>(); }
//	if (!this->Display()) { Output_Handler::Error << "ERR Pointer::Get_Hitbox : This entity has no sprite supplied\n"; return std::pair<double, double>(); }
//	return std::make_pair(
//		(double)this->Display()->Frame_Rect().w * this->Display()->Scale,
//		(double)this->Display()->Frame_Rect().h * this->Display()->Scale
//		);
//}
//
//template<typename T>
//T* Pointer::Display() const
//{
//	if (!this) { Output_Handler::Error << "ERR Pointer::Display : No this Pointer\n"; return nullptr; }
//	return dynamic_cast<T*>(__Texture.get());
//}
//
//double Pointer::Get_Scale() const
//{
//	if (!this) { Output_Handler::Error << "ERR Pointer::Display : No this Pointer\n"; return 1.0; }
//	if (!Display()) { Output_Handler::Error << "ERR Pointer::Display : This entity has no sprite supplied\n"; return 1.0; }
//	return Display()->Scale;
//}
//
//Texture * Pointer::Get_Texture() const
//{
//	if (!this) { Output_Handler::Error << "ERR Pointer::Get_Texture : No this Pointer\n"; return nullptr; }
//	return __Texture.get();
//}
//Movement * Pointer::Get_Movement() const
//{
//	if (!this) { Output_Handler::Error << "ERR Pointer::Get_Movement : No this Pointer\n"; return nullptr; }
//	return __Movement.get();
//}
//Collider * Pointer::Get_Collider(unsigned index) const
//{
//	if (!this) { Output_Handler::Error << "ERR Pointer::Get_Collider : No this Pointer\n"; return nullptr; }
//	if (index >= __Colliders.size()) { Output_Handler::Error << "ERR Pointer::Get_Collider : Given index is greater than the number of Colliders this Pointer has\n"; return nullptr; }
//	return __Colliders[index].get();
//}
//
//
//
//bool Pointer::Register(Pointer * ent, std::string name, bool forceRegister)
//{
//	auto name_exists = __Registered.find(name);
//	if (name_exists != __Registered.end())
//	{
//		if (!forceRegister) Output_Handler::Output << "MSG Pointer::Register : Name already registered; re-registering\n";
//		else { Output_Handler::Error << "ERR Pointer::Register : Name already registered\n"; return false; }
//	}
//	auto ent_registered = __Registered.end();
//	for (auto key = __Registered.begin(); key != __Registered.end(); ++key)
//	{
//		if (key->second == ent) { ent_registered = key; break; }
//	}
//	if (ent_registered != __Registered.end())
//		__Registered.erase(ent_registered->first);
//	__Registered[name] = ent;
//	return true;
//}
//
//Pointer * Pointer::Get(std::string name)
//{
//	auto ent = __Registered.find(name);
//	if (ent == __Registered.end()) Output_Handler::Error << "ERR Pointer::Get : No entity registered with given name; returning nullptr\n";
//	return ent == __Registered.end() ? nullptr : ent->second;
//}
//
//std::vector<std::shared_ptr<Pointer>> Pointer::All()
//{
//	return State::Built.size() ? State::Built.back()->Get_Entities() : std::vector<std::shared_ptr<Pointer>>();
//}
//
//
//



std::pair<double, double> Entity::hitbox()
{
	if (!this) { Output_Handler::Error << "ERR Entity::Get_Hitbox : No this Entity\n"; return std::pair<double, double>(); }
	if (!this->texture) { Output_Handler::Error << "ERR Entity::Get_Hitbox : This entity has no sprite supplied\n"; return std::pair<double, double>(); }
	return std::make_pair(
		(double)this->texture->Frame_Rect().w * this->scale,
		(double)this->texture->Frame_Rect().h * this->scale
	);
}

Entity::operator std::shared_ptr<Body>()
{
	return this->shared_from_this();
}

Entity::operator std::shared_ptr<Entity>()
{
	return std::dynamic_pointer_cast<Entity>(this->shared_from_this());
}

