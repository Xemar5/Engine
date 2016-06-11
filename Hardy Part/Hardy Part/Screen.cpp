#include "Screen.h"
#include "Entity.h"
#include "State.h"
#include "Sprite.h"
#include "Texture.h"
#include "Tileset.h"
#include "Textfield.h"
#include "Output_Handler.h"


bool Screen::__Initialized = false;

SDL_Window* Screen::Window;
SDL_Renderer* Screen::Renderer;

unsigned Screen::__Width = 800;
unsigned Screen::__Height = 600;
double Screen::__Scale = 2;
bool Screen::__Windowed = true;

std::vector<std::shared_ptr<Entity>> Screen::__Entities;
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
	Screen::Window = SDL_CreateWindow("Gmae", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen::__Width, Screen::__Height, SDL_WINDOW_SHOWN);
	Screen::Renderer = SDL_CreateRenderer(Screen::Window, -1, SDL_RENDERER_ACCELERATED);
	return true;
}


bool Screen::Add(std::shared_ptr<Entity> ent)
{
	if (!ent) { Output_Handler::Error << "ERR Screen::Add : No entity supplied\n"; return false; }
	if (!ent->Get_Sprite()) { Output_Handler::Output << "MSG Screen::Add : Given entity has no sprite supplied yet\n"; }

	for (auto it = __Entities.begin(); it != __Entities.end(); ++it)
	{
		if (it->get()->Get_Layer() < ent->Get_Layer()) continue;
		if (it->get()->Y < ent->Y) continue;
		__Entities.insert(it, ent);
		return true;
	}
	__Entities.push_back(ent);
	return true;
}

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
	SDL_RenderClear(Screen::Renderer);
	Screen::__Reorder();
	for (auto ent = __Entities.begin(); ent != __Entities.end(); ++ent)
	{
		if (ent->unique())
		{
			Entity::Destroy(ent->get());
			ent = Screen::__Entities.erase(ent);
			--ent;
			continue;
		}

		auto* ttr = ent->get()->Get_Texture().get();
		SDL_Texture* sdl_texture = ttr->Get_SDL_Texture();
		if (!ttr || !sdl_texture)
		{
			Output_Handler::Error << "ERR Screen::Draw : Given Entity has no texture supplied\n";
			continue;
		}

		double px = (double)ttr->Get_SDL_Starting_Point().x * ent->get()->Get_Scale() * Screen::Get_Scale();
		double py = (double)ttr->Get_SDL_Starting_Point().y * ent->get()->Get_Scale() * Screen::Get_Scale();

		SDL_Point p = { (int)px, (int)py };


		SDL_Rect frame_rect;
		SDL_Rect draw_rect;
		SDL_RendererFlip flip;
		double rotation;

		if (auto spr = ent->get()->Get_Sprite())
		{
			frame_rect = {
			(int)spr->Get_Frame_Pos().first,
			(int)spr->Get_Frame_Pos().second,
			(int)spr->Get_Frame_Size().first,
			(int)spr->Get_Frame_Size().second
			};
			draw_rect = {
				(int)(ent->get()->X * Screen::Get_Scale() - px),
				(int)(ent->get()->Y * Screen::Get_Scale() - py),
				(int)((double)spr->Get_Frame_Size().first * ent->get()->Get_Scale() * Screen::Get_Scale()),
				(int)((double)spr->Get_Frame_Size().second * ent->get()->Get_Scale() * Screen::Get_Scale())
			};
			flip = spr->Flip;
			rotation = spr->Rotation;
		}
		else
		{
			frame_rect = {
			0, 0,
			(int)ttr->Get_Size().first,
			(int)ttr->Get_Size().second
			};
			draw_rect = {
				(int)(ent->get()->X * Screen::Get_Scale() - px),
				(int)(ent->get()->Y * Screen::Get_Scale() - py),
				(int)((double)ttr->Get_Size().first * ent->get()->Get_Scale() * Screen::Get_Scale()),
				(int)((double)ttr->Get_Size().second * ent->get()->Get_Scale() * Screen::Get_Scale())
			};
			flip = SDL_FLIP_NONE;
			rotation = 0.0;
		}


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

	SDL_RenderPresent(Screen::Renderer);
}

void Screen::Exit()
{
	SDL_DestroyRenderer(Screen::Renderer);
	SDL_DestroyWindow(Screen::Window);
}

bool Screen::__Reorder()
{
	//for (unsigned layer = 0; layer < __Entities.size(); ++layer)
	//	for (unsigned i = 1; i < __Entities.size(); ++i)
	//	{
	//		auto temp = __Entities[i];
	//		int j = i - 1;
	//		while (j >= 0 && __Entities[layer][j]->Y > temp->Y)
	//		{
	//			__Entities[layer][j + 1] = __Entities[layer][j];
	//			--j;
	//		}
	//		__Entities[layer][j + 1] = temp;
	//	}
	//return true;
	if (__Entities.size() <= 1) return true;
	for (auto it = __Entities.begin() + 1; it != __Entities.end(); ++it)
	{
		auto temp = it;
		auto jt = it - 1;
		while (jt->get()->Get_Layer() == it->get()->Get_Layer() && jt->get()->Y > temp->get()->Y)
		{
			*(jt + 1) = *jt;
			if (jt == __Entities.begin()) break;
			--jt;
		}
		*(jt + 1) = *temp;
	}
	return true;
}

bool Screen::Change_Layer(Entity * ent)
{
	return false;
}
