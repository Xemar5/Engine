#pragma once
#include "Peer.h"
#include "..\Output_Handler.h"
#include "TCP.h"
#include <functional>
#include <sstream>

class State;

namespace network
{
	namespace message
	{
		using StorageIter = unsigned;
		using InnerStorageIter = std::string;
		using Type = std::function<void(std::istream&)>;

		template <typename Ret, typename... Args>
		Ret Call(Type f, Args&&... args);

		extern std::map<StorageIter, std::map<InnerStorageIter, Type>> messages;



		namespace impl
		{

			template <typename R = void> struct Message;
			template <typename R, typename... S> struct Message<R(S...)>
			{
				Message(R(*f)(S...)) : foo(f) {}
				Message(std::function<R(S...)> f) : foo(f) {}

				R operator()(std::istream& is) const { return call(is, foo, types<S...>{}); }
				R operator()(S... is) const { return foo(std::forward<S>(is)...); }

			private:
				template <typename Ret, typename... Args>
				friend Ret(::network::message::Call)(Type f, Args&&... args);

				//*** Pointer to the actual function
				std::function<R(S...)> foo;
				//*** Helping struct, stores the order of function arguments
				template<class...> struct types {};


				//*** Recursive function peeling received istream from values
				//*** if succeed, calls stored function pointer foo
				template<class Foo, class Head, class... Tail, class... Vs> R call(std::istream& is, Foo&& f, types<Head, Tail...>, Vs&&... vs) const
				{
					bool good = true;
					auto val = get<Head>(is, good);
					if (good) return call(is, f, types<Tail...>{}, std::forward<Vs>(vs)..., val);

					return R();
				}
				//*** Recursive function peeling received istream from values
				//*** if succeed, calls stored function pointer foo
				template<class Foo, class... Vs> R call(std::istream& is, Foo&& f, types<>, Vs&&... vs) const
				{
					return f(std::forward<Vs>(vs)...);
				}
				//*** Handles an unspecialized function argument
				template <class T> static T get(std::istream& args, bool& good)
				{
					T t;
					if (!(args >> t))
					{
						args.clear();
						std::cout << "ERR network::message::impl::Message<>::get : Supplied argument type doesn't match the function's arguments\n";
						good = false;
					}
					args.get();
					return t;
				}
				//*** Handles std::string function argument
				template <> static std::string get(std::istream& args, bool& good)
				{
					return _stringRetrieve(args);
				}
				//*** Handles std::string function argument
				template <> static std::shared_ptr<Peer> get(std::istream& args, bool& good)
				{
					int id;

					if (!(args >> id))
					{
						args.clear();
						std::cout << "ERR network::message::impl::Message<>::get : Supplied argument type is not of Peer ID\n";
						good = false;
					}

					if (id == -1) return nullptr;
					if (my_socket && my_socket->ID() == id) return my_socket;
					if (server_socket && server_socket->ID() == id) return server_socket;
					for (auto c : connections)
						if (c && c->ID() == id) return c;
					return std::make_shared<Peer>(std::make_shared<boost::asio::ip::tcp::socket>(*service), nullptr, id);
				}

			};

			//*** Converts any string-like input into system-readable string
			template <typename T = void> std::string _stringInsert(std::string val)
			{
				for (auto it = val.begin(); it != val.end(); ++it)
					if (*it == '|') { it = val.insert(it, '|'); it += 1; }
				val.push_back('|');
				return val;
			}

			template <typename T = void> std::string _stringRetrieve(std::istream& args)
			{
				std::string t, h;
				while (true)
				{
					std::getline(args, h, '|');
					if (!t.size() && h.size() && h[0] == ' ') h = h.substr(1);
					t += h;
					if (args.get() != '|') break;
					else t += '|';
				}
				return t;
			}

			template <typename ...T, unsigned N> std::string get_arg(std::string& s, const char(&val)[N], T&&... args) { s += " " + _stringInsert(val); return get_arg(s, args...); }
			template <typename ...T			   > std::string get_arg(std::string& s, const char*& val, T&&... args) { s += " " + _stringInsert(val); return get_arg(s, args...); }
			template <typename ...T			   > std::string get_arg(std::string& s, const char& val, T&&... args) { s += " " + std::string(1, val); return get_arg(s, args...); }
			template <typename ...T			   > std::string get_arg(std::string& s, char& val, T&&... args) { s += " " + std::string(1, val); return get_arg(s, args...); }
			template <typename ...T			   > std::string get_arg(std::string& s, std::string& val, T&&... args) { s += " " + _stringInsert(val); return get_arg(s, args...); }
			template <typename ...T			   > std::string get_arg(std::string& s, int& val, T&&... args) { s += " " + std::to_string(val); return get_arg(s, args...); }
			template <typename ...T			   > std::string get_arg(std::string& s, bool& val, T&&... args) { s += " " + std::to_string(val); return get_arg(s, args...); }
			template <typename ...T			   > std::string get_arg(std::string& s, double& val, T&&... args) { s += " " + std::to_string(val); return get_arg(s, args...); }
			template <typename ...T			   > std::string get_arg(std::string& s, float& val, T&&... args) { s += " " + std::to_string(val); return get_arg(s, args...); }
			template <typename ...T			   > std::string get_arg(std::string& s, unsigned& val, T&&... args) { s += " " + std::to_string(val); return get_arg(s, args...); }
			template <typename ...T			   > std::string get_arg(std::string& s, std::shared_ptr<Peer> val, T&&... args) { s += " " + std::to_string(val ? val->ID() : -1); return get_arg(s, args...); }
			template <typename K, typename ...T> std::string get_arg(std::string& s, K&& val, T&&... args)
			{
				Output_Handler::Error << "ERR network::message::impl::get_arg : unsupported value\n";
				return "";
			}
			template <typename T = void		   > std::string get_arg(std::string& s) { return s; }

