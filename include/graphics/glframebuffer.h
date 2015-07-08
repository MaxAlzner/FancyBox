#ifndef FBOX_FRAMEBUFFER_H
#define FBOX_FRAMEBUFFER_H

namespace fbox
{

	class FBOXAPI GlFramebuffer
	{
	public:

		typedef GLuint handleType;

		enum frameType
		{
			TYPE_NONE,
			TYPE_DRAW,
			TYPE_COLOR,
			TYPE_DEPTH,
		};

		GlFramebuffer() : clearColor(0.0f), _dimensions(400, 300), _main(0), _depth(0), _handle(0), _type(TYPE_NONE) {}
		GlFramebuffer(frameType type, ivec2& dimensions) : clearColor(0.0f), _dimensions(dimensions), _main(0), _depth(0), _handle(0), _type(type) {}
		~GlFramebuffer() {}

		void create();
		void release();

		void bind();
		void unbind();

		void clear();
		void resize(ivec2& dimensions);

		void blit(GlFramebuffer* destination);

		const handleType handle() const;
		GlTexture* main() const;
		GlTexture* depth() const;
		ivec2 dimensions() const;

		Color clearColor;

	protected:

		GlTexture* _main;
		GlTexture* _depth;
		handleType _handle;
		frameType _type;
		ivec2 _dimensions;

	};

}

#endif