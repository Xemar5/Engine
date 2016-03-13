#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <memory>

class Movement
{
public:
	//*** Creates and initialises the movement class
	//*** - x/y - coordinates of the position of an entity
	//*** - mass - changes the way the entity accelerates/breaks and behave on different surfaces
	static Movement* Set(double& x, double& y, int mass);
	//*** Moves the entity in a given x and y direction
	//*** - force_x - how fast the entity goes in x dimension
	//*** - force_y - how fast the entity goes in y dimension
	//*** - traction - of the floor, in range from 0 (no traction) to 1 (default traction)
	static bool Move(Movement* movement, double force_x, double force_y, double traction = 1.0);
	//*** Returns the x-dimension velocity
	double Get_Velocity_X();
	//*** Returns the y-dimension velocity
	double Get_Velocity_Y();
private:
	//*** The mass of an entity
	//*** Changes the way it accelerates/breaks and bevahe in contact with other entities
	int __Mass = -1;
	//*** the x-dimension velocity
	double __vx = 0;
	//*** the y-dimension velocity
	double __vy = 0;
	//*** Reference to the enitity's x coordinate
	double* __X = nullptr;
	//*** Reference to the enitity's y coordinate
	double* __Y = nullptr;
	//*** The vector of all initialized movement classes
	static std::vector<std::shared_ptr<Movement>> __Movements;
};