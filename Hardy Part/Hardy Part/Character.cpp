#include "Character.h"
#include "State.h"
#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Texture.h"
#include "Output_Handler.h"
#include "Sprite.h"
#include "Collider.h"

void Character::Create() {}
void Character::Update() {}
void Character::Events() {}

ent::Entity<> Character::Add(unsigned stt, std::string name, int x, int y, unsigned layer, double scale)
{
	if (name.size() == 0)
	{
		Output_Handler::Error << "ERR Character::Add : No name supplied\n";
		return nullptr;
	}
	if (stt > State::Built.size())
	{
		Output_Handler::Error << "ERR Character::Add : Given state no. exceeds max number of built states\n";
		return nullptr;
	}

	if (name == "Nerk")
	{
		auto ent = ent::Add<Character>(State::Built[stt], [layer, x, y, scale](auto ent)
		{
			ent->layer = layer;
			Sprite::Load(ent.get(), "imgs/nerk-sheet.png", 144, 24, 0, 1, 24, 24);
			Sprite::Add_Animation(ent->texture, Animation("idle", "0x80 1x5", true));
			Sprite::Add_Animation(ent->texture, Animation("move", "0x4 2-5x4", false));
			Movement::Set(ent.get(), 1.1, 0.1);
			Collider::Add(ent.get());
			ent->X = x;
			ent->Y = y;
			ent->texture->Scale = scale;
		});
		return ent;
	}

	else if (name == "Dreg")
	{
		auto ent = ent::Add<Character>(State::Built[stt], [layer, x, y, scale](auto ent)
		{
			ent->layer = layer;
			Sprite::Load(ent.get(), "imgs/dreg-sheet.png", 216, 24, 0, 1, 24, 24);
			Sprite::Add_Animation(ent->texture, Animation("idle", "0x63 1-3x5", true));
			Sprite::Add_Animation(ent->texture, Animation("move", "4-8x4", false));
			Movement::Set(ent.get(), 1.3, 10);
			Collider::Add(ent.get());
			ent->X = x;
			ent->Y = y;
			ent->texture->Scale = scale;
		});
		return ent;
	}

	else if (name == "Mosh")
	{
		auto ent = ent::Add<Character>(State::Built[stt], [layer, x, y, scale](auto ent)
		{
			ent->layer = layer;
			Sprite::Load(ent.get(), "imgs/mosh-sheet.png", 168, 24, 0, 1, 24, 24);
			Sprite::Add_Animation(ent->texture, Animation("idle", "0x70 1x3", true));
			Sprite::Add_Animation(ent->texture, Animation("move", "0x6 2-6x6", false));
			Movement::Set(ent.get(), 1.3, 10);
			Collider::Add(ent.get());
			ent->X = x;
			ent->Y = y;
			ent->texture->Scale = scale;
		});
		return ent;
	}

	else if (name == "Raiden")
	{
		auto ent = ent::Add<Character>(State::Built[stt], [layer, x, y, scale](auto ent)
		{
			ent->layer = layer;
			Sprite::Load(ent.get(), "imgs/raiden-sheet.png", 96, 24, 0, 1, 24, 24);
			Sprite::Add_Animation(ent->texture, Animation("idle", "0", true));
			Sprite::Add_Animation(ent->texture, Animation("move", "0-4x4", false));
			Movement::Set(ent.get(), 1.3, 10);
			Collider::Add(ent.get());
			ent->X = x;
			ent->Y = y;
			ent->texture->Scale = scale;
		});
		return ent;
	}

	else if (name == "Tar")
	{
		auto ent = ent::Add<Character>(State::Built[stt], [layer, x, y, scale](auto ent)
		{
			ent->layer = layer;
			Sprite::Load(ent.get(), "imgs/tar-sheet.png", 216, 24, 0, 1, 24, 24);
			Sprite::Add_Animation(ent->texture, Animation("idle", "0x85 1x5", true));
			Sprite::Add_Animation(ent->texture, Animation("move", "0x4 2-8x4", false));
			Movement::Set(ent.get(), 1.3, 40);
			Collider::Add(ent.get());
			ent->X = x;
			ent->Y = y;
			ent->texture->Scale = scale;
		});
		return ent;
	}

	else if (name == "Benio")
	{
		auto ent = ent::Add<Character>(State::Built[stt], [layer, x, y, scale](auto ent)
		{
			ent->layer = layer;
			Sprite::Load(ent.get(), "imgs/benio.png", 24, 24, 0, 1, 24, 24);
			Sprite::Add_Animation(ent->texture, Animation("idle", "0", true));
			Sprite::Add_Animation(ent->texture, Animation("move", "0", false));
			Movement::Set(ent.get(), 1.3, 10);
			Collider::Add(ent.get());
			ent->X = x;
			ent->Y = y;
			ent->texture->Scale = scale;
		});
		return ent;
	}

	Output_Handler::Error << "ERR Character::Add : No character with given name exists\n";
	return nullptr;
}

//void Character::RPC_Add(unsigned state, std::string name, int x, int y, unsigned layer, double scale)
//{
//	auto e = Add(state, name, x, y, layer, scale);
//	//e->networkID.Set();
//}

