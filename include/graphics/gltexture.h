#ifndef FBOX_TEXTURE_H
#define FBOX_TEXTURE_H

namespace fbox
{

	class FBOXAPI GlTexture
	{
	public:

		typedef GLuint handleType;
		typedef GLenum targetType;

		GlTexture() : _handle(0), _target(0) {}
		~GlTexture() {}

		enum texParameter
		{
			PARAM_NONE,
			PARAM_WRAP_U_REPEAT,
			PARAM_WRAP_V_REPEAT,
			PARAM_WRAP_U_CLAMP,
			PARAM_WRAP_V_CLAMP,
			PARAM_MIN_FILTER_NEAREST,
			PARAM_MIN_FILTER_LINEAR,
			PARAM_MIN_FILTER_NEAREST_MIPMAP_NEAREST,
			PARAM_MIN_FILTER_LINEAR_MIPMAP_NEAREST,
			PARAM_MIN_FILTER_NEAREST_MIPMAP_LINEAR,
			PARAM_MIN_FILTER_LINEAR_MIPMAP_LINEAR,
			PARAM_MAG_FILTER_NEAREST,
			PARAM_MAG_FILTER_LINEAR,
			PARAM_MIN_LOD,
			PARAM_MAX_LOD,
			PARAM_MAX_LEVEL,
			PARAM_SWIZZLE_R,
			PARAM_SWIZZLE_G,
			PARAM_SWIZZLE_B,
			PARAM_SWIZZLE_A,
		};

		void create();
		void create(Image::Surface* surface);
		void release();

		void parameter(texParameter param);
		void parameter(texParameter param, int value);
		void parameter(texParameter param, float value);

		const handleType handle() const;
		const targetType target() const;

	protected:

		handleType _handle;
		targetType _target;

	};

}

#endif