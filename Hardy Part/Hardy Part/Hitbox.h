#pragma once
#include <memory>
#include <vector>
#include <iostream>

class Entity;

class Hitbox
{
public:
	//*** Creates and initializes the Hitbox class
	//*** Responsible for colision detection
	//*** - ent - can be nullptr; function will just return pointer
	static std::shared_ptr<Hitbox> Set(Entity* ent, unsigned width, unsigned height);

private:
	//*** If true, the object is considered when colisions are resolved
	bool __Is_Coliding = true;
	
	//*** The Hitbox rect Width
	//*** If 0, the object is not considered when colisions are resolved
	unsigned __Width = 0;
	//*** The Hitbox rect Height
	//*** If 0, the object is not considered when colisions are resolved
	unsigned __Height = 0;

	//*** Handles the way an object responses after colision with this one
	bool __Colision_Response();
};