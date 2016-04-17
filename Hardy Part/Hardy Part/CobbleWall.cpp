#include "Wall.h"

#include "Sprite.h"
#include "Texture.h"
#include "Animation.h"
#include "Movement.h"

void Wall<Wall_Enum::Cobble>::Create()
{
	Sprite::Create(this, Texture::Load("imgs/orange-wall.png", 72, 48, 24, 48, -1, 1));
	Animation::Add(this, "type0", "0", true);
	Animation::Add(this, "type1", "1", true);
	Animation::Add(this, "type2", "2", true);
}
void Wall<Wall_Enum::Cobble>::Update()
{

}
void Wall<Wall_Enum::Cobble>::Events()
{

}


template class Wall<Wall_Enum::Cobble>;