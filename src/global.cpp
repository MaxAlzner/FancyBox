
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

	FBOXAPI Array<Media*> Assets;
	FBOXAPI List<TextureAsset> TextureAssets;
	FBOXAPI List<MeshAsset> MeshAssets;
	FBOXAPI List<AudioAsset> AudioAssets;
	FBOXAPI List<ScriptAsset> ScriptAssets;

	FBOXAPI ScriptManager* MainScriptManager = 0;
	FBOXAPI Camera* MainCamera = 0;
	FBOXAPI Scene* MainScene = 0;

}