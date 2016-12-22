#include "Screen.h"
#include "Entity.h"
#include "State.h"
#include "Sprite.h"
#include "Texture.h"
#include "Generic.h"
#include "Textfield.h"
#include "Output_Handler.h"


bool Screen::__Initialized = false;

bool Screen::ShowWindow = true;
SDL_Window* Screen::Window;
SDL_Renderer* Screen::Renderer;

unsigned Screen::__Width = 800;
unsigned Screen::__Height = 600;
double Screen::__Scale = 2;
bool Screen::__Windowed = true;

//std::vector<std::vector<ent::Entity<>>> Screen::__Entities;
//std::vector<std::vector<std::shared_ptr<Tileset>>> Screen::__Tilesets;

template <typename T>
T max(T v1, T v2)
{
	return v1 > v2 ? v1 : v2;
}


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
	return !Screen::Is_Windowed() ? Screen::Set_Windowed() : Screen::Set_Fullscreen();
}

bool Screen::Set_Fullscreen()
{
	if (!ShowWindow) return false;
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
	if (!ShowWindow) return false;
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
	if (!__Scale) return 1.0;
	return __Scale;
}


bool Screen::Init()
{
	if (Screen::__Initialized)
	{
		Output_Handler::Output << "MSG Screen::Start : Screen has already been initialized\n";
		return false;
	}
	Screen::__Initialized = true;
	if (!ShowWindow)
	{
		Output_Handler::Output << "MSG Screen::Start : Program run in console-only mode\n";
		return true;
	}
	Screen::Window = SDL_CreateWindow("Gmae", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen::__Width, Screen::__Height, SDL_WINDOW_SHOWN);
	Screen::Renderer = SDL_CreateRenderer(Screen::Window, -1, SDL_RENDERER_ACCELERATED);
	return true;
}

//bool Screen::Add(ent::Entity<> ent)
//{
//	if (!ent) { Output_Handler::Error << "ERR Screen::Add : No entity supplied\n"; return false; }
//	//if (!ent->Display()) { Output_Handler::Output << "MSG Screen::Add : Given entity has no sprite supplied yet\n"; }
//	if (!ent::Entity<>::All.size()) return false;
//	for (auto it = ent::Entity<>::All.back().begin(); it != __Entities.back().end(); ++it)
//	{
//		if (ent == *it) return false;
//		if (it->get()->layer < ent->layer) continue;
//		if (it->get()->Y < ent->Y) continue;
//		__Entities.back().insert(it, ent);
//		return true;
//	}
//	__Entities.back().push_back(ent);
//	return true;
//}

//bool Screen::Add(std::shared_ptr<Tileset> tileset, unsigned layer)
//{
//	if (!tileset) { Output_Handler::Error << "ERR Screen::Add : No tileset supplied\n"; return false; }
//	if (!tileset->Get_SDL_Texture()) { Output_Handler::Error << "ERR Screen::Add : Given tileset has no SDL_Texture supplied\n"; return false; }
//
//	if (layer >= Screen::__Tilesets.size())
//		Screen::__Tilesets.resize(layer + 1);
//
//	Screen::__Tilesets[layer].push_back(tileset);
//	return true;
//}



void Screen::Draw()
{
	if (ShowWindow)
	{
		SDL_RenderClear(Screen::Renderer);
		Screen::__Reorder();
		for (auto state : ent::Ordered)
		{
			for (auto layer : state.second)
			{
				for (auto ent : layer.second)
				{
					auto ttr = ent->texture;
					if (!ttr || !ttr->Get_SDL_Texture())
					{
						Output_Handler::Error << "ERR Screen::Draw : Given Entity has no texture supplied\n";
						continue;
					}
					SDL_Texture* sdl_texture = ttr->Get_SDL_Texture();

					double px = (double)ttr->Starting_Point().x * Screen::Get_Scale() * ttr->Scale;
					double py = (double)ttr->Starting_Point().y * Screen::Get_Scale() * ttr->Scale;

					SDL_Point p = { (int)px, (int)py };


					SDL_Rect frame_rect;
					SDL_Rect draw_rect;
					SDL_RendererFlip flip;
					double rotation;

					frame_rect = ttr->Frame_Rect();
					draw_rect = ttr->Draw_Rect();
					draw_rect.x = (int)(((double)draw_rect.x + ent->X) * Get_Scale());
					draw_rect.y = (int)(((double)draw_rect.y + ent->Y) * Get_Scale());
					draw_rect.w *= (int)Get_Scale();
					draw_rect.h *= (int)Get_Scale();

					flip = ttr->Flip;
					rotation = ttr->Rotation;


					SDL_RenderCopyEx
					(
						Screen::Renderer,
						sdl_texture,
						&frame_rect, &draw_rect,
						rotation,
						&p,
						flip
					);
				}
			}
		}
		SDL_RenderPresent(Screen::Renderer);
	}
}

void Screen::Exit()
{
	SDL_DestroyRenderer(Screen::Renderer);
	SDL_DestroyWindow(Screen::Window);
}

bool Screen::__Reorder()
{
	if (ent::Ordered.size()) return false;
	for (auto state : ent::Ordered)
	{
		for (auto layer : state.second)
		{
			for (unsigned i = 1; i < layer.second.size(); ++i)
			{
				auto temp = layer.second[i];
				int j = i - 1;
				while (j >= 0 && layer.second[j]->Y > temp->Y)
				{
					layer.second[j + 1] = layer.second[j];
					--j;
				}
				layer.second[j + 1] = temp;
			}
		}
	}
	//for (unsigned i = 1; i < ent::Ordered.back().size(); ++i)
	//{
	//	auto temp = __Entities.back()[i];
	//	int j = i - 1;
	//	while (j >= 0 && __Entities.back()[i]->layer < __Entities.back()[j]->layer)
	//	{
	//		__Entities.back()[j + 1] = __Entities.back()[j];
	//		--j;
	//	}
	//	__Entities.back()[j + 1] = temp;
	//}
	//for (unsigned i = 1; i < __Entities.back().size(); ++i)
	//{
	//	auto temp = __Entities.back()[i];
	//	int j = i - 1;
	//	while (j >= 0 && __Entities.back()[i]->layer == __Entities.back()[j]->layer && __Entities.back()[j]->Y > temp->Y)
	//	{
	//		__Entities.back()[j + 1] = __Entities.back()[j];
	//		--j;
	//	}
	//	__Entities.back()[j + 1] = temp;
	//}
	return true;
}
