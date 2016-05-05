#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SDL.h>

class Sprite;
class Action;
class Hitbox;
class Stats;
class Texture;
class Movement;


//All your Entities should NOT override this class, deriver Entity class instead.
class Entity
{
public:
	//***  Virtual Create function, should be overriden by derivering entites
	virtual void Create();
	//***  Virtual Update function, should be overriden by derivering entites
	virtual void Update();
	//***  Virtual Events function, should be overriden by derivering entites
	virtual void Events();

	//*** Returns the Hitbox pointer if it exists
	std::pair<double, double> Get_Hitbox();

	//*** Returns the Sprite pointer if it exists
	virtual std::shared_ptr<Sprite> Get_Sprite();
	//*** Returns the Texture pointer if it exists
	virtual std::shared_ptr<Texture> Get_Texture();
	//*** Returns the scale of this entity
	virtual double Get_Scale();

	////*** Returns the Actions vector
	//virtual std::vector<std::shared_ptr<Action>> Get_Actions();

	////*** Returns the Stats pointer if it exists
	//Stats* Get_Stats();

	//*** Returns the Movement pointer if it exists
	Movement* Get_Movement();

	//*** X coordinate of this entity position
	double X = 0;
	//*** Y coordinate of this entity position
	double Y = 0;

protected:
	//*** A class responsible for Colisions and size of the entity
	//*** If nullptr, no colisions are handled
	std::shared_ptr<Hitbox> __Hitbox = nullptr;

	//*** A class containing all compounds needed for a sprite to be rendered
	//*** If nullptr, entity wont be displayed, but still can has usage (Actions)
	std::shared_ptr<Sprite> __Sprite = nullptr;

	//*** Container of all actions controling the movement, abilities and/or usage of this entity
	//*** If nullptr, entiti has no usage, but still can has sprite (Sprite)
	std::vector<std::shared_ptr<Action>> __Actions;

	//*** A class containing all statistics of the entity:
	//***    HP, MP, Str/Dex/Int/..., Passives, ect.
	//*** An entity doesn't have to has all the statistics;
	Stats* __Stats = nullptr;

	//*** A class containing all statistics of the entity:
	//***    HP, MP, Str/Dex/Int/..., Passives, ect.
	//*** An entity doesn't have to has all the statistics;
	std::shared_ptr<Movement> __Movement = nullptr;


	friend class Sprite;
	friend class Hitbox;
	friend class Movement;
	friend class State;
};


