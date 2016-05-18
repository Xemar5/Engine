#pragma once
#include <iostream>

struct Output_Handler
{
	//*** Main Console output stream
	static std::ostream& Output;
	//*** Main Error output stream
	static std::ostream& Error;
};
