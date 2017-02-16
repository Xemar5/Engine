#pragma once
#include "System.h"
#include <functional>

enum ControlsEvent
{
	//*** Fires on key up event
	CE_K_UP,
	//*** Fires on key down event
	CE_K_DOWN,
	//*** Fires on key up event, when the down event has appeared in less than 0.5s before
	CE_K_CLICK,
	//*** Fires on key up event, when the down event has appeared in more than 0.5s before
	CE_K_HELD,

	//*** Fires on gamepad up event
	CE_G_UP,
	//*** Fires on gamepad down event
	CE_G_DOWN,
	//*** Fires on gamepad up event, when the down event has appeared in less than 0.5s before
	CE_G_CLICK,
	//*** Fires on gamepad up event, when the down event has appeared in more than 0.5s before
	CE_G_HELD,
	//*** Fires on gamepad hat up event
	CE_G_HAT_UP,
	//*** Fires on gamepad hat down event
	CE_G_HAT_DOWN,
	//*** Fires on gamepad hat up event, when the down event has appeared in less than 0.5s before
	CE_G_HAT_CLICK,
	//*** Fires on gamepad hat up event, when the down event has appeared in more than 0.5s before
	CE_G_HAT_HELD,
	//*** Fires on gamepad axis move event
	CE_G_MOVE,


	//*** Fires on gamepad up event
	CE_M_UP,
	//*** Fires on gamepad down event
	CE_M_DOWN,
	//*** Fires on gamepad up event, when the down event has appeared in less than 0.5s before
	CE_M_CLICK,
	//*** Fires on gamepad up event, when the down event has appeared in more than 0.5s before
	CE_M_HELD,
	//*** Fires on gamepad axis move event
	CE_M_MOVE
};

class Controls
{
public:

	static void Events();
	static void Update();


	static void Key_Up		(Entity* reciever, std::function<void(Entity*, unsigned)> callback) { AddEvent(reciever, callback, _K_Up); };
	static void Key_Down	(Entity* reciever, std::function<void(Entity*, unsigned)> callback) { AddEvent(reciever, callback, _K_Down); };
	static void Key_Click	(Entity* reciever, std::function<void(Entity*, unsigned)> callback) { AddEvent(reciever, callback, _K_Click); };
	static void Key_Held	(Entity* reciever, std::function<void(Entity*, unsigned, double)> callback) { AddEvent(reciever, callback, _K_Held); };

	static void Gamepad_Up		(Entity* reciever, std::function<void(Entity*, unsigned, unsigned)> callback) { AddEvent(reciever, callback, _G_Up); };
	static void Gamepad_Down	(Entity* reciever, std::function<void(Entity*, unsigned, unsigned)> callback) { AddEvent(reciever, callback, _G_Down); };
	static void Gamepad_Click	(Entity* reciever, std::function<void(Entity*, unsigned, unsigned)> callback) { AddEvent(reciever, callback, _G_Click); };
	static void Gamepad_Held	(Entity* reciever, std::function<void(Entity*, unsigned, unsigned, double)> callback) { AddEvent(reciever, callback, _G_Held); };
	static void Gamepad_Hat_Up		(Entity* reciever, std::function<void(Entity*, unsigned, unsigned)> callback) { AddEvent(reciever, callback, _G_Hat_Up); };
	static void Gamepad_Hat_Down	(Entity* reciever, std::function<void(Entity*, unsigned, unsigned)> callback) { AddEvent(reciever, callback, _G_Hat_Down); };
	static void Gamepad_Hat_Click	(Entity* reciever, std::function<void(Entity*, unsigned, unsigned)> callback) { AddEvent(reciever, callback, _G_Hat_Click); };
	static void Gamepad_Hat_Held	(Entity* reciever, std::function<void(Entity*, unsigned, unsigned, double)> callback) { AddEvent(reciever, callback, _G_Hat_Held); };
	static void Gamepad_Move	(Entity* reciever, std::function<void(Entity*, unsigned, unsigned, int, int)> callback) { AddEvent(reciever, callback, _G_Move); };

	static void Mouse_Up	(Entity* reciever, std::function<void(Entity*, unsigned)> callback) { AddEvent(reciever, callback, _M_Up); };
	static void Mouse_Down	(Entity* reciever, std::function<void(Entity*, unsigned)> callback) { AddEvent(reciever, callback, _M_Down); };
	static void Mouse_Click	(Entity* reciever, std::function<void(Entity*, unsigned)> callback) { AddEvent(reciever, callback, _M_Click); };
	static void Mouse_Held	(Entity* reciever, std::function<void(Entity*, unsigned, double)> callback) { AddEvent(reciever, callback, _M_Held); };
	static void Mouse_Move	(Entity* reciever, std::function<void(Entity*, int, int, int, int)> callback) { AddEvent(reciever, callback, _M_Move); };



