#include "TCP.h"
#include "Network.h"
#include "..\Output_Handler.h"
#include "Server.h"
#include "Peer.h"
#include "UDP.h"
#include <memory>
#include <boost\asio.hpp>
#include <boost\bind.hpp>
#include <boost/algorithm/string.hpp>


typedef boost::asio::ip::tcp boost_tcp;

namespace network
{
	namespace impl
	{
		namespace tcp
		{
			namespace client
			{
				std::string server_ip;

				void AsyncClientResolve(const boost::system::error_code& error, boost_tcp::resolver::iterator it, std::shared_ptr<boost_tcp::resolver> resolver)
				{
					if (error) Output_Handler::Error
						<< "ERR network::impl::tcp::_AsyncClientResolve : An error has occured during server resolving: "
						<< error << " [" << error.message() << "]\n";
					else
					{
						std::shared_ptr<boost::asio::ip::tcp::socket> srv_soc = std::make_shared<boost::asio::ip::tcp::socket>(*network::service);
						boost::asio::async_connect(*srv_soc, it, boost::bind(&AsyncConnectionRequest, srv_soc, boost::asio::placeholders::error, boost::asio::placeholders::iterator));
					}
				}

				void AsyncConnectionRequest(std::shared_ptr<boost::asio::ip::tcp::socket> server_socket, const boost::system::error_code& error, boost::asio::ip::tcp::resolver::iterator ep)
				{
					if (error)
					{
						Output_Handler::Error << "ERR network::impl::tcp::AsyncConnectionRequest : Connection declined\n";
						Disconnect();
					}
					else
					{
						impl::_connection_status = ConnectionStatus::Connecting;
						network::server_socket = std::make_shared<Peer>(server_socket, nullptr, 0);
						my_socket->socket = std::make_shared<boost::asio::ip::tcp::socket>(*service);
						Output_Handler::Output << "MSG network::impl::tcp::AsyncConnectionRequest : Connection reached; awaiting allowance...\n";
					}
				}


				void SendMessage(std::string msg, std::shared_ptr<Peer> receiver)
				{
					std::string s;
					while ((s = PrepareMessage(msg)).size())
					{
						network::server_socket->socket->async_send
						(
							boost::asio::buffer(s.data(), s.size()),
							boost::bind(&AsyncSend, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, server_socket)
						);
						if (s[0] == 0) break;
					}
				}

				void AsyncSend(const boost::system::error_code & error, std::size_t len, std::shared_ptr<Peer> sender)
				{
					if (error)
					{
						if (error == boost::asio::error::connection_reset) std::cout << "Server has restarted connection\n";
						else std::cout << "An error has occured during packet sending (" << error << "): " << error.message() << std::endl;
					}
					else
					{
						//Output_Handler::Output << "MSG network::impl::tcp::client::AsyncSend : Package sent!\n";
					}
				}
				void AsyncRecv(const boost::system::error_code & error, std::shared_ptr<std::array<char, packet_size>> buf, std::size_t len, std::shared_ptr<Peer> sender)
				{
					if (error)
					{
						if (error == boost::asio::error::eof)
						{
							Output_Handler::Output << "MSG network::impl::tcp::client::AsyncRecv : Disconnected by the Server\n";
							Disconnect();
						}
						else if (error == boost::asio::error::timed_out || error == boost::asio::error::operation_aborted)
						{
							Output_Handler::Output << "MSG network::impl::tcp::client::AsyncRecv : Connection timeout; Server stopped responding\n";
							Disconnect();
						}
						else if (error == boost::asio::error::connection_reset)
						{
							Output_Handler::Output << "MSG network::impl::tcp::client::AsyncRecv : Disconnected by the server\n";
							Disconnect();
						}
						else
						{
							Output_Handler::Output << "MSG network::impl::tcp::client::AsyncRecv : Other Read error: " << error << ": " << error.message() << std::endl;
							//sendingSocket->timeout(sendingSocket->timeout() - 1);
							//if (sendingSocket->timeout() < 0)
							//{
							//	std::cout << "Connection timeout; Server stopped responding\n";
								Disconnect();
							//}
						}
					}
					else if (!len)
					{
						std::cout << "ERR network::impl::tcp::server::AsyncRecv : Recieved message has length of 0\n";
					}
					else
					{
						std::string rcvd = std::string(buf->data(), len);
						std::string str = rcvd;
						str.erase(std::remove(str.begin(), str.end(), '\0'), str.end());
						std::cout << "MSG network::impl::tcp::client::AsyncRecv : message received:\n [" << str << "]\n";
						HandleReceivedMessage(rcvd, sender);
					}
					sender->reading = false;
				}
			} //namespace client



