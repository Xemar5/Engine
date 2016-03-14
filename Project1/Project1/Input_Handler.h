#pragma once

class Input_Handler
{
	//*** Updates the Keyboard Handler and Gamepad Handler
	static void __Update();
	//*** Handles events in Keyboard Handler and Gamepad Handler
	static void __Events();

	friend class System;
};