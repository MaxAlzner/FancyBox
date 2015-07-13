#ifndef FBOX_MESHFILTER_H
#define FBOX_MESHFILTER_H

namespace fbox
{

	class FBOXAPI MeshFilter : public Component
	{
	public:

		inline MeshFilter() : Component("MeshFilter") {}
		inline MeshFilter(GlVertexArray* vao) : Component("MeshFilter"), vao(vao) {}
		inline ~MeshFilter() {}

		void bind();

		GlVertexArray* vao;

	};

}

#endif