#ifndef FBOX_GLUNIFORMBLOCK_H
#define FBOX_GLUNIFORMBLOCK_H

namespace fbox
{
	namespace gl
	{

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

	}
}

#endif