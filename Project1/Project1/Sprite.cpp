#include "Sprite.h"
#include "Texture.h"
#include "Animation.h"
#include "Entity.h"

std::vector<std::shared_ptr<Sprite>> Sprite::__Sprites;


Sprite * Sprite::Create(Entity* ent, Texture * texture)
{
	if (!ent)
	{
		std::cout << "MSG Sprite::Create : No entity supplied; returning pointer to this sprite\n";
	}
	if (!texture)
	{
		std::cerr << "ERR Sprite::Set : No Texture supplied\n";
		return nullptr;
	}
	Sprite::__Sprites.emplace_back(std::make_shared<Sprite>());
	Sprite::__Sprites.back()->__Texture = texture;
	Sprite::__Sprites.back()->Flip = SDL_FLIP_NONE;
	if (ent) ent->__Sprite = Sprite::__Sprites.back().get();
	return Sprite::__Sprites.back().get();
}


Texture * Sprite::Get_Texture()
{
	return __Texture;
}


SDL_Texture * Sprite::Get_SDL_Texture()
{
	if (__Texture)
		return __Texture->Get_SDL_Texture();
	return nullptr;
}

std::pair<unsigned, unsigned> Sprite::Get_Frame_Size()
{
	if (this && __Texture)
		return __Texture->Get_Frame_Size();
	std::cerr << "ERR Sprite::Get_Frame_Size : No Texture loaded\n";
	return std::make_pair(0,0);
}

std::pair<unsigned, unsigned> Sprite::Get_Frame_Pos()
{
	return std::make_pair(__Frame_Pos_X, __Frame_Pos_Y);
}

int Sprite::Get_Current_Frame()
{
	if (!this || !__Current_Animation)
	{
		std::cerr << "ERR Sprite::Get_Current_Frame : No Current Animation\n";
		return -1;
	}
	return __Current_Animation->Get_Current_Frame(__Sequence_Iterator);
}

Animation * Sprite::Get_Current_Animation()
{
	return __Current_Animation;
}
