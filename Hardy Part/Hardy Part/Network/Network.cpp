#include "Network.h"
#include "Client.h"
#include "TCP.h"
#include "UDP.h"

namespace network
{
	namespace impl
	{
		bool initialized = false;
		bool stopped = true;
		bool stop_requested = false;
		ConnectionStatus _connection_status = ConnectionStatus::Disconnected;
		ConnectionType _connection_type = ConnectionType::None;

		void Init()
		{
			if (initialized) return;
			initialized = true;

			service = std::make_shared<boost::asio::io_service>();
			work = std::make_shared<boost::asio::io_service::work>(*service);
			my_socket = std::make_shared<Peer>(nullptr, nullptr);
			stopped = false;

			tcp::Init();
			udp::Init();
		}

		void Exit()
		{
			if (!service) return;
			Disconnect();

			impl::stop_requested = true;
			service->stop();
			while (!impl::stopped)
			{
				SDL_Delay(1);
				Update();
			}
			work.reset();
			service.reset();
			my_socket.reset();
		}

	} //namespace impl

	namespace events
	{
		events::Event<std::shared_ptr<Peer>> OnClientConnected;
		events::Event<std::shared_ptr<Peer>> OnClientDisconnected;
		
		events::Event<> OnConnection;
		events::Event<> OnDisconnection;

	} //namespace events

	std::shared_ptr<Peer> my_socket = nullptr;
	std::shared_ptr<Peer> server_socket = nullptr;
	std::vector<std::shared_ptr<Peer>> connections;
	std::shared_ptr<boost::asio::io_service> service = nullptr;
	std::shared_ptr<boost::asio::io_service::work> work = nullptr;
	const unsigned default_port = 40859;
	std::string ip = "127.0.0.1";

	void Update()
	{
		if (!impl::stopped)
		{
			network::service->poll();

			if (impl::stop_requested)
			{
				impl::stopped = true;
			}
			else
			{
				impl::tcp::Update();
				impl::udp::Update();
			}
		}
	}

	void Disconnect()
	{
		if (impl::_connection_status == ConnectionStatus::Disconnecting) return;
		Output_Handler::Output << "MSG network::Disconnect : disconnecting from the server...\n";
		impl::_connection_status = ConnectionStatus::Disconnecting;
		impl::_connection_type = ConnectionType::None;


		Server::AllowConnetions(false);

		boost::system::error_code e;
		object::Identifier::SyncData::ID_count = -abs(object::Identifier::SyncData::ID_count);

		int off = 0;
		for (auto nu : network::object::Identifier::objects)
			if (nu)
			{
				if (nu->ID < 0) ++off;
				else nu->ID = -abs(nu->ID + off);

				if(nu->owner != my_socket)
					nu->owner = nullptr;
			}

		if (impl::udp::socket)
		{
			impl::udp::socket->shutdown(boost::asio::ip::udp::socket::shutdown_both, e);
			impl::udp::socket->close(e);
			impl::udp::socket.reset();
		}

		for (auto c : connections)
		{
			if (c->socket)
			{
				c->socket->shutdown(boost::asio::ip::udp::socket::shutdown_both, e);
				c->socket->close(e);
				c->socket.reset();
			}
			c->endpoint.reset();
		}
		connections.clear();

		if (server_socket)
		{
			if (server_socket->socket)
			{
				server_socket->socket->shutdown(boost::asio::ip::udp::socket::shutdown_both, e);
				server_socket->socket->close(e);
			}
			server_socket.reset();
		}
		if (my_socket)
		{
			if (my_socket->socket)
			{
				my_socket->socket->shutdown(boost::asio::ip::udp::socket::shutdown_both, e);
				my_socket->socket->close(e);
				my_socket->socket.reset();
			}
			my_socket->endpoint.reset();
			my_socket->_ID = -1;
		}




		//if (my_socket && my_socket->socket)
		//{
		//	boost::system::error_code ec;
		//	my_socket->socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
		//	if (ec) std::cout << "ERR my_socket->socket->shutdown : " << ec.message() << std::endl;
		//	my_socket->socket->close(ec);
		//	if (ec) std::cout << "ERR my_socket->socket->close : " << ec.message() << std::endl;
		//}
		//my_socket->reset();

		//if (server_socket && server_socket->socket)
		//{
		//	boost::system::error_code ec;
		//	server_socket->socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
		//	if (ec) std::cout << "ERR server_socket->socket->shutdown : " << ec.message() << std::endl;
		//	server_socket->socket->close(ec);
		//	if (ec) std::cout << "ERR server_socket->socket->close : " << ec.message() << std::endl;
		//}
		//server_socket = nullptr;

		//work = nullptr;
		//if(service)
		//	service->stop();
		//service = nullptr;

		//TODO add disconnecting logic
		impl::_connection_status = ConnectionStatus::Disconnected;

		events::OnDisconnection();
	}

	ConnectionStatus connection_status()
	{
		return impl::_connection_status;
	}

	ConnectionType connection_type()
	{
		return impl::_connection_type;
	}

} //namespace network

