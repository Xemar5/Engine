#pragma once
#include <vector>
#include <memory>
#include <SDL.h>
#include "Texture.h"

class State;

class Generic : public Texture
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
	static std::shared_ptr<Texture> Load(std::vector<std::vector<int>> map, Entity<> ent, std::string path, unsigned width, unsigned height, float starting_point_x = 0, float starting_point_y = 0, int frame_width = 0, int frame_height = 0);

	//*** Reload current tileset and it's texture
	//*** Use when the tileset is not drawn properly
	bool Reload() override;

	//*** Returns the tile that contains the given coordinates
	static int Which_Tile(Entity<> ent, int x, int y);
	//unsigned Which_Tile(int x, int y);

	//*** Returns the visible SDL_Texture created by this Tileset class
	//*** Created when Set function is called
	SDL_Texture* Generic_Texture() { return __Generic_Texture; }


	//*** Width of a frame, greater than 0 and less than Width of the image
	unsigned Frame_Width;
	//*** Height of a frame, greater than 0 and less than Height of the image
	unsigned Frame_Height;
	//*** Returns the max number of different tiles in Sprite
	//*** Not all tiles needs to be filled; leave black if unused
	unsigned Tiles_Count() { return (__Generic_Width / Frame_Width) * (__Generic_Height / Frame_Height); }

	//*** Destroys given Generic class and allocates its resources
	bool Destroy() override;

private:

	//*** The visible  SDL_Texture of this tileset
	//*** Created when Set function is called
	SDL_Texture* __Generic_Texture = nullptr;
	//*** Width of the generic image
	unsigned __Generic_Width;
	//*** Height of the generic image
	unsigned __Generic_Height;
	//*** The matrix of this Tileset containing all tiles
	std::vector<std::vector<int>> __Tilemap;
};