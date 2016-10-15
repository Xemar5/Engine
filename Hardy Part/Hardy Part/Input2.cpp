//#include "Input2.h"
//
//
//
//bool InputBase::operator==(const InputBase & dst) const
//{
//	if (_Type == InputType::Undefined || dst._Type == InputType::Undefined) return false;
//	if (_Key == InputKey::Undefined || dst._Key == InputKey::Undefined) return false;
//	if (_State == InputState::Undefined || dst._State == InputState::Undefined) return false;
//
//	if (_Type != InputType::Any				&& dst._Type != InputType::Any				&& _Type != dst._Type) return false;
//	if (_Key != InputKey::Any				&& dst._Key != InputKey::Any				&& _Key != dst._Key) return false;
//	if (_State != InputState::Any			&& dst._State != InputState::Any			&& _State != dst._State) return false;
//	return true;
//}
//
//
//
//
//
//
//
//double InputBase::Down()
//{
//	if (!this) return 0.0;
//	if(_Type == InputType::Undefined) return 0;
//	return _State == InputState::Pushed ? 1 : 0;
//}
//
//double InputBase::Up()
//{
//	if (!this) return 0.0;
//	if (_Type == InputType::Undefined) return 0;
//	return _State == InputState::Released ? 1 : 0;
//}
//
//double InputBase::Held(Sint32 time)
//{
//	if (!this) return 0.0;
//	switch (_Type)
//	{
//	case InputType::MouseAxis: return dynamic_cast<InputMouseButton*>(this)->Held(); break;
//	case InputType::GamepadAxis: return dynamic_cast<InputMouseButton*>(this)->Held(); break;
//	case InputType::Undefined: return 0; break;
//	default: return _State == InputState::Held ? _Time : 0; break;
//	}
//	return 0.0;
//}
//
//
//
//
//
//
//
//
//double InputMouseAxis::Held(Sint32 time)
//{
//	return 0.0;
//}
//
//
//double InputGamepadAxis::Held(Sint32 time)
//{
//	return 0.0;
//}
//
//InputGamepadHat InputGamepadHat::Set(::ControlerID gamepad, Sint32 hatID, HatDirections hatDirection)
//{
//	auto i = InputBase::Set<InputGamepadHat>((InputKey)hatID, (::ControlerID)gamepad);
//	i._HatDirection = hatDirection;
//	return i;
//}
//
//bool InputGamepadHat::operator==(const InputBase & dst) const
//{
//	if (*this != dst) return false;
//
//	InputBase gh = dst;
//	auto ghp = dynamic_cast<InputGamepadHat*>(&gh);
//	if (!ghp) return false;
//	if (_HatDirection != HatDirections::Any	&& ghp->_HatDirection != HatDirections::Any	&& _HatDirection != ghp->_HatDirection) return false;
//
//	return true;
//}
