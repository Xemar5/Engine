#include "Network.h"
#include "Output_Handler.h"
#include <Windows.h>
#include <functional>
#include <sstream>
#include "Entity.h"
#include "Character.h"

Uint32 NetworkID::idNum = 0;

int Network::port = 42820;
std::string Network::toConnect = "127.0.0.1";
IPaddress Network::host;
UDPsocket Network::client;
UDPpacket* Network::packet = SDLNet_AllocPacket(256);
NetworkState Network::networkState = NetworkState::NS_None;
std::map<std::string, std::pair<std::function<void(std::istream&)>, bool>> Network::RPC_Map;
std::map<NetworkID, Entity*> Network::RegisteredEntities;
std::vector<IPaddress> Network::Clients;
std::vector<UDPpacket*> Network::peedingUDP;
std::vector<std::string> Network::RPC_Saved;
std::regex Network::RPC_Regex("([a-zA-Z_]+)(\\d*)\\.(\\d)\\.([a-zA-Z_<>:\\d]+)\\.(.*)");
ConnectionType Network::connectionType = ConnectionType::CT_None;

void Network::Init()
{
	SDLNet_Init();

	RPC_REG_STORED(Character::RPC_Add);
}

void Network::Host()
{
	if (Network::connectionType == ConnectionType::CT_None)
	{
		//STARTUPINFO si;
		//PROCESS_INFORMATION pi;
		//if (!CreateProcess(NULL, "C:\\Users\\Pabu4\\Desktop", NULL, NULL, false, CREATE_DEFAULT_ERROR_MODE | CREATE_NO_WINDOW | DETACHED_PROCESS, NULL, NULL, &si, &pi))
		//	std::cout << "err: " << GetLastError() << std::endl;
	}
	else if (Network::connectionType == ConnectionType::CT_Server)
	{
		//SDLNet_ResolveHost(&Network::host, NULL, Network::port);
		Network::client = SDLNet_UDP_Open(Network::port);
		if (!Network::client)
		{
			Output_Handler::Error << "ERR Network::Host : Couldn't open port " + std::to_string(Network::port) + ", exiting server\n";
			// Exit Server Foo
		}
		else
		{
			Network::networkState = NetworkState::NS_Connected;
		}
	}
}




void Network::Join(std::string ip, int port)
{
	std::thread jrt(ResolveJoin, ip, port);
	jrt.detach();
}

bool Network::ResolveJoin(std::string ip, int port)
{
	Output_Handler::Output << "MSG Network::ResolveJoin : Connecting to server...\n";

	Network::networkState = NetworkState::NS_Connecting;
	//Network::connectionType = ConnectionType::CT_Client;

	if (!(client = SDLNet_UDP_Open(0))) { Output_Handler::Error << "ERR Network::ResolveJoin : Couldn't open a port\n"; return false; }
	if (SDLNet_ResolveHost(&Network::host, ip.c_str(), port)) { Output_Handler::Error << "ERR Network::ResolveJoin : An error has occured with host resolving\n"; return false; }


	int startTime = SDL_GetTicks();
	while (Network::networkState == NetworkState::NS_Connecting)
	{
		if (SDL_GetTicks() - startTime > 10000) break;
		Output_Handler::Output << "MSG Network::ResolveJoin : Waiting for server response...\n";

		std::string message = "CON.ATTEMPT";
		AllocatePacket(Network::host, message);
		
		SDL_Delay(1000);
	}

	if (Network::networkState == NetworkState::NS_Connected)
	{
		Output_Handler::Output << "MSG Network::ResolveJoin : Connected!\n";
		Network::connectionType = ConnectionType::CT_Client;
		//for (auto rpc : RPC_Saved)
		//	AllocatePacket(Network::host, rpc);
		//RPC_Saved.clear();
		ClientConnected(IPaddress());
	}
	else
	{
		Output_Handler::Output << "MSG Network::ResolveJoin : Connection denied\n";
		Network::connectionType = ConnectionType::CT_None;
		Network::networkState = NetworkState::NS_None;
	}
	return Network::networkState == NetworkState::NS_Connected;
}


