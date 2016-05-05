#include "Mouse_Handler.h"
#include <iostream>
#include "System.h"
#include "Entity.h"
#include "Sprite.h"
#include "Texture.h"

std::map<Sint32, int> Mouse_Handler::__Map;

double Mouse_Handler::Button_Down(std::vector<Sint32> args)
{
	auto it = args.begin();
	if (it == args.end()) { std::cerr << "ERR Mouse_Handler::Button_Down : Button not supplied\n"; return 0.0; }
	Sint32 btn = (Sint32)*it;
	for (std::map<Sint32, int>::iterator it = Mouse_Handler::__Map.begin(); it != Mouse_Handler::__Map.end(); it++)
		if (it->first == btn && it->second == -2)
			return 1.0;
	return 0.0;
}

double Mouse_Handler::Button_Up(std::vector<Sint32> args)
{
	auto it = args.begin();
	if (it == args.end()) { std::cerr << "ERR Mouse_Handler::Button_Up : Button not supplied\n"; return 0.0; }
	Sint32 btn = (Sint32)*it;

	for (std::map<Sint32, int>::iterator it = Mouse_Handler::__Map.begin(); it != Mouse_Handler::__Map.end(); it++)
		if (it->first == btn && it->second == -1)
			return 1.0;
	return 0.0;
}

double Mouse_Handler::Button_Held(std::vector<Sint32> args)
{
	auto it = args.begin();
	if (it == args.end()) { std::cerr << "ERR Mouse_Handler::Button_Held : Button not supplied\n"; return 0.0; }
	Sint32 btn = (Sint32)*it++;

	Sint32 time;
	if (it == args.end()) time = 0;
	else time = (Sint32)*it;

	for (std::map<Sint32, int>::iterator it = Mouse_Handler::__Map.begin(); it != Mouse_Handler::__Map.end(); it++)
		if (it->first == btn && it->second >= 0 && SDL_GetTicks() - it->second >= (Uint32)time)
			return 1.0;
	return 0.0;
}

std::pair<int, int> Mouse_Handler::Get_Mouse_Pos()
{
	
	int x, y;
	SDL_GetMouseState(&x, &y);
	x = (int)((double)x / Screen::Get_Scale());
	y = (int)((double)y / Screen::Get_Scale());

	return std::make_pair(x,y);
}

double Mouse_Handler::Get_Relative_Mouse_X_State(std::vector<Sint32> args)
{
	auto it = args.begin();
	if (it == args.end()) { std::cerr << "ERR Mouse_Handler::Get_Relative_Mouse_X_State : X coordinate not supplied\n"; return 0.0; }
	Sint32 x = (Sint32)*it++;
	if (it == args.end()) { std::cerr << "ERR Mouse_Handler::Get_Relative_Mouse_X_State : Y coordinate not supplied\n"; return 0.0; }
	Sint32 y = (Sint32)*it;

	x *= (Sint32)Screen::Get_Scale();
	y *= (Sint32)Screen::Get_Scale();

	Sint32 mx, my;
	SDL_GetMouseState(&mx, &my);

	return cos(atan2(my - y, mx - x));
}



double Mouse_Handler::Get_Relative_Mouse_Y_State(std::vector<Sint32> args)
{
	auto it = args.begin();
	if (it == args.end()) { std::cerr << "ERR Mouse_Handler::Get_Relative_Mouse_Y_State : X coordinate not supplied\n"; return 0.0; }
	Sint32 x = (Sint32)*it++;
	if (it == args.end()) { std::cerr << "ERR Mouse_Handler::Get_Relative_Mouse_Y_State : Y coordinate not supplied\n"; return 0.0; }
	Sint32 y = (Sint32)*it;

	x *= (Sint32)Screen::Get_Scale();
	y *= (Sint32)Screen::Get_Scale();

	Sint32 mx, my;
	SDL_GetMouseState(&mx, &my);

	return sin(atan2(my - y, mx - x));
}


bool Mouse_Handler::Contains_Mouse(Entity* ent)
{
	if (!ent)
	{
		std::cerr << "ERR Entity::Contains_Mouse : No entity supplied\n";
		return false;
	}
	if (!ent->Get_Sprite())
	{
		std::cerr << "ERR Entity::Contains_Mouse : Given entity has no sprite supplied\n";
		return false;
	}
	if (!ent->Get_Sprite()->Get_Texture())
	{
		std::cerr << "ERR Entity::Contains_Mouse : Given sprite has no texture supplied\n";
		return false;
	}
	int px = Mouse_Handler::Get_Mouse_Pos().first;
	int py = Mouse_Handler::Get_Mouse_Pos().second;
	auto sp = ent->Get_Sprite();
	double offx = sp->Get_Texture()->Get_SDL_Starting_Point().x * sp->Scale;
	double offy = sp->Get_Texture()->Get_SDL_Starting_Point().y * sp->Scale;
	return (
		px >= ent->X - offx &&
		px <= ent->X - offx + ent->Get_Hitbox().first &&
		py >= ent->Y - offy &&
		py <= ent->Y - offy + ent->Get_Hitbox().second
		);
}

void Mouse_Handler::__Events()
{
	if (System::Events.type == SDL_MOUSEBUTTONDOWN)
		Mouse_Handler::__Map.insert(std::make_pair(System::Events.button.button, -2));
	if (System::Events.type == SDL_MOUSEBUTTONUP)
		for (std::map<Sint32, int>::iterator it = Mouse_Handler::__Map.begin(); it != Mouse_Handler::__Map.end(); it++)
			if (it->first == System::Events.button.button)
				it->second = -1;
}

void Mouse_Handler::__Update()
{
	for (std::map<Sint32, int>::iterator it = Mouse_Handler::__Map.begin(); it != Mouse_Handler::__Map.end();)
	{
		if (it->second == -1)
		{
			auto temp = it;
			++it;
			Mouse_Handler::__Map.erase(temp);
		}
		else if (it->second == -2)
		{
			it->second = SDL_GetTicks();
			++it;
		}
		else ++it;
	}
}
