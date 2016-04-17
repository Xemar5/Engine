#include "Character.h"

#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Texture.h"

void Character<Character_Enum::Nerk>::Create()
{
	Sprite::Create(this, Texture::Load("imgs/nerk-sheet.png", 144, 24, 24, 24, 0, 1));
	Animation::Add(this, "idle", "0x80 1x5", true);
	Animation::Add(this, "move", "0x4 2-5x4", false);
	Movement::Set(this, 2.3, 10);
}
void Character<Character_Enum::Nerk>::Update()
{

}
void Character<Character_Enum::Nerk>::Events()
{

}


template class Character<Character_Enum::Nerk>;