			namespace server
			{
				void AsyncConnectHandler(const boost::system::error_code& error, std::shared_ptr<boost::asio::ip::tcp::socket> peedingClient)
				{
					Output_Handler::Output << "MSG network::impl::tcp::server::AsyncConnectHandler : Resolving connection... ";
					if (!error)
					{
						if (connections.size() >= Server::max_connections)
						{
							Output_Handler::Output << "Client Declined\n";
							peedingClient->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
							peedingClient->close();
						}
						else
						{
							std::shared_ptr<Peer> peer = std::make_shared<Peer>(peedingClient, nullptr, Server::_connections_counter++);
							auto ep = peedingClient->remote_endpoint();
							Output_Handler::Output << "Client (" << ep.address() << ":" << ep.port() << ") Connected [ID:" << peer->ID() << "]\n";
							message::Send({ peer }, nullptr, "ConnectionAccepted", peer->ID());
							message::Send(connections, nullptr, "AddClient", peer);
							for(auto c : connections)
								message::Send({ peer }, nullptr, "AddClient", c);
							connections.push_back(peer);

							events::OnClientConnected(peer);
						}
						peedingClient = std::make_shared<boost::asio::ip::tcp::socket>(*network::service);
						Server::_acceptor->async_accept(*peedingClient, boost::bind(&AsyncConnectHandler, boost::asio::placeholders::error, peedingClient));
					}
					else
					{
						Output_Handler::Output << "An error has occured during connection handling: " << error.message() << error << std::endl;
					}
				}

				void SendMessage(std::string msg, std::shared_ptr<Peer> receiver)
				{
					std::string s;
					while ((s = PrepareMessage(msg)).size())
					{
						receiver->socket->async_send
						(
							boost::asio::buffer(s.data(), s.size()),
							boost::bind(&AsyncSend, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, receiver)
						);
						if (s[0] == 0) break;
					}
				}
				void AsyncSend(const boost::system::error_code & error, std::size_t len, std::shared_ptr<Peer> sender)
				{
					if (error)
					{
						if (error == boost::asio::error::connection_reset) std::cout << "Send unavailable: Client has restarted connection\n";
						else std::cout << "An error has occured during packet sending (" << error << "): " << error.message() << std::endl;

					}
					else
					{
						//Output_Handler::Output << "MSG network::impl::tcp::server::AsyncSend : Package sent!\n";
					}
				}
				void AsyncRecv(const boost::system::error_code & error, std::shared_ptr<std::array<char, packet_size>> buf, std::size_t len, std::shared_ptr<Peer> sender)
				{
					if (error)
					{
						if (error == boost::asio::error::eof)
						{
							Output_Handler::Output << "MSG network::impl::tcp::server::AsyncRecv : Client [" << sender->ID() << "] has disconnected\n";
							sender->Disconnect();
						}
						else if (error == boost::asio::error::timed_out || error == boost::asio::error::operation_aborted)
						{
							Output_Handler::Output << "MSG network::impl::tcp::server::AsyncRecv : Connection timeout; Client [" << sender->ID() << "] stopped responding\n";
							sender->Disconnect();
						}
						else if (error == boost::asio::error::connection_reset)
						{
							Output_Handler::Output << "MSG network::impl::tcp::server::AsyncRecv : Receive unavailable: Client [" << sender->ID() << "] has restarted connection\n";
							sender->Disconnect();
						}
						else if (error)
						{
							Output_Handler::Output << "MSG network::impl::tcp::server::AsyncRecv : Other Client [" << sender->ID() << "] Read error: " << error.message() << std::endl;
							sender->Disconnect();
							//sendingSocket->timeout(sendingSocket->timeout() - 1);
							//if (sendingSocket->timeout() <= 0)
							//{
							//	std::cout << "Connection timeout; Peer stopped responding\n";
							//	_disconnectClient(it);
							//}
						}
					}
					else if (!len)
					{
						std::cout << "ERR network::impl::tcp::server::AsyncRecv : Recieved message has length of 0\n";
					}
					else
					{
						std::string rcvd = std::string(buf->data(), len);
						std::string str = rcvd;
						str.erase(std::remove(str.begin(), str.end(), '\0'), str.end());
						std::cout << "MSG network::impl::tcp::server::AsyncRecv : message received:\n [" << str << "]\n";
						HandleReceivedMessage(rcvd, sender);
					}
					sender->reading = false;
				}
			} //namespace server


