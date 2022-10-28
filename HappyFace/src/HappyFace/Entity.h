#pragma once

#include "GLVertexArray.h"
#include "Vertex.h"
#include "GLTexture.h"

#include <vector>

class Entity
{
public:
	Entity(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	~Entity();

	inline GLVertexArray getVAO() const { return m_vao; }
	inline std::vector<unsigned int> getIndices() const { return m_indices; }

	inline GLTexture getTexture() const { return m_texture; }

private:
	GLVertexArray m_vao;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	GLTexture m_texture;
};
