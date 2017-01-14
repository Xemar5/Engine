#include "Texture.h"
#include "Screen.h"
#include "Entity.h"

std::vector<std::shared_ptr<Texture>> Texture::__Textures;

std::shared_ptr<Texture> Texture::Load(std::shared_ptr<Entity> ent, std::string path, unsigned width, unsigned height, float starting_point_x, float starting_point_y)
{
	if (!path.size())
	{
		Output_Handler::Error << "ERR Texture::Load : No path supplied\n";
		return nullptr;
	}


	SDL_Texture* texture = nullptr;
	for (auto& ttr : Texture::__Textures) if (path == ttr->__Path)
	{
		texture = ttr->Get_SDL_Texture();
		break;
	}
	if (!texture) texture = IMG_LoadTexture(Screen::Renderer, path.c_str());
	if (!texture)
	{
		Output_Handler::Error << "ERR Texture::Load : No valid texture file supplied\n";
		return nullptr;
	}


	Texture::__Textures.emplace_back(std::make_shared<Texture>());
	Texture::__Textures.back()->__Path = path;
	Texture::__Textures.back()->__SDL_Texture = texture;
	return __Load(ent, Texture::__Textures.back(), width, height, starting_point_x, starting_point_y);
}


std::shared_ptr<Texture> Texture::Load(std::shared_ptr<Entity> ent, SDL_Texture * texture, unsigned width, unsigned height, float starting_point_x, float starting_point_y)
{
	if (!texture)
	{
		Output_Handler::Error << "ERR Texture::Load : No SDL_Texture supplied\n";
		return nullptr;
	}
	for (auto& t : __Textures)
		if (t->__SDL_Texture == texture)
			return t;
	Texture::__Textures.emplace_back(std::make_shared<Texture>());
	Texture::__Textures.back()->__Path = "";
	Texture::__Textures.back()->__SDL_Texture = texture;
	return __Load(ent, Texture::__Textures.back(), width, height, starting_point_x, starting_point_y);
}

bool Texture::Reload()
{
	if (!__Path.size()) return false;

	SDL_Texture* ttr = IMG_LoadTexture(Screen::Renderer, __Path.c_str());
	if (!ttr) return false;
	SDL_DestroyTexture(__SDL_Texture);
	__SDL_Texture = ttr;

	return true;
}

bool Texture::Set_Starting_Pos(float x, float y)
{
	if (!this)
	{
		Output_Handler::Error << "ERR Texure::Set_Starting_Pos : No this object\n";
		return false;
	}
	if (x < -1) x = -1;
	if (x > 1) x = 1;
	if (y < -1) y = -1;
	if (y > 1) y = 1;
	__X_Off = x;
	__Y_Off = y;
	return true;
}

SDL_Point Texture::Starting_Point()
{
	if (!this)
	{
		Output_Handler::Error << "ERR Texure::Starting_Point : No this Texture\n";
		return{ 0,0 };
	}
	return
	{
		(int)((1.0 + __X_Off) / 2.0 * __Width),
		(int)((1.0 + __Y_Off) / 2.0 * __Height)
	};
}



bool Texture::Destroy()
{
	unsigned count = 0;
	auto this_texture = __Textures.end();
	if (!__SDL_Texture) return false;
	for (auto it = __Textures.begin(); it != __Textures.end(); ++it)
	{
		if (it->get()->__SDL_Texture == __SDL_Texture)
			++count;
		if (it->get() == this)
			this_texture = it;
	}
	if (count == 1)
	{
		SDL_DestroyTexture(__SDL_Texture);
		__SDL_Texture = nullptr;
	}
	if (this_texture != __Textures.end())
		__Textures.erase(this_texture);
	return true;
}

std::shared_ptr<Texture> Texture::__Load(std::shared_ptr<Entity> ent, std::shared_ptr<Texture> t, unsigned width, unsigned height, float starting_point_x, float starting_point_y)
{
	t->__Width = width;
	t->__Height = height;
	t->__X_Off = starting_point_x;
	t->__Y_Off = starting_point_y;
	if (ent) ent->texture = t;
	return t;
}
