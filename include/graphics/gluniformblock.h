#ifndef FBOX_UNIFORMBLOCK_H
#define FBOX_UNIFORMBLOCK_H

namespace fbox
{

	class FBOXAPI GlUniformBlock
	{
	public:

		typedef GLuint indexType;

		GlUniformBlock() : _program(0), _buffer(0), _handle(0) {}
		GlUniformBlock(GlProgram* program, String name) : _program(program), _buffer(0), _handle(0), _name(name) {}
		~GlUniformBlock() {}

		void grab();
		void release();

		void bind(void* data, unsigned int bytes);

		const indexType handle() const;
		const String name() const;
		const GlBuffer* buffer() const;

	protected:

		GlProgram* _program;
		GlBuffer* _buffer;
		indexType _handle;
		String _name;

	};

}

#endif