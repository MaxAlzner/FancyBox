
#define FBOX_EXPORT
#include "../include/FancyBox.h"

namespace fbox
{

	FBOXAPI void GlUniform::grab()
	{
		if (this->_program != 0 && !this->_name.isEmpty())
		{
			this->_handle = glGetUniformLocation(this->_program->handle(), (const char*)this->_name);
		}
	}

	FBOXAPI void GlUniform::bind1i(int x)
	{
		glUniform1i(this->_handle, (GLint)x);
	}
	FBOXAPI void GlUniform::bind2i(ivec2& v)
	{
		glUniform2i(this->_handle, (GLint)v.x, (GLint)v.y);
	}
	FBOXAPI void GlUniform::bind3i(ivec3& v)
	{
		glUniform3i(this->_handle, (GLint)v.x, (GLint)v.y, (GLint)v.z);
	}
	FBOXAPI void GlUniform::bind4i(ivec4& v)
	{
		glUniform4i(this->_handle, (GLint)v.x, (GLint)v.y, (GLint)v.z, (GLint)v.w);
	}
	FBOXAPI void GlUniform::bind1b(bool x)
	{
		glUniform1i(this->_handle, (GLint)x);
	}
	FBOXAPI void GlUniform::bind1f(float x)
	{
		glUniform1f(this->_handle, (GLfloat)x);
	}
	FBOXAPI void GlUniform::bind2f(vec2& v)
	{
		glUniform2f(this->_handle, (GLfloat)v.x, (GLfloat)v.y);
	}
	FBOXAPI void GlUniform::bind3f(vec3& v)
	{
		glUniform3f(this->_handle, (GLfloat)v.x, (GLfloat)v.y, (GLfloat)v.z);
	}
	FBOXAPI void GlUniform::bind4f(vec4& v)
	{
		glUniform4f(this->_handle, (GLfloat)v.x, (GLfloat)v.y, (GLfloat)v.z, (GLfloat)v.w);
	}
	FBOXAPI void GlUniform::bind4f(Color& c)
	{
		glUniform4f(this->_handle, (GLfloat)c.r, (GLfloat)c.g, (GLfloat)c.b, (GLfloat)c.a);
	}
	FBOXAPI void GlUniform::bind1iv(const int* buffer, unsigned int count)
	{
		glUniform1iv(this->_handle, count, (const GLint*)buffer);
	}
	FBOXAPI void GlUniform::bind2iv(const ivec2* buffer, unsigned int count)
	{
		glUniform2iv(this->_handle, count, (const GLint*)buffer);
	}
	FBOXAPI void GlUniform::bind3iv(const ivec3* buffer, unsigned int count)
	{
		glUniform3iv(this->_handle, count, (const GLint*)buffer);
	}
	FBOXAPI void GlUniform::bind4iv(const ivec4* buffer, unsigned int count)
	{
		glUniform4iv(this->_handle, count, (const GLint*)buffer);
	}
	FBOXAPI void GlUniform::bind1fv(const float* buffer, unsigned int count)
	{
		glUniform1fv(this->_handle, count, (const GLfloat*)buffer);
	}
	FBOXAPI void GlUniform::bind2fv(const vec2* buffer, unsigned int count)
	{
		glUniform2fv(this->_handle, count, (const GLfloat*)buffer);
	}
	FBOXAPI void GlUniform::bind3fv(const vec3* buffer, unsigned int count)
	{
		glUniform3fv(this->_handle, count, (const GLfloat*)buffer);
	}
	FBOXAPI void GlUniform::bind4fv(const vec4* buffer, unsigned int count)
	{
		glUniform4fv(this->_handle, count, (const GLfloat*)buffer);
	}
	FBOXAPI void GlUniform::bind4fv(const Color* buffer, unsigned int count)
	{
		glUniform4fv(this->_handle, count, (const GLfloat*)buffer);
	}
	FBOXAPI void GlUniform::bind3x3f(mat3& m)
	{
		glUniformMatrix3fv(this->_handle, 1, GL_FALSE, (const GLfloat*)m);
	}
	FBOXAPI void GlUniform::bind4x4f(mat4& m)
	{
		glUniformMatrix4fv(this->_handle, 1, GL_FALSE, (const GLfloat*)m);
	}

	FBOXAPI void GlUniform::texture(GlTexture* texture, unsigned int slot)
	{
		if (texture == 0)
		{
			return;
		}

		glUniform1i(this->_handle, (GLint)slot);

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

	FBOXAPI const GlUniform::locType GlUniform::handle() const
	{
		return this->_handle;
	}
	FBOXAPI const String GlUniform::name() const
	{
		return this->_name;
	}

}