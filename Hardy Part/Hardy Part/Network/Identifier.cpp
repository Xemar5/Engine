#include "Identifier.h"
#include "Network.h"


namespace network
{
	namespace object
	{
		int Identifier::SyncData::ID_count = 0;
		std::vector<std::shared_ptr<Identifier::SyncData>> Identifier::objects;

		Identifier::SyncData::SyncData(int id) : _identifier(nullptr), ID(id)
		{
			_onClientConnectedIter = events::OnClientConnected += std::bind(&SyncData::_OnClientConnected, this, std::placeholders::_1);
			_onConnectionIter = events::OnConnection += std::bind(&SyncData::_OnConnection, this);
		}
		std::string Identifier::SyncData::GetData()
		{
			if (!this->synchronised()) return"";
			std::string data = std::to_string(ID);
			for (auto v : this->serialised)
				switch (v.which())
				{
				case 0: if (auto val = boost::get<int*>(v))			data += " " + std::to_string(*val); break;
				case 1: if (auto val = boost::get<char*>(v))		data += " " + std::to_string(*val); break;
				case 2: if (auto val = boost::get<unsigned*>(v))	data += " " + std::to_string(*val); break;
				case 3: if (auto val = boost::get<double*>(v))		data += " " + std::to_string(*val); break;
				case 4: if (auto val = boost::get<float*>(v))		data += " " + std::to_string(*val); break;
				case 5: if (auto val = boost::get<std::string*>(v))	data += " " + message::impl::_stringInsert(*val); break;

				case 6: if (auto val = boost::get<std::shared_ptr<int>>(v))			data += " " + std::to_string(*val); break;
				case 7: if (auto val = boost::get<std::shared_ptr<char>>(v))		data += " " + std::to_string(*val); break;
				case 8: if (auto val = boost::get<std::shared_ptr<unsigned>>(v))	data += " " + std::to_string(*val); break;
				case 9: if (auto val = boost::get<std::shared_ptr<double>>(v))		data += " " + std::to_string(*val); break;
				case 10:if (auto val = boost::get<std::shared_ptr<float>>(v))		data += " " + std::to_string(*val); break;
				case 11:if (auto val = boost::get<std::shared_ptr<std::string>>(v))	data += " " + message::impl::_stringInsert(*val); break;
				default: break;
				}
			if (_identifier)
			{
				_identifier->_sync_data->data_output.set(data);
				_identifier->DataSend(_identifier->_sync_data->data_output);
				_identifier->_sync_data->data_output.stream = nullptr;
			}
			return data;
		}

		void Identifier::SyncData::SetData(std::istream & data)
		{
			if (!this->synchronised()) return;
			for (auto v : this->serialised)
			{
				switch (v.which())
				{
				case 0: if (auto val = boost::get<int*>(v))			data >> *val; break;
				case 1: if (auto val = boost::get<char*>(v))		data >> *val; break;
				case 2: if (auto val = boost::get<unsigned*>(v))	data >> *val; break;
				case 3: if (auto val = boost::get<double*>(v))		data >> *val; break;
				case 4: if (auto val = boost::get<float*>(v))		data >> *val; break;
				case 5: if (auto val = boost::get<std::string*>(v)) *val = message::impl::_stringRetrieve(data); break;

				case 6: if (auto val = boost::get<std::shared_ptr<int>>(v))			data >> *val; break;
				case 7: if (auto val = boost::get<std::shared_ptr<char>>(v))		data >> *val; break;
				case 8: if (auto val = boost::get<std::shared_ptr<unsigned>>(v))	data >> *val; break;
				case 9: if (auto val = boost::get<std::shared_ptr<double>>(v))		data >> *val; break;
				case 10:if (auto val = boost::get<std::shared_ptr<float>>(v))		data >> *val; break;
				case 11:if (auto val = boost::get<std::shared_ptr<std::string>>(v))	*val = message::impl::_stringRetrieve(data); break;
				default: break;
				}
			}
			if (_identifier)
			{
				_identifier->_sync_data->data_input.set(data);
				_identifier->DataRecv(_identifier->_sync_data->data_input);
				_identifier->_sync_data->data_input.stream = nullptr;
			}
		}

