#pragma once
#include <vector>
#include <SDL.h>

class Entity;


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


	//*** Initializes all the Screen compounds
	//*** Use only once at the start of the System
	static bool Start();

	//*** Adds the sprite to screen renderer and places it in target position
	//*** If there are more than one entity using particular sprite, all of them
	//    should add their own sprite even though they are all the same
	//*** - x - the X coordinate of where the entity should be placed
	//*** - y - the Y coordinate of where the entity should be placed
	//*** - frame_x - the X coordinate of frame
	//*** - frame_y - the Y coordinate of frame
	static bool Add(Entity* ent);

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

	//*** Where all the entities with supplied sprites are queued to be drawn on the screen the next frame update
	//*** It empties itself every frame update
	static std::vector<Entity*> __Entities;

};