
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void GlBuffer::create()
	{
		glGenBuffers(1, &this->_handle);
	}
	FBOXAPI void GlBuffer::release()
	{
		if (this->_handle != 0)
		{
			glDeleteBuffers(1, &this->_handle);
		}
	}

	FBOXAPI void GlBuffer::bind()
	{
		GLenum target = GL_NONE;
		switch (this->_target)
		{
		case TARGET_ARRAY: target = GL_ARRAY_BUFFER; break;
		case TARGET_ELEMENT_ARRAY: target = GL_ELEMENT_ARRAY_BUFFER; break;
		case TARGET_TEXTURE: target = GL_TEXTURE_BUFFER; break;
		case TARGET_UNIFORM: target = GL_UNIFORM_BUFFER; break;
		default: break;
		}

		glBindBuffer(target, this->_handle);
	}
	FBOXAPI void GlBuffer::unbind()
	{
		GLenum target = GL_NONE;
		switch (this->_target)
		{
		case TARGET_ARRAY: target = GL_ARRAY_BUFFER; break;
		case TARGET_ELEMENT_ARRAY: target = GL_ELEMENT_ARRAY_BUFFER; break;
		case TARGET_TEXTURE: target = GL_TEXTURE_BUFFER; break;
		case TARGET_UNIFORM: target = GL_UNIFORM_BUFFER; break;
		default: break;
		}

		glBindBuffer(target, 0);
	}

	FBOXAPI void GlBuffer::map(const void* data, unsigned int bytes)
	{
		if (bytes < 1)
		{
			return;
		}

		GLenum target = GL_NONE;
		switch (this->_target)
		{
		case TARGET_ARRAY: target = GL_ARRAY_BUFFER; break;
		case TARGET_ELEMENT_ARRAY: target = GL_ELEMENT_ARRAY_BUFFER; break;
		case TARGET_TEXTURE: target = GL_TEXTURE_BUFFER; break;
		case TARGET_UNIFORM: target = GL_UNIFORM_BUFFER; break;
		default: break;
		}

		GLenum usage = GL_NONE;
		switch (this->_usage)
		{
		case USAGE_STATIC_DRAW: usage = GL_STATIC_DRAW;
		case USAGE_DYNAMIC_DRAW: usage = GL_DYNAMIC_DRAW;
		default: break;
		}

		glBindBuffer(target, this->_handle);
		glBufferData(target, bytes, data, usage);
		glBindBuffer(target, 0);
	}

	FBOXAPI const GlBuffer::handleType GlBuffer::handle() const
	{
		return this->_handle;
	}
	FBOXAPI const GlBuffer::targetType GlBuffer::target() const
	{
		return this->_target;
	}
	FBOXAPI const GlBuffer::usageType GlBuffer::usage() const
	{
		return this->_usage;
	}

}