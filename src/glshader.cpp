
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void GlShader::read(String filename)
	{
		this->_file = new File;
		this->_file->read(filename);
	}

	FBOXAPI void GlShader::compile()
	{
		if (this->_type == 0)
		{
			return;
		}

		if (this->_file == 0 || this->_file->isEmpty())
		{
			return;
		}

		GLenum type = GL_NONE;
		switch (this->_type)
		{
		case TYPE_VERTEX: type = GL_VERTEX_SHADER; break;
		case TYPE_FRAGMENT: type = GL_FRAGMENT_SHADER; break;
		case TYPE_GEOMETRY: type = GL_GEOMETRY_SHADER; break;
		default: break;
		}

		const char* source = *this->_file;
		this->_handle = glCreateShader(type);
		glShaderSource(this->_handle, 1, (const char**)&source, 0);
		glCompileShader(this->_handle);
		int logLength = 0;
		glGetShaderiv(this->_handle, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0)
		{
			char* errorBuffer = new char[512];
			memset(errorBuffer, 0, sizeof(char) * 512);
			glGetShaderInfoLog(this->_handle, 512, &logLength, errorBuffer);

			if (logLength > 0)
			{
				printf(errorBuffer);
			}

			delete[] errorBuffer;
		}
	}
	FBOXAPI void GlShader::release()
	{
		if (this->_handle != 0)
		{
			glDeleteShader(this->_handle);
			this->_handle = 0;
		}

		if (this->_file != 0)
		{
			this->_file->release();
			delete this->_file;
			this->_file = 0;
		}
	}

	FBOXAPI const GlShader::handleType GlShader::handle() const
	{
		return this->_handle;
	}

}