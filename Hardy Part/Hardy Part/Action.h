#pragma once
#include <vector>
#include <memory>
#include <SDL.h>

//*** Deriver form this class
class Action
{
protected:
	template<typename U>
	bool _Set_Event_Conditions(U& event_type);
	template<typename U, typename T>
	bool _Set_Event_Conditions(U& event_type, T event_condition);
	template<typename U, typename T, typename ...R>
	bool _Set_Event_Conditions(U& event_type, T event_condition, R&... rest);


	bool _Set_Variables(std::vector<double*>& vars, std::vector<double*>& args);

};

template<typename U>
inline bool Action::_Set_Event_Conditions(U& event_type)
{
	return false;
}

template<typename U, typename T>
inline bool Action::_Set_Event_Conditions(U& event_type, T event_condition)
{
	return false;
}

template<typename U, typename T, typename ...R>
inline bool Action::_Set_Event_Conditions(U& event_type, T event_condition, R& ...rest)
{
	return _Set_Event_Conditions(rest...);
}

