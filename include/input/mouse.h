#ifndef FBOX_MOUSE_H
#define FBOX_MOUSE_H

namespace fbox
{

	typedef enum MouseButton
	{
		BUTTON_LEFT = 0,
		BUTTON_MIDDLE = 1,
		BUTTON_RIGHT = 2,
	} MouseButton;

	typedef struct MouseState
	{

		inline MouseState() : position(0.0f), scroll(0.0f), active(false) {}
		inline ~MouseState() {}

		vec2 position;
		float scroll;
		Button left;
		Button right;
		Button middle;
		bool active;

	} MouseState;

}

#endif