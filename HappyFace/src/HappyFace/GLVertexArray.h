#pragma once

#include <glad/glad.h>

class GLVertexArray
{
public:
	enum BufferType : int {
		ARRAY = GL_ARRAY_BUFFER,
		ELEMENT = GL_ELEMENT_ARRAY_BUFFER
	};

	enum DrawMode : int {
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW,
		STREAM = GL_STREAM_DRAW
	};

public:
	GLVertexArray() noexcept;

	inline unsigned int getID() const { return m_id; }

	void bind() noexcept;
	void attachBuffer(const BufferType type, const size_t size, const void* data, const DrawMode mode) noexcept;
	void setVertexAttribPointers() noexcept;
	void unbind() noexcept;
	void deleteVAO() noexcept;

private:
	unsigned int m_id;
};