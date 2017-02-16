#include "Peer.h"
#include "Network.h"
#include "Message.h"

namespace network
{
	int Peer::_ID_counter = 0;

	void Peer::Disconnect()
	{
		for (auto it = connections.begin(); it != connections.end(); ++it)
			if (it->get() == this)
			{
				auto peer = *it;
				connections.erase(it);
				if (network::connection_type() == ConnectionType::Server) message::Send(connections, "DisconnectClient", peer);
				break;
			}
		if (server_socket.get() == this) Disconnect();
		if (my_socket.get() == this) Disconnect();
	}
	Peer::~Peer()
	{
		if (socket && socket->is_open())
		{
			socket->shutdown(socket->shutdown_both);
			socket->close();
		}
	}
} //namespace network
