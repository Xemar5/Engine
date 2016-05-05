#pragma once
#include <vector>
#include <memory>
#include <SDL.h>
#include "Entity.h"

class Texture;
class State;

class Tileset : public Entity
{
public:
	//*** Creates new tileset template
	//*** - texture - the texture containing all tiles used by this Tileset
	//*** - pos - the position of the top-left corner of this Tileset
	//*** - map - mapping of all tiles in this Tileset
	static std::shared_ptr<Tileset> Set(std::shared_ptr<Texture> texture, std::vector<std::vector<unsigned>> map);
	//*** Adds given tileset to spplied state and sets its properties
	//*** - state - the pointer to a state this is being added to
	//*** - tileset - pointer to an existing tileset
	//***			  use with Tileset::Set
	//*** - x, y - position of this tileset
	//*** - layer - the layer in state this tileset is being added to
	//*** - scale - the individual scale of this tileset
	static Tileset* Add(State* state, std::shared_ptr<Tileset> tileset, double x, double y, unsigned layer, double scale = 1);

	//*** Resets current tileset and it's texture
	//*** Use when the tileset is not drawn properly
	static bool Reset(std::shared_ptr<Tileset> tileset);
	//*** Resets current tileset and it's texture
	//*** Use when the tileset is not drawn properly
	static bool Reset(Tileset* tileset);

	//*** Returns the tile that contains the given coordinates
	unsigned Which_Tile(int x, int y);
	//*** Returns the center position of this Tileset
	//*** Use Get_Real_Pos to get the coordinate of the top-left corner

	//std::pair<int, int> Get_Pos();
	////*** Returns the top-left corner position of this Tileset
	////*** Use Get_Pos to get the position of center
	//std::pair<int, int> Get_Real_Pos();
	////*** Sets the x and y coordinates of this tileset to the given ones
	//bool Set_Pos(int x, int y);
	////*** Moves the tileset by x and y ammount of pixels
	//bool Set_Pos_Relative(int x, int y);

	//*** The individual scale of this tileset
	double Scale = 1;
	//*** Returns the scale of this tileset
	//*** Used for compatibility
	double Get_Scale() override;

	////*** Returns the size of whole Tilemap
	//std::pair<unsigned, unsigned> Get_Size();
	//*** Returns the texture containing tiles
	std::shared_ptr<Texture> Get_Texture() override;
	//*** Returns the visible SDL_Texture created by this Tileset class
	//*** Created when Set function is called
	std::shared_ptr<Texture> Get_Product_Texture();
	//*** Returns the max number of different tiles in Sprite
	//*** Not all tiles needs to be filled; leave black if unused
	unsigned Get_Tiles_Count();

	//*** Returns the container of all Wall Placeholders created in this Tileset
	//*** A Wall Placeholder is created when int 1 occurs in Tileset mapping
	std::vector<std::pair<int, int>> Get_Wall_Placeholders();

private:
	////*** The x and y coordinates of the top-left corner of this tileset
	//std::pair<int, int> __Pos;
	//*** The texture containing tiles
	std::shared_ptr<Texture> __Texture = nullptr;
	//*** The visible  SDL_Texture of this tileset
	//*** Created when Set function is called
	std::shared_ptr<Texture> __Product_Texture = nullptr;
	//*** The matrix of this Tileset containing all tiles
	std::vector<std::vector<unsigned>> __Tilemap;
	//*** The container of positions of all wall placeholders
	std::vector<std::pair<int, int>> __Wall_Placeholders;
};