			namespace stored_messages
			{
				namespace client
				{
					void ConnectionDeclined()
					{
						Output_Handler::Output << "MSG network::impl::tcp::client::ConnectionDeclined : Connection Declined\n";
						Disconnect();
					}

					void ConnectionAccepted(unsigned id)
					{
						Output_Handler::Output << "MSG network::impl::tcp::client::ConnectionAccepted : Connected; my ID: " << id << "\n";
						my_socket->_ID = id;
						udp::client::Join(impl::tcp::client::server_ip);
						_connection_status = ConnectionStatus::Connected;
						_connection_type = ConnectionType::Client;

						//for (auto id : object::Identifier::objects)
						//	network::impl::tcp::peeding_messages.push_back({ std::to_string(server_socket->ID()) + " MakeRequest " + std::to_string(id->owner->ID()) + " " + std::to_string(id->ID) + " " + id->on_client_connect, server_socket });

						events::OnConnection();
					}
				} //namespace client

				namespace server
				{
					void AddClient(std::shared_ptr<Peer> client)
					{
						Output_Handler::Output << "MSG network::impl::tcp::stored_messages::server::AddClient : client [" << client->ID() << "] added\n";
						connections.push_back(client);
						events::OnClientConnected(client);
					}

					void DisconnectClient(std::shared_ptr<Peer> peer)
					{
						Output_Handler::Output << "MSG network::impl::tcp::stored_messages::server::DisconnectClient : client [" << peer->ID() << "] disconnected\n";
						events::OnClientDisconnected(peer);
						peer->Disconnect();
					}

				} //namespace server

			} //namespace stored_messages

			std::vector<std::pair<std::string, std::shared_ptr<Peer>>> peeding_messages;
			std::vector<std::pair<message::Type, std::shared_ptr<std::istream>>> received_function_calls;

			void Init()
			{
				auto sp = State::_state_phase;
				State::_state_phase = State::Phase::StateCreate;

				message::impl::system::SystemStore(stored_messages::client::ConnectionDeclined, "ConnectionDeclined");
				message::impl::system::SystemStore(stored_messages::client::ConnectionAccepted, "ConnectionAccepted");
				message::impl::system::SystemStore(stored_messages::server::DisconnectClient, "DisconnectClient");
				message::impl::system::SystemStore(stored_messages::server::AddClient, "AddClient");

				message::impl::system::SystemStore(object::impl::SyncObject, "SyncObject");
				message::impl::system::SystemStore(object::impl::MakeRequest, "MakeRequest");

				State::_state_phase = sp;
			}

