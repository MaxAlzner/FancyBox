
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace gl
	{

		FBOXAPI void Shader::compile(const std::string& filename)
		{
			if (this->_type == 0)
			{
				return;
			}

			if (this->_handle == 0)
			{
				GLenum type = GL_NONE;
				switch (this->_type)
				{
				case TYPE_VERTEX: type = GL_VERTEX_SHADER; break;
				case TYPE_FRAGMENT: type = GL_FRAGMENT_SHADER; break;
				case TYPE_GEOMETRY: type = GL_GEOMETRY_SHADER; break;
				default: break;
				}

				this->_handle = glCreateShader(type);
			}

			char* raw = 0;
			if (Import::Read(filename, &raw) > 0)
			{
				glShaderSource(this->_handle, 1, (const char**)&raw, 0);
				glCompileShader(this->_handle);
				int logLength = 0;
				glGetShaderiv(this->_handle, GL_INFO_LOG_LENGTH, &logLength);
				if (logLength > 0)
				{
					char* errorBuffer = new char[512];
					memset(errorBuffer, 0, sizeof(char) * 512);
					glGetShaderInfoLog(this->_handle, 512, &logLength, errorBuffer);
					printf("%s\n", errorBuffer);
					delete[] errorBuffer;
				}

				delete[] raw;
			}
		}
		FBOXAPI void Shader::compile(const char* filename)
		{
			this->compile(std::string(filename));
		}

		FBOXAPI void Shader::release()
		{
			if (this->_handle != 0)
			{
				glDeleteShader(this->_handle);
				this->_handle = 0;
			}
		}

		FBOXAPI const Shader::handleType Shader::handle() const
		{
			return this->_handle;
		}

	}
}