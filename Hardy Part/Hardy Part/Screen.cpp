#include "Screen.h"
#include "Entity.h"
#include "State.h"
#include "Sprite.h"
#include "Texture.h"
#include "Generic.h"
#include "Textfield.h"
#include "Output_Handler.h"
#include "Camera.h"


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

//bool Screen::AddChild(Pointer<> ent)
//{
//	if (!ent) { Output_Handler::Error << "ERR Screen::AddChild : No entity supplied\n"; return false; }
//	//if (!ent->Display()) { Output_Handler::Output << "MSG Screen::AddChild : Given entity has no sprite supplied yet\n"; }
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

//bool Screen::AddChild(std::shared_ptr<Tileset> tileset, unsigned layer)
//{
//	if (!tileset) { Output_Handler::Error << "ERR Screen::AddChild : No tileset supplied\n"; return false; }
//	if (!tileset->Get_SDL_Texture()) { Output_Handler::Error << "ERR Screen::AddChild : Given tileset has no SDL_Texture supplied\n"; return false; }
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
		for (auto state : State::Built)
		{
			for(auto child : state->_layer_vector)
				__Draw(child.second, -Camera::Main->X, -Camera::Main->Y, Camera::Main->scale, Camera::Main->rotation);
		}
		SDL_RenderPresent(Screen::Renderer);
		SDL_RenderClear(Screen::Renderer);
	}
}

void Screen::Exit()
{
	SDL_DestroyRenderer(Screen::Renderer);
	SDL_DestroyWindow(Screen::Window);
}


bool Screen::__Draw(std::shared_ptr<Object> ent, double parent_x, double parent_y, double parent_scale, double parent_rotation)
{
	if (auto e = std::dynamic_pointer_cast<Container>(ent))
	{
		double x = ent->parent->Child_X(ent->X);
		double y = ent->parent->Child_Y(ent->Y);

		e->Reorder();
		for (auto child : e->children)
		{
			__Draw(child, parent_x + x, parent_y + y, parent_scale * ent->scale, parent_rotation + ent->rotation);
		}
	}
	if (auto e = std::dynamic_pointer_cast<Entity>(ent))
	{
		if (!e->texture) return false;
		e->texture->Draw(e,  parent_x, parent_y, parent_scale, parent_rotation);
	}
	return true;
}
