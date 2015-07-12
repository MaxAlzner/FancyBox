#ifndef FBOX_GLOBAL_H
#define FBOX_GLBOAL_H

namespace fbox
{

	typedef struct InputState
	{

		MouseState Mouse;
		KeyboardState Key;
		GamepadState Gamepad;

	} InputState;

	extern FBOXAPI InputState Input;

	extern FBOXAPI GlShader* VertexProgram;
	extern FBOXAPI GlShader* FragmentProgram;
	extern FBOXAPI GlProgram* MainProgram;
	extern FBOXAPI Array<GlUniform*> Uniforms;
	extern FBOXAPI Array<GlUniformBlock*> UniformBlocks;

	extern FBOXAPI Array<GlVertexArray*> VertexArrays;
	extern FBOXAPI Array<GlTexture*> Textures;

	extern FBOXAPI ScriptManager* MainScriptManager;
	extern FBOXAPI Array<Actor*> Actors;

}

#endif