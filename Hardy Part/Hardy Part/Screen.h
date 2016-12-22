#pragma once
#include <vector>
#include <memory>
#include <SDL.h>
#include "Entity.h"

class Tileset;


class Screen
{
public:
	//*** If false, only console output
	static bool ShowWindow;
	//*** SDL Window handler
	static SDL_Window* Window;
	//*** SDL Renderer handler
	static SDL_Renderer* Renderer;

	//*** Returns the size of the window
	//*** Use Get_Screen_Size if in-game screen size needed
	static std::pair<unsigned, unsigned> Get_Window_Size();
	//*** Returns the size of the of the screen
	//*** It scales with the Screen::__Scale
	//*** Use Get_Window_Size if the actual window size needed
	static std::pair<unsigned, unsigned> Get_Screen_Size();

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
	static double Get_Scale();


	//*** Initializes all the Screen compounds
	//*** Use only once at the start of the System
	static bool Init();

	////*** Adds the entity to screen renderer queue
	//static bool Add(Entity<> ent);

	////*** Adds the Tileset to screen renderer queue
	//static bool Add(std::shared_ptr<Tileset> tileset, unsigned layer);

	//*** Draws the screen renderer to the screen
	//*** Use when all entities are added to the renderer
	//*** Clears Screen::__Sprites, Screen::__Entity_Pos and Screen::__Frame_Pos
	static void Draw();

	//*** Call when exiting the program for a cleanup
	static void Exit();

private:
	//*** Width of the window screen
	static unsigned __Width;
	//*** Height of the window screen
	static unsigned __Height;

	//*** If true, prevents the user from additional, unnecessary initializations
	//*** Screen::Start should be called only once
	static bool __Initialized;
	
	//*** The global scale ratio of all displayed textures
	static double __Scale;

	//*** If true, the state of the window is set to windowed
	static bool __Windowed;

	//*** Reorders all entities stored in Screen::__Entities
	//*** The greater the Y value of an entity, the greater its index in __Entity
	//*** The greater the index, the later it's printed to the screen
	static bool __Reorder();

	////*** Where all the entities with supplied sprites are queued to be drawn on the screen the next frame update
	////*** It empties itself every frame update\
	////*** Each sub-vector represents a layer
	//static std::vector<std::vector<Entity<>>> __Entities;

	////*** A pointer to the Tileset which is to be drawn on the screen the next frame update
	////*** It empties itself every frame update
	//static std::vector<std::vector<std::shared_ptr<Tileset>>> __Tilesets;

	friend class State;
	template<typename T>
	friend class Entity;
};