#include "Peer.h"
#include "Network.h"
#include "Message.h"

namespace network
{
	void Peer::Disconnect()
	{
		for (auto it = connections.begin(); it != connections.end(); ++it)
			if (it->get() == this)
			{
				auto peer = *it;
				for (auto ids : object::Identifier::objects)
					if (ids->owner == peer) ids->owner = nullptr;
				connections.erase(it);
				if (network::connection_type() == ConnectionType::Server) message::Send(connections, nullptr, "DisconnectClient", peer);
				break;
			}
		if (server_socket.get() == this) Disconnect();
		if (my_socket.get() == this) Disconnect();
	}
	bool Peer::is_host()
	{
		return this == server_socket.get();
	}

	Peer::~Peer()
	{
		std::cout << "~Peer [" << _ID << "]\n";
	}
} //namespace network
