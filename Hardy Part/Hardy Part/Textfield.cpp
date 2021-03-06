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

std::shared_ptr<Textfield> Textfield::SetText(std::shared_ptr<Object> ent, std::string text, std::string font, Uint32 size, SDL_Color color, unsigned width)
{
	if (!ent) { Output_Handler::Error << "MSG Textfield::SetText : No Entity supplied\n"; return nullptr; }
	auto t = std::dynamic_pointer_cast<Textfield>(ent);
	if (!t) { Output_Handler::Error << "MSG Textfield::SetText : Given entity is not a Textfield\n"; return nullptr; }
	return t->SetText(text, font, size, color, width);
}

std::shared_ptr<Textfield> Textfield::SetText(std::string text, std::string font_path, Uint32 size,  SDL_Color color, unsigned width)
{
	if (texture)
	{
		texture->Destroy();
		//Output_Handler::Output << "MSG Textfield::Change : Textfield already set\n";
		//return this;
	}
	auto font = TTF_OpenFont(font_path.c_str(), size);
	if (!font)
	{
		Output_Handler::Error << "ERR Textfield::Change : Cannot open " << font_path << " font\n";
		return nullptr;
	}
	SDL_Surface* srf = width > 0 ? 
		TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, width) :
		TTF_RenderText_Blended(font, text.c_str(), color);
	if (!srf)
	{
		Output_Handler::Error << "ERR Textfield::Change : Cannot render text\n";
		return nullptr;
	}
	double x_off = texture ? texture->Get_Starting_Pos().first : 0;
	double y_off = texture ? texture->Get_Starting_Pos().second : 0;
	SDL_Texture* ttr = SDL_CreateTextureFromSurface(Screen::Renderer, srf);
	std::shared_ptr<Textfield> tf = std::dynamic_pointer_cast<Textfield>(this->shared_from_this());
	Texture::Load(tf, ttr, srf->w, srf->h, x_off, y_off);
	SDL_FreeSurface(srf);
	TTF_CloseFont(font);
	//if(texture) texture->Scale = 1 / Screen::Get_Scale();

	_Text = text;
	return tf;
}
