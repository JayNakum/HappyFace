#pragma once

#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Model
{
public:
	inline std::vector<Mesh> getMeshes() const { return m_meshes; }

	void attachMesh(const Mesh& mesh);
	void deleteModel();

	void translate(const glm::vec3& position);
	void rotate(const float radians, const glm::vec3& axis);
	void scale(const glm::vec3& scale);
	inline glm::mat4 getModelMatrix() const { return (glm::scale(glm::mat4(1.0f), m_scale) * glm::translate(glm::mat4(1.0f), m_position)); }

private:
	std::vector<Mesh> m_meshes;
	glm::vec3 m_scale, m_position, m_axis;
	float m_radians;
};
