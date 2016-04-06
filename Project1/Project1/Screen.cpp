#include "Screen.h"
#include "Entity.h"
#include "State.h"
#include "Sprite.h"
#include "Texture.h"
#include "Tileset.h"


bool Screen::__Initialized = false;

SDL_Window* Screen::Window;
SDL_Renderer* Screen::Renderer;

unsigned Screen::Screen_Width = 800;
unsigned Screen::Screen_Height = 600;
unsigned Screen::__Scale = 2;

std::vector<std::vector<std::shared_ptr<Entity>>> Screen::__Entities;
std::vector<std::shared_ptr<Tileset>> Screen::__Tilesets;


unsigned Screen::Get_Scale()
{
	return __Scale;
}

bool Screen::Start()
{
	if (Screen::__Initialized)
	{
		std::cout << "MSG Screen::Start : Screen has already been initialized\n";
		return false;
	}
	Screen::__Initialized = true;
	Screen::Window = SDL_CreateWindow("Gmae", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen::Screen_Width, Screen::Screen_Height, SDL_WINDOW_SHOWN);
	Screen::Renderer = SDL_CreateRenderer(Screen::Window, -1, SDL_RENDERER_ACCELERATED);
	return true;
}


bool Screen::Add(std::shared_ptr<Entity> ent)
{
	if (!ent) { std::cerr << "ERR Screen::Add : No entity supplied\n"; return false; }
	if (!ent->Get_Sprite()) { std::cerr << "ERR Screen::Add : Given entity has no sprite supplied\n"; return false; }

	if (ent->Get_Layer() >= Screen::__Entities.size())
		Screen::__Entities.resize(ent->Get_Layer() + 1);

	for (unsigned i = 0; i <= Screen::__Entities[ent->Get_Layer()].size(); i++)
	{
		if (i != Screen::__Entities[ent->Get_Layer()].size() && ent->Y > Screen::__Entities[ent->Get_Layer()][i]->Y) continue;
		Screen::__Entities[ent->Get_Layer()].insert(Screen::__Entities[ent->Get_Layer()].begin() + i, ent);
		break;
	}
	return true;
}

bool Screen::Add(std::shared_ptr<Tileset> tileset)
{
	if (!tileset) { std::cerr << "ERR Screen::Add : No tileset supplied\n"; return false; }
	if (!tileset->Get_SDL_Texture()) { std::cerr << "ERR Screen::Add : Given tileset has no SDL_Texture supplied\n"; return false; }
	Screen::__Tilesets.push_back(tileset);
	return true;
}

unsigned Screen::Draw()
{
	for (unsigned i = 0; i < Screen::__Tilesets.size(); ++i)
	{
		auto& tile = Screen::__Tilesets[i];
		if (tile.unique())
		{
			Screen::__Tilesets.erase(Screen::__Tilesets.begin() + i);
			--i;
			continue;
		}
		SDL_Rect src = { 0,0, (int)tile->Get_Size().first, (int)tile->Get_Size().second };
		SDL_Rect dst = {
			(int)tile->Get_Pos().first * (int)Screen::Get_Scale(),
			(int)tile->Get_Pos().second * (int)Screen::Get_Scale(),
			(int)tile->Get_Size().first * (int)Screen::Get_Scale(),
			(int)tile->Get_Size().second * (int)Screen::Get_Scale()
		};
		SDL_RenderCopy(Screen::Renderer, tile->Get_SDL_Texture(), &src, &dst);
	}

	unsigned count = 0;
	Screen::__Reorder();
	for (unsigned layer = 0; layer < Screen::__Entities.size(); ++layer)
	{
		for (unsigned ent = 0; ent < Screen::__Entities[layer].size(); ++ent)
		{
			auto& e = Screen::__Entities[layer][ent];
			if (e.unique())
			{
				Screen::__Entities.erase(Screen::__Entities.begin() + ent);
				--ent;
				continue;
			}
			auto* spr = e->Get_Sprite();
			if (!spr)
			{
				std::cerr << "ERR Screen::Draw : Given Entity has no sprite supplied\n";
				return 0;
			}
			++count;
			SDL_Rect frame_rect = {
				(int)spr->Get_Frame_Pos().first,
				(int)spr->Get_Frame_Pos().second,
				(int)spr->Get_Frame_Size().first,
				(int)spr->Get_Frame_Size().second,
			};
			SDL_Rect draw_rect = {
				(int)e->X - e->Get_Sprite()->Get_Texture()->Get_SDL_Starting_Point().x * (int)Screen::Get_Scale(),
				(int)e->Y - e->Get_Sprite()->Get_Texture()->Get_SDL_Starting_Point().y * (int)Screen::Get_Scale(),
				(int)spr->Get_Frame_Size().first * (int)Screen::Get_Scale(),
				(int)spr->Get_Frame_Size().second * (int)Screen::Get_Scale(),
			};

			auto p = spr->Get_Texture()->Get_SDL_Starting_Point();
			p.x *= Screen::Get_Scale();
			p.y *= Screen::Get_Scale();
			SDL_RenderCopyEx
				(
					Screen::Renderer,
					spr->Get_SDL_Texture(),
					&frame_rect, &draw_rect,
					spr->Rotation,
					&p,
					spr->Flip
					);
		}
	}
	
	SDL_RenderPresent(Screen::Renderer);
	SDL_RenderClear(Screen::Renderer);
	//Screen::__Entities.clear();
	return count;
}

void Screen::Exit()
{
	SDL_DestroyRenderer(Screen::Renderer);
	SDL_DestroyWindow(Screen::Window);
}

bool Screen::__Reorder()
{
	for (unsigned layer = 0; layer < __Entities.size(); ++layer)
		for (unsigned i = 1; i < __Entities[layer].size(); ++i)
		{
			auto temp = __Entities[layer][i];
			int j = i - 1;
			while (j >= 0 && __Entities[layer][j]->Y > temp->Y)
			{
				__Entities[layer][j + 1] = __Entities[layer][j];
				--j;
			}
			__Entities[layer][j + 1] = temp;
		}
	return true;
}
