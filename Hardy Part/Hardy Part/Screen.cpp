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
bool Screen::__Windowed = true;

//std::vector<std::vector<Pointer<>>> Screen::__Entities;
//std::vector<std::vector<std::shared_ptr<Tileset>>> Screen::__Tilesets;

//template <typename T>
//T max(T v1, T v2)
//{
//	return v1 > v2 ? v1 : v2;
//}


std::pair<unsigned, unsigned> Screen::Window_Size()
{
	return std::make_pair(__Width, __Height);
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
		Screen::__Width = (unsigned)mode.w;
		Screen::__Height = (unsigned)mode.h;
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
	SDL_SetWindowFullscreen(Screen::Window, 0);
	__Windowed = true;
	return true;
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

//bool Screen::Add(Pointer<> ent)
//{
//	if (!ent) { Output_Handler::Error << "ERR Screen::Add : No entity supplied\n"; return false; }
//	//if (!ent->Display()) { Output_Handler::Output << "MSG Screen::Add : Given entity has no sprite supplied yet\n"; }
//	if (!Pointer<>::All.size()) return false;
//	for (auto it = Pointer<>::All.back().begin(); it != __Entities.back().end(); ++it)
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
		for (auto state : State::Built)
		{
			for(auto child : state->children)
				__Draw(child, 0, 0, 1, 0);
		}
		SDL_RenderPresent(Screen::Renderer);
	}
}

void Screen::Exit()
{
	SDL_DestroyRenderer(Screen::Renderer);
	SDL_DestroyWindow(Screen::Window);
}


bool Screen::__Draw(std::shared_ptr<Body> ent, double parent_x, double parent_y, double parent_scale, double parent_rotation)
{
	double x = ent->parent->Child_X(ent->X);
	double y = ent->parent->Child_Y(ent->Y);

	std::shared_ptr<Entity> en = std::dynamic_pointer_cast<Entity>(ent);

	if (auto e = std::dynamic_pointer_cast<Container>(ent))
	{
		e->Reorder();
		for (auto child : e->children)
		{
			__Draw(child, parent_x + x, parent_y + y, parent_scale * ent->scale, parent_rotation + ent->rotation);
		}
		if (!en || !en->texture || !en->texture->Get_SDL_Texture()) return true;
	}

	auto ttr = en->texture;
	if (!ttr || !ttr->Get_SDL_Texture())
	{
		Output_Handler::Error << "ERR Screen::Draw : Given Entity has no texture supplied\n";
		return false;
	}
	SDL_Texture* sdl_texture = ttr->Get_SDL_Texture();

	double px = (double)ttr->Starting_Point().x * ent->scale * parent_scale;
	double py = (double)ttr->Starting_Point().y * ent->scale * parent_scale;

	SDL_Point p = { (int)px, (int)py };


	SDL_Rect frame_rect;
	SDL_Rect draw_rect;
	SDL_RendererFlip flip;
	double rotation;

	frame_rect = ttr->Frame_Rect();
	draw_rect = ttr->Draw_Rect();
	draw_rect.x = (int)(((double)draw_rect.x * ent->scale + x) * parent_scale + parent_x);
	draw_rect.y = (int)(((double)draw_rect.y * ent->scale + y) * parent_scale + parent_y);
	draw_rect.w = (int)((double)draw_rect.w * parent_scale * ent->scale);
	draw_rect.h = (int)((double)draw_rect.h * parent_scale * ent->scale);

	flip = ttr->Flip;
	rotation = ent->rotation + parent_rotation;


	SDL_RenderCopyEx
	(
		Screen::Renderer,
		sdl_texture,
		&frame_rect, &draw_rect,
		rotation,
		&p,
		flip
	);
	return true;
}
