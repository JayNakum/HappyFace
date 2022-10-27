#include "Entity.h"

#include "GLShader.h"

Entity::Entity(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	: m_vertices(vertices), m_indices(indices)
{
	GLShader vertexShader(GLShader::VERTEX, "res/shaders/test_shader.vs.glsl");
	GLShader fragmentShader(GLShader::FRAGMENT, "res/shaders/test_shader.fs.glsl");

	m_shader.attach(vertexShader.getID());
	m_shader.attach(fragmentShader.getID());
	m_shader.linkProgram();

	vertexShader.deleteShader();
	fragmentShader.deleteShader();

	m_shader.use();

	m_vao.create();
	m_vao.bind();

	m_vao.attachBuffer(GLVertexArray::BufferType::ARRAY, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GLVertexArray::DrawMode::STATIC);
	m_vao.attachBuffer(GLVertexArray::BufferType::ELEMENT, m_indices.size() * sizeof(unsigned int), &m_indices[0], GLVertexArray::DrawMode::STATIC);

	const static auto stride = sizeof(Vertex);

	m_vao.enableAttribute(0, 3, stride, nullptr);
	m_vao.enableAttribute(1, 2, stride, reinterpret_cast<void*>(offsetof(Vertex, TexCoords)));
	m_vao.enableAttribute(2, 3, stride, reinterpret_cast<void*>(offsetof(Vertex, Normal)));
	m_vao.enableAttribute(3, 3, stride, reinterpret_cast<void*>(offsetof(Vertex, Tangent)));

	m_vao.unbind();
}