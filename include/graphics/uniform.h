#ifndef FBOX_GLUNIFORM_H
#define FBOX_GLUNIFORM_H

namespace fbox
{
	namespace gl
	{

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

	}
}

#endif