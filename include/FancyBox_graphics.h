#ifndef FBOX_GRAPHICS_H
#define FBOX_GRAPHICS_H

#include "FancyBox_setup.h"

namespace fbox
{
	namespace gl
	{
		class FBOXAPI Uniform;
		class FBOXAPI Texture;
		class FBOXAPI Buffer;
		class FBOXAPI UniformBlock;
		class FBOXAPI VertexArray;
		class FBOXAPI Framebuffer;
		class FBOXAPI Shader;
		class FBOXAPI Program;

		class FBOXAPI Uniform
		{
		public:

			typedef GLint locType;

			Uniform() : _program(0), _handle(0) {}
			Uniform(Program* program, string& name) : _program(program), _handle(0), _name(name) {}
			~Uniform() {}

			void grab();

			void bind1i(int x);
			void bind2i(glm::ivec2& v);
			void bind3i(glm::ivec3& v);
			void bind4i(glm::ivec4& v);
			void bind1b(bool x);
			void bind1f(float x);
			void bind2f(glm::vec2& v);
			void bind3f(glm::vec3& v);
			void bind4f(glm::vec4& v);
			void bind1iv(const int* buffer, unsigned int count);
			void bind2iv(const glm::ivec2* buffer, unsigned int count);
			void bind3iv(const glm::ivec3* buffer, unsigned int count);
			void bind4iv(const glm::ivec4* buffer, unsigned int count);
			void bind1bv(const bool* buffer, unsigned int count);
			void bind1fv(const float* buffer, unsigned int count);
			void bind2fv(const glm::vec2* buffer, unsigned int count);
			void bind3fv(const glm::vec3* buffer, unsigned int count);
			void bind4fv(const glm::vec4* buffer, unsigned int count);
			void bind3x3f(glm::mat3& m);
			void bind4x4f(glm::mat4& m);

			void texture(Texture* texture, unsigned int slot);

			bool valid() const;

			const locType handle() const;
			const string name() const;

		protected:

			Program* _program;
			locType _handle;
			string _name;

		};

		class FBOXAPI Texture
		{
		public:

			typedef GLuint handleType;
			typedef GLenum targetType;

			Texture() : _handle(0), _target(0) {}
			~Texture() {}

			enum texParameter
			{
				PARAM_NONE,
				PARAM_WRAP_U_REPEAT,
				PARAM_WRAP_V_REPEAT,
				PARAM_WRAP_U_CLAMP,
				PARAM_WRAP_V_CLAMP,
				PARAM_MIN_FILTER_NEAREST,
				PARAM_MIN_FILTER_LINEAR,
				PARAM_MIN_FILTER_NEAREST_MIPMAP_NEAREST,
				PARAM_MIN_FILTER_LINEAR_MIPMAP_NEAREST,
				PARAM_MIN_FILTER_NEAREST_MIPMAP_LINEAR,
				PARAM_MIN_FILTER_LINEAR_MIPMAP_LINEAR,
				PARAM_MAG_FILTER_NEAREST,
				PARAM_MAG_FILTER_LINEAR,
				PARAM_MIN_LOD,
				PARAM_MAX_LOD,
				PARAM_MAX_LEVEL,
				PARAM_SWIZZLE_R,
				PARAM_SWIZZLE_G,
				PARAM_SWIZZLE_B,
				PARAM_SWIZZLE_A,
			};

			void create();
			void create(surface* surface);
			void release();

			void parameter(texParameter param);
			void parameter(texParameter param, int value);
			void parameter(texParameter param, float value);

			const handleType handle() const;
			const targetType target() const;

		protected:

			handleType _handle;
			targetType _target;

		};

		class FBOXAPI Buffer
		{
		public:

			typedef GLuint handleType;

			enum targetType
			{
				TARGET_NONE = 0,
				TARGET_ARRAY = 1,
				TARGET_ELEMENT_ARRAY = 2,
				TARGET_TEXTURE = 3,
				TARGET_UNIFORM = 4
			};

			enum usageType
			{
				USAGE_NONE = 0,
				USAGE_STATIC_DRAW = 1,
				USAGE_DYNAMIC_DRAW = 2
			};

			Buffer() : _handle(0), _target(TARGET_NONE), _usage(USAGE_NONE) {}
			Buffer(targetType target, usageType usage) : _handle(0), _target(target), _usage(usage) {}
			~Buffer() {}

