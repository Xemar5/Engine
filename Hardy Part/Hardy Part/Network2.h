#pragma once
#include <SDL_net.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <thread>

#define RPCreg(NAME) Network::RPCregister(#NAME, stream_function<decltype(NAME)>(NAME));
typedef void(*RPCfunction)(std::string arg);

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








//*** Functions responsible for RPC reflections
//*** Use with RPCreg / RPCregister and RPC

template<class R> struct invoker
{
	R result;
	template<class F, class... Args>
	invoker(F&& f, Args&&... args) : result(f(std::forward<Args>(args)...)) {}
};
template<> struct invoker<void>
{
	template<class F, class... Args>
	invoker(F&& f, Args&&... args)
	{
		f(std::forward<Args>(args)...);
	}
};
template<class F, class Sig> struct stream_function_;
template<class F, class R, class... Args> class stream_function_<F, R(Args...)>
{
public:
	stream_function_(F f) : _f(f) {}
	void operator()(std::istream& args) const { call(args, std::is_void<R>()); }

private:
	template<class T>
	static T get(std::istream& args)
	{
		T t; // must be default constructible
		if (!(args >> t))
		{
			args.clear();
			std::cout << "err";
			throw std::invalid_argument("invalid argument to stream_function");
		}
		return t;
	}
	template <> static std::string get<std::string> (std::istream& args)
	{
		std::string t, h;
		while (true)
		{
			std::getline(args, h, '|');
			t += h;
			if (args.get() != '|') break;
		}
		return t;
	}

	void call(std::istream& args, std::true_type) const
	{
		invoker<void>{_f, get<Args>(args)...};
	}
	F _f;
};
template<class Sig, class F> stream_function_<F, Sig> stream_function(F f) { return{ f }; }







class Network
{
public:
	//*** Initializes the Network class
	static void Init();

	//*** Sets this Game instance as a Host
	//*** This function creates new process and uses it
	//***    as a host each player can connect to
	static void Host();
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




	//*** Calls given function over the TCP connection
	//template <typename F, typename...T> static bool Network::RPC(F foo, T && ...args);
	template <typename F, typename...T> static bool Network::RPC(F foo, T && ...args) { std::cout << "lol"; return RPCcall<F, T...>::act(foo, args...); }
	//*** Calls given function over the TCP connection
	//template <typename ...T> static bool RPC<std::string, T>(std::string foo, T&&... args);
	//*** Registers an RPC function
	template <typename F> static bool RPCregister(std::string name, F foo);


private:
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
	//*** Current state of the network
	static void ReceiveUDP();
	//*** Fires at the end of each update
	//*** Sends all messages (UDP and TCP/RPC)
	static void SendAll();




	template<typename T, typename K, typename... U> struct getAddress
	{
		static size_t getAddressf(std::function<T(K, U...)> f) {
			typedef T(fnType)(K, U...);
			fnType ** fnPointer = f.template target<fnType*>();
			return (size_t)*fnPointer;
		}
	};
	template<typename T, typename... U > struct getAddress<T, std::string, U...>
	{
		static size_t getAddressf(std::function<T(std::string, U...)> f) {
			typedef T(fnType)(std::string, U...);
			fnType ** fnPointer = f.template target<fnType*>();
			return (size_t)*fnPointer;
		}
	};
	template <typename K, typename ...T> struct RPCcall
	{ 
		static bool act(K foo, T && ...args)
		{
			if (Network::networkState == NetworkState::NS_Connected) return false;
			for (auto f = RPCmap.begin(); f != RPCmap.end(); ++f)
				if (getAddress<K>::getAddressf(f->second) == getAddress<K>::getAddressf(foo))
				{
					std::string s;
					return RPC(s, f, args...);
				}
			Output_Handler::Error << "ERR Network::RPC : No RPC function registered with given name\n";
			return false;
		}
	};
	template <typename ...T> struct RPCcall<std::string, T...> 
	{
		static bool act(std::string f, T && ...args)
		{
			if (Network::networkState == NetworkState::NS_Connected) return false;
			auto f = RPCmap.find(foo);
			if (f != RPCmap.end())
			{
				std::string s;
				return RPC(s, f, args...);
			}
			Output_Handler::Error << "ERR Network::RPC : No RPC function registered with given name\n";
			return false;
		}
	};

