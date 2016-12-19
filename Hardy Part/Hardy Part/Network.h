#pragma once
#include <SDL_net.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <thread>
#include <boost\asio.hpp>
#include "RPC.h"

#define RPC_REG(NAME) Network::RPC_Register(#NAME, stream_function<decltype(NAME)>(NAME));
#define RPC_REG_STORED(NAME) Network::RPC_RegisterStored(#NAME, stream_function<decltype(NAME)>(NAME));
typedef void(*RPCfunction)(std::string arg);

class Entity;

enum ConnectionType
{
	CT_None,
	CT_Server,
	CT_Host,
	CT_Client
};

enum NetworkState
{
	NS_None,
	NS_Connecting,
	NS_Connected,
	NS_Disconnecting
};







////*** Functions responsible for RPC reflections
////*** Use with RPCreg / RPCregister and RPC
//
//template<class...> struct types {};
//template<class F, class Sig> struct stream_function_;
//template<class Sig, class F> stream_function_<F, Sig> stream_function(F f) { return{ f }; }
//template<class F, class R, class... Args> class stream_function_<F, R(Args...)>
//{
//public:
//	stream_function_(F f) : _f(f) {}
//	void operator()(std::istream& is) const { call(is, _f, types<Args...>{}); }
//private:
//	F _f;
//	template<class Foo, class Head, class... Tail, class... Vs> void call(std::istream& is, Foo&& f, types<Head, Tail...>, Vs&&... vs) const
//	{
//		bool good = true;
//		auto val = get<Head>(is, good);
//		if (good) call(is, f, types<Tail...>{}, std::forward<Vs>(vs)..., val);
//	}
//	template<class Foo, class... Vs> void call(std::istream& is, Foo&& f, types<>, Vs&&... vs) const
//	{
//		f(std::forward<Vs>(vs)...);
//	}
//	template <class T>static T get(std::istream& args, bool& good)
//	{
//		T t;
//		if (!(args >> t))
//		{
//			args.clear();
//			Output_Handler::Error << "ERR stream_function_::get : Supplied argument type doesn't match the function's arguments\n";
//			good = false;
//		}
//		args.get();
//		return t;
//	}
//	template <>static std::string get(std::istream& args, bool& good)
//	{
//		std::string t, h;
//		while (true)
//		{
//			std::getline(args, h, '|');
//			t += h;
//			if (args.get() != '|') break;
//		}
//		return t;
//	}
//};



class NetworkID
{
public:
	NetworkID() { }
	NetworkID(bool set) { if (set)Set(); }

	//*** Returns the id of this NetworkID
	Uint32 Get() { return id; }
	//*** Sets the entity as a over-the-network synchronised entity
	void Set() { id = idNum++; std::cout << id << std::endl; }

	bool operator<(const NetworkID nid) const { return this->id < nid.id; }
	bool operator>(const NetworkID nid) const { return this->id > nid.id; }
	bool operator==(const NetworkID nid) const { return this->id == nid.id; }
private:
	//*** The network ID of this entity
	//*** Unique for each entity in one program instance
	//*** Same for every other game instances
	//*** if Uint32 MAX, id not set yet
	Uint32 id = -1;
	//*** Increments with each NetworkID creation
	static Uint32 idNum;
	//*** Resets the idNum
	//*** Use in each new state
	static void Reset() { idNum = 0; }
	friend class Network;
	friend class State;
};



class Network
{
public:
	//*** Initializes the Network class
	static void Init();

	//*** Sets this Game instance as a Host
	//*** This function creates new process and uses it
	//***    as a host each player can connect to
	static void Host();

	static std::string toConnect;
	//*** Tries to connect to given ip/port combination
	static void Join(std::string ip, int port);


	//*** The default Port this application uses
	static int port;
	//*** Your IP address
	static IPaddress host;
	//*** This instance's UDP socket
	static UDPsocket client;
	//*** The type of this game instance's connection
	static ConnectionType connectionType;
	//*** The current state of the network 
	static NetworkState networkState;