			void create();
			void release();

			void bind();
			void unbind();

			void map(const void* data, unsigned int bytes);

			const handleType handle() const;
			const targetType target() const;
			const usageType usage() const;

		protected:

			handleType _handle;
			targetType _target;
			usageType _usage;

		};

		class FBOXAPI UniformBlock
		{
		public:

			typedef GLuint indexType;

			UniformBlock() : _program(0), _buffer(0), _handle(0) {}
			UniformBlock(Program* program, string& name) : _program(program), _buffer(0), _handle(0), _name(name) {}
			~UniformBlock() {}

			void grab();
			void release();

			void bind(unsigned int index, void* data, unsigned int bytes);

			bool valid() const;

			const indexType handle() const;
			const string name() const;
			const Buffer* buffer() const;

		protected:

			Program* _program;
			Buffer* _buffer;
			indexType _handle;
			string _name;

		};

		class FBOXAPI VertexArray
		{
		public:

			typedef GLuint handleType;

			enum attribute
			{
				INCLUDE_VERTEX = 1,
				INCLUDE_TEXCOORD = 2,
				INCLUDE_NORMAL = 4,
				INCLUDE_BINORMAL = 8,
				INCLUDE_TANGENT = 16,
				INCLUDE_BONEWEIGHT = 32,
				INCLUDE_BONEINDEX = 64
			};

			VertexArray() : _program(0), _vertices(0), _indices(0), _elements(0), _handle(0) {}
			VertexArray(Program* program) : _program(program), _vertices(0), _indices(0), _elements(0), _handle(0) {}
			~VertexArray() {}

			void create();
			void create(
				const void* data, unsigned int bytes,
				const int* indices, unsigned int elements,
				unsigned int components, attribute attributes, const unsigned int* strides, const unsigned int* offsets);
			void create(shape* shape);
			void release();

			void draw();

			const handleType handle() const;

		protected:

			Program* _program;
			Buffer* _vertices;
			Buffer* _indices;
			unsigned int _elements;
			handleType _handle;

		};

		class FBOXAPI Framebuffer
		{
		public:

			typedef GLuint handleType;

			enum frameType
			{
				TYPE_NONE,
				TYPE_DRAW,
				TYPE_COLOR,
				TYPE_DEPTH,
			};

			Framebuffer() : clearColor(0.0f), _dimensions(400, 300), _main(0), _depth(0), _handle(0), _type(TYPE_NONE) {}
			Framebuffer(frameType type, glm::ivec2& dimensions) : clearColor(0.0f), _dimensions(dimensions), _main(0), _depth(0), _handle(0), _type(type) {}
			~Framebuffer() {}

			void create();
			void release();

			void bind();
			void unbind();

			void clear();
			void resize(glm::ivec2& dimensions);

			void blit(Framebuffer* destination);

			const handleType handle() const;
			Texture* main() const;
			Texture* depth() const;
			glm::ivec2 dimensions() const;

			static void screen(glm::ivec2& dimensions);

			glm::vec4 clearColor;

		protected:

			Texture* _main;
			Texture* _depth;
			handleType _handle;
			frameType _type;
			glm::ivec2 _dimensions;

			static glm::ivec2 _screen;

		};

		class FBOXAPI Shader
		{
		public:

			typedef GLuint handleType;

			enum shaderType
			{
				TYPE_NONE = 0,
				TYPE_VERTEX = 1,
				TYPE_FRAGMENT = 2,
				TYPE_GEOMETRY = 3
			};

			Shader() : _handle(0), _type(TYPE_NONE) {}
			Shader(shaderType type) : _handle(0), _type(type) {}
			~Shader() {}

			void compile(string& filepath);
			void compile(const char* filepath);

			void release();

			const handleType handle() const;

		protected:

			handleType _handle;
			shaderType _type;

		};

		class FBOXAPI Program
		{
		public:

			typedef GLuint handleType;

			Program() : _handle(0), _vertex(0), _fragment(0), _geometry(0) {}
			~Program() {}

			void vertex(Shader* shader);
			void fragment(Shader* shader);
			void geometry(Shader* shader);

			void activate();

			void link();
			void release();

			const handleType handle() const;

		protected:

			Shader* _vertex;
			Shader* _fragment;
			Shader* _geometry;
			handleType _handle;

		};

	}
}

#endif