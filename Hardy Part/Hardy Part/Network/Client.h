#pragma once
#include "Network.h"
#include "Peer.h"
#include <iostream>
#include <memory>
#include <boost\asio.hpp>

namespace network
{

	class Client
	{
	public:
		Client() = delete;


		//*** Tries to connect to server with given ip
		//*** Check connection_status() if the connection succeded
		static void Join(std::string ip, unsigned port);
		
		//*** Disconnects from the server
		static void Disconnect();

		//*** returns the current status of the connection
		//*** Use with network::Client::Join and network::Server::Host
		static ConnectionStatus connection_status();


	private:


		friend void Disconnect();
	};

} //namespace network