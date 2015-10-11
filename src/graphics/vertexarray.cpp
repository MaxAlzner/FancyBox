
#define FBOX_EXPORT
#include "../../include/FancyBox.h"

namespace fbox
{
	namespace gl
	{

		FBOXAPI void VertexArray::create()
		{
			glGenVertexArrays(1, &this->_handle);
		}
		FBOXAPI void VertexArray::create(
			const void* data, unsigned int bytes,
			const int* indices, unsigned int elements,
			unsigned int components, attribute attributes, const unsigned int* strides, const unsigned int* offsets)
		{
			if (data == 0 || bytes < 1 || indices == 0 || elements < 1 || strides == 0 || offsets == 0 || this->_program == 0)
			{
				return;
			}

			glGenVertexArrays(1, &this->_handle);
			glBindVertexArray(this->_handle);

			this->_vertices = new Buffer(Buffer::TARGET_ARRAY, Buffer::USAGE_STATIC_DRAW);
			this->_vertices->create();
			this->_vertices->map(data, bytes);

			this->_vertices->bind();
			for (unsigned int i = 0; i < components; i++)
			{
				if (attributes & INCLUDE_VERTEX)
				{
					glBindAttribLocation(this->_program->handle(), i, "vertex");
				}
				else if (attributes & INCLUDE_TEXCOORD)
				{
					glBindAttribLocation(this->_program->handle(), i, "uv");
				}
				else if (attributes & INCLUDE_NORMAL)
				{
					glBindAttribLocation(this->_program->handle(), i, "normal");
				}
				else if (attributes & INCLUDE_BINORMAL)
				{
					glBindAttribLocation(this->_program->handle(), i, "binormal");
				}
				else if (attributes & INCLUDE_TANGENT)
				{
					glBindAttribLocation(this->_program->handle(), i, "tangent");
				}
				else if (attributes & INCLUDE_BONEWEIGHT)
				{
					glBindAttribLocation(this->_program->handle(), i, "weight");
				}
				else if (attributes & INCLUDE_BONEINDEX)
				{
					glBindAttribLocation(this->_program->handle(), i, "boneIndex");
				}

				glVertexAttribPointer(i, strides[i], GL_FLOAT, GL_FALSE, strides[i] * sizeof(float), (const GLvoid*)offsets[i]);
				glEnableVertexAttribArray(i);
			}

			this->_vertices->unbind();

			this->_indices = new Buffer(Buffer::TARGET_ELEMENT_ARRAY, Buffer::USAGE_STATIC_DRAW);
			this->_indices->create();
			this->_indices->map(indices, sizeof(int) * elements);
			this->_elements = elements;

			glBindVertexArray(0);
		}
		FBOXAPI void VertexArray::create(shape* shape)
		{
			if (shape == 0 || shape->empty() || this->_program == 0)
			{
				return;
			}

			const int stride =
				shape->vertices.stride +
				shape->texcoords.stride +
				shape->normals.stride +
				shape->tangents.stride +
				shape->binormals.stride;

			glGenVertexArrays(1, &this->_handle);
			glBindVertexArray(this->_handle);

			this->_vertices = new Buffer(Buffer::TARGET_ARRAY, Buffer::USAGE_STATIC_DRAW);
			this->_vertices->create();
			this->_vertices->map(shape->vertices.buffer, shape->elements() * stride);

			this->_vertices->bind();
			glBindAttribLocation(this->_program->handle(), 0, "vertex");
			glBindAttribLocation(this->_program->handle(), 1, "uv");
			glBindAttribLocation(this->_program->handle(), 2, "normal");
			glBindAttribLocation(this->_program->handle(), 3, "tangent");
			glBindAttribLocation(this->_program->handle(), 4, "binormal");
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (const GLvoid*)shape->vertices.offset);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const GLvoid*)shape->texcoords.offset);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const GLvoid*)shape->normals.offset);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const GLvoid*)shape->tangents.offset);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const GLvoid*)shape->binormals.offset);
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glEnableVertexAttribArray(4);
			this->_vertices->unbind();

			this->_indices = new Buffer(Buffer::TARGET_ELEMENT_ARRAY, Buffer::USAGE_STATIC_DRAW);
			this->_indices->create();
			this->_indices->map(shape->indices.buffer, sizeof(int) * shape->indices.elements);
			this->_elements = shape->indices.elements;

			glBindVertexArray(0);
		}
		FBOXAPI void VertexArray::release()
		{
			this->_elements = 0;
			if (this->_handle != 0)
			{
				glDeleteVertexArrays(1, &this->_handle);
			}

			if (this->_vertices != 0)
			{
				this->_vertices->release();
				delete this->_vertices;
				this->_vertices = 0;
			}

			if (this->_vertices != 0)
			{
				this->_indices->release();
				delete this->_indices;
				this->_indices = 0;
			}
		}

		FBOXAPI void VertexArray::draw()
		{
			if (this->_handle != 0 && this->_vertices != 0 && this->_indices != 0 && this->_elements > 0)
			{
				glBindVertexArray(this->_handle);
				this->_indices->bind();
				glDrawElements(GL_TRIANGLES, this->_elements, GL_UNSIGNED_INT, 0);
				this->_indices->unbind();
				glBindVertexArray(0);
			}
		}

		FBOXAPI const VertexArray::handleType VertexArray::handle() const
		{
			return this->_handle;
		}

	}
}