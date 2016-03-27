#include "Character.h"

#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Texture.h"

void Character<Tar>::Create()
{
	Sprite::Create(this, Texture::Load("imgs/tar-sheet.png", 216, 24, 24, 24, 0, 1));
	Animation::Add(this, "idle", "0x85 1x5", true);
	Animation::Add(this, "move", "0x4 2-8x4", false);
	Movement::Set(this, 2.2, 40);
}
void Character<Tar>::Update()
{

}
void Character<Tar>::Events()
{

}


template class Character<Tar>;