bool Network::ResolveConnection(UDPpacket* packet)
{
	std::string response((char*)packet->data, packet->len);

	if (Network::connectionType == ConnectionType::CT_Server)
	{
		if (response == "CON.ATTEMPT")
		{
			IPaddress clientIP;
			clientIP.host = packet->address.host;
			clientIP.port = packet->address.port;

			std::string message = "CON.ACCEPT";
			if (Network::Clients.size() == 4) message = "CON.DECLINE";
			else if (message == "CON.ACCEPT")
			{
				for (auto c : Network::Clients)
					if (c.host == clientIP.host && c.port == clientIP.port)
					{
						message = "CON.DECLINE";
						break;
					}
			}

			AllocatePacket(clientIP, message);

			if (message == "CON.ACCEPT")
			{
				Output_Handler::Output << "MSG Network::ResolveConnection : Client connected\n";
				Clients.push_back(clientIP);
				ClientConnected(clientIP);
			}
			else
			{
				Output_Handler::Output << "MSG Network::ResolveConnection : Client denied\n";
			}
		}
	}
	else 
	{
		if (Network::networkState == NetworkState::NS_Connecting)
		{
			if (response == "CON.DECLINE") Network::networkState = NetworkState::NS_Disconnecting;
			else if (response == "CON.ACCEPT") 
			{ 
				Network::networkState = NetworkState::NS_Connected;
			}
		}
	}
	return true;
}

UDPpacket * Network::AllocatePacket(IPaddress receiver, std::string data)
{
	auto p = SDLNet_AllocPacket(256);
	p->address.host = receiver.host;
	p->address.port = receiver.port;
	memcpy(p->data, data.c_str(), data.length());
	p->len = data.length();
	peedingUDP.push_back(p);
	return p;
}

void Network::ReceiveUDP()
{
	while (SDLNet_UDP_Recv(Network::client, Network::packet) > 0)
	{
		if (Network::packet->len > 1)
		{
			char c = ((char*)Network::packet->data)[0];
			if (c == 'C') ResolveConnection(Network::packet);
			if (c == 'R') RPC::_Decode(Network::packet);
			if (c == 'B') BackmessageResponse(Network::packet);
		}
	}
}


bool Network::RegisterEntity(Entity * ent)
{
	for (auto it = RegisteredEntities.begin(); it != RegisteredEntities.end(); ++it)
		if (it->second == ent) return Output_Handler::ErrorReturn("ERR Network::RegisterEntity : Entity already registered\n", false);
	NetworkID nid;
	RegisteredEntities[nid] = ent;
	return false;
}

void Network::ClientUpdate()
{
	Network::ReceiveUDP();
}

void Network::ServerUpdate()
{
	Network::ReceiveUDP();
}

void Network::Update()
{
	if (Network::connectionType == CT_Server) ServerUpdate();
	else if (Network::networkState == NetworkState::NS_Connected || Network::networkState == NetworkState::NS_Connecting) ClientUpdate();
}













//void Network::RPC_Decode(UDPpacket* packet)
//{
//	bool allowed = false;
//	for(auto c : Clients)
//		if (c.host == packet->address.host && c.port == packet->address.port) { allowed = true; break; }
//	if(Network::host.host == packet->address.host && Network::host.port == packet->address.port) allowed = true;
//
//	if (allowed)
//	{
//		std::string s((char*)packet->data, packet->len);
//		auto m = std::cmatch{};
//
//		if (std::regex_match(s.c_str(), m, RPC_Regex) && m.size() == 6)
//		{
//			if (m[1] == "RPC")
//			{
//				std::string bmstr = m[2];
//				RPC_Receiver r = (RPC_Receiver)std::stoi(m[3]);
//				std::string f = m[4];
//				std::string a = m[5];
//				unsigned bm = bmstr.size() ? (unsigned)std::stoi(bmstr) : -1;
//				if (Network::connectionType == ConnectionType::CT_Server && RPC_Map.find(f) != RPC_Map.end() && RPC_Map[f].second)
//					RPC_Saved.push_back("RPC." + std::to_string(r) + "." + f + "." + a);
//				Backmessage(packet->address, bm);
//				RPC_DecodeResolve(packet->address, r, f, a);
//			}
//		}
//	}
//}

