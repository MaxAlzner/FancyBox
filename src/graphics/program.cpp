
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace gl
	{

		FBOXAPI void Program::vertex(Shader* shader)
		{
			this->_vertex = shader;
		}
		FBOXAPI void Program::fragment(Shader* shader)
		{
			this->_fragment = shader;
		}
		FBOXAPI void Program::geometry(Shader* shader)
		{
			this->_geometry = shader;
		}

		FBOXAPI void Program::activate()
		{
			glUseProgram(this->_handle);
		}

		FBOXAPI void Program::link()
		{
			if (this->_vertex == 0)
			{
				return;
			}

			if (this->_fragment == 0)
			{
				return;
			}

			this->_handle = glCreateProgram();
			glAttachShader(this->_handle, this->_vertex->handle());
			glAttachShader(this->_handle, this->_fragment->handle());

			int logLength = 0;
			char* errorBuffer = new char[512];
			memset(errorBuffer, 0, sizeof(char) * 512);
			int linkStatus = GL_FALSE;

			glLinkProgram(this->_handle);
			glGetProgramiv(this->_handle, GL_LINK_STATUS, &linkStatus);
			glGetProgramiv(this->_handle, GL_INFO_LOG_LENGTH, &logLength);
			glGetProgramInfoLog(this->_handle, 512, &logLength, errorBuffer);

			if (logLength > 0)
			{
				printf(errorBuffer);
			}

			delete[] errorBuffer;
		}
		FBOXAPI void Program::release()
		{
			this->_vertex = 0;
			this->_fragment = 0;
			this->_geometry = 0;
			if (this->_handle != 0)
			{
				glDeleteProgram(this->_handle);
			}
		}

		FBOXAPI const Program::handleType Program::handle() const
		{
			return this->_handle;
		}

	}
}