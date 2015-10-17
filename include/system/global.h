#ifndef FBOX_GLOBAL_H
#define FBOX_GLBOAL_H

namespace fbox
{

	typedef enum UNIFORM_FLAG
	{

		UNIFORM_FLAG_INVALID,

		UNIFORM_FLAG_MATRIX_OBJECT_TO_WORLD,
		UNIFORM_FLAG_MATRIX_WORLD_TO_CAMERA,
		UNIFORM_FLAG_MATRIX_WORLD_TO_LIGHT,
		UNIFORM_FLAG_MATRIX_PROJECTION,

		UNIFORM_FLAG_LIGHT_DIRECTIONAL_VECTOR,
		UNIFORM_FLAG_LIGHT_DIRECTIONAL_COLOR,
		UNIFORM_FLAG_LIGHT_DIRECTIONAL_INTENSITY,
		//UNIFORM_FLAG_LIGHT_POINT_POSITION,
		//UNIFORM_FLAG_LIGHT_POINT_COLOR,
		//UNIFORM_FLAG_LIGHT_POINT_INTENSITY,
		//UNIFORM_FLAG_LIGHT_POINT_RANGE,
		UNIFORM_FLAG_LIGHT_POINT_NUM,
		//UNIFORM_FLAG_LIGHT_SPOT_POSITION,
		//UNIFORM_FLAG_LIGHT_SPOT_VECTOR,
		//UNIFORM_FLAG_LIGHT_SPOT_COLOR,
		//UNIFORM_FLAG_LIGHT_SPOT_INTENSITY,
		//UNIFORM_FLAG_LIGHT_SPOT_RANGE,
		UNIFORM_FLAG_LIGHT_SPOT_NUM,

		UNIFORM_FLAG_COLOR_OVERLAY,
		UNIFORM_FLAG_COLOR_HIGHLIGHT,
		UNIFORM_FLAG_BRDF_ROUGHNESS,
		UNIFORM_FLAG_BRDF_REFRACTION_INDEX,
		UNIFORM_FLAG_UV_REPEAT,
		UNIFORM_FLAG_UV_OFFSET,

		UNIFORM_FLAG_SIZE_SCREEN,
		UNIFORM_FLAG_SIZE_MAP,
		UNIFORM_FLAG_FILTER_RANDOM,
		UNIFORM_FLAG_GAMMA,

		UNIFORM_FLAG_MAP_COLOR,
		UNIFORM_FLAG_MAP_NORMAL,
		UNIFORM_FLAG_MAP_SPECULAR,

		UNIFORM_FLAG_STATE,

	} UNIFORM_FLAG;

	typedef enum UNIFORM_BLOCK
	{

		UNIFORM_BLOCK_INVALID,

		UNIFORM_BLOCK_LIGHT_POINT1,
		UNIFORM_BLOCK_LIGHT_POINT2,
		UNIFORM_BLOCK_LIGHT_POINT3,
		UNIFORM_BLOCK_LIGHT_POINT4,
		UNIFORM_BLOCK_LIGHT_SPOT1,
		UNIFORM_BLOCK_LIGHT_SPOT2,
		UNIFORM_BLOCK_LIGHT_SPOT3,
		UNIFORM_BLOCK_LIGHT_SPOT4,

	} UNIFORM_BLOCK;

	typedef enum UNIFORM_MODE
	{

		UNIFORM_MODE_NONE,
		UNIFORM_MODE_NORMAL,
		UNIFORM_MODE_SHADOW_MAP,
		UNIFORM_MODE_PREVIOUS,

	} UNIFORM_MODE;

	typedef struct InputState
	{

		MouseState Mouse;
		KeyboardState Key;
		GamepadState Gamepad;

	} InputState;

	typedef struct TextureAsset
	{

		surface* Surface;
		gl::Texture* Texture;
		string Filename;

	} TextureAsset;

	typedef struct MeshAsset
	{

		shape* Shape;
		gl::VertexArray* VertexArrayObject;
		string Filename;

	} MeshAsset;

