#include "Network.h"
#include "Client.h"
#include "TCP.h"
#include "UDP.h"

namespace network
{
	namespace impl
	{
		ConnectionStatus _connection_status = ConnectionStatus::Disconnected;
		ConnectionType _connection_type = ConnectionType::None;

		bool Init()
		{
			if (connection_type() != ConnectionType::None) return false;

			service = std::make_shared<boost::asio::io_service>();
			work = std::make_shared<boost::asio::io_service::work>(*service);

			tcp::Init();
			udp::Init();

			return true;
		}

	} //namespace impl

	namespace events
	{
		events::Event<std::shared_ptr<Peer>> OnClientConnected;
		events::Event<std::shared_ptr<Peer>> OnClientDisconnected;
		
		events::Event<> OnConnection;
		events::Event<> OnDisconnection;

	} //namespace events

	std::shared_ptr<Peer> my_socket = std::make_shared<Peer>(nullptr, nullptr);
	std::shared_ptr<Peer> server_socket = nullptr;
	std::vector<std::shared_ptr<Peer>> connections;
	std::shared_ptr<boost::asio::io_service> service = nullptr;
	std::shared_ptr<boost::asio::io_service::work> work = nullptr;
	const unsigned default_port = 40859;
	std::string ip = "127.0.0.1";

	void Update()
	{
		if (network::service && !network::service->stopped())
			network::service->poll();
		
		impl::tcp::Update();
		impl::udp::Update();
	}

	void Disconnect()
	{
		Output_Handler::Output << "MSG network::Disconnect : disconnecting from the server...\n";
		impl::_connection_status = ConnectionStatus::Disconnecting;
		impl::_connection_type = ConnectionType::None;

		impl::udp::resolver = nullptr;

		if (object::Identifier::SyncData::ID_count > 0)
			object::Identifier::SyncData::ID_count = -object::Identifier::SyncData::ID_count;

		for (auto nu : network::object::Identifier::objects)
			nu->owner = nullptr;

		connections.clear();
		my_socket = nullptr;
		server_socket = nullptr;

		work = nullptr;
		service->stop();
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

