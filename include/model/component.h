#ifndef FBOX_COMPONENT_H
#define FBOX_COMPONENT_H

namespace fbox
{

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
			parent(parent != this ? parent : 0) { this->zero(); }
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
		inline Light(LIGHTTYPE lightType, glm::vec4& color, const float intensity) :
			Component("Light"),
			lightType(lightType),
			color(color),
			intensity(intensity),
			range(5.0f),
			angle(60.0f) {}
		inline Light(LIGHTTYPE lightType, glm::vec4& color, const float intensity, const float range) :
			Component("Light"),
			lightType(lightType),
			color(color),
			intensity(intensity),
			range(range),
			angle(60.0f) {}
		inline Light(LIGHTTYPE lightType, glm::vec4& color, const float intensity, const float range, const float angle) :
			Component("Light"),
			lightType(lightType),
			color(color),
			intensity(intensity),
			range(range),
			angle(angle) {}
		inline ~Light() {}

		void bind();

		LIGHTTYPE lightType;
		glm::vec4 color;
		float intensity;
		float range;
		float angle;

	protected:

	};

}

#endif