#pragma once
#include <vector>
#include <memory>
#include <boost\variant.hpp>
#include "Message.h"
#include "Event.h"
#include "Network.h"
#include "..\State.h"

namespace network
{
	class Peer;

	namespace object
	{

		class Identifier abstract
		{
		public:
			typedef boost::variant<
				int*, char*, unsigned*, double*, float*, std::string*,
				std::shared_ptr<int>, std::shared_ptr<char>, std::shared_ptr<unsigned>,
				std::shared_ptr<double>, std::shared_ptr<float>, std::shared_ptr<std::string>> DataType;
		private:
			//*** Stores all serializable variables of the Unit class
			struct SyncData
			{
				SyncData(int id);

				//*** Returns true if Unit has been synchronised over the network
				bool synchronised() { return ID >= 0; }
				//*** The id this Unit has over the network
				//*** If ID < 0, Unit not synchronised 
				int ID = -1;
				//*** the owner of this Identifier
				std::shared_ptr<Peer> owner;

				//*** Stores all serializable variables of the Unit class
				std::vector<DataType> serialised;


				//*** Returns serialised data stored within this Unit
				std::string GetData();
				//*** Updates this Unit's data gathered from the network
				void SetData(std::istream& is);


				//*** Global counter for all newly created Units
				static int ID_count;
				//*** String containing all information this Identifier needs to create itself
				//***   in another process on its connection
				std::string on_client_connect;

				virtual ~SyncData();
			private:
				//*** The iterator of the callback stored in OnClientConnected
				unsigned _onClientConnectedIter;
				//*** The iterator of the callback stored in OnClientConnected
				unsigned _onConnectionIter;

				//*** Event fired on client connection
				void _OnClientConnected(std::shared_ptr<Peer> client);
				//*** Event fired on connecting to the network
				void _OnConnection();
			};


			//*** Stores all synchronised variables of this Unit
			//*** use as so: seriallise << var;
			std::shared_ptr<SyncData> _sync_data = nullptr;

		public:

			//*** Initializes serialisation
			Identifier(std::vector<DataType> v);

			//*** Returns true if Unit has been synchronised over the network
			bool synchronised() { return _sync_data ? _sync_data->synchronised() : false; }

			//*** Returns the ID this Unit is recognised with over the network
			//*** If ID() < 0, Unit not yet synchronised
			int ID() { return _sync_data ? _sync_data->ID : 0; }

			//*** Returns the owner of this Identifier
			std::shared_ptr<Peer> owner();


			//*** Returns the network::Identifier::SyncData by its id
			static std::shared_ptr<SyncData> Get(int id);

			//*** Stores all network-synchronised objects
			static std::vector<std::shared_ptr<SyncData>> objects;

			virtual ~Identifier() = 0;

			template <typename T, typename... Args>
			friend std::shared_ptr<T> Make(Args&&... args);
			friend class Server;
			friend void network::Disconnect();
		};


		template <typename T, typename... Args>
		void Store()
		{
			if (State::state_phase() != State::Phase::StateCreate)
			{
				Output_Handler::Error << "ERR network::object::Store : Store only in state Create() function\n";
				return void();
			}
			message::impl::Message<std::shared_ptr<T>(Args...)> msg = { Object::Make<T, Args...> };
			message::messages[2][typeid(T).raw_name()] = msg;
		}

		template <typename T> message::Type Get() { return message::impl::_Get<message::Type>(typeid(T).raw_name(), 2); }
		template <typename T = void> message::Type Get(std::string name) { return message::impl::_Get<message::Type>(name, 2); }
		template <typename T, typename... Args> std::shared_ptr<T> Make(Args&&... args)
		{
			if (!std::is_base_of<Identifier, T>())
			{
				std::cout << "ERR network::message::object::Make : Supplied type does not derive from network::Identifier class\n";
				return nullptr;
			}
			auto ent = message::Call<std::shared_ptr<T>>(object::Get<T>(), std::forward<Args>(args)...);
			auto obj = std::dynamic_pointer_cast<Identifier>(ent);

			obj->_sync_data->owner = my_socket;
			obj->_sync_data->on_client_connect = message::impl::_stringInsert(typeid(T).raw_name()) + " " + message::Serialise(args...);

			if (connection_type() == ConnectionType::Server)
			{
				message::Send(connections, "MakeRequest", server_socket, obj->ID(), typeid(T).raw_name(), message::Serialise(std::forward<Args>(args)...));
			}
			else if (connection_type() == ConnectionType::Client)
			{
				message::Send({ server_socket }, "MakeRequest", my_socket, obj->ID(), typeid(T).raw_name(), message::Serialise(std::forward<Args>(args)...));
			}

			return ent;
		}

		namespace impl
		{
			//*** Synchronises Object at Creator's process
			void SyncObject(int old_id, int new_id);
			//*** Requests creation of an Object
			void MakeRequest(std::shared_ptr<Peer> owner, int id, std::string object_name, std::string args);

		} //namespace impl


	} //namespace object

} //namespace network
