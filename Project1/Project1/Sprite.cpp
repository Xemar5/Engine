#include "Sprite.h"
#include "Animation.h"
#include "System.h"
#include "Screen.h"

std::vector<std::shared_ptr<Sprite>> Sprite::__Loaded;


Sprite* Sprite::Load(std::string path, unsigned width, unsigned height, int frame_width, int frame_height, float starting_point_x, float starting_point_y)
{
	if (!path.size())
	{
		std::cerr << "ERR Sprite::Load : No path supplied\n";
		return nullptr;
	}
	for (auto sprite : Sprite::__Loaded) if (path == sprite->__Path)
	{
		std::cerr << "MSG Sprite::Load : Sprite already loaded, returning loaded version\n";
		return sprite.get();
	}
	Sprite::__Loaded.emplace_back(std::make_shared<Sprite>());
	Sprite::__Loaded.back()->__Texture = IMG_LoadTexture(Screen::Renderer, path.c_str());
	if (!Sprite::__Loaded.back()->__Texture)
	{
		std::cerr << "ERR Sprite::Load : No valid texture file supplied\n";
		Sprite::__Loaded.pop_back();
		return nullptr;
	}
	Sprite::__Loaded.back()->__Path = path;
	Sprite::__Loaded.back()->__Width = width;
	Sprite::__Loaded.back()->__Height = height;
	Sprite::__Loaded.back()->Set_Starting_Point(starting_point_x, starting_point_y);
	Sprite::__Loaded.back()->Set_Frame_Size(frame_width, frame_height);
	//Animation::Add(Sprite::__Loaded.back().get(), "default", { 0 });
	return Sprite::__Loaded.back().get();
}

inline std::vector<std::shared_ptr<Sprite>> Sprite::Get_Loaded()
{
	return Sprite::__Loaded;
}

bool Sprite::Destroy(Sprite* sprite)
{
	if (!sprite)
	{
		std::cerr << "ERR Sprite::Destroy_Sprite : No pointer to Sprite supplied\n";
		return false;
	}
	if (int pos = Sprite::Already_Loaded(sprite->__Path))
	{
		Sprite::__Loaded.erase(Sprite::__Loaded.begin() + pos);
		return true;
	}
	return false;
}

int Sprite::Already_Loaded(std::string path)
{
	if (!path.size())
	{
		std::cerr << "ERR Sprite::__Check_If_Sprite_Already_Loaded : No sprite path supplied\n";
		return -1;
	}
	for (unsigned i = 0; i < Sprite::__Loaded.size(); i++)
		if (path == Sprite::__Loaded[i]->__Path)
		{
			return i;
		}
	return -1;
}

unsigned Sprite::Get_Frames_Number()
{
	unsigned x, y;
	x = (unsigned)floor(__Width / __Frame_Width);
	y = (unsigned)floor(__Height / __Frame_Height);
	return x*y;
}

std::pair<unsigned, unsigned> Sprite::Get_Frame_Pos(unsigned frame)
{
	if (frame >= Get_Frames_Number())
	{
		std::cerr << "ERR Sprite::Get_Frame_Pos : Given frame is greater than the max number of frames\n";
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




std::pair<unsigned, unsigned> Sprite::Get_Size()
{
	return std::make_pair(__Width, __Height);
}



std::pair<unsigned, unsigned> Sprite::Get_Frame_Size()
{
	return std::make_pair(__Frame_Width, __Frame_Height);
}
std::pair<unsigned, unsigned> Sprite::Set_Frame_Size(int w, int h)
{

	if (w < 0) w = __Width / -w;
	else if ((unsigned)w > __Width) { std::cout << "MSG Sprite::Set_Frame_Size : Given Frame width is invalid; Setting to Texture Width\n"; w = __Width; }
	else if (w == 0)w = __Width;

	if (h < 0) h = __Height / -h;
	else if ((unsigned)h > __Height) { std::cout << "MSG Sprite::Set_Frame_Size : Given Frame height is invalid; Setting to Texture Height\n"; h = __Height; }
	else if (h == 0)h = __Height;
	__Frame_Width = w;
	__Frame_Height = h;
	return std::make_pair(w, h);
}

inline unsigned Sprite::Max_Frames()
{
	return (__Width / __Frame_Width) * (__Height / __Frame_Height);
}



inline std::pair<float, float> Sprite::Get_Starting_Point()
{
	return std::make_pair(__Starting_Point_X, __Starting_Point_Y);
}
SDL_Texture * Sprite::Get_Texture()
{
	return this->__Texture;
}
std::pair<float, float> Sprite::Set_Starting_Point(float x, float y)
{
	if (x > 1.0) { std::cout << "MSG Sprite::Set_Starting_Point : Starting point x only in range from -1 to 1; Setting to 1\n"; x = 1.0; }
	if (x < -1.0) { std::cout << "MSG Sprite::Set_Starting_Point : Starting point x only in range from -1 to 1; Setting to -1\n"; x = -1.0; }
	if (y > 1.0) { std::cout << "MSG Sprite::Set_Starting_Point : Starting point y only in range from -1 to 1; Setting to 1\n";  y = 1.0; }
	if (y < -1.0) { std::cout << "MSG Sprite::Set_Starting_Point : Starting point y only in range from -1 to 1; Setting to -1\n"; y = -1.0; }
	__Starting_Point_X = x;
	__Starting_Point_Y = y;
	return std::make_pair(x, y);
}
