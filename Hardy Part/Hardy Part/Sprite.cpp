#include "Sprite.h"
#include "Screen.h"
#include "Entity.h"
#include "Animation.h"

std::shared_ptr<Texture> Sprite::Load(Entity* ent, std::string path, unsigned width, unsigned height, float starting_point_x, float starting_point_y, int frame_width, int frame_height)
{
	if (!path.size())
	{
		Output_Handler::Error << "ERR Texture::Load : No path supplied\n";
		return false;
	}

	SDL_Texture* tr = nullptr;
	for (auto& ttr : Texture::__Textures)
		if (path == ttr->__Path)
		{
			tr = ttr->Get_SDL_Texture();
		}
	if (!tr) tr = IMG_LoadTexture(Screen::Renderer, path.c_str());

	if (!tr)
	{
		Output_Handler::Error << "ERR Texture::Load : No valid texture file supplied\n";
		return false;
	}

	Texture::__Textures.emplace_back(std::make_shared<Sprite>());
	Sprite* sp = dynamic_cast<Sprite*>(__Textures.back().get());
	sp->__Path = path;
	sp->__SDL_Texture = tr;

	if (frame_width == 0) sp->Frame_Width = width;
	else if (frame_width < 0) sp->Frame_Width = width / -frame_width;
	else sp->Frame_Width = frame_width;

	if (frame_height == 0) sp->Frame_Height = height;
	else if (frame_height < 0) sp->Frame_Height = height / -frame_height;
	else sp->Frame_Height = frame_height;

	Sprite::Add_Animation(sp, Animation("idle", "0", true));
	return Texture::__Load(ent, Texture::__Textures.back(), width, height, starting_point_x, starting_point_y);
}


SDL_Rect Sprite::Frame_Rect()
{
	SDL_Rect r;
	auto cf = Current_Frame();
	r.w = Frame_Width;
	r.h = Frame_Height;
	r.y = 0;
	r.x = cf * (int)Frame_Width;
	while (r.x >= (int)__Width)
	{
		r.x -= __Width;
		r.y += Frame_Height;
	}
	return r;
}

SDL_Rect Sprite::Draw_Rect()
{
	SDL_Rect r;
	r.x = -(int)((double)Starting_Point().x * Scale);
	r.y = -(int)((double)Starting_Point().y * Scale);
	r.w = (int)((double)Frame_Width * Scale);
	r.h = (int)((double)Frame_Height * Scale);
	return r;
}

SDL_Point Sprite::Starting_Point()
{
	if (!this)
	{
		Output_Handler::Error << "ERR Sprite::Starting_Point : No this Sprite\n";
		return{ 0,0 };
	}
	return
	{
		(int)((1.0 + __X_Off) / 2.0 * Frame_Width),
		(int)((1.0 + __Y_Off) / 2.0 * Frame_Height)
	};
}


bool Sprite::Add_Animation(Texture* texture, Animation& anim)
{
	if (!texture || !dynamic_cast<Sprite*>(texture))
	{
		Output_Handler::Output << "MSG Sprite::Add_Animation : No Sprite supplied\n";
		return false;
	}
	auto sp = dynamic_cast<Sprite*>(texture);
	if (!anim.Name().size()) return false;
	if (!anim.Sequence().size()) return false;
	for (auto& a : sp->__Animations)
		if (a.Name() == anim.Name()) return false;
	sp->__Animations.push_back(anim);
	sp->__Animations.back().__User = sp;
	return true;
}

Animation & Sprite::operator[](std::string name)
{
	if (!name.size()) return __Animations[0];
	for (auto& a : __Animations)
		if (a.Name() == name) return a;
	return __Animations[0];
}

