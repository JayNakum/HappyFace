#include "Model.h"

void Model::attachMesh(const Mesh& mesh)
{
	m_meshes.push_back(mesh);
}

void Model::translate(const glm::vec3& position)
{
	m_position = position;
}

void Model::rotate(const float radians, const glm::vec3& axis)
{
	m_radians = radians;
	m_axis = axis;
}

void Model::scale(const glm::vec3& scale)
{
	m_scale = scale;
}

void Model::deleteModel()
{
	for (auto& mesh : m_meshes) {
		mesh.getVAO().deleteVAO();
		mesh.getTexture().deleteTexture();
	}
	
	m_meshes.clear();
}