			void Update()
			{
				if (_connection_status == ConnectionStatus::Connected)
				{
					for (auto s : peeding_messages)
					{
						if (connection_type() == ConnectionType::Client) client::SendMessage(s.first, s.second);
						if (connection_type() == ConnectionType::Server) server::SendMessage(s.first, s.second);
					}
					peeding_messages.clear();

				}
				ReceiveMessage();
				for (auto f : received_function_calls)
					if (f.first)
						f.first(*f.second);
				received_function_calls.clear();
			}

			std::string PrepareMessage(std::string & message)
			{
				std::string buf(packet_size, '\0');
				std::size_t sz = buf.size() - 1;

				buf.replace
				(
					buf.begin() + 1,
					message.size() > sz ? buf.end() : buf.begin() + 1 + message.size(),
					message.begin(),
					message.size() > sz ? message.begin() + sz : message.end()
				);


				if (message.size() > sz)
				{
					message = message.substr(sz, message.size() - sz);
					buf[0] = 1;
				}
				else
				{
					buf[0] = 0;
				}

				return buf;
			}

			void ReceiveMessage()
			{
				if (_connection_type == ConnectionType::Server)
				{
					for (auto p : network::connections)
						if (!p->reading)
						{
							p->reading = true;
							std::shared_ptr<std::array<char, packet_size>> buf = std::make_shared<std::array<char, packet_size>>();
							p->socket->async_read_some(boost::asio::buffer(*buf, buf->size()),
								boost::bind(&server::AsyncRecv, boost::asio::placeholders::error, buf, boost::asio::placeholders::bytes_transferred, p)
							);
						}
				}
				else if (_connection_type == ConnectionType::Client || _connection_status == ConnectionStatus::Connecting)
				{
					if (server_socket && !server_socket->reading)
					{
						server_socket->reading = true;
						std::shared_ptr<std::array<char, packet_size>> buf = std::make_shared<std::array<char, packet_size>>();
						server_socket->socket->async_read_some(boost::asio::buffer(*buf, buf->size()),
							boost::bind(&client::AsyncRecv, boost::asio::placeholders::error, buf, boost::asio::placeholders::bytes_transferred, server_socket)
						);
					}
				}
			}

			void HandleReceivedMessage(std::string msg, std::shared_ptr<Peer> sender)
			{
				char completed = msg[0];
				msg = msg.substr(1, msg.size() - 1);
				sender->message << msg;

				if (completed == 0)
				{
					int receiver = -1;

					sender->message >> receiver;

					sender->message.ignore(1);
					std::string state_name;
					std::getline(sender->message, state_name, '|');
					sender->message.ignore(1);

					std::vector<std::pair<message::Type, std::shared_ptr<std::istream>>>* received_function_calls_container = nullptr;
					if (state_name.empty())
						received_function_calls_container = &received_function_calls;
					else
						for (auto state : State::Built)
							if (typeid(*state).raw_name() == state_name)
								received_function_calls_container = &state->received_function_calls;

					if (receiver != my_socket->ID() || received_function_calls_container)
					{
						std::string foo_name;
						sender->message >> foo_name;
						std::string msg;
						std::getline(sender->message, msg);


						if (_connection_type == ConnectionType::Server && receiver != my_socket->ID())
						{
							std::shared_ptr<Peer> r;
							boost::trim_right_if(msg, [](char c) { return c == '\0' || c == ' '; });
							for (unsigned i = 0; i < connections.size(); ++i)
								if (connections[i]->ID() == receiver) r = connections[i];
							message::impl::_Send({ r }, state_name + '|', foo_name, msg);
						}
						else if (receiver == my_socket->ID() || !my_socket->synchronised())
						{
							auto f = message::impl::_Get(foo_name, 0);
							if (!f) f = message::impl::_Get(foo_name, 1);

							received_function_calls_container->push_back({ f,std::make_shared<std::stringstream>(msg) });

						}
					}
					else
					{
						Output_Handler::Output << "MSG network::impl::tcp::HandleReceivedMessage : State not found\n [" << state_name << "]\n";
					}
					sender->message.str(std::string());
					sender->message.clear();
				}

			}

		} //namespace tcp

	} //namespcae impl

} //namespace network

