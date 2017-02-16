#pragma once
#include "Event.h"

#include <memory>
#include <boost\asio.hpp>

namespace network
{
	class Peer;

	enum struct ConnectionStatus
	{
		Disconnected,
		Connecting,
		Connected,
		Disconnecting
	};
	enum struct ConnectionType
	{
		None,
		Server,
		Client
	};

	namespace impl
	{
		//*** initializes all main resources of the network system
		bool Init();
		//*** Current status of the connection
		extern ConnectionStatus _connection_status;
		//*** Current status of the connection
		extern ConnectionType _connection_type;

	} //namespace impl

	namespace events
	{
		extern events::Event<std::shared_ptr<Peer>> OnClientConnected;
		extern events::Event<std::shared_ptr<Peer>> OnClientDisconnected;

		extern events::Event<> OnConnection;
		extern events::Event<> OnDisconnection;

	} //namespace events


	class Peer;

	//*** My network data
	extern std::shared_ptr<Peer> my_socket;
	//*** Contains server data
	extern std::shared_ptr<Peer> server_socket;
	//*** Contains all connections data
	extern std::vector<std::shared_ptr<Peer>> connections;



	void Update();

	//*** Ends the network connection
	//*** If client - Disconnects from the server
	//*** If server - Closes all connections and shuts down the server
	void Disconnect();

	//*** The boost::asio::io_service
	//*** Handles the network system
	extern std::shared_ptr<boost::asio::io_service> service;
	//*** The boost::asio::io_service::work
	//*** Gives service something to do
	extern std::shared_ptr<boost::asio::io_service::work> work;
	//*** The default port server will use to start on
	//*** Client will try to connect to this port if not specified
	extern const unsigned default_port;
	//*** The default port server will use to start on
	//*** Client will try to connect to this port if not specified
	extern std::string ip;

	//*** Returns the current status of the connection
	ConnectionStatus connection_status();
	//*** Returns the current status of the connection
	ConnectionType connection_type();

} //namespace network



#include "Peer.h"
#include "Client.h"
#include "Server.h"
#include "Message.h"
#include "Identifier.h"

