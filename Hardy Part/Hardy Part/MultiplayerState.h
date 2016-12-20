#pragma once
#include "State.h"
#include "Character.h"

class MultiplayerState : public State
{
public:
	void Create() override
	{
		//if(Network::connectionType == ConnectionType::CT_Server) Network::Host();
		//else if(Network::toConnect.size()) Network::Join(Network::toConnect, Network::port);
	}

	void Update() override
	{
		//if (Mouse::Get[Input::Set(IT_MOUSE_BUTTON, SDL_BUTTON_LEFT)].Held())
		//	Network::RPC("Lold", System::Events.motion.x, System::Events.motion.y);
	}

	void Events() override
	{
		//if (Mouse::Get[Input::Set(IT_MOUSE_BUTTON, SDL_BUTTON_LEFT)].Up())
		//{
		//	RPC::Set(
		//		RPCr_All,
		//		"Character::RPC_Add",
		//		0,
		//		"Nerk",
		//		(int)(System::Events.motion.x / Screen::Get_Scale()),
		//		(int)(System::Events.motion.y / Screen::Get_Scale()),
		//		0u,
		//		1.0);
		//	//Network::RPC(RPCr_All, "f1", (int)(System::Events.motion.x / Screen::Get_Scale()), (int)(System::Events.motion.y / Screen::Get_Scale()));
		//}
		//if (Mouse::Get[Input::Set(IT_MOUSE_BUTTON, SDL_BUTTON_RIGHT)].Up())
		//{
		//	RPC::Set(RPCr_All, "Character::RPC_Add", 0u, "Tar", (int)(System::Events.motion.x / Screen::Get_Scale()), (int)(System::Events.motion.y / Screen::Get_Scale()), 0u, 1.0);
		//}
		//	Network::RPC("Lold", System::Events.motion.x, System::Events.motion.y);
	}
};