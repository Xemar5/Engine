#include "Entity.h"
#include "Texture.h"
#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Screen.h"
#include "Output_Handler.h"


void Entity::Create()
{
}

void Entity::Update()
{
}

void Entity::Events()
{
}

std::pair<double, double> Entity::Get_Hitbox()
{
	if (!this) { Output_Handler::Error << "ERR Entity::Get_Hitbox : No this Entity\n"; return std::pair<double, double>(); }
	if (!this->Get_Sprite()) { Output_Handler::Error << "ERR Entity::Get_Hitbox : This entity has no sprite supplied\n"; return std::pair<double, double>(); }
	return std::make_pair(
		(double)this->Get_Sprite()->Get_Frame_Size().first * this->Get_Sprite()->Scale,
		(double)this->Get_Sprite()->Get_Frame_Size().second * this->Get_Sprite()->Scale
		);
}

std::shared_ptr<Sprite> Entity::Get_Sprite()
{
	if (!this) { Output_Handler::Error << "ERR Entity::Get_Sprite : No this Entity\n"; return nullptr; }
	return __Sprite;
}

std::shared_ptr<Texture> Entity::Get_Texture()
{
	if (!this) { Output_Handler::Error << "ERR Entity::Get_Texture : No this Entity\n"; return nullptr; }
	if (!Get_Sprite()) { Output_Handler::Error << "ERR Entity::Get_Texture : This entity has no sprite supplied\n"; return nullptr; }
	return Get_Sprite()->Get_Texture();
}

double Entity::Get_Scale()
{
	if (!this) { Output_Handler::Error << "ERR Entity::Get_Texture : No this Entity\n"; return 1.0; }
	if (!Get_Sprite()) { Output_Handler::Error << "ERR Entity::Get_Texture : This entity has no sprite supplied\n"; return 1.0; }
	return Get_Sprite()->Scale;
}

//std::vector<std::shared_ptr<Action>> Entity::Get_Actions()
//{
//	if (!this) { Output_Handler::Error << "ERR Entity::Get_Actions : No this Entity\n"; return{}; }
//	return __Actions;
//}
//
//Stats * Entity::Get_Stats()
//{
//	if (!this) { Output_Handler::Error << "ERR Entity::Get_Stats : No this Entity\n"; return nullptr; }
//	return __Stats;
//}

Movement * Entity::Get_Movement()
{
	if (!this) { Output_Handler::Error << "ERR Entity::Get_Movement : No this Entity\n"; return nullptr; }
	return __Movement.get();
}

unsigned Entity::Get_Layer()
{
	return ++__Layer;
}

bool Entity::Destroy(Entity * ent)
{
	if (!ent)
	{
		Output_Handler::Output << "MSG Entity::Destroy : No entity supplied\n";
		return false;
	}
	auto sprt = ent->__Sprite.get();
	ent->__Sprite = nullptr;
	Sprite::Destroy(sprt);
	return true;
}



