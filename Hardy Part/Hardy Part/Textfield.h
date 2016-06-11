#pragma once
#include "Entity.h"
#include <SDL_ttf.h>


class Textfield : public Entity
{
public:
	Textfield* Set(std::string text, std::string font, Uint32 size = 24, SDL_Color color = 0xffffffff);
private:
	
	
};