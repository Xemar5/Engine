#include "Sprite_Handler.h"
#include "Sprite.h"
#include "Animation.h"

std::vector<std::shared_ptr<Sprite_Handler>> Sprite_Handler::__Sprite_Handlers;


Sprite_Handler * Sprite_Handler::Create(Sprite * sprite)
{
	if (!sprite)
	{
		std::cerr << "ERR Sprite_Handler::Set : No Sprite supplied\n";
		return nullptr;
	}
	Sprite_Handler::__Sprite_Handlers.emplace_back(std::make_shared<Sprite_Handler>());
	Sprite_Handler::__Sprite_Handlers.back()->__Sprite = sprite;
	Sprite_Handler::__Sprite_Handlers.back()->Flip = SDL_FLIP_NONE;
	return Sprite_Handler::__Sprite_Handlers.back().get();
}


Sprite * Sprite_Handler::Get_Sprite()
{
	return __Sprite;
}


SDL_Texture * Sprite_Handler::Get_Texture()
{
	if (__Sprite)
		return __Sprite->Get_Texture();
	return nullptr;
}

std::pair<unsigned, unsigned> Sprite_Handler::Get_Frame_Size()
{
	if (this && __Sprite)
		return __Sprite->Get_Frame_Size();
	std::cerr << "ERR Sprite_Handler::Get_Frame_Size : No Sprite loaded\n";
	return std::make_pair(0,0);
}

std::pair<unsigned, unsigned> Sprite_Handler::Get_Frame_Pos()
{
	return std::make_pair(__Frame_Pos_X, __Frame_Pos_Y);
}

int Sprite_Handler::Get_Current_Frame()
{
	if (!this || !__Current_Animation)
	{
		std::cerr << "ERR Sprite_Handler::Get_Current_Frame : No Current Animation\n";
		return -1;
	}
	return __Current_Animation->Get_Current_Frame(__Sequence_Iterator);
}

Animation * Sprite_Handler::Get_Current_Animation()
{
	return __Current_Animation;
}
