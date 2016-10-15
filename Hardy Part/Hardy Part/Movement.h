#pragma once
#include <iostream>
#include <SDL.h>
#include <vector>
#include <memory>

#include "Action.h"

class Entity;



class Movement
{
public:
	//*** Creates and initialises the movement class
	//*** - x/y - coordinates of the position of an entity
	//*** - speed - how many pixels this entity moves by every frame
	//*** - mass - changes the way the entity accelerates/breaks and behave on different surfaces
	static std::shared_ptr<Movement> Set(double& x, double& y, double speed, double mass);
	//*** Creates and initialises the movement class
	//*** - ent - an entity movement class is being created for
	//*** - speed - how many pixels this entity moves by every frame
	//*** - mass - changes the way the entity accelerates/breaks and behave on different surfaces
	static std::shared_ptr<Movement> Set(Entity* ent, double speed, double mass);


	//*** Changes given Movement class' X and Y to a given x and y direction
	//*** - force_x - how fast the entity goes in x dimension
	//*** - force_y - how fast the entity goes in y dimension
	//*** - traction - of the floor, in range from 0 (no traction) to 1 (default traction)
	static bool Add_Force(Movement* movement, double force_x, double force_y);
	//*** Moves the entity in a given x and y direction
	//*** - force_x - how fast the entity goes in x dimension
	//*** - force_y - how fast the entity goes in y dimension
	//*** - traction - of the floor, in range from 0 (no traction) to 1 (default traction)
	static bool Add_Force(Entity* ent, double force_x, double force_y);


	//*** Returns the max speed
	double Get_Speed();
	//*** Returns the mass
	double Get_Mass();

	//*** Returns the x-dimension velocity
	double Get_Velocity_X();
	//*** Returns the y-dimension velocity
	double Get_Velocity_Y();

	//*** Sets the max speed of this Entity
	double Set_Speed(double speed);

private:
	//*** The max amount of pixels the entity is moving each frame
	//*** How fast the entity gets to that speed is defined by it's mass
	double __Speed = 0;
	//*** The mass of an entity
	//*** Changes the way it accelerates/breaks and bevahe in contact with other entities
	//*** - -1 - this entiti's mass is infinit, can't be moved
	//*** -  0 - no mass; no traction, can't start without an external force nor slow down on it's own
	//*** - >0 - the greater the mass te slower it accelerates and breaks
	double __Mass = -1;
	//*** the x-dimension velocity
	double __vx = 0;
	//*** the y-dimension velocity
	double __vy = 0;
	//*** Reference to the enitity's x coordinate
	double* __X = nullptr;
	//*** Reference to the enitity's y coordinate
	double* __Y = nullptr;
	//*** A container of all forces pushing the entity during this frame
	//*** Empties itself every frame
	std::vector<std::pair<double, double>> __Forces;
	//*** Moves the entity at the end of each frames
	static bool __Resolve_Movement(Movement* movement);
	//*** Moves the entity at the end of each frames
	static bool __Resolve_Movement(Entity* movement);

	friend class State;
};




