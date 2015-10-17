#ifndef FBOX_GLFRAMEBUFFER_H
#define FBOX_GLFRAMEBUFFER_H

namespace fbox
{
	namespace gl
	{

		class FBOXAPI Framebuffer
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

			Framebuffer() : clearColor(0.0f), _dimensions(400, 300), _main(0), _depth(0), _handle(0), _type(TYPE_NONE) {}
			Framebuffer(frameType type, glm::ivec2& dimensions) : clearColor(0.0f), _dimensions(dimensions), _main(0), _depth(0), _handle(0), _type(type) {}
			~Framebuffer() {}

			void create();
			void release();

			void bind();
			void unbind();

			void clear();
			void resize(glm::ivec2& dimensions);

			void blit(Framebuffer* destination);

			const handleType handle() const;
			Texture* main() const;
			Texture* depth() const;
			glm::ivec2 dimensions() const;

			static void screen(glm::ivec2& dimensions);

			glm::vec4 clearColor;

		protected:

			Texture* _main;
			Texture* _depth;
			handleType _handle;
			frameType _type;
			glm::ivec2 _dimensions;

			static glm::ivec2 _screen;

		};

	}
}

#endif