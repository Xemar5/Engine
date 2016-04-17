#include "Character.h"

#include "Sprite.h"
#include "Texture.h"
#include "Animation.h"
#include "Movement.h"

void Character<Character_Enum::Mosh>::Create()
{
	Sprite::Create(this, Texture::Load("imgs/mosh-sheet.png", 168, 24, 24, 24, 0, 1));
	Animation::Add(this, "idle", "0x70 1x3", true);
	Animation::Add(this, "move", "0x6 2-6x6", false);
	Movement::Set(this, 2.3, 10);
}
void Character<Character_Enum::Mosh>::Update()
{

}
void Character<Character_Enum::Mosh>::Events()
{

}


template class Character<Character_Enum::Mosh>;