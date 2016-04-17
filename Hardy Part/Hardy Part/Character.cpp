#include "Character.h"
#include "State.h"
#include "Sprite.h"
#include "Animation.h"
#include "Movement.h"
#include "Texture.h"
#include <iostream>

void Character::Create() {}
void Character::Update() {}
void Character::Events() {}

Character * Character::Add(State* stt, std::string name, int x, int y, unsigned layer)
{
	if (name.size() == 0)
	{
		std::cerr << "ERR Character::Add : No name supplied\n";
		return nullptr;
	}
	if (!stt)
	{
		std::cerr << "ERR Character::Add : No state supplied\n";
		return nullptr;
	}

	if (name == "Nerk")
	{
		auto ent = stt->Add_Entity<Character>(layer);
		Sprite::Create(ent, Texture::Load("imgs/nerk-sheet.png", 144, 24, 24, 24, 0, 1));
		Animation::Add(ent, "idle", "0x80 1x5", true);
		Animation::Add(ent, "move", "0x4 2-5x4", false);
		Movement::Set(ent, 2.3, 10);
		return ent;
	}

	else if (name == "Dreg")
	{
		auto ent = stt->Add_Entity<Character>(layer);
		Sprite::Create(ent, Texture::Load("imgs/dreg-sheet.png", 216, 24, 24, 24, 0, 1));
		Animation::Add(ent, "idle", "0x63 1-3x5", true);
		Animation::Add(ent, "move", "4-8x4", false);
		Movement::Set(ent, 2.3, 10);
		return ent;
	}

	else if (name == "Mosh")
	{
		auto ent = stt->Add_Entity<Character>(layer);
		Sprite::Create(ent, Texture::Load("imgs/mosh-sheet.png", 168, 24, 24, 24, 0, 1));
		Animation::Add(ent, "idle", "0x70 1x3", true);
		Animation::Add(ent, "move", "0x6 2-6x6", false);
		Movement::Set(ent, 2.3, 10);
		return ent;
	}

	else if (name == "Raiden")
	{
		auto ent = stt->Add_Entity<Character>(layer);
		Sprite::Create(ent, Texture::Load("imgs/raiden-sheet.png", 96, 24, 24, 24, 0, 1));
		Animation::Add(ent, "idle", "0", true);
		Animation::Add(ent, "move", "0-4x4", false);
		Movement::Set(ent, 2.3, 10);
		return ent;
	}

	else if (name == "Tar")
	{
		auto ent = stt->Add_Entity<Character>(layer);
		Sprite::Create(ent, Texture::Load("imgs/tar-sheet.png", 216, 24, 24, 24, 0, 1));
		Animation::Add(ent, "idle", "0x85 1x5", true);
		Animation::Add(ent, "move", "0x4 2-8x4", false);
		Movement::Set(ent, 2.3, 40);
		return ent;
	}

	else if (name == "Benio")
	{
		auto ent = stt->Add_Entity<Character>(layer);
		Sprite::Create(ent, Texture::Load("imgs/benio.png", 24, 24, 24, 24, 0, 1));
		Animation::Add(ent, "idle", "0", true);
		Animation::Add(ent, "move", "0", false);
		Movement::Set(ent, 2.3, 10);
		return ent;
	}

	std::cerr << "ERR Character::Add : No character with given name exists\n";
	return nullptr;
}