			//*** Searches network::message::messages vector for a functor with given name
			//*** returns nullptr if no functor was found
			template <typename T = Type> Type _Get(InnerStorageIter name, StorageIter iter)
			{
				for (auto& m : messages[iter])
					if (m.first == name)
						return m.second;
				return nullptr;
			}
			//*** Pairs a function with a name and stores them in network::message::messages
			//***   iter - used for differentiation system and non-system functors
			//***		   non-system functors will be erased after state change
			template <typename R, typename... A> Type _Store(std::function<R(A...)> f, InnerStorageIter name, StorageIter iter)
			{
				if (State::state_phase() != State::Phase::StateCreate)
				{
					Output_Handler::Error << "ERR network::message::impl::_Store : Store only in state Create() function\n";
					return impl::Message<void()>{ nullptr };
				}

				auto m = _Get(name, iter);
				if (m)
				{
					std::cout << "ERR network::message::impl::_Store : Name \"" << name << "\" already taken\n";
					return m;
				}
				impl::Message<R(A...)> msg{ f };
				messages[iter][name] = msg;
				return msg;
			}

			void _Send(std::vector<std::shared_ptr<Peer>> receivers, std::shared_ptr<State> state, InnerStorageIter message_name, std::string args);
			void _Send(std::vector<std::shared_ptr<Peer>> receivers, std::string state_name, InnerStorageIter message_name, std::string args);

			namespace system
			{
				template <typename T = Type> Type SystemGet(std::string name) { return _Get<Type>(name, 1); }

				template <typename R, typename... A> Type SystemStore(R(*f)(A...), std::string name) { return SystemStore(std::function<R(A...)>{f}, name); };
				template <typename R, typename... A> Type SystemStore(std::function<R(A...)> f, std::string name) { return _Store(f, name, 1); }

			} //namespace system

		} //namespace impl


		template <typename T = Type> Type Get(std::string name) { return impl::_Get<Type>(name, 0); }
		template <typename... Args> std::string Serialise(Args... args) { std::string s; return impl::get_arg(s, args...); };

		template <typename R, typename... A> Type Store(R(*f)(A...), std::string name) { return Store(std::function<R(A...)>{f}, name); }
		template <typename R, typename... A> Type Store(std::function<R(A...)> f, std::string name) { return impl::_Store(f, name, 0); }

		template <typename Ret = void, typename... Args> Ret Call(Type f, Args&&... args)
		{
			if (!f)
			{
				Output_Handler::Error << "ERR network::message::Call : no function supplied\n";
				return Ret();
			}
			auto foo = f.target<impl::Message<Ret(Args...)>>();
			if (!foo)
			{
				Output_Handler::Output << "MSG : network::message::Call : supplied arguments or return type does not match the underlying function\n";
				Output_Handler::Output << "MSG : network::message::Call : calling with istream...\n";

				std::string s;
				impl::get_arg(s, args...);

				f(std::stringstream(s));
				return Ret();
			}
			return foo->foo(std::forward<Args>(args)...);
		};

		enum class Receivers
		{
			Server,
			Me, 
			All,
			AllClients,
			OtherClients,
			OtherClientsAndServer
		};

		template <typename... A> void Send(std::vector<std::shared_ptr<Peer>> receivers, std::shared_ptr<State> state, std::string message_name,  A... args)
		{
			impl::_Send(receivers, state, message_name, Serialise(args...));
		}
		template <typename... A> void Send(Receivers receivers, std::shared_ptr<State> state, std::string message_name, A... args)
		{
			if (connection_type() == ConnectionType::None)
			{
				switch (receivers)
				{
				case network::message::Receivers::All: 
				case network::message::Receivers::Me: 
				case network::message::Receivers::AllClients: Call<void, A...>(impl::_Get(message_name, 0), std::forward<A>(args)...); break;
				case network::message::Receivers::Server: break;
				case network::message::Receivers::OtherClients: break;
				case network::message::Receivers::OtherClientsAndServer: break;
				default: break;
				}
			}
			else
			{
				switch (receivers)
				{
				case network::message::Receivers::Server:
					if (connection_type() == ConnectionType::Server) Call<void, A...>(impl::_Get(message_name, 0), std::forward<A>(args)...);
					else Send({ server_socket }, state, message_name, std::forward<A>(args)...);
					break;
				case network::message::Receivers::Me:
					if (connection_type() == ConnectionType::Server) Call<void, A...>(impl::_Get(message_name, 0), std::forward<A>(args)...);
					else Send({ my_socket }, state, message_name, std::forward<A>(args)...);
					break;
				case network::message::Receivers::All:
				{
					auto v = connections;
					if (connection_type() != ConnectionType::Server)
					{
						v.push_back(server_socket);
						v.push_back(my_socket);
					}
					Send(v, state, message_name, args...);
					if (connection_type() == ConnectionType::Server) Call<void, A...>(impl::_Get(message_name, 0), std::forward<A>(args)...);
				}
				break;
				case network::message::Receivers::AllClients:
				{
					auto v = connections;
					if (connection_type() != ConnectionType::Server)
						v.push_back(my_socket);
					Send(v, state, message_name, std::forward<A>(args)...);
				}
				break;
				case network::message::Receivers::OtherClients:
					Send(connections, state, message_name, std::forward<A>(args)...);
					break;
				case network::message::Receivers::OtherClientsAndServer:
				{
					auto v = connections;
					v.push_back(server_socket);
					Send(v, state, message_name, std::forward<A>(args)...);
				}
				break;
				default:
					break;
				}
			}
		}

	} //namespace message

} //namespace network
