
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace gl
	{

		FBOXAPI void Uniform::grab()
		{
			if (this->_program != 0 && !this->_name.empty())
			{
				this->_handle = glGetUniformLocation(this->_program->handle(), (const char*)this->_name.data());
			}
		}

		FBOXAPI void Uniform::bind1i(int x)
		{
			if (this->_handle >= 0)
			{
				glUniform1i(this->_handle, (GLint)x);
			}
		}
		FBOXAPI void Uniform::bind2i(const glm::ivec2& v)
		{
			if (this->_handle >= 0)
			{
				glUniform2i(this->_handle, (GLint)v.x, (GLint)v.y);
			}
		}
		FBOXAPI void Uniform::bind3i(const glm::ivec3& v)
		{
			if (this->_handle >= 0)
			{
				glUniform3i(this->_handle, (GLint)v.x, (GLint)v.y, (GLint)v.z);
			}
		}
		FBOXAPI void Uniform::bind4i(const glm::ivec4& v)
		{
			if (this->_handle >= 0)
			{
				glUniform4i(this->_handle, (GLint)v.x, (GLint)v.y, (GLint)v.z, (GLint)v.w);
			}
		}
		FBOXAPI void Uniform::bind1b(bool x)
		{
			if (this->_handle >= 0)
			{
				glUniform1i(this->_handle, (GLint)x);
			}
		}
		FBOXAPI void Uniform::bind1f(float x)
		{
			if (this->_handle >= 0)
			{
				glUniform1f(this->_handle, (GLfloat)x);
			}
		}
		FBOXAPI void Uniform::bind2f(const glm::vec2& v)
		{
			if (this->_handle >= 0)
			{
				glUniform2f(this->_handle, (GLfloat)v.x, (GLfloat)v.y);
			}
		}
		FBOXAPI void Uniform::bind3f(const glm::vec3& v)
		{
			if (this->_handle >= 0)
			{
				glUniform3f(this->_handle, (GLfloat)v.x, (GLfloat)v.y, (GLfloat)v.z);
			}
		}
		FBOXAPI void Uniform::bind4f(const glm::vec4& v)
		{
			if (this->_handle >= 0)
			{
				glUniform4f(this->_handle, (GLfloat)v.x, (GLfloat)v.y, (GLfloat)v.z, (GLfloat)v.w);
			}
		}
		FBOXAPI void Uniform::bind1iv(const int* buffer, unsigned int count)
		{
			if (this->_handle >= 0)
			{
				glUniform1iv(this->_handle, count, (const GLint*)buffer);
			}
		}
		FBOXAPI void Uniform::bind2iv(const glm::ivec2* buffer, unsigned int count)
		{
			if (this->_handle >= 0)
			{
				glUniform2iv(this->_handle, count, (const GLint*)buffer);
			}
		}
		FBOXAPI void Uniform::bind3iv(const glm::ivec3* buffer, unsigned int count)
		{
			if (this->_handle >= 0)
			{
				glUniform3iv(this->_handle, count, (const GLint*)buffer);
			}
		}
		FBOXAPI void Uniform::bind4iv(const glm::ivec4* buffer, unsigned int count)
		{
			if (this->_handle >= 0)
			{
				glUniform4iv(this->_handle, count, (const GLint*)buffer);
			}
		}
		FBOXAPI void Uniform::bind1fv(const float* buffer, unsigned int count)
		{
			if (this->_handle >= 0)
			{
				glUniform1fv(this->_handle, count, (const GLfloat*)buffer);
			}
		}
		FBOXAPI void Uniform::bind2fv(const glm::vec2* buffer, unsigned int count)
		{
			if (this->_handle >= 0)
			{
				glUniform2fv(this->_handle, count, (const GLfloat*)buffer);
			}
		}
		FBOXAPI void Uniform::bind3fv(const glm::vec3* buffer, unsigned int count)
		{
			if (this->_handle >= 0)
			{
				glUniform3fv(this->_handle, count, (const GLfloat*)buffer);
			}
		}
		FBOXAPI void Uniform::bind4fv(const glm::vec4* buffer, unsigned int count)
		{
			if (this->_handle >= 0)
			{
				glUniform4fv(this->_handle, count, (const GLfloat*)buffer);
			}
		}
		FBOXAPI void Uniform::bind3x3f(const glm::mat3& m)
		{
			if (this->_handle >= 0)
			{
				glUniformMatrix3fv(this->_handle, 1, GL_FALSE, (const GLfloat*)glm::value_ptr(m));
			}
		}
		FBOXAPI void Uniform::bind4x4f(const glm::mat4& m)
		{
			if (this->_handle >= 0)
			{
				glUniformMatrix4fv(this->_handle, 1, GL_FALSE, (const GLfloat*)glm::value_ptr(m));
			}
		}

		FBOXAPI void Uniform::texture(Texture* texture, unsigned int slot)
		{
			if (texture == 0)
			{
				return;
			}

			if (this->_handle >= 0)
			{
				glUniform1i(this->_handle, (GLint)slot);
			}

			switch (slot)
			{
			case 0:
				glActiveTexture(GL_TEXTURE0);
				break;
			case 1:
				glActiveTexture(GL_TEXTURE1);
				break;
			case 2:
				glActiveTexture(GL_TEXTURE2);
				break;
			case 3:
				glActiveTexture(GL_TEXTURE3);
				break;
			case 4:
				glActiveTexture(GL_TEXTURE4);
				break;
			case 5:
				glActiveTexture(GL_TEXTURE5);
				break;
			case 6:
				glActiveTexture(GL_TEXTURE6);
				break;
			case 7:
				glActiveTexture(GL_TEXTURE7);
				break;
			case 8:
				glActiveTexture(GL_TEXTURE8);
				break;
			case 9:
				glActiveTexture(GL_TEXTURE9);
				break;
			case 10:
				glActiveTexture(GL_TEXTURE10);
				break;
			case 11:
				glActiveTexture(GL_TEXTURE11);
				break;
			case 12:
				glActiveTexture(GL_TEXTURE12);
				break;
			case 13:
				glActiveTexture(GL_TEXTURE13);
				break;
			case 14:
				glActiveTexture(GL_TEXTURE14);
				break;
			case 15:
				glActiveTexture(GL_TEXTURE15);
				break;
			case 16:
				glActiveTexture(GL_TEXTURE16);
				break;
			case 17:
				glActiveTexture(GL_TEXTURE17);
				break;
			case 18:
				glActiveTexture(GL_TEXTURE18);
				break;
			case 19:
				glActiveTexture(GL_TEXTURE19);
				break;
			case 20:
				glActiveTexture(GL_TEXTURE20);
				break;
			case 21:
				glActiveTexture(GL_TEXTURE21);
				break;
			case 22:
				glActiveTexture(GL_TEXTURE22);
				break;
			case 23:
				glActiveTexture(GL_TEXTURE23);
				break;
			case 24:
				glActiveTexture(GL_TEXTURE24);
				break;
			case 25:
				glActiveTexture(GL_TEXTURE25);
				break;
			case 26:
				glActiveTexture(GL_TEXTURE26);
				break;
			case 27:
				glActiveTexture(GL_TEXTURE27);
				break;
			case 28:
				glActiveTexture(GL_TEXTURE28);
				break;
			case 29:
				glActiveTexture(GL_TEXTURE29);
				break;
			case 30:
				glActiveTexture(GL_TEXTURE30);
				break;
			case 31:
				glActiveTexture(GL_TEXTURE31);
				break;
			default:
				break;
			}

			glBindTexture(texture->target(), texture->handle());
		}

		FBOXAPI bool Uniform::valid() const
		{
			return this->_handle >= 0;
		}

		FBOXAPI const Uniform::locType Uniform::handle() const
		{
			return this->_handle;
		}
		FBOXAPI const std::string Uniform::name() const
		{
			return this->_name;
		}

	}
}