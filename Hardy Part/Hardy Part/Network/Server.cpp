#include "Server.h"
#include "TCP.h"
#include "UDP.h"
#include "..\Output_Handler.h"
#include <boost\bind.hpp>

namespace network
{
	std::shared_ptr<boost::asio::ip::tcp::acceptor> Server::_acceptor = nullptr;
	unsigned Server::max_connections = 4;
	unsigned Server::_connections_counter = 1;

	void Server::Host()
	{
		if (connection_status() == ConnectionStatus::Disconnected)
		{
			impl::_connection_status = ConnectionStatus::Connecting;

			my_socket->socket = std::make_shared<boost::asio::ip::tcp::socket>(*service);
			my_socket->_ID = 0;
			_connections_counter = 1;
			object::Identifier::SyncData::ID_count = abs(object::Identifier::SyncData::ID_count);

			server_socket = my_socket;

			Server::_acceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(*network::service);
			if (!Server::AllowConnetions(true))
			{
				Disconnect();
				return;
			}
			impl::udp::server::Host();

			impl::_connection_status = ConnectionStatus::Connected;
			impl::_connection_type = ConnectionType::Server;

			events::OnConnection();
		}
	}

	void Server::Disconnect()
	{
		network::Disconnect();
	}

	bool Server::AllowConnetions(bool allow)
	{
		if (_acceptor)
		{
			if (!allow)
			{
				Output_Handler::Output << "MSG network::Server::AllowConnections : Connections disallowed\n";
				_acceptor->cancel();
				_acceptor->close();
			}
			else
			{
				boost::asio::ip::tcp::endpoint ep( boost::asio::ip::tcp::v4(), default_port );
				try
				{
					_acceptor->open(ep.protocol());
					_acceptor->bind(ep);
					_acceptor->listen();
				}
				catch (const std::exception&)
				{
					Output_Handler::Error << "ERR network::Server::AllowConnections : Cannot start the server; propably port already in use\n";
					return false;
				}
				std::shared_ptr<boost::asio::ip::tcp::socket> peeding_socket = std::make_shared<boost::asio::ip::tcp::socket>(*network::service);
				_acceptor->async_accept(*peeding_socket, boost::bind(&impl::tcp::server::AsyncConnectHandler, boost::asio::placeholders::error, peeding_socket));
				Output_Handler::Output << "MSG network::Server::AllowConnections : Connections allowed\n";
			}
			return allow;
		}
		return false;
	}

	ConnectionStatus Server::connection_status()
	{
		return ::network::connection_status();
	}

} //namespace network
