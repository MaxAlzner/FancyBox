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

	typedef struct TextureAsset
	{

		Image::Surface* Surface;
		GlTexture* Texture;
		String Filepath;

	} TextureAsset;

	typedef struct MeshAsset
	{

		Mesh::Shape* Shape;
		GlVertexArray* VertexArrayObject;
		String Filepath;

	} MeshAsset;

	typedef struct AudioAsset
	{

		Sound::Track* Track;
		AlBuffer* Buffer;
		String Filepath;

	} SoundAsset;

	typedef struct ScriptAsset
	{

		ScriptFile* Script;
		String Filepath;

	} ScriptAsset;

	extern FBOXAPI InputState Input;

	extern FBOXAPI GlShader* VertexProgram;
	extern FBOXAPI GlShader* FragmentProgram;
	extern FBOXAPI GlProgram* MainProgram;
	extern FBOXAPI Array<GlUniform*> Uniforms;
	extern FBOXAPI Array<GlUniformBlock*> UniformBlocks;
	extern FBOXAPI Array<GlVertexArray*> VertexArrays;
	extern FBOXAPI Array<GlTexture*> Textures;

	extern FBOXAPI Array<Media*> Assets;
	extern FBOXAPI List<TextureAsset> TextureAssets;
	extern FBOXAPI List<MeshAsset> MeshAssets;
	extern FBOXAPI List<AudioAsset> AudioAssets;
	extern FBOXAPI List<ScriptAsset> ScriptAssets;

	extern FBOXAPI Camera* MainCamera;
	extern FBOXAPI Scene* MainScene;

}

#endif