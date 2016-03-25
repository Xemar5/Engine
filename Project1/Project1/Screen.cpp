#include "Screen.h"
#include "Entity.h"
#include "Sprite.h"
#include "Texture.h"

bool Screen::__Initialized = false;

SDL_Window* Screen::Window;
SDL_Renderer* Screen::Renderer;

unsigned Screen::Screen_Width = 800;
unsigned Screen::Screen_Height = 600;

std::vector<std::vector<Entity*>> Screen::__Entities;


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

unsigned Screen::Draw()
{
	unsigned count = 0;
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
				(int)layer[count]->X - layer[count]->Get_Sprite()->Get_Texture()->Get_SDL_Starting_Point().x * 3,
				(int)layer[count]->Y - layer[count]->Get_Sprite()->Get_Texture()->Get_SDL_Starting_Point().y * 3,
				(int)sh->Get_Frame_Size().first * 3,
				(int)sh->Get_Frame_Size().second * 3,
			};
			auto sp = sh->Get_Texture()->Get_SDL_Starting_Point();
			sp.x *= 3;
			sp.y *= 3;
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
