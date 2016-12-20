#include "Textfield.h"
#include "Texture.h"
#include "Screen.h"
#include "Output_Handler.h"

SDL_Color Textfield::Color(unsigned int hex)
{
	SDL_Color c;
	c.r = 0xff & hex >> 6;
	c.g = 0xff & hex >> 4;
	c.b = 0xff & hex >> 2;
	c.a = 0xff & hex >> 0;
	return c;
}

Entity<Textfield> Textfield::SetText(Entity<> ent, std::string text, std::string font, Uint32 size, SDL_Color color, unsigned width)
{
	if (!ent) { Output_Handler::Error << "MSG Textfield::SetText : No Entity supplied\n"; return nullptr; }
	if (!(Entity<Textfield>)ent) { Output_Handler::Error << "MSG Textfield::SetText : Given entity is not a Textfield\n"; return nullptr; }
	return ((Entity<Textfield>)ent)->SetText(text, font, size, color, width);
}

Entity<Textfield> Textfield::SetText(std::string text, std::string font_path, Uint32 size,  SDL_Color color, unsigned width)
{
	if (texture)
	{
		texture->Destroy();
		//Output_Handler::Output << "MSG Textfield::Set : Textfield already set\n";
		//return this;
	}
	auto font = TTF_OpenFont(font_path.c_str(), size);
	if (!font)
	{
		Output_Handler::Error << "ERR Textfield::Set : Cannot open " << font_path << " font\n";
		return nullptr;
	}
	SDL_Surface* srf = width > 0 ? 
		TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, width) :
		TTF_RenderText_Blended(font, text.c_str(), color);
	if (!srf)
	{
		Output_Handler::Error << "ERR Textfield::Set : Cannot render text\n";
		return nullptr;
	}
	SDL_Texture* ttr = SDL_CreateTextureFromSurface(Screen::Renderer, srf);
	Texture::Load(Entity<Textfield>(this->shared_from_this()), ttr, srf->w, srf->h, 0, 0);
	SDL_FreeSurface(srf);
	TTF_CloseFont(font);
	if(texture) texture->Scale = 1 / Screen::Get_Scale();

	_Text = text;
	return Entity<Textfield>(this->shared_from_this());
}
