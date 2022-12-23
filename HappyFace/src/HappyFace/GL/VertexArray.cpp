#include "VertexArray.h"

namespace GL {
	void VertexArray::create() noexcept
	{
		glGenVertexArrays(1, &m_id);
	}

	void VertexArray::bind() const noexcept
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::attachBuffer(const BufferType type, const size_t size, const void* data, const DrawMode mode) noexcept
	{
		bind();
		unsigned int buffer;
		glGenBuffers(1, &buffer);

		glBindBuffer(type, buffer);
		glBufferData(type, size, data, mode);
	}

	void VertexArray::enableAttribute(const unsigned int index, const int size, AttribType type, const unsigned int offset, const void* data) noexcept
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, GL_FALSE, offset, data);
	}

	void VertexArray::unbind() const noexcept
	{
		glBindVertexArray(0);
	}

	void VertexArray::deleteVAO() noexcept
	{
		glDeleteVertexArrays(1, &m_id);
	}
}
