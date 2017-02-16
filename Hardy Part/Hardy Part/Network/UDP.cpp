#include "UDP.h"
#include "Network.h"
#include "..\Output_Handler.h"
#include "Identifier.h"
#include "Peer.h"
#include "Message.h"

namespace network
{
	namespace impl
	{
		namespace udp
		{
			namespace client
			{
				void Join(std::string ip)
				{
					resolver = std::make_shared<boost::asio::ip::udp::resolver>(*service);
					boost::asio::ip::udp::resolver::query query{ boost::asio::ip::udp::v4(), ip, "daytime" };
					resolver->async_resolve(query, std::bind(AsyncClientResolve, std::placeholders::_1, std::placeholders::_2));
				}

				void AsyncClientResolve(const boost::system::error_code & err, boost::asio::ip::udp::resolver::iterator it)
				{
					if (err)
					{
						Output_Handler::Error << "ERR network::impl::udp::client::AsyncClientResolve : An error has occured: " << err << std::endl;
						Disconnect();
					}
					else
					{
						server_socket->endpoint = std::make_shared<boost::asio::ip::udp::endpoint>(it->endpoint().address(), default_port);
						udp::socket = std::make_shared<boost::asio::ip::udp::socket>(*service);
						boost::system::error_code ignored_error;
						auto id = my_socket->ID();
						//std::array<char, 1> send_buf = { { 0 } };
						std::array<char, sizeof(my_socket->ID())> send_buf = { { id & 0xff, (id >> 8) & 0xff, (id >> 16) & 0xff, (id >> 24) & 0xff } };
						udp::socket->open(boost::asio::ip::udp::v4(), ignored_error);
						udp::socket->send_to(boost::asio::buffer(send_buf), *server_socket->endpoint, 0, ignored_error);
						Output_Handler::Output << "MSG network::impl::udp::client::AsyncClientResolve : UDP Connection Initialized\n";
					}

				}

			} //namespace client

			namespace server
			{
				void Host()
				{
					using boost_udp = boost::asio::ip::udp;
					udp::socket = std::make_shared<boost_udp::socket>(*service, boost_udp::endpoint(boost_udp::v4(), default_port));
					Output_Handler::Output << "MSG network::impl::udp::server::Host : UDP Host Initialized\n";
				}

			} //namespace server


			std::shared_ptr<boost::asio::ip::udp::resolver> resolver = nullptr;
			std::shared_ptr<boost::asio::ip::udp::socket> socket = nullptr;
			bool reading = false;


			void SendData()
			{
				std::shared_ptr<std::string> buf = std::make_shared<std::string>();

				auto send = [&buf]
				{
					if (connection_type() == ConnectionType::Client)
					{
						udp::socket->async_send_to(boost::asio::buffer(*buf, packet_size), *server_socket->endpoint, std::bind(&SendHandler, std::placeholders::_1, std::placeholders::_2, server_socket->endpoint, buf));
					}

					else if (connection_type() == ConnectionType::Server)
						for (auto c : connections)
						{
							if (c->endpoint)
								udp::socket->async_send_to(boost::asio::buffer(*buf, buf->size()), *c->endpoint, std::bind(&SendHandler, std::placeholders::_1, std::placeholders::_2, c->endpoint, buf));
						}
				};

				for (auto s : object::Identifier::objects)
				{
					if (!s->synchronised()) continue;
					if (connection_type() == ConnectionType::Client && s->owner != my_socket) continue;

					auto data = message::impl::_stringInsert(s->GetData());
					if (buf->size() + data.size() > packet_size)
					{
						send();
						buf->clear();
					}

					*buf += data + " ";
				}
				if(buf->size())
					send();
			}

			void SendHandler(const boost::system::error_code & error, std::size_t bytes_transferred, std::shared_ptr<boost::asio::ip::udp::endpoint> sender, std::shared_ptr<std::string> buf)
			{
				if (error)
				{
					std::cout << "UDP error: " << error.message() << error << std::endl;
				}
				else if (!bytes_transferred) std::cout << "NO data was send\n";
				//else std::cout << "UDP package send!\n";
			}

			void RecvData()
			{
				if (!reading)
				{
					reading = true;
					std::shared_ptr<std::array<char, packet_size>> buf = std::make_shared<std::array<char, packet_size>>();
					std::shared_ptr<boost::asio::ip::udp::endpoint> ep = std::make_shared<boost::asio::ip::udp::endpoint>();
					udp::socket->async_receive_from(boost::asio::buffer(*buf, buf->size()), *ep, std::bind(&RecvHandler, std::placeholders::_1, std::placeholders::_2, ep, buf));
				}
			}

			void RecvHandler(const boost::system::error_code & error, std::size_t bytes_transferred, std::shared_ptr<boost::asio::ip::udp::endpoint> sender, std::shared_ptr<std::array<char, packet_size>> buf)
			{
				if (error)
				{
					std::cout << "ERROR: " << error.message() << error << std::endl;
				}
				else if (!bytes_transferred);// std::cout << "No UDP data received\n";
				else if (bytes_transferred == 4)
				{
					int id = (buf->at(0) << 0) | (buf->at(1) << 8) | (buf->at(2) << 16) | (buf->at(3) << 24);
					for (auto c : connections)
						if (c->ID() == id)
						{
							c->endpoint = sender;
							Output_Handler::Output << "MSG network::impl::udp::RecvHandler : Succesful assignment of Client[" << id << "] UDP endpoint\n";
						}

				}
				else
				{
					std::stringstream data(std::string(buf->data(), bytes_transferred));
					while(true)
					{
						auto str = message::impl::_stringRetrieve(data);
						if (!str.size()) break;
						std::stringstream ss (str);

						int id;
						if (ss >> id)
						{
							for (auto o : object::Identifier::objects)
								if (o->ID == id)
								{
									//std::cout << "recvd datat from " << id << std::endl;
									if (connection_type() == ConnectionType::Client && o->owner == my_socket)
										std::cout << "   THEY MESS MY DATA " << id << "\n";
									else
										o->SetData(ss);
									break;
								}
						}
					}

				}
				reading = false;
			}

			void Init()
			{
			}

			unsigned update_interval = 10;
			unsigned update_interval_countdown = 0;

			void Update()
			{
				if (udp::socket && _connection_status == ConnectionStatus::Connected)
				{
					if (++update_interval_countdown >= update_interval)
					{
						update_interval_countdown = 0;
						SendData();
					}
					RecvData();
				}
			}

		} //namespace udp

	} //namespace impl

} //namespace network