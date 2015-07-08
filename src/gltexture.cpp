
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void GlTexture::create()
	{
		glGenTextures(1, &this->_handle);
		this->_target = GL_TEXTURE_2D;
	}
	FBOXAPI void GlTexture::create(Image::Surface* surface)
	{
		if (surface == 0 || surface->isEmpty())
		{
			return;
		}

		this->_target = GL_TEXTURE_2D;
		glGenTextures(1, &this->_handle);
		glBindTexture(this->_target, this->_handle);

		surface->reformat(Image::PIXELFORMAT_RGBA);

		glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(this->_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(this->_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
		glPixelStorei(GL_PACK_SWAP_BYTES, GL_FALSE);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glPixelStorei(GL_PACK_ALIGNMENT, 4);
		glTexImage2D(this->_target, 0, GL_RGBA, surface->width(), surface->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->map());
		glGenerateMipmap(this->_target);

		glBindTexture(this->_target, 0);
	}
	FBOXAPI void GlTexture::release()
	{
		if (this->_handle != 0)
		{
			glDeleteTextures(1, &this->_handle);
		}
	}

	FBOXAPI void GlTexture::parameter(texParameter param)
	{
		glBindTexture(this->_target, this->_handle);
		switch (param)
		{
		case PARAM_WRAP_U_REPEAT:
			glTexParameteri(this->_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
			break;
		case PARAM_WRAP_V_REPEAT:
			glTexParameteri(this->_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		case PARAM_WRAP_U_CLAMP:
			glTexParameteri(this->_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
			break;
		case PARAM_WRAP_V_CLAMP:
			glTexParameteri(this->_target, GL_TEXTURE_WRAP_T, GL_CLAMP);
			break;
		case PARAM_MIN_FILTER_NEAREST:
			glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
		case PARAM_MIN_FILTER_LINEAR:
			glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		case PARAM_MIN_FILTER_NEAREST_MIPMAP_NEAREST:
			glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			break;
		case PARAM_MIN_FILTER_LINEAR_MIPMAP_NEAREST:
			glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			break;
		case PARAM_MIN_FILTER_NEAREST_MIPMAP_LINEAR:
			glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			break;
		case PARAM_MIN_FILTER_LINEAR_MIPMAP_LINEAR:
			glTexParameteri(this->_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			break;
		case PARAM_MAG_FILTER_NEAREST:
			glTexParameteri(this->_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case PARAM_MAG_FILTER_LINEAR:
			glTexParameteri(this->_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		default:
			break;
		}
		glBindTexture(this->_target, 0);
	}
	FBOXAPI void GlTexture::parameter(texParameter param, int value)
	{
		glBindTexture(this->_target, this->_handle);
		switch (param)
		{
		case PARAM_MIN_LOD:
			glTexParameteri(this->_target, GL_TEXTURE_MIN_LOD, value);
			break;
		case PARAM_MAX_LOD:
			glTexParameteri(this->_target, GL_TEXTURE_MAX_LOD, value);
			break;
		case PARAM_MAX_LEVEL:
			glTexParameteri(this->_target, GL_TEXTURE_MAX_LEVEL, value);
			break;
		default:
			break;
		}
		glBindTexture(this->_target, 0);
	}
	FBOXAPI void GlTexture::parameter(texParameter param, float value)
	{
		glBindTexture(this->_target, this->_handle);
		switch (param)
		{
		case PARAM_SWIZZLE_R:
			glTexParameterf(this->_target, GL_TEXTURE_SWIZZLE_R, value);
			break;
		case PARAM_SWIZZLE_G:
			glTexParameterf(this->_target, GL_TEXTURE_SWIZZLE_G, value);
			break;
		case PARAM_SWIZZLE_B:
			glTexParameterf(this->_target, GL_TEXTURE_SWIZZLE_B, value);
			break;
		case PARAM_SWIZZLE_A:
			glTexParameterf(this->_target, GL_TEXTURE_SWIZZLE_A, value);
			break;
		default:
			break;
		}
		glBindTexture(this->_target, 0);
	}

	FBOXAPI const GlTexture::handleType GlTexture::handle() const
	{
		return this->_handle;
	}
	FBOXAPI const GlTexture::targetType GlTexture::target() const
	{
		return this->_target;
	}

}