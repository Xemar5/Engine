#pragma once
#include "Network.h"
#include "TCP.h"

namespace network
{

	class Server final
	{
	public:
		Server() = delete;

		//*** Starts the server
		static void Host();

		//*** Closes all connections and shuts down the server
		static void Disconnect();

		//*** Allows or disallows new connections
		static bool AllowConnetions(bool allow);

		//*** returns the current status of the connection
		//*** Use with network::Client::Join and network::Server::Host
		static ConnectionStatus connection_status();

		//*** The maximum number of players
		static unsigned max_connections;

	private:

		//*** Counts the id of the newest client
		static unsigned _connections_counter;

		//*** Handles all incomming connections
		static std::shared_ptr<boost::asio::ip::tcp::acceptor> _acceptor;

		friend void impl::tcp::server::AsyncConnectHandler(const boost::system::error_code& error, std::shared_ptr<boost::asio::ip::tcp::socket> peedingClient);
	};

} //namespace network