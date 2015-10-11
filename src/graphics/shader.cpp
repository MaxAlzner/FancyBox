
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace gl
	{

		FBOXAPI void Shader::read(string& filename)
		{
			if (this->_raw != 0)
			{
				this->release();
			}

			FILE* file = fopen(filename.data(), "r");
			if (file != 0)
			{
				fseek(file, 0, SEEK_END);
				long size = ftell(file);
				this->_raw = (char*)malloc(size + 1);
				memset(this->_raw, 0, size + 1);
				fseek(file, 0, SEEK_SET);
				fread(this->_raw, size, 1, file);
			}
		}
		FBOXAPI void Shader::read(const char* filename)
		{
			this->read(string(filename));
		}

		FBOXAPI void Shader::compile()
		{
			if (this->_type == 0)
			{
				return;
			}

			if (this->_raw == 0)
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

			this->_handle = glCreateShader(type);
			glShaderSource(this->_handle, 1, (const char**)&this->_raw, 0);
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
		FBOXAPI void Shader::release()
		{
			if (this->_handle != 0)
			{
				glDeleteShader(this->_handle);
				this->_handle = 0;
			}

			if (this->_raw != 0)
			{
				delete[] this->_raw;
				this->_raw = 0;
			}
		}

		FBOXAPI const Shader::handleType Shader::handle() const
		{
			return this->_handle;
		}

	}
}