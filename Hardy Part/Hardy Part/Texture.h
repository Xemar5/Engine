#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <string>
#include <vector>
#include "Output_Handler.h"
#include "Animation.h"
#include "Entity.h"

class Animation;
class Sprite_Handler;

class Texture
{
public:

	//*** Load new sprite from a path
	//*** - path - the path to the texture file
	//*** - width - of loading texture
	//*** - height - of loading texture
	//*** - frame_width - of loading texture; leave 0 to set to max; set to negative to devide texture into n segments
	//*** - frame_height - of loading texture; leave 0 to set to max; set to negative to devide texture into n segments
	//*** - starting_point_x - x of point where texture starts
	//*** - starting_point_y - y of point where texture starts
	//*** Adds a default "idle" animation
	//*** Returns pointer to it if created or already existing
	static std::shared_ptr<Texture> Load(std::shared_ptr<Entity> ent, std::string path, unsigned width, unsigned height, float starting_point_x = 0, float starting_point_y = 0);
	//*** Load new sprite from a path
	//*** - texture - an existing SDL_Texture that is not being used yet
	//*** - width - of loading texture
	//*** - height - of loading texture
	//*** - frame_width - of loading texture; leave 0 to set to max; set to negative to devide texture into n segments
	//*** - frame_height - of loading texture; leave 0 to set to max; set to negative to devide texture into n segments
	//*** - starting_point_x - x of point where texture starts
	//*** - starting_point_y - y of point where texture starts
	//*** Adds a default "idle" animation
	//*** Returns pointer to it if created or already existing
	static std::shared_ptr<Texture> Load(std::shared_ptr<Entity> ent, SDL_Texture* texture, unsigned width, unsigned height, float starting_point_x = 0, float starting_point_y = 0);

	//*** If true, SDL_Texture will be reloaded when exiting and re-entering the window
	bool Needs_Reloading = false;
	//*** Unloads a loaded SDL_Texture from this texture if created from __Path
	virtual bool Reload();



	//*** Returns the pair of Width and Height of the whole Texture
	std::pair<unsigned, unsigned> Size() { return{ __Width, __Height }; }
	//*** Sets the starting point to the given one
	//*** Choose numbers from -1 to 1
	bool Set_Starting_Pos(float x, float y);
	//*** Returns the offset of this texture
	//*** Two numbers from -1 to 1
	std::pair<float, float> Get_Starting_Pos() { return{ __X_Off, __Y_Off }; }

	//*** Returns the rectangle of the texture to draw
	virtual SDL_Rect Frame_Rect() { return{ 0, 0, (int)__Width, (int)__Height }; }
	//*** Returns the rectangle of the texture to draw
	virtual SDL_Rect Draw_Rect() { return{ -(int)(Starting_Point().x), -(int)(Starting_Point().y), (int)(__Width), (int)(__Height) }; }
	//*** Returns pair of x and y of Sprite starting position in SDL_Point format
	virtual SDL_Point Starting_Point();
	//*** Returns the SDL_Texture of sprite
	virtual SDL_Texture* Get_SDL_Texture() { return __SDL_Texture; }


	//*** Draws texture to teh screen
	virtual bool Draw(std::shared_ptr<Entity> ent, double parent_x, double parent_y, double parent_scale, double parent_rotation);


	//*** Horizontal or vertical flip of this sprite
	SDL_RendererFlip Flip = SDL_FLIP_NONE;
	////*** The angle in radians of this texture to be drawn
	////*** If set to 0, sprite will be displayed without rotation
	//double Rotation = 0;


	//*** Returns all loaded Textures in this session
	static std::vector<std::shared_ptr<Texture>> All() { return __Textures; }

	//*** Destroys given Texture class and allocates its resources
	virtual bool Destroy();

private:

	//*** Initializes supplied texture with given parameters
	static std::shared_ptr<Texture> __Load(std::shared_ptr<Entity> ent, std::shared_ptr<Texture> t, unsigned width, unsigned height, float starting_point_x = 0, float starting_point_y = 0);

	//*** Path to the image
	std::string __Path = "";

	//*** Width of the image
	unsigned __Width;
	//*** Height of the image
	unsigned __Height;


	//*** Values in range from -1 to 1 and inbetween
	//***  1 -> right
	//***  0 -> center
	//*** -1 -> left
	float __X_Off;

	//*** Values in range from -1 to 1 and inbetween
	//***  1 -> down
	//***  0 -> center
	//*** -1 -> up
	float __Y_Off;





	//***  The SDL texture of this Texture object
	SDL_Texture* __SDL_Texture;

	//*** All loaded Textures
	static std::vector<std::shared_ptr<Texture>> __Textures;

	friend class Animation;
	friend class Sprite;
	friend class Generic;
};