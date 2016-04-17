#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SDL.h>

class Animation;
class Texture;
class Entity;


class Sprite
{
public:
	//*** Creates new Sprite Handler and sets its Sprite
	//*** - ent - the entity this sprite will be given to; leave nullptr if no entity wanted
	//*** - texture - a pointer to an existing texture class; can't be nullptr
	static Sprite* Create(Entity* ent, std::shared_ptr<Texture> texture);
	//*** Returns the sprite of this Sprite Handler
	std::shared_ptr<Texture> Get_Texture();
	//*** Returns SDL_Texture stored in Texture of this Sprite
	SDL_Texture* Get_SDL_Texture();
	//*** Returns the size of a frame in the sprite stored in this Sprite Handler
	std::pair<unsigned, unsigned> Get_Frame_Size();
	//*** Returns the position of current frame in the sprite stored in this Sprite Handler
	std::pair<unsigned, unsigned> Get_Frame_Pos();
	//*** Returns the current frame
	int Get_Current_Frame();
	//*** Returns the current animation
	Animation* Get_Current_Animation();
	//*** Horizontal or vertical flip of this sprite
	SDL_RendererFlip Flip;
	//*** The angle in radians of this entity to be drawn
	//*** If set to 0, sprite will be displayed without rotation
	double Rotation = 0;
private:
	//*** Loaded Texture of this entity
	std::shared_ptr<Texture> __Texture = nullptr;
	//*** The X coordinate of this entity frame position
	unsigned __Frame_Pos_X = 0;
	//*** The Y coordinate of this entity frame position
	unsigned __Frame_Pos_Y = 0;
	//*** Current animation that is being played on this Entity; USE WITH ANIMATION CLASS
	Animation* __Current_Animation = nullptr;
	//*** Current frame number in the animation's sequence; Equal to -1 when animation ended
	int __Sequence_Iterator = -1;

	//*** Set of sprite handlers of all entities
	static std::vector<std::shared_ptr<Sprite>> __Sprites;

	friend class Animation;
};