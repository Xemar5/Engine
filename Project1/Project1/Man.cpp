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
void Man::Update()
{
	double vx1 = 0;
	double vy1 = 0;
	double vx2 = 0;
	double vy2 = 0;
	if (Input_Handler::Key_Held(SDLK_w)) vy1 = -3;
	if (Input_Handler::Key_Held(SDLK_s)) vy2 = 3;
	if (Input_Handler::Key_Held(SDLK_a)) vx1 = -3;
	if (Input_Handler::Key_Held(SDLK_d)) vx2 = 3;
	Move(vx1 + vx2, vy1 + vy2, 0.02);
	Entity::Update();
}
void Man::Events()
{
}