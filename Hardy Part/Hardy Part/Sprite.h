#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SDL.h>
#include "Texture.h"
#include "Entity.h"

class Animation;
class Sprite;


class Sprite : public Texture
{
public:
	//*** Load new sprite from a path
	//*** - ent - the entity this sprite is supplied to; leave null if unused
	//*** - path - the path to the texture file
	//*** - width - of loading texture
	//*** - height - of loading texture
	//*** - frame_width - of loading texture; leave 0 to set to max; set to negative to devide texture into n segments
	//*** - frame_height - of loading texture; leave 0 to set to max; set to negative to devide texture into n segments
	//*** - starting_point_x - x of point where texture starts
	//*** - starting_point_y - y of point where texture starts
	//*** Adds a default "idle" animation
	//*** Returns pointer to it if created or already existing
	static std::shared_ptr<Texture> Load(Entity<> ent, std::string path, unsigned width, unsigned height, float starting_point_x = 0, float starting_point_y = 0, int frame_width = 0, int frame_height = 0);


	//*** Width of a frame, greater than 0 and less than Width of the image
	unsigned Frame_Width;
	//*** Height of a frame, greater than 0 and less than Height of the image
	unsigned Frame_Height;
	//*** Returns the max nuber of frames
	unsigned Max_Frames() { return (__Width / Frame_Width) * (__Height / Frame_Height); }

	//*** Returns the rectangle of the texture to draw
	SDL_Rect Frame_Rect() override;
	//*** Returns the rectangle of the texture to draw
	SDL_Rect Draw_Rect() override;
	//*** Returns pair of x and y of Sprite starting position in SDL_Point format
	SDL_Point Starting_Point() override;

	
	
	//*** Adds given animation to this Sprite
	//*** Does nothing if the name is already taken or sequence is empty
	static bool Add_Animation(std::shared_ptr<Texture> texture, Animation& anim);
	//*** Returns the animation with given name
	//*** If no name supplied or animation not found, returns "idle"
	Animation& operator[](std::string name);

	//*** Returns the current frame
	int Current_Frame() { return __Current_Animation ? __Current_Animation->Current_Frame() : -1; }
	//*** Returns the current animation
	Animation* Current_Animation() { return __Current_Animation; }

private:

	//*** Set of all animations of this Texture; USE WITH ANIMATION CLASS
	std::vector<Animation> __Animations;

	//*** Current animation that is being played on this Entity; USE WITH ANIMATION CLASS
	Animation* __Current_Animation = nullptr;

	friend class Animation;
	friend class State;
};



