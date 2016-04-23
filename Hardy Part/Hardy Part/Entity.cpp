#include "Entity.h"
#include "Texture.h"
#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Screen.h"


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
	if (!this) { std::cerr << "ERR Entity::Get_Hitbox : No this Entity\n"; return std::pair<double, double>(); }
	if (!this->Get_Sprite()) { std::cerr << "ERR Entity::Get_Hitbox : This entity has no sprite supplied\n"; return std::pair<double, double>(); }
	return std::make_pair(
		this->Get_Sprite()->Get_Frame_Size().first * this->Get_Sprite()->Scale * Screen::Get_Scale(),
		this->Get_Sprite()->Get_Frame_Size().second * this->Get_Sprite()->Scale * Screen::Get_Scale()
		);
}

std::shared_ptr<Sprite> Entity::Get_Sprite()
{
	if (!this) { std::cerr << "ERR Entity::Get_Sprite : No this Entity\n"; return nullptr; }
	return __Sprite;
}

std::vector<std::shared_ptr<Action>> Entity::Get_Actions()
{
	if (!this) { std::cerr << "ERR Entity::Get_Actions : No this Entity\n"; return{}; }
	return __Actions;
}

Stats * Entity::Get_Stats()
{
	if (!this) { std::cerr << "ERR Entity::Get_Stats : No this Entity\n"; return nullptr; }
	return __Stats;
}

Movement * Entity::Get_Movement()
{
	if (!this) { std::cerr << "ERR Entity::Get_Movement : No this Entity\n"; return nullptr; }
	return __Movement.get();
}

unsigned Entity::Get_Layer()
{
	if (!this) { std::cerr << "ERR Entity::Get_Layer : No this Entity\n"; return 0; }
	return __Layer;
}



