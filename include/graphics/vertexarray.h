#ifndef FBOX_GLVERTEXARRY_H
#define FBOX_GLVERTEXARRY_H

namespace fbox
{
	namespace gl
	{

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

	}
}

#endif