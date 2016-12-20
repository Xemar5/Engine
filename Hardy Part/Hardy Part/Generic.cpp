#include "Generic.h"
#include "Texture.h"
#include "Screen.h"


std::shared_ptr<Texture> Generic::Load(std::vector<std::vector<int>> map, Entity<> ent, std::string path, unsigned width, unsigned height, float starting_point_x, float starting_point_y, int frame_width, int frame_height)
{
	if (!path.size())
	{
		Output_Handler::Error << "ERR Generic::Load : No path supplied\n";
		return nullptr;
	}
	if (!map.size() || !map[0].size())
	{
		Output_Handler::Error << "ERR Generic::Set : Given map has width/height equal to 0\n";
		return nullptr;
	}

	SDL_Texture* gt = nullptr;
	for (auto& ttr : Texture::__Textures) if (path == ttr->__Path && dynamic_cast<Generic*>(ttr.get()))
	{
		gt = dynamic_cast<Generic*>(ttr.get())->__Generic_Texture;
		break;
	}
	if (!gt) gt = IMG_LoadTexture(Screen::Renderer, path.c_str());
	if (!gt)
	{
		Output_Handler::Error << "ERR Texture::Load : No valid texture file supplied\n";
		return nullptr;
	}

	auto texture = SDL_CreateTexture
		(
		Screen::Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		frame_width * map[0].size(),
		frame_height * map.size()
		);
	if (!texture)
	{
		Output_Handler::Error << "ERR Texture::Load : Couldn't create SDL_Texture (probably size is too big)\n";
		SDL_DestroyTexture(gt);
		return nullptr;
	}

	Texture::__Textures.emplace_back(std::make_shared<Generic>());
	Texture::__Load(ent, Texture::__Textures.back(), frame_width * map[0].size(), frame_height * map.size(), starting_point_x, starting_point_y);
	std::shared_ptr<Generic> ts = std::static_pointer_cast<Generic>(Texture::__Textures.back());



	ts->__Generic_Texture = gt;
	ts->__Generic_Width = width;
	ts->__Generic_Height = height;
	ts->__Width = frame_width * map[0].size();
	ts->__Height = frame_height * map.size();
	ts->__SDL_Texture = texture;
	ts->__Tilemap = map;
	ts->__Path = path;

	if (frame_width == 0) ts->Frame_Width = width;
	else if (frame_width < 0) ts->Frame_Width = width / -frame_width;
	else ts->Frame_Width = frame_width;

	if (frame_height == 0) ts->Frame_Height = height;
	else if (frame_height < 0) ts->Frame_Height = height / -frame_height;
	else ts->Frame_Height = frame_height;

	if (ent) ent->texture = Texture::__Textures.back();


	SDL_SetTextureBlendMode(ts->__SDL_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Screen::Renderer, ts->__SDL_Texture);


	SDL_Rect src = { 0,0, (int)frame_width, (int)frame_height };
	SDL_Rect dst = { 0,0, (int)frame_width, (int)frame_height };

	auto get_frame_pos = [&ts](int frame)->std::pair<int, int>
	{
		if (frame < 0) return std::pair<int, int>( frame, frame );
		std::pair<int, int> p;
		p.second = 0;
		p.first = frame * (int)ts->Frame_Width;
		while (p.first >= (int)ts->__Generic_Width)
		{
			p.first -= ts->__Generic_Width;
			p.second += ts->Frame_Height;
		}
		return p;
	};

	SDL_RenderClear(Screen::Renderer);
	for (unsigned i = 0; i < map.size(); i++)
	{
		for (unsigned j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] < (int)ts->Tiles_Count())
			{
				auto frame_pos = get_frame_pos(map[i][j]);
				src.x = frame_pos.first;
				src.y = frame_pos.second;
			}
			else
			{
				Output_Handler::Output << "MSG Generic::Set : Tile " << map[i][j] << " doesn't exist (max " << ts->Tiles_Count() - 1 << "); no tile is drawn\n";
				src.x = 0;
				src.y = 0;
			}
			if(src.x >= 0 && src.y >= 0)
				SDL_RenderCopy(Screen::Renderer, ts->__Generic_Texture, &src, &dst);
			dst.x += frame_width;
		}
		dst.y += frame_height;
		dst.x = 0;
	}

	//ent->__Type = ET_Generic;
	SDL_SetRenderTarget(Screen::Renderer, NULL);
	return Texture::__Textures.back();
}

bool Generic::Reload()
{
	if (!__Path.size()) return false;

	if (__SDL_Texture) SDL_DestroyTexture(__SDL_Texture);
	if (__Generic_Texture) SDL_DestroyTexture(__Generic_Texture);
	__SDL_Texture = nullptr;
	__Generic_Texture = nullptr;
	*this = *std::dynamic_pointer_cast<Generic>(Load(__Tilemap, nullptr, __Path, __Width, __Height, __X_Off, __Y_Off, Frame_Width, Frame_Height));

	return true;
}

//unsigned Generic::Which_Tile(int x, int y)
//{
//	if (!this) { Output_Handler::Error << "ERR Generic::Which_Tile : No this Generic\n"; return -1; }
//	if (!Frame_Width || !Frame_Height) { Output_Handler::Error << "ERR Generic::Which_Tile : Frame size has width/height equal to 0\n"; return -1; }
//
//	x /= Frame_Width;
//	y /= Frame_Height;
//
//	if (x < 0 || x >= (int)__Width / (int)Frame_Width ||
//		y < 0 || y >= (int)__Height / (int)Frame_Height)
//	{
//		return -1;
//	}
//	return __Tilemap[y][x];
//}

int Generic::Which_Tile(Entity<> ent, int x, int y)
{
	if (!ent) { Output_Handler::Error << "ERR Generic::Which_Tile : No Entity supplied\n"; return -1; }
	if (!ent->texture) { Output_Handler::Error << "ERR Generic::Which_Tile : Supplied Entity has no Texture\n"; return -1; }
	if (!std::dynamic_pointer_cast<Generic>(ent->texture)) { Output_Handler::Error << "ERR Generic::Which_Tile : Supplied Entity has no Generic type Texture\n"; return -1; }

	auto gt = std::dynamic_pointer_cast<Generic>(ent->texture);
	if (!gt->Frame_Width || !gt->Frame_Height) { Output_Handler::Error << "ERR Generic::Which_Tile : Frame size has width/height equal to 0\n"; return -1; }

	x -= gt->Draw_Rect().x + (int)ent->X;
	y -= gt->Draw_Rect().y + (int)ent->Y;

	x = (int)((double)x / (double)gt->Frame_Width / gt->Scale);
	y = (int)((double)y / (double)gt->Frame_Height / gt->Scale);

	if (x < 0 || x >= (int)gt->__Width / (int)gt->Frame_Width ||
		y < 0 || y >= (int)gt->__Height / (int)gt->Frame_Height)
	{
		return -1;
	}
	return gt->__Tilemap[y][x];
}


bool Generic::Destroy()
{
	if (__Generic_Texture)
	{
		for (auto& ttr : __Textures)
			if (auto cast = std::dynamic_pointer_cast<Generic>(ttr))
				if (cast.get() != this && cast->__Generic_Texture == __Generic_Texture)
					return Texture::Destroy();
		SDL_DestroyTexture(__Generic_Texture);
		__Generic_Texture = nullptr;
	}
	return Texture::Destroy();
}
