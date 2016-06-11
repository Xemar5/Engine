#include "Textfield.h"
#include "Screen.h"
#include "Output_Handler.h"

Textfield* Textfield::Set(std::string text, std::string font_path, Uint32 size,  SDL_Color color)
{
	auto font = TTF_OpenFont(font_path.c_str(), size);
	if (!font)
	{
		Output_Handler::Error << "ERR Textfield::Set : Cannot open " << font_path << " font\n";
		return nullptr;
	}
	SDL_Surface* srf = TTF_RenderText_Blended(font, text.c_str(), color);
	if (!srf)
	{
		Output_Handler::Error << "ERR Textfield::Set : Cannot render text\n";
		return nullptr;
	}
	SDL_Texture* ttr = SDL_CreateTextureFromSurface(Screen::Renderer, srf);
	if (Get_Sprite())
		Sprite::Destroy(Get_Sprite().get());
	Sprite::Create(this, Texture::Load(ttr, srf->w, srf->h));
	SDL_FreeSurface(srf);
	TTF_CloseFont(font);
	if(Get_Sprite())Get_Sprite()->Scale = 1 / Screen::Get_Scale();
	return this;
}