	//*** Registers entity over the network
	//*** Synchronises it's position
	//*** client - adds entity to waiting list
	//*** server - sends the NetworkID to all clients
	static bool RegisterEntity(Entity* ent);



	////*** Calls given function over the TCP connection
	////template <typename F, typename...T> static bool Network::RPC(F foo, T && ...args);
	////template <typename F, typename...T> static bool Network::RPC(F foo, T && ...args);
	////*** Calls given function over the TCP connection
	//template <typename ...T> static bool RPC(RPC_Receiver reciever, std::string foo, T&&... args);
	////*** Registers an RPC function
	//template <typename F> static bool RPC_Register(std::string name, F foo);
	////*** Registers an RPC function
	////*** Each on-server call of the registered function will save it
	////***	for each client that enters after the call
	//template <typename F> static bool RPC_RegisterStored(std::string name, F foo);


private:
	Network() {};
	//*** Loop updating all server components, accepting new connections
	//***    and maitaining responses
	static void ServerUpdate();
	//*** Loop updating client
	static void ClientUpdate();


	//*** Fires when a client connects
	static void ClientConnected(IPaddress client);
	//*** Creates thread waiting for server response
	static bool ResolveJoin(std::string ip, int port);
	//*** Allows or denies incomming client connection request
	static bool ResolveConnection(UDPpacket* packet);
	//*** All connected clients
	static std::vector<IPaddress> Clients;






	//*** Packet with incomming data
	static UDPpacket* packet;
	//*** All peeding UDP messages waiting for the end of update loop
	static std::vector<UDPpacket*> peedingUDP;
	//*** Allocates a UDP packet with given data
	static UDPpacket* AllocatePacket(IPaddress receiver, std::string data);
	//*** Current state of the network
	static void ReceiveUDP();
	//*** Responsible for managing RPC callbacks
	//*** If after a send RPC sender doesn't receive Backmessage,
	//***	it will send the RPC again
	static void BackmessageResponse(UDPpacket* packet);
	//*** Thread responsible for sending unresponsed RPCs
	static void ResolveBackmessages();
	//*** Returns the next unused backmessage hash
	static unsigned NextBackMessage();
	//*** Sends the backmessage to the sender
	static void Backmessage(IPaddress sender,unsigned hash);
	//*** Fires at the end of each update
	//*** Sends all messages (UDP and TCP/RPC)
	static void SendAll();

	//*** All over-network registered entities
	//*** Each entity has it's own unique NetworkID
	static std::map<NetworkID, Entity*> RegisteredEntities;



