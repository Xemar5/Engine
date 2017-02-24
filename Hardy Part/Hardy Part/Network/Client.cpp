#include "Client.h"
#include "TCP.h"
#include "..\Output_Handler.h"
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <memory>

namespace network
{
	void Client::Join(std::string ip, unsigned port)
	{
		if (connection_status() == ConnectionStatus::Disconnected)
		{
			std::shared_ptr<boost::asio::ip::tcp::resolver> resolver = std::make_shared<boost::asio::ip::tcp::resolver>(*network::service);
			impl::tcp::client::server_ip = ip;
			boost::asio::ip::tcp::resolver::query query{ ip, std::to_string(port) };
			Output_Handler::Output << "MSG network::impl::tcp::Join : joining " << ip << ":" << std::to_string(port) << "...\n";

			resolver->async_resolve(query, boost::bind
			(
				&impl::tcp::client::AsyncClientResolve,
				boost::asio::placeholders::error,
				boost::asio::placeholders::iterator,
				resolver
			));
		}
	}

	void Client::Disconnect()
	{
		network::Disconnect();
	}

	ConnectionStatus Client::connection_status()
	{
		return ::network::connection_status();
	}

} //namespace network
