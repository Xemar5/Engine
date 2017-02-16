#pragma once
#include <map>
#include <functional>

namespace network
{
	namespace events
	{

		template<typename... Args> class Event
		{
		public:
			Event() {}

			const unsigned operator+= (std::function<void(Args...)> callback)
			{
				_callbacks[_counter] = callback;
				return _counter++;
			}

			void operator -= (unsigned iterator)
			{
				if (!_callbacks.size()) return;
				auto it = _callbacks.find(iterator);
				if (it != _callbacks.end())
					_callbacks.erase(it);
			}

			void operator() (Args&... args)
			{
				for (auto cb = _callbacks.begin(); cb != _callbacks.end();)
				{
					if (cb->second)
						std::invoke((cb++)->second, args...);
					else cb = _callbacks.erase(cb);
				}
			}
		private:
			unsigned _counter = 0;
			std::map<unsigned, std::function<void(Args...)>> _callbacks;
		};


	} //namespace events

} //namespace network