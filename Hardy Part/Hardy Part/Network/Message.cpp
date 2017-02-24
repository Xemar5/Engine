#include "Network.h"
#include "Message.h"
#include "Identifier.h"
#include "../State.h"

std::map<network::message::StorageIter, std::map<network::message::InnerStorageIter, network::message::Type>> network::message::messages;

void network::message::impl::_Send(std::vector<std::shared_ptr<Peer>> receivers, std::string state_name, InnerStorageIter message_name, std::string args)
{
	if (message_name.size() && receivers.size())
	{
		std::string s = state_name + " " + message_name + " " + args;
		for (auto r : receivers)
		{
			if (r) network::impl::tcp::peeding_messages.push_back({ std::to_string(r->ID()) + " " + s, r });
		}
	}
}
void network::message::impl::_Send(std::vector<std::shared_ptr<Peer>> receivers, std::shared_ptr<State> state, InnerStorageIter message_name, std::string args)
{
	_Send(receivers, state ? impl::_stringInsert(typeid(*state).raw_name()) : "|", message_name, args);
}
