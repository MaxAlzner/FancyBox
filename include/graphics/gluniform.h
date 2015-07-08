#ifndef FBOX_UNIFORM_H
#define FBOX_UNIFORM_H

namespace fbox
{

	class FBOXAPI GlUniform
	{
	public:

		typedef GLint locType;

		GlUniform() : _program(0), _handle(0) {}
		GlUniform(GlProgram* program, String name) : _program(program), _handle(0), _name(name) {}
		~GlUniform() {}

		void grab();

		void bind1i(int x);
		void bind2i(ivec2& v);
		void bind3i(ivec3& v);
		void bind4i(ivec4& v);
		void bind1b(bool x);
		void bind1f(float x);
		void bind2f(vec2& v);
		void bind3f(vec3& v);
		void bind4f(vec4& v);
		void bind4f(Color& c);
		void bind1iv(const int* buffer, unsigned int count);
		void bind2iv(const ivec2* buffer, unsigned int count);
		void bind3iv(const ivec3* buffer, unsigned int count);
		void bind4iv(const ivec4* buffer, unsigned int count);
		void bind1bv(const bool* buffer, unsigned int count);
		void bind1fv(const float* buffer, unsigned int count);
		void bind2fv(const vec2* buffer, unsigned int count);
		void bind3fv(const vec3* buffer, unsigned int count);
		void bind4fv(const vec4* buffer, unsigned int count);
		void bind4fv(const Color* buffer, unsigned int count);
		void bind3x3f(mat3& m);
		void bind4x4f(mat4& m);

		void texture(GlTexture* texture, unsigned int slot);

		const locType handle() const;
		const String name() const;

	protected:

		GlProgram* _program;
		locType _handle;
		String _name;

	};

}

#endif