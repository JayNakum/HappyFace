#include "Entity.h"

#include "GLShader.h"
#include "ResourceManager.h"

Entity::Entity(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	: m_vertices(vertices), m_indices(indices), 
	m_texture(ResourceManager::getInstance().loadTexture("res/textures/wall.jpg", "texture_diffuse"))
{
	m_vao.create();
	m_vao.bind();

	m_vao.attachBuffer(GLVertexArray::BufferType::ARRAY, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GLVertexArray::DrawMode::STATIC);
	m_vao.attachBuffer(GLVertexArray::BufferType::ELEMENT, m_indices.size() * sizeof(unsigned int), &m_indices[0], GLVertexArray::DrawMode::STATIC);

	const static auto stride = sizeof(Vertex);

	m_vao.enableAttribute(0, 3, GLVertexArray::FLOAT, stride, nullptr);
	m_vao.enableAttribute(1, 2, GLVertexArray::FLOAT, stride, reinterpret_cast<void*>(offsetof(Vertex, texCoords)));
	m_vao.enableAttribute(2, 3, GLVertexArray::FLOAT, stride, reinterpret_cast<void*>(offsetof(Vertex, normal)));
	m_vao.enableAttribute(3, 3, GLVertexArray::FLOAT, stride, reinterpret_cast<void*>(offsetof(Vertex, tangent)));

	m_vao.unbind();
}

Entity::~Entity()
{
	m_vao.deleteVAO();
	m_vertices.clear();
	m_indices.clear();
}
