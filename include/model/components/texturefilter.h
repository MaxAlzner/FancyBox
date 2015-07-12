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

		enum SAMPLETYPE
		{
			SAMPLE_NEAREST,
			SAMPLE_LINEAR,
		};

		inline TextureFilter() : Component("TextureFilter"), type(TEXTURE_NONE) {}
		inline TextureFilter(Image::Surface* surface, const TEXTURETYPE type) : Component("TextureFilter"), type(type) { this->texture.create(surface); }
		inline ~TextureFilter() {}

		void bind();

		const TEXTURETYPE type;
		GlTexture texture;

	};

}

#endif