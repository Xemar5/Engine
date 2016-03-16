#include "Entity.h"
#include "Texture.h"
#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"


Hitbox * Entity::Get_Hitbox()
{
	return __Hitbox.get();
}

Sprite * Entity::Get_Sprite()
{
	return __Sprite;
}

std::vector<std::shared_ptr<Action>> Entity::Get_Actions()
{
	return __Actions;
}

Stats * Entity::Get_Stats()
{
	return __Stats;
}

Movement * Entity::Get_Movement()
{
	return __Movement.get();
}
