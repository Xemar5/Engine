#include "Animation.h"
#include "Sprite.h"
#include "Texture.h"
#include "Entity.h"
#include "Output_Handler.h"

Animation* Animation::Add(Texture* sprite, std::string name, std::string frame_sequence, bool repeat)
{
	if (!sprite)
	{
		Output_Handler::Error << "ERR Animation::Add : No Sprite to add the animation to is supplied\n";
		return nullptr;
	}
	if (!name.size())
	{
		Output_Handler::Error << "ERR Animation::Add : No name of the animation supplied\n";
		return nullptr;
	}
	if (!frame_sequence.size())
	{
		Output_Handler::Error << "ERR Animation::Add : No frames supplied\n";
		return nullptr;
	}
	if (auto* anim = Animation::Exists(sprite, name))
	{
		//if(name != "idle") Output_Handler::Output << "MSG Animation::Add : Animation " << name << " already exists, replacing\n";
		anim->__Frame_Sequence = Animation::Decode(frame_sequence);
		anim->__Name = name;
		anim->__Repeat = repeat;
		return anim;
	}
	sprite->__Animations.emplace_back(std::make_shared<Animation>());
	sprite->__Animations.back()->__Frame_Sequence = Animation::Decode(frame_sequence);
	sprite->__Animations.back()->__Name = name;
	sprite->__Animations.back()->__Repeat = repeat;
	return sprite->__Animations.back().get();
}


Animation * Animation::Add(Entity * ent, std::string name, std::string frame_sequence, bool repeat)
{
	if (!ent)
	{
		Output_Handler::Error << "ERR Animation::Add : No entity supplied\n";
		return nullptr;
	}
	return Animation::Add(ent->Get_Sprite()->Get_Texture().get(), name, frame_sequence, repeat);
}

Animation * Animation::Exists(Texture* sprite, std::string name)
{
	for (auto anim : sprite->__Animations)
		if (anim->__Name == name) return anim.get();
	return nullptr;
}

std::vector<unsigned> Animation::Get_Sequence(Texture* sprite, std::string name)
{
	if (auto anim = Animation::Exists(sprite, name))
		return anim->__Frame_Sequence;
	Output_Handler::Error << "ERR Animation::Get_Sequence : Animation " << name << " doesnt exist in supplied sprite\n";
	return{};
}

std::string Animation::Get_Name()
{
	return __Name;
}

unsigned Animation::Get_Current_Frame(unsigned sequence_iterator)
{
	if (sequence_iterator >= __Frame_Sequence.size()) { Output_Handler::Error << "ERR Animation::Get_Current_Frame : Given iterator is greater than the size of Frame Sequence\n"; return 0; }
	return __Frame_Sequence[sequence_iterator];
}

bool Animation::Set_Frame(Entity* ent, unsigned frame)
{
	if (!ent) { Output_Handler::Error << "ERR Animation::Set_Frame : No Entity supplied\n"; return false; }
	if (!ent->Get_Sprite()) { Output_Handler::Error << "ERR Animation::Set_Frame : Given Entity has no Sprite supplied\n"; return false; };
	if (!ent->Get_Sprite()->Get_Texture()) { Output_Handler::Error << "ERR Animation::Set_Frame : Given Sprite has no Texture supplied\n"; return false; };
	if (frame >= ent->Get_Sprite()->Get_Texture()->Get_Frames_Number()) { Output_Handler::Error << "ERR Animation::Set_Frame : Given frame number is greater than the max number of frames\n"; return false; }

	auto pos = ent->Get_Sprite()->Get_Texture()->Get_Frame_Pos(frame);
	ent->Get_Sprite()->__Frame_Pos_X = pos.first;
	ent->Get_Sprite()->__Frame_Pos_Y = pos.second;
	return true;
}

unsigned Animation::Next_Frame(Entity* ent)
{
	if (!ent) { Output_Handler::Error << "ERR Animation::Next_Frame : No Entity supplied\n"; return 0; }
	if (!ent->Get_Sprite()) { Output_Handler::Error << "ERR Animation::Next_Frame : Given Entity has no Sprite supplied\n"; return 0; };
	if (!ent->Get_Sprite()->Get_Texture()) { Output_Handler::Error << "ERR Animation::Next_Frame : Given Sprite has no Texture supplied\n"; return 0; };
	if (!ent->Get_Sprite()->__Current_Animation){ Output_Handler::Error << "ERR Animation::Next_Frame : Given Sprite plays no Animation\n"; return 0; }

	ent->Get_Sprite()->__Sequence_Iterator++;
	if (ent->Get_Sprite()->__Sequence_Iterator >= (int)Animation::Get_Sequence(ent->Get_Sprite()->Get_Texture().get(), ent->Get_Sprite()->__Current_Animation->__Name).size())
	{
		ent->Get_Sprite()->__Sequence_Iterator = -1;
		if (!ent->Get_Sprite()->__Current_Animation->__Repeat) ent->Get_Sprite()->__Current_Animation = nullptr;
	}
	return ent->Get_Sprite()->__Sequence_Iterator;
}

Animation* Animation::Play(Entity* ent, std::string name)
{
	if (!ent) { Output_Handler::Error << "ERR Animation::Play : No Entity supplied\n"; return nullptr; }
	return Animation::Play(ent->Get_Sprite().get(), name);
}

Animation* Animation::Play(Sprite* sprite, std::string name)
{
	if (!sprite) { Output_Handler::Error << "ERR Animation::Play : Given Entity has no Sprite supplied\n"; return nullptr; };
	if (!sprite->Get_Texture()) { Output_Handler::Error << "ERR Animation::Play : Given Sprite has no Texture supplied\n"; return nullptr; }
	if (!name.size()) { Output_Handler::Error << "ERR Animation::Play : No name of the animation supplied\n"; }

	if (sprite->__Current_Animation && sprite->__Current_Animation->Get_Name() == name) return sprite->__Current_Animation;
	return Animation::Force_Play(sprite, name);
}

