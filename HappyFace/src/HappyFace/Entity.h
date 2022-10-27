#pragma once

#include "GLShaderProgram.h"
#include "GLVertexArray.h"
#include "Vertex.h"

#include <vector>

class Entity
{
public:
	Entity(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	~Entity();

	inline GLShaderProgram getShader() const { return m_shader; }
	inline GLVertexArray getVAO() const { return m_vao; }
	inline std::vector<unsigned int> getIndices() const { return m_indices; }
	inline unsigned int getTextureID() const { return m_texture; }

private:
	GLShaderProgram m_shader;
	GLVertexArray m_vao;

	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	unsigned int m_texture;
};
