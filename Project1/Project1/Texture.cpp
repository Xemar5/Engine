#include "Texture.h"
#include "Animation.h"
#include "System.h"
#include "Screen.h"

std::vector<std::shared_ptr<Texture>> Texture::__Loaded;


Texture* Texture::Load(std::string path, unsigned width, unsigned height, int frame_width, int frame_height, float starting_point_x, float starting_point_y)
{
	if (!path.size())
	{
		std::cerr << "ERR Texture::Load : No path supplied\n";
		return nullptr;
	}
	for (auto sprite : Texture::__Loaded) if (path == sprite->__Path)
	{
		std::cerr << "MSG Texture::Load : Texture already loaded, returning loaded version\n";
		return sprite.get();
	}
	SDL_Texture* tr = IMG_LoadTexture(Screen::Renderer, path.c_str());
	if (!tr)
	{
		std::cerr << "ERR Texture::Load : No valid texture file supplied\n";
		return nullptr;
	}
	Texture* texture = Texture::Load(tr, width, height, frame_width, frame_height, starting_point_x, starting_point_y);
	texture->__Path = path;
	return texture;
}

Texture * Texture::Load(SDL_Texture * texture, unsigned width, unsigned height, int frame_width, int frame_height, float starting_point_x, float starting_point_y)
{
	if (!texture)
	{
		std::cerr << "ERR Texture::Load : No SDL_Texture supplied\n";
		return nullptr;
	}
	Texture::__Loaded.emplace_back(std::make_shared<Texture>());
	Texture::__Loaded.back()->__Texture = texture;
	Texture::__Loaded.back()->__Width = width;
	Texture::__Loaded.back()->__Height = height;
	Texture::__Loaded.back()->Set_Starting_Point(starting_point_x, starting_point_y);
	Texture::__Loaded.back()->Set_Frame_Size(frame_width, frame_height);
	Animation::Add(Texture::__Loaded.back().get(), "idle", { 0 });
	return Texture::__Loaded.back().get();
}

inline std::vector<std::shared_ptr<Texture>> Texture::Get_Loaded()
{
	return Texture::__Loaded;
}

bool Texture::Destroy(Texture* sprite)
{
	if (!sprite)
	{
		std::cerr << "ERR Texture::Destroy_Sprite : No pointer to Texture supplied\n";
		return false;
	}
	if (int pos = Texture::Already_Loaded(sprite->__Path))
	{
		Texture::__Loaded.erase(Texture::__Loaded.begin() + pos);
		return true;
	}
	return false;
}

int Texture::Already_Loaded(std::string path)
{
	if (!path.size())
	{
		std::cerr << "ERR Texture::__Check_If_Sprite_Already_Loaded : No sprite path supplied\n";
		return -1;
	}
	for (unsigned i = 0; i < Texture::__Loaded.size(); i++)
		if (path == Texture::__Loaded[i]->__Path)
		{
			return i;
		}
	return -1;
}

unsigned Texture::Get_Frames_Number()
{
	unsigned x, y;
	x = (unsigned)floor(__Width / __Frame_Width);
	y = (unsigned)floor(__Height / __Frame_Height);
	return x*y;
}

std::pair<unsigned, unsigned> Texture::Get_Frame_Pos(unsigned frame)
{
	if (frame >= Get_Frames_Number())
	{
		std::cerr << "ERR Texture::Get_Frame_Pos : Given frame is greater than the max number of frames\n";
		return std::make_pair<unsigned, unsigned>(0, 0);
	}
	unsigned x, y = 0;
	x = frame * __Frame_Width;
	while (x >= __Width)
	{
		x -= __Width;
		y += __Frame_Height;
	}
	return std::make_pair(x,y);
}




std::pair<unsigned, unsigned> Texture::Get_Size()
{
	return std::make_pair(__Width, __Height);
}



std::pair<unsigned, unsigned> Texture::Get_Frame_Size()
{
	return std::make_pair(__Frame_Width, __Frame_Height);
}
std::pair<unsigned, unsigned> Texture::Set_Frame_Size(int w, int h)
{

	if (w < 0) w = __Width / -w;
	else if ((unsigned)w > __Width) { std::cout << "MSG Texture::Set_Frame_Size : Given Frame width is invalid; Setting to Texture Width\n"; w = __Width; }
	else if (w == 0)w = __Width;

	if (h < 0) h = __Height / -h;
	else if ((unsigned)h > __Height) { std::cout << "MSG Texture::Set_Frame_Size : Given Frame height is invalid; Setting to Texture Height\n"; h = __Height; }
	else if (h == 0)h = __Height;
	__Frame_Width = w;
	__Frame_Height = h;
	return std::make_pair(w, h);
}

unsigned Texture::Max_Frames()
{
	return (__Width / __Frame_Width) * (__Height / __Frame_Height);
}



std::pair<float, float> Texture::Get_Starting_Point()
{
	return std::make_pair(__Starting_Point_X, __Starting_Point_Y);
}
SDL_Point Texture::Get_SDL_Starting_Point()
{
	if (!this)
	{
		std::cerr << "ERR Texure::Get_SDL_Starting_Point : No this Texture\n";
		return { 0,0 };
	}
	return 
	{
		(int)((1.0 + __Starting_Point_X) / 2 * __Frame_Width) ,
		(int)((1.0 + __Starting_Point_Y) / 2 * __Frame_Height)
	};
}
SDL_Texture * Texture::Get_SDL_Texture()
{
	return this->__Texture;
}
std::pair<float, float> Texture::Set_Starting_Point(float x, float y)
{
	if (x > 1.0) { std::cout << "MSG Texture::Set_Starting_Point : Starting point x only in range from -1 to 1;\n"; }
	if (x < -1.0) { std::cout << "MSG Texture::Set_Starting_Point : Starting point x only in range from -1 to 1;\n"; }
	if (y > 1.0) { std::cout << "MSG Texture::Set_Starting_Point : Starting point y only in range from -1 to 1;\n"; }
	if (y < -1.0) { std::cout << "MSG Texture::Set_Starting_Point : Starting point y only in range from -1 to 1;\n"; }
	__Starting_Point_X = x;
	__Starting_Point_Y = y;
	return std::make_pair(x, y);
}
