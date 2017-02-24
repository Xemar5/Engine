#pragma once
#include <SDL.h>
#include <cmath>
#include <memory>
#include <unordered_map>

class Entity;

namespace controlls
{
	unsigned DeviceByName(std::string name);
	class Mapping;

	enum class Directions
	{
		None = 0b0000,
		Up = 0b0001,
		Right = 0b0010,
		Down = 0b0100,
		Left = 0b1000
	};

	enum class Actions
	{
		Input = 0,
		Button = 1,
		Key = 1,
		Axis = 2,
		MouseAxis = 2,
		Hat = 3
	};

	enum class Devices
	{
		Device,
		Keyboard,
		Mouse,
		Gamepad0,
		Gamepad1,
		Gamepad2,
		Gamepad3,
		Gamepad4,
		Gamepad5,
		Gamepad6,
		Gamepad7,
		Gamepad8,
		Gamepad9
	};


	namespace impl
	{
		template <typename T> int sgn(T val) {
			return (T(0) < val) - (val < T(0));
		}


		template <typename T>
		class ActionHandler;
		struct MouseAxis;

		class Signal
		{
		public:
			static void Update();
			static void Events();

			//*** Set at the time of input manipulation
			//*** Shows when was the input used
			//*** Use with SDL_GetTicks()
			unsigned push_time = 0;
			//*** Current value of this input
			double value = 0;
			//*** The value of this input before current event
			//*** Can be used outside of Events loop
			double last_value = 0;

			//*** Sets the input as handled in Events loop
			//*** Don't use if not needed
			bool EventResolve();
		private:
			//*** If true, Events loop has already _resolved this input
			bool _resolved = false;
			//*** Sets values of this input
			static void _SetInput(unsigned device, unsigned action, unsigned index, unsigned time, double value);
			friend struct Gamepad;
		};
		//*** Contains all inputs
		extern std::unordered_map<unsigned, std::unordered_map<unsigned, std::unordered_map<unsigned, Signal>>> input_map;



		template <typename T> struct StoreInput;
		template <typename T> struct StoreInput<std::shared_ptr<T>>
		{
			//*** Stores input to given input type
			template <typename K>
			static std::shared_ptr<T> to(K& input)
			{
				auto ptr = std::make_shared<K>(input.get_device(), input.get_index());
				return std::dynamic_pointer_cast<T>(ptr);
			}
		};
		template <typename T> struct InputTypeRetrive;
		template <typename T> struct InputTypeRetrive<std::shared_ptr<T>>
		{
			//*** Retrives input from given input type
			static std::shared_ptr<T> from(unsigned device, unsigned action, unsigned index)
			{
				return std::make_shared<T>(device, action, index);
			}

			template <typename U>
			static std::shared_ptr<T> through(unsigned device, unsigned action, unsigned index)
			{
				return std::dynamic_pointer_cast<T>(std::make_shared<U>(device, action, index));
			}
		};

		class Input
		{
		public:
			Input(unsigned Device, unsigned Action) : _device(Device), _action(Action) {}
			Input(unsigned Device, unsigned Action, unsigned Index) : _device(Device), _action(Action), _index(Index) {}

			bool operator==(const Input& other) { return other.get_action() == this->get_action() && other.get_device() == this->get_device() && other.get_index() == this->get_index(); }
			bool operator!=(const Input& other) { return !operator==(other); }

			//*** Returns current value of this input
			virtual double value() const { return _signal().value; }
			//*** Returns the value of this input before this event has occured
			virtual double last_value() const { return _signal().last_value; }
			//*** If not equal to 0, the value of this input is being changed
			//*** <0 - value descends
			//*** >0 - value increases
			//*** Dont use with Axis (might give wrong data)
			virtual int in_motion() const { return pushed() - released(); }
			//*** Returns the raw value of this input
			//*** Works only for Axis (for other types returns value() )
			virtual double raw_value() const { return _signal().value; }
			//*** Returns the value of this input before this event has occured
			virtual double raw_last_value() const { return _signal().last_value; }
			//*** If 1, the input is being curently pushed
			//*** Works for Button and Hat
			virtual bool pushed() const { return abs((int)last_value()) < abs((int)value()) ? _signal().EventResolve() : false; }
			//virtual bool pushed() { auto& i = input_map[get_device()][get_action()][get_index()]; return (int)i.last_value < i.value ? i.EventResolve() : false; }
			//*** If 1, the input is being curently released
			//*** Works for Button and Hat
			virtual bool released() const { return abs((int)last_value()) > abs((int)value()) ? _signal().EventResolve() : false; }

