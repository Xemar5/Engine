#include "Network.h"
#include "Message.h"
#include "Identifier.h"

std::map<network::message::StorageIter, std::map<std::string, network::message::Type>> network::message::messages;
