#include "Input_Presets.h"

std::vector<std::shared_ptr<Input_Preset>> Input_Preset::__Input_Presets;


Input_Preset * Input_Preset::Set_Gamepad(int gamepad_index)
{
	return nullptr;
}

Input_Preset * Input_Preset::Set_Keyboard()
{
	return nullptr;
}

Input_Preset * Input_Preset::Load_Form_File()
{
	return nullptr;
}

Input_Preset & Input_Preset::operator=(Input_Preset& const src)
{
	Up = src.Up;
	Down = src.Down;
	Left = src.Left;
	Right = src.Right;

	UpAlt = src.UpAlt;
	DownAlt = src.DownAlt;
	LeftAlt = src.LeftAlt;
	RightAlt = src.RightAlt;


	Aim_V = src.Aim_V;
	Aim_H = src.Aim_H;

	Action = src.Action;
	Cancel = src.Cancel;
	Switch = src.Switch;
	Accept = src.Accept;

	L1 = src.L1;
	L2 = src.L2;
	R1 = src.R1;
	R2 = src.R2;

	Start = src.Start;
	Select = src.Select;

	return *this;
}

Input_Preset & Input_Preset::operator<<(Input_Function arg)
{
	if (!Up) Up = arg;
	else if (!Down) Down = arg;
	else if (!Left) Left = arg;
	else if (!Right) Right = arg;

	else if (!UpAlt) UpAlt = arg;
	else if (!DownAlt) DownAlt = arg;
	else if (!LeftAlt) LeftAlt = arg;
	else if (!RightAlt) RightAlt = arg;


	else if (!Aim_V) Aim_V = arg;
	else if (!Aim_H) Aim_H = arg;

	else if (!Action) Action = arg;
	else if (!Cancel) Cancel = arg;
	else if (!Switch) Switch = arg;
	else if (!Accept) Accept = arg;

	else if (!L1) L1 = arg;
	else if (!L2) L2 = arg;
	else if (!R1) R1 = arg;
	else if (!R2) R2 = arg;

	else if (!Start) Start = arg;
	else if (!Select) Select = arg;

	else std::cout << "MSG Input_Preset::operator<< : all fields supplied\n";

	return *this;
}

std::vector<std::shared_ptr<Input_Preset>> Input_Preset::Get_Input_Presets()
{
	return __Input_Presets;
}
