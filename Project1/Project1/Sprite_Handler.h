#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SDL.h>

class Animation;
class Sprite;


class Sprite_Handler
{
public:
	//*** Creates new Sprite Handler and sets its Sprite
	//*** - sprite - can't be nullptr
	static Sprite_Handler* Create(Sprite* sprite);
	//*** Returns the sprite of this Sprite Handler
	Sprite* Get_Sprite();
	//*** Returns Texture stored in sprite of this Sprite Handler
	SDL_Texture* Get_Texture();
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
private:
	//*** Loaded sprite of this entity
	Sprite* __Sprite = nullptr;
	//*** The X coordinate of this entity frame position
	unsigned __Frame_Pos_X = 0;
	//*** The Y coordinate of this entity frame position
	unsigned __Frame_Pos_Y = 0;
	//*** Current animation that is being played on this Entity; USE WITH ANIMATION CLASS
	Animation* __Current_Animation = nullptr;
	//*** Current frame number in the animation's sequence; Equal to -1 when animation ended
	int __Sequence_Iterator = -1;

	//*** Set of sprite handlers of all entities
	static std::vector<std::shared_ptr<Sprite_Handler>> __Sprite_Handlers;

	friend class Animation;
};