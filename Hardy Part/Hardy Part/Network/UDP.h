#pragma once
#include <string>
#include <memory>
#include <boost\asio.hpp>


namespace network
{
	namespace impl
	{
		namespace udp
		{
			//*** The size of a single udp packet
			//*** if a packet is too big, it will be cut into smaller ones
			constexpr size_t packet_size = 256;


			namespace client
			{
				//*** Creates udp connection
				void Join(std::string ip);
				//*** Handles udp connsection resolving
				void AsyncClientResolve(std::shared_ptr<boost::asio::ip::udp::resolver> resolver, const boost::system::error_code & err, boost::asio::ip::udp::resolver::iterator it);

			} //namespace client

			namespace server
			{
				//*** Creates udp connection acceptor
				void Host();

			} //namespace server

			//*** Handles udp connection
			extern std::shared_ptr<boost::asio::ip::udp::socket> socket;
			//*** If true, system is awaiting an incomming UDP data
			extern bool reading;

			//*** Gathers data from all owned network::Unit and sends it to others
			void SendData();
			//*** Handles data sending
			void SendHandler(const boost::system::error_code& error, std::size_t bytes_transferred, std::shared_ptr<boost::asio::ip::udp::endpoint> sender, std::shared_ptr<std::string> buf);
			//*** Receives data from all non-owned network::Unit and updates their serialised values
			void RecvData();
			//*** Updates all network::Unit with received data
			void RecvHandler(const boost::system::error_code& error, std::size_t bytes_transferred, std::shared_ptr<boost::asio::ip::udp::endpoint> sender, std::shared_ptr<std::array<char, packet_size>> buf);


			//*** The time in which udp update function will be called
			extern unsigned update_interval;
			//*** How much time in program ticks is left for udp Update func to be called
			extern unsigned update_interval_countdown;

			void Init();
			void Update();


		} //namespace udp

	} //namespace impl

} //namespace network