	////*** Decodes recieved tcp data
	//static void RPC_Decode(UDPpacket* packet);
	////*** Decodes recieved tcp data
	//static void RPC_DecodeResolve(IPaddress sender, RPC_Receiver reciever, std::string foo, std::string args);
	////*** A Map of all RPC functions and their names
	//static std::map<std::string, std::pair<std::function<void(std::istream&)>, bool>> RPC_Map;
	////*** Contains all saved RPC which are called at client connection
	//static std::vector<std::string> RPC_Saved;
	////*** Regex applied to rpc functions
	//static std::regex RPC_Regex;
	////*** A function to help encode the RPC string parameter
	//static std::string stringInsert(std::string val)
	//{
	//	for (auto it = val.begin(); it != val.end(); ++it)
	//		if (*it == '|') { it = val.insert(it, '|'); it += 1; }
	//	val.push_back('|');
	//	return val;
	//}
	//static bool RPC(std::string& s, int r, decltype(RPC_Map.end()) foo);
	//template <typename K, typename ...T> static bool RPC(std::string& s, int r, decltype(RPC_Map.end()) foo, K&& val, T&&... args);
	//template <typename ...T, unsigned N> static bool RPC(std::string& s, int r, decltype(RPC_Map.end()) foo, const char(&val)[N], T&&... args)	{ s += (s.size() ? " " : "") + stringInsert(val); return RPC(s, r, foo, args...); }
	//template <typename ...T			   > static bool RPC(std::string& s, int r, decltype(RPC_Map.end()) foo, int& val, T&&... args)				{ s += (s.size() ? " " : "") + std::to_string(val); return RPC(s, r, foo, args...); }
	//template <typename ...T			   > static bool RPC(std::string& s, int r, decltype(RPC_Map.end()) foo, double& val, T&&... args)			{ s += (s.size() ? " " : "") + std::to_string(val); return RPC(s, r, foo, args...); }
	//template <typename ...T			   > static bool RPC(std::string& s, int r, decltype(RPC_Map.end()) foo, float& val, T&&... args)			{ s += (s.size() ? " " : "") + std::to_string(val); return RPC(s, r, foo, args...); }
	//template <typename ...T			   > static bool RPC(std::string& s, int r, decltype(RPC_Map.end()) foo, char& val, T&&... args)			{ s += (s.size() ? " " : "") + std::string(1, val); return RPC(s, r, foo, args...); }
	//template <typename ...T			   > static bool RPC(std::string& s, int r, decltype(RPC_Map.end()) foo, const char& val, T&&... args)		{ s += (s.size() ? " " : "") + std::string(1, val); return RPC(s, r, foo, args...); }
	//template <typename ...T			   > static bool RPC(std::string& s, int r, decltype(RPC_Map.end()) foo, unsigned& val, T&&... args)		{ s += (s.size() ? " " : "") + std::to_string(val); return RPC(s, r, foo, args...); }
	//template <typename ...T			   > static bool RPC(std::string& s, int r, decltype(RPC_Map.end()) foo, std::string& val, T&&... args)		{ s += (s.size() ? " " : "") + stringInsert(val); return RPC(s, r, foo, args...); }
	//template <typename ...T			   > static bool RPC(std::string& s, int r, decltype(RPC_Map.end()) foo, const char*& val, T&&... args)		{ s += (s.size() ? " " : "") + stringInsert(val); return RPC(s, r, foo, args...); }

	static void Update();
	friend class System;
	friend class State;
};

#include "Output_Handler.h"

//template<typename ...T>
//inline bool Network::RPC(RPC_Receiver reciever, std::string foo, T && ...args)
//{
//	//if (Network::networkState != NetworkState::NS_Connected) return false;
//	auto f = RPC_Map.find(foo);
//	if (f != RPC_Map.end())
//	{
//		std::string s;
//		return RPC(s, reciever, f, args...);
//	}
//	Output_Handler::Error << "ERR Network::RPC : No RPC function registered with given name\n";
//	return false;
//}
////
////
////template<typename F, typename...T>
////inline bool Network::RPC(F foo, T && ...args)
////{
////	if (Network::networkState == NetworkState::NS_Connected) return false;
////	for (auto f = RPC_Map.begin(); f != RPC_Map.end(); ++f)
////		if (getAddress(f->second) == getAddress(foo))
////		{
////			std::string s;
////			return RPC(s, f, args...);
////		}
////	Output_Handler::Error << "ERR Network::RPC : No RPC function registered with given name\n";
////	return false;
////}
//
//
//template<typename F>
//inline bool Network::RPC_Register(std::string name, F foo)
//{
//	if (RPC_Map.find(name) != RPC_Map.end()) return Output_Handler::OutputReturn("ERR Network::RegisterRPC : Name already taken\n", false);
//	RPC_Map[name] = std::pair<F, bool>(foo, false);
//	return true;
//}
//
//template<typename F>
//inline bool Network::RPC_RegisterStored(std::string name, F foo)
//{
//	if (RPC_Map.find(name) != RPC_Map.end()) return Output_Handler::OutputReturn("ERR Network::RPC_RegisterStored : Name already taken\n", false);
//	RPC_Map[name] = std::pair<F, bool>(foo, true);
//	return true;
//}
//
//
//
//template<typename K, typename ...T>
//inline bool Network::RPC(std::string& s, int r, decltype(RPC_Map.end()) foo, K&& val, T&& ...args)
//{
//	Output_Handler::Error << "ERR Network::RPC : unsupported value\n";
//	return false;
//}







