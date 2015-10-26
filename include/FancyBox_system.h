#ifndef FBOX_SYSTEM_H
#define FBOX_SYSTEM_H

#include "FancyBox_setup.h"
#include "FancyBox_input.h"
#include "FancyBox_graphics.h"

namespace fbox
{

	class FBOXAPI Component;
	class FBOXAPI Transform;
	class FBOXAPI MeshFilter;
	class FBOXAPI TextureFilter;
	class FBOXAPI Material;
	class FBOXAPI Behavior;
	class FBOXAPI Camera;
	class FBOXAPI Light;
	
	class FBOXAPI Actor;
	class FBOXAPI Scene;
	
	class FBOXAPI Schema;

	class FBOXAPI Component
	{
	public:

		inline Component() {}
		inline Component(string& type) : componentType(type) {}
		inline Component(const char* type) : componentType(type) {}
		inline ~Component() {}

		virtual void bind() = 0;

		Actor* object;
		string componentType;

	};

	class FBOXAPI Transform : public Component
	{
	public:

		inline Transform() : Component("Transform"), parent(0) { this->zero(); }
		inline Transform(Transform* parent) :
			Component("Transform"),
			parent(parent != this ? parent : 0) {
			this->zero();
		}
		inline ~Transform() {}

		void bind();

		void recalculate();
		void zero();

		void look(const glm::vec3& focus);

		const Transform* parent;
		glm::mat4 transformation;
		glm::mat4 space;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 right;
		glm::vec3 up;
		glm::vec3 forward;

	};

	class FBOXAPI MeshFilter : public Component
	{
	public:

		inline MeshFilter() : Component("MeshFilter") {}
		inline MeshFilter(gl::VertexArray* vao) : Component("MeshFilter"), vao(vao) {}
		inline ~MeshFilter() {}

		void bind();

		gl::VertexArray* vao;

	};

	class FBOXAPI TextureFilter : public Component
	{
	public:

		enum TEXTURETYPE
		{
			TEXTURE_NONE,
			TEXTURE_COLOR,
			TEXTURE_NORMAL,
			TEXTURE_SPECULAR,
			TEXTURE_TRANSPARENCY,
			TEXTURE_REFLECT,
			TEXTURE_EMISSIVE,
			TEXTURE_DISPLACEMENT,
		};

		inline TextureFilter() : Component("TextureFilter"), type(TEXTURE_NONE) {}
		inline TextureFilter(const TEXTURETYPE type, gl::Texture* texture) :
			Component("TextureFilter"),
			type(type),
			texture(texture) {}
		inline ~TextureFilter() {}

		void bind();

		const TEXTURETYPE type;
		gl::Texture* texture;

	};

	class FBOXAPI Material : public Component
	{
	public:

		inline Material() : Component("Material") {}
		inline ~Material() {}

		void bind();

	};

	class FBOXAPI Behavior : public Component
	{
	public:

		inline Behavior() : Component("Behavior") {}
		inline Behavior(string& name) : Component("Behavior"), name(name) {}
		inline Behavior(const char* name) : Component("Behavior"), name(name) {}
		inline ~Behavior() {}

		void bind();

		void start();
		void end();
		void update();

		string name;
		js::Object state;

	};

	class FBOXAPI Camera : public Component
	{
	public:

		inline Camera() :
			Component("Camera"),
			aperture(0.0f),
			clipping(0.0f),
			fov(0.0f) {}
		inline Camera(const glm::vec2& aperture, const glm::vec2& clipping, const float fov) :
			Component("Camera"),
			aperture(aperture),
			clipping(clipping),
			fov(fov) {}
		inline ~Camera() {}

		void bind();

		void adjust(float width, float height);

		//inline ray getRay(float u, float v);
		//inline ray getRay(vec2& uv);

		glm::vec2 aperture;
		glm::vec2 clipping;
		float fov;

	protected:

		struct
		{

			glm::vec3 p1;
			glm::vec3 p2;
			glm::vec3 p3;
			glm::vec3 p4;
			glm::vec3 px;
			glm::vec3 py;
			glm::vec3 focal;

		} viewport;

	};

	class FBOXAPI Light : public Component
	{
	public:

		enum LIGHTTYPE
		{
			LIGHT_NONE,
			LIGHT_DIRECTIONAL,
			LIGHT_POINT,
			LIGHT_SPOT,
		};

		inline Light() :
			Component("Light"),
			lightType(LIGHT_NONE),
			color(1.0f),
			intensity(1.0f),
			range(5.0f),
			angle(60.0f) {}
		inline Light(LIGHTTYPE lightType) :
			Component("Light"),
			lightType(lightType),
			color(1.0f),
			intensity(1.0f),
			range(5.0f),
			angle(60.0f) {}
		inline ~Light() {}

		void bind();

		LIGHTTYPE lightType;
		glm::vec4 color;
		float intensity;
		float range;
		float angle;

	protected:

	};

	class FBOXAPI Actor
	{
	public:

		inline Actor() :
			transform(0),
			meshfilter(0),
			material(0),
			camera(0),
			light(0)
		{
			this->add(new Transform);
		}
		inline ~Actor() {}

		void dispose();

		bool empty() const;

		void start();
		void update();
		void render();

		void add(Component* component);

		Component* findComponent(string& type);
		Component* findComponent(const char* type);

