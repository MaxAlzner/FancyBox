#ifndef FBOX_GLSHADER_H
#define FBOX_GLSHADER_H

namespace fbox
{
	namespace gl
	{

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

			Shader() : _handle(0), _type(TYPE_NONE), _raw(0) {}
			Shader(shaderType type) : _handle(0), _type(type), _raw(0) {}
			~Shader() {}

			void read(string& filepath);
			void read(const char* filepath);

			void compile();
			void release();

			const handleType handle() const;

		protected:

			handleType _handle;
			shaderType _type;
			char* _raw;

		};

	}
}

#endif