	//*** Decodes recieved tcp data
	static void RPCdecode(UDPpacket* packet);
	//*** A Map of all RPC functions and their names
	static std::map<std::string, std::function<void(std::istream&)>> RPCmap;
	//*** Regex applied to rpc functions
	static std::regex RPCregex;
	//*** A function to help encode the RPC string parameter
	static std::string stringInsert(std::string val)
	{
		for (auto it = val.begin(); it != val.end(); ++it)
			if (*it == '|') { it = val.insert(it, '|'); it += 1; }
		val.push_back('|');
		return val;
	}
	template <typename K, typename ...T> static bool RPC(std::string& s, decltype(RPCmap.end()) foo, K&& val, T&&... args);
	template <typename ...T> static bool RPC(std::string& s, decltype(RPCmap.end()) foo, int& val, T&&... args) { s += (s.size() ? " " : "") + std::to_string(val); return RPC(s, foo, args...); }
	template <typename ...T> static bool RPC(std::string& s, decltype(RPCmap.end()) foo, double& val, T&&... args) { s += (s.size() ? " " : "") + std::to_string(val); return RPC(s, foo, args...); }
	template <typename ...T> static bool RPC(std::string& s, decltype(RPCmap.end()) foo, float& val, T&&... args) { s += (s.size() ? " " : "") + std::to_string(val); return RPC(s, foo, args...); }
	template <typename ...T> static bool RPC(std::string& s, decltype(RPCmap.end()) foo, char& val, T&&... args) { s += (s.size() ? " " : "") + std::string(1, val); return RPC(s, foo, args...); }
	template <typename ...T> static bool RPC(std::string& s, decltype(RPCmap.end()) foo, const char& val, T&&... args) { s += (s.size() ? " " : "") + std::string(1, val); return RPC(s, foo, args...); }
	template <typename ...T> static bool RPC(std::string& s, decltype(RPCmap.end()) foo, unsigned& val, T&&... args) { s += (s.size() ? " " : "") + std::to_string(val); return RPC(s, foo, args...); }
	template <typename ...T> static bool RPC(std::string& s, decltype(RPCmap.end()) foo, std::string& val, T&&... args) { s += (s.size() ? " " : "") + stringInsert(val); return RPC(s, foo, args...); }
	template <typename ...T> static bool RPC(std::string& s, decltype(RPCmap.end()) foo, const char*& val, T&&... args) { s += (s.size() ? " " : "") + stringInsert(val); return RPC(s, foo, args...); }
	template <typename ...T, unsigned N> static bool RPC(std::string& s, decltype(RPCmap.end()) foo, const char(&val)[N], T&&... args) { s += (s.size() ? " " : "") + stringInsert(val); return RPC(s, foo, args...); }
	static bool RPC(std::string& s, decltype(RPCmap.end()) foo);

	static void Update();
	friend class System;
};

#include "Output_Handler.h"

//template<typename ...T>
//inline bool Network::RPC(std::string foo, T && ...args)
//{
//	if (Network::networkState == NetworkState::NS_Connected) return false;
//	auto f = RPCmap.find(foo);
//	if (f != RPCmap.end())
//	{
//		std::string s;
//		return RPC(s, f, args...);
//	}
//	Output_Handler::Error << "ERR Network::RPC : No RPC function registered with given name\n";
//	return false;
//}
//
//
//template<typename F, typename...T>
//inline bool Network::RPC(F foo, T && ...args)
//{
//	if (Network::networkState == NetworkState::NS_Connected) return false;
//	for (auto f = RPCmap.begin(); f != RPCmap.end(); ++f)
//		if (getAddress(f->second) == getAddress(foo))
//		{
//			std::string s;
//			return RPC(s, f, args...);
//		}
//	Output_Handler::Error << "ERR Network::RPC : No RPC function registered with given name\n";
//	return false;
//}

template<typename F>
inline bool Network::RPCregister(std::string name, F foo)
{
	if (RPCmap.find(name) != RPCmap.end()) Output_Handler::OutputReturn("ERR Network::RegisterRPC : Name already taken\n", false);
	RPCmap[name] = foo;
	return true;
}



template<typename K, typename ...T>
inline bool Network::RPC(std::string& s, decltype(RPCmap.end()) foo, K&& val, T&& ...args)
{
	Output_Handler::Error << "ERR Network::RPC : unsupported value\n";
	return false;
}







