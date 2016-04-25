#include "Screen.h"
#include "Entity.h"
#include "State.h"
#include "Sprite.h"
#include "Texture.h"
#include "Tileset.h"


bool Screen::__Initialized = false;

SDL_Window* Screen::Window;
SDL_Renderer* Screen::Renderer;

unsigned Screen::__Width = 800;
unsigned Screen::__Height = 600;
double Screen::__Scale = 2;
bool Screen::__Windowed = true;

std::vector<std::vector<std::shared_ptr<Entity>>> Screen::__Entities;
std::vector<std::shared_ptr<Tileset>> Screen::__Tilesets;


std::pair<unsigned, unsigned> Screen::Get_Window_Size()
{
	return std::make_pair(__Width, __Height);
}

std::pair<unsigned, unsigned> Screen::Get_Screen_Size()
{
	if (!Screen::__Scale) return std::make_pair(Screen::__Width, Screen::__Height);
	return std::make_pair(Screen::__Width / Screen::__Scale, Screen::__Height / Screen::__Scale);
}

bool Screen::Is_Windowed()
{
	return __Windowed;
}

bool Screen::Change_Window_State()
{
	if (!Screen::Is_Windowed()) return Screen::Set_Windowed();
	return Screen::Set_Fullscreen();
}

bool Screen::Set_Fullscreen()
{
	SDL_DisplayMode mode;
	if (!SDL_GetCurrentDisplayMode(0, &mode))
	{
		//SDL_SetWindowSize(Screen::Window, mode.w, mode.h);
		//Screen::__Windowed_Width = Screen::Width;
		//Screen::__Windowed_Height = Screen::Height;
		Screen::__Width = mode.w;
		Screen::__Height = mode.h;
		Screen::__Scale = mode.w / 500;
		SDL_SetWindowFullscreen(Screen::Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		__Windowed = false;
		return true;
	}
	return false;
}

bool Screen::Set_Windowed()
{
	//SDL_SetWindowSize(Screen::Window, Screen::Width, Screen::Height);
	Screen::__Width = 800;
	Screen::__Height = 600;
	Screen::__Scale = 2;
	SDL_SetWindowFullscreen(Screen::Window, 0);
	__Windowed = true;
	return true;
}

double Screen::Get_Scale()
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
	Screen::Window = SDL_CreateWindow("Gmae", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen::__Width, Screen::__Height, SDL_WINDOW_SHOWN);
	Screen::Renderer = SDL_CreateRenderer(Screen::Window, -1, SDL_RENDERER_ACCELERATED);
	return true;
}


bool Screen::Add(std::shared_ptr<Entity> ent)
{
	if (!ent) { std::cerr << "ERR Screen::Add : No entity supplied\n"; return false; }
	if (!ent->Get_Sprite()) { std::cout << "MSG Screen::Add : Given entity has no sprite supplied yet\n"; }

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
	SDL_RenderClear(Screen::Renderer);

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
			tile->Get_Real_Pos().first * Get_Scale(),
			tile->Get_Real_Pos().second * Get_Scale(),
			//tile->Get_Pos().first - (double)(tile->Get_Texture()->Get_Starting_Point().first + 1) / 2 * tile->Get_Size().first,
			//tile->Get_Pos().second - (double)(tile->Get_Texture()->Get_Starting_Point().second + 1) / 2 * tile->Get_Size().second,
			(int)((double)tile->Get_Size().first * tile->Scale) * Get_Scale(),
			(int)((double)tile->Get_Size().second * tile->Scale) * Get_Scale()
		};
		SDL_RenderCopy(Screen::Renderer, tile->Get_SDL_Texture(), &src, &dst);
	}

	unsigned count = 0;
	Screen::__Reorder();
	for (unsigned layer = 0; layer < Screen::__Entities.size(); ++layer)
	{
		if (!Screen::__Entities[layer].size())
		{
			Screen::__Entities.erase(Screen::__Entities.begin() + layer);
			layer--;
			continue;
		}

		for (unsigned ent = 0; ent < Screen::__Entities[layer].size(); ++ent)
		{
			auto& e = Screen::__Entities[layer][ent];
			if (e.unique())
			{
				Screen::__Entities[layer].erase(Screen::__Entities[layer].begin() + ent);
				--ent;
				continue;
			}

			auto* spr = e->Get_Sprite().get();
			if (!spr)
			{
				std::cerr << "ERR Screen::Draw : Given Entity has no sprite supplied\n";
				return 0;
			}
			++count;

			double px = (double)spr->Get_Texture()->Get_SDL_Starting_Point().x * spr->Scale * Get_Scale();
			double py = (double)spr->Get_Texture()->Get_SDL_Starting_Point().y * spr->Scale * Get_Scale();

			SDL_Point p = { (int)px, (int)py };

			SDL_Rect frame_rect = {
				(int)spr->Get_Frame_Pos().first,
				(int)spr->Get_Frame_Pos().second,
				(int)spr->Get_Frame_Size().first,
				(int)spr->Get_Frame_Size().second,
			};
			SDL_Rect draw_rect = {
				(int)(e->X * Get_Scale() - px),
				(int)(e->Y * Get_Scale() - py),
				(int)((double)spr->Get_Frame_Size().first * spr->Scale) * Get_Scale(),
				(int)((double)spr->Get_Frame_Size().second * spr->Scale) * Get_Scale(),
			};

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
