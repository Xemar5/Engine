#include "Wall.h"

#include "Sprite.h"
#include "Texture.h"
#include "Animation.h"
#include "Movement.h"

void Wall<Wall_Enum::Cobble>::Create()
{
	Sprite::Load(this, "imgs/orange-wall.png", 72, 48, 24, 48, -1, 1);
	Sprite::Add_Animation(this->Display(), Animation("type0", "0", true));
	Sprite::Add_Animation(this->Display(), Animation("type0", "1", true));
	Sprite::Add_Animation(this->Display(), Animation("type0", "2", true));
}
void Wall<Wall_Enum::Cobble>::Update()
{

}
void Wall<Wall_Enum::Cobble>::Events()
{

}


template class Wall<Wall_Enum::Cobble>;