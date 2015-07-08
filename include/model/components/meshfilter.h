#ifndef FBOX_MESHFILTER_H
#define FBOX_MESHFILTER_H

namespace fbox
{

	class FBOXAPI MeshFilter : public Component
	{
	public:

		inline MeshFilter() : Component("MeshFilter") {}
		inline MeshFilter(Mesh::Shape* shape) : Component("MeshFilter") { this->vao.create(shape); }
		inline ~MeshFilter() {}

		inline void bind();

		GlVertexArray vao;

	};

}

#endif