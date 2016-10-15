#pragma once
//#include <SDL.h>
//#include "Device.h"
//
//class Device;
//
//enum class InputState
//{
//	Undefined,
//	Any,
//	Released,
//	Pushed,
//	Held = 4,
//	Moving = 4
//};
//enum class InputType
//{
//	Undefined,
//	Any,
//	KeyboardButton,
//	MouseButton,
//	MouseAxis,
//	GamepadButton,
//	GamepadAxis,
//	GamepadHat
//};
//enum class InputKey
//{
//	Undefined = -2,
//	Any = -1,
//};
//enum class MouseAxis
//{
//	X,
//	Y
//};
//enum class HatDirections
//{
//	Any = -1,
//	None = 0b0000,
//	U = 0b0001,
//	UR = 0b0011,
//	UL = 0b1001,
//	D = 0b0100,
//	DR = 0b0110,
//	DL = 0b1100,
//	R = 0b0010,
//	L = 0b1000,
//};
//enum class GamepadAxisType
//{
//	Default,
//	Inverted,
//	Halved,
//	Halved_Inverted
//};
//enum class ControlerID
//{
//	Undefined = -3,
//	Any = -2,
//	Mouse = -1,
//	Keyboard = -1,
//	Gamepad0,
//	Gamepad1,
//	Gamepad2,
//	Gamepad3,
//	Gamepad4,
//	Gamepad5,
//	Gamepad6,
//	Gamepad7,
//	Gamepad8,
//	Gamepad9,
//	Gamepad10,
//	Gamepad11,
//	Gamepad12,
//	Gamepad13,
//	Gamepad14,
//	Gamepad15,
//	Gamepad16,
//	Gamepad17,
//	Gamepad18,
//	Gamepad19,
//	Gamepad20,
//};
//
//
//class InputBase
//{
//public:
//	template <typename T = InputBase>
//	static T Set(InputKey key = InputKey::Any, ::ControlerID device = ControlerID::Any, HatDirections hatDir = HatDirections::Any);
//
//	InputState State() { return _State; }
//	InputType Type() { return _Type; }
//	ControlerID ControlerID() { return _ControlerID; }
//	Device Controler() { return Device::Get((Sint32)_ControlerID); }
//
//	virtual double Down();
//	virtual double Up();
//	virtual double Held(Sint32 time = 0);
//
//	explicit operator bool() const { return *this == InputBase::Set() ? false : true; }
//	virtual bool operator==(const InputBase& dst) const;
//	virtual bool operator!=(const InputBase& dst) const { return *this == dst ? false : true; }
//protected:
//	InputBase() {};
//
//	Sint32 _Value = 0;
//	InputState _State = InputState::Undefined;
//	InputKey _Key = InputKey::Undefined;
//	InputType _Type = InputType::Undefined;
//	::ControlerID _ControlerID = ControlerID::Undefined;
//	HatDirections _HatDirection = HatDirections::Any;
//	GamepadAxisType _AxisType = GamepadAxisType::Default;
//	Sint32 _Time = 0;
//};
//
//
//InputBase InputBase::Set(InputKey key, ::ControlerID device, HatDirections hatDir)
//{
//	InputBase i;
//	if (dynamic_cast<InputKeyboard*>(ptr))			i._Type = InputType::KeyboardButton;
//	if (dynamic_cast<InputMouseButton*>(ptr))		i._Type = InputType::MouseButton;
//	if (dynamic_cast<InputMouseAxis*>(ptr))			i._Type = InputType::MouseAxis;
//	if (dynamic_cast<InputGamepadAxis*>(ptr))		i._Type = InputType::GamepadAxis;
//	if (dynamic_cast<InputGamepadButton*>(ptr))		i._Type = InputType::GamepadButton;
//	if (dynamic_cast<InputGamepadHat*>(ptr))		i._Type = InputType::GamepadHat;
//	i._Key = key;
//	i._ControlerID = device;
//	i._HatDirection = hatDir;
//	return i;
//}
//
//
//
//
//
//
//
//class InputKeyboard : protected InputBase
//{
//public:
//	static InputBase Set(Sint32 key) { return InputBase::Set<InputKeyboard>((InputKey)key, ControlerID::Keyboard); };
//
//	Sint32 Key() { return (Sint32)_Key; }
//
//	double Down() override { return this->InputBase::Down(); }
//	double Up() override { return this->InputBase::Up(); }
//	double Held(Sint32 time = 0) override { return this->InputBase::Held(time); }
//	friend class InputBase;
//private:
//	InputKeyboard() {};
//};
//
//
//
//
//
//
//
//
//class InputMouseButton : protected InputBase
//{
//public:
//	static InputMouseButton Set(Sint32 button) { return InputBase::Set<InputMouseButton>((InputKey)button, ControlerID::Mouse); }
//
//	Sint32 Button() { return (Sint32)_Key; }
//
//	double Down() override { return this->InputBase::Down(); }
//	double Up() override { return this->InputBase::Up(); }
//	double Held(Sint32 time = 0) override { return this->InputBase::Held(time); }
//	friend class InputBase;
//};
//class InputMouseAxis : protected InputBase
//{
//public:
//	static InputMouseAxis Set(MouseAxis axis) { return InputBase::Set<InputMouseAxis>((InputKey)axis, ControlerID::Mouse); }
//
//	MouseAxis Axis() { return (MouseAxis)_Key; }
//	Sint32 Position() { return (Sint32)Held(0); }
//
//private:
//	double Down() override { return 0; }
//	double Up() override { return 0; }
//	double Held(Sint32 time = 0) override;
//	friend class InputBase;
//};
//
//
//
//
//
//
//
//class InputGamepadButton : protected InputBase
//{
//public:
//	static InputGamepadButton Set(::ControlerID gamepad, Sint32 button) { return InputBase::Set<InputGamepadButton>((InputKey)button, (::ControlerID)gamepad); }
//
//	Sint32 Button() { return (Sint32)_Key; }
//
//	double Down() override { return this->InputBase::Down(); }
//	double Up() override { return this->InputBase::Up(); }
//	double Held(Sint32 time = 0) override { return this->InputBase::Held(time); }
//	friend class InputBase;
//};
//class InputGamepadAxis : protected InputBase
//{
//public:
//	static InputGamepadAxis Set(::ControlerID gamepad, Sint32 axis) { return InputBase::Set<InputGamepadAxis>((InputKey)axis, (::ControlerID)gamepad); }
//
//	Sint32 Axis() { return (Sint32)_Key; }
//	Sint32 Value() { return (Sint32)Held(0); }
//
//private:
//	double Down() override { return 0; }
//	double Up() override { return 0; }
//	double Held(Sint32 time = 0) override;
//	friend class InputBase;
//};
//class InputGamepadHat : protected InputBase
//{
//public:
//	static InputGamepadHat Set(::ControlerID gamepad, Sint32 hatID, HatDirections hatDirection);
//
//	Sint32 HatID() { return (Sint32)_Key; }
//	HatDirections HatDirection() { return _HatDirection; }
//
//	double Down() override { return this->InputBase::Down(); }
//	double Up() override { return this->InputBase::Up(); }
//	double Held(Sint32 time = 0) override { return this->InputBase::Held(time); }
//
//	bool operator==(const InputBase& dst) const override;
//	bool operator!=(const InputBase& dst) const override { return *this == dst ? false : true; }
//
//private:
//	friend class InputBase;
//};
//
