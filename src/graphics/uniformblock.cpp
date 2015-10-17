
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace gl
	{

		FBOXAPI void UniformBlock::grab()
		{
			if (this->_program != 0)
			{
				this->_handle = glGetUniformBlockIndex(this->_program->handle(), (const char*)this->_name.data());
			}

			if (this->valid())
			{
				if (this->_buffer == 0)
				{
					this->_buffer = new Buffer(Buffer::TARGET_UNIFORM, Buffer::USAGE_DYNAMIC_DRAW);
					this->_buffer->create();
				}

				this->_buffer->bind();
				glBindBufferBase(GL_UNIFORM_BUFFER, this->_handle, this->_buffer->handle());
				this->_buffer->unbind();
			}
		}
		FBOXAPI void UniformBlock::release()
		{
			if (this->_buffer != 0)
			{
				this->_buffer->release();
				delete this->_buffer;
				this->_buffer = 0;
			}
		}

		FBOXAPI void UniformBlock::bind(unsigned int index, void* data, unsigned int bytes)
		{
			glUniformBlockBinding(this->_program->handle(), this->_handle, index);
			if (this->_buffer != 0)
			{
				this->_buffer->map(data, bytes);
			}
		}

		FBOXAPI bool UniformBlock::valid() const
		{
			return this->_program != 0 && this->_handle != GL_INVALID_INDEX;
		}

		FBOXAPI const UniformBlock::indexType UniformBlock::handle() const
		{
			return this->_handle;
		}
		FBOXAPI const string UniformBlock::name() const
		{
			return this->_name;
		}
		FBOXAPI const Buffer* UniformBlock::buffer() const
		{
			return this->_buffer;
		}

	}
}