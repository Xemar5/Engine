#pragma once
#include <iostream>

struct Output_Handler
{
	//*** Main Console output stream
	static std::ostream& Output;
	//*** Main Error output stream
	static std::ostream& Error;

	//*** Writes to Output stream and returns a value
	template <typename T> static T OutputReturn(std::string stream, T returnValue);
	//*** Writes to Error stream and returns a value
	template <typename T> static T ErrorReturn(std::string stream, T returnValue);
};

template<typename T>
inline T Output_Handler::OutputReturn(std::string stream, T returnValue)
{
	Output << stream;
	return returnValue;
}

template<typename T>
inline T Output_Handler::ErrorReturn(std::string stream, T returnValue)
{
	Error << stream;
	return returnValue;
}