//void Network::RPC_DecodeResolve(IPaddress sender, RPC_Receiver reciever, std::string foo, std::string args)
//{
//	std::string s;
//	std::istringstream arg(args);
//
//	if (Network::connectionType == ConnectionType::CT_Client || Network::connectionType == ConnectionType::CT_None)
//	{
//		RPC::_Map[foo].first(arg);
//	}
//	else if (Network::connectionType == ConnectionType::CT_Server)
//	{
//		if (RPC_Map.find(foo) != RPC_Map.end())
//		{
//			unsigned backmessage = Network::NextBackMessage();
//			switch (reciever)
//			{
//			case RPCr_All:
//				s = "RPC" + (backmessage != -1 ? std::to_string(backmessage) : "") + ".0." + foo + "." + args;
//				for (auto c : Clients) AllocatePacket(c, s);
//				RPC_Map[foo].first(arg);
//				break;
//			case RPCr_Others:
//				s = "RPC" + (backmessage != -1 ? std::to_string(backmessage) : "") + ".1." + foo + "." + args;
//				for (auto c : Clients) if (c.host != packet->address.host && c.port != packet->address.port) AllocatePacket(c, s);
//				if(sender.host || sender.port) RPC_Map[foo].first(arg);
//				break;
//			case RPCr_Server:
//				RPC_Map[foo].first(arg);
//				break;
//			default:
//				break;
//			}
//		}
//	}
//}


void Network::ClientConnected(IPaddress client)
{
	if (Network::connectionType == ConnectionType::CT_Server)
		for (auto rpc : RPC::_Saved)
		{
			rpc = rpc.substr(0, 3) + std::to_string(Network::NextBackMessage()) + rpc.substr(3, rpc.length() - 3);
			AllocatePacket(client, rpc);
		}
}

void Network::BackmessageResponse(UDPpacket * packet)
{
	std::string d = std::string((char*)packet->data, packet->len);
	if (d.find("BM.") == 0)
	{
		unsigned bm = std::stoi(d.substr(3, d.length() - 3));
		if(bm != -1)
			std::cout << "      kk: " << bm <<"."<< std::endl;
	}
}

void Network::ResolveBackmessages()
{
	// SENDER
	//    wysyla co x sekund powiadomienie o braku nieodebranych Backmessage'ow
	//    albo wysy³a nieodebrane RPC ponownie z dopiskiem RPCa (a - again?)
	// RECEIVER
	//    odbiera wiadomosc o braku nieodebranych Backmessage'ow z radoscia I USOWA HISTORIE RPC
	//    albo otrzymuje RPCa
	//        jezeli jest to pierwsze RPCa z tym id(hash), call function i Backmessage
	//		  albo Backmessage
}

unsigned BBBBBB = 0;
unsigned Network::NextBackMessage()
{
	return BBBBBB++;
}

void Network::Backmessage(IPaddress sender, unsigned hash)
{
	if (hash != -1)
	{
		std::string s = "BM." + std::to_string(hash);
		AllocatePacket(sender, s);
	}
}

void Network::SendAll()
{
	//SDLNet_UDP_SendV(Network::client, peedingUDP.data(), peedingUDP.size());
	for (auto t : peedingUDP)
	{
		SDLNet_UDP_Send(Network::client, -1, t);
		SDLNet_FreePacket(t);
	}
	peedingUDP.clear();
}




//bool Network::RPC(std::string& s, int r, decltype(RPC_Map.end()) foo)
//{
//	if (foo == RPC_Map.end()) return Output_Handler::ErrorReturn("ERR Network::RPC : Given RPC function not supplied\n", false);
//
//	std::string message;
//	if (Network::connectionType == ConnectionType::CT_Server || Network::connectionType == ConnectionType::CT_None)
//	{
//		message = "RPC." + std::to_string(r) + "." + foo->first + "." + s;
//		if (Network::connectionType == ConnectionType::CT_Server && foo->second.second) RPC_Saved.push_back(message);
//		RPC_DecodeResolve(IPaddress(), (RPC_Receiver)r, foo->first, s);
//	}
//	else
//	{
//		message = "RPC" + std::to_string(Network::NextBackMessage()) + "." + std::to_string(r) + "." + foo->first + "." + s;
//		AllocatePacket(Network::host, message);
//	}
//	return true;
//}