Animation * Animation::Soft_Play(Entity * ent, std::string name)
{
	if (!ent) { Output_Handler::Error << "ERR Animation::Soft_Play : No Entity supplied\n"; return nullptr; }
	return Animation::Soft_Play(ent->Get_Sprite().get(), name);
}

Animation * Animation::Soft_Play(Sprite * sprite, std::string name)
{
	if (!sprite) { Output_Handler::Error << "ERR Animation::Soft_Play : Given Entity has no Sprite supplied\n"; return nullptr; };
	if (!sprite->Get_Texture()) { Output_Handler::Error << "ERR Animation::Soft_Play : Given Sprite has no Texture supplied\n"; return nullptr; }
	if (!name.size()) { Output_Handler::Error << "ERR Animation::Soft_Play : No name of the animation supplied\n"; }

	if (sprite->__Current_Animation) return sprite->__Current_Animation;
	return Animation::Force_Play(sprite, name);
}

Animation * Animation::Force_Play(Entity * ent, std::string name)
{
	if (!ent) { Output_Handler::Error << "ERR Animation::Force_Play : No Entity supplied\n"; return nullptr; }
	return Animation::Force_Play(ent->Get_Sprite().get(), name);
}


Animation * Animation::Force_Play(Sprite * sprite, std::string name)
{
	if (!sprite) { Output_Handler::Error << "ERR Animation::Force_Play : Given Entity has no Sprite supplied\n"; return nullptr; };
	if (!sprite->Get_Texture()) { Output_Handler::Error << "ERR Animation::Force_Play : Given Sprite has no Texture supplied\n"; return nullptr; }
	if (!name.size()) { Output_Handler::Error << "ERR Animation::Force_Play : No name of the animation supplied\n"; }
	if (!(sprite->__Current_Animation = Animation::Exists(sprite->Get_Texture().get(), name)))
	{
		Output_Handler::Output << "MSG Animation::Play : Animation \"" << name << "\" doesn't exists in supplied sprite; setting to \"idle\"\n";
		sprite->__Current_Animation = Animation::Exists(sprite->Get_Texture().get(), "idle");
	}
	sprite->__Sequence_Iterator = -1;
	return sprite->__Current_Animation;
}

bool Animation::Terminate(Entity* ent, std::string name)
{
	if (!ent) { Output_Handler::Error << "ERR Animation::Terminate : No Entity supplied\n"; return false; }
	return Terminate(ent->Get_Sprite().get(), name);
}

bool Animation::Terminate(Sprite * sprite, std::string name)
{
	if (!sprite) { Output_Handler::Error << "ERR Animation::Terminate : Given Entity has no Sprite supplied\n"; return false; };
	if (!sprite->Get_Texture()) { Output_Handler::Error << "ERR Animation::Terminate : Given Sprite has no Texture supplied\n"; return false; }

	if (!sprite->Get_Current_Animation()) return false;
	if (!name.size() || sprite->Get_Current_Animation()->Get_Name() == name)
	{
		sprite->__Sequence_Iterator = -1;
		sprite->__Current_Animation = nullptr;
		return true;
	}
	return false;
}

std::vector<unsigned> Animation::Decode(std::string code)
{
	std::vector<unsigned> frames;
	std::string segment = "";
	for (unsigned i = 0; i < code.size(); i++)
	{
		if (code[i] == '\0') break;
		if ((code[i] < '0' ||
			code[i] > '9') &&
			code[i] != '-' &&
			code[i] != 'x' &&
			code[i] != ' ')
		{
			Output_Handler::Output << "MSG Animation::Decode : Unsupported character '"<< code[i] <<"'; use only numbers, '-', 'x' and '(space)'\n";
			continue;
		}

		if (!segment.size() && (
			code[i] == '-' ||
			code[i] == 'x' ||
			code[i] == ' '))
			continue;
		
		if (segment.size() && (
			segment.back() == '-' ||
			segment.back() == 'x'))
		{
			if (code[i] == ' ' ||
				code[i] == '-' ||
				code[i] == 'x')
				segment.pop_back();
		}

		if (code[i] == ' ' && segment.size())
		{
			auto v = Animation::__Decode_Segment(segment);
			for (auto el : v) frames.push_back(el);
			segment.clear();
			continue;
		}

		segment += code[i];
	}

	if (segment.size())
	{
		auto v = Animation::__Decode_Segment(segment);
		for (auto el : v) frames.push_back(el);
		segment.clear();
	}

	if (!frames.size()) frames.push_back(0);
	return frames;
}

std::vector<unsigned> Animation::__Decode_Segment(std::string code)
{
	std::vector<unsigned> v;

	int base = 0;
	int series = -1;
	int multi = -1;
	int* flag = &base;

	for (unsigned i = 0; i < code.size(); i++)
	{
		if (code[i] >= '0' && code[i] <= '9')
		{
			*flag *= 10;
			*flag += code[i] - '0';
		}
		else if (code[i] == '-')
		{
			series = 0;
			flag = &series;
		}
		else if (code[i] == 'x')
		{
			multi = 0;
			flag = &multi;
		}
	}

	if (series == -1) series = base;
	while (true)
	{
		auto m = multi;
		if (m == -1) m = 1;
		while (m--)	v.push_back(base);
		if (series == base) break;
		if (series < base) base--;
		if (series > base) base++;
	}

	return v;
}
