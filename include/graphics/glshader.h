#ifndef FBOX_SHADER_H
#define FBOX_SHADER_H

namespace fbox
{

	class FBOXAPI GlShader
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

		GlShader() : _file(0), _handle(0), _type(TYPE_NONE) {}
		GlShader(shaderType type) : _file(0), _handle(0), _type(type) {}
		~GlShader() {}

		void read(String filepath);

		void compile();
		void release();

		const handleType handle() const;

	protected:

		File* _file;
		handleType _handle;
		shaderType _type;

	};

}

#endif