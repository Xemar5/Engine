#pragma once
#include <string>
class Device;

enum Input_Type
{
	IT_UNDEFINED =		0b000000,
	IT_ANY =			0b11111111,
	IT_KEYBOARD_KEY =	0b000001,
	IT_GAMEPAD_BUTTON = 0b000010,
	IT_GAMEPAD_AXIS =	0b000100,
	IT_GAMEPAD_HAT =	0b001000,
	IT_MOUSE_BUTTON =	0b010000,
	IT_MOUSE_AXIS =		0b100000
};

enum Input_State
{
	IS_UNDEFINED,
	IS_ANY,
	IS_RELEASED,
	IS_PUSHED,
	IS_MOVING = 4,
	IS_HELD = 4
};
enum Input_Key
{
	IK_UNDEFINED = -1,
	IK_ANY = -2
};
enum Mouse_Input
{
	MI_AXIS,
	MI_BUTTON
};
enum Mouse_Axis
{
	MA_X,
	MA_Y
};
enum Hat_Directions
{
	HD_ANY = -1,
	HD_NONE = 0b0000,
	HD_U = 0b0001,
	//HD_UR = 0b0011,
	//HD_UL = 0b1001,
	HD_D = 0b0100,
	//HD_DR = 0b0110,
	//HD_DL = 0b1100,
	HD_R = 0b0010,
	HD_L = 0b1000,
};
enum Controller_Index
{
	CI_UNDEFINED = -3,
	CI_ANY = -2,
	CI_KEYBOARD_MOUSE = -1
};
enum Input_Variant
{
	IV_ANY = -1,
	IV_AXIS_DEFAULT = 0,
	IV_AXIS_INVERTED = 1,
	IV_AXIS_HALVED = 2,
	AT_AXIS_INVERTED_HALVED = 3
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
	static Input Set(Sint32 type = IT_ANY, Sint32 key = IK_ANY, Sint32 controllerID = CI_ANY, Sint32 variant = IV_ANY, Input_State state = IS_ANY);


	//*** Current value of this input
	Sint32 Value = 0;
	//*** The state of this Input
	Input_State State = IS_UNDEFINED;


	//*** Returns the key bound to this Input
	Sint32 Key() const { return __Key; }
	//*** Returns the key bound to this Input
	std::string KeyName() const;
	//*** Returns the type of this Input
	Input_Type Type() const { return (Input_Type)__Type; }
	//*** Returns the controller id this input is comming from
	Controller_Index ControllerID() const { return __ControllerID; }
	//*** Returns the device this input is comming from
	Device& Controller() const;
	//*** Returns the variant of this input
	//*** Used in Gamepad Hats and Gamepad Axes
	Sint32 Variant() const { return __Variant; }

	//*** Returns 1 value when the Input has just been used  
	double Down();
	//*** Returns 1 value when the Input is no longer in use
	double Up();
	//*** Returns 1 value when the Input has been released before ClickTime
	double Click();
	//*** Returns continously updated value of the Input
	//*** - time - the amount of time this Input needs to wait before returning a value
	double Held(Sint32 time = 0);

	static double ClickTime;

	explicit operator bool() const { return (*this == Set() ? false : true); }
	bool operator==(const Input& dst) const;
	bool operator!=(const Input& dst) const { return *this == dst ? false : true; };

private:
	//*** The additional Variant of this input
	//*** -1 - Any Variant possible
	//*** Use in Gamepad Axes:
	//*** 0 - default
	//*** 1 - inverted
	//*** 2 - halved
	//*** 3 - inverted and halved
	//*** Use in Gamepad Hats:
	//*** 0,1,2... - the index of the hat
	Sint32 __Variant = -1;
	//*** The time this input was used at
	//*** Used in Buttons/Keys
	Sint32 __Time = -1;
	//*** The type of this Input
	Uint8 __Type = IT_UNDEFINED;
	//*** The Key this Input is bound to
	Sint32 __Key = IK_UNDEFINED;
	//*** The Controller id this input is comming from
	Controller_Index __ControllerID = CI_UNDEFINED;

	////*** Handles Mouse Axis Up and Down functions 
	//double __Handle_Mouse_Axis(Input* input);


	friend class Device;
	friend class Gamepad;
	friend class Keyboard;
	friend class Mapping;
};