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
	static std::pair<unsigned, unsigned> Window_Size();

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


	//*** Initializes all the Screen compounds
	//*** Use only once at the start of the System
	static bool Init();

	////*** Adds the entity to screen renderer queue
	//static bool AddChild(Pointer<> ent);

	////*** Adds the Tileset to screen renderer queue
	//static bool AddChild(std::shared_ptr<Tileset> tileset, unsigned layer);

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
	
	//*** If true, the state of the window is set to windowed
	static bool __Windowed;

	//*** Draws given Pointer on the Renderer
	//*** If the Pointer is of type Container, iterates throught every child
	static bool __Draw(std::shared_ptr<Object> ent, double parent_x, double parent_y, double parent_scale, double parent_rotation);

	////*** Where all the entities with supplied sprites are queued to be drawn on the screen the next frame update
	////*** It empties itself every frame update\
	////*** Each sub-vector represents a layer
	//static std::vector<std::vector<Pointer<>>> __Entities;

	////*** A pointer to the Tileset which is to be drawn on the screen the next frame update
	////*** It empties itself every frame update
	//static std::vector<std::vector<std::shared_ptr<Tileset>>> __Tilesets;

	friend class State;
	template<typename T>
	friend class Pointer;
};