	static void Key_Up_Unsubscribe		(Entity* reciever) { RemoveEvent(reciever, _K_Up); }
	static void Key_Down_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _K_Down); };
	static void Key_Click_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _K_Click); };
	static void Key_Held_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _K_Held); };

	static void Gamepad_Up_Unsubscribe		(Entity* reciever) { RemoveEvent(reciever, _G_Up); };
	static void Gamepad_Down_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _G_Down); };
	static void Gamepad_Click_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _G_Click); };
	static void Gamepad_Held_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _G_Held); };
	static void Gamepad_Hat_Up_Unsubscribe		(Entity* reciever) { RemoveEvent(reciever, _G_Hat_Up); };
	static void Gamepad_Hat_Down_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _G_Hat_Down); };
	static void Gamepad_Hat_Click_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _G_Hat_Click); };
	static void Gamepad_Hat_Held_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _G_Hat_Held); };
	static void Gamepad_Move_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _G_Move); };

	static void Mouse_Up_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _M_Up); };
	static void Mouse_Down_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _M_Down); };
	static void Mouse_Click_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _M_Click); };
	static void Mouse_Held_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _M_Held); };
	static void Mouse_Move_Unsubscribe	(Entity* reciever) { RemoveEvent(reciever, _M_Move); };

private:
	template <typename T> static int ContainsEvent(Entity* ent, std::vector<std::pair<Entity*, T>>& e);
	template <typename T> static void RemoveEvent(Entity* ent, std::vector<std::pair<Entity*, T>>& e);
	template <typename T, typename K> static void AddEvent(Entity* ent, K callback, std::vector<std::pair<Entity*, T>>& e);

	
	
	static std::map<unsigned, double> _Keyboard_Buttons;


	static void _Mouse_Update();
	static std::map<unsigned, double> _Mouse_Buttons;
	static int _new_Mouse_X;
	static int _new_Mouse_Y;


	static void _Gamepad_Axis_Update();
	static std::map<unsigned, std::map<unsigned, int>> _Gamepad_Axes;
	static std::map<unsigned, std::map<unsigned, double>> _Gamepad_Buttons;

	static void _Gamepad_Hat_Update();
	static std::vector<std::vector<std::pair<double, int>>> _Gamepad_Hat;


	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> _K_Up;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> _K_Down;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> _K_Click;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, double)>>> _K_Held;

	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> _G_Up;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> _G_Down;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> _G_Click;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned, double)>>> _G_Held;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> _G_Hat_Up;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> _G_Hat_Down;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned)>>> _G_Hat_Click;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned, double)>>> _G_Hat_Held;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, unsigned, int, int)>>> _G_Move;

	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> _M_Up;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> _M_Down;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned)>>> _M_Click;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, unsigned, double)>>> _M_Held;
	static std::vector<std::pair<Entity*, std::function<void(Entity*, int, int, int, int)>>> _M_Move;
};




template<typename T>
inline int Controls::ContainsEvent(Entity * ent, std::vector<std::pair<Entity*, T>>& e)
{
	for (unsigned i = 0; i < e.size(); ++i)
		if (e[i].first == ent) return (int)i;
	return -1;
}

template <typename T, typename K>
inline void Controls::AddEvent(Entity * ent, K callback, std::vector<std::pair<Entity*, T>>& e)
{
	if (!ent) Output_Handler::Error << "ERR Controls::AddEvent : No Entity supplied\n";
	else if(!callback) Output_Handler::Error << "ERR Controls::AddEvent : No callback function supplied\n";
	else
	{
		auto contains = ContainsEvent(ent, e);
		if (contains == -1) e.push_back({ ent, callback });
		else Output_Handler::Error << "ERR Controls::AddEvent : Given Entity already subscribes this event\n";
	}
}

template <typename T>
inline void Controls::RemoveEvent(Entity * ent, std::vector<std::pair<Entity*, T>>& e)
{
	if (!ent) Output_Handler::Error << "ERR Controls::RemoveEvent : No Entity supplied\n";
	else
	{
		auto contains = ContainsEvent(ent, e);
		if (contains != -1) e.erase(e.begin() + contains);
		else Output_Handler::Error << "ERR Controls::RemoveEvent : Given Entity does not subscribe to this event\n";
	}
}

