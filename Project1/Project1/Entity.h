#pragma once
#include <iostream>
#include <string>

class Sprite;
class Animation;
class Sprite_Handler;
class Movement;

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



	//*** Load new sprite from a path
	//*** - path - the path to the texture file
	//*** - width - of loading texture
	//*** - height - of loading texture
	//*** - frame_width - of loading texture; leave 0 to set to max; set to negative to devide texture into n segments
	//*** - frame_height - of loading texture; leave 0 to set to max; set to negative to devide texture into n segments
	//*** - starting_point_x - x of point where texture starts
	//*** - starting_point_y - y of point where texture starts
	//*** Also sets Sprite handler to the loaded sprite
	//*** Adds a default "idle" animation
	bool Load_Sprite(std::string path, unsigned width, unsigned height, int frame_width = 0, int frame_height = 0, float starting_point_x = 0, float starting_point_y = 0);

	//*** Adds an animation to sprite this entity uses
	//*** Select it's unique name and number and order of each frame
	//*** If the name is already taken, this function will replace it instead of making new
	//*** If another entity uses this sprite, it doesn't have to override existing animations
	//*** USE ONLY AFTER THE SPRITE IS LOADED
	Animation* Add_Animation(std::string name, std::string frame_sequence, bool repeat = false);
	//*** Sets the currently playing animation to the given one if it exists
	Animation* Play_Animation(std::string name);

	//*** Returns the sprite handler of this entity if it exists
	Sprite_Handler* Get_Sprite_Handler();
	//*** Returns the sprite of this entity if it exists
	Sprite* Get_Sprite();
	//*** Returns current frame based on the Sequence Iterator from Sprite Handler
	int Get_Current_Frame();




	//*** Creates a movement class for this entity
	//*** - mass - on this parameter depends how the entity will slide when accelerating or breaking
	//***    = 0 - the entity has no traction
	//***    =-1 - the entity is immovable (no Movement set also works like -1)
	//***    > 0 - the higher the mass, the faster the entity accelerates
	bool Set_Movement(int mass);
	//*** Changes the acceleration to force_x for X  and force_y  for Y
	//*** - traction - in range from 0 to 1, changes how fast the entite accelerates/breaks
	bool Move(double force_x, double force_y, double traction);
	//*** Returns the Movement class of this entity if it exists
	Movement* Get_Movement();

	//*** X coordinate of this entity position
	double X = 0;
	//*** Y coordinate of this entity position
	double Y = 0;

private:
	//*** A class containing all compounds needed for a sprite to be rendered
	//*** Use with Load Sprite function
	Sprite_Handler* __Sprite_Handler = nullptr;

	//*** A class controling the movement of this entity
	//*** If entity doesn't move, no need for implementing Movement class (leave nullptr)
	//*** Use with Create Movement function
	Movement* __Movement = nullptr;
};






////*** All your Entities should override this class, not Entity_Base.
//template <typename T>
//class Entity_Type : public Entity
//{
//public:
//	//*** Returns the type of this entity
//	static std::string Get_Type();
//
//private:
//#define SET_ENTITY_NAME(NAME) const std::string Entity<NAME>::__Type = #NAME
//	//Every entity must have it's own type
//	static const std::string __Type;
//};
//
//template<typename T>
//const std::string Entity<T>::__Type = "";
//
//
//template<typename T>
//std::string Entity<T>::Get_Type()
//{
//	if (!Entity<T>::__Type.size())
//	{
//		std::cerr << "ERR (Entity): Type of Entity not choosen.\n";
//	}
//	return Entity<T>::__Type;
//}

