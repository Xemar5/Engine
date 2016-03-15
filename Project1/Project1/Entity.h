#pragma once
#include <iostream>
#include <string>

class Sprite;
class Actions;
class Hitbox;
class Stats;

//All your Entities should NOT override this class, deriver Entity class instead.
class Entity
{
public:
	//***  Virtual Create function, should be overriden by derivering entites
	virtual void Create() = 0;
	//***  Virtual Update function, should be overriden by derivering entites
	virtual void Update();
	//***  Virtual Events function, should be overriden by derivering entites
	virtual void Events() = 0;



	//*** X coordinate of this entity position
	double X = 0;
	//*** Y coordinate of this entity position
	double Y = 0;

private:
	//*** A class responsible for Colisions and size of the entity
	//*** If nullptr, no colisions are handled
	Hitbox* __Hitbox = nullptr;

	//*** A class containing all compounds needed for a sprite to be rendered
	//*** If nullptr, entity wont be displayed, but still can has usage (Actions)
	Sprite_Handler* __Sprite = nullptr;

	//*** A class controling the movement, abilities and/or usage of this entity
	//*** If nullptr, entiti has no usage, but still can has sprite (Sprite)
	Actions* __Actions = nullptr;

	//*** A class containing all statistics of the entity:
	//***    HP, MP, Str/Dex/Int/..., Passives, ect.
	//*** An entity doesn't have to has all the statistics;
	Stats* __Stats = nullptr;
};


