#ifndef FBOX_GLOBAL_H
#define FBOX_GLBOAL_H

namespace fbox
{

	static struct
	{

		MouseState Mouse;
		KeyboardState Key;
		GamepadState Gamepad;

	} Input;

	static struct
	{

		Array<GlUniform> Uniforms;

	} Renderer;

}

#endif