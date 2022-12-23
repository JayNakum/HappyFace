#include "GLVertexArray.h"

void GLVertexArray::create() noexcept
{
	glGenVertexArrays(1, &m_id);
}

void GLVertexArray::bind() const noexcept
{
	glBindVertexArray(m_id);
}

void GLVertexArray::attachBuffer(const BufferType type, const size_t size, const void* data, const DrawMode mode) noexcept
{
	bind();
	unsigned int buffer;
	glGenBuffers(1, &buffer);

	glBindBuffer(type, buffer);
	glBufferData(type, size, data, mode);
}

void GLVertexArray::enableAttribute(const unsigned int index, const int size, AttribType type, const unsigned int offset, const void* data) noexcept
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, GL_FALSE, offset, data);
}

void GLVertexArray::unbind() const noexcept
{
	glBindVertexArray(0);
}

void GLVertexArray::deleteVAO() noexcept
{
	glDeleteVertexArrays(1, &m_id);
}
