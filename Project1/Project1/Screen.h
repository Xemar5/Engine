#pragma once
#include <vector>
#include <memory>
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
	static unsigned Width;
	//*** Height of the window screen
	static unsigned Height;

	//*** Returns true if the screen is windowed
	static bool Is_Windowed();
	//*** If __Windowed is set to True, this changes the window state to fullscreen
	//*** Otherwise changes to windowed
	static bool Change_Window_State();
	//*** Changes the current state of the window to fullscren
	//*** Returns false if the screen is already fullscreen
	static bool Set_Fullscreen();
	//*** Changes the current state of the window to windowed
	//*** Returns false if the screen is already windowed
	static bool Set_Windowed();

	//*** Returns the scale of the whole screen
	static unsigned Get_Scale();


	//*** Initializes all the Screen compounds
	//*** Use only once at the start of the System
	static bool Start();

	//*** Adds the entity to screen renderer queue
	static bool Add(std::shared_ptr<Entity> ent);

	//*** Adds the Tileset to screen renderer queue
	static bool Add(std::shared_ptr<Tileset> tileset);

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
	
	//*** The global scale ratio of all displayed textures
	static unsigned __Scale;

	//*** If true, the state of the window is set to windowed
	static bool __Windowed;

	//*** Reorders all entities stored in Screen::__Entities
	//*** The greater the Y value of an entity, the greater its index in __Entity
	//*** The greater the index, the later it's printed to the screen
	static bool __Reorder();

	//*** Where all the entities with supplied sprites are queued to be drawn on the screen the next frame update
	//*** It empties itself every frame update\
	//*** Each sub-vector represents a layer
	static std::vector<std::vector<std::shared_ptr<Entity>>> __Entities;

	//*** A pointer to the Tileset which is to be drawn on the screen the next frame update
	//*** It empties itself every frame update
	static std::vector<std::shared_ptr<Tileset>> __Tilesets;

};