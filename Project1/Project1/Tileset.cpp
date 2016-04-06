#include "Tileset.h"
#include "Sprite.h"
#include "Texture.h"
#include "Screen.h"
#include <iostream>


std::shared_ptr<Tileset> Tileset::Set(Texture * texture, std::pair<int, int> pos, std::vector<std::vector<unsigned>> map)
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

	ts->__SDL_Texture = SDL_CreateTexture(Screen::Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		texture->Get_Frame_Size().first * map[0].size(),
		texture->Get_Frame_Size().second * map.size());

	SDL_SetRenderTarget(Screen::Renderer, ts->__SDL_Texture);

	ts->__Texture = texture;
	ts->__Pos = pos;
	ts->__Tilemap = map;

	auto frame_size = texture->Get_Frame_Size();
	SDL_Rect src = { 0,0, (int)frame_size.first, (int)frame_size.second };
	SDL_Rect dst = { 0,0, (int)frame_size.first, (int)frame_size.second };

	for (unsigned i = 0; i < map.size(); i++)
	{
		for (unsigned j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 1)
			{
				ts->__Wall_Placeholders.push_back(std::make_pair(dst.x, dst.y));
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

unsigned Tileset::Which_Tile(int x, int y)
{
	if (!this) { std::cerr << "ERR Tileset::Which_Tile : No this Tileset\n"; return 0; }
	if (!__Texture) { std::cerr << "ERR Tileset::Which_Tile : No Sprite supplied\n"; return 0; }
	std::pair<unsigned, unsigned> frame_size = __Texture->Get_Frame_Size();
	if(!frame_size.first || !frame_size.second) { std::cerr << "ERR Tileset::Which_Tile : Frame size has width/height equal to 0\n"; return 0; }
	x -= __Pos.first;
	y -= __Pos.second;

	x /= frame_size.first * Screen::Get_Scale();
	y /= frame_size.second * Screen::Get_Scale();

	if (x < 0 || x >= (int)Get_Size().first / frame_size.first ||
		y < 0 || y >= (int)Get_Size().second / frame_size.second)
	{
		return 0;
	}
	return __Tilemap[y][x];
}

std::pair<int, int> Tileset::Get_Pos()
{
	return __Pos;
}

bool Tileset::Set_Pos(int x, int y)
{
	if (!this)
	{
		std::cerr << "ERR Tileset::Set_Pos : No this Tileset\n";
		return false;
	}
	__Pos.first = x;
	__Pos.second = y;
	return true;
}

bool Tileset::Set_Pos_Relative(int x, int y)
{
	if (!this)
	{
		std::cerr << "ERR Tileset::Set_Pos_Relative : No this Tileset\n";
		return false;
	}
	__Pos.first += x;
	__Pos.second += y;
	return true;
}

std::pair<unsigned, unsigned> Tileset::Get_Size()
{
	if (!__Tilemap.size() || !__Tilemap[0].size())
	{
		std::cerr << "ERR Tileset::Get_Size : Supplied Tilemap has width/height equal to 0\n";
		return{ 0,0 };
	}
	return std::make_pair(__Tilemap[0].size() * __Texture->Get_Frame_Size().first,__Tilemap.size() * __Texture->Get_Frame_Size().second);
}

Texture * Tileset::Get_Texture()
{
	if (!this)
	{
		std::cerr << "ERR Tileset::Get_Sprite : No this Tileset\n";
		return nullptr;
	}
	return __Texture;
}


SDL_Texture * Tileset::Get_SDL_Texture()
{
	if (!this)
	{
		std::cerr << "ERR Tileset::Get_Texture : No this Tileset\n";
		return nullptr;
	}
	return __SDL_Texture;
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

