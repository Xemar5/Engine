#pragma once
#include <vector>
#include <memory>
#include <SDL.h>

class Texture;

class Tileset
{
public:
	//*** Sets and initializes the Tileset
	//*** - texture - the texture containing all tiles used by this Tileset
	//*** - pos - the position of the top-left corner of this Tileset
	//*** - map - mapping of all tiles in this Tileset
	static std::shared_ptr<Tileset> Set(Texture* texture, std::pair<int, int> pos, std::vector<std::vector<unsigned>> map);

	//*** Returns the tile that contains the given coordinates
	unsigned Which_Tile(int x, int y);
	//*** Returns the position of this Tileset
	std::pair<int, int> Get_Pos();
	//*** Sets the x and y coordinates of this tileset to the given ones
	bool Set_Pos(int x, int y);
	//*** Moves the tileset by x and y ammount of pixels
	bool Set_Pos_Relative(int x, int y);
	//*** Returns the size of whole Tilemap
	std::pair<unsigned, unsigned> Get_Size();
	//*** Returns the texture containing tiles
	Texture* Get_Texture();
	//*** Returns the visible SDL_Texture created by this Tileset class
	//*** Created when Set function is called
	SDL_Texture* Get_SDL_Texture();
	//*** Returns the max number of different tiles in Sprite
	//*** Not all tiles needs to be filled; leave black if unused
	unsigned Get_Tiles_Count();

	//*** Returns the container of all Wall Placeholders created in this Tileset
	//*** A Wall Placeholder is created when int 1 occurs in Tileset mapping
	std::vector<std::pair<int, int>> Get_Wall_Placeholders();

private:
	std::pair<int, int> __Pos;
	//*** The texture containing tiles
	Texture* __Texture = nullptr;
	//*** The visible  SDL_Texture of this tileset
	//*** Created when Set function is called
	SDL_Texture* __SDL_Texture = nullptr;
	//*** The matrix of this Tileset containing all tiles
	std::vector<std::vector<unsigned>> __Tilemap;
	//*** The container of positions of all wall placeholders
	std::vector<std::pair<int, int>> __Wall_Placeholders;
};