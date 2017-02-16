#pragma once
#include <boost\asio.hpp>


namespace network
{
	namespace impl { namespace tcp { namespace stored_messages { namespace client { void ConnectionAccepted(unsigned id); } } } }
	

	class Peer
	{
	public:
		Peer
		(
			std::shared_ptr<boost::asio::ip::tcp::socket> socket,
			std::shared_ptr<boost::asio::ip::udp::endpoint> endpoint
		) : socket(socket), endpoint(endpoint), _ID(-1) {}
		//*** Use only if server
		Peer
		(
			std::shared_ptr<boost::asio::ip::tcp::socket> socket,
			std::shared_ptr<boost::asio::ip::udp::endpoint> endpoint,
			unsigned id
		) : socket(socket), endpoint(endpoint), _ID(id) {}


		void Disconnect();

		std::shared_ptr<boost::asio::ip::tcp::socket> socket = nullptr;
		std::shared_ptr<boost::asio::ip::udp::endpoint> endpoint = nullptr;

		int ID() { return _ID; }
		bool synchronised() { return _ID >= 0; }
		bool reading = false;
		std::stringstream message;

		virtual ~Peer();

	private:
		int _ID = 0;
		static int _ID_counter;


		friend class Server;
		friend void impl::tcp::stored_messages::client::ConnectionAccepted(unsigned id);
	};

} //namespace network