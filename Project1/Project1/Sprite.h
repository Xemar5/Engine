#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <string>
#include <vector>

//#include "System.h"
//#include "Animation.h"
class Animation;
class Sprite_Handler;

class Sprite
{
public:

	//*** Returns the pair of Width and Height of the whole texture
	std::pair<unsigned, unsigned> Get_Size();

	//*** Returns the size of a frame
	std::pair<unsigned, unsigned> Get_Frame_Size();

	//*** Sets the size of every frame
	//***  n>0                    - size of frame in pixels
	//***   0 OR n>_Width/_Height - sets to Sprite max _Width/_Height
	//***  n<0                    - devides the _Width/_Height into n segments
	std::pair<unsigned, unsigned> Set_Frame_Size(int width, int height);

	//*** Returns the max nuber of frames
	unsigned Max_Frames();

	//*** Returns pair of x and y of Sprite starting position
	std::pair<float, float> Get_Starting_Point();
	//*** Returns the texture of sprite
	SDL_Texture* Get_Texture();

	//*** Sets the Starting position of Sprite
	//***  - It is the point where the Sprites (0,0) point is located
	//***  - Choose numbers between -1 / 1
	std::pair<float, float> Set_Starting_Point(float x, float y);



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
	static Sprite* Load(std::string path, unsigned width, unsigned height, int frame_width = 0, int frame_height = 0, float starting_point_x = 0, float starting_point_y = 0);

	//*** Returns all loaded sprites in this session
	static std::vector<std::shared_ptr<Sprite>> Get_Loaded();

	//*** Destroys a sprite
	static bool Destroy(Sprite*);

	//*** Checks if a certain sprite from a path is loaded:
	//*** -1 if not loaded
	//*** it's possition in Sprite::__Loaded_Sprites if loaded
	static int Already_Loaded(std::string);

	//*** Returns the max number of frames
	unsigned Get_Frames_Number();
	//*** Returns the X and Y coordinates of the given frame, if it exists
	std::pair<unsigned, unsigned> Get_Frame_Pos(unsigned frame);
private:
	//*** Path to the image
	std::string __Path;

	//*** Width of the image
	unsigned __Width;
	//*** Height of the image
	unsigned __Height;


	//*** Width of a frame, greater than 0 and less than Width of the image
	unsigned __Frame_Width;
	//*** Height of a frame, greater than 0 and less than Height of the image
	unsigned __Frame_Height;

	//*** Set of all animations of this Sprite; USE WITH ANIMATION CLASS
	std::vector<std::shared_ptr<Animation>> __Animations;

	//*** Values in range from -1 to 1 and inbetween
	//***  1 -> right
	//***  0 -> center
	//*** -1 -> left
	float __Starting_Point_X;

	//*** Values in range from -1 to 1 and inbetween
	//***  1 -> down
	//***  0 -> center
	//*** -1 -> up
	float __Starting_Point_Y;



	//***  The texture of a sprite
	SDL_Texture* __Texture;

	//*** All loaded sprites
	static std::vector<std::shared_ptr<Sprite>> __Loaded;

	friend class Animation;
};