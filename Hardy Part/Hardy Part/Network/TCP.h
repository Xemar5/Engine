#pragma once
#include "Message.h"
#include <string>
#include <map>
#include <boost\asio.hpp>

class State;
#undef SendMessage

namespace network
{
	class Client;
	class Server;
	class Serialised;

	namespace impl
	{
		namespace tcp
		{

			//*** The size of a single tcp packet
			//*** if a packet is too big, it will be cut into smaller ones
			constexpr size_t packet_size = 256;

			//*** The state received message is send to
			extern std::shared_ptr<State> received_message_state;


			namespace client
			{

				//*** Resolves client connection
				//*** Checks if given port is open on the supplied ip
				void AsyncClientResolve
				(
					const boost::system::error_code& error,
					boost::asio::ip::tcp::resolver::iterator it,
					std::shared_ptr<boost::asio::ip::tcp::resolver> resolver
				);
				//*** Tries to connect to given ip
				void AsyncConnectionRequest
				(
					std::shared_ptr<boost::asio::ip::tcp::socket> server_socket,
					const boost::system::error_code& error,
					boost::asio::ip::tcp::resolver::iterator ep
				);

				extern std::string server_ip;
				//*** Prepares and sends the message to the server / through the server to the receiver
				void SendMessage(std::string msg, std::shared_ptr<Peer> receiver);
				//*** Handles send response
				//*** if an error occures, tries again or disconnects from the server
				void AsyncSend
				(
					const boost::system::error_code& error,
					std::size_t len,
					std::shared_ptr<Peer> sender
				);
				//*** Awaits and decodes incomming server messages
				void AsyncRecv
				(
					const boost::system::error_code& error,
					std::shared_ptr<std::array<char, packet_size>> buf,
					std::size_t len,
					std::shared_ptr<Peer> sender
				);


			} //namespace client


			namespace server
			{

				//*** Handles the incoming connection from client
				void AsyncConnectHandler
				(
					const boost::system::error_code& error,
					std::shared_ptr<boost::asio::ip::tcp::socket> peedingClient
				);

				//*** Prepares and sends the message to the receiver
				void SendMessage(std::string msg, std::shared_ptr<Peer> receiver);
				//*** Handles send response
				//*** if an error occures, tries again or disconnects the client
				void AsyncSend
				(
					const boost::system::error_code& error,
					std::size_t len,
					std::shared_ptr<Peer> sender
				);
				//*** Awaits and decodes incomming clients' messages
				void AsyncRecv
				(
					const boost::system::error_code& error,
					std::shared_ptr<std::array<char, packet_size>> buf,
					std::size_t len,
					std::shared_ptr<Peer> sender
				);

			} //namespace server

			//*** Vector containing all messages ready to be sent
			//*** It is being cleared every time all messages has been sent
			extern std::vector<std::pair<std::string, std::shared_ptr<Peer>>> peeding_messages;
			//*** All received function calls
			extern std::vector<std::pair<std::function<void(std::istream&)>, std::shared_ptr<std::istream>>> received_function_calls;

			//*** Awaits an incomming message
			void ReceiveMessage();
			//*** Handles the received message
			void HandleReceivedMessage(std::string msg, std::shared_ptr<Peer> sender);

			namespace stored_messages
			{
				namespace client
				{

					//*** Called on client being rejected from the server
					void ConnectionDeclined();
					//*** Called on client being rejected from the server
					void ConnectionAccepted(unsigned id);

				} //namespace client

				namespace server
				{

					//*** Adds a new client and synchronises it
					void AddClient(std::shared_ptr<Peer> client);
					//*** Disconnects client
					void DisconnectClient(std::shared_ptr<Peer> peer);

				} //namespace server

			} //namespace message

			//*** Prepares given message
			//*** Returns a string ready to be send
			//*** Returns empty string if no package is to be sent
			std::string PrepareMessage(std::string& message);

			void Init();
			void Update();



		} //namespace tcp

	} //namespace impl

} //namespace network