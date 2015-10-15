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

	}
}

#endif