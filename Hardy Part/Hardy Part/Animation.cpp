#include "Animation.h"
#include "Output_Handler.h"
#include "Sprite.h"

int Animation::Current_Frame()
{
	if (__Iterator == -1)
		return -1;
	return __Frame_Sequence[__Iterator];
}

int Animation::Next_Frame()
{
	if (__Iterator + 1 >= __Frame_Sequence.size())
	{
		if (__User && __User->__Current_Animation == this)
			__User->__Current_Animation = nullptr;
		return __Iterator = -1;
	}
	return __Frame_Sequence[++__Iterator];
}





bool Animation::Play()
{
	if (!this)
	{
		Output_Handler::Output << "MSG Animation::Play : No this Animation\n";
		return false;
	}
	if (!__User)
	{
		Output_Handler::Output << "MSG Animation::Play : This Animation has no User\n";
		return false;
	}
	if (__User->__Current_Animation == this) return false;
	return Force_Play();
}

bool Animation::Soft_Play()
{
	if (!this)
	{
		Output_Handler::Output << "MSG Animation::Soft_Play : No this Animation\n";
		return false;
	}
	if (!__User)
	{
		Output_Handler::Output << "MSG Animation::Soft_Play : This Animation has no User\n";
		return false;
	}
	if (__User->__Current_Animation) return false;
	return Force_Play();
}

bool Animation::Force_Play()
{
	if (!this)
	{
		Output_Handler::Output << "MSG Animation::Force_Play : No this Animation\n";
		return false;
	}
	if (!__User)
	{
		Output_Handler::Output << "MSG Animation::Force_Play : This Animation has no User\n";
		return false;
	}
	if (__User->__Current_Animation) __User->__Current_Animation->Terminate();
	__User->__Current_Animation = this;
	__User->__Current_Animation->__Iterator = 0;
	return true;
}

bool Animation::Terminate()
{
	if (!this)
	{
		Output_Handler::Output << "MSG Animation::Terminate : No this Animation\n";
		return false;
	}
	if (!__User)
	{
		Output_Handler::Output << "MSG Animation::Terminate : This Animation has no User\n";
		return false;
	}
	if (!__User->__Current_Animation) return false;
	__User->__Current_Animation->__Iterator = -1;
	__User->__Current_Animation = nullptr;
	return true;
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
			Output_Handler::Output << "MSG Animation::Decode : Unsupported character '" << code[i] << "'; use only numbers, '-', 'x' and '(space)'\n";
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
