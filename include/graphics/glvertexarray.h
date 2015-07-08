#ifndef FBOX_VERTEXARRY_H
#define FBOX_VERTEXARRY_H

namespace fbox
{

	class FBOXAPI GlVertexArray
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

		GlVertexArray() : _program(0), _vertices(0), _indices(0), _elements(0), _handle(0) {}
		GlVertexArray(GlProgram* program) : _program(program), _vertices(0), _indices(0), _elements(0), _handle(0) {}
		~GlVertexArray() {}

		void create();
		void create(
			const void* data, unsigned int bytes,
			const int* indices, unsigned int elements,
			unsigned int components, attribute attributes, const unsigned int* strides, const unsigned int* offsets);
		void create(Mesh::Shape* shape);
		void release();

		void draw();

		const handleType handle() const;

	protected:

		GlProgram* _program;
		GlBuffer* _vertices;
		GlBuffer* _indices;
		unsigned int _elements;
		handleType _handle;

	};

}

#endif