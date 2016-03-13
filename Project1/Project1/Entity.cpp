#include "Entity.h"
#include "Sprite.h"
#include "Sprite_Handler.h"
#include "Animation.h"
#include "Movement.h"


void Entity::Update()
{
	if (Animation::Next_Frame(Get_Sprite_Handler()) != -1)
	{
		Animation::Set_Frame(Get_Sprite_Handler(), Get_Current_Frame());
	}
	else if(!Get_Sprite_Handler()->Get_Current_Animation()) Play_Animation("idle");
}

bool Entity::Load_Sprite(std::string path, unsigned width, unsigned height, int frame_width, int frame_height, float starting_point_x, float starting_point_y)
{
	Sprite* sprt = nullptr;
	if (__Sprite_Handler)
	{
		printf("MSG Entity::Load_Sprite : An Sprite was already loaded, changing to new sprite\n");
	}
	if (!(sprt = Sprite::Load(path, width, height, frame_width, frame_height, starting_point_x, starting_point_y)))
	{
		printf("ERR Entity::Load_Sprite : No sprite was loaded\n");
		return nullptr;
	}
	__Sprite_Handler = Sprite_Handler::Create(sprt);
	Add_Animation("idle", "0", true);
	return false;
}

Animation * Entity::Add_Animation(std::string name, std::string frame_sequence, bool repeat)
{
	if (!__Sprite_Handler)
	{
		std::cerr << "ERR Entity::Add_Animation : No Sprite Handler supplied, use Load_Sprite function first\n";
		return nullptr;
	}
	return Animation::Add(Get_Sprite(), name, frame_sequence, repeat);
}

Animation * Entity::Play_Animation(std::string name)
{
	if (!__Sprite_Handler)
	{
		std::cerr << "ERR Entity::Play_Animation : No Sprite Handler supplied, use Load_Sprite function first\n";
		return nullptr;
	}
	return Animation::Play(Get_Sprite_Handler(), name);
}

bool Entity::Set_Movement(int mass)
{
	__Movement = Movement::Set(X, Y, mass);
	return true;
}

bool Entity::Move(double force_x, double force_y, double traction)
{
	return Movement::Move(Get_Movement(), force_x, force_y, traction);
}

Movement * Entity::Get_Movement()
{
	return __Movement;
}

Sprite_Handler* Entity::Get_Sprite_Handler()
{
	return __Sprite_Handler;
}
Sprite* Entity::Get_Sprite()
{
	if (__Sprite_Handler)
		return __Sprite_Handler->Get_Sprite();
	return nullptr;
}

int Entity::Get_Current_Frame()
{
	return __Sprite_Handler->Get_Current_Frame();
}
