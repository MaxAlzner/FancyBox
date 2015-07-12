
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI InputState Input;

	FBOXAPI GlShader* VertexProgram = 0;
	FBOXAPI GlShader* FragmentProgram = 0;
	FBOXAPI GlProgram* MainProgram = 0;
	FBOXAPI Array<GlUniform*> Uniforms;
	FBOXAPI Array<GlUniformBlock*> UniformBlocks;

	FBOXAPI Array<GlVertexArray*> VertexArrays;
	FBOXAPI Array<GlTexture*> Textures;

	FBOXAPI ScriptManager* MainScriptManager = 0;
	FBOXAPI Array<Actor*> Actors;

}