			//*** Returns the device the input is comming from
			virtual unsigned get_device() const { return _device ? _device : input_map[_device][0][1].push_time; }
			//*** Returns the action this input is comming from (see enum class Actions)
			virtual unsigned get_action() const { return _action ? _action : (unsigned)input_map[_device][0][1].value; }
			//*** Returns the index of this input
			virtual unsigned get_index() const { return _action ? _index : (unsigned)input_map[_device][0][1].last_value; }
			//*** Returns the modifier of this input
			//*** Modifiers are used in Hat inputs, determining direction
			virtual unsigned get_modifier() const { return 0; }

			//*** Returns the name of current input action
			std::string get_action_name() const;

			//*** Converts this input to a specific type
			template <typename T> T as() { return InputTypeRetrive<T>::from(get_device(), get_action(), get_index()); }
		protected:

			//*** current device
			unsigned _device = 0;
			//*** current action (see enum class Actions)
			unsigned _action = 0;
			//*** index of this input
			unsigned _index = 0;

			//*** Returns the signal this Input points to
			Signal& _signal() const { return input_map[get_device()][get_action()][get_index()]; }

			template <typename T> friend class ActionHandler;
			friend class GamepadMap;
			friend class Mapping;
		};
		struct Button : public Input
		{
			Button(unsigned Device) : Input(Device, 1) {}
			Button(unsigned Device, unsigned Index) : Input(Device, 1, Index) {}
			Button(unsigned Device, unsigned Action, unsigned Index) : Input(Device, 1, Index) {}
		};
		struct Hat : public Input
		{
			Hat(unsigned Device) : Input(Device, 3) {}
			Hat(unsigned Device, unsigned Index) : Input(Device, 3, Index) {}
			Hat(unsigned Device, unsigned Action, unsigned Index) : Input(Device, 3, Index) {}
			//*** Returns the currently pushed direction on the Hat
			unsigned get_modifier() const override { return (unsigned)value(); }
			//*** Returns the direction that is being currently pushed
			bool pushed() const override;
			//*** Returns the direction that is being currently released
			bool released() const override;
		};
		struct Axis : public Input
		{
			Axis(unsigned Device) : Input(Device, 2) {}
			Axis(unsigned Device, unsigned Index) : Input(Device, 2, Index) {}
			Axis(unsigned Device, unsigned Action, unsigned Index) : Input(Device, 2, Index) {}
			double value() const override { auto val = _signal().value; return val >= 32500 ? 1 : val <= -32500 ? -1 : val / 32768.0; }
			double last_value() const override { auto val = _signal().last_value; return val >= 32500 ? 1 : val <= -32500 ? -1 : val / 32768.0; }
			//*** Don't use this (TODO)
			int in_motion() const override { return _signal().value != _signal().last_value; }
		private:
		};
		struct MouseAxis : public Input
		{
			MouseAxis(unsigned Device, unsigned Axis) : Input(Device, 2, Axis) {}
			MouseAxis(unsigned Device, unsigned Action, unsigned Axis) : Input(Device, 2, Axis) {}
			//*** If not equal to 0, the value of this input is being changed
			//*** <0 - value descends
			//*** >0 - value increases
			int in_motion() const override { return (int)(SDL_GetTicks() < 100 + input_map[_device][_action][_index + 2].push_time) * sgn(input_map[_device][_action][_index + 2].value); }
			//*** True if mouse is in between 0 - 1 /4 of the screen and in between 3 - 4 /4 of the screen
			bool pushed() const override;
			//*** True if mouse is in between 1 - 3 /4 of the screen
			bool released() const override { return !pushed(); }
		private:
			using Input::pushed;
			using Input::released;
		};

		template <typename T>
		class ActionHandler
		{
		private:
			std::shared_ptr<T> action;
		public:
			ActionHandler(unsigned Device) { action = std::make_shared<T>(Device); }
			//*** Returns input with specific index
			std::shared_ptr<T> operator[](unsigned index) { action->_index = index; return action; }
		};


		struct Device;
		struct Keyboard;
		struct Mouse;
		struct Gamepad;
		class GamepadMap;

	} //namespace impl

	  //*** Device that is being currently used
	extern impl::Device device;
	//*** Keyboard device
	extern impl::Keyboard keyboard;
	//*** Mouse device
	extern impl::Mouse mouse;
	//*** map containing all connected gamepads
	extern impl::GamepadMap gamepads;


