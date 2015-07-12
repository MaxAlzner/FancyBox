#ifndef FBOX_GAMEPAD_H
#define FBOX_GAMEPAD_H

namespace fbox
{

	typedef enum ButtonCode
	{
		BUTTON_A = 0,
		BUTTON_B = 1,
		BUTTON_X = 2,
		BUTTON_Y = 3,
		BUTTON_L_BUMPER = 4,
		BUTTON_R_BUMPER = 5,
		BUTTON_BACK = 6,
		BUTTON_START = 7,
		BUTTON_L_STICK = 8,
		BUTTON_R_STICK = 9,
	} ButtonCode;

	typedef enum DPadCode
	{
		DPAD_UP = 0,
		DPAD_UP_RIGHT = 1,
		DPAD_RIGHT = 2,
		DPAD_DOWN_RIGHT = 3,
		DPAD_DOWN = 4,
		DPAD_DOWN_LEFT = 5,
		DPAD_LEFT = 6,
		DPAD_UP_LEFT = 7,
	} DPadCode;

	typedef enum AxisCode
	{
		AXIS_L_STICK_X = 0,
		AXIS_L_STICK_Y = 1,
		AXIS_L_TRIGGER = 2,
		AXIS_R_STICK_X = 3,
		AXIS_R_STICK_Y = 4,
		AXIS_R_TRIGGER = 5,
	} AxisCode;

	typedef struct GamepadState
	{

		inline GamepadState() : connected(false), user(-1) {}
		inline ~GamepadState() {}

		struct
		{
			Axis x;
			Axis y;
		} stickLeft;

		struct
		{
			Axis x;
			Axis y;
		} stickRight;

		Axis triggerLeft;
		Axis triggerRight;

		Button a;
		Button b;
		Button x;
		Button y;
		Button bumperLeft;
		Button bumperRight;
		Button back;
		Button start;
		Button stickButtonLeft;
		Button stickButtonRight;

		struct
		{
			Button up;
			Button right;
			Button down;
			Button left;
		} dpad;

		bool connected;
		int user;

	} GamepadState;

}

#endif