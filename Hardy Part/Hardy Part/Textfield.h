#pragma once
#include "Entity.h"
#include "Texture.h"
#include <SDL_ttf.h>



class Textfield : public Entity
{
public:
	void Create() override {};
	void Update() override {};
	void Events() override {};

	//*** Returns an SDL_Color from given hex
	static SDL_Color Color(unsigned int hex);

	//*** Initializes or changes the text of the given textfield 
	static std::shared_ptr<Textfield> SetText(std::shared_ptr<Object> ent, std::string text, std::string font, Uint32 size = 24, SDL_Color color = Color(0xffffffff), unsigned width = 0);
	//*** Initializes or changes the text of this textfield 
	std::shared_ptr<Textfield> SetText(std::string text, std::string font, Uint32 size = 24, SDL_Color color = Color(0xffffffff), unsigned width = 0);

	//*** Returns the text this Textfield contains
	//*** To change text use SetText
	std::string Text() { return _Text; }

	//*** Returns the width of this Textfield text in pixels
	int TextWidth() { return texture ? texture->Draw_Rect().w : 0; }
	//*** Returns the height of this Textfield text in pixels
	int TextHeight() { return texture ? texture->Draw_Rect().h : 0; }

protected:
	//*** The text this Textfield contains
	//*** Changing this won't change the displayed text - use SetText instead
	std::string _Text = "";
};