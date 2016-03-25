#include "Man.h"

#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Texture.h"

void Man::Create()
{
	Sprite::Create(this, Texture::Load("imgs/dut1-sheet.png", 120, 24, -5, 0, 0, 1));
	Animation::Add(this, "idle", "0", true);
	Animation::Add(this, "move", "0-4x4", false);
	Movement::Set(this, 2.3, 10);
}
void Man::Update()
{

}
void Man::Events()
{

}