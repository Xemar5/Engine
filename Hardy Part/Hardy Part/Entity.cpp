#include "Entity.h"
#include "Texture.h"
#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"


void Entity::Create()
{
}

void Entity::Update()
{
}

void Entity::Events()
{
}

Hitbox * Entity::Get_Hitbox()
{
	if (!this) { std::cerr << "ERR Entity::Get_Hitbox : No this Entity\n"; return nullptr; }
	return __Hitbox.get();
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


