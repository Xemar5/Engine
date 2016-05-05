#include "Tileset.h"
#include "Sprite.h"
#include "Texture.h"
#include "Screen.h"
#include "State.h"
#include <iostream>


std::shared_ptr<Tileset> Tileset::Set(std::shared_ptr<Texture> texture, std::vector<std::vector<unsigned>> map)
{
	if (!texture)
	{
		std::cerr << "ERR Tileset::Set : No Texture supplied\n";
		return nullptr;
	}
	if (!map.size() || !map[0].size())
	{
		std::cerr << "ERR Tileset::Set : Given map has width/height equal to 0\n";
		return nullptr;
	}
	
	std::shared_ptr<Tileset> ts = std::make_shared<Tileset>();
	auto frame_size = texture->Get_Frame_Size();

	SDL_Texture* ttr = SDL_CreateTexture(Screen::Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		frame_size.first * map[0].size(),
		frame_size.second * map.size());

	ts->__Texture = Texture::Load(ttr,
		frame_size.first * map[0].size(),
		frame_size.second * map.size(),
		frame_size.first * map[0].size(),
		frame_size.second * map.size(),
		texture->Get_Starting_Point().first,
		texture->Get_Starting_Point().second
	);

	SDL_SetTextureBlendMode(ts->__Texture->Get_SDL_Texture(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Screen::Renderer, ts->__Texture->Get_SDL_Texture());

	ts->__Product_Texture = texture;
	ts->__Tilemap = map;

	SDL_Rect src = { 0,0, (int)frame_size.first, (int)frame_size.second };
	SDL_Rect dst = { 0,0, (int)frame_size.first, (int)frame_size.second };

	for (unsigned i = 0; i < map.size(); i++)
	{
		for (unsigned j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 1)
			{
				ts->__Wall_Placeholders.push_back(std::make_pair(dst.x + ts->X, dst.y + ts->Y));
			}
			if (map[i][j] < texture->Max_Frames())
			{
				auto frame_pos = texture->Get_Frame_Pos(map[i][j]);
				src.x = frame_pos.first;
				src.y = frame_pos.second;
			}
			else
			{
				std::cout << "MSG Tileset::Set : Tile " << map[i][j] << " doesn't exist (max " << texture->Max_Frames() - 1 << "); no tile is drawn\n";
				src.x = 0;
				src.y = 0;
			}
			if(src.x || src.y)
				SDL_RenderCopy(Screen::Renderer, texture->Get_SDL_Texture(), &src, &dst);
			dst.x += frame_size.first;
		}
		dst.y += frame_size.second;
		dst.x = 0;
	}


	SDL_SetRenderTarget(Screen::Renderer, NULL);
	return ts;
}

Tileset * Tileset::Add(State * state, std::shared_ptr<Tileset> tileset, double x, double y, unsigned layer, double scale)
{
	if (!state)
	{
		std::cout << "MSG Tileset::Add : No State supplied; initializing tileset\n";
	}
	if (!tileset)
	{
		std::cerr << "ERR Tileset::Add : No tileset supplied\n";
		return nullptr;
	}
	(*state)[layer].Entities.push_back(tileset);
	tileset->Create();
	tileset->X = x;
	tileset->Y = y;
	tileset->Scale = scale;
	Screen::Add(tileset, layer);
	return tileset.get();
}

bool Tileset::Reset(std::shared_ptr<Tileset> tileset)
{
	return Tileset::Reset(tileset.get());
}

bool Tileset::Reset(Tileset * tileset)
{
	if (!tileset)
	{
		std::cout << "MSG Tileset::Reset : No Tileset supplied\n";
		return false;
	}
	Texture::Reload(tileset->Get_Texture().get());
	tileset->__Product_Texture = Tileset::Set(tileset->__Texture, tileset->__Tilemap)->__Product_Texture;
	return false;
}

unsigned Tileset::Which_Tile(int x, int y)
{
	if (!this) { std::cerr << "ERR Tileset::Which_Tile : No this Tileset\n"; return 0; }
	if (!__Texture) { std::cerr << "ERR Tileset::Which_Tile : No Sprite supplied\n"; return 0; }
	std::pair<unsigned, unsigned> frame_size = __Product_Texture->Get_Frame_Size();
	if(!frame_size.first || !frame_size.second) { std::cerr << "ERR Tileset::Which_Tile : Frame size has width/height equal to 0\n"; return 0; }

	x -= (int)X - __Texture->Get_SDL_Starting_Point().x;
	y -= (int)Y - __Texture->Get_SDL_Starting_Point().y;

	x /= frame_size.first;
	y /= frame_size.second;

	if (x < 0 || x >= (int)__Texture->Get_Size().first / (int)frame_size.first ||
		y < 0 || y >= (int)__Texture->Get_Size().second / (int)frame_size.second)
	{
		return 0;
	}
	return __Tilemap[y][x];
}


//std::pair<int, int> Tileset::Get_Pos()
//{
//	return __Pos;
//}
//
//std::pair<int, int> Tileset::Get_Real_Pos()
//{
//	return
//	{
//		__Pos.first - (double)(Get_Texture()->Get_Starting_Point().first + 1) / 2 * Get_Size().first,
//		__Pos.second - (double)(Get_Texture()->Get_Starting_Point().second + 1) / 2 * Get_Size().second
//	};
//}
//
//bool Tileset::Set_Pos(int x, int y)
//{
//	if (!this)
//	{
//		std::cerr << "ERR Tileset::Set_Pos : No this Tileset\n";
//		return false;
//	}
//	__Pos.first = x;
//	__Pos.second = y;
//	return true;
//}
//
//bool Tileset::Set_Pos_Relative(int x, int y)
//{
//	if (!this)
//	{
//		std::cerr << "ERR Tileset::Set_Pos_Relative : No this Tileset\n";
//		return false;
//	}
//	__Pos.first += x;
//	__Pos.second += y;
//	return true;
//}

double Tileset::Get_Scale()
{
	return Scale;
}

//std::pair<unsigned, unsigned> Tileset::Get_Size()
//{
//	if (!__Tilemap.size() || !__Tilemap[0].size())
//	{
//		std::cerr << "ERR Tileset::Get_Size : Supplied Tilemap has width/height equal to 0\n";
//		return{ 0,0 };
//	}
//	return std::make_pair(__Tilemap[0].size() * __Texture->Get_Frame_Size().first,__Tilemap.size() * __Texture->Get_Frame_Size().second);
//}

std::shared_ptr<Texture> Tileset::Get_Texture()
{
	if (!this)
	{
		std::cerr << "ERR Tileset::Get_Sprite : No this Tileset\n";
		return nullptr;
	}
	return __Texture;
}


std::shared_ptr<Texture> Tileset::Get_Product_Texture()
{
	if (!this)
	{
		std::cerr << "ERR Tileset::Get_Texture : No this Tileset\n";
		return nullptr;
	}
	return __Product_Texture;
}

unsigned Tileset::Get_Tiles_Count()
{
	if (!this)
	{
		std::cerr << "ERR Tileset::Get_Tiles_Count : No this Tileset\n";
		return 0;
	}
	auto sp = Get_Texture();
	if (!sp)
	{
		std::cerr << "ERR Tileset::Get_Tiles_Count : No Sprite supplied\n";
		return 0;
	}
	return Get_Texture()->Max_Frames();
}

std::vector<std::pair<int, int>> Tileset::Get_Wall_Placeholders()
{
	return __Wall_Placeholders;
}

