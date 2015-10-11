
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace gl
	{

		FBOXAPI void Framebuffer::create()
		{
			glGenFramebuffers(1, &this->_handle);
			glBindFramebuffer(GL_FRAMEBUFFER, this->_handle);

			if (this->_type == TYPE_COLOR || this->_type == TYPE_DRAW)
			{
				this->_main = new Texture;
				this->_main->create();
				glBindTexture(GL_TEXTURE_2D, this->_main->handle());
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->_dimensions.x, this->_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_INT, NULL);
				glGenerateMipmap(GL_TEXTURE_2D);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->_main->handle(), 0);

				glBindTexture(GL_TEXTURE_2D, 0);
			}

			if (this->_type == TYPE_DEPTH || this->_type == TYPE_DRAW)
			{
				this->_depth = new Texture;
				this->_depth->create();
				glBindTexture(GL_TEXTURE_2D, this->_depth->handle());
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, this->_dimensions.x, this->_dimensions.y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

				glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->_depth->handle(), 0);

				glBindTexture(GL_TEXTURE_2D, 0);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		FBOXAPI void Framebuffer::release()
		{
			if (this->_handle != 0)
			{
				glDeleteFramebuffers(1, &this->_handle);

				if (this->_main != 0)
				{
					this->_main->release();
					delete this->_main;
					this->_main = 0;
				}

				if (this->_depth != 0)
				{
					this->_depth->release();
					delete this->_depth;
					this->_depth = 0;
				}
			}
		}

		FBOXAPI void Framebuffer::bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, this->_handle);
			glViewport(0, 0, this->_dimensions.x, this->_dimensions.y);
			glClearColor(this->clearColor.r, this->clearColor.g, this->clearColor.b, this->clearColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		FBOXAPI void Framebuffer::unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		FBOXAPI void Framebuffer::clear()
		{
			glClearColor(this->clearColor.r, this->clearColor.g, this->clearColor.b, this->clearColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		FBOXAPI void Framebuffer::resize(glm::ivec2& dimensions)
		{
			this->_dimensions = dimensions;
		}

		FBOXAPI void Framebuffer::blit(Framebuffer* destination)
		{
			glBindFramebuffer(GL_READ_FRAMEBUFFER, this->_handle);

			if (destination == 0)
			{
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
				if (this->_main != 0)
				{
					glBlitFramebuffer(0, 0, this->_dimensions.x, this->_dimensions.y, 0, 0, this->_dimensions.x, this->_dimensions.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
				}

				if (this->_depth != 0)
				{
					glBlitFramebuffer(0, 0, this->_dimensions.x, this->_dimensions.y, 0, 0, this->_dimensions.x, this->_dimensions.y, GL_DEPTH_BUFFER_BIT, GL_LINEAR);
				}
			}
			else
			{
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER, destination->_handle);
				if (this->_main != 0)
				{
					glBlitFramebuffer(0, 0, this->_dimensions.x, this->_dimensions.y, 0, 0, destination->_dimensions.x, destination->_dimensions.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
				}

				if (this->_depth != 0)
				{
					glBlitFramebuffer(0, 0, this->_dimensions.x, this->_dimensions.y, 0, 0, destination->_dimensions.x, destination->_dimensions.y, GL_DEPTH_BUFFER_BIT, GL_LINEAR);
				}
			}

			glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		}

		FBOXAPI const Framebuffer::handleType Framebuffer::handle() const
		{
			return this->_handle;
		}
		FBOXAPI Texture* Framebuffer::main() const
		{
			return this->_main;
		}
		FBOXAPI Texture* Framebuffer::depth() const
		{
			return this->_depth;
		}
		FBOXAPI glm::ivec2 Framebuffer::dimensions() const
		{
			return this->_dimensions;
		}

	}
}