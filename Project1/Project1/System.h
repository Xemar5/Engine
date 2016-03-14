#pragma once
#include <SDL.h>
#include <vector>
#include <memory>
//#include "State.h"

class Timer;



class System final
{
public:
	//*** Initialises the system with given State
	template <typename T>
	static void Start();

	//*** SDL Event handler
	static SDL_Event Events;
	//*** The timer that resets everytime the frame should be updated
	//*** Adjust the FPS to make it reset faster/slower
	static Timer FPS_Clock;
	//*** The approximate number of frames per second
	static unsigned FPS;
protected:

	//*** Main System loop, where all the states are updated
	static void _System_Update();
private:
	static void __Delete();
	static void __Update();
	static void __Events();
};

#include "Screen.h"

template <typename T>
void System::Start()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
	Screen::Start();
	State::New<T>();
	_System_Update();
}
