#include "Screen.h"
#include "Entity.h"
#include "Sprite.h"
#include "Texture.h"
#include "Tileset.h"

bool Screen::__Initialized = false;

SDL_Window* Screen::Window;
SDL_Renderer* Screen::Renderer;

unsigned Screen::Screen_Width = 800;
unsigned Screen::Screen_Height = 600;
unsigned Screen::__Scale = 2;

std::vector<std::vector<Entity*>> Screen::__Entities;
Tileset* Screen::__Tileset = nullptr;


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

bool Screen::Add(Entity* ent)
{
	if (!ent) { std::cerr << "ERR Screen::Add : No entity supplied\n"; return false; }
	if (!ent->Get_Sprite()) { std::cerr << "ERR Screen::Add : Given entity has no sprite supplied\n"; return false; }

	while (ent->Get_Layer() >= Screen::__Entities.size())
		Screen::__Entities.push_back(std::vector<Entity*>());

	for (unsigned i = 0; i <= Screen::__Entities[ent->Get_Layer()].size(); i++)
	{
		if (i != Screen::__Entities[ent->Get_Layer()].size() && ent->Y > Screen::__Entities[ent->Get_Layer()][i]->Y) continue;
		Screen::__Entities[ent->Get_Layer()].insert(Screen::__Entities[ent->Get_Layer()].begin() + i, ent);
		break;
	}
	return true;
}

bool Screen::Add(Tileset * tileset)
{
	if (!tileset) { std::cerr << "ERR Screen::Add : No tileset supplied\n"; return false; }
	if (!tileset->Get_SDL_Texture()) { std::cerr << "ERR Screen::Add : Given tileset has no SDL_Texture supplied\n"; return false; }
	Screen::__Tileset = tileset;
	return true;
}

unsigned Screen::Draw()
{
	unsigned count = 0;
	if (__Tileset)
	{
		SDL_Rect src = { 0,0, (int)__Tileset->Get_Size().first, (int)__Tileset->Get_Size().second };
		SDL_Rect dst = { 
			(int)__Tileset->Get_Pos().first * (int)Screen::Get_Scale(),
			(int)__Tileset->Get_Pos().second * (int)Screen::Get_Scale(),
			(int)__Tileset->Get_Size().first * (int)Screen::Get_Scale(),
			(int)__Tileset->Get_Size().second * (int)Screen::Get_Scale()
		};
		SDL_RenderCopy(Screen::Renderer, __Tileset->Get_SDL_Texture(), &src, &dst);
	}
	for (auto layer : Screen::__Entities)
	{
		while (count < layer.size())
		{
			auto* sh = layer[count]->Get_Sprite();
			if (!sh)
			{
				std::cerr << "ERR Screen::Draw : Given Entity has no sprite supplied\n";
				return 0;
			}
			SDL_Rect frame_rect = {
				(int)sh->Get_Frame_Pos().first,
				(int)sh->Get_Frame_Pos().second,
				(int)sh->Get_Frame_Size().first,
				(int)sh->Get_Frame_Size().second,
			};
			SDL_Rect draw_rect = {
				(int)layer[count]->X - layer[count]->Get_Sprite()->Get_Texture()->Get_SDL_Starting_Point().x * (int)Screen::Get_Scale(),
				(int)layer[count]->Y - layer[count]->Get_Sprite()->Get_Texture()->Get_SDL_Starting_Point().y * (int)Screen::Get_Scale(),
				(int)sh->Get_Frame_Size().first * (int)Screen::Get_Scale(),
				(int)sh->Get_Frame_Size().second * (int)Screen::Get_Scale(),
			};
			auto sp = sh->Get_Texture()->Get_SDL_Starting_Point();
			sp.x *= Screen::Get_Scale();
			sp.y *= Screen::Get_Scale();
			SDL_RenderCopyEx
				(
					Screen::Renderer,
					sh->Get_SDL_Texture(),
					&frame_rect, &draw_rect,
					sh->Rotation,
					&sp,
					sh->Flip
					);
			count++;
		}
		count = 0;
	}
	SDL_RenderPresent(Screen::Renderer);
	SDL_RenderClear(Screen::Renderer);
	Screen::__Entities.clear();
	return count;
}

void Screen::Exit()
{
	Screen::__Entities.clear();
	SDL_DestroyRenderer(Screen::Renderer);
	SDL_DestroyWindow(Screen::Window);
}
