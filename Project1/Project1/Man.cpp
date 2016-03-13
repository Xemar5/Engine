#include "Man.h"
#include "Input_Handler.h"


void Man::Create()
{
	Load_Sprite("imgs/Sprite-0001-sheet.png", 96, 32, -3, 0, 0, 1);
	Add_Animation("idle2", "0x100 1x100 2x100", true);
	//Load_Sprite("imgs/Paku_G.bmp", 256, 128, -8, -4, 0, 1);
	//Add_Animation("idle2", "0x43 1x5 2x26 1x5", true);
	Play_Animation("idle2");
	Set_Movement(10);
	X = 20;
	Y = 20;
}
	double vx = 0;
	double vy = 0;
void Man::Update()
{
	Move(vx, vy, .02);
	Entity::Update();
}
void Man::Events()
{
	if (Input_Handler::Key_Held(SDLK_w)) vy = -1;
	else if (Input_Handler::Key_Held(SDLK_s)) vy = 1;
	else vy = 0;
	if (Input_Handler::Key_Held(SDLK_a)) vx = -1;
	else if (Input_Handler::Key_Held(SDLK_d)) vx = 1;
	else vx = 0;
}