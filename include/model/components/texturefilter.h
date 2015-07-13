#ifndef FBOX_TEXTUREFILTER_H
#define FBOX_TEXTUREFILTER_H

namespace fbox
{

	class FBOXAPI TextureFilter : public Component
	{
	public:

		enum TEXTURETYPE
		{
			TEXTURE_NONE,
			TEXTURE_COLOR,
			TEXTURE_NORMAL,
			TEXTURE_SPECULAR,
			TEXTURE_TRANSPARENCY,
			TEXTURE_REFLECT,
			TEXTURE_EMISSIVE,
			TEXTURE_DISPLACEMENT,
		};

		inline TextureFilter() : Component("TextureFilter"), type(TEXTURE_NONE) {}
		inline TextureFilter(const TEXTURETYPE type, GlTexture* texture) : Component("TextureFilter"), type(type), texture(texture) {}
		inline ~TextureFilter() {}

		void bind();

		const TEXTURETYPE type;
		GlTexture* texture;

	};

}

#endif