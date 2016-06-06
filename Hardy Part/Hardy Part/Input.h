#pragma once
#include <string>

enum Input_Type
{
	IT_UNDEFINED,
	IT_ANY,
	IT_KEYBOARD_KEY,
	IT_GAMEPAD_BUTTON,
	IT_GAMEPAD_AXIS,
	IT_GAMEPAD_HAT,
	IT_MOUSE_BUTTON,
	IT_MOUSE_AXIS
};

enum Input_State
{
	IS_UNDEFINED = -(1 << 15) - 4,
	IS_ANY = -(1 << 15) - 3,
	IS_RELEASED = -(1 << 15) - 2,
	IS_PUSHED = -(1 << 15) - 1
};
enum Input_Key
{
	IK_UNDEFINED = -1,
	IK_ANY = -2
};

typedef double(*Input_Foo)(Sint32&);
typedef double(*Input_Foo_Held)(Sint32&, Sint32);

class Input
{
public:
	//*** Creates a new Input object
	//*** - type - the type of the input (see Input_Type enum)
	//*** - key - the key that is being pushed/released/moved/held (see Input_Key enum)
	//*** - state - the initial state value for this Input (see Input_State enum)
	static Input Set(Sint32 type = IT_ANY, Sint32 key = IK_ANY, Input_State state = IS_ANY);

	//*** Converts the index to a specialized Hat index
	//*** Use when setting a hat Input
	static Uint32 Hat(Uint32 index = 0) { return index << 4; };
	//*** Returns the hat index based on the given key
	static Uint32 Which_Hat(Uint32 key) { return key >> 4; };

	//*** Converts the given controller id to a specialized Key Type index
	//*** Use when setting an Input for any joystick
	static Input_Type Controller(Uint32 ID) { return (Input_Type)((ID << 4) | (1 << 3)); };
	//*** Returns the controller index based on the given type
	static Sint32 Which_Controller(Uint32 type) { return (type & (1 << 3)) ? type >> 4 : -1; };

	//*** The state of this Input
	Sint32 State = IS_UNDEFINED;
	//*** Returns the key bound to this Input
	Sint32 Key() const { return __Key; };
	//*** Returns the type of this Input
	Input_Type Type() const { return __Type; };

	//*** Returns a value when tha Input has been used  
	double Down();
	//*** Returns a value when the Input is no longer in use
	double Up();
	//*** Returns continously updated value of the Input
	//*** - time - the amount of time this Input needs to wait before returning a value
	double Held(Sint32 time = 0);

	explicit operator bool() const { return (*this == Set() ? false : true); }
	bool operator==(const Input& dst) const;
	bool operator!=(const Input& dst) const { return *this == dst ? false : true; };

private:
	//*** The type of this Input
	Input_Type __Type = IT_UNDEFINED;
	//*** The Key this Input is bound to
	Sint32 __Key = IK_UNDEFINED;

	friend class Device;
	friend class Mapping;
};