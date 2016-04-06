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

//bool Screen::Add(Entity* ent)
//{
//	if (!ent) { std::cerr << "ERR Screen::Add : No entity supplied\n"; return false; }
//	if (!ent->Get_Sprite()) { std::cerr << "ERR Screen::Add : Given entity has no sprite supplied\n"; return false; }
//
//	while (ent->Get_Layer() >= Screen::__Entities.size())
//		Screen::__Entities.push_back(std::vector<Entity*>());
//
//	for (unsigned i = 0; i <= Screen::__Entities[ent->Get_Layer()].size(); i++)
//	{
//		if (i != Screen::__Entities[ent->Get_Layer()].size() && ent->Y > Screen::__Entities[ent->Get_Layer()][i]->Y) continue;
//		Screen::__Entities[ent->Get_Layer()].insert(Screen::__Entities[ent->Get_Layer()].begin() + i, ent);
//		break;
//	}
//	return true;
//}

//bool Screen::Add(Tileset * tileset)
//{
//	if (!tileset) { std::cerr << "ERR Screen::Add : No tileset supplied\n"; return false; }
//	if (!tileset->Get_SDL_Texture()) { std::cerr << "ERR Screen::Add : Given tileset has no SDL_Texture supplied\n"; return false; }
//	Screen::__Tileset = tileset;
//	return true;
//}

unsigned Screen::Draw()
{
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

	unsigned count = 0;
	for (unsigned stt = 0; stt < State::Built.size(); ++stt)
	{
		for (unsigned layer = 0; layer < State::Built[stt]->Layers.size(); ++layer)
		{
			for (unsigned ent = 0; ent < State::Built[stt]->Layers[layer]->Entities.size(); ++ent)
			{
				auto& e = State::Built[stt]->Layers[layer]->Entities[ent];
				auto& l = State::Built[stt]->Layers[layer];
				auto* spr = e->Get_Sprite();
				if (!spr)
				{
					std::cerr << "ERR Screen::Draw : Given Entity has no sprite supplied\n";
					return 0;
				}
				SDL_Rect frame_rect = {
					(int)spr->Get_Frame_Pos().first,
					(int)spr->Get_Frame_Pos().second,
					(int)spr->Get_Frame_Size().first,
					(int)spr->Get_Frame_Size().second,
				};
				SDL_Rect draw_rect = {
					(int)e->X + l->X - e->Get_Sprite()->Get_Texture()->Get_SDL_Starting_Point().x * (int)Screen::Get_Scale(),
					(int)e->Y + l->Y - e->Get_Sprite()->Get_Texture()->Get_SDL_Starting_Point().y * (int)Screen::Get_Scale(),
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
