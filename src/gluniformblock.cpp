
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void GlUniformBlock::grab()
	{
		if (this->_program != 0)
		{
			this->_handle = glGetUniformBlockIndex(this->_program->handle(), (const char*)this->_name);
		}

		if (this->_handle == GL_INVALID_INDEX)
		{
			return;
		}

		if (this->_buffer == 0)
		{
			this->_buffer = new GlBuffer(GlBuffer::TARGET_UNIFORM, GlBuffer::USAGE_DYNAMIC_DRAW);
			this->_buffer->create();
		}

		this->_buffer->bind();
		glBindBufferBase(GL_UNIFORM_BUFFER, this->_handle, this->_buffer->handle());
		this->_buffer->unbind();
	}
	FBOXAPI void GlUniformBlock::release()
	{
		if (this->_buffer != 0)
		{
			this->_buffer->release();
			delete this->_buffer;
			this->_buffer = 0;
		}
	}

	FBOXAPI void GlUniformBlock::bind(void* data, unsigned int bytes)
	{
		if (this->_buffer != 0)
		{
			this->_buffer->map(data, bytes);
		}
	}

	FBOXAPI const GlUniformBlock::indexType GlUniformBlock::handle() const
	{
		return this->_handle;
	}
	FBOXAPI const String GlUniformBlock::name() const
	{
		return this->_name;
	}
	FBOXAPI const GlBuffer* GlUniformBlock::buffer() const
	{
		return this->_buffer;
	}

}