		string name;
		Transform* transform;
		MeshFilter* meshfilter;
		Material* material;
		Camera* camera;
		Light* light;
		std::list<Component*> components;
		std::list<TextureFilter*> texturefilters;
		std::list<Behavior*> behaviors;

	};

	class FBOXAPI Scene
	{
	public:

		inline Scene() {}
		inline ~Scene() {}

		void dispose();

		bool empty() const;

		void start();
		void update();
		void render();

		void add(Actor* actor);

		Actor* findActor(string& name);
		Actor* findActor(const char* name);

		string name;
		std::list<Actor*> actors;

	};

	class FBOXAPI Schema
	{
	public:

		typedef rapidxml::xml_document<char> XmlDocument;
		typedef rapidxml::xml_node<char> XmlNode;
		typedef rapidxml::xml_attribute<char> XmlAttribute;

		typedef struct ComponentModel
		{

			string type;
			std::map<string, string> attributes;

		} ComponentModel;

		typedef struct ActorModel
		{

			string name;
			std::list<ComponentModel*> transforms;
			std::list<ComponentModel*> components;

		} ActorModel;

		inline Schema() {}
		inline ~Schema() {}

		void release();

		void parse(string& filename);
		void parse(XmlNode* node);
		void parse(XmlNode* node, ActorModel* actor);
		void parse(XmlNode* node, ComponentModel* component);

		void apply(Scene* scene);

		std::list<string> scripts;
		std::list<ActorModel*> actors;

	protected:

		static string value(XmlAttribute* attribute);
		static float fvalue(string& str, float def = 0.0f);
		static int ivalue(string& str, int def = 0);
		static bool bvalue(string& str, bool def = false);
		static glm::vec4 color(string& str);

	};

	typedef enum FBOXAPI UNIFORM_FLAG
	{

		UNIFORM_FLAG_INVALID,

		UNIFORM_FLAG_MATRIX_OBJECT_TO_WORLD,
		UNIFORM_FLAG_MATRIX_WORLD_TO_CAMERA,
		UNIFORM_FLAG_MATRIX_WORLD_TO_LIGHT,
		UNIFORM_FLAG_MATRIX_PROJECTION,

		UNIFORM_FLAG_LIGHT_DIRECTIONAL_VECTOR,
		UNIFORM_FLAG_LIGHT_DIRECTIONAL_COLOR,
		UNIFORM_FLAG_LIGHT_DIRECTIONAL_INTENSITY,
		UNIFORM_FLAG_LIGHT_POINT_NUM,
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

	typedef enum FBOXAPI UNIFORM_BLOCK
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

	typedef enum FBOXAPI UNIFORM_MODE
	{

		UNIFORM_MODE_NONE,
		UNIFORM_MODE_NORMAL,
		UNIFORM_MODE_SHADOW_MAP,
		UNIFORM_MODE_PREVIOUS,

	} UNIFORM_MODE;

	typedef struct FBOXAPI TextureAsset
	{

		surface* Surface;
		gl::Texture* Texture;
		string Filename;

	} TextureAsset;

	typedef struct FBOXAPI MeshAsset
	{

		shape* Shape;
		gl::VertexArray* VertexArrayObject;
		string Filename;

	} MeshAsset;

	class FBOXAPI Input
	{
	public:

		static MouseState Mouse;
		static KeyboardState Key;
		static GamepadState Gamepad;

	};

	class FBOXAPI Stage
	{
	public:

		static Scene* CurrentScene;

		static std::list<Scene*> Scenes;
		static std::list<Schema*> Schemas;

		static void Release();

		static void Build();

	};

	class FBOXAPI Renderer
	{
	public:

		static glm::ivec2 Screen;
		static glm::ivec2 MainRender;
		static Camera* MainCamera;

		static gl::Shader* VertexProgram;
		static gl::Shader* FragmentProgram;
		static gl::Program* MainProgram;
		static gl::Framebuffer* MainFramebuffer;
		static std::vector<gl::Uniform> Uniforms;
		static std::vector<gl::UniformBlock> UniformBlocks;
		static std::vector<gl::VertexArray*> VertexArrays;
		static std::vector<gl::Texture*> Textures;

		static std::list<TextureAsset> TextureAssets;
		static std::list<MeshAsset> MeshAssets;

		static void Initialize();
		static void Dispose();

		static void Release();

		static void GrabUniforms();

		static UNIFORM_FLAG GetUniformFlag(string& name);
		static UNIFORM_BLOCK GetUniformBlockFlag(string& name);

		static gl::Uniform* GetUniform(UNIFORM_FLAG flag);
		static gl::UniformBlock* GetUniformBlock(UNIFORM_BLOCK block);

	};

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

		static string VertexShader;
		static string FragmentShader;

		static int Read(string& filename, char** outRaw);

		static void Config(string& filename);
		static void Config(const char* filename);

		static void Load(string& filename);
		static void Load(const char* filename);

		static void Model(string& filename);

		static void Register(string& filename, gl::Texture** outTexture);
		static void Register(string& filename, gl::VertexArray** outVertexArray);

	};

	class FBOXAPI Event
	{
	public:

		static void OnPreInitialize();
		static void OnInitialize();
		static void OnDispose();

		static void OnLoad();
		static void OnUnload();

		static void OnReshape(int width, int height);

		static void OnStart();
		static void OnUpdate();
		static void OnDraw();

	};
}

#endif