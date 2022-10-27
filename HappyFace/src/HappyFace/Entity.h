#pragma once

#include "GLVertexArray.h"
#include "GLShaderProgram.h"
#include "Vertex.h"

#include <vector>

class Entity
{
public:
	Entity(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

	inline GLShaderProgram getShader() const { return m_shader; }
	inline GLVertexArray getVAO() const { return m_vao; }
	inline std::vector<unsigned int> getIndices() const { return m_indices; }

private:
	GLShaderProgram m_shader;
	GLVertexArray m_vao;
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
};