	//typedef struct AudioAsset
	//{

	//	Sound::Track* Track;
	//	al::Buffer* Buffer;
	//	string Filename;

	//} SoundAsset;

	extern FBOXAPI InputState Input;

	extern FBOXAPI Camera* MainCamera;
	extern FBOXAPI Scene* MainScene;

	extern FBOXAPI gl::Shader* VertexProgram;
	extern FBOXAPI gl::Shader* FragmentProgram;
	extern FBOXAPI gl::Program* MainProgram;
	extern FBOXAPI std::vector<gl::Uniform> Uniforms;
	extern FBOXAPI std::vector<gl::UniformBlock> UniformBlocks;
	extern FBOXAPI std::vector<gl::VertexArray*> VertexArrays;
	extern FBOXAPI std::vector<gl::Texture*> Textures;

	//extern FBOXAPI std::vector<Media*> Assets;
	extern FBOXAPI std::list<TextureAsset> TextureAssets;
	extern FBOXAPI std::list<MeshAsset> MeshAssets;
	//extern FBOXAPI std::list<AudioAsset> AudioAssets;

	FBOXAPI extern void ReleaseAssets();

	FBOXAPI extern void GrabUniforms();

	FBOXAPI extern UNIFORM_FLAG GetUniformFlag(string& name);
	FBOXAPI extern UNIFORM_BLOCK GetUniformBlockFlag(string& name);

	FBOXAPI extern gl::Uniform* GetUniform(UNIFORM_FLAG flag);
	FBOXAPI extern gl::UniformBlock* GetUniformBlock(UNIFORM_BLOCK block);

	class FBOXAPI Frame
	{
	public:

		typedef __int64 frameValue;
		typedef __int64 clockValue;
		typedef float timeValue;

		static frameValue Count;
		static frameValue Current;
		static frameValue Rate;

		static timeValue FixedTime;
		static timeValue DeltaTime;

		static void SetFramesPerSecond(frameValue fps);

		static void Start();
		static void Finish();

	protected:

		static clockValue Ping;
		static clockValue LastFrameTicks;
		static clockValue LastSecond;

		static frameValue FramesPerSecond;
		static clockValue TicksPerSecond;
		static clockValue TicksPerFrame;

	};

	class FBOXAPI Import
	{
	public:

		typedef rapidxml::xml_document<char> XmlDocument;
		typedef rapidxml::xml_node<char> XmlNode;
		typedef rapidxml::xml_attribute<char> XmlAttribute;

		static int Read(string& filename, char** outRaw);

		static void Parse(string& filename);

		static void Register(string& filename, gl::Texture** outTexture);
		static void Register(string& filename, gl::VertexArray** outVertexArray);

	protected:

		static void ParseScript(XmlNode* node);
		static void ParseScene(XmlNode* node);
		static void ParseActor(XmlNode* node);

		static void ParseTransform(XmlNode* node, Transform* transform);
		static MeshFilter* ParseMesh(XmlNode* node);
		static TextureFilter* ParseTexture(XmlNode* node);
		static Material* ParseMaterial(XmlNode* node);
		static Behavior* ParseBehavior(XmlNode* node);
		static Camera* ParseCamera(XmlNode* node);
		static Light* ParseLight(XmlNode* node);

		static int ParseInt(XmlNode* node, int defaultValue = 0);
		static int ParseInt(XmlAttribute* attr, int defaultValue = 0);
		static float ParseFloat(XmlNode* node, float defaultValue = 0.0f);
		static float ParseFloat(XmlAttribute* attr, float defaultValue = 0.0f);
		static bool ParseBool(XmlNode* node, bool defaultValue = false);
		static bool ParseBool(XmlAttribute* attr, bool defaultValue = false);
		static glm::vec4 ParseColor(XmlNode* node);
		static glm::vec4 ParseColor(XmlAttribute* attr);
		static string Value(XmlAttribute* attr);

	};

}

#endif