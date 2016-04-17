#include <iostream>
#include "Action.h"
#include "System.h"



bool Action::_Set_Variables(std::vector<double*>& vars, std::vector<double*>& args)
{
	auto ita = args.begin();
	auto itv = vars.begin();
	while (ita != args.end())
	{
		if (itv != vars.end())
		{
			*itv = *ita;
			++ita;
			++itv;
			continue;
		}
		std::cout << "MSG Movement::Set_Variables : Too many arguments; ignoring excess\n";
		break;
	}
	for (auto it = vars.begin(); it != vars.end(); it++)
	{
		if (*it) continue;
		std::cerr << "ERR Movement::Set_Variables : Not enough arguments\n";
		return false;
	}
	return true;
}

