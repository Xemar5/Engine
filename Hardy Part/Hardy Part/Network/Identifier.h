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
		namespace impl
		{
			//*** Synchronises Object at Creator's process
			void SyncObject(int old_id, int new_id);
			//*** Requests creation of an Object
			void MakeRequest(std::shared_ptr<Peer> owner, int id, std::string object_name, std::string args);

		} //namespace impl



		class Identifier abstract
		{
		public:
			class DataInput
			{
			public:

				DataInput& operator >> (int* dst) { if (dst) *stream >> *dst; return *this; }
				DataInput& operator >> (char* dst) { if (dst) *stream >> *dst; return *this; }
				DataInput& operator >> (unsigned* dst) { if (dst) *stream >> *dst; return *this; }
				DataInput& operator >> (double* dst) { if (dst) *stream >> *dst; return *this; }
				DataInput& operator >> (float* dst) { if (dst) *stream >> *dst; return *this; }
				DataInput& operator >> (std::string* dst) { if (dst) *dst = message::impl::_stringRetrieve(*stream); return *this; }

				DataInput& operator >> (std::shared_ptr<int> dst) { if (dst) *stream >> *dst; return *this; }
				DataInput& operator >> (std::shared_ptr<char> dst) { if (dst) *stream >> *dst; return *this; }
				DataInput& operator >> (std::shared_ptr<unsigned> dst) { if (dst) *stream >> *dst; return *this; }
				DataInput& operator >> (std::shared_ptr<double> dst) { if (dst) *stream >> *dst; return *this; }
				DataInput& operator >> (std::shared_ptr<float> dst) { if (dst) *stream >> *dst; return *this; }
				DataInput& operator >> (std::shared_ptr<std::string> dst) { if (dst) *dst = message::impl::_stringRetrieve(*stream); return *this; }

			private:
				void set(std::istream& is) { stream = &is; }
				//*** Stream containing received
				std::istream* stream;
				friend class Identifier;
			};
			class DataOutput
			{
			public:
				DataOutput& operator << (int* dst) { if (dst) *stream += " " + std::to_string(*dst); return *this; }
				DataOutput& operator << (char* dst) { if (dst) *stream += " " + std::to_string(*dst); return *this; }
				DataOutput& operator << (unsigned* dst) { if (dst) *stream += " " + std::to_string(*dst); return *this; }
				DataOutput& operator << (double* dst) { if (dst) *stream += " " + std::to_string(*dst); return *this; }
				DataOutput& operator << (float* dst) { if (dst) *stream += " " + std::to_string(*dst); return *this; }
				DataOutput& operator << (std::string* dst) { if (dst) *stream += " " + message::impl::_stringInsert(*dst); return *this; }

				DataOutput& operator << (std::shared_ptr<int> dst) { if (dst) *stream += " " + std::to_string(*dst); return *this; }
				DataOutput& operator << (std::shared_ptr<char> dst) { if (dst) *stream += " " + std::to_string(*dst); return *this; }
				DataOutput& operator << (std::shared_ptr<unsigned> dst) { if (dst) *stream += " " + std::to_string(*dst); return *this; }
				DataOutput& operator << (std::shared_ptr<double> dst) { if (dst) *stream += " " + std::to_string(*dst); return *this; }
				DataOutput& operator << (std::shared_ptr<float> dst) { if (dst) *stream += " " + std::to_string(*dst); return *this; }
				DataOutput& operator << (std::shared_ptr<std::string> dst) { if (dst) *stream += " " + message::impl::_stringInsert(*dst); return *this; }

			private:
				void set(std::string& is) { stream = &is; }
				//*** Stream containing received
				std::string* stream;
				friend class Identifier;
			};
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
				//*** the network_owner of this Identifier
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
				std::shared_ptr<Identifier> _identifier;
				DataInput data_input;
				DataOutput data_output;

				//*** The iterator of the callback stored in OnClientConnected
				unsigned _onClientConnectedIter;
				//*** The iterator of the callback stored in OnClientConnected
				unsigned _onConnectionIter;

				//*** Event fired on client connection
				void _OnClientConnected(std::shared_ptr<Peer> client);
				//*** Event fired on connecting to the network
				void _OnConnection();

				template <typename T, typename... Args>
				friend std::shared_ptr<T> Make(Args&&... args);
				friend class Identifier;
				friend void network::object::impl::MakeRequest(std::shared_ptr<Peer> owner, int id, std::string object_name, std::string args);
			};


			//*** Stores all synchronised variables of this Unit
			std::shared_ptr<SyncData> _sync_data = nullptr;

		public:

			//*** Fired on every Network data synchronisation
			//*** Receives all data send by DataSend function override
			//*** Use in pair with DataSend
			virtual void DataRecv(DataInput& i) {};
			//*** Fired on every Network data synchronisation
			//*** Sends all data to other Network Clients
			//*** Use in pair with DataRecv
			virtual void DataSend(DataOutput& o) {};


			//*** Initializes serialisation
			Identifier(std::vector<DataType> v);
			//*** Initializes serialisation
			Identifier();

			//*** Returns true if Unit has been synchronised over the network
			bool synchronised() { return _sync_data ? _sync_data->synchronised() : false; }

			//*** Returns the ID this Unit is recognised with over the network
			//*** If ID() < 0, Unit not yet synchronised
			int ID() { return _sync_data ? _sync_data->ID : 0; }

			//*** Returns the network_owner of this Identifier
			std::shared_ptr<Peer> network_owner();


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
				return Object::Make<T>(std::forward<Args>(args)...);
			}
			auto ent = message::Call<std::shared_ptr<T>>(object::Get<T>(), std::forward<Args>(args)...);
			auto obj = std::dynamic_pointer_cast<Identifier>(ent);
			obj->_sync_data->_identifier = obj;

			obj->_sync_data->owner = my_socket;
			obj->_sync_data->on_client_connect = 
				message::impl::_stringInsert(typeid(*State::CurrentState()).raw_name()) + " " +
				message::impl::_stringInsert(typeid(T).raw_name()) + " " +
				message::Serialise(args...);

			if (connection_type() == ConnectionType::Server)
			{
				message::Send(connections, State::CurrentState(), "MakeRequest", server_socket, obj->ID(), message::impl::_stringInsert(typeid(T).raw_name()), message::Serialise(std::forward<Args>(args)...));
			}
			else if (connection_type() == ConnectionType::Client)
			{
				message::Send({ server_socket }, State::CurrentState(), "MakeRequest", my_socket, obj->ID(), message::impl::_stringInsert(typeid(T).raw_name()), message::Serialise(std::forward<Args>(args)...));
			}

			return ent;
		}

	} //namespace object

} //namespace network