		Identifier::SyncData::~SyncData()
		{
			events::OnClientConnected -= _onClientConnectedIter;
			events::OnConnection -= _onConnectionIter;
		}

		void Identifier::SyncData::_OnClientConnected(std::shared_ptr<Peer> client)
		{
			if (network::connection_type() == ConnectionType::Server && on_client_connect.size())
			{
				auto it = on_client_connect.find('|');
				network::impl::tcp::peeding_messages.push_back(
				{
					std::to_string(client->ID()) + " " +
					on_client_connect.substr(0, it + 1) +
					" MakeRequest " +
					std::to_string(owner ? owner->ID() : -1) + " " +
					std::to_string(ID) + " " +
					on_client_connect.substr(it + 1, on_client_connect.size() - it - 1),
					client
				});
			}
		}

		void Identifier::SyncData::_OnConnection()
		{
			if (network::connection_type() == ConnectionType::Server)
				ID = abs(ID);
			else if (network::connection_type() == ConnectionType::Client)
			{
				auto it = on_client_connect.find('|');
				network::impl::tcp::peeding_messages.push_back(
				{
					std::to_string(server_socket->ID()) + " " +
					on_client_connect.substr(0, it + 1) +
					" MakeRequest " +
					std::to_string(owner ? owner->ID() : -1) + " " +
					std::to_string(ID) + " " +
					on_client_connect.substr(it + 1, on_client_connect.size() - it - 1),
					server_socket
				});
			}
		}

		Identifier::Identifier(std::vector<DataType> v)
		{
			if (connection_type() == ConnectionType::Server) ++SyncData::ID_count;
			else --SyncData::ID_count;

			_sync_data = std::make_shared<SyncData>(SyncData::ID_count);
			objects.push_back(_sync_data);
			_sync_data->serialised = v;
		}

		Identifier::Identifier()
		{
			if (connection_type() == ConnectionType::Server) ++SyncData::ID_count;
			else --SyncData::ID_count;

			_sync_data = std::make_shared<SyncData>(SyncData::ID_count);
			objects.push_back(_sync_data);
		}

		std::shared_ptr<Peer> Identifier::network_owner()
		{
			return _sync_data ? _sync_data->owner : nullptr;
		}

		std::shared_ptr<Identifier::SyncData> Identifier::Get(int id)
		{
			for (auto o : objects)
				if (o->ID == id) return o;
			return nullptr;
		}

		Identifier::~Identifier()
		{
			for (auto nu = objects.begin(); nu != objects.end(); ++nu)
				if (*nu == this->_sync_data) { objects.erase(nu); break; }
			_sync_data = nullptr;
		}


		namespace impl
		{

			void SyncObject(int old_id, int new_id)
			{
				if (auto obj = network::object::Identifier::Get(old_id))
				{
					std::cout << " Object [" << old_id << "] is now [" << new_id << "]\n";
					obj->ID = new_id;
					obj->owner = my_socket;
				}
			}

			void MakeRequest(std::shared_ptr<Peer> owner, int id, std::string object_name, std::string args)
			{
				std::cout << " Peer [" << (owner ? owner->ID() : -1) << "] requested make (old id [" << id << "])\n";
				network::object::Get(object_name)(std::stringstream(message::Serialise(args)));
				std::shared_ptr<Identifier> idt = std::dynamic_pointer_cast<Identifier>(Object::last_object);
				auto obj = network::object::Identifier::objects.back();
				obj->_identifier = idt;
				obj->owner = owner;
				obj->on_client_connect = message::impl::_stringInsert(typeid(*State::CurrentState()).raw_name()) + " " + message::impl::_stringInsert(object_name) + " " + args;


				if (connection_type() == ConnectionType::Server)
				{
					for (auto p : connections)
					{
						if (p == owner) message::Send({ p }, State::CurrentState(), "SyncObject", id, obj->ID);
						else message::Send({ p }, State::CurrentState(), "MakeRequest", owner, obj->ID, object_name, args);
					}
				}
				else if (connection_type() == ConnectionType::Client)
				{
					obj->ID = id;
					//obj->ID_count++;
				}
			}


		} //namespace impl

	} //namespace object

} //namespace network