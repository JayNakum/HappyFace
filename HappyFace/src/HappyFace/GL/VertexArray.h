#pragma once

#include <glad/glad.h>

namespace GL {
	class VertexArray
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

		enum AttribType : int {
			INT = GL_INT,
			FLOAT = GL_FLOAT
		};

	public:
		inline unsigned int getID() const { return m_id; }

		void create() noexcept;
		void bind() const noexcept;
		void attachBuffer(const BufferType type, const size_t size, const void* data, const DrawMode mode) noexcept;
		void enableAttribute(const unsigned int index, const int size, AttribType type, const unsigned int offset, const void* data) noexcept;
		void unbind() const noexcept;
		void deleteVAO() noexcept;

	private:
		unsigned int m_id;
	};
}
