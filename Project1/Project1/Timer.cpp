#include "Timer.h"
#include <iostream>

Uint32 Timer::Start()
{
	if (__Started)
	{
		std::cout << "MSG Timer::Start : Timer already started\n";
		return 0;
	}
	__Paused = false;
	__Started = true;
	__Time_Before_Start = SDL_GetTicks();
	return __Time_Before_Start;
}

Uint32 Timer::Stop()
{
	if (!__Started)
	{
		std::cout << "MSG Timer::Stop : Timer not started, can't stop\n";
		return 0;
	}
	__Paused = false;
	__Started = false;
	auto t = SDL_GetTicks() - __Time_Before_Start - __Time_Paused;
	__Time_Before_Start = 0;
	__Time_Paused = 0;
	__Time = 0;
	return t;
}

Uint32 Timer::Restart()
{
	if (!__Started)
	{
		std::cout << "MSG Timer::Restart : Timer not started\n";
		return 0;
	}
	Stop();
	return Start();
}

Uint32 Timer::Pause()
{
	if (!__Started)
	{
		std::cout << "MSG Timer::Pause : Timer not started, can't pause\n";
		return 0;
	}
	if (__Paused)
	{
		std::cout << "MSG Timer::Pause : Timer already paused\n";
		return __Time_Paused = SDL_GetTicks() - __Time_Before_Start - __Time;
	}
	__Paused = true;
	__Time = SDL_GetTicks() - __Time_Before_Start - __Time_Paused;
	return __Time;
}

Uint32 Timer::Unpause()
{
	if (!__Started)
	{
		std::cout << "MSG Timer::Unpause : Timer not started, can't unpause\n";
		return 0;
	}
	if (!__Paused)
	{
		std::cout << "MSG Timer::Unpause : Timer not paused\n";
		return __Time = SDL_GetTicks() - __Time_Before_Start - __Time_Paused;
	}
	__Paused = false;
	__Time_Paused = SDL_GetTicks() - __Time_Before_Start - __Time;
	return __Time_Paused;
}

Uint32 Timer::Get()
{
	if (!__Started)
	{
		std::cout << "MSG Timer::Get : Timer not started, can't get the time\n";
		return 0;
	}
	if (!__Paused)
	{
		__Time = SDL_GetTicks() - __Time_Before_Start - __Time_Paused;
	}
	return __Time;
}

bool Timer::Is_Started()
{
	return __Started;
}

bool Timer::Is_Paused()
{
	return __Paused;
}

