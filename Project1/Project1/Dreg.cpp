#include "Character.h"

#include "Sprite.h"
#include "Texture.h"
#include "Animation.h"
#include "Movement.h"

void Character<Character_Enum::Dreg>::Create()
{
	Sprite::Create(this, Texture::Load("imgs/dreg-sheet.png", 216, 24, 24, 24, 0, 1));
	Animation::Add(this, "idle", "0x63 1-3x5", true);
	Animation::Add(this, "move", "4-8x4", false);
	Movement::Set(this, 2.3, 10);
}
void Character<Character_Enum::Dreg>::Update()
{

}
void Character<Character_Enum::Dreg>::Events()
{

}


template class Character<Character_Enum::Dreg>;