	namespace impl
	{

		struct Device
		{
			Device(unsigned index) { input = std::make_shared<impl::Input>(index, 0); }
			virtual ~Device() = default;
			//*** Currently retrived input
			std::shared_ptr<impl::Input> input;
			virtual std::string name() { return "Unknown Device"; }
		};


		struct Keyboard : public Device
		{
			Keyboard() : Device(1), key(1) {}
			impl::ActionHandler<Button> key;
			std::string name() override { return "Keyboard"; }
		};

		struct Mouse : public Device
		{
			Mouse() : Device(2), button(2) { horizontal_axis = std::make_shared<impl::MouseAxis>(2, 0); vertical_axis = std::make_shared<impl::MouseAxis>(2, 1); }
			impl::ActionHandler<Button> button;
			std::shared_ptr<impl::MouseAxis> horizontal_axis;
			std::shared_ptr<impl::MouseAxis> vertical_axis;
			std::string name() override { return "Mouse"; }
			bool ContainsMouse(std::shared_ptr<Entity> ent);
		};
		struct Gamepad : public Device
		{
			Gamepad(unsigned index) : Device(3 + index), button(3 + index), axis(3 + index), hat(3 + index) { _joystick = nullptr; _controller = nullptr; }
			impl::ActionHandler<Button> button;
			impl::ActionHandler<Axis> axis;
			impl::ActionHandler<Hat> hat;
			std::string name() override { return _name; }
			bool is_gamecontroller() { return _controller ? true : false; }
		protected:
			static void _AddJoystick(unsigned id);
			static void _RemoveJoystick(unsigned id);

			std::string _name;
			SDL_Joystick* _joystick;
			SDL_GameController* _controller;

			friend void Signal::Events();
		};


		class GamepadMap
		{
		public:
			//*** Returns a gamepad by its index
			Gamepad& operator[](unsigned index)
			{
				auto it = map.find(index);
				if (it == map.end()) return map.insert({ index, Gamepad{ index } }).first->second;
				return it->second;
			}
			std::size_t count() const { return map.size(); }
			unsigned last_connected = 0;
		private:
			//*** Map containing all connected gamepads
			std::unordered_map<unsigned, Gamepad> map;
			//*** The index of recently connected gamepad

			friend unsigned controlls::DeviceByName(std::string);
			friend struct Gamepad;
			friend void Signal::Events();
			friend class ::controlls::Mapping;
		};

	} //namespace impl

	  //*** Converts given input parameters and to T type
	  //*** Returened input can be stored for later use/checks
	template<typename T = std::shared_ptr<impl::Input>, typename V = std::shared_ptr<impl::Input>>
	T StoreInput(V input) { return StoreInput<T>(input->get_device(), input->get_action(), input->get_index()); }

	//*** Copies given input and converts it to T type
	//*** Returened input can be stored for later use/checks
	template<typename T = std::shared_ptr<impl::Input>>
	T StoreInput(unsigned device, unsigned action, unsigned index)
	{
		switch (action)
		{
		case 1:
			return impl::InputTypeRetrive<T>::through<impl::Button>(device, action, index);
		case 2:
			if (device == 2) return impl::InputTypeRetrive<T>::through<impl::MouseAxis>(device, action, index);
			return impl::InputTypeRetrive<T>::through<impl::Axis>(device, action, index);
		case 3:
			return impl::InputTypeRetrive<T>::through<impl::Hat>(device, action, index);
		default:
			break;
		}
		return impl::InputTypeRetrive<T>::from(device, action, index);
	}

	
	////*** Copies given input and converts it to T type
	////*** Returened input can be stored for later use/checks
	//template <typename T = std::shared_ptr<impl::Input>>
	//T GetInput(unsigned device, unsigned action, unsigned index)
	//{
	//	return StoreInput<T>(device, action, index);
	//}

	//*** Returns the device index by supplied name
	//*** If no device has this name, unsigned max (-1) is returned
	unsigned DeviceByName(std::string name);

	//*** Undefined input
	extern std::shared_ptr<impl::Input> undefined;

	using Input = std::shared_ptr<impl::Input>;
	using Axis = std::shared_ptr<impl::Axis>;
	using Hat = std::shared_ptr<impl::Hat>;
	using Button = std::shared_ptr<impl::Button>;
	using Key = std::shared_ptr<impl::Button>;
	using MouseAxis = std::shared_ptr<impl::MouseAxis>;


} //namespace controlls


#include "Mapping.h"

