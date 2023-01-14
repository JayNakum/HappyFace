#pragma once

#include <glm/vec3.hpp>

class Light
{
protected:
	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};
