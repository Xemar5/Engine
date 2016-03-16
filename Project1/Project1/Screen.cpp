#include "Screen.h"
#include "Sprite.h"
#include "Texture.h"

bool Screen::__Initialized = false;

SDL_Window* Screen::Window;
SDL_Renderer* Screen::Renderer;

unsigned Screen::Screen_Width = 200;
unsigned Screen::Screen_Height = 150;

std::vector<Sprite*> Screen::__Sprites;
std::vector<std::pair<double, double>> Screen::__Entity_Pos;


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

bool Screen::Add(Sprite* sprite, double x, double y)
{
	if (!sprite)
	{
		std::cerr << "ERR Screen::Add : No sprite supplied\n";
		return false;
	}
	Screen::__Sprites.push_back(sprite);
	Screen::__Entity_Pos.push_back(std::make_pair(x, y));
	return true;
}

unsigned Screen::Draw()
{
	unsigned count = 0;
	while (count < Screen::__Sprites.size())
	{
		auto* sh = Screen::__Sprites[count];
		SDL_Rect frame_rect = {
			(int)sh->Get_Frame_Pos().first,
			(int)sh->Get_Frame_Pos().second,
			(int)sh->Get_Frame_Size().first,
			(int)sh->Get_Frame_Size().second,
		};
		SDL_Rect draw_rect = {
			(int)Screen::__Entity_Pos[count].first,
			(int)Screen::__Entity_Pos[count].second,
			(int)sh->Get_Frame_Size().first * 3,
			(int)sh->Get_Frame_Size().second * 3,
		};
		SDL_RenderCopyEx(Screen::Renderer, sh->Get_SDL_Texture(), &frame_rect, &draw_rect, 0, NULL, sh->Flip);
		count++;
	}
	SDL_RenderPresent(Screen::Renderer);
	SDL_RenderClear(Screen::Renderer);
	Screen::__Sprites.clear();
	Screen::__Entity_Pos.clear();
	return count;
}

void Screen::Exit()
{
	Screen::__Sprites.clear();
	Screen::__Entity_Pos.clear();
	SDL_DestroyRenderer(Screen::Renderer);
	SDL_DestroyWindow(Screen::Window);
}
