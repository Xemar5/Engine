#pragma once
#include <vector>
#include <SDL.h>

class Entity;
class Tileset;


class Screen
{
public:
	//*** SDL Window handler
	static SDL_Window* Window;
	//*** SDL Renderer handler
	static SDL_Renderer* Renderer;

	//*** Width of the window screen
	static unsigned Screen_Width;
	//*** Height of the window screen
	static unsigned Screen_Height;

	//*** Returns the scale of the whole screen
	static unsigned Get_Scale();


	//*** Initializes all the Screen compounds
	//*** Use only once at the start of the System
	static bool Start();

	//*** Adds the entity to screen renderer queue
	static bool Add(Entity* ent);

	//*** Adds the Tileset to screen renderer queue
	static bool Add(Tileset* tileset);

	//*** Draws the screen renderer to the screen
	//*** Use when all entities are added to the renderer
	//*** Clears Screen::__Sprites, Screen::__Entity_Pos and Screen::__Frame_Pos
	static unsigned Draw();

	//*** Call when exiting the program for a cleanup
	static void Exit();

private:
	//*** If true, prevents the user from additional, unnecessary initializations
	//*** Screen::Start should be called only once
	static bool __Initialized;

	static unsigned __Scale;

	//*** Where all the entities with supplied sprites are queued to be drawn on the screen the next frame update
	//*** It empties itself every frame update\
		//*** Each sub-vector represents a layer
	static std::vector<std::vector<Entity*>> __Entities;

	//*** A pointer to the Tileset which is to be drawn on the screen the next frame update
	//*** It empties itself every frame update
	static Tileset* __Tileset;

};